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
		rowsDisplayed="15">

    <ec:export 
       view="xls" 
       fileName="output.xls" />

	<ec:row highlightRow="true">
		<ec:column property="custno" headerStyle="text-align:center"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("special.custid",getServletContext())%>' />
			
		<ec:column property="custname" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.name",getServletContext())%>' />	
			
		<ec:column property="cuttype" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.type",getServletContext())%>' />
			
		<ec:column property="deptname" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.dept",getServletContext())%>' />
			
		<ec:column property="txdate" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("oneaccount.detail.date",getServletContext())%>' />
			
		<ec:column property="txtime" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("oneaccount.detail.time",getServletContext())%>' />
		<ec:column property="billno" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("ticket.ticketno1",getServletContext())%>' />
		<ec:column property="amount" headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("oneshopaccount.tradeamt",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>

