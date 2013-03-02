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

package com.liferay.portlet.xslcontent.util;

import com.liferay.portal.kernel.util.ByteArrayMaker;
import com.liferay.util.Http;

import java.io.IOException;
import java.io.StringReader;

import java.net.URL;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;

/**
 * <a href="XSLContentUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class XSLContentUtil {

	public static String DEFAULT_XML_URL =
		"http://www.w3schools.com/xml/simple.xml";

	public static String DEFAULT_XSL_URL =
		"http://www.w3schools.com/xml/simple.xsl";

	public static String transform(URL xmlURL, URL xslURL)
		throws IOException, TransformerException {

		String xml = Http.URLtoString(xmlURL);
		String xsl = Http.URLtoString(xslURL);

		StreamSource xmlSource = new StreamSource(new StringReader(xml));
		StreamSource xslSource = new StreamSource(new StringReader(xsl));

		TransformerFactory transformerFactory =
			TransformerFactory.newInstance();

		Transformer transformer =
			transformerFactory.newTransformer(xslSource);

		ByteArrayMaker bam = new ByteArrayMaker();

		transformer.transform(xmlSource, new StreamResult(bam));

		return bam.toString();
	}

}