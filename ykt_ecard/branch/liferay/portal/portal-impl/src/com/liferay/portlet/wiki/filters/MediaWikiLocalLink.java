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

package com.liferay.portlet.wiki.filters;

import org.stringtree.factory.AbstractStringFetcher;
import org.stringtree.factory.Container;
import org.stringtree.factory.Fetcher;
import org.stringtree.juicer.Initialisable;
import org.stringtree.regex.Matcher;
import org.stringtree.regex.Pattern;

/**
 * <a href="MediaWikiLocalLink.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class MediaWikiLocalLink
	extends AbstractStringFetcher implements Initialisable {

	public MediaWikiLocalLink() {
		this(null);
	}

	public MediaWikiLocalLink(Container pages) {
		_pages = pages;
	}

	public void init(Fetcher context) {
		_pages = (Container)context.getObject("wiki.pages");
	}

	public Object getObject(String key) {
		String value = key;

		Matcher match = _pattern.matcher(key);

		if (match.find()) {
			key = encodeKey(match.group(3).trim());

			String title = match.group(6).trim();

			if (_pages.contains(key)) {
				value = "\nview_mw{" + title + "," + key + "}\n";
			}
			else{
				value = "\nedit_mw{" + title + "," + key + "}\n";
			}
		}

		return value;
	}

	protected String encodeKey(String key) {
		return key.replaceAll("\\W", "_");
	}

	private static final Pattern _pattern = Pattern.compile(
		"(^|\\p{Punct}|\\p{Space})(\\[\\s*(((\\p{Lu}\\p{Ll}+)\\s?)+)\\s*\\|\\s*((([\\p{Alpha}\\p{Digit}]+)\\s?)+)\\s*\\])(\\z|\\n|\\p{Punct}|\\p{Space})");

	private Container _pages;

}