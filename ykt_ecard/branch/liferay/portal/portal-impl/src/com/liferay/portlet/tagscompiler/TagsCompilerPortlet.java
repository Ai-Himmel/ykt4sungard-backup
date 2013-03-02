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

package com.liferay.portlet.tagscompiler;

import com.liferay.portal.kernel.portlet.LiferayPortlet;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.RenderParametersPool;
import com.liferay.portlet.tagscompiler.util.TagsCompilerSessionUtil;

import java.io.IOException;

import java.util.Collection;

import javax.portlet.PortletException;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="TagsCompilerPortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsCompilerPortlet extends LiferayPortlet {

	public void render(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		// Compile entries

		String entriesFromURL = ParamUtil.getString(req, "entries");
		String[] entriesFromURLArray = StringUtil.split(entriesFromURL);

		if (_log.isDebugEnabled()) {
			_log.debug("Entries from friendly URL " + entriesFromURL);
		}

		Collection entriesFromSession = TagsCompilerSessionUtil.getEntries(req);
		String[] entriesFromSessionArray =
			(String[])entriesFromSession.toArray(new String[0]);

		if (_log.isDebugEnabled()) {
			_log.debug(
				"Entries from session " +
					StringUtil.merge(entriesFromSessionArray));
		}

		String[] entries = ArrayUtil.append(
			entriesFromURLArray, entriesFromSessionArray);

		req.setAttribute(WebKeys.TAGS_COMPILER_ENTRIES, entries);

		// Clear render parameters cache

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
			WebKeys.THEME_DISPLAY);

		RenderParametersPool.clear(
			httpReq, themeDisplay.getPlid(), PortletKeys.TAGS_COMPILER);
	}

	private static Log _log = LogFactory.getLog(TagsCompilerPortlet.class);

}