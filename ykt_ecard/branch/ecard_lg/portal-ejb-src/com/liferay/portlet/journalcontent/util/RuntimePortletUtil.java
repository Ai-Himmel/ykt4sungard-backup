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

package com.liferay.portlet.journalcontent.util;

import com.liferay.portal.model.Portlet;
import com.liferay.portal.service.spring.PortletServiceUtil;
import com.liferay.portal.theme.PortletDisplay;
import com.liferay.portal.theme.PortletDisplayFactory;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import java.io.StringReader;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="RuntimePortletUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Raymond Auge
 * @version $Revision: 1.7 $
 *
 */
public class RuntimePortletUtil {

	public static final String RUNTIME_PORTLET_OPEN = "<runtime-portlet";

	public static final String RUNTIME_PORTLET_CLOSE_1 = "</runtime-portlet>";

	public static final String RUNTIME_PORTLET_CLOSE_2 = "/>";

	public static void processContent(
			ServletContext ctx, HttpServletRequest req, HttpServletResponse res,
			PageContext pageContext, RenderRequest renderRequest,
			RenderResponse renderResponse, String content,
			ThemeDisplay themeDisplay)
		throws Exception {

		if (Validator.isNull(content)) {
			return;
		}

		// Get current portlet config

		PortletConfig portletConfig =
			(PortletConfig)req.getAttribute(WebKeys.JAVAX_PORTLET_CONFIG);

		// Clone portlet display

		PortletDisplay portletDisplay = themeDisplay.getPortletDisplay();

		PortletDisplay portletDisplayClone =
			(PortletDisplay)portletDisplay.clone();

		// Process content

		JspWriter out = pageContext.getOut();

		int x = 0;
		int y = content.indexOf(RUNTIME_PORTLET_OPEN);

		try {
			while (y != -1) {
				out.print(content.substring(x, y));

				// The XSL template engine may or may not close the
				// runtime-portlet tag that the user inputs. The processor must
				// be prepared to deal with both scenarios.

				// <runtime-portlet name="19" width="200"></runtime-portlet>
				// <runtime-portlet name="19" width="200"/>

				int close1 = content.indexOf(RUNTIME_PORTLET_CLOSE_1, y);
				int close2 = content.indexOf(RUNTIME_PORTLET_CLOSE_2, y);

				if ((close2 == -1) || ((close1 != -1) && (close1 < close2))) {
					x = close1 + RUNTIME_PORTLET_CLOSE_1.length();
				}
				else {
					x = close2 + RUNTIME_PORTLET_CLOSE_2.length();
				}

				String runtimePortlet = content.substring(y, x);

				_log.debug("Parsing [" + runtimePortlet + "]");

				SAXReader reader = new SAXReader();

				Document doc = reader.read(new StringReader(runtimePortlet));

				Element root = doc.getRootElement();

				String portletId = root.attributeValue("name");
				String instanceId = root.attributeValue("instance");
				String width = root.attributeValue("width");

				// For now, do not nest other Journal Content or Portlet
				// Aggregator portlets

				if (!portletId.startsWith(PortletKeys.JOURNAL_CONTENT_NARROW) &&
					!portletId.startsWith(PortletKeys.JOURNAL_CONTENT_WIDE) &&
					!portletId.startsWith(
						PortletKeys.PORTLET_AGGREGATOR_NARROW) &&
					!portletId.startsWith(
						PortletKeys.PORTLET_AGGREGATOR_WIDE)) {

					Portlet portlet = PortletServiceUtil.getPortletById(
						themeDisplay.getCompanyId(), portletId);

					// If the portlet is instanceable, it must have a valid
					// instance id

					if (portlet.isInstanceable()) {
						if (Validator.isNotNull(instanceId) &&
							Validator.isPassword(instanceId) &&
							(instanceId.length() == 4)) {

							portletId +=
								Portlet.INSTANCE_SEPARATOR + instanceId;

							portlet = PortletServiceUtil.getPortletById(
								themeDisplay.getCompanyId(), portletId);
						}
						else {
							_log.debug(
								"Portlet " + portlet.getPortletId() +
									" is instanceable but does not have a " +
										"valid instance id");

							portlet = null;
						}
					}

					// Render the portlet if and only if it is not null

					if (portlet != null) {
						String curColumnOrder = StringPool.BLANK;
						int curColumnPos = 0;
						int curColumnCount = 0;

						PortalUtil.renderPortlet(
							ctx, req, res, pageContext, portlet,
							new Integer(width), curColumnOrder,
							new Integer(curColumnPos),
							new Integer(curColumnCount));
					}
				}

				_defineObjects(
					req, portletConfig, renderRequest, renderResponse);

				y = content.indexOf(RUNTIME_PORTLET_OPEN, x);
			}
		}
		finally {

			// Copy portlet display and recycle the clone

			portletDisplay.copyFrom(portletDisplayClone);

			try {
				PortletDisplayFactory.recycle(portletDisplayClone);
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		if (y == -1) {
			out.print(content.substring(x, content.length()));
		}
	}

	private static void _defineObjects(
		HttpServletRequest req, PortletConfig portletConfig,
		RenderRequest renderRequest, RenderResponse renderResponse) {

		req.setAttribute(WebKeys.JAVAX_PORTLET_CONFIG, portletConfig);
		req.setAttribute(WebKeys.JAVAX_PORTLET_REQUEST, renderRequest);
		req.setAttribute(WebKeys.JAVAX_PORTLET_RESPONSE, renderResponse);
	}

	private static final Log _log = LogFactory.getLog(RuntimePortletUtil.class);

}