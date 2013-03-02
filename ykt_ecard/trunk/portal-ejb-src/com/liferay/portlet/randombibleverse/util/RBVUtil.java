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

package com.liferay.portlet.randombibleverse.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebCachePool;
import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.randombibleverse.model.Bible;
import com.liferay.portlet.randombibleverse.model.Verse;
import com.liferay.util.StringPool;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Random;

import javax.portlet.PortletPreferences;

import javax.servlet.http.HttpServletRequest;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="RBVUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.19 $
 *
 */
public class RBVUtil {

	public static Bible getBible(PortletPreferences prefs, Locale locale) {
		return _instance._getBible(prefs, locale);
	}

	public static Map getBibles() {
		return _instance._bibles;
	}

	public static Verse getVerse(HttpServletRequest req)
		throws PortalException, SystemException {

		return getVerse(
			PortalUtil.getPreferences(req), PortalUtil.getLocale(req));
	}

	public static Verse getVerse(PortletPreferences prefs, Locale locale) {
		return _instance._getVerse(prefs, locale);
	}

	private RBVUtil() {
		Document doc = null;

		try {
			doc = new SAXReader().read(getClass().getClassLoader().getResource(
				"content/common/random_bible_verse.xml"));
		}
		catch (DocumentException de) {
			de.printStackTrace();
		}

		_bibles = new LinkedHashMap();
		_verses = new ArrayList();

		Element root = doc.getRootElement();

		Iterator itr = root.element("bibles").elements("bible").iterator();

		while (itr.hasNext()) {
			Element bible = (Element)itr.next();

			_bibles.put(
				bible.attributeValue("language"),
				new Bible(
					bible.attributeValue("language"),
					bible.attributeValue("language-name"),
					bible.attributeValue("version-id")));
		}

		_bibles = Collections.unmodifiableMap(_bibles);

		itr = root.element("verses").elements("verse").iterator();

		while (itr.hasNext()) {
			Element verse = (Element)itr.next();

			_verses.add(verse.attributeValue("location"));
		}

		_verses = Collections.unmodifiableList(_verses);
	}

	private Bible _getBible(PortletPreferences prefs, Locale locale) {
		Bible bible = (Bible)_bibles.get(
			prefs.getValue("language", StringPool.BLANK));

		if (bible == null) {
			bible = (Bible)_bibles.get(locale.getLanguage());
		}

		if (bible == null) {
			bible = (Bible)_bibles.get("en");
		}

		return bible;
	}

	private Verse _getVerse(PortletPreferences prefs, Locale locale) {
		Bible bible = _getBible(prefs, locale);

		Random random = new Random();
		int i = random.nextInt(_verses.size());

		return _getVerse((String)_verses.get(i), bible.getVersionId());
	}

	private Verse _getVerse(String location, String versionId) {
		WebCacheable wc = new VerseConverter(location, versionId);

		return (Verse)WebCachePool.get(
			RBVUtil.class.getName() + StringPool.PERIOD + location +
				StringPool.PERIOD + versionId,
			wc);
	}

	private static RBVUtil _instance = new RBVUtil();

	private Map _bibles;
	private List _verses;

}