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

package com.liferay.portlet.news.model;

import java.io.Serializable;

/**
 * <a href="Feed.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class Feed implements Comparable, Serializable {

	public Feed(String feedURL, String fullName, String shortName,
				String categoryName) {
		_feedURL = feedURL;
		_fullName = fullName;
		_shortName = shortName;
		_categoryName = categoryName;
	}

	public String getFeedURL() {
		return _feedURL;
	}

	public String getFullName() {
		return _fullName;
	}

	public String getShortName() {
		return _shortName;
	}

	public String getCategoryName() {
		return _categoryName;
	}

	public int compareTo(Object obj) {
		Feed feed = (Feed)obj;

		String categoryName = feed.getCategoryName();
		String fullName = feed.getFullName();

		if (categoryName.compareTo(_categoryName) == 0) {
			return -(fullName.compareTo(_fullName));
		}
		else if (categoryName.compareTo(_categoryName) < 0) {
			return 1;
		}
		else {
			return -1;
		}
	}

	public boolean equals(Object obj) {
		Feed feed = (Feed)obj;

		String feedURL = feed.getFeedURL();

		if (_feedURL.equals(feedURL)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return _feedURL.hashCode();
	}

	private String _feedURL;
	private String _fullName;
	private String _shortName;
	private String _categoryName;

}