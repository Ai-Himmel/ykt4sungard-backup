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

package com.liferay.portal.theme;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.service.impl.ThemeLocalUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.util.CollectionFactory;
import com.liferay.util.FileUtil;

import java.io.File;

import java.util.Map;

import javax.servlet.ServletContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.Element;

/**
 * <a href="ThemeLoader.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ThemeLoader {

	public String getServletContextName() {
		return _servletContextName;
	}

	public String getThemesPath() {
		return _themesPath;
	}

	public File getFileStorage() {
		return _fileStorage;
	}

	public synchronized void loadThemes() {
		if (_log.isInfoEnabled()) {
			_log.info("Loading themes in " + _fileStorage);
		}

		File[] files = _fileStorage.listFiles();

		if (files == null) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"There are no directories to process for  " + _fileStorage);
			}

			return;
		}

		for (int i = 0; i < files.length; i++) {
			if (_log.isDebugEnabled()) {
				_log.debug("Process directory " + files[i]);
			}

			File liferayLookAndFeelXML = new File(
				files[i] + "/liferay-look-and-feel.xml");

			if (liferayLookAndFeelXML.exists()) {
				String lastModifiedKey = liferayLookAndFeelXML.toString();

				Long prevLastModified =
					(Long)_lastModifiedMap.get(lastModifiedKey);

				long lastModified = liferayLookAndFeelXML.lastModified();

				if ((prevLastModified == null) ||
					(prevLastModified.longValue() < lastModified)) {

					registerTheme(liferayLookAndFeelXML);

					_lastModifiedMap.put(
						lastModifiedKey, new Long(lastModified));
				}
				else {
					if (_log.isDebugEnabled()) {
						_log.debug(
							"Do not refresh " + liferayLookAndFeelXML +
								" because it is has not been modified");
					}
				}
			}
			else {
				if (_log.isWarnEnabled()) {
					_log.warn(liferayLookAndFeelXML + " does not exist");
				}
			}
		}
	}

	protected ThemeLoader(
		String servletContextName, ServletContext ctx, String[] xmls) {

		_servletContextName = servletContextName;
		_ctx = ctx;

		try {
			Document doc = PortalUtil.readDocumentFromXML(xmls[0], true);

			Element root = doc.getRootElement();

			_themesPath = GetterUtil.getString(
				root.elementText("themes-path"), "/themes");

			String fileStorageValue = PropsValues.THEME_LOADER_STORAGE_PATH;

			fileStorageValue = GetterUtil.getString(
				root.elementText("file-storage"), fileStorageValue);

			if (Validator.isNotNull(fileStorageValue)) {
				_fileStorage = new File(fileStorageValue);
				_loadFromServletContext = false;
			}
			else {
				_fileStorage = new File(ctx.getRealPath(_themesPath));
				_loadFromServletContext = true;
			}

			if (!_fileStorage.exists()) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"File storage " + _fileStorage + " does not exist");
				}

				if (!_fileStorage.mkdirs()) {
					_log.error(
						"Unable to create theme loader file storage at " +
							_fileStorage);
				}
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		loadThemes();
	}

	protected void destroy() {
	}

	protected void registerTheme(File liferayLookAndFeelXML) {
		if (_log.isDebugEnabled()) {
			_log.debug("Registering " + liferayLookAndFeelXML);
		}

		try {
			String content = FileUtil.read(liferayLookAndFeelXML);

			ThemeLocalUtil.init(
				_servletContextName, _ctx, _themesPath, _loadFromServletContext,
				new String[] {content}, null);
		}
		catch (Exception e) {
			_log.error(
				"Error registering theme " + liferayLookAndFeelXML.toString(),
				e);
		}
	}

	private static Log _log = LogFactory.getLog(ThemeLoader.class);

	private String _servletContextName;
	private ServletContext _ctx;
	private String _themesPath;
	private File _fileStorage;
	private boolean _loadFromServletContext = true;
	private Map _lastModifiedMap = CollectionFactory.getHashMap();

}