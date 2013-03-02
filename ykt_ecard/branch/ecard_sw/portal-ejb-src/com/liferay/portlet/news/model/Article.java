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

import java.util.Date;

/**
 * <a href="Article.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class Article implements Serializable {

	public Article(String headline, String headlineURL,
				   String source, String sourceURL,
				   String accessStatus, String accessURL,
				   Date date) {
		_headline = headline;
		_headlineURL = headlineURL;
		_source = source;
		_sourceURL = sourceURL;
		_accessStatus = accessStatus;
		_accessURL = accessURL;
		_date = date;
	}

	public String getHeadline() {
		return _headline;
	}

	public String getHeadlineURL() {
		return _headlineURL;
	}

	public String getSource() {
		return _source;
	}

	public String getSourceURL() {
		return _sourceURL;
	}

	public String getAccessStatus() {
		return _accessStatus;
	}

	public String getAccessURL() {
		return _accessURL;
	}

	public Date getDate() {
		return _date;
	}

	private String _headline;
	private String _headlineURL;
	private String _source;
	private String _sourceURL;
	private String _accessStatus;
	private String _accessURL;
	private Date _date;

}