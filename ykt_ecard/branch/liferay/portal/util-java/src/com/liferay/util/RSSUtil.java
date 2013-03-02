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

package com.liferay.util;

import com.liferay.portal.kernel.util.CharPool;

import com.sun.syndication.feed.synd.SyndContent;
import com.sun.syndication.feed.synd.SyndEntry;
import com.sun.syndication.feed.synd.SyndFeed;
import com.sun.syndication.io.FeedException;
import com.sun.syndication.io.SyndFeedOutput;

import java.io.IOException;

import java.util.List;

import org.jdom.IllegalDataException;

/**
 * <a href="RSSUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RSSUtil {

	public static final String RSS = "rss";

	public static final double[] RSS_VERSIONS = new double[] {
		0.9, 0.91, 0.93, 0.94, 1.0, 2.0
	};

	public static final String ATOM = "atom";

	public static final double[] ATOM_VERSIONS = new double[] {0.3, 1.0};

	public static final String DEFAULT_TYPE = ATOM;

	public static final double DEFAULT_VERSION = 1.0;

	public static final String DISPLAY_STYLE_ABSTRACT = "abstract";

	public static final String DISPLAY_STYLE_FULL_CONTENT = "full-content";

	public static final String DISPLAY_STYLE_TITLE = "title";

	public static String export(SyndFeed feed)
		throws FeedException, IOException {

		feed.setEncoding("UTF-8");

		SyndFeedOutput output = new SyndFeedOutput();

		try {
			return output.outputString(feed);
		}
		catch (IllegalDataException ide) {

			// LEP-4450

			_regexpStrip(feed);

			return output.outputString(feed);
		}
	}

	private static void _regexpStrip(SyndFeed feed) {
		feed.setTitle(_regexpStrip(feed.getTitle()));
		feed.setDescription(_regexpStrip(feed.getDescription()));

		List entries = feed.getEntries();

		for (int i = 0; i < entries.size(); i++) {
			SyndEntry entry = (SyndEntry)entries.get(i);

			entry.setTitle(_regexpStrip(entry.getTitle()));

			SyndContent content = entry.getDescription();

			content.setValue(_regexpStrip(content.getValue()));
		}
	}

	private static String _regexpStrip(String text) {
		text = Normalizer.normalizeToAscii(text);

		char[] array = text.toCharArray();

		for (int i = 0; i < array.length; i++) {
			String s = String.valueOf(array[i]);

			if (!s.matches(_REGEXP_STRIP)) {
				array[i] = CharPool.SPACE;
			}
		}

		return new String(array);
	}

	private static final String _REGEXP_STRIP = "[\\d\\w]";

}