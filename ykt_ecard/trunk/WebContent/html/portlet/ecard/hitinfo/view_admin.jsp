<%@ include file="/html/portlet/ecard/hitinfo/init.jsp"%>
<%@ include file="/html/portlet/ecard/hitinfo/permission.jsp" %>
<%
	List results = HitInfoUtil.getHitInfos();
	SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardhit.tab.view" /></td>
          <td width="11%" valign="bottom">&nbsp;</td>
          <td width="15%" align="right" valign="middle" nowrap class="text_brown">&nbsp;</td>
        </tr>
      </table></td>
    </tr>
  </table>
    <table width="100"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="5"></td>
      </tr>
    </table>
    <table width="719"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td width="9" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_1.jpg" width="9" height="7"></td>
        <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_top.jpg"></td>
        <td width="6" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_1.jpg" width="6" height="7"></td>
      </tr>
      <tr>
        <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_2.jpg">&nbsp;</td>
        <td valign="top" align=center bgcolor="#FFFFFF">
        <!-- content table -->
         <table width="100%"  border="0" cellspacing="0" cellpadding="0">        	
          <tr>            
            <td valign="bottom">&nbsp;
            	<marquee onmouseover="this.stop()" onmouseout="this.start()" SCROLLDELAY=200><bean:message key="ecardhit.tab.title" />:&nbsp;
            	<%Iterator it = results.iterator();
            	while (it.hasNext()) {
            		HashMap hitInfo = (HashMap)it.next();
            		String infoType = (String) hitInfo.get("infoType");
            		String[] urlInfos = TypeMappingUtil.getPortletURLInfo(infoType);
            		if (infoType.equals(EcardConstants.INFORMATION_DOCUMENT_TYPE)) {
            			String[] attachIds = StringUtil.split((String) hitInfo.get("attachments"), EcardConstants.DELIMITER);%>
            		<a href="<%= urlInfos[1]%>?id=<%= attachIds[0]%>" 
            		class="blue_link_line"><%= hitInfo.get("title")%>(<%= format.format((Date) hitInfo.get("createDate"))%>)</a>
            		&nbsp;&nbsp;
            		<%} else if (infoType.indexOf(EcardConstants.INFORMATION_FAQ_TYPE + ".") == 0) {%>
					<a href="<portlet:renderURL portletName="<%= urlInfos[0]%>" windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="<%=urlInfos[1]%>" /></portlet:renderURL>&subid=<%= infoType%>" 
            		class="blue_link_line"><%= hitInfo.get("title")%>(<%= format.format((Date) hitInfo.get("createDate"))%>)</a>
            		&nbsp;&nbsp;
            		<%} else {%>
            		<a href="<portlet:renderURL portletName="<%= urlInfos[0]%>" windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="<%=urlInfos[1]%>" /></portlet:renderURL>&id=<%= hitInfo.get("infoId")%>" 
            		class="blue_link_line"><%= hitInfo.get("title")%>(<%= format.format((Date) hitInfo.get("createDate"))%>)</a>
            		&nbsp;&nbsp;
            		<%}%>
            	<%}%>
            	</marquee>
              </td>            
          </tr>
        </table>
          <!-- content table --></td>
        <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_2.jpg">&nbsp;</td>
      </tr>
      <tr>
        <td width="9" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_3.jpg" width="9" height="7"></td>
        <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_foot.jpg"></td>
        <td width="6" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_3.jpg" width="6" height="7"></td>
      </tr>
    </table>