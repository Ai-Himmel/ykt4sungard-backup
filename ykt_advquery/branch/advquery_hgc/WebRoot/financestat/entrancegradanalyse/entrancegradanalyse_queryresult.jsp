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
<%String groupedlist = request.getAttribute("egroupedlist").toString();%>
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
			
		<%	String[] grpList = groupedlist.split(",");
			int grpSize = grpList.length;
			String currGrp = "";
			for (int i=0;i<grpSize;i++){
			currGrp = grpList[i].toString();
				if ("dept".equals(currGrp)){
		%>
			<ec:column property="deptName" headerStyle="text-align:center"
				style="text-align:left"
				filterable="false" 
				sortable="false" 
				title='<%= GetProperty.getProperties("ana.dept",getServletContext())%>' />
		<%	}else if ("spec".equals(currGrp)){%>
			<ec:column property="specName" headerStyle="text-align:center"
				style="text-align:left"
				filterable="false" 
				sortable="false" 
				title='<%= GetProperty.getProperties("ana.spec",getServletContext())%>' />
		<%	}else if ("class".equals(currGrp)){%>
			<ec:column property="classNo" headerStyle="text-align:center"
				style="text-align:left"
				filterable="false" 
				sortable="false" 
				title='<%= GetProperty.getProperties("ana.class",getServletContext())%>' />
		
		<%	}else if ("custtype".equals(currGrp)){%>
			<ec:column property="cutTypeName" headerStyle="text-align:center"
				style="text-align:left"
				filterable="false" 
				sortable="false" 
				title='<%= GetProperty.getProperties("ana.custtype",getServletContext())%>' />
		<%	}else if ("cardtype".equals(currGrp)){%>
			<ec:column property="cardTypeName" headerStyle="text-align:center"
				style="text-align:left"
				filterable="false" 
				sortable="false" 
				title='<%= GetProperty.getProperties("ana.cardtype",getServletContext())%>' />
		<%	}else if ("devuse".equals(currGrp)){%>
		<ec:column property="devUseName" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("ana.devuse",getServletContext())%>' />
		<%	}}%>
			
		<ec:column property="num" headerStyle="text-align:center"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("ana.num",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>

