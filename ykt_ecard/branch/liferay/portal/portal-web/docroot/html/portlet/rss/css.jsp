<%
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
%>

<%@ include file="/html/portlet/css_init.jsp" %>

.portlet-rss .feed-date {
	background: url(<%= themeImagesPath %>/common/time.png) no-repeat 0 50%;
	margin: 0.3em 0;
	padding-left: 20px;
}

.portlet-rss .feed-description {
 	margin: 0 0 5px 0;
}

.portlet-rss .feed-entries {
	font-size: 1.1em;
}

.portlet-rss .feed-entry {
	margin-bottom: 4px;
}

.portlet-rss .feed-entry-author {
	display: block;
	font-size: 0.9em;
}

.portlet-rss .feed-entry-content {
	padding-left: 1.8em;
}

.portlet-rss .feed-entry-content img {
	margin-right: 0.5em;
}

.portlet-rss .feed-entry-expander {
	cursor: pointer;
	float: left;
	padding-right: 5px;
}

.portlet-rss .feed-entry-title {
	display: block;
	font-weight: bold;
}

.portlet-rss .feed-image-left {
 	margin: 4px 0 4px 20px;
 	text-align: left;
}

.portlet-rss .feed-image-right {
	float: right;
 	margin: 0 0 4px 4px;
}

.portlet-rss .feed-published-date.feed-date {
	background-image: url(<%= themeImagesPath %>/common/date.png)
}

.portlet-rss .feed-published-date a {
	font-weight: bold;
	text-decoration: none;
}

.portlet-rss .feed-title {
	font-size: 1.2em;
	font-weight: bold;
	margin: 0 0 0.5em -20px;
}

.portlet-rss .feed-title a {
	background: url(<%= themeImagesPath %>/common/news.png) no-repeat 0 50%;
	padding-left: 20px;
}

.portlet-rss .feed {
	padding-left: 20px;
}

.portlet-rss .feed .separator {
	margin-left: -20px;
}