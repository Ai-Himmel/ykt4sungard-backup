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

package com.liferay.portlet.rss.util;

import com.liferay.portal.util.WebCacheable;
import com.liferay.util.ConverterException;
import com.liferay.util.Time;

import de.nava.informa.core.ChannelIF;
import de.nava.informa.impl.basic.ChannelBuilder;
import de.nava.informa.parsers.FeedParser;

import java.net.URL;

/**
 * <a href="RSSConverter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.10 $
 *
 */
public class RSSConverter implements WebCacheable {

	public RSSConverter(String url) {
		_url = url;
	}

	public Object convert(String id) throws ConverterException {
		ChannelIF channel = null;

		try {
			ChannelBuilder builder = new ChannelBuilder();

			// com.liferay.util.Http will break the connection if it spends
			// more than 5 seconds looking up a location. However, German
			// umlauts do not get encoded correctly. This may be a bug with
			// commons-httpclient or with how FeedParser uses java.io.Reader.

			// Use http://xml.newsisfree.com/feeds/29/629.xml and
			// http://test.domosoft.com/up/RSS to test if German umlauts show
			// up correctly.

			/*Reader reader = new StringReader(
				new String(Http.URLtoByteArray(_url)));

			channel = FeedParser.parse(builder, reader);*/

			channel = FeedParser.parse(builder, new URL(_url));
		}
		catch (Exception e) {
			throw new ConverterException(_url + " " + e.toString());
		}

		return channel;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.MINUTE * 20;

	private String _url;

}