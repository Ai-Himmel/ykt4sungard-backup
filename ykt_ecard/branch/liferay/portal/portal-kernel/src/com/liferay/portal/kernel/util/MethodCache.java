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

import java.lang.reflect.Method;

import java.util.HashMap;
import java.util.Map;

/**
 * <a href="MethodCache.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael C. Han
 *
 */
public class MethodCache {

	public static Method get(String className, String methodName)
		throws ClassNotFoundException, NoSuchMethodException {

		return get(className, methodName, new Class[] {});
	}

	public static Method get(
			String className, String methodName, Class[] parameterTypes)
		throws ClassNotFoundException, NoSuchMethodException {

		MethodKey methodKey = new MethodKey(
			className, methodName, parameterTypes);

		return get(methodKey);
	}

	public static Method get(MethodKey methodKey)
		throws ClassNotFoundException, NoSuchMethodException {

		return _instance._get(methodKey);
	}

	private MethodCache() {
		_classes = new HashMap();
		_methods = new HashMap();
	}

	private Method _get(MethodKey methodKey)
		throws ClassNotFoundException, NoSuchMethodException {

		Method method = (Method)_methods.get(methodKey);

		if (method == null) {
			String className = methodKey.getClassName();
			String methodName = methodKey.getMethodName();
			Class[] types = methodKey.getTypes();

			Class classObj = (Class)_classes.get(className);

			if (classObj == null) {
				ClassLoader contextClassLoader =
					Thread.currentThread().getContextClassLoader();

				classObj = contextClassLoader.loadClass(className);

				_classes.put(className, classObj);
			}

			method = classObj.getMethod(methodName, types);

			_methods.put(methodKey, method);
		}

		return method;
	}

	private static MethodCache _instance = new MethodCache();

	private Map _classes;
	private Map _methods;

}