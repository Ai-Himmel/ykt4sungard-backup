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

package com.liferay.portlet.news.util;

import com.liferay.portal.kernel.webcache.WebCacheException;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portlet.news.model.Article;
import com.liferay.portlet.news.model.News;
import com.liferay.util.Http;
import com.liferay.util.Time;

import java.io.ByteArrayInputStream;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="NewsWebCacheItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class NewsWebCacheItem implements WebCacheItem {

	public Object convert(String text) throws WebCacheException {
		try {
			int pos = text.indexOf(";");

			String categoryName = text.substring(0, pos);
			String feedURL = text.substring(pos + 1, text.length());
			String xml = Http.URLtoString(
				"http://p.moreover.com/cgi-local/page?" + feedURL + "&o=xml");

			ByteArrayInputStream bais =
				new ByteArrayInputStream(xml.getBytes());

			Document doc = new SAXReader().read(bais);

			ArrayList list = new ArrayList();

			DateFormat df = new SimpleDateFormat("MMM d yyyy K:mma z");

			Element root = doc.getRootElement();

			List articles = root.elements("article");
			Iterator i = articles.iterator();

			while (i.hasNext()) {
				Element article = (Element)i.next();

				String harvestTime =
					article.element("harvest_time").getTextTrim() + " GMT";

				list.add(new Article(
					article.element("headline_text").getTextTrim(),
					article.element("url").getTextTrim(),
					article.element("source").getTextTrim(),
					article.element("document_url").getTextTrim(),
					article.element("access_status").getTextTrim(),
					article.element("access_registration").getTextTrim(),
					df.parse(harvestTime)));
			}

			return new News(feedURL, categoryName, list);
		}
		catch (Exception e) {
			throw new WebCacheException(e);
		}
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.MINUTE * 20;

}