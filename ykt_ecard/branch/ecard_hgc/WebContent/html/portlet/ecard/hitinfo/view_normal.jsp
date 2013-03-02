<%@ include file="/html/portlet/ecard/hitinfo/init.jsp"%>
<%
	List results = HitInfoUtil.getHitInfos();
	SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
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
          <!-- content table -->