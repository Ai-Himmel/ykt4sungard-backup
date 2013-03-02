<%
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
%>
<c:if test="<%= portletDisplay.isActive() %>">
	<c:if test="<%= portletDisplay.isAccess() && (!BrowserSniffer.is_ns_4(request) || (BrowserSniffer.is_ns_4(request) && !portletDisplay.isStateMin())) %>">
	<table width="1000" border="0" cellpadding="0" cellspacing="0">
 	 <tr>
    <td height="425" valign="top" bgcolor="#f5f9ff">
	<table width="1000" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="8"></td>
      </tr>
    </table>
	<table width="1000" height="425" border="0" cellpadding="0" cellspacing="0">
        <tr>
		<c:if test="<%= Validator.isNotNull(tilesPortletSubNav) %>">
			<!-- +++++++++++ -->
			<td width="243" height="425" valign="top">
			
			<liferay:include page="<%= Constants.TEXT_HTML_DIR + tilesPortletSubNav %>" flush="true" />					
				
			</td>
			<td width="20" valign="top">&nbsp;</td>
			<!-- ---------- -->
		</c:if>
				
		<c:if test="<%= portletDisplay.isStateMax() %>">
			
		</c:if>
		<!-- ++++++++++ -->
		<c:if test="<%= Validator.isNotNull(tilesPortletSubNav) %>">
			<td width="737" valign="top">
		</c:if>
		
		<c:if test="<%= !Validator.isNotNull(tilesPortletSubNav) %>">
			<td width="1000" valign="top">
		</c:if>
         <! ----------- -->
		<c:if test="<%= Validator.isNotNull(tilesPortletContent) %>">
			<liferay:include page="<%= Constants.TEXT_HTML_DIR + tilesPortletContent %>" flush="true" />
		</c:if>

		<c:if test="<%= Validator.isNull(tilesPortletContent) %>">

			<%
			pageContext.getOut().print(renderRequest.getAttribute(WebKeys.PORTLET_CONTENT));
			%>

		</c:if>
		<!-- +++++++++++ -->
				</td>
				</tr>
				</table>
			</td>
			</tr>
			</table>
        <!-- ---------- -->
		<c:if test="<%= portletDisplay.isStateMax() %>">
			
		</c:if>
	</c:if>

	<c:if test="<%= !portletDisplay.isAccess() %>">
		<liferay:include page="/html/portal/portlet_access_denied.jsp" />
	</c:if>
</c:if>

<c:if test="<%= !portletDisplay.isActive() %>">
	<liferay:include page="/html/portal/portlet_inactive.jsp" />
</c:if>