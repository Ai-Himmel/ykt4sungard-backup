
<%@ include file="/html/portlet/ecard/link/init.jsp" %>
<%
List list = ((ResultPage) request.getAttribute("result")).getList();
%>

<table cellpadding="0" align=center cellspacing="0" class=tdclass>

  <%java.util.Iterator it = list.iterator();
					while(it.hasNext()) {
						FriendsLink link = (FriendsLink) it.next();			
					%>

	<tr>				
		<td align=center>
			 <a href="<%=link.getLinkUrl()%>"  class=brown_link_line target="_blank"><%= link.getLinkName()%></a>
		</td>
	</tr>  
	<%}%>
</table>
&nbsp;
