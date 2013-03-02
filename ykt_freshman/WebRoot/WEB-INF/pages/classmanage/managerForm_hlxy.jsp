<%@ page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<html:form action="managerAction.do?method=save&getrole=2">
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium"><bean:message bundle="classmanage" key="manager.managermanage" /></font></strong>
					</td>
				</tr>
				<tr>
					<td align="left" valign="middle">
						<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
					</td>
				</tr>
				<tr>
					<td align="center" valign="top">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
							<tbody>
								<tr align="center" valign="middle">
									<td width="15%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="manager.no" />
									</td>
									<td align="left" valign="middle" class="tableHeader3" colspan="3">
										<%if ("Add".equals(request.getAttribute("actionFlag"))) {%>
										<html:hidden property="managermodel.managerId" value="" />
										<html:text property="managermodel.managerNo" styleClass="input_box" maxlength="20" />
										<%} else {%>
										<html:hidden property="managermodel.managerId" />
										<html:text property="managermodel.managerNo" styleClass="input_box" maxlength="20" readonly="true" />
										<%}

		%>
										<html:submit property="search" styleClass="button_nor" onclick="javascript: return search_check();">
											<bean:message key="button.search" />
										</html:submit>
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
									<td height="24" align="right" valign="middle" class="tableHeader2">
										<bean:message bundle="classmanage" key="manager.contact" />
									</td>
									<td align="left" valign="middle" class="tableHeader3" >
										<html:text property="managermodel.contact" styleClass="input_box" maxlength="30" />
									</td>
									<!--<td height="24" align="right" valign="middle" class="tableHeader2">
										<bean:message bundle="classmanage" key="manager.school" />
									</td>
									<td align="left" valign="middle" class="tableHeader3" >

										<html:select styleClass="select01" property="managermodel.schoolId"  >
											<html:option value="">--------------------------</html:option>
											<html:options collection="schoolList" labelProperty="schoolName" property="schoolId" />
											<html:hidden property="managermodel.schoolId" />
										</html:select>										
									</td>		-->	
								<td  align="left" valign="middle" class="tableHeader2">
									<bean:message bundle="classmanage" key="manager.available" />
								</td>									
								<td align="left" valign="middle" class="tableHeader3" >
									<html:select styleClass="select01" property="managermodel.available">
										<html:option value="1">是</html:option>
										<html:option value="0">否</html:option>										
									</html:select>
								</td>															
								</tr>
								<tr align="center" valign="middle">
									<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="manager.duties" />
									</td>
									<td colspan="3" align="left" valign="middle" class="tableHeader3">
										<table border="0" cellspacing="0" cellpadding="0">
											<tr align="center" valign="middle">

												<td width="25">
													<html:checkbox property="assistant" value="21" onclick="disTutor();" />
												</td>
												<td width="45" align="left">
													<bean:message bundle="classmanage" key="manager.assistant" />
												</td>
												<td width="25" align="center">
													<html:checkbox property="tutor" value="22" onclick="disAssist();" />
												</td>
												<td width="40" align="left">
													<bean:message bundle="classmanage" key="manager.tutor" />
												</td>
												<td width="25" align="center">
													<html:checkbox property="teacher" value="01" />
												</td>
												<td width="42" align="left">
													<bean:message bundle="classmanage" key="manager.teacher" />
												</td>
											</tr>
										</table>
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
						<INPUT type="button" class="button_nor" value="<bean:message bundle="classmanage" key="class.return" />" onclick="javascript:howtoreturn();">
					</td>
				</tr>
			</html:form>
		</table>
	</body>
</center>

<script language="javascript">
	function disTutor(){
		if(document.all("assistant").checked==true){
			document.all("tutor").checked=false;
			document.all("tutor").disabled=true;
		}else{
			document.all("tutor").disabled=false;
			document.all("tutor").checked=false;
		}
	}
	function disAssist(){
		if(document.all("tutor").checked==true){
			document.all("assistant").checked=false;
			document.all("assistant").disabled=true;
		}else{
			document.all("assistant").disabled=false;
			document.all("assistant").checked=false;
		}
	}
	

	function add_check(){	

		if(document.all("managermodel.managerNo").value==""){
			alert("人员编号不能为空");
			document.all("managermodel.managerNo").focus();
			return false;
		}
		if(document.all("managermodel.managerName").value==""){
			alert("请先查询该人员是否存在");
			return false;
		}
		if(document.all("managermodel.gender").value==""){
			alert("人员性别不能为空");
			return false;
		}
		if((document.all("assistant").checked==false)&&(document.all("tutor").checked==false)&&(document.all("teacher").checked==false)){
			alert("人员职务不能为空");
			return false;
		}					
		return true;
	}
	
	function delete_check(){
		if(document.all("managermodel.managerNo").value==""){
			alert("没有可删除对象");
			return false;
		}else{
			if(document.all("managermodel.managerName").value==""){
				alert("请先查询该人员是否存在");
				return false;
			}
		}		
		document.forms[0].action='managerAction.do?method=delete';
		return true;
	}
	
	function search_check(){
		if(document.all("managermodel.managerNo").value==""){
			alert("请先填写学工号");
			document.all("managermodel.managerNo").focus();
			return false;
		}
		document.forms[0].action='managerAction.do?method=load4NameSearch&getrole=2';
		return true;
	}
	function howtoreturn(){
		if(document.all.myerror.value != ""){
			window.location.href='managerAction.do?method=load4Search&getrole=2';
		}else{
			window.location.href='managerAction.do?method=load4Search&getrole=2';
		}
	}
	function showError(){
		if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	}

	 window.onload=showError;	
</script>
