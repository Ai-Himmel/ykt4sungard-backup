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

package com.liferay.util.ant;

import java.io.File;

import org.apache.tools.ant.Project;
import org.apache.tools.ant.taskdefs.War;

/**
 * <a href="WarTask.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Unknown
 * @version $Rev: $
 *
 */
public class WarTask {

	public static void war(
		String baseDir, String destination, String excludes, String webxml) {

		war(
			new File(baseDir), new File(destination), excludes,
			new File(webxml));
	}

	public static void war(
		File baseDir, File destination, String excludes, File webxml) {

		Project project = AntUtil.getProject();

		War war = new War();

		war.setProject(project);
		war.setBasedir(baseDir);
		war.setDestFile(destination);
		war.setExcludes(excludes);
		war.setWebxml(webxml);

		war.execute();
	}

}