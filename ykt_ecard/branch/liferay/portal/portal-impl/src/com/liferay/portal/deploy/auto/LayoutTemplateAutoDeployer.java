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

package com.liferay.portal.deploy.auto;

import com.liferay.portal.deploy.DeployUtil;
import com.liferay.portal.kernel.deploy.auto.AutoDeployException;
import com.liferay.portal.kernel.util.ServerDetector;
import com.liferay.portal.tools.LayoutTemplateDeployer;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="LayoutTemplateAutoDeployer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ivica Cardic
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutTemplateAutoDeployer
	extends LayoutTemplateDeployer implements AutoDeployer {

	public LayoutTemplateAutoDeployer() {
		try {
			baseDir = PrefsPropsUtil.getString(
				PropsUtil.AUTO_DEPLOY_DEPLOY_DIR,
				PropsValues.AUTO_DEPLOY_DEPLOY_DIR);
			destDir = DeployUtil.getAutoDeployDestDir();
			appServerType = ServerDetector.getServerId();
			jbossPrefix = PrefsPropsUtil.getString(
				PropsUtil.AUTO_DEPLOY_JBOSS_PREFIX,
				PropsValues.AUTO_DEPLOY_JBOSS_PREFIX);
			unpackWar = PrefsPropsUtil.getBoolean(
				PropsUtil.AUTO_DEPLOY_UNPACK_WAR,
				PropsValues.AUTO_DEPLOY_UNPACK_WAR);

			List jars = new ArrayList();

			this.jars = jars;

			checkArguments();
		}
		catch (Exception e) {
			_log.error(e);
		}
	}

	public void autoDeploy(String file) throws AutoDeployException {
		List wars = new ArrayList();

		wars.add(file);

		this.wars = wars;

		try {
			deploy();
		}
		catch (Exception e) {
			throw new AutoDeployException(e);
		}
	}

	private static Log _log =
		LogFactory.getLog(LayoutTemplateAutoDeployer.class);

}