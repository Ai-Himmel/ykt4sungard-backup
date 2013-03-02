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

package com.liferay.portlet.news.util;

import com.liferay.portal.util.ContentUtil;
import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.news.model.Feed;
import com.liferay.util.CollectionFactory;
import com.liferay.util.ConverterException;
import com.liferay.util.Http;
import com.liferay.util.Time;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

/**
 * <a href="CategoryConverter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class CategoryConverter implements WebCacheable {

	public Object convert(String url) throws ConverterException {
		try {
			Map categoryMap = CollectionFactory.getHashMap();
			Set categorySet = new TreeSet();
			Map feedMap = CollectionFactory.getHashMap();
			Set feedSet = new TreeSet();

			String xml = null;

			try {
				xml = Http.URLtoString(url);
			}
			catch (IOException ioe) {
				xml = ContentUtil.get("content/common/news.tsv");
			}

			BufferedReader br = new BufferedReader(new StringReader(xml));

			String s = null;

			while ((s = br.readLine()) != null) {
				String feedURL;
				String fullName;
				String shortName;
				String categoryName;

				int pos;

				pos = s.indexOf("\t");
				feedURL = s.substring(0, pos);

				s = s.substring(pos + 1, s.length());
				pos = s.indexOf("\t");
				fullName = s.substring(0, pos);

				s = s.substring(pos + 1, s.length());
				pos = s.indexOf("\t");
				shortName = s.substring(0, pos);

				categoryName = s.substring(pos + 1, s.length());

				Feed feed =
					new Feed(feedURL, fullName, shortName, categoryName);

				categorySet.add(feed.getCategoryName());
				feedMap.put(feedURL, feed);
				feedSet.add(feed);
			}

			categoryMap = CollectionFactory.getHashMap();

			String temp = "";
			Set tempSet = null;

			Iterator i = feedSet.iterator();

			while (i.hasNext()) {
				Feed feed = (Feed)i.next();

				if (temp.equals(feed.getCategoryName())) {
					tempSet.add(feed);
				}
				else {
					tempSet = new TreeSet();
					categoryMap.put(feed.getCategoryName(), tempSet);
					tempSet.add(feed);
				}

				temp = feed.getCategoryName();
			}

			categoryMap = Collections.unmodifiableMap(categoryMap);
			categorySet = Collections.unmodifiableSet(categorySet);

			feedMap = Collections.unmodifiableMap(feedMap);
			feedSet = Collections.unmodifiableSet(feedSet);

			List list = new ArrayList();
			list.add(categoryMap);
			list.add(categorySet);
			list.add(feedMap);
			list.add(feedSet);

			return list;
		}
		catch (Exception e) {
			throw new ConverterException(e);
		}
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.DAY * 3;

}