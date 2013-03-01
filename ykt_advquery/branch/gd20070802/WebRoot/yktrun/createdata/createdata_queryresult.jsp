<%@ include file="/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<%String consume30DaysYLableNum = request.getAttribute("consume30DaysYLableNum").toString();%>
<%String consume30DaysYLableMoney = request.getAttribute("consume30DaysYLableMoney").toString();%>
<%String areaConsume30DaysYLableNum = request.getAttribute("areaConsume30DaysYLableNum").toString();%>
<%String areaConsume30DaysYLableMoney = request.getAttribute("areaConsume30DaysYLableMoney").toString();%>
<%String consume30WeeksYLableNum = request.getAttribute("consume30WeeksYLableNum").toString();%>
<%String consume30WeeksYLableMoney = request.getAttribute("consume30WeeksYLableMoney").toString();%>
<%String consume30MonthsYLableNum = request.getAttribute("consume30MonthsYLableNum").toString();%>
<%String consume30MonthsYLableMoney = request.getAttribute("consume30MonthsYLableMoney").toString();%>
<TABLE>
<!-- consume 30 days-->
<cewolf:chart 
	id="consume30DaysNum" 
	title='<%= GetProperty.getProperties("report.consume.title.num",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=consume30DaysYLableNum%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="consume30DaysChartNum" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="consume30DaysNum" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<cewolf:chart 
	id="consume30DaysMoney" 
	title='<%= GetProperty.getProperties("report.consume.title.money",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=consume30DaysYLableMoney%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="consume30DaysChartMoney" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="consume30DaysMoney" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<!-- end========================================================================================-->

<!-- area consume 30 days-->
<cewolf:chart 
	id="areaConsume30DaysNum" 
	title='<%= GetProperty.getProperties("report.area.consume.title.num",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=areaConsume30DaysYLableNum%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="areaConsume30DaysChartNum" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="areaConsume30DaysNum" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<cewolf:chart 
	id="areaConsume30DaysMoney" 
	title='<%= GetProperty.getProperties("report.area.consume.title.money",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=areaConsume30DaysYLableMoney%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="areaConsume30DaysChartMoney" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="areaConsume30DaysMoney" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<!-- end========================================================================================-->
<!-- consume 30 weeks-->
<cewolf:chart 
	id="consume30WeeksNum" 
	title='<%= GetProperty.getProperties("report.week.consume.title.num",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=consume30WeeksYLableNum%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="consume30WeeksChartNum" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="weekbardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="consume30WeeksNum" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<cewolf:chart 
	id="consume30WeeksMoney" 
	title='<%= GetProperty.getProperties("report.week.consume.title.money",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=consume30WeeksYLableMoney%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="consume30WeeksChartMoney" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="weekbardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="consume30WeeksMoney" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<!-- end========================================================================================-->

<!-- consume 30 months-->
<cewolf:chart 
	id="consume30MonthsNum" 
	title='<%= GetProperty.getProperties("report.month.consume.title.num",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=consume30MonthsYLableNum%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="consume30MonthsChartNum" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="consume30MonthsNum" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<cewolf:chart 
	id="consume30MonthsMoney" 
	title='<%= GetProperty.getProperties("report.month.consume.title.money",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=consume30MonthsYLableMoney%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="consume30MonthsChartMoney" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="consume30MonthsMoney" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<!-- end========================================================================================-->



<!-- @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-->
<!--||+^^^^^+|| -->
<!--||+^^^^^+|| -->
<!--||+^^^^^+|| -->
<!--||+^^^^^+|| -->
<!--||+^^^^^+|| -->
<!-- @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-->
<!-- begin consume -->
<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"></span>
	  </td>
    </tr>
</table>
</div>

<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"><bean:message key="report.consume.title"/></span>
	  </td>
    </tr>

	<tr>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.days"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.date"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.week"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.consume.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.consume.money"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.manage.money"/></td>
	</tr>
	<tbody class="tableBody" >
	<logic:present name="consume30DaysResult" scope="request">
		<logic:iterate id="consume30DaysInfo" name="consume30DaysResult"  indexId="i">
			<tr class="odd"  onmouseover="this.className='highlight'"  onmouseout="this.className='odd'" >
				<td align=center class="data"><div align="center"><bean:write name="consume30DaysInfo" property="sysdate"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="consume30DaysInfo" property="balance_date"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="consume30DaysInfo" property="week"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="consume30DaysInfo" property="tradenum"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="consume30DaysInfo" property="tradeamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="consume30DaysInfo" property="mngamt" format="##,###,##0.00"/></div></td>
			</tr>
		</logic:iterate>
	</logic:present>
	</tbody>
