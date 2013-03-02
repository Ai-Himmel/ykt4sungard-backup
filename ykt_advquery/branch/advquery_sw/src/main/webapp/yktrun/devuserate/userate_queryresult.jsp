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
<%String picType = request.getAttribute("pictype").toString();%>
<%String dateRange = request.getAttribute("daterange").toString();%>
<%String devName = request.getAttribute("devname").toString();%>
<%String yLabel = request.getAttribute("ylabel").toString();%>
<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="result" 
		title='<%= devName+GetProperty.getProperties("dev.title",getServletContext())+dateRange%>'
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
		<ec:column property="devuse" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("dev.use",getServletContext())%>' />	
		<ec:column property="total" 
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("dev.totle",getServletContext())%>' />
		<ec:column property="rate" 
			cell="currency"
			format="#0"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("dev.rate",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>
<table>
<cewolf:chart 
	id="line" 
	title='<%= devName+GetProperty.getProperties("dev.title",getServletContext())%>'
	type="<%=picType%>"
	yaxislabel="<%=yLabel%>"
	> 
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="devUseRateChart" />
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