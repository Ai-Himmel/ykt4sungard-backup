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
import com.liferay.portal.kernel.deploy.auto.AutoDeployListener;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.util.FileUtil;

import java.io.File;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.Element;

/**
 * <a href="BaseExplodedTomcatListener.java.html"><b><i>View Source</i></b></a>
 *
 * @author Olaf Fricke
 * @author Brian Wing Shun Chan
 *
 */
public abstract class BaseExplodedTomcatListener implements AutoDeployListener {

	public void copyContextFile(File file) throws AutoDeployException {
		try {
			String tomcatConfDir = PrefsPropsUtil.getString(
				PropsUtil.AUTO_DEPLOY_TOMCAT_CONF_DIR,
				PropsValues.AUTO_DEPLOY_TOMCAT_CONF_DIR);

			if (_log.isInfoEnabled()) {
				_log.info(
					"Copying file " + file.getPath() + " to " + tomcatConfDir);
			}

			FileUtil.copyFile(
				file, new File(tomcatConfDir + "/" + file.getName()));
		}
		catch (Exception e) {
			throw new AutoDeployException(e.getMessage());
		}
	}

	public File getDocBaseDir(File file, String checkXmlFile)
		throws AutoDeployException {

		if (!isMatchingFileExtension(file)) {
			return null;
		}

		String docBase = null;

		try {
			String content = FileUtil.read(file);

			Document doc = PortalUtil.readDocumentFromXML(content);

			Element root = doc.getRootElement();

			docBase = root.attributeValue("docBase");
		}
		catch (Exception e) {
			throw new AutoDeployException(e);
		}

		if (Validator.isNull(docBase)) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					file.getPath() + " does not have a docBase defined");
			}

			return null;
		}

		File docBaseDir = new File(docBase);

		if (!docBaseDir.exists()) {
			if (_log.isDebugEnabled()) {
				_log.debug(docBase + " does not exist");
			}

			return null;
		}

		if (!docBaseDir.isDirectory()) {
			if (_log.isDebugEnabled()) {
				_log.debug(docBase + " is not a directory");
			}

			return null;
		}

		if (!FileUtil.exists(docBase + "/" + checkXmlFile)) {
			if (_log.isDebugEnabled()) {
				_log.debug(docBase + " does not have " + checkXmlFile);
			}

			return null;
		}

		return docBaseDir;
	}

	public boolean isMatchingFileExtension(File file) {
		if (file.getName().endsWith(".xml")) {
			if (_log.isDebugEnabled()) {
				_log.debug(file.getPath() + " has a matching extension");
			}

			return true;
		}
		else {
			if (_log.isDebugEnabled()) {
				_log.debug(
					file.getPath() + " does not have a matching extension");
			}

			return false;
		}
	}

	private static Log _log =
		LogFactory.getLog(BaseExplodedTomcatListener.class);

}