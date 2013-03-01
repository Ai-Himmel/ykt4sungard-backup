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
   
    <%List registerList = (List) request.getAttribute("registerList");%>
  <%
         String       begindate= (String) request.getAttribute("beginDate");
         String       enddate = (String) request.getAttribute("endDate");
  %>
  <body>
        <table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="registerList" var="register"
		title='<%= GetProperty.getProperties("register.query",getServletContext())+begindate+"--"+enddate%>'
		filterable="false"
		imagePath="/advquery/commons/ximages/*.gif" 
		rowsDisplayed="10"
		action="/advquery/registerQuery.do"
		locale="zh_CN"
		>

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
	   <ec:column property="feeName" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.feeType",getServletContext())%>' />	
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
	   <ec:column property="txDate" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("register.date",getServletContext())%>' />	
	    <ec:column property="comments" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("register.comments",getServletContext())%>' >		
			<a href="#"	onclick="window.open('/advquery/registerComment.do?cmd=query&regId=${register.regId}&custId=${register.custId}','<%= GetProperty.getProperties("register.comments",getServletContext())%>','top=450,left=600,height=250,width=400,scrollbars=no,resizable=no,status=no,toolbar=no,menubar=no,location=no'); return false;" ><%= GetProperty.getProperties("register.comments",getServletContext())%></a>	
	   </ec:column>
			
	</ec:row>

</ec:table>
</td></tr></table>
<table>
  </body>
</html>
