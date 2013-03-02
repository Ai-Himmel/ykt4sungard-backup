<%@ include file="/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>

<%String statTypeShow = request.getAttribute("stattypeshow").toString();%>
<%List result = (List) request.getAttribute("result");%>
<%String dateRange = request.getAttribute("daterange").toString();%>
<%String yLabel = request.getAttribute("ylabel").toString();%>
<%String picType = request.getAttribute("pictype").toString();%>
<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>

<ec:table items="result" 
		title='<%= GetProperty.getProperties("tranfer.title",getServletContext())+dateRange%>' 
		filterable="false"
		imagePath="../../commons/ximages/*.gif" 
		rowsDisplayed="10">

    <ec:export 
       view="xls" 
       fileName="output.xls" />

	<ec:row highlightRow="true">
		<ec:column property="balance_date" 
			filterable="false" 
			sortable="false"
			title="<%= statTypeShow%>" />
		<ec:column property="inaccount" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("tranfer.account",getServletContext())%>' />	
		<ec:column property="account" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("tranfer.inaccount",getServletContext())%>' />
		<ec:column property="rate" 
			cell="currency"
			format="#0.00"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("tranfer.rate",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>

<table>
<cewolf:chart 
	id="line" 
	title='<%= GetProperty.getProperties("transfer.title",getServletContext())%>'
	type="<%=picType%>"
	yaxislabel="<%=yLabel%>"
	> 
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="transferChart" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="dataColor">
    </cewolf:chartpostprocessor>

</cewolf:chart>

<cewolf:img 
	chartid="line" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'/>
</table>