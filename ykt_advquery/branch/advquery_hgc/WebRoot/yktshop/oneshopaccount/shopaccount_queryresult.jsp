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
<%String dateRange = request.getAttribute("dateRange").toString();%>

<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="result" 
		title='<%= GetProperty.getProperties("shopaccount.title",getServletContext())+dateRange%>' 
		filterable="false"
		imagePath="../../commons/ximages/*.gif" 
		rowsDisplayed="10" locale="zh_CN"
		>
    <ec:export 
       view="xls" 
       fileName="output.xls" />

	<ec:row highlightRow="true">
		<ec:column property="shopName" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false"
			title="<%= GetProperty.getProperties("shopcompare.shopname",getServletContext())%>" />
		<ec:column property="deviceName"  headerStyle="text-align:center"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("shopaccount.childname",getServletContext())%>' />	
		<ec:column property="sumCount"  headerStyle="text-align:center"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("shopaccount.tradecount",getServletContext())%>' />
		<ec:column property="sumTrade"  headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("shopaccount.tradeamt",getServletContext())%>' />
		<ec:column property="sumMng"  headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("shopaccount.mngamt",getServletContext())%>' />
		<ec:column property="sumTotal"  headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("shopaccount.totalamt",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>
