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

package com.liferay.portal.kernel.util;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.log.LogUtil;

/**
 * <a href="JavaProps.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JavaProps {

	public static final double JAVA_CLASS_VERSION_JDK_5 = 49.0;

	public static String getJavaClassPath() {
		return _instance._javaClassPath;
	}

	public static double getJavaClassVersion() {
		return _instance._javaClassVersion;
	}

	public static String getJavaRuntimeVersion() {
		return _instance._javaRuntimeVersion;
	}

	public static double getJavaSpecificationVersion() {
		return _instance._javaSpecificationVersion;
	}

	public static String getJavaVersion() {
		return _instance._javaVersion;
	}

	public static String getJavaVmVersion() {
		return _instance._javaVmVersion;
	}

	public static boolean isJDK5() {
		if (JavaProps.getJavaClassVersion() >=
				JavaProps.JAVA_CLASS_VERSION_JDK_5) {

			return true;
		}
		else {
			return false;
		}
	}

	private JavaProps() {
		_javaClassPath = System.getProperty("java.class.path");
		_javaClassVersion = Double.parseDouble(System.getProperty(
			"java.class.version"));
		_javaRuntimeVersion = System.getProperty("java.runtime.version");
		_javaSpecificationVersion = Double.parseDouble(System.getProperty(
			"java.specification.version"));
		_javaVersion = System.getProperty("java.version");
		_javaVmVersion = System.getProperty("java.vm.version");

		LogUtil.debug(_log, System.getProperties());
	}

	private static Log _log = LogFactoryUtil.getLog(JavaProps.class);

	private static JavaProps _instance = new JavaProps();

	private String _javaClassPath;
	private double _javaClassVersion;
	private String _javaRuntimeVersion;
	private double _javaSpecificationVersion;
	private String _javaVersion;
	private String _javaVmVersion;

}