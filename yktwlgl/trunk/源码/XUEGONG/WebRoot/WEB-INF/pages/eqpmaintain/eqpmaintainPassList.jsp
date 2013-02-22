<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
	<head>
		<title>上海复旦大学物料库存及仓储管理系统</title>

		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/eqpmaintainAction.do?method=search4passList" method="post">

			<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td align="left" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td height="25" align="left" valign="top">
									<table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">
												维修情况登记
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="center" valign="top">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<tbody>
											<tr align="center" valign=center>
												<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													设备编号
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_bh" styleClass="input_box" maxlength="32" />
												</td>
												<td width="20%" lign="left" valign="middle" class="tableHeader2">
													设备资产号
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_zch" styleClass="input_box" maxlength="50" />
												</td>
												<td width="15%" align="left" valign="middle" class="tableHeader2">
													设备序列号
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_xlh" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													设备大类
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_wldl" styleClass="select01" onchange="changeXl(this)">
														<html:option value="">请选择	</html:option>
														<html:options collection="dllist" labelProperty="dlmc" property="id" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													设备小类
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_wlxl" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="xllist" labelProperty="xlmc" property="id" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													设备名称
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_wlmc" styleClass="input_box" maxlength="100" />
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													故障原因
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_gzyy" styleClass="input_box" maxlength="100" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													维修商
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_wxs" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="wxslist" labelProperty="companyName" property="id" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													是否完成
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_done" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:option value="1">是</html:option>
														<html:option value="0">否</html:option>
													</html:select>
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													申请人
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_sqr" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													申请日期从
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_sqrqc" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_sqrqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="开始日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<td align="right" valign="middle" class="tableHeader2">
													申请日期到
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_sqrqd" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_sqrqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="结束日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
											</tr>
											<script type="text/javascript">
                new calendar("search_sqrqc", "select_sqrqc", "%Y-%m-%d");
                new calendar("search_sqrqd", "select_sqrqd", "%Y-%m-%d");
           </script>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">
									<input name="Submit" type="submit" class="button_nor" value="查 询">
									&nbsp;
									<input name="Submit2" type="button" class="button_nor" value="重 置" onclick="DoClear()">
								</td>

							</tr>
							<logic:present name="msg" scope="request">
								<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
							</logic:present>
							<logic:notPresent name="msg" scope="request">
								<input name="hmsg" type="hidden" value="">
							</logic:notPresent>
							<logic:present name="nccols" scope="request">
								<input name="hnccols" type="hidden" value="<bean:write name="nccols" />">
							</logic:present>
							<logic:notPresent name="nccols" scope="request">
								<input name="hnccols" type="hidden" value="">
							</logic:notPresent>
							<logic:present name="ncdispatch" scope="request">
								<input name="hncdispatch" type="hidden" value="<bean:write name="ncdispatch" />">
							</logic:present>
							<logic:notPresent name="ncdispatch" scope="request">
								<input name="hncdispatch" type="hidden" value="">
							</logic:notPresent>
							<logic:present name="ncupdate" scope="request">
								<input name="hncupdate" type="hidden" value="<bean:write name="ncupdate" />">
							</logic:present>
							<logic:notPresent name="ncupdate" scope="request">
								<input name="hncupdate" type="hidden" value="">
							</logic:notPresent>
							</html:form>

							<tr>
								<td height="35" align="center" valign="middle" class="mediumblack">
									设备维修列表
								</td>
							</tr>

							<tr>
								<td height="20" align="center" valign="middle">
									<ec:table items="eqplist" var="eqpJBInfo" autoIncludeParameters="false" rowsDisplayed="10" action="eqpmaintainAction.do?method=search4passList">

										<ec:parameter name="search_bh" />
										<ec:parameter name="search_zch" />
										<ec:parameter name="search_xlh" />
										<ec:parameter name="search_wldl" />
										<ec:parameter name="search_wlxl" />
										<ec:parameter name="search_wlmc" />
										<ec:parameter name="search_gzyy" />
										<ec:parameter name="search_wxs" />
										<ec:parameter name="search_done" />
										<ec:parameter name="search_sqr" />
										<ec:parameter name="search_sqrqc" />
										<ec:parameter name="search_sqrqd" />

										<ec:exportXls fileName="eqpmaintainList.xls" tooltip="导出 Excel" />
										<ec:row>
											<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" headerStyle="text-align:center" style="text-align: left">
												<input type="checkbox" name="cbgroup" value="${eqpJBInfo.id}" style="border:0px" onClick="doSel(this)" />
											</ec:column>
											<ec:column property="equipmentNo" title="查看" headerStyle="text-align:center" style="text-align: left" width="80">
											<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')"><font color="green">查看</font></a>
												</c:if>
												<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')"><font color="green">查看</font></a>
												</c:if>	
										
										</c:when>
				                        </c:choose>
				                  
												<c:choose>
										<c:when test="${eqpJBInfo.doneName!='是'}">
											<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')">查看</a>
												</c:if>
												<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
												<a href="javascript:DoView('${eqpJBInfo.id}')">查看</a>
												</c:if>	
										
										</c:when>
				                        </c:choose>											
											</ec:column>	
											<ec:column property="assetNo" title="设备标识" headerStyle="text-align:center" style="text-align: left" width="80">
														<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
										<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
											<font color="green"><a href="javascript:DoViewEqp('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.equipmentNo}</a></font>
												</c:if>
												<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
												<font color="green"><a href="javascript:DoViewEqp('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.assetNo}</a></font>
												</c:if>		
										</c:when><c:otherwise>
										<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
										<a href="javascript:DoViewEqp('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.equipmentNo}</a>
										</c:if>
										<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
										<a href="javascript:DoViewEqp('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.assetNo}</a>
										</c:if>	
										</c:otherwise>
				                        </c:choose>
				                  
				                        </ec:column>
																					
											<ec:column property="wlmc" title="名称" headerStyle="text-align:center" style="text-align: left" width="110" >
											<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<font color="green">${eqpJBInfo.wlmc}</font>
										</c:when>
				                        </c:choose>
				                      
				                        </ec:column>
											<ec:column property="managerName" title="管理员" headerStyle="text-align:center" style="text-align: left" width="60" >
													<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<font color="green">${eqpJBInfo.managerName}</font>
										</c:when>
				                        </c:choose>
				                        <c:choose>
										<c:when test="${eqpJBInfo.doneName==''}">
											${eqpJBInfo.managerName}
										</c:when>
				                        </c:choose>
				                        </ec:column>
				                        
											<ec:column property="maintainReason" title="故障原因" headerStyle="text-align:center" style="text-align: left" width="100" >
													<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<font color="green">${eqpJBInfo.maintainReason}</font>&nbsp;
										</c:when>
				                        </c:choose>
				                       
				                        </ec:column>
											<ec:column property="maintainerName" title="维修商" headerStyle="text-align:center" style="text-align: left" width="110" >
													<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<font color="green">${eqpJBInfo.maintainerName}</font>&nbsp;
										</c:when>
				                        </c:choose>
				                     
				                        </ec:column>
											<ec:column property="beginDate" title="开始" headerStyle="text-align:center" style="text-align: left" width="50" >
													<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<font color="green">${eqpJBInfo.beginDate}</font>&nbsp;
										</c:when>
				                        </c:choose>
				                        
				                        </ec:column>
											<ec:column property="endDate" title="结束" headerStyle="text-align:center" style="text-align: left" width="50" >
													<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<font color="green">${eqpJBInfo.endDate}</font>&nbsp;
										</c:when>
				                        </c:choose>
				                      
				                        </ec:column>
											<%if (request.getAttribute("ifLimit").equals("0")) {%>
											<ec:column property="maintainPrice" title="金额" headerStyle="text-align:center" style="text-align: left" width="50" >
													<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<font color="green">${eqpJBInfo.maintainPrice}</font>&nbsp;
										</c:when>
				                        </c:choose>
				                        
				                        </ec:column>
											<%}%>
											<ec:column property="doneName" title="完成" headerStyle="text-align:center" style="text-align: left" width="40" >
													<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<font color="green">${eqpJBInfo.doneName}</font>&nbsp;
										</c:when>
				                        </c:choose>
				                      
				                        </ec:column>
				                        <ec:column property="applyPersonName" title="申请人" headerStyle="text-align:center" style="text-align: left" width="60" >
													<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<font color="green">${eqpJBInfo.applyPersonName}</font>&nbsp;
										</c:when>
				                        </c:choose>
				                        </ec:column>
											<ec:column property="updatorName" title="更新人" headerStyle="text-align:center" style="text-align: left" width="60" >
													<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<font color="green">${eqpJBInfo.updatorName}</font>&nbsp;
										</c:when>
				                        </c:choose>
				                     
				                        </ec:column>
											<ec:column property="updateTime" title="更新日期" headerStyle="text-align:center" style="text-align: left" width="80" >
													<c:choose>
										<c:when test="${eqpJBInfo.doneName=='是'}">
											<font color="green"><bean:write name="eqpJBInfo" property="updateTime" format="yyyy-MM-dd"/></font>&nbsp;
										</c:when><c:otherwise>
										<bean:write name="eqpJBInfo" property="updateTime" format="yyyy-MM-dd"/>
										</c:otherwise>
				                        </c:choose>
				                      
				                        </ec:column>
										</ec:row>
									</ec:table>
								</td>
							</tr>
							<%if (((java.util.ArrayList) request.getAttribute("eqplist")).size() > 0) {%>
							<tr>
								<td height="40" align="left" valign="middle">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<tbody>
											<tr align="center" valign=center>
												<td height="40" align="left" valign="middle">
													<input name="selectall" type="button" class="button_nor" value="全 选" onClick="DoSelectall()">
													<input name="notselectall" type="button" class="button_nor" value="全不选" onClick="DoNotselectall()">
													<input name="reverseselect" type="button" class="button_nor" value="反 选" onClick="DoReverseselect()">
												</td>
												<td height="40" align="right" valign="middle">
													<input name="bupdate" type="button" class="button_nor" value="维修情况登记" onClick="DoUpdate()">
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<%}%>

						</table>
					</td>
				</tr>
			</table>
	</body>
