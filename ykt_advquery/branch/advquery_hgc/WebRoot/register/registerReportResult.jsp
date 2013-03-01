<%@ include file="/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>

<html xmlns="http://www.w3.org/1999/xhtml">
   <html:base/>
   
  <body>
 <%
         String       begindate= (String) request.getAttribute("beginDate");
         String       enddate = (String) request.getAttribute("endDate");
 %>

<ec:table items="registerReport" 
		title='<%= GetProperty.getProperties("register.report",getServletContext())+begindate+"--"+enddate%>'
		filterable="false"
		imagePath="/advquery/commons/ximages/*.gif" 
		rowsDisplayed="15"
		action="/advquery/registerReportResult.do"
		>

    <ec:export 
       view="xls" 
       fileName="output.xls" />
       
	<ec:row highlightRow="true">
	
		<ec:column property="term" 
			filterable="false" 
			sortable="false"
			title="<%= GetProperty.getProperties("register.term",getServletContext())%>" />
			
		<ec:column property="deptName" 
			filterable="false" 
			sortable="false"
			title="<%= GetProperty.getProperties("spec.dept",getServletContext())%>" />	
			
		<ec:column property="classname" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.class",getServletContext())%>' />	
			
		<ec:column property="classtotal" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("register.total",getServletContext())%>' />	
			
	   <ec:column property="regtotal" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("register.regtotal",getServletContext())%>' />	
	</ec:row>

</ec:table>


  </body>
</html>
