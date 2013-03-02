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
   document.forms[0].submit();
	
}
function checkselect(){
	var len = document.getElementsByName("item").length; 
    var retstr = ""; 
    for (i = 0; i < len; i++) 
    { 
        if (document.getElementsByName("item")[i].checked == true) 
        {   
            retstr = retstr + document.getElementsByName("item")[i].value +","; 
        } 
    } 
    return retstr;
}

function doTrans(){
 
   var sflag=0;
   
   if(document.all.item.length>1){
          for(var i=0;i<document.all.item.length;i++){
              if(document.all.item[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag==0){
              alert("请选择要处理的记录！");
              return;
          } 
   }
   else{
        if(!document.all.item.checked){
              alert("请选择要处理的记录！");
              return;        
        }
   }
   if(confirm("您确定要处理此记录吗？")){
       document.reportForm.action="roomTrans.do?method=roomTrans&para="+checkselect();
       document.reportForm.submit();
       
   }else
	   return;
}
</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 当日上课教室用电处理 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
			<jodd:form bean="request">
				<html:form action="roomTrans.do?method=roomTransList" method="post" >
				 <tr> 
				   <td>
				   &nbsp;校  区
                    <html:select property="schoolarea">
                        <html:option value="">请选择</html:option>
                        <html:options collection="areaList" property="areaCode" labelProperty="areaName"/>
                    </html:select>
                   </td> 
            		<td>&nbsp;</td>
            		<td>&nbsp;</td>
            		<td>&nbsp;</td>
            		<td>
					<input name="Submit" width="50" type="button" class="button_nor" value="查  询" onclick="docheck();">
					</td>
					</tr>
				</html:form>
			</jodd:form>
		</div>
	
		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
				<td height="40" align="left" valign="middle" class="tdborder02">
					
					&nbsp;&nbsp;&nbsp;
					
					<input name="sub" type="button" class="submitButton" value="处   理" onclick="doTrans();">
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
			<ec:table items="roomTransList" var="roomtrans"  rowsDisplayed="50"
			    action="roomTrans.do?method=roomTransList"
			    locale="zh_CN"
			       filterable="false"
			    >
				<ec:exportXls fileName="roomelec.xls"  tooltip="导出 Excel" />
				<ec:row>
				    <ec:column property="checkbox" title="选择"  sortable="false" viewsAllowed="html" width="5%" style="text-align: center">
							<input type="checkbox" name="item" value="${roomtrans.serialno}"  style="border:0px" />
					</ec:column>
					<ec:column property="areaname"  title="校区" width="17%" sortable="false" />
					<ec:column property="build" title="楼宇" width="17%"  />
					<ec:column property="roomname" title="教室" width="17%" />
					<ec:column property="usedate" title="上课日期" width="10%"  />
					<ec:column property="begintime" title="开始时间" width="10%"  />
					<ec:column property="endtime" title="结束时间" width="10%"  />
					<ec:column property="statename" title="用电状态" width="14%" sortable="false" />
				</ec:row>
			</ec:table>
		</div>
		
		                     
	</body>
</html>
<SCRIPT language='javascript'>
function docheck(){
    document.forms[0].submit();
}
function renderRow(row) {
    switch (row.cells[7].innerText) {
        case "超时未断电":
            row.cells[7].style.background= "#FE3E00";
            break;
    }
}
window.setInterval(docheck , 60000);
renderTable('ec_table');
</SCRIPT>

