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

import com.liferay.portal.util.WebCachePool;
import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.news.model.Feed;
import com.liferay.portlet.news.model.News;
import com.liferay.util.CollectionFactory;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.portlet.PortletPreferences;

/**
 * <a href="NewsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class NewsUtil {

	public static Map getCategoryMap() {
		return _instance._categoryMap;
	}

	public static Set getCategorySet() {
		return _instance._categorySet;
	}

	public static Map getFeedMap() {
		return _instance._feedMap;
	}

	public static Set getFeedSet() {
		return _instance._feedSet;
	}

	public static News getNews(String xml) {
		Feed feed = (Feed)NewsUtil.getFeedMap().get(xml);

		WebCacheable wc = new NewsConverter();

		return (News)WebCachePool.get(feed.getShortName() + ";" + xml, wc);
	}

	public static List getNews(PortletPreferences prefs) {
		List news = new ArrayList();

		Iterator itr = NewsUtil.getSelFeeds(prefs).iterator();

		while (itr.hasNext()) {
			Feed feed = (Feed)itr.next();

			news.add(NewsUtil.getNews(feed.getFeedURL()));
		}

		return news;
	}

	public static Map getSelCategories(Set selFeeds) {
		Map selCategories = CollectionFactory.getHashMap();

		Iterator itr = selFeeds.iterator();

		while (itr.hasNext()) {
			Feed feed = (Feed)itr.next();

			String categoryName = feed.getCategoryName();

			if (selCategories.containsKey(categoryName)) {
				List feedList = (List)selCategories.get(categoryName);

				feedList.add(feed);
			}
			else {
				List feedList = new ArrayList();

				feedList.add(feed);

				selCategories.put(categoryName, feedList);
			}
		}

		return selCategories;
	}

	public static Set getSelFeeds(PortletPreferences prefs) {
		Map feedMap = getFeedMap();

		Set selFeeds = new LinkedHashSet();

		String[] selFeedsArray = prefs.getValues("sel-feeds", new String[0]);

		for (int i = 0; i < selFeedsArray.length; i++) {
			Feed feed = (Feed)feedMap.get(selFeedsArray[i]);

			selFeeds.add(feed);
		}

		return selFeeds;
	}

	public static String[] getSelFeeds(Set selFeeds) {
		List list = new ArrayList();

		Iterator itr = selFeeds.iterator();

		while (itr.hasNext()) {
			Feed feed = (Feed)itr.next();

			list.add(feed.getFeedURL());
		}

		return (String[])list.toArray(new String[0]);
	}

	private NewsUtil() {
		try {
			WebCacheable wc = new CategoryConverter();

			List list = (List)WebCachePool.get(
				"http://w.moreover.com/categories/category_list.tsv2", wc);

			_categoryMap = (Map)list.get(0);
			_categorySet = (Set)list.get(1);
			_feedMap = (Map)list.get(2);
			_feedSet = (Set)list.get(3);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	private static NewsUtil _instance = new NewsUtil();

	private Map _categoryMap;
	private Set _categorySet;
	private Map _feedMap;
	private Set _feedSet;

}