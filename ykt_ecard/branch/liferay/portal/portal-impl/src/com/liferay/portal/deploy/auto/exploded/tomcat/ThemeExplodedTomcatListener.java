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

package com.liferay.portal.deploy.auto.exploded.tomcat;

import com.liferay.portal.kernel.deploy.auto.AutoDeployException;

import java.io.File;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ThemeExplodedTomcatListener.java.html"><b><i>View Source</i></b></a>
 *
 * @author Olaf Fricke
 * @author Brian Wing Shun Chan
 *
 */
public class ThemeExplodedTomcatListener extends BaseExplodedTomcatListener {

	public ThemeExplodedTomcatListener() {
		_deployer = new ThemeExplodedTomcatDeployer();
	}

	public void deploy(File file) throws AutoDeployException {
		if (_log.isDebugEnabled()) {
			_log.debug("Invoking deploy for " + file.getPath());
		}

		File docBaseDir = getDocBaseDir(
			file, "WEB-INF/liferay-look-and-feel.xml");

		if (docBaseDir == null) {
			return;
		}

		if (_log.isInfoEnabled()) {
			_log.info("Modifying themes for " + file.getPath());
		}

		_deployer.explodedTomcatDeploy(file, docBaseDir, null);

		if (_log.isInfoEnabled()) {
			_log.info(
				"Themes for " + file.getPath() + " modified successfully");
		}

		copyContextFile(file);
	}

	private static Log _log =
		LogFactory.getLog(ThemeExplodedTomcatListener.class);

	private ExplodedTomcatDeployer _deployer;

}