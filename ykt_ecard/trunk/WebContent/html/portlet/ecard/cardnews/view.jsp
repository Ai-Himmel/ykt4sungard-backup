<%@ include file="/html/portlet/ecard/cardnews/init.jsp" %>

<%
List list = ((ResultPage) request.getAttribute("result")).getList();
SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
<table cellpadding="4" cellspacing="0" width="100%" >

		
				<%java.util.Iterator it = list.iterator();				
				while(it.hasNext()) {
					EcardInformation info = (EcardInformation) it.next();
					%>
					<tr>
					<td>
					<img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/jiantou.jpg" width="8" height="8">
                  <a  class="brown_link_line" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardnews/view" /></portlet:renderURL>&id=<%= info.getId()%>">                  
                  	<%= info.getInfoTitle()%>(<%= format.format(info.getCreateDate())%>)
                  	</a>
                  	<c:if test="<%= DateFormatUtil.isHotInfo(info.getCreateDate())%>">
                  	<img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/hot.gif" width="17" height="8">
                  	</c:if>
					</td></tr>
                <%}%>                         		
		
	
	<tr>
	              <td align = right>
	              <a class=text_brown href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardnews/view" /></portlet:renderURL>">
	              <bean:message key="ecard.more" />>></a></td>
	</tr>
</table>

