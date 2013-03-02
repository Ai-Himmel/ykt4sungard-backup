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

package com.liferay.support.glassfish;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import java.text.SimpleDateFormat;

import java.util.Date;

/**
 * <a href="LiferayAddonUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raju Uppalapati
 * @author Brian Wing Shun Chan
 *
 */
public class LiferayAddonUtil {

	public static void copyFile(String sourceFile, String destFile)
		throws IOException {

		copyFile(new File(sourceFile), new File(destFile));
	}

	public static void copyFile(File sourceFile, File destFile)
		throws IOException {

		boolean doCopy = false;

		if (sourceFile.exists() && sourceFile.isFile()) {
			if (!sourceFile.toURI().equals(destFile.toURI())) {
				doCopy = true;

				if (destFile.exists()) {
					if (destFile.canWrite()) {
						destFile.delete();
					}
					else {
						doCopy = false;
					}
				}
			}
		}

		if (doCopy) {
			InputStream in = new FileInputStream(sourceFile);
			OutputStream out = new FileOutputStream(destFile);

			byte[] buf = new byte[1024];
			int len = 0;

			while ((len = in.read(buf)) > 0) {
				out.write(buf, 0, len);
			}

			in.close();
			out.close();
		}
	}

	public static String getTimestamp() {
		SimpleDateFormat sdf = new SimpleDateFormat(_TIMESTAMP);

		return sdf.format(new Date());
	}

	public static File getTmpDir() {
		File tmpDir = new File(
			System.getProperty("java.io.tmpdir") + "/" + getTimestamp());

		if (!tmpDir.exists()) {
			tmpDir.mkdirs();
		}

		return tmpDir;
	}

	private static final String _TIMESTAMP = "yyyyMMddHHmm";

}