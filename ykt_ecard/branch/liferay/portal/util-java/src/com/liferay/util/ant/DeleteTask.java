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

package com.liferay.util.ant;

import java.io.File;

import org.apache.tools.ant.taskdefs.Delete;
import org.apache.tools.ant.types.FileSet;

/**
 * <a href="DeleteTask.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DeleteTask {

	public static void deleteDirectory(String dir) {
		deleteDirectory(new File(dir));
	}

	public static void deleteDirectory(File dir) {
		Delete delete = new Delete();

		delete.setProject(AntUtil.getProject());
		delete.setDir(dir);
		delete.setFailOnError(false);

		delete.execute();
	}

	public static void deleteFile(String file) {
		deleteFile(new File(file));
	}

	public static void deleteFile(File file) {
		Delete delete = new Delete();

		delete.setProject(AntUtil.getProject());
		delete.setFile(file);
		delete.setFailOnError(false);

		delete.execute();
	}

	public static void deleteFiles(
		String dir, String includes, String excludes) {

		deleteFiles(new File(dir), includes, excludes);
	}

	public static void deleteFiles(File dir, String includes, String excludes) {
		Delete delete = new Delete();

		delete.setProject(AntUtil.getProject());
		delete.setFailOnError(false);

		FileSet fileSet = new FileSet();

		fileSet.setDir(dir);
		fileSet.setIncludes(includes);
		fileSet.setExcludes(excludes);

		delete.addFileset(fileSet);

		delete.execute();
	}

}