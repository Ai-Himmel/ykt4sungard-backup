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

package com.liferay.portal.deploy;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ServerDetector;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.util.FileUtil;
import com.liferay.util.SystemProperties;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

/**
 * <a href="DeployUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DeployUtil {

	public static String getAutoDeployDestDir() throws Exception {
		String destDir = PrefsPropsUtil.getString(
			PropsUtil.AUTO_DEPLOY_DEST_DIR, PropsValues.AUTO_DEPLOY_DEST_DIR);

		if (Validator.isNull(destDir)) {
			destDir = getAutoDeployServerDestDir();
		}

		return destDir;
	}

	public static String getAutoDeployServerDestDir() throws Exception {
		String destDir = null;

		String serverId = GetterUtil.getString(ServerDetector.getServerId());

		if (serverId.equals(ServerDetector.TOMCAT_ID)) {
			destDir = PrefsPropsUtil.getString(
				PropsUtil.AUTO_DEPLOY_TOMCAT_DEST_DIR,
				PropsValues.AUTO_DEPLOY_TOMCAT_DEST_DIR);
		}
		else {
			destDir = PrefsPropsUtil.getString(
				"auto.deploy." + serverId + ".dest.dir");
		}

		if (Validator.isNull(destDir)) {
			destDir = PrefsPropsUtil.getString(
				PropsUtil.AUTO_DEPLOY_DEFAULT_DEST_DIR,
				PropsValues.AUTO_DEPLOY_DEFAULT_DEST_DIR);
		}

		destDir = StringUtil.replace(
			destDir, StringPool.BACK_SLASH, StringPool.SLASH);

		return destDir;
	}

	public static String getResourcePath(String resource)
		throws Exception {

		return _instance._getResourcePath(resource);
	}

	private DeployUtil() {
	}

	private String _getResourcePath(String resource) throws IOException {
		String tmpDir = SystemProperties.get(SystemProperties.TMP_DIR);

		File file = new File(
			tmpDir + "/liferay/com/liferay/portal/deploy/dependencies/" +
				resource);

		File parentFile = file.getParentFile();

		if (parentFile != null) {
			parentFile.mkdirs();
		}

		byte[] byteArray = FileUtil.getBytes(
			getClass().getResourceAsStream("dependencies/" + resource));

		OutputStream os = new FileOutputStream(file);

		os.write(byteArray);

		return FileUtil.getAbsolutePath(file);
	}

	private static DeployUtil _instance = new DeployUtil();

}