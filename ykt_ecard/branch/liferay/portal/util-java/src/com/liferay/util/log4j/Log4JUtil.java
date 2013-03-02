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

package com.liferay.util.log4j;

import java.net.URL;

import java.util.Enumeration;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.apache.log4j.Level;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.apache.log4j.helpers.NullEnumeration;
import org.apache.log4j.xml.DOMConfigurator;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="Log4JUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Log4JUtil {

	public static void configureLog4J(URL url) {
		if (url == null) {
			return;
		}

		if (Logger.getRootLogger().getAllAppenders() instanceof
				NullEnumeration) {

			DOMConfigurator.configure(url);
		}
		else {
			Set currentLoggerNames = new HashSet();

			Enumeration enu = LogManager.getCurrentLoggers();

			while (enu.hasMoreElements()) {
				Logger logger = (Logger)enu.nextElement();

				currentLoggerNames.add(logger.getName());
			}

			try {
				SAXReader reader = new SAXReader();

				Document doc = reader.read(url);

				Element root = doc.getRootElement();

				Iterator itr = root.elements("category").iterator();

				while (itr.hasNext()) {
					Element category = (Element)itr.next();

					String name = category.attributeValue("name");
					String priority =
						category.element("priority").attributeValue("value");

					Logger logger = Logger.getLogger(name);

					logger.setLevel(Level.toLevel(priority));
				}
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

}