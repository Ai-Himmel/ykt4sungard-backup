<%@ include file="/commons/init.jsp"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<%List result = (List) request.getAttribute("result");
%>
<%//String dateRange = request.getAttribute("dateRange").toString();%>
<%String specStatTip = request.getAttribute("specStatTip").toString();%>
<%//String yLabel = request.getAttribute("ylabel").toString();%>

<body>

<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="result" 
		title='<%=specStatTip%>' 
		filterable="false"
		imagePath="/advquery/commons/ximages/*.gif" 
		rowsDisplayed="50"
		showExports="true"
		action="/advquery/tradetotalresult.do"
		>
   <ec:export 
       view="xls" 
       fileName="output.xls" />
       
	<ec:row highlightRow="true">

	   
		
		<ec:column property="cutId" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("customerId",getServletContext())%>' />
			
		<ec:column property="cutName" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("cutName",getServletContext())%>' />
			
	    
		<ec:column property="deptName" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("deptName",getServletContext())%>' />
			
		
		<ec:column property="manId" headerStyle="text-align:center"	
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("manNo",getServletContext())%>' />
		
		<ec:column property="tradeFee" headerStyle="text-align:center"
			format="###,###,##0.00"
			cell="currency"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("feetrade",getServletContext())%>' />
			
		<ec:column property="count" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("feecount",getServletContext())%>' />	
			
			
	</ec:row>
</ec:table>
</td></tr></table>


</body>
</html>


