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

import com.liferay.portal.kernel.util.Validator;

import java.io.File;

import java.util.Iterator;
import java.util.Map;

import org.apache.tools.ant.taskdefs.Copy;
import org.apache.tools.ant.types.FileSet;
import org.apache.tools.ant.types.FilterSet;

/**
 * <a href="CopyTask.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CopyTask {

	public static void copyDirectory(String source, String destination) {
		copyDirectory(source, destination, null, null);
	}

	public static void copyDirectory(
		String source, String destination, String includes, String excludes) {

		copyDirectory(
			new File(source), new File(destination), includes, excludes);
	}

	public static void copyDirectory(File source, File destination) {
		copyDirectory(source, destination, null, null);
	}

	public static void copyDirectory(
		File source, File destination, String includes, String excludes) {

		copyDirectory(source, destination, includes, excludes, false, true);
	}

	public static void copyDirectory(
		File source, File destination, String includes, String excludes,
		boolean overwrite, boolean preserveLastModified) {

		Copy copy = new Copy();

		FileSet fileSet = new FileSet();

		fileSet.setDir(source);

		if (Validator.isNotNull(includes)) {
			fileSet.setIncludes(includes);
		}

		if (Validator.isNotNull(excludes)) {
			fileSet.setExcludes(excludes);
		}

		copy.setProject(AntUtil.getProject());
		copy.addFileset(fileSet);
		copy.setTodir(destination);
		copy.setOverwrite(overwrite);
		copy.setPreserveLastModified(preserveLastModified);

		copy.execute();
	}

	public static void copyFile(
		File sourceFile, File destinationDir, boolean overwrite,
		boolean preserveLastModified) {

		copyFile(
			sourceFile, destinationDir, null, overwrite, preserveLastModified);
	}

	public static void copyFile(
		File sourceFile, File destinationDir, Map filterMap,
		boolean overwrite, boolean preserveLastModified) {

		Copy copy = new Copy();

		FileSet fileSet = new FileSet();

		fileSet.setFile(sourceFile);

		copy.setProject(AntUtil.getProject());
		copy.setFiltering(true);
		copy.addFileset(fileSet);
		copy.setTodir(destinationDir);
		copy.setOverwrite(overwrite);
		copy.setPreserveLastModified(preserveLastModified);

		if (filterMap != null) {
			FilterSet filterSet = copy.createFilterSet();

			Iterator itr = filterMap.keySet().iterator();

			while (itr.hasNext()) {
				String token = (String)itr.next();

				String replacement = (String)filterMap.get(token);

				filterSet.addFilter(token, replacement);
			}
		}

		copy.execute();
	}

}