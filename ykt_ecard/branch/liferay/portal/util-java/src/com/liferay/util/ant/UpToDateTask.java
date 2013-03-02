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

import org.apache.tools.ant.Project;
import org.apache.tools.ant.taskdefs.UpToDate;

/**
 * <a href="UpToDateTask.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UpToDateTask {

	public static boolean isUpToDate(String source, String target) {
		return isUpToDate(new File(source), new File(target));
	}

	public static boolean isUpToDate(File source, File target) {
		if (!source.exists() || !target.exists()) {
			return false;
		}

		Project project = AntUtil.getProject();

		UpToDate upToDate = new UpToDate();

		upToDate.setProject(project);
		upToDate.setProperty("uptodate");
		upToDate.setSrcfile(source);
		upToDate.setTargetFile(target);

		upToDate.execute();

		if (project.getProperty("uptodate") != null) {
			return true;
		}
		else {
			return false;
		}
	}

}