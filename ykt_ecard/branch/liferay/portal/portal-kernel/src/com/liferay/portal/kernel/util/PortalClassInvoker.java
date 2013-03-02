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

/**
 * <a href="PortalClassInvoker.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortalClassInvoker {

	public static Object invoke(String className, String methodName)
		throws Exception {

		return invoke(className, methodName, new Object[] {});
	}

	public static Object invoke(String className, String methodName, Object arg)
		throws Exception {

		return invoke(className, methodName, new Object[] {arg});
	}

	public static Object invoke(
			String className, String methodName, Object arg1, Object arg2)
		throws Exception {

		return invoke(className, methodName, new Object[] {arg1, arg2});
	}

	public static Object invoke(
			String className, String methodName, Object arg1, Object arg2,
			Object arg3)
		throws Exception {

		return invoke(className, methodName, new Object[] {arg1, arg2, arg3});
	}

	public static Object invoke(
			String className, String methodName, Object[] args)
		throws Exception {

		return invoke(className, methodName, args, true);
	}

	public static Object invoke(
		String className, String methodName, boolean newInstance)
		throws Exception {

		return invoke(className, methodName, new Object[] {}, newInstance);
	}

	public static Object invoke(
			String className, String methodName, Object arg,
			boolean newInstance)
		throws Exception {

		return invoke(className, methodName, new Object[] {arg}, newInstance);
	}

	public static Object invoke(
			String className, String methodName, Object arg1, Object arg2,
			boolean newInstance)
		throws Exception {

		return invoke(
			className, methodName, new Object[] {arg1, arg2}, newInstance);
	}

	public static Object invoke(
			String className, String methodName, Object arg1, Object arg2,
			Object arg3, boolean newInstance)
		throws Exception {

		return invoke(
			className, methodName, new Object[] {arg1, arg2, arg3},
			newInstance);
	}

	public static Object invoke(
			String className, String methodName, Object[] args,
			boolean newInstance)
		throws Exception {

		ClassLoader contextClassLoader =
			Thread.currentThread().getContextClassLoader();

		try {
			Thread.currentThread().setContextClassLoader(
				PortalClassLoaderUtil.getClassLoader());

			MethodWrapper methodWrapper = new MethodWrapper(
				className, methodName, args);

			return MethodInvoker.invoke(methodWrapper, newInstance);
		}
		finally {
			Thread.currentThread().setContextClassLoader(contextClassLoader);
		}
	}

}