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

package com.liferay.portal.servlet.taglib.portlet;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.HttpUtil;

import java.util.StringTokenizer;

import javax.portlet.PortletURL;

import javax.servlet.jsp.JspException;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="RenderURLParamsTagUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RenderURLParamsTagUtil {

	public static String doEndTag(String varImpl, PageContext pageContext)
		throws JspException {

		try {
			PortletURL portletURL =
				(PortletURL)pageContext.getAttribute(varImpl);

			String params = StringPool.BLANK;

			if (portletURL != null) {
				params = _toParamsString(portletURL);

				pageContext.getOut().print(params);
			}

			return params;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new JspException(e);
		}
	}

	private static String _toParamsString(PortletURL portletURL)
		throws Exception {

		StringMaker sm = new StringMaker();

		String url = portletURL.toString();

		String queryString = HttpUtil.getQueryString(url);

		StringTokenizer st = new StringTokenizer(
			queryString, StringPool.AMPERSAND);

		while (st.hasMoreTokens()) {
			String token = st.nextToken();

			if (Validator.isNotNull(token)) {
				String[] kvp = StringUtil.split(token, StringPool.EQUAL);

				if ((kvp != null) && (kvp.length > 0)) {
					String key = kvp[0];
					String value = StringPool.BLANK;

					if (kvp.length > 1) {
						value = kvp[1];
					}

					value = HttpUtil.decodeURL(value);

					sm.append("<input name=\"");
					sm.append(key);
					sm.append("\" type=\"hidden\" value=\"");
					sm.append(value);
					sm.append("\" />");
				}
			}
		}

		return sm.toString();
	}

	private static Log _log = LogFactory.getLog(ActionURLTagUtil.class);

}