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

import org.apache.tools.ant.taskdefs.Manifest;
import org.apache.tools.ant.taskdefs.ManifestException;

/**
 * <a href="ManifestTask.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ManifestTask {

	public static void manifest(String file, Manifest.Attribute[] attributes)
		throws ManifestException {

		manifest(new File(file), attributes);
	}

	public static void manifest(File file, Manifest.Attribute[] attributes)
		throws ManifestException {

		String parentFile = file.getParent();

		if (parentFile != null) {
			MkdirTask.mkdir(parentFile);
		}

		org.apache.tools.ant.taskdefs.ManifestTask manifest =
			new org.apache.tools.ant.taskdefs.ManifestTask();

		manifest.setProject(AntUtil.getProject());
		manifest.setFile(file);

		for (int i = 0; i < attributes.length; i++) {
			manifest.addConfiguredAttribute(attributes[i]);
		}

		manifest.execute();
	}

}