</table>
</div>
<!-- end========================================================================================-->

<!-- begin area consume money and num-->
<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"><bean:message key="report.area.consume.title"/></span>
	  </td>
    </tr>

	<tr>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.days"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.date"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.week"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.hd.money"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.fl.money"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.zj.money"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.hd.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.fl.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.zj.num"/></td>
	</tr>
	<tbody class="tableBody" >
	<logic:present name="areaConsume30DaysResult" scope="request">
		<logic:iterate id="areaConsume30DaysInfo" name="areaConsume30DaysResult"  indexId="i">
			<tr class="odd"  onmouseover="this.className='highlight'"  onmouseout="this.className='odd'" >
				<td align=center class="data"><div align="center"><bean:write name="areaConsume30DaysInfo" property="sysdate"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="areaConsume30DaysInfo" property="balance_date"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="areaConsume30DaysInfo" property="week"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="areaConsume30DaysInfo" property="hdamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="areaConsume30DaysInfo" property="flamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="areaConsume30DaysInfo" property="zjamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="areaConsume30DaysInfo" property="hdnum"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="areaConsume30DaysInfo" property="flnum"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="areaConsume30DaysInfo" property="zjnum"/></div></td>
			</tr>
		</logic:iterate>
	</logic:present>
	</tbody>
</table>
</div>
<!-- end========================================================================================-->

<!-- begin weeks consume -->
<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"><bean:message key="report.week.consume.title"/></span>
	  </td>
    </tr>
	<tr>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.weeks"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.daterange"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.consume.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.consume.money"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.manage.money"/></td>
	</tr>
	<tbody class="tableBody" >
	<logic:present name="consume30WeeksResult" scope="request">
		<logic:iterate id="consume30WeeksInfo" name="consume30WeeksResult"  indexId="i">
			<tr class="odd"  onmouseover="this.className='highlight'"  onmouseout="this.className='odd'" >
				<td align=center class="data"><div align="center"><bean:write name="consume30WeeksInfo" property="sysusedweek"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="consume30WeeksInfo" property="balance_date"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="consume30WeeksInfo" property="tradenum"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="consume30WeeksInfo" property="tradeamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="consume30WeeksInfo" property="mngamt" format="##,###,##0.00"/></div></td>
			</tr>
		</logic:iterate>
	</logic:present>
	</tbody>
</table>
</div>
<!-- end========================================================================================-->
<!-- begin months consume -->
<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"><bean:message key="report.month.consume.title"/></span>
	  </td>
    </tr>
	<tr>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.month"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.consume.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.consume.money"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.manage.money"/></td>
	</tr>
	<tbody class="tableBody" >
	<logic:present name="consume30MonthsResult" scope="request">
		<logic:iterate id="consume30MonthsInfo" name="consume30MonthsResult"  indexId="i">
			<tr class="odd"  onmouseover="this.className='highlight'"  onmouseout="this.className='odd'" >
				<td align=center class="data"><div align="center"><bean:write name="consume30MonthsInfo" property="balance_date"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="consume30MonthsInfo" property="tradenum"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="consume30MonthsInfo" property="tradeamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="consume30MonthsInfo" property="mngamt" format="##,###,##0.00"/></div></td>
			</tr>
		</logic:iterate>
	</logic:present>
	</tbody>
</table>
</div>
<!-- end========================================================================================-->


