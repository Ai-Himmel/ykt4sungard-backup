<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<%@ page import="org.king.web.util.Constants"%>
<html>
	<head>
		<title>上海复旦大学物料库存及仓储管理系统</title>
		<meta http-equiv="Content-Type" content="text/html;">
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

		<SCRIPT language=javascript>
setTimeout('doInit()',30);
function doInit(){
    var templist = document.all.ec.elements["itemlist"];
    if(templist!=null){
    	for(var i=0;i<templist.length;i++){
        	if(templist[i].type == 'hidden'){
        		templist[i].disabled = true;
        	}
    	}
    }
    var tempS ='<bean:write name="forView"/>';
    if(tempS!=null&&tempS!=''){
    	if(tempS.substring(0,2)=='SB'){
    	alert(tempS+'因为已经报废或者正在维修中，因此不能退货！！');
    	}else{
    	alert(tempS+'因为当前库存为0，因此无法退货！！');
    	}
    }
}
function deleteUntread(){
  var sflag = 0;
  if(document.all.itemlist.checked==true){
    ec.action = "<c:url value="/lf/untreadAction.do"/>?method=deleteUntreadInfo";
	ec.submit();
  }else{
          for(var i=0;i<document.all.itemlist.length;i++){
              if(document.all.itemlist[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag>1){
    ec.action = "<c:url value="/lf/untreadAction.do"/>?method=deleteUntreadInfo";
	ec.submit();
          }else if(sflag<1){
          	  alert("请选择要删除的退货记录！");
          }else{
    ec.action = "<c:url value="/lf/untreadAction.do"/>?method=deleteUntreadInfo";
	ec.submit();
          } 
  }
}
function search(){
    untreadSearchForm.action = "<c:url value="/lf/untreadAction.do"/>?method=loadUntread4RegSearch";
	untreadSearchForm.submit();
}
function addSBUntread(){
    untreadSearchForm.action = "<c:url value="/lf/equipmentAction.do"/>?method=loadSBList4Untread";
	untreadSearchForm.submit();
}
function addYHPUntread(){
    untreadSearchForm.action = "<c:url value="/lf/yhpAction.do"/>?method=loadYHPList4Untread";
	untreadSearchForm.submit();
}
function DoView1(eno){
    if(eno.substring(0,2)=='SB'){
		window.open("../gyf/equipmentAction.do?method=load4view&equipmentNo="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
	}else{
		window.open("../gyf/yhpAction.do?method=load4view&yhpNo="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
	}
}
function DoView2(eno){
	window.open("purDtlAction.do?method=load4PurDtlInfo4Show&purDtlId="+eno+"&tag=1","detailInfo","height=600,width=850,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
}
function DoView3(eno){
	window.open("untreadBillAction.do?method=loadUntreadInfo4Search&untreadId="+eno,"detailInfo","height=600,width=850,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
}
function doUpdate(){
  var sflag = 0;
  if(document.all.itemlist.checked==true){
     ec.action="<c:url value="/lf/untreadBillAction.do"/>?method=loadUntreadInfo4Reg";    
   	 ec.submit();
  }else{
          for(var i=0;i<document.all.itemlist.length;i++){
              if(document.all.itemlist[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag>1){
           
   			  ec.action="<c:url value="/lf/untreadBillAction.do"/>?method=loadUntreadsInfo4Reg";    
   			  ec.submit();
          }else if(sflag<1){
          	  alert("请选择一条要修改的退货记录！");
          }else{
           
   			  ec.action="<c:url value="/lf/untreadBillAction.do"/>?method=loadUntreadInfo4Reg";    
   			  ec.submit();
          } 
}
}
function DoSelectall(){
  if(document.all.itemlist!=null&&document.all.itemlist.length>1){   
       for(var i=0;i<document.all.itemlist.length;i++){
              document.all.itemlist[i].checked=true;
       }
       
  }
  else if(document.all.itemlist!=null){
       document.all.itemlist.checked=true;       
  }
  else{
       alert("当前无记录！");
  }
  

}

function DoNotselectall(){
  
  if(document.all.itemlist!=null&&document.all.itemlist.length>1){   
       for(var i=0;i<document.all.itemlist.length;i++){
              document.all.itemlist[i].checked=false;
       }
       
  }
  else if(document.all.itemlist!=null){
       document.all.itemlist.checked=false;       
  }
  else{
       alert("当前无记录！");
  }
}

function DoReverseselect(){
   
   if(document.all.itemlist!=null&&document.all.itemlist.length>1){   
       for(var i=0;i<document.all.itemlist.length;i++){
           if(document.all.itemlist[i].checked)
              document.all.itemlist[i].checked=false;
           else if(!document.all.itemlist[i].checked)
              document.all.itemlist[i].checked=true;
       }
       
  }
  else if(document.all.itemlist!=null){
      if(document.all.itemlist.checked)
          document.all.itemlist.checked=false; 
      else if(!document.all.itemlist.checked)
          document.all.itemlist.checked=true;    
  }
  else{
       alert("当前无记录！");
  }
  

}
</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" style="padding-left:10px">
		<br>

		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<tr>
				<td align="left" valign="top">

					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td height="25" align="left" valign="top">
								<html:form action="/lf/untreadAction" method="post">
									<table width="150" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr><td width="10" bgcolor="#0066CA">&nbsp;</td>
											<td bgcolor="#0066CA" class="mediumwhite">退货登记</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
										</tr>
									</table>
							</td>
						</tr>
						<tr>
							<td height="40" align="center" valign="top">
								<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>

									<tbody>
										<tr align="center" valign=center>
											<td width="13%" align="left" valign="middle" class="tableHeader2">
												退货登记号
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
												<html:text property="search_untreadId" styleClass="input_box" maxlength="50" />
											</td>
											<td width="13%" align="left" valign="middle" class="tableHeader2">
												经办人
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
												<html:text property="search_rtnPName" styleClass="input_box" maxlength="50" />
											</td>
										</tr>
										<tr align="center" valign=center>
											<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
												登记日期
											</td>
											<td align="left" valign="middle" class="tableHeader3" colspan=3>
												<table border="0" cellspacing="0" cellpadding="0">
													<tr>
														<td>
															<html:text property="search_regTimeStart" styleClass="input_box" maxlength="50" readonly="true" />
														</td>
														<td width="25" align="right">&nbsp;
															<img id="selectregTimeStart" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>"
																border="0" alt="开始日期" style="cursor:pointer">
														</td>
														<td>&nbsp;－&nbsp;</td>
														<td>
															<html:text property="search_regTimeEnd" styleClass="input_box" maxlength="50" readonly="true" />
														</td>
														<td width="25" align="right">&nbsp;
															<img id="selectregTimeEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>"
																border="0" alt="结束日期" style="cursor:pointer">
														</td>
													</tr>
												</table>
											</td>
											
										</tr>
									</tbody>

								</table>
							</td>
						</tr>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<input name="Submit" type="button" class="button_nor" onClick="search()" value="查 询">
								&nbsp;&nbsp;
<input name="Submit2" type="button" class="button_nor" value="重 置" onclick="DoClear()">
							</td>
						</tr>
						</html:form>
						<tr>
							<td height="35" align="center" valign="middle" class="mediumblack">
								退货登记列表
							</td>
						</tr>
						<tr>
							<td height="20" align="center" valign="middle">
								<ec:table items="untreadList" var="untread" rowsDisplayed="10"
									action="untreadAction.do?method=loadUntread4RegSearch">
			    <ec:parameter name="search_untreadId" />
				<ec:parameter name="search_rtnPName" />
				<ec:parameter name="search_regTimeStart" />
				<ec:parameter name="search_regTimeEnd" />
									<ec:exportXls fileName="untreadList.xls" tooltip="导出 Excel" />
									<ec:row>
										<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="50"
											headerStyle="text-align:center" style="text-align: center">
											<input type="checkbox" name="itemlist" value="${untread.materialId}" style="border:0px" />
										</ec:column>
										<ec:column property="materialId" title="退货登记号" headerStyle="text-align:center" style="text-align: center"
											width="70">
											<a href="javascript:DoView3('${untread.materialId}')">${untread.materialId}</a>
										</ec:column>
										<ec:column property="rtnPersonName" title="退货经办人" headerStyle="text-align:center" style="text-align: center"
											width="70" />
										<ec:column property="rcdTime" title="登记日期" cell="date" format="yyyy-MM-dd" headerStyle="text-align:center" style="text-align: center"
											width="60" />
										<ec:column property="purDtlId" title="采购信息" headerStyle="text-align:center" style="text-align: center"
											width="60">
											
											<c:if test="${untread.purDtlId!=''}">
											<a href="javascript:DoView2('${untread.purDtlId}')">
											采购信息
											</a>
											</c:if>
											<c:if test="${untread.purDtlId==''}">
											无
											</c:if>
											
										</ec:column>
										<ec:column property="wlArrivalDtlId" title="物料信息" headerStyle="text-align:center" style="text-align: center"
											width="60">
											<a href="javascript:DoView1('${untread.materialId}')">物料信息</a>
										</ec:column>
									</ec:row>
								</ec:table>
							</td>
						</tr>
						<tr>
						        <td><table width="100%" border="0">
        	<tr>
        		<td height="40" align="left" valign="middle">
          			<input name="selectall" type="button" class="button_nor" value="全 选" onClick="DoSelectall()" >   
          			<input name="notselectall" type="button" class="button_nor" value="全不选" onClick="DoNotselectall()" >
          			<input name="reverseselect" type="button" class="button_nor" value="反 选" onClick="DoReverseselect()" >
        		</td>
							<td height="40" align="right" valign="middle">
								<input name="Submit1" type="button" class="button_nor" value="设备退货" onClick="addSBUntread()">
								<input name="Submit1" type="button" class="button_nor" value="易耗品退货" onClick="addYHPUntread()">
								<input name="Submit3" type="button" class="button_nor" value="修改退货" onClick="doUpdate()">
								<input name="Submit3" type="button" class="button_nor" value="删除退货" onClick="deleteUntread()">
							</td>
										</tr>
		</table></td>
						</tr>
					</table>
				</td>
			</tr>
		</table>

	</body>

</html>
<script>
function DoClear(){
    document.purAppSearchForm.elements["search_untreadId"].value="";
    document.purAppSearchForm.elements["search_rtnPName"].value="";
    document.purAppSearchForm.elements["search_regTimeStart"].value="";
    document.purAppSearchForm.elements["search_regTimeEnd"].value="";
}
</SCRIPT>
<script type="text/javascript">
                new calendar("search_regTimeStart", "selectregTimeStart", "%Y-%m-%d");
                new calendar("search_regTimeEnd", "selectregTimeEnd", "%Y-%m-%d");
           </script>
