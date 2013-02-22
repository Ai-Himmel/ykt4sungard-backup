<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
<head>
<title>上海复旦大学物料库存及仓储管理系统</title>
<meta http-equiv="Content-Type" content="text/html;">

<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<link href="<c:url value="/pages/styles/extremecomponents.css"/>" rel="stylesheet" type="text/css">
<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

<SCRIPT language=javascript>
function pass(){
   wlArrivalDtlBillForm.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=checkPass";    
   wlArrivalDtlBillForm.submit();
}
function noPass(){
   wlArrivalDtlBillForm.action="<c:url value="/lf/wlArrivalDtlAction.do"/>?method=checkNoPass";    
   wlArrivalDtlBillForm.submit();
}
function back(){
 	wlArrivalDtlBillForm.action = "<c:url value="/lf/wlArrivalDtlAction4Search.do"/>?method=loadWlArrivalDtlList4Check";
	wlArrivalDtlBillForm.submit();
}
function openOrCloseOpt(opts_id,opt_id)
{
      var optDiv = document.getElementById('opt_div_'+opts_id+'_'+opt_id);
      if(optDiv!=null){
	  if(optDiv.style.display=="none"){
	    optDiv.style.display="inline";
	    document.getElementById('opt_'+opt_id).src='<c:url value="/pages/style/default/images/title_close.gif"/>';
	  }else{
	    optDiv.style.display="none";
	    document.getElementById('opt_'+opt_id).src='<c:url value="/pages/style/default/images/title_open.gif"/>';
         }
       }
}
function DoSelectall(){
  if(document.all.apiItemList!=null&&document.all.apiItemList.length>1){   
       for(var i=0;i<document.all.apiItemList.length;i++){
              document.all.apiItemList[i].checked=true;
       }
       
  }
  else if(document.all.apiItemList!=null){
       document.all.apiItemList.checked=true;       
  }
  else{
       alert("当前无记录！");
  }
  

}

function DoNotselectall(){
  
  if(document.all.apiItemList!=null&&document.all.apiItemList.length>1){   
       for(var i=0;i<document.all.apiItemList.length;i++){
              document.all.apiItemList[i].checked=false;
       }
       
  }
  else if(document.all.apiItemList!=null){
       document.all.apiItemList.checked=false;       
  }
  else{
       alert("当前无记录！");
  }
}

function DoReverseselect(){
   
   if(document.all.apiItemList!=null&&document.all.apiItemList.length>1){   
       for(var i=0;i<document.all.apiItemList.length;i++){
           if(document.all.apiItemList[i].checked)
              document.all.apiItemList[i].checked=false;
           else if(!document.all.apiItemList[i].checked)
              document.all.apiItemList[i].checked=true;
       }
       
  }
  else if(document.all.apiItemList!=null){
      if(document.all.apiItemList.checked)
          document.all.apiItemList.checked=false; 
      else if(!document.all.apiItemList.checked)
          document.all.apiItemList.checked=true;    
  }
  else{
       alert("当前无记录！");
  }
  

}
</SCRIPT>

</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>

		<table width="99%" border="0" align="left" cellpadding="0" cellspacing="0" style="padding-left:10px">
			<tr>
				<td align="left" valign="top">

					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td height="25" align="left" valign="top">
<html:form action="/lf/wlArrivalDtlAction" method="post">
<jodd:form bean="request">
            <input type="hidden" name="ec_i" />
            <input type="hidden" name="ec_p" />
            <input type="hidden" name="ec_crd" />
            <input type="hidden" name="search_dlid" />
            <input type="hidden" name="search_xlid" />
            <input type="hidden" name="search_wlid" />     
            <input type="hidden" name="search_wlxh" />
            <input type="hidden" name="search_ifAppendix" />
            <input type="hidden" name="search_dtlState" />
            <input type="hidden" name="search_producterId" />     
            <input type="hidden" name="search_providerId" />	
</jodd:form>
									<table width="150" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">到货安置列表</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
										</tr>
									</table>
							</td>
						</tr>
						<tr>
							<td height="40" align="center" valign="top">
								<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
		<html:hidden property="wlArrivalId" styleClass="input_box"/>
		<html:hidden property="wlArrivalDtlId" styleClass="input_box"/>
									<tbody>
										<tr align="center" valign=center>
											<td width="13%" class="tableHeader2">
												物料名称
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
											<bean:write name="wlArrivalDtlBillForm" property="wlmc"/>
												
											</td>
											<td width="13%" class="tableHeader2">
												物料规格
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
											<bean:write name="wlArrivalDtlBillForm" property="wlsption"/>
												
											</td>
										</tr>
										<tr align="center" valign=center>
											<td width="13%" class="tableHeader2">
												物料来源
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
												<table border="0" cellspacing="0" cellpadding="0">
													<tr>
														<td>
														<bean:write name="wlArrivalDtlBillForm" property="mtlSource"/>
															
														</td>

														<td width="25" align="right"></td>
													</tr>
												</table>
											</td>
											<td width="13%" class="tableHeader2">
												物料型号
											</td>
											<td width="37%" align="left" valign="middle" class="tableHeader3">
												<table border="0" cellspacing="0" cellpadding="0">
													<tr>
														<td>
														<bean:write name="wlArrivalDtlBillForm" property="wlmodel"/>
															
														</td>
														<td width="25" align="right">
															&nbsp;
														</td>
													</tr>
												</table>
											</td>
										</tr>
									</tbody>

								</table>
							</td>
						</tr>
