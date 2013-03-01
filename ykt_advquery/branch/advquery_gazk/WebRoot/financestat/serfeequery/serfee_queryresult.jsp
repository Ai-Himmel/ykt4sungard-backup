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
<%String titles = request.getAttribute("titles").toString();%>
<%List result = (List) request.getAttribute("result");%>
<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="SerFeeQuery" 
		title="<%=titles%>"
		filterable="false"
		imagePath="${pageContext.request.contextPath}/commons/ximages/*.gif" 
		rowsDisplayed="20">
      
    <ec:export 
       view="xls" 
       fileName="output.xls" />
   
	<ec:row highlightRow="true">
		<ec:column property="custName" headerStyle="text-align:center"
			width="60"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("serfee.name",getServletContext())%>' />
			
		<ec:column property="stuempNo" headerStyle="text-align:center"
			width="60"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("serfee.stuempno",getServletContext())%>' />	
		
		<ec:column property="classNo" headerStyle="text-align:center"
			width="60"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("serfee.classno",getServletContext())%>' />	
			
		<ec:column property="manId" headerStyle="text-align:center"
			width="80"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("serfee.manId",getServletContext())%>' />	
			
	  		
		<ec:column property="fillserfee" headerStyle="text-align:center"
			width="50"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("serfee.fillserfee",getServletContext())%>' />
		<ec:column property="fillselftotle" headerStyle="text-align:center"
			width="50"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("serfee.fillself",getServletContext())%>' />
		<ec:column property="accountbal" headerStyle="text-align:center"
			width="50"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("serfee.accountbal",getServletContext())%>' />
		<ec:column property="smlbalance" headerStyle="text-align:center"
			width="50"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("serfee.smlbalance",getServletContext())%>' />
		<ec:column property="facttotlebal" headerStyle="text-align:center"
			width="50"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("serfee.facttotlebal",getServletContext())%>' />
		
		<ec:column property="backbal" headerStyle="text-align:center"
			width="50"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("serfee.backbal",getServletContext())%>' />
		<ec:column property="consbal" headerStyle="text-align:center"
			width="50"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("serfee.consbal",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>

