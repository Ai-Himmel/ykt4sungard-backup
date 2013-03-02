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

package com.liferay.portlet.westminstercatechism.util;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portlet.westminstercatechism.model.WCEntry;

import java.net.URL;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="WCUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WCUtil {

	public static List getLarger() {
		return _instance._getLarger();
	}

	public static List getShorter() {
		return _instance._getShorter();
	}

	public static String translate(String text) {
		return StringUtil.replace(
			text,
			new String[] {
				" doth ", " hath "
			},
			new String[] {
				" does ", " has "
			}
		);
	}

	private WCUtil() {
		Document doc = null;

		try {
			SAXReader reader = new SAXReader();

			ClassLoader classLoader = getClass().getClassLoader();

			URL url = classLoader.getResource(
				"com/liferay/portlet/westminstercatechism/dependencies/" +
					"westminster_catechmism.xml");

			doc = reader.read(url);
		}
		catch (DocumentException de) {
			_log.error(de);
		}

		_shorter = new ArrayList();

		Element root = doc.getRootElement();

		Iterator itr1 = root.element("shorter").elements("entry").iterator();

		while (itr1.hasNext()) {
			Element entry = (Element)itr1.next();

			List proofs = new ArrayList();

			Iterator itr2 = entry.element(
				"proofs").elements("scriptures").iterator();

			while (itr2.hasNext()) {
				Element scriptures = (Element)itr2.next();

				proofs.add(StringUtil.split(
					scriptures.getText(), StringPool.SEMICOLON));
			}

			_shorter.add(
				new WCEntry(
					entry.elementText("question"),
					entry.elementText("answer"),
					(String[][])proofs.toArray(new String[0][0])));
		}

		_shorter = Collections.unmodifiableList(_shorter);

		_larger = new ArrayList();

		itr1 = root.element("larger").elements("entry").iterator();

		while (itr1.hasNext()) {
			Element entry = (Element)itr1.next();

			List proofs = new ArrayList();

			Iterator itr2 = entry.element(
				"proofs").elements("scriptures").iterator();

			while (itr2.hasNext()) {
				Element scriptures = (Element)itr2.next();

				proofs.add(StringUtil.split(
					scriptures.getText(), StringPool.SEMICOLON));
			}

			_larger.add(
				new WCEntry(
					entry.elementText("question"),
					entry.elementText("answer"),
					(String[][])proofs.toArray(new String[0][0])));
		}

		_larger = Collections.unmodifiableList(_larger);
	}

	private List _getLarger() {
		return _larger;
	}

	private List _getShorter() {
		return _shorter;
	}

	private static Log _log = LogFactory.getLog(WCUtil.class);

	private static WCUtil _instance = new WCUtil();

	private List _larger;
	private List _shorter;

}