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

import com.liferay.portal.kernel.util.GetterUtil;

import org.dom4j.Element;
import org.dom4j.Namespace;
import org.dom4j.QName;

/**
 * <a href="DocUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DocUtil {

	public static void add(Element el, String name, boolean text) {
		add(el, name, String.valueOf(text));
	}

	public static void add(Element el, String name, double text) {
		add(el, name, String.valueOf(text));
	}

	public static void add(Element el, String name, float text) {
		add(el, name, String.valueOf(text));
	}

	public static void add(Element el, String name, int text) {
		add(el, name, String.valueOf(text));
	}

	public static void add(Element el, String name, long text) {
		add(el, name, String.valueOf(text));
	}

	public static void add(Element el, String name, short text) {
		add(el, name, String.valueOf(text));
	}

	public static void add(Element el, String name, Object text) {
		add(el, name, String.valueOf(text));
	}

	public static void add(Element el, String name, String text) {
		el.addElement(name).addText(GetterUtil.getString(text));
	}

	public static Element add(Element el, String name, Namespace ns) {
		return el.addElement(new QName(name, ns));
	}

	public static void add(
		Element el, String name, Namespace ns, boolean text) {

		add(el, name, ns, String.valueOf(text));
	}

	public static void add(Element el, String name, Namespace ns, double text) {
		add(el, name, ns, String.valueOf(text));
	}

	public static void add(Element el, String name, Namespace ns, float text) {
		add(el, name, ns, String.valueOf(text));
	}

	public static void add(Element el, String name, Namespace ns, int text) {
		add(el, name, ns, String.valueOf(text));
	}

	public static void add(Element el, String name, Namespace ns, long text) {
		add(el, name, ns, String.valueOf(text));
	}

	public static void add(Element el, String name, Namespace ns, short text) {
		add(el, name, ns, String.valueOf(text));
	}

	public static void add(Element el, String name, Namespace ns, Object text) {
		add(el, name, ns, String.valueOf(text));
	}

	public static void add(Element el, String name, Namespace ns, String text) {
		el.addElement(new QName(name, ns)).addText(GetterUtil.getString(text));
	}

}