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

import com.liferay.portal.kernel.deploy.auto.AutoDeployException;
import com.liferay.portal.kernel.deploy.auto.AutoDeployListener;

import java.io.File;
import java.io.IOException;

import java.util.zip.ZipFile;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="BaseAutoDeployListener.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ivica Cardic
 * @author Brian Wing Shun Chan
 *
 */
public abstract class BaseAutoDeployListener implements AutoDeployListener {

	public boolean isMatchingFile(File file, String checkXmlFile)
		throws AutoDeployException {

		if (!isMatchingFileExtension(file)) {
			return false;
		}

		ZipFile zipFile = null;

		try {
			zipFile = new ZipFile(file);

			if (zipFile.getEntry(checkXmlFile) == null) {
				if (_log.isDebugEnabled()) {
					_log.debug(
						file.getPath() + " does not have " + checkXmlFile);
				}

				return false;
			}
			else {
				return true;
			}
		}
		catch (IOException ioe) {
			throw new AutoDeployException(ioe);
		}
		finally {
			if (zipFile != null) {
				try {
					zipFile.close();
				}
				catch (IOException ioe) {
				}
			}
		}
	}

	public boolean isMatchingFileExtension(File file) {
		String fileName = file.getName().toLowerCase();

		if (fileName.endsWith(".war") || fileName.endsWith(".zip")) {
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

	public boolean isThemePlugin(File file) throws AutoDeployException {
		if (isMatchingFile(file, "WEB-INF/liferay-look-and-feel.xml")) {
			return true;
		}

		if ((isMatchingFile(
				file, "WEB-INF/liferay-plugin-package.properties")) &&
			(file.getName().indexOf("-theme") != -1)) {

			return true;
		}

		return false;
	}

	private static Log _log = LogFactory.getLog(BaseAutoDeployListener.class);

}