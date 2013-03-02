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

package com.liferay.portlet.wiki.util;

import com.efsol.friki.ClassicToHTMLFilter;

import java.util.Map;

import javax.portlet.PortletURL;

import org.stringtree.factory.Fetcher;
import org.stringtree.factory.TractFetcher;

/**
 * <a href="NodeFilter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class NodeFilter extends ClassicToHTMLFilter {

	public NodeFilter(Fetcher context, TractFetcher pages, Map remoteNames,
					  String spec, NodeRepository nodeRepository,
					  PortletURL portletURL, long nodeId) {

		super(context, pages, remoteNames, spec);

		_nodeRepository = nodeRepository;
		_portletURL = portletURL;
		_nodeId = nodeId;
	}

	public Map getTitles() {
		return _nodeRepository.getTitles();
	}

	public PortletURL getPortletURL() {
		return _portletURL;
	}

	public long getNodeId() {
		return _nodeId;
	}

	private NodeRepository _nodeRepository;
	private PortletURL _portletURL;
	private long _nodeId;

}