<!-- saving ************************************************************************************-->
<!-- saving ************************************************************************************-->
<!-- saving ************************************************************************************-->
<%String saving30DaysYLableNum = request.getAttribute("saving30DaysYLableNum").toString();%>
<%String saving30DaysYLableMoney = request.getAttribute("saving30DaysYLableMoney").toString();%>
<%String billSaving30DaysYLableNum = request.getAttribute("billSaving30DaysYLableNum").toString();%>
<%String billSaving30DaysYLableMoney = request.getAttribute("billSaving30DaysYLableMoney").toString();%>
<%String posSaving30DaysYLableNum = request.getAttribute("posSaving30DaysYLableNum").toString();%>
<%String posSaving30DaysYLableMoney = request.getAttribute("posSaving30DaysYLableMoney").toString();%>
<%String savingCompare30WeeksYLableNum = request.getAttribute("savingCompare30WeeksYLableNum").toString();%>
<%String savingCompare30WeeksYLableMoney = request.getAttribute("savingCompare30WeeksYLableMoney").toString();%>
<%String billSaving30WeeksYLableNum = request.getAttribute("billSavingCompare30WeeksYLableNum").toString();%>
<%String billSaving30WeeksYLableMoney = request.getAttribute("billSavingCompare30WeeksYLableMoney").toString();%>
<%String savingCompare30MonthsYLableNum = request.getAttribute("savingCompare30MonthsYLableNum").toString();%>
<%String savingCompare30MonthsYLableMoney = request.getAttribute("savingCompare30MonthsYLableMoney").toString();%>
<%String billSaving30MonthsYLableNum = request.getAttribute("billSavingCompare30MonthsYLableNum").toString();%>
<%String billSaving30MonthsYLableMoney = request.getAttribute("billSavingCompare30MonthsYLableMoney").toString();%>
<!-- saving 30 days-->
<cewolf:chart 
	id="saving30DaysNum" 
	title='<%= GetProperty.getProperties("report.saving.title.num",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=saving30DaysYLableNum%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="saving30DaysChartNum" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="saving30DaysNum" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<cewolf:chart 
	id="saving30DaysMoney" 
	title='<%= GetProperty.getProperties("report.saving.title.money",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=saving30DaysYLableMoney%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="saving30DaysChartMoney" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="saving30DaysMoney" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<!-- billsaving 30 days-->
<cewolf:chart 
	id="billSaving30DaysNum" 
	title='<%= GetProperty.getProperties("report.saving.title.num.bill",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=billSaving30DaysYLableNum%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="billSaving30DaysChartNum" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="billSaving30DaysNum" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<cewolf:chart 
	id="billSaving30DaysMoney" 
	title='<%= GetProperty.getProperties("report.saving.title.money.bill",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=billSaving30DaysYLableMoney%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="billSaving30DaysChartMoney" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="billSaving30DaysMoney" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<!-- end========================================================================================-->

<!-- Pos saving compare 30 days-->
<cewolf:chart 
	id="posSaving30DaysNum" 
	title='<%= GetProperty.getProperties("report.possaving.title.num",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=posSaving30DaysYLableNum%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="posSaving30DaysChartNum" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="posSaving30DaysNum" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<cewolf:chart 
	id="posSaving30DaysMoney" 
	title='<%= GetProperty.getProperties("report.possaving.title.money",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=posSaving30DaysYLableMoney%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="posSaving30DaysChartMoney" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="posSaving30DaysMoney" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<!-- end========================================================================================-->
<!-- saving compare 30 weeks-->
<cewolf:chart 
	id="savingCompare30WeeksNum" 
	title='<%= GetProperty.getProperties("report.saving.week.title.num",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=savingCompare30WeeksYLableNum%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="savingCompare30WeeksChartNum" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="weekbardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="savingCompare30WeeksNum" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<cewolf:chart 
	id="savingCompare30WeeksMoney" 
	title='<%= GetProperty.getProperties("report.saving.week.title.money",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=savingCompare30WeeksYLableMoney%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="savingCompare30WeeksChartMoney" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="weekbardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="savingCompare30WeeksMoney" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<!-- end========================================================================================-->
<!-- billsaving 30 weeks-->
<cewolf:chart 
	id="billSaving30WeeksNum" 
	title='<%= GetProperty.getProperties("report.saving.week.title.num.bill",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=billSaving30WeeksYLableNum%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="billSavingCompare30WeeksChartNum" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="weekbardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="billSaving30WeeksNum" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<cewolf:chart 
	id="billSaving30WeeksMoney" 
	title='<%= GetProperty.getProperties("report.saving.week.title.money.bill",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=billSaving30WeeksYLableMoney%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="billSavingCompare30WeeksChartMoney" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="weekbardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="billSaving30WeeksMoney" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<!-- end========================================================================================-->

