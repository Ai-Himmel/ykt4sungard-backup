

<%@ include file="init.jsp" %>
<c:if test="<%= portletDisplay.isNarrow()%>">
	<table width="300" bgColor=#ffffff border="0" cellspacing="0" cellpadding="0">
</c:if>
<c:if test="<%= !portletDisplay.isNarrow()%>">
	<table width="100%" bgColor=#ffffff border="0" cellspacing="0" cellpadding="0">
</c:if>
    <tr>
      <td width="9" height="20"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_l_1.jpg" width="9" height="20"></td>
      <td height="20" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_top.jpg">			
		<c:if test="<%= Validator.isNotNull(portletDisplay.getTitle()) %>">
				  <table width="85" height="20" border="0" cellpadding="0" cellspacing="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/menu.jpg">
	                <tr>
	                  <td width="16">&nbsp;</td>
	                  <td width="69" class="text_brown_12_c"><%= portletDisplay.getTitle() %></td>
	                </tr>
	              </table>
		</c:if>
		</td>
		
		
		<td width="9" height="20"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_r_1.jpg" width="9" height="20"></td>
    	 </tr>
			<tr>
              <td valign="top"><img height=240 id="<portlet:namespace />leftImage" src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_l_2.jpg" width="9"></td>
              <td valign="top">
          
