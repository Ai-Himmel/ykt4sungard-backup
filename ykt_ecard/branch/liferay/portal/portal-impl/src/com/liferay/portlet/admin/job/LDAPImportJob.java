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

package com.liferay.portlet.admin.job;

import com.liferay.portal.job.IntervalJob;
import com.liferay.portal.security.ldap.PortalLDAPUtil;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.Time;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * <a href="LDAPImportJob.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class LDAPImportJob implements IntervalJob {

	public LDAPImportJob() {
		try {
			long rawInterval = PrefsPropsUtil.getLong(
				PropsUtil.LDAP_IMPORT_INTERVAL);

			if (_log.isDebugEnabled()) {
				_log.debug("Interval " + rawInterval + " minutes");
			}

			_interval =  rawInterval * Time.MINUTE;
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public long getInterval() {
		return _interval;
	}

	public void execute(JobExecutionContext context)
		throws JobExecutionException {

		try {
			PortalLDAPUtil.importFromLDAP();
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	private static Log _log = LogFactory.getLog(LDAPImportJob.class);

	private long _interval;

}