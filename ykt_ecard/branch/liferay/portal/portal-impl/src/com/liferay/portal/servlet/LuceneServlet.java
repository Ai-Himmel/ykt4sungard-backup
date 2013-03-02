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

package com.liferay.portal.servlet;

import com.liferay.portal.job.JobScheduler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ObjectValuePair;
import com.liferay.portal.kernel.util.ServerDetector;
import com.liferay.portal.lucene.CleanUpJob;
import com.liferay.portal.lucene.LuceneIndexer;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.quartz.SchedulerException;

/**
 * <a href="LuceneServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class LuceneServlet extends HttpServlet {

	public void init(ServletConfig config) throws ServletException {
		super.init(config);

		long[] companyIds = PortalInstances.getCompanyIds();

		for (int i = 0; i < companyIds.length; i++) {
			long companyId = companyIds[i];

			if (GetterUtil.getBoolean(
					PropsUtil.get(PropsUtil.INDEX_ON_STARTUP))) {

				if (_log.isInfoEnabled()) {
					_log.info("Indexing Lucene on startup");
				}

				LuceneIndexer indexer = new LuceneIndexer(companyId);
				Thread indexerThread = null;

				if (GetterUtil.getBoolean(
						PropsUtil.get(PropsUtil.INDEX_WITH_THREAD)) ||
					ServerDetector.isOrion()) {

					indexerThread = new Thread(
						indexer, THREAD_NAME + "." + companyId);

					indexerThread.setPriority(THREAD_PRIORITY);

					indexerThread.start();
				}
				else {
					indexer.reIndex();
				}

				_indexers.add(new ObjectValuePair(indexer, indexerThread));
			}
			else {
				LuceneUtil.checkLuceneDir(companyId);
			}

			if (PropsValues.LUCENE_STORE_JDBC_AUTO_CLEAN_UP) {
				try {
					JobScheduler.schedule(new CleanUpJob());
				}
				catch (SchedulerException se) {
					_log.error(se);
				}
			}
		}
	}

	public void destroy() {

		// Wait for indexer to be gracefully interrupted

		for (int i = 0; i < _indexers.size(); i++) {
			ObjectValuePair ovp = (ObjectValuePair)_indexers.get(i);

			LuceneIndexer indexer = (LuceneIndexer)ovp.getKey();
			Thread indexerThread = (Thread)ovp.getValue();

			if ((indexer != null) && (!indexer.isFinished()) &&
				(indexerThread != null)) {

				if (_log.isWarnEnabled()) {
					_log.warn("Waiting for Lucene indexer to shutdown");
				}

				indexer.halt();

				try {
					indexerThread.join(THREAD_TIMEOUT);
				}
				catch (InterruptedException e) {
					_log.error("Lucene indexer shutdown interrupted", e);
				}
			}
		}

		// Parent

		super.destroy();
	}

	private static final String THREAD_NAME = LuceneIndexer.class.getName();

	private static final int THREAD_PRIORITY = Thread.MIN_PRIORITY;

	private static final int THREAD_TIMEOUT = 60000;

	private static Log _log = LogFactory.getLog(LuceneServlet.class);

	private List _indexers = new ArrayList();

}