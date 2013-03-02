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

import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.service.spring.JournalArticleServiceUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.Html;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import java.io.StringReader;

import java.util.Iterator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="ContentTransformerListener.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class ContentTransformerListener extends TransformerListener {

	public String onXml(String s) {
		_log.debug("onXml");

		s = replaceContent(s);

		return s;
	}

	public String onXsl(String s) {
		_log.debug("onXsl");

		return s;
	}

	public String onOutput(String s) {
		_log.debug("onOutput");

		return s;
	}

	/**
	 * Fill one article with content from another approved article. See the
	 * article DOCUMENTATION-INSTALLATION-BORLAND for a sample use case.
	 *
     * @param		s the given string
     * @return		the processed string
	 */
	protected String replaceContent(String xml) {
		try {
			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(xml));

			Element root = doc.getRootElement();

			replaceContent(root);

			xml = JournalUtil.formatXML(doc);
		}
		catch (Exception e) {
			_log.error(e);
		}

		return xml;
	}

	protected void replaceContent(Element root) throws Exception {
		Iterator itr = root.elements().iterator();

		while (itr.hasNext()) {
			Element el = (Element)itr.next();

			Element dynamicContent = el.element("dynamic-content");

			if (dynamicContent != null) {
				String text = dynamicContent.getText();

				text = Html.stripComments(text);
				text = Html.stripHtml(text);
				text = text.trim();

				// [@articleId;elementName@]

				if (Validator.isNotNull(text) && text.length() >= 7 &&
					text.startsWith("[@") && text.endsWith("@]")) {

					text = text.substring(2, text.length() - 2);

					int pos = text.indexOf(";");

					if (pos != -1) {
						String articleId = text.substring(0, pos);
						String elementName =
							text.substring(pos + 1, text.length());

						JournalArticle article =
							JournalArticleServiceUtil.getArticle(articleId);

						dynamicContent.setText(StringPool.BLANK);
						dynamicContent.addCDATA(
							_getDynamicContent(
								article.getContent(), elementName));
					}
				}

				// Make sure to point images to the full path

				else if ((text != null) &&
						 (text.startsWith("/image/journal/article?img_id"))) {

					dynamicContent.setText("@root_path@" + text);
				}
			}

			replaceContent(el);
		}
	}

	private String _getDynamicContent(String xml, String elementName) {
		String content = null;

		try {
			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(xml));

			Element root = doc.getRootElement();

			Iterator itr = root.elements().iterator();

			while (itr.hasNext()) {
				Element el = (Element)itr.next();

				String elName = el.attributeValue("name", StringPool.BLANK);

				if (elName.equals(elementName)) {
					content = el.elementText("dynamic-content");

					break;
				}
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		return GetterUtil.getString(content);
	}

	private static final Log _log =
		LogFactory.getLog(ContentTransformerListener.class);

}