<input name="checkMemo" type="hidden" value="">
						</html:form>
						<tr>
							<td height="35" align="center" valign="middle" class="mediumblack">
							</td>
						</tr>

      <tr>
        <td height="20" align="center" valign="middle" colspan="2">
        <ec:table items="allocationInfoList" var="allocationInfo" rowsDisplayed="10" action="wlArrivalDtlAction.do?method=loadAllocationList4Reg" >
								
				<ec:exportXls fileName="allocationInfoList" tooltip="导出 Excel" />
				<ec:row>
				    <ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="50" headerStyle="text-align:center" style="text-align: center">
						<input type="checkbox" name="apiItemList" value="${allocationInfo.alId}" style="border:0px"/>
					</ec:column>
					<ec:column property="xqName" title="校区" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="bdName" title="楼宇" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="80" 
					/>
					<ec:column property="rmName" title="房间" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					/>
					<ec:column property="placeNum" title="安置数量" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="60" 
					/>
					<ec:column property="managerName" title="管理员" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					/>
					<ec:column property="state" title="安置状态" 
					    headerStyle="text-align:center" 
					    style="text-align: center"
					    width="130" 
					    
					/>
				</ec:row>
			</ec:table></td>
      </tr>
      <form name="tempForm" action="" method="post">
      <tr>
              <td height="40" align="right" valign="middle">
         <table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign=center>
              <td width="12%" align="left" valign="middle" class="tableHeader2" >审批意见</td>
              <td width="88%" align="left" valign="middle" class="tableHeader3" >
                  <textarea name="checkOpinion" cols="75" onchange="javascript:document.wlArrivalDtlBillForm.checkMemo.value=this.value;"></textarea>
              </td>
              </tr>
          </tbody>
        </table>
</td>
</tr>
    </form>  
      <tr>
              <td><table width="99%" border="0">
        	<tr>
        		<td height="40" align="left" valign="middle">
          			<input name="selectall" type="button" class="button_nor" value="全 选" onClick="DoSelectall()" >   
          			<input name="notselectall" type="button" class="button_nor" value="全不选" onClick="DoNotselectall()" >
          			<input name="reverseselect" type="button" class="button_nor" value="反 选" onClick="DoReverseselect()" >
        		</td>
        <td height="40" align="right" valign="middle" colspan="2">
         
          <input name="Submit1" type="button" class="button_nor" value="通 过"  onClick="pass()">
<input name="Submit3" type="button" class="button_nor" value="不通过" onClick="noPass()">
 <input name="Submit31" type="button" class="button_nor" value="返 回" onClick="back()"></td>

			</tr>
		</table></td>
      </tr>
    </table></td>
  </tr>
     <tr>
  <td>
<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
<tr>
<td width="12%" align="center" valign="middle" class="tableHeader2" >审批日志:</td>
<td width="88%" align="left"><img onmouseover="this.style.cursor='hand';" id="opt_367628" src="<c:url value="/pages/style/default/images/title_open.gif"/>" onclick="openOrCloseOpt(105295,367628)" /></img></td>
</tr>
<tr><td colspan="2" height="10px"><td width="1"></tr>
<tr>
<td colspan="2">
<div id="opt_div_105295_367628" style="display:none">
<table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#3F738B bordercolordark=#ffffff id=submenu1> 
          <tbody>
<tr width="50" align="center">
    <td width="12%" valign="middle" class="tableHeader"><strong>审批人</strong></td>
    <td width="12%" valign="middle" class="tableHeader"><strong>审批结果</strong></td>
	<td width="58%" valign="middle" class="tableHeader"><strong>审批意见</strong></td>
	<td width="18%" valign="middle" class="tableHeader"><strong>审批时间</strong></td>
</tr>	
			   
<logic:present name="checkProcessList" scope="request">
	<logic:iterate name="checkProcessList" id="checkProcess" type="java.util.Map">
		<tr align="center">
			<td><bean:write name="checkProcess" property="checkPerson"/></td>
			<td><bean:write name="checkProcess" property="checkResult"/></td>
			<td><bean:write name="checkProcess" property="checkMemo"/></td>
			<td><bean:write name="checkProcess" property="checkTime" format="yyyy-MM-dd"/></td>
		</tr>
	</logic:iterate>
</logic:present>
 </tbody>
</table>
</div></td>
</tr>
</table>
  </td>
  </tr>
</table>
</body>
</html>