<!-- saving compare 30 months-->
<cewolf:chart 
	id="savingCompare30MonthsNum" 
	title='<%= GetProperty.getProperties("report.saving.month.title.num",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=savingCompare30MonthsYLableNum%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="savingCompare30MonthsChartNum" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="savingCompare30MonthsNum" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<cewolf:chart 
	id="savingCompare30MonthsMoney" 
	title='<%= GetProperty.getProperties("report.saving.month.title.money",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=savingCompare30MonthsYLableMoney%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="savingCompare30MonthsChartMoney" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="savingCompare30MonthsMoney" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<!-- end========================================================================================-->
<!-- billsaving 30 weeks-->
<cewolf:chart 
	id="billSaving30MonthsNum" 
	title='<%= GetProperty.getProperties("report.saving.month.title.num.bill",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=billSaving30MonthsYLableNum%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="billSavingCompare30MonthsChartNum" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="billSaving30MonthsNum" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<cewolf:chart 
	id="billSaving30MonthsMoney" 
	title='<%= GetProperty.getProperties("report.saving.month.title.money.bill",getServletContext())%>'
	type="VerticalBar"
	yaxislabel="<%=billSaving30MonthsYLableMoney%>"
	> 
	
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="billSavingCompare30MonthsChartMoney" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="bardataColor">
        <cewolf:param name="0" value='<%= GetProperty.getProperties("chart.customer1",getServletContext()) %>'/>
        <cewolf:param name="1" value='<%= GetProperty.getProperties("chart.customer2",getServletContext()) %>'/>
        <cewolf:param name="2" value='<%= GetProperty.getProperties("chart.customer3",getServletContext()) %>'/>
        <cewolf:param name="3" value='<%= GetProperty.getProperties("chart.customer4",getServletContext()) %>'/>
        <cewolf:param name="4" value='<%= GetProperty.getProperties("chart.customer5",getServletContext()) %>'/>
        <cewolf:param name="5" value='<%= GetProperty.getProperties("chart.customer6",getServletContext()) %>'/>
    </cewolf:chartpostprocessor>
</cewolf:chart>
<cewolf:img 
	chartid="billSaving30MonthsMoney" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'
/>
<!-- end========================================================================================-->


<!-- begin saving 30days -->
<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"><bean:message key="report.saving.title"/></span>
	  </td>
    </tr>
	<tr>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.days"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.date"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.week"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.pos.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.transfer.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.cash.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.pos.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.transfer.num"/></td>
	</tr>
	<tbody class="tableBody" >
	<logic:present name="saving30DaysResult" scope="request">
		<logic:iterate id="saving30DaysInfo" name="saving30DaysResult"  indexId="i">
			<tr class="odd"  onmouseover="this.className='highlight'"  onmouseout="this.className='odd'" >
				<td align=center class="data"><div align="center"><bean:write name="saving30DaysInfo" property="sysdate"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="saving30DaysInfo" property="balance_date"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="saving30DaysInfo" property="week"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="saving30DaysInfo" property="posamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="saving30DaysInfo" property="transferamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="saving30DaysInfo" property="cashamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="saving30DaysInfo" property="posnum"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="saving30DaysInfo" property="transfernum"/></div></td>
			</tr>
		</logic:iterate>
	</logic:present>
	</tbody>
</table>
</div>
<!-- end========================================================================================-->
<!-- begin bill saving 30days -->
<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"><bean:message key="report.saving.title.bill"/></span>
	  </td>
    </tr>
	<tr>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.days"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.date"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.week"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.outlay.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.ticket.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.outlay.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.ticket.num"/></td>
	</tr>
	<tbody class="tableBody" >
	<logic:present name="billSaving30DaysResult" scope="request">
		<logic:iterate id="billSaving30DaysInfo" name="billSaving30DaysResult"  indexId="i">
			<tr class="odd"  onmouseover="this.className='highlight'"  onmouseout="this.className='odd'" >
				<td align=center class="data"><div align="center"><bean:write name="billSaving30DaysInfo" property="sysdate"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="billSaving30DaysInfo" property="balance_date"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="billSaving30DaysInfo" property="week"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="billSaving30DaysInfo" property="outlaymoney" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="billSaving30DaysInfo" property="ticketmoney" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="billSaving30DaysInfo" property="outlaynum"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="billSaving30DaysInfo" property="ticketnum"/></div></td>
			</tr>
		</logic:iterate>
	</logic:present>
	</tbody>
