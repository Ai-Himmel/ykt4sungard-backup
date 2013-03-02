<%@ page import="com.kingstargroup.advquery.hibernate.util.UserUtil" %>
<%@ page import="com.kingstargroup.advquery.util.GetterUtil" %>
<%
String username = GetterUtil.get((String)request.getSession().getAttribute("username"), ""); 
if(!UserUtil.checkUserRight(username, "/savingsortcont.do")) {%> 
	<bean:message key="eadvquery.error.illegalvisit" /> 
	<%
	return;
}%>