/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.journal.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Company;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.service.spring.CompanyLocalServiceUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.service.spring.JournalTemplateServiceUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.FiniteUniqueStack;
import com.liferay.util.LocaleUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.xml.XMLFormatter;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.StringReader;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Stack;

import javax.portlet.PortletRequest;
import javax.portlet.PortletSession;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.DocumentFactory;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;
import org.dom4j.Node;
import org.dom4j.XPath;
import org.dom4j.io.SAXReader;

/**
 * <a href="JournalUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.23 $
 *
 */
public class JournalUtil {

	public static final int MAX_STACK_SIZE = 20;

	public static final String XML_INDENT = "  ";

	public static void addRecentArticle(
		PortletRequest req, JournalArticle article) {

		if (article != null) {
			Stack stack = getRecentArticles(req);

			stack.push(article);
		}
	}

	public static void addRecentStructure(
		PortletRequest req, JournalStructure structure) {

		if (structure != null) {
			Stack stack = getRecentStructures(req);

			stack.push(structure);
		}
	}

	public static void addRecentTemplate(
		PortletRequest req, JournalTemplate template) {

		if (template != null) {
			Stack stack = getRecentTemplates(req);

			stack.push(template);
		}
	}

	public static void addReservedEl(
		Element root, Map tokens, String name, String value) {

		// XML

		DocumentFactory docFactory = DocumentFactory.getInstance();

		Element dynamicEl = docFactory.createElement("dynamic-element");

		dynamicEl.add(docFactory.createAttribute(dynamicEl, "name", name));
		dynamicEl.add(docFactory.createAttribute(dynamicEl, "type", "text"));

		Element dynamicContent = docFactory.createElement("dynamic-content");

		//dynamicContent.setText("<![CDATA[" + value + "]]>");
		dynamicContent.setText(value);

		dynamicEl.add(dynamicContent);

		root.add(dynamicEl);

		// Tokens

		tokens.put(
			StringUtil.replace(name, StringPool.DASH, StringPool.UNDERLINE),
			value);
	}

	public static String formatXML(String xml)
		throws DocumentException, IOException {

		// This is only supposed to format your xml, however, it will also
		// unwantingly change &#169; and other characters like it into their
		// respective readable versions

		xml = StringUtil.replace(xml, "&#", "[$SPECIAL_CHARACTER$]");

		xml = XMLFormatter.toString(xml, XML_INDENT);

		xml = StringUtil.replace(xml, "[$SPECIAL_CHARACTER$]", "&#");

		return xml;
	}

	public static String formatXML(Document doc)
		throws DocumentException, IOException {

		return XMLFormatter.toString(doc, XML_INDENT);
	}

	public static Stack getRecentArticles(PortletRequest req) {
		PortletSession ses = req.getPortletSession();

		Stack recentArticles =
			(Stack)ses.getAttribute(WebKeys.JOURNAL_RECENT_ARTICLES);

		if (recentArticles == null) {
			recentArticles = new FiniteUniqueStack(MAX_STACK_SIZE);

			ses.setAttribute(WebKeys.JOURNAL_RECENT_ARTICLES, recentArticles);
		}

		return recentArticles;
	}

	public static Stack getRecentStructures(PortletRequest req) {
		PortletSession ses = req.getPortletSession();

		Stack recentStructures =
			(Stack)ses.getAttribute(WebKeys.JOURNAL_RECENT_STRUCTURES);

		if (recentStructures == null) {
			recentStructures = new FiniteUniqueStack(MAX_STACK_SIZE);

			ses.setAttribute(
				WebKeys.JOURNAL_RECENT_STRUCTURES, recentStructures);
		}

		return recentStructures;
	}

	public static Stack getRecentTemplates(PortletRequest req) {
		PortletSession ses = req.getPortletSession();

		Stack recentTemplates =
			(Stack)ses.getAttribute(WebKeys.JOURNAL_RECENT_TEMPLATES);

		if (recentTemplates == null) {
			recentTemplates = new FiniteUniqueStack(MAX_STACK_SIZE);

			ses.setAttribute(WebKeys.JOURNAL_RECENT_TEMPLATES, recentTemplates);
		}

		return recentTemplates;
	}

