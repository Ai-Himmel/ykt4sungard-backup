/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.lucene;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.service.CompanyLocalServiceUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.SystemProperties;

import edu.emory.mathcs.backport.java.util.concurrent.Semaphore;

import java.io.File;
import java.io.IOException;

import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.analysis.SimpleAnalyzer;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;

/**
 * <a href="IndexWriterFactory.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * Lucene only allows one IndexWriter to be open at a time. However, multiple
 * threads can use this single IndexWriter. This class manages a global
 * IndexWriter and uses reference counting to determine when it can be closed.
 * </p>
 *
 * <p>
 * To delete documents, IndexReaders are used but cannot delete while another
 * IndexWriter or IndexReader has the write lock. A semaphore is used to
 * serialize delete and add operations. If the shared IndexWriter is open,
 * concurrent add operations are permitted.
 * </p>
 *
 * @author Harry Mark
 * @author Brian Wing Shun Chan
 *
 */
public class IndexWriterFactory {

	public IndexWriterFactory() {
		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		// Create semaphores for all companies

		try {
			List companies = CompanyLocalServiceUtil.getCompanies();

			for (int i = 0; i < companies.size(); i++) {
				Company company = (Company)companies.get(i);

				_lockLookup.put(
					new Long(company.getCompanyId()), new Semaphore(1));
			}

			_lockLookup.put(new Long(CompanyImpl.SYSTEM), new Semaphore(1));
		}
		catch (SystemException se) {
			_log.error(se);
		}
	}

	public void acquireLock(long companyId, boolean needExclusive)
		throws InterruptedException {

		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		Semaphore lock = (Semaphore)_lockLookup.get(new Long(companyId));

		if (lock != null) {

			// Exclusive checking is used to prevent greedy IndexWriter sharing.
			// This registers a need for exclusive lock, and causes IndexWriters
			// to wait in FIFO order.

			if (needExclusive) {
				synchronized (_lockLookup) {
					_needExclusiveLock++;
				}
			}

			try {
				lock.acquire();
			}
			finally {
				if (needExclusive) {
					synchronized (_lockLookup) {
						_needExclusiveLock--;
					}
				}
			}
		}
		else {
			if (_log.isWarnEnabled()) {
				_log.warn("IndexWriterFactory lock not found for " + companyId);
			}
		}
	}

	public void deleteDocuments(long companyId, Term term)
		throws InterruptedException, IOException {

		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		try {
			acquireLock(companyId, true);

			IndexReader reader = null;

			try {
				reader = IndexReader.open(LuceneUtil.getLuceneDir(companyId));

				reader.deleteDocuments(term);
			}
			finally {
				if (reader != null) {
					reader.close();
				}
			}
		}
		finally {
			releaseLock(companyId);
		}
	}

	public IndexWriter getWriter(long companyId, boolean create)
		throws IOException {

		if (LuceneUtil.INDEX_READ_ONLY) {
			return getReadOnlyIndexWriter();
		}

		Long companyIdObj = new Long(companyId);

		boolean hasError = false;
		boolean newWriter = false;

		try {

			// If others need an exclusive lock, then wait to acquire lock
			// before proceeding. This prevents starvation.

			if (_needExclusiveLock > 0) {
				acquireLock(companyId, false);
				releaseLock(companyId);
			}

			synchronized(this) {
				IndexWriterData writerData =
					(IndexWriterData)_writerLookup.get(companyIdObj);

				if (writerData == null) {
                    newWriter = true;

					acquireLock(companyId, false);

                    IndexWriter writer = new IndexWriter(
                        LuceneUtil.getLuceneDir(companyId),
                        LuceneUtil.getAnalyzer(), create);

                    writer.setMergeFactor(_MERGE_FACTOR);

                    writerData = new IndexWriterData(companyId, writer, 0);

                    _writerLookup.put(companyIdObj, writerData);
                }

				writerData.setCount(writerData.getCount() + 1);

				return writerData.getWriter();
			}
		}
		catch (Exception e) {
			hasError = true;

			_log.error("Unable to create a new writer", e);

			throw new IOException("Unable to create a new writer");
		}
		finally {
			if (hasError && newWriter) {
				try {
					releaseLock(companyId);
				}
				catch (Exception e) {
				}
			}
		}
	}

