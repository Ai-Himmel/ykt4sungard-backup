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

package com.liferay.portal.servlet.taglib.ui;

import com.germinus.easyconf.Filter;

import com.liferay.portal.kernel.servlet.PortalIncludeUtil;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.HttpUtil;

import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.util.FastHashMap;

/**
 * <a href="SocialBookmarkTagUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class SocialBookmarkTagUtil {

	public static void doEndTag(
			String page, String type, String url, String title, String target,
			PageContext pageContext)
		throws JspException {

		try {
			HttpServletRequest req =
				(HttpServletRequest)pageContext.getRequest();

			req.setAttribute("liferay-ui:social-bookmark:type", type);
			req.setAttribute("liferay-ui:social-bookmark:url", url);
			req.setAttribute("liferay-ui:social-bookmark:title", title);
			req.setAttribute("liferay-ui:social-bookmark:target", target);

			String[] socialTypes = PropsUtil.getArray(
				PropsUtil.SOCIAL_BOOKMARK_TYPES);

			if (!ArrayUtil.contains(socialTypes, type)) {
				return;
			}

			String postUrl = _getPostUrl(type, url, title);

			req.setAttribute("liferay-ui:social-bookmark:postUrl", postUrl);

			PortalIncludeUtil.include(pageContext, page);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new JspException(e);
		}
	}

	private static String _getPostUrl(String type, String url, String title)
		throws Exception {

		Map vars = new FastHashMap();

		vars.put("liferay:social-bookmark:url", url);
		vars.put("liferay:social-bookmark:title", HttpUtil.encodeURL(title));

		String postUrl = PropsUtil.getComponentProperties().getString(
			PropsUtil.SOCIAL_BOOKMARK_POST_URL,
			Filter.by(type).setVariables(vars));

		return postUrl;
	}

	private static Log _log = LogFactory.getLog(SocialBookmarkTagUtil.class);

}