</html>

<SCRIPT language=javascript>

setTimeout('init()',10);
function init(){
       
  if(document.eqpmaintainForm.hmsg.value=='9')
      alert("请勿重复保存！");
  if(document.eqpmaintainForm.hmsg.value=='dok')
       alert("删除成功！");
  else if(document.eqpmaintainForm.hmsg.value=='dfail')
       alert("删除失败！");
  if(document.eqpmaintainForm.hnccols.value!='')
       alert(document.eqpmaintainForm.hnccols.value+" 非最新维修记录或存在审核中或已审核的设备维修申请，不能删除！");
  if(document.eqpmaintainForm.hncdispatch.value!='')
       alert(document.eqpmaintainForm.hncdispatch.value+" 维修审核尚未结束或设备已在维修中，暂时不能再次申请维修！");
  if(document.eqpmaintainForm.hncupdate.value!=''){
       alert("修改"+document.eqpmaintainForm.hncupdate.value+"条维修记录！");
       alert("一个设备只能修改最新的维修记录，若维修申请在审核中或已审核通过，不能修改！");
   }
}  

function zchSetup(sel){

   alert(sel.value);

}
function doSel(sel){
//alert(sel.value);
}

function DoSelectall(){

  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=true;       
  }
  else{
       alert("当前无记录！");
  }
  

}