</table>
</div>
<!-- end========================================================================================-->
<!-- begin possaving compare 30days -->
<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"><bean:message key="report.possaving.title"/></span>
	  </td>
    </tr>
	<tr>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.days"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.date"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.week"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.hd.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.hd.money"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.fl.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.fl.money"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.zj.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.area.zj.money"/></td>
	</tr>
	<tbody class="tableBody" >
	<logic:present name="posSaving30DaysResult" scope="request">
		<logic:iterate id="posSaving30DaysInfo" name="posSaving30DaysResult"  indexId="i">
			<tr class="odd"  onmouseover="this.className='highlight'"  onmouseout="this.className='odd'" >
				<td align=center class="data"><div align="center"><bean:write name="posSaving30DaysInfo" property="sysdate"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="posSaving30DaysInfo" property="balance_date"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="posSaving30DaysInfo" property="week"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="posSaving30DaysInfo" property="hdnum"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="posSaving30DaysInfo" property="hdamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="posSaving30DaysInfo" property="flnum"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="posSaving30DaysInfo" property="flamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="posSaving30DaysInfo" property="zjnum"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="posSaving30DaysInfo" property="zjamt" format="##,###,##0.00"/></div></td>
			</tr>
		</logic:iterate>
	</logic:present>
	</tbody>
</table>
</div>
<!-- end========================================================================================-->
<!-- begin saving 30weeks -->
<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"><bean:message key="report.saving.week.title"/></span>
	  </td>
    </tr>
	<tr>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.weeks"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.daterange"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.pos.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.transfer.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.cash.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.pos.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.transfer.num"/></td>
	</tr>
	<tbody class="tableBody" >
	<logic:present name="savingCompare30WeeksResult" scope="request">
		<logic:iterate id="savingCompare30WeeksInfo" name="savingCompare30WeeksResult"  indexId="i">
			<tr class="odd"  onmouseover="this.className='highlight'"  onmouseout="this.className='odd'" >
				<td align=center class="data"><div align="center"><bean:write name="savingCompare30WeeksInfo" property="sysusedweek"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="savingCompare30WeeksInfo" property="balance_date"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="savingCompare30WeeksInfo" property="posamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="savingCompare30WeeksInfo" property="transferamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="savingCompare30WeeksInfo" property="cashamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="savingCompare30WeeksInfo" property="posnum"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="savingCompare30WeeksInfo" property="transfernum"/></div></td>
			</tr>
		</logic:iterate>
	</logic:present>
	</tbody>
</table>
</div>
<!-- end========================================================================================-->
<!-- begin bill saving 30weeks -->
<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"><bean:message key="report.saving.week.title.bill"/></span>
	  </td>
    </tr>
	<tr>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.weeks"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.daterange"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.outlay.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.ticket.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.outlay.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.ticket.num"/></td>
	</tr>
	<tbody class="tableBody" >
	<logic:present name="billSavingCompare30WeeksResult" scope="request">
		<logic:iterate id="billSaving30WeeksInfo" name="billSavingCompare30WeeksResult"  indexId="i">
			<tr class="odd"  onmouseover="this.className='highlight'"  onmouseout="this.className='odd'" >
				<td align=center class="data"><div align="center"><bean:write name="billSaving30WeeksInfo" property="sysusedweek"/></div></td>
				<td align=center class="data"><div align="center"><bean:write name="billSaving30WeeksInfo" property="balance_date"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="billSaving30WeeksInfo" property="outlaymoney" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="billSaving30WeeksInfo" property="ticketmoney" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="billSaving30WeeksInfo" property="outlaynum"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="billSaving30WeeksInfo" property="ticketnum"/></div></td>
			</tr>
		</logic:iterate>
	</logic:present>
	</tbody>
