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

package com.liferay.portlet.layoutconfiguration.util.velocity;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.portal.util.comparator.PortletRenderWeightComparator;
import com.liferay.portlet.layoutconfiguration.util.RuntimePortletUtil;

import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortletColumnLogic.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ivica Cardic
 * @author Brian Wing Shun Chan
 *
 */
public class PortletColumnLogic extends RuntimeLogic {

	public PortletColumnLogic(
		ServletContext ctx, HttpServletRequest req, HttpServletResponse res) {

		_ctx = ctx;
		_req = req;
		_res = res;
		_themeDisplay = (ThemeDisplay)_req.getAttribute(WebKeys.THEME_DISPLAY);
		_portletsMap = new TreeMap(new PortletRenderWeightComparator());

		_parallelRenderEnable = PropsValues.LAYOUT_PARALLEL_RENDER_ENABLE;

		if (_parallelRenderEnable) {
			if (PropsValues.SESSION_DISABLED) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"Parallel rendering should be disabled if sessions " +
							"are disabled");
				}
			}
		}

		if (_parallelRenderEnable) {
			Boolean portletParallelRender =
				(Boolean)req.getAttribute(WebKeys.PORTLET_PARALLEL_RENDER);

			if ((portletParallelRender != null) &&
				(portletParallelRender.booleanValue() == false)) {

				_parallelRenderEnable = false;
			}
		}
		else {
			req.removeAttribute(WebKeys.PORTLET_PARALLEL_RENDER);
		}
	}

	public void processContent(StringMaker sm, Map attributes)
		throws Exception {

		LayoutTypePortlet layoutTypePortlet =
			_themeDisplay.getLayoutTypePortlet();

		String columnId = (String)attributes.get("id");

		List portlets = layoutTypePortlet.getAllPortlets(columnId);

		String columnCssClass = "lfr-portlet-column";

		if (portlets.size() == 0) {
			columnCssClass += " empty";
		}

		sm.append("<div class=\"");
		sm.append(columnCssClass);
		sm.append("\" id=\"layout-column_");
		sm.append(columnId);
		sm.append("\">");

		for (int i = 0; i < portlets.size(); i++) {
			Portlet portlet = (Portlet)portlets.get(i);

			String queryString = null;
			Integer columnPos = new Integer(i);
			Integer columnCount = new Integer(portlets.size());
			String path = null;

			if (_parallelRenderEnable) {
				path = "/html/portal/load_render_portlet.jsp";

				if (portlet.getRenderWeight() >= 1) {
					_portletsMap.put(
						portlet,
						new Object[] {
							queryString, columnId, columnPos, columnCount
						});
				}
			}

			RuntimePortletUtil.processPortlet(
				sm, _ctx, _req, _res, portlet, queryString, columnId, columnPos,
				columnCount, path);
		}

		sm.append("</div>");
	}

	public Map getPortletsMap() {
		return _portletsMap;
	}

	private static Log _log = LogFactory.getLog(PortletColumnLogic.class);

	private ServletContext _ctx;
	private HttpServletRequest _req;
	private HttpServletResponse _res;
	private ThemeDisplay _themeDisplay;
	private Map _portletsMap;
	private boolean _parallelRenderEnable;

}