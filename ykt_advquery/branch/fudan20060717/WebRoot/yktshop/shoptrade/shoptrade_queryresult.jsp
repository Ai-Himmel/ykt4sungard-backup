<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ include file="/commons/init.jsp"%>
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
<tr>
<td>
<ec:table items="result" 
		title='<%= GetProperty.getProperties("menu.shop.posequery",getServletContext())%>' 
		filterable="false"
		imagePath="/advquery/commons/ximages/*.gif" 
		rowsDisplayed="20" locale="zh_CN"
		action="/advquery/shoptraderesult.do"
		>

    <ec:export 
       view="xls" 
       fileName="output.xls" />

	<ec:row highlightRow="true">
		<ec:column property="devName" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("savingsort.devname",getServletContext())%>' />
		<ec:column property="stuNo" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("special.custid",getServletContext())%>' />
		<ec:column property="name"  headerStyle="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.name",getServletContext())%>' />	
		<ec:column property="tradCount"  headerStyle="text-align:center"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.tradenum",getServletContext())%>' />	
		<ec:column property="opfee"  headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("deptaccount.consume",getServletContext())%>' />
		<ec:column property="optDate"  headerStyle="text-align:center"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("oneaccount.detail.date",getServletContext())%>' />
	   <ec:column property="optTime"  headerStyle="text-align:center"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("oneaccount.detail.time",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>




