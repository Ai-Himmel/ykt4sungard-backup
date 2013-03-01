<%@ include file="/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<%request.setCharacterEncoding("GBK");%>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<html:base/>
<html xmlns="http://www.w3.org/1999/xhtml">
   
   
  <body>
        <table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="registerComeList" var="register"
		title='<%= GetProperty.getProperties("register.query",getServletContext())%>'
		filterable="false"
		imagePath="/advquery/commons/ximages/*.gif" 
		rowsDisplayed="20"
		action="/advquery/registercomeQuery.do">

    <ec:export 
       view="xls" 
       fileName="output.xls" />
       
	<ec:row highlightRow="true">
	
	    <ec:column property="termName" 
			filterable="false" 
			sortable="false"
			title="<%= GetProperty.getProperties("register.term",getServletContext())%>" />
			
		<ec:column property="stuempNo" 
			filterable="false" 
			sortable="false"
			title="<%= GetProperty.getProperties("spec.stuempNo",getServletContext())%>" />
		<ec:column property="cutName" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.name",getServletContext())%>' />	
		<ec:column property="typeName" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.degree",getServletContext())%>' />	

	   <ec:column property="deptName" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.dept",getServletContext())%>' />	
	   <ec:column property="Sname" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.scode",getServletContext())%>' />	
	  <ec:column property="classNo" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.class",getServletContext())%>' />
			
	   <ec:column property="register" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("register.isregister",getServletContext())%>' />		
				
	</ec:row>

</ec:table>
</td></tr></table>
<table>
  </body>
</html>