</table>
</div>
<!-- end========================================================================================-->
<!-- begin saving 30months -->
<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"><bean:message key="report.saving.month.title"/></span>
	  </td>
    </tr>
	<tr>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.month"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.pos.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.transfer.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.cash.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.pos.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.transfer.num"/></td>
	</tr>
	<tbody class="tableBody" >
	<logic:present name="savingCompare30MonthsResult" scope="request">
		<logic:iterate id="savingCompare30MonthsInfo" name="savingCompare30MonthsResult"  indexId="i">
			<tr class="odd"  onmouseover="this.className='highlight'"  onmouseout="this.className='odd'" >
				<td align=center class="data"><div align="center"><bean:write name="savingCompare30MonthsInfo" property="balance_date"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="savingCompare30MonthsInfo" property="posamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="savingCompare30MonthsInfo" property="transferamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="savingCompare30MonthsInfo" property="cashamt" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="savingCompare30MonthsInfo" property="posnum"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="savingCompare30MonthsInfo" property="transfernum"/></div></td>
			</tr>
		</logic:iterate>
	</logic:present>
	</tbody>
</table>
</div>
<!-- end========================================================================================-->
<!-- begin bill saving 30months -->
<div class="eXtremeTable" >
<table border="0"  cellspacing="0"  cellpadding="0"  width="100%"  class="tableRegion" >
	<tr>
	  <td height="22" colspan="9" align="center" valign="middle" >
	  		<span class="STYLE1"><bean:message key="report.saving.month.title.bill"/></span>
	  </td>
    </tr>
	<tr>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.month"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.outlay.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.ticket.amt"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.outlay.num"/></td>
		<td class="tableHeader"  style="text-align:center" ><bean:message key="report.saving.ticket.num"/></td>
	</tr>
	<tbody class="tableBody" >
	<logic:present name="billSavingCompare30MonthsResult" scope="request">
		<logic:iterate id="billSaving30MonthsInfo" name="billSavingCompare30MonthsResult"  indexId="i">
			<tr class="odd"  onmouseover="this.className='highlight'"  onmouseout="this.className='odd'" >
				<td align=center class="data"><div align="center"><bean:write name="billSaving30MonthsInfo" property="balance_date"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="billSaving30MonthsInfo" property="outlaymoney" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:message key="money.format"/><bean:write name="billSaving30MonthsInfo" property="ticketmoney" format="##,###,##0.00"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="billSaving30MonthsInfo" property="outlaynum"/></div></td>
				<td align=center class="data"><div align="right"><bean:write name="billSaving30MonthsInfo" property="ticketnum"/></div></td>
			</tr>
		</logic:iterate>
	</logic:present>
	</tbody>
</table>
</div>
<!-- end========================================================================================-->
<!-- begin transferSucceed -->
<%String transferSuccessRateYLabel = request.getAttribute("transferSuccessRateYLabel").toString();%>
<%String transferSuccessAccountYLabel = request.getAttribute("transferSuccessAccountYLabel").toString();%>
<cewolf:chart 
	id="rateLine" 
	title='<%= GetProperty.getProperties("report.transfer.title.rate",getServletContext())%>'
	type="timeseries"
	yaxislabel="<%=transferSuccessRateYLabel%>"
	> 
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="transferRateChart" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="linedataColor">
    </cewolf:chartpostprocessor>

</cewolf:chart>

<cewolf:img 
	chartid="rateLine" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'/>
	
<cewolf:chart 
	id="accountLine" 
	title='<%= GetProperty.getProperties("report.transfer.title.inaccount",getServletContext())%>'
	type="timeseries"
	yaxislabel="<%=transferSuccessAccountYLabel%>"
	> 
	<cewolf:colorpaint color='<%= GetProperty.getProperties("chart.bgcolor",getServletContext())%>'/>
	<cewolf:data>
		<cewolf:producer id="transferAccountChart" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="linedataColor">
    </cewolf:chartpostprocessor>

</cewolf:chart>

<cewolf:img 
	chartid="accountLine" 
	renderer="/cewolf" 
	width='<%= Integer.parseInt(GetProperty.getProperties("chart.barwidth",getServletContext()))%>'
	height='<%= Integer.parseInt(GetProperty.getProperties("chart.barheight",getServletContext()))%>'/>

	
	
	
	