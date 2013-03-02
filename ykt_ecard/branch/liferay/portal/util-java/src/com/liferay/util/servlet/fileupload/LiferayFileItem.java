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

package com.liferay.util.servlet.fileupload;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.util.FileUtil;
import com.liferay.util.SystemProperties;

import java.io.File;

import org.apache.commons.fileupload.disk.DiskFileItem;

/**
 * <a href="LiferayFileItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Zongliang Li
 * @author Harry Mark
 *
 */
public class LiferayFileItem extends DiskFileItem {

	public static final int THRESHOLD_SIZE = GetterUtil.getInteger(
		SystemProperties.get(
			LiferayFileItem.class.getName() + ".threshold.size"));

	public LiferayFileItem(String fieldName, String contentType,
						   boolean isFormField, String fileName,
						   int sizeThreshold, File repository) {

		super(fieldName, contentType, isFormField, fileName, sizeThreshold,
			  repository);

		_fileName = fileName;
		_repository = repository;
	}

	public String getFileName() {
		if (_fileName == null) {
			return null;
		}

		int pos = _fileName.lastIndexOf("/");

		if (pos == -1) {
			pos = _fileName.lastIndexOf("\\");
		}

		if (pos == -1) {
			return _fileName;
		}
		else {
			return _fileName.substring(pos + 1, _fileName.length());
		}
	}

	public String getFullFileName() {
		return _fileName;
	}

	public String getFileNameExtension() {
		return FileUtil.getExtension(_fileName);
	}

	public String getString() {

		// Prevent serialization of uploaded content

		if (getSize() > THRESHOLD_SIZE) {
			return StringPool.BLANK;
		}

		if (_encodedString == null) {
			return super.getString();
		}
		else {
			return _encodedString;
		}
	}

	public void setString(String encode) {
		try {
			_encodedString = getString(encode);
		}
		catch (Exception e) {
		}
	}

	protected File getTempFile() {
		String tempFileName = "upload_" + _getUniqueId();

		String extension = getFileNameExtension();

		if (extension != null) {
			tempFileName += "." + extension;
		}

		File tempFile = new File(_repository, tempFileName);

		tempFile.deleteOnExit();

		return tempFile;
	}

	private static String _getUniqueId() {
		int current;

		synchronized (LiferayFileItem.class) {
			current = _counter++;
		}

		String id = Integer.toString(current);

		if (current < 100000000) {
			id = ("00000000" + id).substring(id.length());
		}

		return id;
	}

	private static int _counter = 0;

	private String _fileName;
	private File _repository;
	private String _encodedString;

}