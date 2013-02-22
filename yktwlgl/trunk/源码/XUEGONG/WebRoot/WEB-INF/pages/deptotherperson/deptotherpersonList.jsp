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
		<%String jaddNum = request.getAttribute("addNum") == null ? ""
					: (String) request.getAttribute("addNum");
%>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/deptOtherPersonAction.do?method=search4List" method="post">

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
												部门外部人员设置
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="center" valign="top">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<input type="hidden" name="formName" value="<%=request.getAttribute("formName")==null?"":request.getAttribute("formName")%>">
										<tbody>
											<input type="hidden" name="addNum" value="<%=request.getAttribute("addNum")==null?"":request.getAttribute("addNum")%>">
											<input type="hidden" name="updateid" value="">
											<input type="hidden" name="noNew" value="<%=request.getAttribute("noNew")==null?"0":request.getAttribute("noNew")%>">
											<tr align="center" valign=center>
												<td width="20%" align="right" valign="middle" class="tableHeader2">
													人员姓名
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_otherpersonname" styleClass="input_box" maxlength="100" />
												</td>
												<td width="20%" align="right" valign="middle" class="tableHeader2">
													状态
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:select property="search_otherpersonstate" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="mcztlist" labelProperty="ztName" property="ztCode" />
													</html:select>
												</td>
											</tr>
											<tr align="center" valign=center>
												<td width="20%" align="right" valign="middle" class="tableHeader2">
													人员部门
												</td>
												<td width="80%" align="left" valign="middle" class="tableHeader3" colspan="3">
													<html:select property="search_otherpersondept" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="deptlist" labelProperty="deptName" property="deptCode" />
													</html:select>
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">

									<input name="Submit" type="button" class="button_nor" value="查 询" onclick="DoFind()">
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
							<logic:present name="repeatSet" scope="request">
								<input name="hrepeatSet" type="hidden" value="<bean:write name="repeatSet" />">
							</logic:present>
							<logic:notPresent name="repeatSet" scope="request">
								<input name="hrepeatSet" type="hidden" value="">
							</logic:notPresent>
							<input type="hidden" name="ec_p" value="<%=request.getParameter("ec_p")==null?"1":request.getParameter("ec_p")%>">
							<input type="hidden" name="ec_i" value="<%=request.getParameter("ec_i")==null?"":request.getParameter("ec_i")%>">
							<input type="hidden" name="ec_crd" value="<%=request.getParameter("ec_crd")==null?"":request.getParameter("ec_crd")%>">
							</html:form>

							<tr>
								<td height="35" align="center" valign="middle" class="mediumblack">
									部门中已设置的外部人员列表
								</td>
							</tr>
							<jodd:form bean="request">
								<tr>
									<td height="20" align="center" valign="middle">
										<ec:table items="otherpersonlist" var="otherperson" autoIncludeParameters="false" rowsDisplayed="10" action="deptOtherPersonAction.do?method=search4List">

											<ec:exportXls fileName="otherpersonList.xls" tooltip="导出 Excel" />
											<ec:parameter name="search_otherpersondept" />
											<ec:parameter name="search_otherpersonname" />
											<ec:parameter name="search_otherpersonstate" />
											<ec:parameter name="formName" />
											<ec:parameter name="addNum" />
											<ec:row>
												<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" headerStyle="text-align:center" style="text-align: left">
													<input type="checkbox" name="cbgroup" value="${otherperson.idmc}" style="border:0px" />
												</ec:column>
												<ec:column property="personName" title="姓名" headerStyle="text-align:center" style="text-align: left" width="80">
													<c:choose>
														<c:when test="${otherperson.state=='02'}">
															<font color="#A8A8A8">${otherperson.personName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${otherperson.state=='00'}">
															<font color="#FF9999">${otherperson.personName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="employeeNo" title="工号" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${otherperson.state=='02'}">
															<font color="#A8A8A8">${otherperson.employeeNo}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${otherperson.state=='00'}">
															<font color="#FF9999">${otherperson.employeeNo}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="genderName" title="性别" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${otherperson.state=='02'}">
															<font color="#A8A8A8">${otherperson.genderName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${otherperson.state=='00'}">
															<font color="#FF9999">${otherperson.genderName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="telephone" title="电话" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${otherperson.state=='02'}">
															<font color="#A8A8A8">${otherperson.telephone}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${otherperson.state=='00'}">
															<font color="#FF9999">${otherperson.telephone}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="mobilePhone" title="手机" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${otherperson.state=='02'}">
															<font color="#A8A8A8">${otherperson.mobilePhone}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${otherperson.state=='00'}">
															<font color="#FF9999">${otherperson.mobilePhone}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="emailAddress" title="邮件" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${otherperson.state=='02'}">
															<font color="#A8A8A8">${otherperson.emailAddress}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${otherperson.state=='00'}">
															<font color="#FF9999">${otherperson.emailAddress}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="deptName" title="部门" headerStyle="text-align:center" style="text-align: left" width="150">
													<c:choose>
														<c:when test="${otherperson.state=='02'}">
															<font color="#A8A8A8">${otherperson.deptName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${otherperson.state=='00'}">
															<font color="#FF9999">${otherperson.deptName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="stateName" title="状态" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${otherperson.state=='02'}">
															<font color="#A8A8A8">${otherperson.stateName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${otherperson.state=='00'}">
															<font color="#FF9999">${otherperson.stateName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="updatorName" title="更新人" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${otherperson.state=='02'}">
															<font color="#A8A8A8">${otherperson.updatorName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${otherperson.state=='00'}">
															<font color="#FF9999">${otherperson.updatorName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="updateTime" title="更新日期" headerStyle="text-align:center" style="text-align: left" width="100">
													<c:choose>
														<c:when test="${otherperson.state=='02'}">
															<font color="#A8A8A8">${otherperson.updateTime}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${otherperson.state=='00'}">
															<font color="#FF9999">${otherperson.updateTime}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
											</ec:row>
										</ec:table>
									</td>
								</tr>
								<%if (((java.util.ArrayList) request.getAttribute("otherpersonlist"))
					.size() > 0) {%>
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
														<%if (request.getAttribute("addNum") == null
						|| request.getAttribute("addNum").equals("")) {%>
														<input name="bupdate" type="button" class="button_nor" value="修 改" onClick="DoUpdate()">
														<input name="bnotuse" type="button" class="button_nor" value="废弃/不通过" onClick="DoUse('02')">
														<input name="buse" type="button" class="button_nor" value="使用/通过" onClick="DoUse('01')">
														<%if (request.getAttribute("noNew") == null
							|| request.getAttribute("noNew").equals("")
							|| request.getAttribute("noNew").equals("0")) {%>
														<input name="Submit4" type="button" class="button_nor" value="新 增" onClick="DoAdd()">
														<%}%>
														<%} else {%>
														<input name="selectOK" type="button" class="button_nor" value="确 定" onClick="addOtherPerson()">
														<input name="Submit4" type="button" class="button_nor" value="新 增" onClick="DoAdd()">														
														<%}%>
													</td>
												</tr>
											</tbody>
										</table>
									</td>
								</tr>
								<%} else {%>
								<%if (request.getAttribute("noNew") == null
						|| request.getAttribute("noNew").equals("")
						|| request.getAttribute("noNew").equals("0")) {%>
								<tr>
									<td height="40" align="right" valign="middle">
										<input name="Submit4" type="button" class="button_nor" value="新 增" onClick="DoAdd()">
									</td>
								</tr>
								<%}%>
								<%}%>
							</jodd:form>



						</table>
					</td>
				</tr>
			</table>
	</body>
</html>

<SCRIPT language=javascript>

setTimeout('init()',50);
function init(){

   if(document.deptOtherPersonForm.formName.value!=''){
      if(document.all.selectOK!=null)
          document.all.selectOK.style.display='';//显示确定按钮      
  }
  else{
      if(document.all.selectOK!=null)
          document.all.selectOK.style.display='none';//不显示确定按钮
  }
  
  if(document.deptOtherPersonForm.hmsg.value=='dok')
       alert("设置成功！");
  else if(document.deptOtherPersonForm.hmsg.value=='dfail')
       alert("设置失败！");
  if(document.deptOtherPersonForm.hrepeatSet.value!='')
       alert(document.deptOtherPersonForm.hrepeatSet.value+" 重复设置！");     
}

function addOtherPerson(){   
   
   var sflag=0;
   
   if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag==0){
              alert("请选择外部人员姓名！");
              return;
          }
          if(sflag>1){
              alert("只能选择一个外部人员！");
              return;
          }           
   }
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择外部人员姓名！");
              return;        
        }
   }   
   
   var opid="";
   var opmc="";
   if(document.all.cbgroup.length>1){
       for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   var idmc=document.all.cbgroup[i].value;
                   var pos=idmc.indexOf('_');
                   if(pos!=-1){
                        opid=idmc.substring(0,pos);
                        opmc=idmc.substring(pos+1,idmc.length); 
                   }                                                  
              }
       }
   
   }
   else{
        if(document.all.cbgroup.checked){
             var idmc=document.all.cbgroup.value;
                   var pos=idmc.indexOf('_');
                   if(pos!=-1){
                        opid=idmc.substring(0,pos);
                        opmc=idmc.substring(pos+1,idmc.length); 
                   }              
        }
   
   }  
   
   var targetForm=document.deptOtherPersonForm.formName.value;   
   
   if(parseInt(document.deptOtherPersonForm.addNum.value)==1||eval("opener."+targetForm+".bacpid==null")){   
       eval("opener."+targetForm+".acpid.value=opid;");       
       var haswl=false;
       for(var j=0;j<eval("opener."+targetForm+".s_acpid.length");j++){
          if(eval("opener."+targetForm+".s_acpid[j].value")==opid){
	         eval("opener."+targetForm+".s_acpid[j].selected=true;");
	         haswl=true;
	      }
       }   
       eval("opener."+targetForm+".tempAcpPerson.value=opmc;")
       
       if(haswl){
           eval("opener."+targetForm+".tempAcpPerson.style.display='none';");
           eval("opener."+targetForm+".s_acpid.style.display='';");
       }
       else{
           eval("opener."+targetForm+".s_acpid.style.display='none';");
           eval("opener."+targetForm+".tempAcpPerson.style.display='';");
       }
       eval("opener."+targetForm+".s_deptacpid.value='';");
   }
   else if(parseInt(document.deptOtherPersonForm.addNum.value)>1){
       eval("opener."+targetForm+".bacpid.value=opid;");
       var haswl=false;
       for(var j=0;j<eval("opener."+targetForm+".bs_acpid.length");j++){
          if(eval("opener."+targetForm+".bs_acpid[j].value")==opid){
	         eval("opener."+targetForm+".bs_acpid[j].selected=true;");
	         haswl=true;
	      }
       }   
       eval("opener."+targetForm+".btempAcpPerson.value=opmc;");
       eval("opener."+targetForm+".ifChanged.value='1';");
       
       if(haswl){
           eval("opener."+targetForm+".btempAcpPerson.style.display='none';");
           eval("opener."+targetForm+".bs_acpid.style.display='';");
       }
       else{
           eval("opener."+targetForm+".bs_acpid.style.display='none';");
           eval("opener."+targetForm+".btempAcpPerson.style.display='';");
       }
       eval("opener."+targetForm+".bs_deptacpid.value='';");
   }
   this.window.close();

}

function DoFind(){

   var opstate=document.deptOtherPersonForm.elements["search_otherpersonstate"].value;
   var opname=document.deptOtherPersonForm.elements["search_otherpersonname"].value;
   var opdept=document.deptOtherPersonForm.elements["search_otherpersondept"].value;
   
   if(document.deptOtherPersonForm.addNum.value!=''){      
//      if(opname.length%2!=0)
//            opname=opname+"曰"; 
//      window.open('deptOtherPersonAction.do?method=search4List&otherpersonState='+opstate+'&otherpersonDept='+opdept+'&otherpersonName='+opname+'&formName='+document.deptOtherPersonForm.formName.value+'&addNum='+document.deptOtherPersonForm.addNum.value,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');
        deptOtherPersonForm.action="deptOtherPersonAction.do?method=search4List";
        deptOtherPersonForm.submit();
   }
   else{
      deptOtherPersonForm.action="deptOtherPersonAction.do?method=search4List";
      deptOtherPersonForm.submit();
   
   }

}

function DoAdd(){
   if(document.deptOtherPersonForm.addNum.value!='')
       window.open('deptOtherPersonAction.do?method=load4Add&addNum='+document.deptOtherPersonForm.addNum.value+'&formName='+document.deptOtherPersonForm.formName.value,'nextwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');
   else{
       document.forms.ec.action="deptOtherPersonAction.do?method=load4Add&search_otherpersonstate="+document.deptOtherPersonForm.elements["search_otherpersonstate"].value;
       document.forms.ec.submit();
   
   }

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
   var cb=0;

   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;   
                   cb=i;                                  
              }
          } 
          if(sflag>1){
                       alert("只可选择一条记录进行修改！");
                       return;
          }         
          
          else if(sflag==0){
              alert("请选择要修改的外部人员！");
              return;
          } 
          else
              document.deptOtherPersonForm.updateid.value=document.all.cbgroup[cb].value;
   } 
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要修改的外部人员！");
              return;        
        }
        else
            document.deptOtherPersonForm.updateid.value=document.all.cbgroup.value;
   
   }   
   if(document.deptOtherPersonForm.addNum.value!='')
       window.open('deptOtherPersonAction.do?method=load4Update&otherpersonId='+document.deptOtherPersonForm.updateid.value+'&addNum='+document.deptOtherPersonForm.addNum.value,'nextwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');
   else{
       document.forms.ec.action="deptOtherPersonAction.do?method=load4Update&otherpersonId="+document.deptOtherPersonForm.updateid.value+"&search_otherpersonstate="+document.deptOtherPersonForm.elements["search_otherpersonstate"].value;
       document.forms.ec.submit();
   }
}

