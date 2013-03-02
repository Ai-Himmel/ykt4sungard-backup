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

<%@ include file="/html/portal/init.jsp" %>

<%
Portlet portlet = (Portlet)request.getAttribute(WebKeys.RENDER_PORTLET);

String columnId = (String)request.getAttribute(WebKeys.RENDER_PORTLET_COLUMN_ID);
Integer columnPos = (Integer)request.getAttribute(WebKeys.RENDER_PORTLET_COLUMN_POS);
Integer columnCount = (Integer)request.getAttribute(WebKeys.RENDER_PORTLET_COLUMN_COUNT);

String currentURL = PortalUtil.getCurrentURL(request);
%>

<c:choose>
	<c:when test="<%= portlet.getRenderWeight() >= 1 %>">
		[$TEMPLATE_PORTLET_<%= portlet.getPortletId() %>$]
	</c:when>
	<c:otherwise>

		<%
		portletDisplay.setId(portlet.getPortletId());
		portletDisplay.setNamespace(PortalUtil.getPortletNamespace(portlet.getPortletId()));
		%>

		<div class="loading-animation" id="p_load<%= portletDisplay.getNamespace() %>"></div>

		<%
		String doAsUserId = themeDisplay.getDoAsUserId();

		StringMaker url = new StringMaker();

		url.append(themeDisplay.getPathMain());
		url.append("/portal/render_portlet");
		url.append("?p_l_id=");
		url.append(plid.longValue());
		url.append("&p_p_id=");
		url.append(portlet.getPortletId());
		url.append("&p_p_action=0&p_p_state=normal&p_p_mode=view&p_p_col_id=");
		url.append(columnId);
		url.append("&p_p_col_pos=");
		url.append(columnPos);
		url.append("&p_p_col_count=");
		url.append(columnCount);

		if (portlet.isStatic()) {
			url.append("&p_p_static=1");

			if (portlet.isStaticStart()) {
				url.append("&p_p_static_start=1");
			}
		}

		if (Validator.isNotNull(doAsUserId)) {
			url.append("&doAsUserId=");
			url.append(doAsUserId);
		}

		url.append("&currentURL=");
		url.append(HttpUtil.encodeURL(currentURL));

		String ppid = ParamUtil.getString(request, "p_p_id");

		if (ppid.equals(portlet.getPortletId())) {
			Enumeration enu = request.getParameterNames();

			while (enu.hasMoreElements()) {
				String name = (String)enu.nextElement();

				if (!PortalUtil.isReservedParameter(name)) {
					String[] values = request.getParameterValues(name);

					for (int i = 0; i < values.length; i++) {
						url.append(StringPool.AMPERSAND);
						url.append(name);
						url.append(StringPool.EQUAL);
						url.append(HttpUtil.encodeURL(values[i]));
					}
				}
			}

			Map renderParameters = RenderParametersPool.get(request, plid.longValue(), ppid);

			Iterator itr = renderParameters.keySet().iterator();

			while (itr.hasNext()) {
				String name = (String)itr.next();

				String[] values = (String[])renderParameters.get(name);

				for (int i = 0; i < values.length; i++) {
					url.append(StringPool.AMPERSAND);
					url.append(name);
					url.append(StringPool.EQUAL);
					url.append(HttpUtil.encodeURL(values[i]));
				}
			}
		}
		%>

		<script type="text/javascript">
			function <%= portletDisplay.getNamespace() %>refreshPortlet() {
				jQuery("#p_p_id<%= portletDisplay.getNamespace() %>").empty().append('<div class="loading-animation" id="p_load<%= portletDisplay.getNamespace() %>"></div>');
				addPortletHTML("<%= url.toString() %>", jQuery("#p_load<%= portletDisplay.getNamespace() %>")[0]);
			}

			jQuery(window).load(
				function () {
					addPortletHTML("<%= url.toString() %>", jQuery("#p_load<%= portletDisplay.getNamespace() %>")[0]);
				}
			);
		</script>
	</c:otherwise>
</c:choose>