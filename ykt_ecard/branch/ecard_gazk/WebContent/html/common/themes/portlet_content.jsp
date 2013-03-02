<c:if test="<%= portletDisplay.isActive() %>">
	<c:if test="<%= portletDisplay.isAccess() && (!BrowserSniffer.is_ns_4(request) || (BrowserSniffer.is_ns_4(request) && !portletDisplay.isStateMin())) %>">
		
		<c:if test="<%= Validator.isNotNull(tilesPortletSubNav) %>">
			<!-- +++++++++ -->
			
			<table border="0" cellpadding="0" cellspacing="0" width="100%">
				<tr>
          		<td height="22" valign="top" bgcolor="#7EA2C6">
	          		<table width="177" height="19" border="0" cellpadding="0" cellspacing="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/menu_2.jpg">
					<tr>
					<td width="11" align="right" class="text_brown"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/dian.jpg" width="3" height="5"></td>						
			<liferay:include page="<%= Constants.TEXT_HTML_DIR + tilesPortletSubNav %>" flush="true" />

					</tr>
					</table>
				</td>
				</tr>
			</table>
			<!-- -------- -->
		</c:if>
				
		<c:if test="<%= portletDisplay.isStateMax() %>">
			
		</c:if>
		<%//+++++++++++++%>
		<table width="100%"  id="<portlet:namespace />contentTable" border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="8" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/kk_l_1.jpg" width="8" height="7"></td>
              <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/kk_top.jpg"></td>
              <td width="7" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/kk_r_1.jpg" width="7" height="7"></td>
            </tr>
            <tr>
              <td bgcolor="#FFFFFF">&nbsp;</td>
              <td valign="top" bgcolor="#FFFFFF">
         <%//+++++++++++%>
		<c:if test="<%= Validator.isNotNull(tilesPortletContent) %>">
			<liferay:include page="<%= Constants.TEXT_HTML_DIR + tilesPortletContent %>" flush="true" />
		</c:if>

		<c:if test="<%= Validator.isNull(tilesPortletContent) %>">

			<%
			pageContext.getOut().print(renderRequest.getAttribute(WebKeys.PORTLET_CONTENT));
			%>

		</c:if>
		<%//++++%>
				</td>
			<td bgcolor="#FFFFFF">&nbsp;</td>
            </tr>
            <tr>
              <td height="5"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/kk_l_3.jpg" width="8" height="5"></td>
              <td height="5" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/kk_foot.jpg"></td>
              <td width="7" height="5"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/kk_r_3.jpg" width="7" height="5"></td>
            </tr>
        </table>
        <%//++++++++%>
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