	public void releaseLock(long companyId) {
		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		Semaphore lock = (Semaphore)_lockLookup.get(new Long(companyId));

		if (lock != null) {
			lock.release();
		}
	}

	public void write(long companyId) throws IOException {
		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		IndexWriterData writerData =
			(IndexWriterData)_writerLookup.get(new Long(companyId));

		if (writerData != null) {
			decrement(writerData);
		}
		else {
			if (_log.isWarnEnabled()) {
				_log.warn("IndexWriterData not found for " + companyId);
			}
		}
	}

	public void write(IndexWriter writer) throws IOException {
		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		boolean writerFound = false;

		synchronized(this) {
			if (!_writerLookup.isEmpty()) {
				Iterator itr = _writerLookup.values().iterator();

				while (itr.hasNext()) {
					IndexWriterData writerData = (IndexWriterData)itr.next();

					if (writerData.getWriter() == writer) {
						writerFound = true;

						decrement(writerData);

						break;
					}
				}
			}
		}

		if (!writerFound) {
			try {
				_optimizeCount++;

				if ((_OPTIMIZE_INTERVAL == 0) ||
					(_optimizeCount >= _OPTIMIZE_INTERVAL)) {

					writer.optimize();

					_optimizeCount = 0;
				}
			}
			finally {
				writer.close();
			}
		}
	}

	protected void decrement(IndexWriterData writerData) throws IOException {
		if (writerData.getCount() > 0) {
			writerData.setCount(writerData.getCount() - 1);

			if (writerData.getCount() == 0) {
				_writerLookup.remove(new Long(writerData.getCompanyId()));

				try {
					IndexWriter writer = writerData.getWriter();

					try {
						_optimizeCount++;

						if ((_OPTIMIZE_INTERVAL == 0) ||
							(_optimizeCount >= _OPTIMIZE_INTERVAL)) {

							writer.optimize();

							_optimizeCount = 0;
						}
					}
					finally {
						writer.close();
					}
				}
				catch (Exception e) {
					_log.error(e, e);
				}
				finally {
					releaseLock(writerData.getCompanyId());
				}
			}
		}
	}

	protected IndexWriter getReadOnlyIndexWriter() {
		if (_readOnlyIndexWriter == null) {
			try {
				if (_log.isInfoEnabled()) {
					_log.info("Disabling writing to index for this process");
				}

				_readOnlyIndexWriter = new ReadOnlyIndexWriter(
					getReadOnlyLuceneDir(), new SimpleAnalyzer(), true);
			}
			catch (IOException ioe) {
				throw new RuntimeException(ioe);
			}
		}

		return _readOnlyIndexWriter;
	}

	protected Directory getReadOnlyLuceneDir() throws IOException {
		if (_readOnlyLuceneDir == null) {
			String tmpDir = SystemProperties.get(SystemProperties.TMP_DIR);

			File dir = new File(tmpDir + "/liferay/lucene/empty");

			dir.mkdir();

			_readOnlyLuceneDir = FSDirectory.getDirectory(dir.getPath(), false);
		}

		return _readOnlyLuceneDir;
	}

	private static final int _MERGE_FACTOR = GetterUtil.getInteger(
		PropsUtil.get(PropsUtil.LUCENE_MERGE_FACTOR));

	private static final int _OPTIMIZE_INTERVAL = GetterUtil.getInteger(
		PropsUtil.get(PropsUtil.LUCENE_OPTIMIZE_INTERVAL));

	private static Log _log = LogFactory.getLog(IndexWriterFactory.class);

	private FSDirectory _readOnlyLuceneDir = null;
	private IndexWriter _readOnlyIndexWriter = null;
	private Map _lockLookup = CollectionFactory.getHashMap();
	private Map _writerLookup = CollectionFactory.getHashMap();
	private int _needExclusiveLock = 0;
	private int _optimizeCount = 0;

}