function DoUse(str){

   var sflag=0;
   var ids="";
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1; 
                   var id=document.all.cbgroup[i].value;
                   var pos=id.indexOf('_');
                   if(pos!=-1)
                       id=id.substring(0,pos);
                   ids=ids+"'"+id+"'"+",";                                                 
              }
          }           
         if(sflag==0){
              alert("请选择外部人员！");
              return;
          } 
   }
   else{
        if(document.all.cbgroup.checked){
              var id=document.all.cbgroup.value;
              var pos=id.indexOf('_');
              if(pos!=-1)
                  id=id.substring(0,pos);
              ids=ids+"'"+id+"'"+",";      
        }
        else{
            alert("请选择外部人员！");
            return;   
        }            
   }
 
if(str=='02'){  
   if(confirm("您确定要废弃该外部人员吗？")){
       deptOtherPersonForm.action="deptOtherPersonAction.do?method=setOtherPersonInfo&otherpersonIds="+ids.substring(0,ids.length-1)+"&otherpersonstate="+str+"&ec_p="+document.forms.ec.elements["ec_p"].value+"&ec_i="+document.forms.ec.elements["ec_i"].value+"&ec_crd="+document.forms.ec.elements["ec_crd"].value;
       deptOtherPersonForm.submit();
   }
   else
      return;
}
if(str=='01'){  
   if(confirm("您确定要使用该外部人员吗？")){
       deptOtherPersonForm.action="deptOtherPersonAction.do?method=setOtherPersonInfo&otherpersonIds="+ids.substring(0,ids.length-1)+"&otherpersonstate="+str+"&ec_p="+document.forms.ec.elements["ec_p"].value+"&ec_i="+document.forms.ec.elements["ec_i"].value+"&ec_crd="+document.forms.ec.elements["ec_crd"].value;
       deptOtherPersonForm.submit();
   }
   else
      return;
}

}

function DoClear(){

    document.deptOtherPersonForm.elements["search_otherpersondept"].value="";
    document.deptOtherPersonForm.elements["search_otherpersonname"].value="";
    document.deptOtherPersonForm.elements["search_otherpersonstate"].value="";    
}

//去左空格;     
function ltrim(s){     
    return s.replace( /^\s*/, "");     
}     
   
//去右空格;     
function rtrim(s){     
    return s.replace( /\s*$/, "");     
}     
   
//去左右空格;     
function trim(s){     
    return rtrim(ltrim(s));     
} 

</SCRIPT>
