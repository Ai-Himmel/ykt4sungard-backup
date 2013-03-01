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
<%List result = (List) request.getAttribute("result");%>
<%String dateRange = request.getAttribute("daterange").toString();%>
<%String picType = request.getAttribute("pictype").toString();%>
<%String yLabel = request.getAttribute("ylabel").toString();%>
<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr>
<td>
<ec:table items="result" 
		title='<%= GetProperty.getProperties("shopcompare.title",getServletContext())+dateRange%>' 
		filterable="false"
		imagePath="../../commons/ximages/*.gif" 
		rowsDisplayed="10" locale="zh_CN"
		>

    <ec:export 
       view="xls" 
       fileName="output.xls" />

	<ec:row highlightRow="true">
		<ec:column property="shopid" headerStyle="text-align:center"
			style="text-align:center"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("shopcompare.shopid",getServletContext())%>' />
		<ec:column property="shopname" headerStyle="text-align:center"
			style="text-align:left"
			filterable="false" 
			sortable="false"
			title='<%= GetProperty.getProperties("shopcompare.shopname",getServletContext())%>' />
		<ec:column property="tradenum"  headerStyle="text-align:center"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("shopcompare.tradenum",getServletContext())%>' />	
		<ec:column property="tradeamt"  headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("shopcompare.tradeamt",getServletContext())%>' />	
		<ec:column property="mngamt"  headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("shopcompare.mngamt",getServletContext())%>' />
		<ec:column property="totalamt"  headerStyle="text-align:center"
			cell="currency"
			format="###,###,###,##0.00"
			style="text-align:right"
			filterable="false" 
			sortable="false" 
			title='<%= GetProperty.getProperties("shopcompare.totalamt",getServletContext())%>' />
	</ec:row>

</ec:table>
</td></tr></table>
<table>
<cewolf:chart 
	id="verticalBar" 
	title='<%= GetProperty.getProperties("shopcompare.title",getServletContext())%>'
	type="<%=picType%>"
	yaxislabel="<%=yLabel%>"
	> 
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="shopCompareData" />
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

<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0" bgcolor="#f8f8f8">
	<tr>
		<td height="30">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="85%" class="red_text"></td>
				<td width="15%" align="center">
				<button onclick="javascript:renderCancelPage();"><bean:message key="btn.return" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>
</tr></table>
<script>

      	function renderCancelPage() {
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/shopcomparecont.do';
		}
</script>

