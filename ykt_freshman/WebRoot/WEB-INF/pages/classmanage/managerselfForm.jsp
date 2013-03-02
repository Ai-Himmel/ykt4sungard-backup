<%@ page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<html:form action="managerAction.do?method=selfsave">
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium">管理人员信息个人维护</font></strong>
					</td>
				</tr>
				<tr>
					<td align="left" valign="middle">
						<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
					</td>
				</tr>
				<%if(request.getAttribute("optresult")!=null&&request.getAttribute("optresult").equals("notManager")){%>
				<tr>
					<td align="center" valign="middle">
						<font size="2.5" color="#990000">您不是管理人员，不能操作本界面！</font>
					</td>
				</tr>				
				<%}else{%>
				<tr>
					<td align="center" valign="top">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
							<tbody>
								<tr align="center" valign="middle">
									<td width="15%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="manager.no" />
									</td>
									<td align="left" valign="middle" class="tableHeader3" colspan="3">										
										<html:hidden property="managermodel.managerId" /><html:hidden property="managermodel.schoolId" />
										<html:text property="managermodel.managerNo" styleClass="input_box" maxlength="20" readonly="true" />
					                </td>
								</tr>
								<tr align="center" valign="middle">
									<td width="15%" height="24" align="right" valign="middle" class="tableHeader2">
										<bean:message bundle="classmanage" key="manager.name" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:text property="managermodel.managerName" style="background:#ECE6E6" styleClass="input_box" maxlength="20" readonly="true" />
									</td>
									<td width="10%" align="right" valign="middle" class="tableHeader2">
										<bean:message bundle="classmanage" key="manager.gender" />
									</td>
									<td class="tableHeader3">
										<html:select styleClass="select01" property="managermodel.gender" style="background:#ECE6E6" disabled="true">
											<html:option value="">----------</html:option>
											<html:options collection="genderList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
										<html:hidden property="managermodel.gender" />
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td align="right" valign="middle" class="tableHeader2">
										<bean:message bundle="classmanage" key="manager.managerType" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:text property="managermodel.managerType" style="background:#ECE6E6" styleClass="input_box" maxlength="20" readonly="true" />
									</td>
									<td align="right" valign="middle" class="tableHeader2">
										<bean:message bundle="classmanage" key="manager.managerOrg" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="managermodel.managerOrg" style="background:#ECE6E6" disabled="true">
											<html:option value="">------------------------------------------------------------</html:option>
											<html:options collection="typeList" labelProperty="deptName" property="deptCode" />
											<html:hidden property="managermodel.managerOrg" />
										</html:select>
									</td>

								</tr>
								<tr align="center" valign="middle">
								    <td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="manager.duties" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									    <%if(request.getAttribute("managerrole")!=null&&request.getAttribute("managerrole").equals("11")){%>
									    学工组组长
									    <%}else if(request.getAttribute("managerrole")!=null&&request.getAttribute("managerrole").equals("21")){%>
										辅导员
										<%}else if(request.getAttribute("managerrole")!=null&&request.getAttribute("managerrole").equals("22")){%>
										导师
										<%}else if(request.getAttribute("managerrole")!=null&&request.getAttribute("managerrole").equals("01")){%>
										教务员
										<%}%>
									</td>
								<td  align="left" valign="middle" class="tableHeader2">
									<bean:message bundle="classmanage" key="manager.available" />
								</td>										
								<td align="left" valign="middle" class="tableHeader3" >
								     <html:hidden property="managermodel.available" />
								     <%if(request.getAttribute("manageravail")!=null&&request.getAttribute("manageravail").equals("1")){%>
									    是
									 <%}else{%>
										否
									<%}%>								    
								</td>																
								</tr>
								<tr align="center" valign="middle">
									<td height="24" align="right" valign="middle" class="tableHeader2">
										<bean:message bundle="classmanage" key="manager.contact" />
									</td>
									<td align="left" valign="middle" class="tableHeader3" colspan="3" >
										<html:text property="managermodel.contact" styleClass="input_box" maxlength="30" />
									</td>
								</tr>

								<tr align="center" valign="middle">
									<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="manager.introduction" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3" colspan="3">
										<html:textarea property="managermodel.introduction" cols="70" rows="4"></html:textarea>
									</td>
								</tr>
							</tbody>
						</table>
					</td>
				</tr>
				<tr>
					<td height="40" align="right" valign="middle">
						<html:submit property="save" styleClass="button_nor" onclick="javascript: return add_check();">
							<bean:message key="button.save" />
						</html:submit>
					</td>
				</tr>
				<%}%>
 <logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
  </logic:notPresent>
			</html:form>
		</table>
	</body>
</center>

<script language="javascript">
setTimeout('DoInit()',300);

function DoInit(){

if(document.all.hmsg.value=='0')
      alert("保存成功!");
else if(document.all.hmsg.value=='1')
      alert("保存失败!");

}

	function add_check(){	

	if(document.all("managermodel.introduction").value.length>100){   
        alert("简介内容不能超过100字!");
        return false;   
    }
    else		
		return true;
	}
	
	function showError(){
		if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	}

	 window.onload=showError;	
</script>
