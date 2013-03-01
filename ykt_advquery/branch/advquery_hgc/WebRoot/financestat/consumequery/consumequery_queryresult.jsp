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

<%List resultList = (List) request.getAttribute("resultList");%>
<%String specStatTip = request.getAttribute("specStatTip").toString();%>

<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="resultList" 
		title="<%=specStatTip%>"
		filterable="false"
		imagePath="${pageContext.request.contextPath}/commons/ximages/*.gif" 
		rowsDisplayed="15">
		
    <ec:export 
       view="xls" 
       fileName="output.xls" />

	<ec:row highlightRow="true">
		<ec:column property="stuempNo" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.stuempNo",getServletContext())%>' />
		<ec:column property="custName" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.name",getServletContext())%>' />
		<ec:column property="custSex" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("query.sex",getServletContext())%>' />
		<ec:column property="custType" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.custType",getServletContext())%>' />
		<ec:column property="deptName" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.dept",getServletContext())%>' />
		<ec:column property="specName" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.scode",getServletContext())%>' />
		<ec:column property="classNo" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.class",getServletContext())%>' />
		<ec:column property="consumeNum" headerStyle="text-align:center"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("ana.num",getServletContext())%>' />
		<ec:column property="consumeMoney" headerStyle="text-align:center"
			format="###,###,##0.00"
			cell="currency"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("ana.money",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>

