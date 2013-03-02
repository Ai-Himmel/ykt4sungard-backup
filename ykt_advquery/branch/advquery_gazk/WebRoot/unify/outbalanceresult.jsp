<%@ include file="/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<%@ page language="java" pageEncoding="UTF-8"%>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<html:base/>
<html>
   
   <%
      List result = (List) request.getAttribute("result");
      String title = (String)request.getAttribute("title");
   %>
  
  
  <body>
        <table border="0"  cellpadding="0"  cellspacing="0"  width="60%">
<tr><td>
<ec:table items="result" 
		title='<%=title%>'
		filterable="false"
		imagePath="/advquery/commons/ximages/*.gif" 
		rowsDisplayed="15"
		action="/advquery/outBalanceQry.do"
		>

    <ec:export 
       view="xls" 
       fileName="output.xls" />
       
	<ec:row highlightRow="true">
	     
		<ec:column property="stuempNo" headerStyle="text-align:center"
		    style="text-align:center"
			filterable="false" 
			sortable="false"
			title="<%= GetProperty.getProperties("special.manId",getServletContext())%>" />
		<ec:column property="cutName" headerStyle="text-align:center"
		    style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.name",getServletContext())%>' />	
		
	   <ec:column property="deptName" headerStyle="text-align:center"
	        style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.deptname",getServletContext())%>' />	
	 
	   <ec:column property="operateDate" headerStyle="text-align:center"
	        style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.optDate",getServletContext())%>' />	
				
	  <ec:column property="operateTime" headerStyle="text-align:center"
	        style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.optTime",getServletContext())%>' />	
			
	  <ec:column property="outBalance" headerStyle="text-align:center"
	        style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.outbalance",getServletContext())%>'
			 >			
			
	 		</ec:column>                                                                                                                                                                           
	</ec:row>

</ec:table>
</td></tr></table>
<table>
  </body>
</html>
