<%@ include file="/commons/init.jsp"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<%List result = (List) request.getAttribute("result");%>
<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="result" 
		filterable="false"
		imagePath="${pageContext.request.contextPath}/commons/ximages/*.gif" 
		rowsDisplayed="20">

    <ec:export 
       view="xls" 
       fileName="output.xls" />

	<ec:row highlightRow="true">
		<ec:column property="shopname" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			width="400"
			title='<%= GetProperty.getProperties("shop.shopname",getServletContext())%>' />
		<ec:column property="balancedate" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			width="100"
			sortable="true" 
			title='<%= GetProperty.getProperties("shop.balancedate",getServletContext())%>' />	
		<ec:column property="operatedate" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			width="100"
			sortable="true" 
			title='<%= GetProperty.getProperties("shop.operdate",getServletContext())%>' />
		<ec:column property="tradenum" headerStyle="text-align:center"
			style="text-align:right"
			parse="true"
			width="100"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("shop.tradenum",getServletContext())%>' />
		<ec:column property="totalamt" headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			parse="true"
			width="100"
			title='<%= GetProperty.getProperties("shop.tradeatm",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>

