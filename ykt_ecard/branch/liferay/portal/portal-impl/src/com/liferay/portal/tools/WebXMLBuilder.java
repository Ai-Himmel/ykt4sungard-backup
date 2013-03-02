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
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.Html;
import com.liferay.util.xml.XMLFormatter;
import com.liferay.util.xml.XMLMerger;
import com.liferay.util.xml.descriptor.WebXML23Descriptor;
import com.liferay.util.xml.descriptor.WebXML24Descriptor;

import java.io.IOException;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;

/**
 * <a href="WebXMLBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Tang Ying Jian
 * @author Brian Myunghun Kim
 *
 */
public class WebXMLBuilder {

	public static void main(String[] args) {
		if (args.length == 3) {
			new WebXMLBuilder(args[0], args[1], args[2]);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	public static String organizeWebXML(String webXML)
		throws DocumentException, IOException {

		webXML = Html.stripComments(webXML);

		double version = 2.3;

		Document doc = PortalUtil.readDocumentFromXML(webXML);

		Element root = doc.getRootElement();

		version = GetterUtil.getDouble(root.attributeValue("version"), version);

		XMLMerger merger = null;

		if (version == 2.3) {
			merger = new XMLMerger(new WebXML23Descriptor());
		}
		else {
			merger = new XMLMerger(new WebXML24Descriptor());
		}

		merger.organizeXML(doc);

		webXML = XMLFormatter.toString(doc);

		return webXML;
	}

	public WebXMLBuilder(String originalWebXML, String customWebXML,
						 String mergedWebXML) {

		try {
			String customContent = FileUtil.read(customWebXML);

			int x = customContent.indexOf("<web-app");

			x = customContent.indexOf(">", x) + 1;

			int y = customContent.indexOf("</web-app>");

			customContent = customContent.substring(x, y);

			String originalContent = FileUtil.read(originalWebXML);

			int z = originalContent.indexOf("<web-app");

			z = originalContent.indexOf(">", z) + 1;

			String mergedContent =
				originalContent.substring(0, z) + customContent +
					originalContent.substring(z, originalContent.length());

			mergedContent = organizeWebXML(mergedContent);

			FileUtil.write(mergedWebXML, mergedContent, true);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}