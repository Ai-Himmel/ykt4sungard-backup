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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Tuple;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.WebDAVProps;
import com.liferay.portal.webdav.WebDAVUtil;
import com.liferay.util.xml.XMLFormatter;

import java.io.StringReader;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.Namespace;
import org.dom4j.QName;
import org.dom4j.io.SAXReader;

/**
 * <a href="WebDAVPropsImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class WebDAVPropsImpl
	extends WebDAVPropsModelImpl implements WebDAVProps {

	public WebDAVPropsImpl() {
	}

	public String getProps() {
		String props = super.getProps();

		if (Validator.isNull(props)) {
			return _PROPS;
		}
		else {
			return props;
		}
	}

	public Set getPropsSet() throws Exception {
		Set propsSet = new HashSet();

		Document doc = _getPropsDocument();

		Element root = doc.getRootElement();

		Iterator itr = root.elements().iterator();

		while (itr.hasNext()) {
			Element el = (Element)itr.next();

			String prefix = el.getNamespacePrefix();
			String uri = el.getNamespaceURI();

			Namespace namespace = null;

			if (uri.equals(WebDAVUtil.DAV_URI.getURI())) {
				namespace = WebDAVUtil.DAV_URI;
			}
			else if (Validator.isNull(prefix)) {
				namespace = Namespace.get(uri);
			}
			else {
				namespace = Namespace.get(prefix, uri);
			}

			propsSet.add(new Tuple(el.getName(), namespace));
		}

		return propsSet;
	}

	public String getText(String name, String prefix, String uri)
		throws Exception {

		Namespace namespace = null;

		if (Validator.isNull(prefix)) {
			namespace = Namespace.get(uri);
		}
		else {
			namespace = Namespace.get(prefix, uri);
		}

		QName qname = new QName(name, namespace);

		Document doc = _getPropsDocument();

		Element root = doc.getRootElement();

		Element prop = root.element(qname);

		return prop.getText();
	}

	public void addProp(String name, String prefix, String uri)
		throws Exception {

		Namespace namespace = null;

		if (Validator.isNull(prefix)) {
			namespace = Namespace.get(uri);
		}
		else {
			namespace = Namespace.get(prefix, uri);
		}

		QName qname = new QName(name, namespace);

		Element root = _removeExisting(qname);

		root.addElement(qname);
	}

	public void addProp(String name, String prefix, String uri, String text)
		throws Exception {

		Namespace namespace = null;

		if (Validator.isNull(prefix)) {
			namespace = Namespace.get(uri);
		}
		else {
			namespace = Namespace.get(prefix, uri);
		}

		QName qname = new QName(name, namespace);

		Element root = _removeExisting(qname);

		root.addElement(qname).addText(text);
	}

	public void removeProp(String name, String prefix, String uri)
		throws Exception {

		Namespace namespace = null;

		if (Validator.isNull(prefix)) {
			namespace = Namespace.get(uri);
		}
		else {
			namespace = Namespace.get(prefix, uri);
		}

		QName qname = new QName(name, namespace);

		_removeExisting(qname);
	}

	public void store() throws Exception {
		if (_document != null) {
			String xml = XMLFormatter.toString(
				_document, StringPool.FOUR_SPACES);

			setProps(xml);

			_document = null;
		}
	}

	private Document _getPropsDocument() throws DocumentException {
		if (_document == null) {
			SAXReader reader = new SAXReader();

			_document = reader.read(new StringReader(getProps()));
		}

		return _document;
	}

	private Element _removeExisting(QName qname) throws Exception {
		Document doc = _getPropsDocument();

		Element root = doc.getRootElement();

		Iterator itr = root.elements(qname).iterator();

		while (itr.hasNext()) {
			Element el = (Element)itr.next();

			root.remove(el);
		}

		return root;
	}

	private static final String _PROPS = "<properties />";

	private Document _document = null;

}