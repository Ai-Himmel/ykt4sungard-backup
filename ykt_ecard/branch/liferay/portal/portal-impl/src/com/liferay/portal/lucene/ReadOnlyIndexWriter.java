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

import java.io.IOException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;
import org.apache.lucene.store.Directory;

/**
 * <a href="ReadOnlyIndexWriter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 */
public class ReadOnlyIndexWriter extends IndexWriter {

	public ReadOnlyIndexWriter(
			Directory luceneDir, Analyzer analyzer, boolean create)
		throws IOException {

		super(luceneDir, analyzer, create);
	}

	public void addDocument(Document document)
		throws CorruptIndexException, IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Ignoring invocation to addDocument");
		}
	}

	public void addDocument(Document document, Analyzer analyzer)
		throws CorruptIndexException, IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Ignoring invocation to addDocument");
		}
	}

	public synchronized void addIndexes(Directory[] directories)
		throws CorruptIndexException, IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Ignoring invocation to addIndexes");
		}
	}

	public synchronized void addIndexes(IndexReader[] indexReaders)
		throws CorruptIndexException, IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Ignoring invocation to addIndexes");
		}
	}

	public synchronized void addIndexesNoOptimize(Directory[] directories)
		throws CorruptIndexException, IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Ignoring invocation to addIndexesNoOptimize");
		}
	}

	public synchronized void deleteDocuments(Term term)
		throws CorruptIndexException, IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Ignoring invocation to deleteDocuments");
		}
	}

	public synchronized void deleteDocuments(Term[] terms)
		throws CorruptIndexException, IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Ignoring invocation to deleteDocuments");
		}
	}

	public void updateDocument(Term term, Document document)
		throws CorruptIndexException, IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Ignoring invocation to updateDocument");
		}
	}

	public void updateDocument(Term term, Document document, Analyzer analyzer)
		throws CorruptIndexException, IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Ignoring invocation to updateDocument");
		}
	}

	public synchronized void optimize()
		throws CorruptIndexException, IOException {

		if (_log.isDebugEnabled()) {
			_log.debug("Ignoring invocation to optimize");
		}
	}

	private static Log _log = LogFactory.getLog(ReadOnlyIndexWriter.class);

}