<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ include file="/commons/init.jsp"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<%@ page import="com.kingstargroup.advquery.util.ParamUtil" %>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<%String titles = request.getAttribute("title").toString();%>
<%List result = (List) request.getAttribute("result");%>
<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="result" 
		title="<%=titles%>"
		filterable="false"
		imagePath="${pageContext.request.contextPath}/commons/ximages/*.gif" 
		rowsDisplayed="50">

    <ec:export 
       view="xls" 
       fileName="output.xls" />

	<ec:row highlightRow="true">
		<ec:column property="deviceId" headerStyle="text-align:center"
			width="15%"
			style="text-align:center"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("door.deviceId",getServletContext())%>' />
			
		<ec:column property="deviceName" headerStyle="text-align:center"
			width="40%"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("door.deviceName",getServletContext())%>' />	
			
		<ec:column property="txDate" headerStyle="text-align:center"
			width="15%"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("door.txDate",getServletContext())%>' />
			
		<ec:column property="txTime" headerStyle="text-align:center"
		    width="15%"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("door.txTime",getServletContext())%>' />
			
		<ec:column property="custId" headerStyle="text-align:center"
		    width="15%"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("door.custno",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>

