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
		<ec:column property="operdate" headerStyle="text-align:center"
			width="15%"
			style="text-align:center"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("oneaccount.detail.date",getServletContext())%>' />
		<ec:column property="opertime" headerStyle="text-align:center"
			width="15%"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("oneaccount.detail.time",getServletContext())%>' />	
		<ec:column property="opfee" headerStyle="text-align:center"
			width="15%"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("savingsort.money",getServletContext())%>' />
		
		<ec:column property="newfee" headerStyle="text-align:center"
			width="15%"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.outbalance",getServletContext())%>' />
			
		<ec:column property="devid" headerStyle="text-align:center"
		    width="25%"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("oneaccount.detail.devname",getServletContext())%>' />
			
		<ec:column property="comments" headerStyle="text-align:center"
		    width="15%"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("oneaccount.detail.comments",getServletContext())%>' />
			
	</ec:row>

</ec:table>
</td></tr></table>

