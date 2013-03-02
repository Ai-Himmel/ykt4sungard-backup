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

package com.liferay.util.xml;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.util.TextFormatter;

import java.lang.reflect.Method;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Element;

/**
 * <a href="BeanToXMLUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 *
 */
public class BeanToXMLUtil {

	public static void addBean(Object obj, Element parentEl) {
		String classNameWitoutPackage = getClassNameWithoutPackage(
			obj.getClass().getName());

		Element el = parentEl.addElement(classNameWitoutPackage);

		addFields(obj, el);
	}

	public static void addFields(Object obj, Element parentEl) {
		Method[] methods = obj.getClass().getMethods();

		for (int i = 0; i < methods.length; i++) {
			Method method = methods[i];

			if (method.getName().startsWith("get") &&
				!method.getName().equals("getClass")) {

				String memberName = StringUtil.replace(
					method.getName(), "get", StringPool.BLANK);

				memberName = TextFormatter.format(memberName, TextFormatter.I);
				memberName = TextFormatter.format(memberName, TextFormatter.K);

				try {
					Object returnValue = method.invoke(obj, new Object[] {});

					DocUtil.add(parentEl, memberName, returnValue.toString());
				}
				catch (Exception e) {
					if (_log.isWarnEnabled()) {
						_log.warn(e.getMessage());
					}
				}
			}
		}
	}

	public static String getClassNameWithoutPackage(String className) {
		String[] classNameArray = StringUtil.split(
			className, StringPool.PERIOD);

		String classNameWitoutPackage =
			classNameArray[classNameArray.length - 1];

		classNameWitoutPackage = TextFormatter.format(
			classNameWitoutPackage, TextFormatter.I);
		classNameWitoutPackage = TextFormatter.format(
			classNameWitoutPackage, TextFormatter.K);

		return classNameWitoutPackage;
	}

	private static Log _log = LogFactory.getLog(BeanToXMLUtil.class);

}