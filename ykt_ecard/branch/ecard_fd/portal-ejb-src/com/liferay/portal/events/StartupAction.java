/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.events;

import com.liferay.lock.service.spring.LockServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.spring.ImageLocalServiceUtil;
import com.liferay.portal.service.spring.ReleaseLocalServiceUtil;
import com.liferay.portal.struts.ActionException;
import com.liferay.portal.struts.SimpleAction;
import com.liferay.portal.upgrade.UpgradeProcess;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.ReleaseInfo;
import com.liferay.util.SimpleCachePool;

import java.util.Date;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="StartupAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.20 $
 *
 */
public class StartupAction extends SimpleAction {

	public void run(String[] ids) throws ActionException {

		try {

			// Print release information

			System.out.println("Starting " + ReleaseInfo.getReleaseInfo());

			// Keep track of uptime

			SimpleCachePool.put(
				StartupAction.class.getName() + ".uptime", new Date());

			// Clear locks

			try {
				LockServiceUtil.clear();
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			// Add shutdown hook

			Runtime.getRuntime().addShutdownHook(
				new Thread(new ShutdownHook()));

			// Upgrade

			int buildNumber =
				ReleaseLocalServiceUtil.getRelease().getBuildNumber();

			String[] upgradeProcesses =
				PropsUtil.getArray(PropsUtil.UPGRADE_PROCESSES);

			for (int i = 0; i < upgradeProcesses.length; i++) {
				_log.debug("Attempt to upgrade with " + upgradeProcesses[i]);

				UpgradeProcess upgradeProcess =
					(UpgradeProcess)Class.forName(
						upgradeProcesses[i]).newInstance();

				upgradeProcess.upgrade(buildNumber);
			}

			ReleaseLocalServiceUtil.updateRelease();

			// Delete temporary images

			_deleteTempImages();
		}
		catch (Exception e) {
			throw new ActionException(e);
		}
	}

	private void _deleteTempImages() throws PortalException, SystemException {

		// Journal

		ImageLocalServiceUtil.deleteByImageId("%.journal.article.PREVIEW_%");
	}

	private static final Log _log = LogFactory.getLog(StartupAction.class);

}