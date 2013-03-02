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

package com.liferay.portal.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.LayoutLocalServiceUtil;

import java.util.Iterator;
import java.util.List;
import java.util.Properties;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

/**
 * <a href="SitemapUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class SitemapUtil {

	public static String getSitemap(
			long groupId, boolean privateLayout, String urlPrefix)
		throws PortalException, SystemException {

		List layouts = LayoutLocalServiceUtil.getLayouts(
			groupId, privateLayout);

		return getSitemap(layouts, urlPrefix);
	}

	public static String getSitemap(List layouts, String urlPrefix)
		throws PortalException, SystemException {

		Document doc = DocumentHelper.createDocument();

		doc.setXMLEncoding("UTF-8");

		Element root = doc.addElement(
			"urlset", "http://www.google.com/schemas/sitemap/0.84");

		_visitLayouts(root, layouts, urlPrefix);

		return doc.asXML();
	}

	public static String encodeXML(String input){
		return StringUtil.replace(
			input,
			new String[] {"&", "<", ">", "'", "\""},
			new String[] {"&amp;", "&lt;", "&gt;", "&apos;", "&quot;"});
	}

	private static void _visitLayouts(
			Element element, List layouts, String urlPrefix)
		throws PortalException, SystemException {

		Iterator itr = layouts.iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			Properties props = layout.getTypeSettingsProperties();

			if (PortalUtil.isLayoutSitemapable(layout) && !layout.isHidden() &&
				GetterUtil.getBoolean(
					props.getProperty("sitemap-include"), true)) {

				Element url = element.addElement("url");

				String layoutURL = PortalUtil.getLayoutActualURL(
					layout, urlPrefix);

				url.addElement("loc").addText(encodeXML(layoutURL));

				String changefreq = props.getProperty("sitemap-changefreq");

				if (Validator.isNotNull(changefreq)) {
					url.addElement("changefreq").addText(changefreq);
				}

				String priority = props.getProperty("sitemap-priority");

				if (Validator.isNotNull(priority)) {
					url.addElement("priority").addText(priority);
				}

				List children = layout.getChildren();

				_visitLayouts(element, children, urlPrefix);
			}
		}
	}

}