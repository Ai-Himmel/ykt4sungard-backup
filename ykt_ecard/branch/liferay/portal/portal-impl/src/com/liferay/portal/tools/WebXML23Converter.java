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

package com.liferay.portal.tools;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.xml.XMLFormatter;

import java.util.Iterator;

import org.dom4j.Document;
import org.dom4j.Element;

/**
 * <a href="WebXML23Converter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 *
 */
public class WebXML23Converter {

	public static void main(String[] args) {
		if (args.length == 2) {
			new WebXML23Converter(args[0], args[1]);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	public WebXML23Converter(String input, String output) {
		try {
			String webXML24 = FileUtil.read(input);

			Document doc = PortalUtil.readDocumentFromXML(webXML24);

			Element root = doc.getRootElement();

			double version = GetterUtil.getDouble(
				root.attributeValue("version"));

			if (version == 2.4) {
				System.out.println(
					"Convert web.xml because it is Servlet 2.4");
			}
			else {
				System.out.println(
					"Do not convert web.xml because it is not Servlet 2.4");

				return;
			}

			Iterator itr1 = root.elements("filter-mapping").iterator();

			while (itr1.hasNext()) {
				Element filterMapping = (Element)itr1.next();

				Iterator itr2 = filterMapping.elements("dispatcher").iterator();

				while (itr2.hasNext()) {
					Element dispatcher = (Element)itr2.next();

					dispatcher.detach();
				}
			}

			String webXML23 = XMLFormatter.toString(doc);

			int x = webXML23.indexOf("<web-app");
			int y = webXML23.indexOf(">", x);

			webXML23 = webXML23.substring(0, x) + "<!DOCTYPE web-app PUBLIC \"-//Sun Microsystems, Inc.//DTD Web Application 2.3//EN\" \"http://java.sun.com/dtd/web-app_2_3.dtd\"><web-app>" + webXML23.substring(y + 1, webXML23.length());

			webXML23 = StringUtil.replace(
				webXML23,
				new String[] {
					"<jsp-config>", "</jsp-config>"
				},
				new String[] {
					"", ""
				});

			webXML23 = XMLFormatter.toString(webXML23);

			FileUtil.write(output, webXML23);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}