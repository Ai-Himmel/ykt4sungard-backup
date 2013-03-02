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
<%String dateRange = request.getAttribute("daterange").toString();%>
<%String specStatTip = request.getAttribute("specStatTip").toString();%>
<%String yLabel = request.getAttribute("ylabel").toString();%>
<%String mealStr = request.getAttribute("mealStr").toString();%>
<%List resultAvg = (List) request.getAttribute("resultAvg");%>

<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="resultAvg" 
		title='<%=specStatTip%>' 
		filterable="false"
		imagePath="../../commons/ximages/*.gif" 
		rowsDisplayed="5"
		showExports="false">
    <ec:export 
       view="xls" 
       fileName="output.xls" />
	<ec:row highlightRow="true">
		<ec:column property="accyear" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.year",getServletContext())%>' />
		<ec:column property="femaleavg" headerStyle="text-align:center"
			format="###,###,##0.00"
			cell="currency"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.femaleavg",getServletContext())%>' />
		<ec:column property="maleavg" headerStyle="text-align:center"
			format="###,###,##0.00"
			cell="currency"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.maleavg",getServletContext())%>' />
		<ec:column property="totavg" headerStyle="text-align:center"
			format="###,###,##0.00"
			cell="currency"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.avg",getServletContext())%>' />
	</ec:row>
</ec:table>
</td></tr></table>

.

<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="resultList" 
		title='<%=GetProperty.getProperties("spec.title",getServletContext())+dateRange%>' 
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
			title='<%= GetProperty.getProperties("spec.stuempNo",getServletContext())%>' />
		<ec:column property="cut_name" headerStyle="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.name",getServletContext())%>' />	
		<ec:column property="dept_name" headerStyle="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.dept",getServletContext())%>' />
		<ec:column property="s_name" headerStyle="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.scode",getServletContext())%>' />
		<ec:column property="class_no" headerStyle="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.class",getServletContext())%>' />
		<ec:column property="type_name" headerStyle="text-align:center"
			filterable="false" 
			style="text-align:left"
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.custType",getServletContext())%>' />
		<ec:column property="meal" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.meal",getServletContext())%>' />
		<ec:column property="amcount" headerStyle="text-align:center"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.amcount",getServletContext())%>' />
		<ec:column property="amsum" headerStyle="text-align:center"
			format="###,###,##0.00"
			cell="currency"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.amsum",getServletContext())%>' />
		<ec:column property="avg" headerStyle="text-align:center"
			format="###,###,##0.00"
			cell="currency"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("spec.avg",getServletContext())%>' />
	</ec:row>
</ec:table>
</td></tr></table>

<table>
<cewolf:chart 
	id="verticalBar" 
	title='<%= mealStr+"-"+GetProperty.getProperties("spec.consTitle",getServletContext())%>'
	type="verticalBar"
	yaxislabel="<%=yLabel%>"> 
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="consAvgData" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="dataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>

</cewolf:chart>

<cewolf:img 
	chartid="verticalBar" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'/>
</table>

