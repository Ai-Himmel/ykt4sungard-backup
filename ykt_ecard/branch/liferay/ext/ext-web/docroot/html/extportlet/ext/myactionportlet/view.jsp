<%@page pageEncoding="UTF-8"%>
<%@ include file="/html/extportlet/ext/myactionportlet/init.jsp" %>
<br/>
添加一本書:
<br/><br/>
<form action="<portlet:actionURL windowState="<%=WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/ext/myaction/addbook"/></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
书名:
<input name="<portlet:namespace />book_title" size="20" type="text" value=""><br/><br/>
<input type="button" value="Submit" onClick="submitForm(document.<portlet:namespace />fm);">
</form>
<br/>