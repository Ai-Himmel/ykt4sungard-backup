d<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
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
<cache:cache>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr><TD>
<ec:table items="result" 
		title='<%= GetProperty.getProperties("cardues.title",getServletContext())%>' 
		filterable="false"
		imagePath="../../commons/ximages/*.gif" 
		rowsDisplayed="10">
    <ec:export 
       view="xls" 
       fileName="output.xls" />


	<ec:row highlightRow="true">
		<ec:column property="dict_caption" 
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("cardues.cardtype",getServletContext())%>' />
		<ec:column property="cardnum" 
			
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("cardues.num",getServletContext())%>' />	
		<ec:column property="rate" 
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			cell="number"
			format="##0.0000"
			title='<%= GetProperty.getProperties("cardues.prop",getServletContext())%>' />
	</ec:row>

</ec:table>
</TD></tr></table>
<table>
<cewolf:chart 
	id="verticalBar" 
	title='<%= GetProperty.getProperties("carduse.title",getServletContext())%>'
	type="verticalBar3D"> 
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="cardUseVBarData" />
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


<cewolf:chart id="pieChart"
	title='<%= GetProperty.getProperties("cardues.scale",getServletContext())%>'
	type="pie">
	<cewolf:colorpaint
		color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>' />
		<cewolf:data>
			<cewolf:producer id="cardUsePieData" />
		</cewolf:data>
		<cewolf:chartpostprocessor id="dataColorPie">
		</cewolf:chartpostprocessor>
	</cewolf:chart>

	<cewolf:img chartid="pieChart" renderer="/cewolf"
		width='<%= Integer.parseInt(GetProperty.getProperties("chart.piewidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.piewidth",getServletContext()))%>' />

</table>
</cache:cache>
