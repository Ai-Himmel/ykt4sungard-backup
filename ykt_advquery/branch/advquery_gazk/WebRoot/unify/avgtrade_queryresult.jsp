<%@ include file="/commons/init.jsp"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<%List result = (List) request.getAttribute("result");
%>
<%String dateRange = request.getAttribute("dateRange").toString();%>
<%String specStatTip = request.getAttribute("specStatTip").toString();%>
<%String yLabel = request.getAttribute("ylabel").toString();%>

<body>

<table border="0"  cellpadding="0"  cellspacing="0"  width="60%">
<tr><td>
<ec:table items="result" 
		title='<%=specStatTip%>' 
		filterable="false"
		imagePath="/advquery/commons/ximages/*.gif" 
		rowsDisplayed="5"
		showExports="true"
		action="/advquery/avgtradeQry.do"
		>
   <ec:export 
       view="xls" 
       fileName="output.xls" />
       
	<ec:row highlightRow="true">

	    <ec:column property="opeDate" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("allconsume.month",getServletContext())%>' />
	    
		<ec:column property="deptName" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("special.deptname",getServletContext())%>' />
			
		
		<ec:column property="count" headerStyle="text-align:center"	
			style="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("allconsume.deptnum",getServletContext())%>' />
		
		<ec:column property="tradeFee" headerStyle="text-align:center"
			format="###,###,##0.00"
			cell="currency"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("deptconsume.money",getServletContext())%>' />
		
	   <ec:column property="avgFee" headerStyle="text-align:center"
			format="###,###,##0.00"
			cell="currency"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("allconsume.avgtrade",getServletContext())%>' />
		
			
	</ec:row>
</ec:table>
</td></tr></table>


<table border="0"  cellpadding="0"  cellspacing="0"  width="60%">
<cewolf:chart 
	id="verticalBar" 
	title='<%= GetProperty.getProperties("allconsume.avgtrade",getServletContext())+dateRange%>'
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


</body>
</html>


