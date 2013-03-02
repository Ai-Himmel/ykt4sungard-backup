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

import com.liferay.portal.kernel.search.Indexer;
import com.liferay.portal.kernel.util.InstancePool;
import com.liferay.portal.kernel.util.ServerDetector;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.util.comparator.PortletLuceneComparator;
import com.liferay.util.Time;

import java.io.IOException;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.lang.time.StopWatch;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.index.IndexWriter;

/**
 * <a href="LuceneIndexer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LuceneIndexer implements Runnable {

	public LuceneIndexer(long companyId) {
		_companyId = companyId;
	}

	public void halt() {
	}

	public boolean isFinished() {
		return _finished;
	}

	public void run() {
		reIndex();
	}

	public void reIndex() {
		if (LuceneUtil.INDEX_READ_ONLY) {
			return;
		}

		if (_log.isInfoEnabled()) {
			_log.info("Reindexing Lucene started");
		}

		if (ServerDetector.isOrion()) {

			// Wait 10 seconds because Orion 2.0.7 initiates LuceneServlet
			// before it initiates MainServlet.

			try {
				Thread.sleep(Time.SECOND * 10);
			}
			catch (InterruptedException ie) {
			}
		}

		StopWatch stopWatch1 = null;

		if (_log.isInfoEnabled()) {
			stopWatch1 = new StopWatch();

			stopWatch1.start();
		}

		LuceneUtil.delete(_companyId);

		try {
			IndexWriter writer = LuceneUtil.getWriter(_companyId, true);

			LuceneUtil.write(writer);
		}
		catch (IOException ioe) {
			_log.error(ioe.getMessage(), ioe);
		}

		String[] indexIds = new String[] {String.valueOf(_companyId)};

		try {
			List portlets = PortletLocalServiceUtil.getPortlets(_companyId);

			Collections.sort(portlets, new PortletLuceneComparator());

			Iterator itr = portlets.iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				String className = portlet.getIndexerClass();

				if (portlet.isActive() && className != null) {
					StopWatch stopWatch2 = null;

					if (_log.isInfoEnabled()) {
						stopWatch2 = new StopWatch();

						stopWatch2.start();
					}

					if (_log.isInfoEnabled()) {
						_log.info("Reindexing with " + className + " started");
					}

					Indexer indexer = (Indexer)InstancePool.get(className);

					indexer.reIndex(indexIds);

					if (_log.isInfoEnabled()) {
						_log.info(
							"Reindexing with " + className + " completed in " +
								(stopWatch2.getTime() / Time.SECOND) +
									" seconds");
					}
				}
			}

			if (_log.isInfoEnabled()) {
				_log.info(
					"Reindexing Lucene completed in " +
						(stopWatch1.getTime() / Time.SECOND) + " seconds");
			}
		}
		catch (Exception e) {
			_log.error("Error encountered while reindexing", e);

			if (_log.isInfoEnabled()) {
				_log.info("Reindexing Lucene failed");
			}
		}

		_finished = true;
	}

	private static Log _log = LogFactory.getLog(LuceneIndexer.class);

	private long _companyId;
	private boolean _finished;

}