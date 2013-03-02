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
<%String dateRange = request.getAttribute("daterange").toString();%>
<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="result" 
		title='<%=GetProperty.getProperties("special.title",getServletContext())+dateRange%>' 
		filterable="false"
		imagePath="../../commons/ximages/*.gif" 
		rowsDisplayed="20">

    <ec:export 
       view="xls" 
       fileName="output.xls" />

	<ec:row highlightRow="true">
		<ec:column property="stuemp_no" headerStyle="text-align:center"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("special.custid",getServletContext())%>' />
		<ec:column property="cut_name" headerStyle="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.name",getServletContext())%>' />	
		<ec:column property="dept_name" headerStyle="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.dept",getServletContext())%>' />
		<ec:column property="s_name" headerStyle="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.scode",getServletContext())%>' />
		<ec:column property="tradefee" headerStyle="text-align:center"
			filterable="false" 
			style="text-align:right"
			sortable="false" 
			title='<%= GetProperty.getProperties("special.tradefee",getServletContext())%>' />
		<ec:column property="avgfee" headerStyle="text-align:center"
			format="###,###,##0.00"
			cell="currency"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.avgfee",getServletContext())%>' />
		<ec:column property="tradenum" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.tradenum",getServletContext())%>' />
		<ec:column property="avgnum" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.avgnum",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>
