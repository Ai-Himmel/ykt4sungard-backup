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

package com.liferay.portal.tools;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.util.FileUtil;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="JSPCompiler.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Henrik Bentel
 *
 */
public class JSPCompiler {

	public static void main(String[] args) throws Exception {
		if (args.length == 4) {
			new JSPCompiler(args[0], args[1], args[2], args[3], false);
		}
		else if (args.length == 5) {
			new JSPCompiler(
				args[0], args[1], args[2], args[3],
				GetterUtil.getBoolean(args[4]));
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	public JSPCompiler(
			String appServerType, String compiler, String classPath,
			String directory, boolean checkTimeStamp)
		throws Exception {

		_compiler = compiler;

		if (!_compiler.equals("jikes")) {
			_compiler = "javac";
		}

		_classPath = StringUtil.replace(
			classPath, ";", System.getProperty("path.separator"));
		_directory = directory;
		_checkTimeStamp = checkTimeStamp;

		_compile(new File(directory));
	}

	private void _compile(File directory) throws Exception {
		if (directory.exists() && directory.isDirectory()) {
			List fileList = new ArrayList();

			File[] fileArray = FileUtil.sortFiles(directory.listFiles());

			for (int i = 0; i < fileArray.length; i++) {
				File file = fileArray[i];

				if (file.isDirectory()) {
					_compile(fileArray[i]);
				}
				else if (file.getName().endsWith(".java")) {
					fileList.add(file);
				}
			}

			_compile(directory.getPath(), fileList);
		}
	}

	private void _compile(String sourcePath, List files) throws Exception {
		if (files.size() == 0) {
			return;
		}

		System.out.println(sourcePath);

		for (int i = 0; i < files.size(); i++) {
			File file = (File)files.get(i);

			String classDestination = _directory;

			String cmd =
				_compiler + " -classpath " + _classPath +
				" -d " + classDestination + " " +
				file.toString();

			File classFile = new File(
				sourcePath + File.separator +
				StringUtil.replace(file.getName(), ".java", ".class"));

			if (!classFile.exists() ||
				(_checkTimeStamp &&
				 (file.lastModified() > classFile.lastModified()))) {

				Runtime rt = Runtime.getRuntime();

				Process p = rt.exec(cmd);

				BufferedReader br = new BufferedReader(
					new InputStreamReader(p.getErrorStream()));

				StringMaker sm = new StringMaker();
				String line = null;

				while ((line = br.readLine()) != null) {
					sm.append(line).append("\n");
				}

				br.close();

				p.waitFor();
				p.destroy();

				if (!classFile.exists()) {
					throw new Exception(sm.toString());
				}
			}
		}
	}

	private String _compiler;
	private String _classPath;
	private String _directory;
	private boolean _checkTimeStamp;

}