function DoNotselectall(){
  
  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=false;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=false;       
  }
  else{
       alert("当前无记录！");
  }

}

function DoReverseselect(){
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
           if(document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=false;
           else if(!document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
      if(document.all.cbgroup.checked)
          document.all.cbgroup.checked=false; 
      else if(!document.all.cbgroup.checked)
          document.all.cbgroup.checked=true;    
  }
  else{
       alert("当前无记录！");
  }
  

}

function DoUpdate(){
 
   var sflag=0;
   var ids="";
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1; 
                   ids=ids+document.all.cbgroup[i].value+",";                                                 
              }
          }           
         if(sflag==0){
              alert("请选择要修改的设备维修记录！");
              return;
          } 
   }
   else{
        if(document.all.cbgroup.checked){
              ids=ids+document.all.cbgroup.value+","; 
              sflag=sflag+1;     
        }
        else{
            alert("请选择要修改的设备维修记录！");
            return;   
        }            
   }
   
   document.forms.ec.action="eqpmaintainAction.do?method=load4passupdate&idset="+ids.substring(0,ids.length-1)+"&idcount="+sflag;     
   document.forms.ec.submit();
   
  
  
}

function DoView(eno){

    window.open("eqpmaintainAction.do?method=load4view&maintainId="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function DoViewEqp(eno){

    window.open("equipmentAction.do?method=load4view&equipmentNo="+eno,"detailInfo","height=600,width=1000,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function DoClear(){

    document.eqpmaintainForm.elements["search_bh"].value="";
    document.eqpmaintainForm.elements["search_zch"].value="";    
    document.eqpmaintainForm.elements["search_xlh"].value="";
    
    document.eqpmaintainForm.elements["search_wldl"].value="";
    document.eqpmaintainForm.elements["search_wlxl"].value="";
    document.eqpmaintainForm.elements["search_wlmc"].value="";
    
    document.eqpmaintainForm.elements["search_done"].value="";
    document.eqpmaintainForm.elements["search_gzyy"].value="";
    document.eqpmaintainForm.elements["search_wxs"].value="";
        
    document.eqpmaintainForm.elements["search_sqr"].value="";
    document.eqpmaintainForm.elements["search_sqrqc"].value="";
    document.eqpmaintainForm.elements["search_sqrqd"].value="";
            
}

</SCRIPT>

