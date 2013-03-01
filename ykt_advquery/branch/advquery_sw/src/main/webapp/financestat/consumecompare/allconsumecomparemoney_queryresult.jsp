<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ include file="/commons/init.jsp"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<%String statTypeShow = request.getAttribute("stattypeshow").toString();%>
<%String dateRange = request.getAttribute("daterange").toString();%>
<%List result = (List) request.getAttribute("result");%>
<%String picType = request.getAttribute("pictype").toString();%>
<%String yLabel = request.getAttribute("ylabel").toString();%>

<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>
<ec:table items="result" 
		title='<%= GetProperty.getProperties("allconsumecompare.title",getServletContext())+dateRange%>' 
		filterable="false"
		
		imagePath="../../commons/ximages/*.gif" 
		rowsDisplayed="10">
    <ec:export
       view="xls"
       fileName="output.xls"
        />
	<ec:row highlightRow="true">
		<ec:column property="balance_date" headerStyle="text-align:center"
			filterable="false" 
			sortable="false"
			title="<%= statTypeShow%>" />
		<ec:column property="hd" headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("allconsumecompare.hd",getServletContext())%>' />	
		<ec:column property="fl" headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("allconsumecompare.fl",getServletContext())%>' />
		<ec:column property="zj" headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("allconsumecompare.zj",getServletContext())%>' />
		<ec:column property="jw" headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("allconsumecompare.jw",getServletContext())%>' />
	</ec:row>
</ec:table>
</td></tr></table>
<table>
	<cewolf:chart 
		id="verticalBar" 
		title='<%= GetProperty.getProperties("consumecomparemoney.title",getServletContext())%>'
		type="<%=picType%>"
		yaxislabel="<%=yLabel%>"
		> 
		<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
		<cewolf:data>
			<cewolf:producer id="AllConsumeCompareMoneyChart" />
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