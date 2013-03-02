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

package com.liferay.portlet.documentlibrary.model.impl;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.NullSafeProperties;
import com.liferay.portal.kernel.util.PropertiesUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.model.DLFolder;
import com.liferay.portlet.documentlibrary.service.DLFolderLocalServiceUtil;
import com.liferay.util.FileUtil;

import java.io.IOException;

import java.util.Iterator;
import java.util.Map;
import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="DLFileEntryImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class DLFileEntryImpl
	extends DLFileEntryModelImpl implements DLFileEntry {

	public static final double DEFAULT_VERSION = 1.0;

	public static final int DEFAULT_READ_COUNT = 0;

	public static String stripExtension(String name, String title) {
		String extension = FileUtil.getExtension(name);

		if (extension == null) {
			return title;
		}

		int pos = title.toLowerCase().lastIndexOf(
			StringPool.PERIOD + extension);

		if (pos > 0) {
			title = title.substring(0, pos);
		}

		return title;
	}

	public DLFileEntryImpl() {
	}

	public String getUserUuid() throws SystemException {
		return PortalUtil.getUserValue(getUserId(), "uuid", _userUuid);
	}

	public void setUserUuid(String userUuid) {
		_userUuid = userUuid;
	}

	public DLFolder getFolder() {
		DLFolder folder = null;

		try {
			folder = DLFolderLocalServiceUtil.getFolder(getFolderId());
		}
		catch (Exception e) {
			folder = new DLFolderImpl();

			_log.error(e);
		}

		return folder;
	}

	public String getTitleWithExtension() {
		StringMaker sm = new StringMaker();

		sm.append(getTitle());
		sm.append(StringPool.PERIOD);
		sm.append(FileUtil.getExtension(getName()));

		return sm.toString();
	}

	public String getExtraSettings() {
		if (_extraSettingsProperties == null) {
			return super.getExtraSettings();
		}
		else {
			return PropertiesUtil.toString(_extraSettingsProperties);
		}
	}

	public void setExtraSettings(String extraSettings) {
		_extraSettingsProperties = null;

		super.setExtraSettings(extraSettings);
	}

	public Properties getExtraSettingsProperties() {
		if (_extraSettingsProperties == null) {
			_extraSettingsProperties = new NullSafeProperties();

			try {
				PropertiesUtil.load(
					_extraSettingsProperties, super.getExtraSettings());
			}
			catch (IOException ioe) {
				_log.error(ioe);
			}
		}

		return _extraSettingsProperties;
	}

	public void setExtraSettingsProperties(Properties extraSettingsProperties) {
		_extraSettingsProperties = extraSettingsProperties;

		super.setExtraSettings(
			PropertiesUtil.toString(_extraSettingsProperties));
	}

	public String getLuceneProperties() {
		StringMaker sm = new StringMaker();

		sm.append(getTitle());
		sm.append(StringPool.SPACE);
		sm.append(getDescription());
		sm.append(StringPool.SPACE);

		Properties extraSettingsProps = getExtraSettingsProperties();

		Iterator itr = (Iterator)extraSettingsProps.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String value = GetterUtil.getString((String)entry.getValue());

			sm.append(value);
		}

		return sm.toString();
	}

	private static Log _log = LogFactory.getLog(DLFileEntryImpl.class);

	private Properties _extraSettingsProperties = null;
	private String _userUuid;

}