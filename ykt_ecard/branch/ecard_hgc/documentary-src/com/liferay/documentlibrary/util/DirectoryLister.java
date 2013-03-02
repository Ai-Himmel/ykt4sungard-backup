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

package com.liferay.documentlibrary.util;

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.FileUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.lang.FastStringBuffer;

import java.io.File;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * <a href="DirectoryLister.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.10 $
 *
 */
public class DirectoryLister {

	public DirectoryView getDirectoryView(String rootDir) {
		_rootDir = rootDir;
		_nodeId = 1;

		_fileList = new ArrayList();
		_fileList.add("1|0|0||Root|0");

		File rootFile = new File(_rootDir);

		if (!rootFile.exists()) {
			rootFile.mkdirs();
		}

		_fileExtensions = CollectionFactory.getHashMap();

		int fileExtensionPos = 12;

		String[] fileExtensions =
			PropsUtil.getArray(PropsUtil.DL_FILE_EXTENSIONS);

		for (int i = 0; i < fileExtensions.length; i++) {

			// Only process non wildcard extensions

			if (!StringPool.STAR.equals(fileExtensions[i])) {

				// Strip starting period

				String extension = fileExtensions[i];
				extension = extension.substring(1, extension.length());

				_fileExtensions.put(
					extension, Integer.toString(fileExtensionPos++));
			}
		}

		_createFileList(_rootDir, 1);

		return new DirectoryView(_fileList);
	}

	private void _createFileList(String directory, int parentId) {
		File file = new File(directory);

		File[] files = FileUtil.sortFiles(file.listFiles());

		for (int i = 0; i < files.length; i++) {
			String fullName = files[i].toString().toLowerCase();
			fullName = StringUtil.replace(fullName, "\\", "/");
			fullName = fullName.substring(_rootDir.length(), fullName.length());

			FastStringBuffer sb = new FastStringBuffer();

			sb.append(++_nodeId).append("|");
			sb.append(parentId).append("|");

			if ((i + 1) == files.length) {
				sb.append("1");
			}
			else {
				sb.append("0");
			}

			sb.append("|");

			String path = files[i].getParent();
			path = path.substring(_rootDir.length(), path.length());
			path = StringUtil.replace(path, "\\", "/");

			sb.append(path).append("|");

			sb.append(files[i].getName()).append("|");

			if (files[i].isDirectory()) {
				sb.append("9");

				_fileList.add(sb.toString());

				_createFileList(files[i].toString(), _nodeId);
			}
			else {
				String extension = StringPool.BLANK;

				int pos = files[i].getName().lastIndexOf(".");
				if (pos != -1) {
					extension = files[i].getName().substring(
						pos + 1, files[i].getName().length()).toLowerCase();
				}

				String extensionPos = (String)_fileExtensions.get(extension);

				if (extensionPos != null) {
					sb.append(extensionPos);
				}
				else {
					sb.append("11");
				}

				_fileList.add(sb.toString());
			}
		}
	}

	private String _rootDir;
	private int _nodeId;
	private List _fileList;
	private Map _fileExtensions;

}