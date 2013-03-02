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

package com.liferay.portal.search;

import com.liferay.util.HttpUtil;

import java.text.SimpleDateFormat;

import java.util.Date;

import org.dom4j.Element;
import org.dom4j.Namespace;
import org.dom4j.QName;

/**
 * <a href="OpenSearchUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 * @author Brian Wing Shun Chan
 *
 */
public class OpenSearchUtil {

	public static final int DEFAULT_NAMESPACE = 0;

	public static final int OS_NAMESPACE = 1;

	public static final int RELEVANCE_NAMESPACE = 2;

	public static Element addElement(
		Element el, String name, int namespaceType) {

		return el.addElement(getQName(name, namespaceType));
	}

	public static Element addElement(
		Element el, String name, int namespaceType, Date value) {

		SimpleDateFormat sdf = new SimpleDateFormat(
			"yyyy-MM-dd'T'HH:mm:sszzz");

		return addElement(el, name, namespaceType, sdf.format(value));
	}

	public static Element addElement(
		Element el, String name, int namespaceType, double value) {

		return addElement(el, name, namespaceType, String.valueOf(value));
	}

	public static Element addElement(
		Element el, String name, int namespaceType, int value) {

		return addElement(el, name, namespaceType, String.valueOf(value));
	}

	public static Element addElement(
		Element el, String name, int namespaceType, String value) {

		Element returnElement = el.addElement(getQName(name, namespaceType));

		returnElement.addCDATA(value);

		return returnElement;
	}

	public static void addLink(
		Element root, String searchURL, String rel, String keywords, int page,
		int itemsPerPage) {

		Element link = addElement(root, "link", DEFAULT_NAMESPACE);

		link.addAttribute("rel", rel);
		link.addAttribute(
			"href",
			searchURL + "?keywords=" + HttpUtil.encodeURL(keywords) + "&p=" +
				page + "&c=" + itemsPerPage + "&format=atom");
		link.addAttribute("type", "application/atom+xml");
	}

	public static Namespace getNamespace(int namespaceType) {
		Namespace namespace = null;

		if (namespaceType == DEFAULT_NAMESPACE) {
			namespace = new Namespace("", "http://www.w3.org/2005/Atom");
		}
		else if (namespaceType == OS_NAMESPACE) {
			namespace = new Namespace(
				"opensearch", "http://a9.com/-/spec/opensearch/1.1/");
		}
		else if (namespaceType == RELEVANCE_NAMESPACE) {
			namespace = new Namespace(
				"relevance",
				"http://a9.com/-/opensearch/extensions/relevance/1.0/");
		}

		return namespace;
	}

	public static QName getQName(String name, int namespaceType) {
		return new QName(name, getNamespace(namespaceType));
	}

}