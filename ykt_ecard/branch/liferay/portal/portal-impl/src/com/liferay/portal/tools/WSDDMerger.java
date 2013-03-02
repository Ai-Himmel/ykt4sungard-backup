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

import com.liferay.util.FileUtil;
import com.liferay.util.xml.XMLFormatter;

import java.io.File;
import java.io.IOException;

import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="WSDDMerger.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WSDDMerger {

	public static void main(String[] args) {
		new WSDDMerger(args[0], args[1]);
	}

	public static void merge(String source, String destination)
		throws DocumentException, IOException {

		// Source

		File sourceFile = new File(source);

		SAXReader reader = new SAXReader();

		Document doc = reader.read(sourceFile);

		Element root = doc.getRootElement();

		List sourceServices = root.elements("service");

		if (sourceServices.size() == 0) {
			return;
		}

		// Destination

		File destinationFile = new File(destination);

		reader = new SAXReader();

		doc = reader.read(destinationFile);

		root = doc.getRootElement();

		Map servicesMap = new TreeMap();

		Iterator itr = root.elements("service").iterator();

		while (itr.hasNext()) {
			Element service = (Element)itr.next();

			String name = service.attributeValue("name");

			servicesMap.put(name, service);

			service.detach();
		}

		itr = sourceServices.iterator();

		while (itr.hasNext()) {
			Element service = (Element)itr.next();

			String name = service.attributeValue("name");

			servicesMap.put(name, service);

			service.detach();
		}

		itr = servicesMap.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			Element service = (Element)entry.getValue();

			root.add(service);
		}

		FileUtil.write(destination, XMLFormatter.toString(doc), true);
	}

	public WSDDMerger(String source, String destination) {
		try {
			merge(source, destination);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}