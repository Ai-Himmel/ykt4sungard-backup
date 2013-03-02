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

package com.liferay.portal.webdav;

import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.HttpUtil;

import java.io.InputStream;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import java.util.Date;
import java.util.Locale;

/**
 * <a href="BaseResourceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class BaseResourceImpl implements Resource {

	public BaseResourceImpl(
		String parentPath, long name, long displayName) {

		this(parentPath, String.valueOf(name), String.valueOf(displayName));
	}

	public BaseResourceImpl(
		String parentPath, long name, String displayName) {

		this(parentPath, String.valueOf(name), displayName);
	}

	public BaseResourceImpl(
		String parentPath, String name, String displayName) {

		this(parentPath, name, displayName, null, null);
	}

	public BaseResourceImpl(
		String parentPath, String name, String displayName, Date createDate,
		Date modifiedDate) {

		this(parentPath, name, displayName, createDate, modifiedDate, 0);
	}

	public BaseResourceImpl(
		String parentPath, String name, String displayName, Date createDate,
		Date modifiedDate, int size) {

		_href = parentPath;

		if (Validator.isNotNull(name)) {
			name = HttpUtil.encodeURL(name);
			name = StringUtil.replace(name, StringPool.PLUS, "%20");

			_href += StringPool.SLASH + name;
		}

		_displayName = displayName;

		if (createDate == null) {
			_createDate = new Date();
		}
		else {
			_createDate = createDate;
		}

		if (modifiedDate == null) {
			_modifiedDate = new Date();
		}
		else {
			_modifiedDate = _createDate;
		}

		_size = size;
	}

 	public String getHREF() {
		return _href;
	}

	public String getDisplayName() {
		return _displayName;
	}

	public boolean isCollection() {
		return true;
	}

 	public String getCreateDate() {
		return _createDateFormatter.format(_createDate);
	}

 	public String getModifiedDate() {
		return _modifiedDateFormatter.format(_modifiedDate);
	}

	public int getSize() {
		return _size;
	}

	public Object getModel() {
		return _model;
	}

	public void setModel(Object model) {
		_model = model;
	}

 	public String getClassName() {
 		return _className;
 	}

 	public void setClassName(String className) {
 		_className = className;
 	}

 	public long getPrimaryKey() {
 		return _primaryKey;
 	}

 	public void setPrimaryKey(long primaryKey) {
 		_primaryKey = primaryKey;
 	}

	public String getContentType() {
		return ContentTypes.HTTPD_UNIX_DIRECTORY;
	}

	public InputStream getContentAsStream() throws WebDAVException {
		return null;
	}

	private static DateFormat _createDateFormatter =
		new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss'Z'", Locale.US);

	private static DateFormat _modifiedDateFormatter =
		new SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss zzz", Locale.US);

	private String _href;
	private String _displayName;
	private Date _createDate;
	private Date _modifiedDate;
	private int _size;
	private Object _model;
	private String _className;
	private long _primaryKey = -1;

}