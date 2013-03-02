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

package com.liferay.util;

import com.liferay.portal.kernel.util.StringUtil;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;

import org.apache.tools.ant.DirectoryScanner;

/**
 * <a href="Java2Html.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Java2Html {

	public static void main(String[] args) {
		new Java2Html(args);
	}

	public Java2Html(String[] args) {
		if ((args == null) || (args.length != 3)) {
			return;
		}

		String batchFile = args[0];
		String srcDir = args[1];
		String outDir = args[2];
		//String projectName = args[3];

		//batchFile = StringUtil.replace(batchFile, "/", "\\");

		try {
			Runtime rt = Runtime.getRuntime();

			String javaHome = System.getProperty("java.home");

			if (javaHome.endsWith("\\jre") || javaHome.endsWith("/jre")) {
				javaHome = javaHome.substring(0, javaHome.length() - 4);
			}

			Process p = rt.exec(
				batchFile +
				" -js " + srcDir +
				" -d " + outDir +
				" -jd " + javaHome + "/docs/api" +
					" http://java.sun.com/products/jdk/1.4/docs/api" +
				" -m 4 -t 4" +
				//" -n " + projectName +
				" -nf");

			// Read process input to ensure process is completed before
			// proceding to next step

			BufferedReader br = new BufferedReader(
				new InputStreamReader(p.getInputStream()));

			while (br.readLine() != null) {
			}

			br.close();

			DirectoryScanner ds = new DirectoryScanner();

			ds.setIncludes(new String[] {"**\\*.java.html"});
			ds.setBasedir(outDir);

			ds.scan();

			String[] files = ds.getIncludedFiles();

			for (int i = 0; i < files.length; i++) {
				File file = new File(outDir + "/" + files[i]);

				String content = FileUtil.read(file);

				content = StringUtil.replace(
					content, "stylesheet.css", "java2html.css");

				FileUtil.write(file, content);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		System.exit(0);
	}

}