<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>上海电大校园一卡通考勤管理系统</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<script type='text/javascript' src='<c:url value="/dwr/engine.js"/>'></script>   
        <script type='text/javascript' src='<c:url value="/dwr/util.js"/>'></script> 
        <script type='text/javascript' src='<c:url value="/dwr/interface/OPT.js"/>'></script>
		<SCRIPT language='javascript'>
	function docheck(){
		if(validate()==false){
            return;
		}
   		document.forms[0].submit();	
	}
	function validate()
	{
		var startDate=document.forms[0].beginDate.value;
		var endDate=document.forms[0].endDate.value;
		
		if(startDate>endDate)
		{		
			alert("开始日期不能大于结束时间");
			return false;
		}
	}
        </SCRIPT>
	</head>
	<%
	String beginDate="";
	if(request.getAttribute("beginDate")!=null){
		beginDate = request.getAttribute("beginDate").toString();
	}else if(session.getAttribute("beginDate")!=null){
	    beginDate = session.getAttribute("beginDate").toString();
	}
	String endDate="";
	if(request.getAttribute("endDate")!=null){
		endDate = request.getAttribute("endDate").toString();
	}else if(session.getAttribute("endDate")!=null){
	   endDate = session.getAttribute("endDate").toString();
	}
    %>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 教室用电处理日志 </font> </strong>
		</div>
		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
			<jodd:form bean="request">
				<html:form action="transperson.do?method=transPersonList" method="post" >
				 <tr> 
				   <td>
				   &nbsp;校  区
                    <html:select property="schoolarea">
                        <html:option value="">请选择</html:option>
                        <html:options collection="areaList" property="areaCode" labelProperty="areaName"/>
                    </html:select>
                   </td> 
            		 <td>
					&nbsp; 开始日期
					<html:text property="beginDate" size="10"  readonly="readonly" value="<%=beginDate%>"/>			
					<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
					</td>
					 <td>
					&nbsp; 结束日期
					<html:text property="endDate" size="10"  readonly="readonly" value="<%=endDate%>"/>
					<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
					<script type="text/javascript">
		                new calendar("beginDate", "calBegin", "%Y%m%d");
		                new calendar("endDate", "calEnd", "%Y%m%d");
            		</script>
            		</td>
            		<td>
					<input name="Submit" width="50" type="button" class="button_nor" value="查  询" onclick="docheck()">
					</td>
					</tr>
				</html:form>
			</jodd:form>
		</div>
	
		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
				<td height="40" align="left" valign="middle" class="tdborder02">
					
					&nbsp;&nbsp;&nbsp;
					
				</td>
			</tr>
		</table>	
		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<ec:table items="transpersonList" var="person"  rowsDisplayed="50"
			    action="transperson.do?method=transPersonList"
			    locale="zh_CN"
			       filterable="false"
			    >
				<ec:exportXls fileName="transperson.xls"  tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="areaname"  title="校区" width="17%" sortable="false"   />
					<ec:column property="build" title="楼宇" width="17%"  />
					<ec:column property="roomname" title="教室" width="17%" />
					<ec:column property="updatedate" title="处理日期" width="17%"/>
					<ec:column property="updatetime" title="处理时间" width="17%" />
					<ec:column property="personname" title="处理人" width="15%" />
				</ec:row>
			</ec:table>
		</div>
		
	</body>
</html>

