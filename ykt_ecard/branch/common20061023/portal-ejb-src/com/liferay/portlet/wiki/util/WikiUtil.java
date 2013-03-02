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

package com.liferay.portlet.wiki.util;

import com.efsol.friki.PageRepository;

import com.liferay.portlet.PortletURLImpl;
import com.liferay.util.Http;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;

import java.io.IOException;
import java.io.StringReader;
import java.io.StringWriter;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.StringTokenizer;

import javax.portlet.PortletURL;

import org.stringtree.factory.memory.MapStringRepository;

/**
 * <a href="WikiUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class WikiUtil {

	public static String convert(NodeFilter filter, String content)
		throws IOException {

		return _instance._convert(filter, content);
	}

	public static NodeFilter getFilter(String nodeId) {
		return _instance._getFilter(null, nodeId);
	}

	public static NodeFilter getFilter(PortletURL portletURL, String nodeId) {
		return _instance._getFilter(portletURL, nodeId);
	}

	private WikiUtil() {
		try {
			ClassLoader classLoader = getClass().getClassLoader();

			_spec = Http.URLtoString(classLoader.getResource("wiki.transform"));
			_remoteNames = _buildRemoteNamesMap(Http.URLtoString(
				classLoader.getResource("intermap.txt")));
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	private Map _buildRemoteNamesMap(String names) {
		Map remoteNames = new HashMap();

		StringTokenizer st = new StringTokenizer(names, "\n");

		while (st.hasMoreTokens()) {
			String line = st.nextToken().trim();

			int sep = line.indexOf(StringPool.SPACE);

			if (sep > 0) {
				String name = line.substring(0, sep);
				String url = line.substring(sep + 1);

				remoteNames.put(name, url);
			}
		}

		return remoteNames;
	}

	private String _convert(NodeFilter filter, String content)
		throws IOException {

		if (content == null) {
			return StringPool.BLANK;
		}

		StringWriter out = new StringWriter();

		filter.filter(new StringReader(content), out);

		String newContent = out.toString();

		String portletURLToString = StringPool.BLANK;

		PortletURLImpl portletURL = (PortletURLImpl)filter.getPortletURL();

		if (portletURL != null) {
			portletURL.setParameter("node_id", filter.getNodeId());

			Iterator itr = filter.getTitles().keySet().iterator();

			while (itr.hasNext()) {
				String title = (String)itr.next();

				portletURL.setParameter("page_title", title, false);

				portletURLToString = portletURL.toString();

				newContent = StringUtil.replace(
					newContent,
					"[$BEGIN_PAGE_TITLE$]" + title + "[$END_PAGE_TITLE$]",
					portletURLToString);
			}
		}

		return newContent;
	}

	private NodeFilter _getFilter(PortletURL portletURL, String nodeId) {
		MapStringRepository context = new MapStringRepository();
		NodeRepository nodeRepository = new NodeRepository(nodeId);
		PageRepository pageRepository = new PageRepository(nodeRepository);

		NodeFilter filter = new NodeFilter(
			context, pageRepository, _remoteNames, _spec, nodeRepository,
			portletURL, nodeId);

		return filter;
	}

	private static WikiUtil _instance = new WikiUtil();

	private String _spec;
	private Map _remoteNames;

}