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

package com.liferay.portlet.tagscompiler.util;

import com.liferay.portal.util.WebKeys;

import java.util.Collection;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import javax.portlet.PortletRequest;
import javax.portlet.PortletSession;

/**
 * <a href="TagsCompilerSessionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsCompilerSessionUtil {

	public static void addEntries(PortletRequest req, List entries) {
		Set entriesSet = _getEntriesSet(req);

		entriesSet.addAll(entries);
	}

	public static void addEntry(PortletRequest req, String entry) {
		Set entriesSet = _getEntriesSet(req);

		entriesSet.add(entry);
	}

	public static void clearEntries(PortletRequest req) {
		Set entriesSet = _getEntriesSet(req);

		entriesSet.clear();
	}

	public static Collection getEntries(PortletRequest req) {
		Set entriesSet = _getEntriesSet(req);

		return entriesSet;
	}

	public static void removeEntries(PortletRequest req, List entries) {
		Set entriesSet = _getEntriesSet(req);

		entriesSet.removeAll(entries);
	}

	public static void setEntries(PortletRequest req, List entries) {
		Set entriesSet = _getEntriesSet(req);

		entriesSet.clear();

		entriesSet.addAll(entries);
	}

	private static Set _getEntriesSet(PortletRequest req) {
		PortletSession ses = req.getPortletSession();

		Set entriesSet = (Set)ses.getAttribute(
			WebKeys.TAGS_COMPILER_ENTRIES, PortletSession.APPLICATION_SCOPE);

		if (entriesSet == null) {
			entriesSet = new TreeSet();

			ses.setAttribute(
				WebKeys.TAGS_COMPILER_ENTRIES, entriesSet,
				PortletSession.APPLICATION_SCOPE);
		}

		return entriesSet;
	}

}