	public static String getTemplateXsl(
			String templateId, Map tokens, String languageId)
		throws PortalException, SystemException {

		return getTemplateXsl(templateId, tokens, languageId, true);
	}

	public static String getTemplateXsl(
			String templateId, Map tokens, String languageId, boolean transform)
		throws PortalException, SystemException {

		JournalTemplate template =
			JournalTemplateServiceUtil.getTemplate(templateId);

		String xsl = template.getXsl();

		if (transform) {

			// Listeners

			String[] listeners =
				PropsUtil.getArray(PropsUtil.JOURNAL_TRANSFORMER_LISTENER);

			for (int i = 0; i < listeners.length; i++) {
				TransformerListener listener = null;

				try {
					listener =
						(TransformerListener)Class.forName(
							listeners[i]).newInstance();

					listener.setTokens(tokens);
					listener.setLanguageId(languageId);
				}
				catch (Exception e) {
					e.printStackTrace();
				}

				// Modify XSL

				if (listener != null) {
					xsl = listener.onXsl(xsl);
				}
			}
		}

		return xsl;
	}

	public static Map getTokens(String companyId, String rootPath) {
		Map tokens = CollectionFactory.getHashMap();

		try {
			Company company = CompanyLocalServiceUtil.getCompany(companyId);

			String friendlyURLPath = rootPath + PropsUtil.get(
				PropsUtil.LAYOUT_FRIENDLY_URL_SERVLET_MAPPING);

			tokens.put("company_id", companyId);
			tokens.put("cms_url", rootPath + "/cms/servlet");
			tokens.put("friendly_url", friendlyURLPath);
			tokens.put("page_url", friendlyURLPath);
			tokens.put("portal_url", company.getPortalURL());
			tokens.put("root_path", rootPath);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return tokens;
	}

	public static String mergeLocaleContent(
		String curContent, String newContent, String xsd) {

		try {
			SAXReader reader = new SAXReader();

			Document curContentDoc = reader.read(new StringReader(curContent));
			Document newContentDoc = reader.read(new StringReader(newContent));
			Document xsdDoc = reader.read(new StringReader(xsd));

			Element curContentRoot = curContentDoc.getRootElement();
			Element newContentRoot = newContentDoc.getRootElement();
			Element xsdRoot = xsdDoc.getRootElement();

			curContentRoot.addAttribute(
				"default-locale",
				newContentRoot.attributeValue("default-locale"));
			curContentRoot.addAttribute(
				"available-locales",
				newContentRoot.attributeValue("available-locales"));

			Stack path = new Stack();

			path.push(xsdRoot.getName());

			_merge(
				path, curContentDoc, newContentDoc, xsdRoot,
				LocaleUtil.toLanguageId(Locale.getDefault()));

			curContent = formatXML(curContentDoc);
		}
		catch (Exception e) {
			_log.error(e);
		}

		return curContent;
	}

	public static String transform(
			Map tokens, String languageId, String xml, String xsl)
		throws TransformerException {

		// Listeners

		List listenersList = new ArrayList();

		String[] listeners =
			PropsUtil.getArray(PropsUtil.JOURNAL_TRANSFORMER_LISTENER);

		for (int i = 0; i < listeners.length; i++) {
			TransformerListener listener = null;

			try {
				listener =
					(TransformerListener)Class.forName(
						listeners[i]).newInstance();

				listener.setTokens(tokens);
				listener.setLanguageId(languageId);

				listenersList.add(listener);
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			// Modify XML

			_log.debug("XML before listener\n" + xml);

			if (listener != null) {
				xml = listener.onXml(xml);

				_log.debug("XML after listener\n" + xml);
			}

			// Modify XSL

			_log.debug("XSL before listener\n" + xsl);

			if (listener != null) {
				xsl = listener.onXsl(xsl);

				_log.debug("XSL after listener\n" + xsl);
			}
		}

		// Transform

		StreamSource xmlSource = new StreamSource(new StringReader(xml));
		StreamSource xslSource = new StreamSource(new StringReader(xsl));

		ByteArrayOutputStream outputBaos = new ByteArrayOutputStream();

		TransformerFactory transformerFactory =
			TransformerFactory.newInstance();

		transformerFactory.setURIResolver(new URIResolver(tokens, languageId));

		Transformer transformer = transformerFactory.newTransformer(xslSource);

		transformer.transform(xmlSource, new StreamResult(outputBaos));

		String output = outputBaos.toString();

		for (int i = 0; i < listenersList.size(); i++) {
			TransformerListener listener =
				(TransformerListener)listenersList.get(i);

			// Modify output

			_log.debug("Output before listener\n" + output);

			output = listener.onOutput(output);

			_log.debug("Output after listener\n" + output);
		}

		return output;
	}

	private static void _merge(
		Stack path, Document curDoc, Document newDoc, Element xsdEl,
		String defaultLocale) {

		String elPath = "";

		for (int i = 0; i < path.size(); i++) {
			elPath += "/" + path.elementAt(i);
		}

		for (int i = 0; i < xsdEl.nodeCount(); i++) {
			Node xsdNode = xsdEl.node(i);

			if ((xsdNode instanceof Element) &&
				(xsdNode.getName().equals("dynamic-element"))) {

				Element xsdElement = (Element)xsdNode;

				String localPath =
					"dynamic-element[@name='" +
						xsdElement.attributeValue("name") + "']";

				String fullPath = elPath + "/" + localPath;

				XPath xPathSelector = DocumentHelper.createXPath(fullPath);

				List curElements = xPathSelector.selectNodes(curDoc);

				Element newEl =
					(Element)xPathSelector.selectNodes(newDoc).get(0);

				if (curElements.size() > 0) {
					Element curEl = (Element)curElements.get(0);

					List curDynamicContents = curEl.elements("dynamic-content");

					Element newContentEl = newEl.element("dynamic-content");

					String newContentLanguageId = newContentEl.attributeValue(
						"language-id", StringPool.BLANK);

					if (newContentLanguageId.equals(StringPool.BLANK)) {
						for (int k = curDynamicContents.size() - 1; k >= 0 ;
								k--) {

							Element curContentEl =
								(Element)curDynamicContents.get(k);

							String curContentLanguageId =
								curContentEl.attributeValue(
									"language-id", StringPool.BLANK);

							if ((curEl.attributeValue("type").equals(
									"image")) &&
					            (!curContentLanguageId.equals(defaultLocale) &&
					             !curContentLanguageId.equals(
									StringPool.BLANK))) {

								ImageLocalUtil.remove(
									curContentEl.attributeValue("id"));
							}

							curContentEl.detach();
						}

						curEl.content().add(newContentEl.createCopy());
					}
					else {
				        boolean match = false;

						for (int k = curDynamicContents.size() - 1; k >= 0 ;
								k--) {

							Element curContentEl =
								(Element)curDynamicContents.get(k);

							String curContentLanguageId =
								curContentEl.attributeValue(
									"language-id", StringPool.BLANK);

					        if ((newContentLanguageId.equals(
									curContentLanguageId)) ||
						        (newContentLanguageId.equals(defaultLocale) &&
					             curContentLanguageId.equals(
									StringPool.BLANK))) {

						        curContentEl.detach();

								curEl.content().add(
									k, newContentEl.createCopy());

								match = true;
					        }

					        if (curContentLanguageId.equals(StringPool.BLANK)) {
						        curContentEl.addAttribute(
									"language-id", defaultLocale);
					        }
					    }

					    if (!match) {
						    curEl.content().add(newContentEl.createCopy());
					    }
				    }
				}
				else {
					xPathSelector = DocumentHelper.createXPath(elPath);

					Element parentEl =
						(Element)xPathSelector.selectNodes(curDoc).get(0);

					parentEl.content().add(newEl.createCopy());
				}

				String xsdElementType =
					xsdElement.attributeValue("type", StringPool.BLANK);

				if (!xsdElementType.equals("list") &&
					!xsdElementType.equals("multi-list")) {

					path.push(localPath);

					_merge(path, curDoc, newDoc, xsdElement, defaultLocale);

					path.pop();
				}
			}
		}
	}

	private static final Log _log = LogFactory.getLog(JournalUtil.class);

}