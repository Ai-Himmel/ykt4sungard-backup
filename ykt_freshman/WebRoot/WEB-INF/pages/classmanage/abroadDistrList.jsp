<%@page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>

<script language="JavaScript">
function clearAll(){
	document.all("studentmodel.studentNo").value="";
	document.all("studentmodel.stuName").value="";
	document.all("studentmodel.majorin").value="";
	document.all("studentmodel.nationality").value="";
}

</script>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table id="stuSelect" width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02" colspan="2">
				<strong><font class="medium"><bean:message bundle="classmanage" key="abroadDistribution.searchAbroadStu" /></font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="middle">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="top" colspan="2">
				<html:form action="studentAction.do?method=abroad4Search">
					<table width=100% border=1 align="center" cellpadding="1" cellspacing="0" bordercolor="#FFFFFF" id="submenu1">
						<tbody>
							<tr align="center" valign="middle">
								<td width="15%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<span class="medium"><bean:message bundle="classmanage" key="studentsearch.studentNo" /></span>
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<html:text property="studentmodel.studentNo" styleClass="input_box_stu" maxlength="20" />
								</td>

								<td width="15%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<bean:message bundle="classmanage" key="studentsearch.stuName" />
								</td>
								<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
									<html:text property="studentmodel.stuName" styleClass="input_box_stu" maxlength="20" />
								</td>
							</tr>
							<tr align="right" valign="middle">
								<td width="15%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<bean:message bundle="classmanage" key="studentsearch.nationality" />
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="studentmodel.nationality">
										<html:option value="">-----------------------------------------</html:option>
										<html:options collection="nationalityList" labelProperty="dictCaption" property="id.dictValue" />
									</html:select>
								</td>
								<td width="15%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<bean:message bundle="classmanage" key="studentsearch.majorin" />
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="studentmodel.majorin">
										<html:option value="">-----------------------------------------</html:option>
										<html:options collection="majorinList" labelProperty="dictCaption" property="id.dictValue" />
									</html:select>
								</td>
							</tr>
						</tbody>
					</table>
					<tr>
						<td height="40" align="left" valign="middle" class="tdborder02">
							<font color="green"> 已分配班级的留学生需要取消其班级才能再次重新分配 </font>
						</td>
						<td height="40" align="right" valign="middle" class="tdborder02">
							<html:submit property="search" styleClass="button_nor">
								<bean:message key="button.query" />
							</html:submit>
							<html:button property="reset" styleClass="button_nor" onclick="clearAll();">
								<bean:message key="button.reset" />
							</html:button>
						</td>
					</tr>
				</html:form>
			</td>
		</tr>

		<tr>
			<td height="20" align="left" valign="middle" class="medium" colspan="2">
				<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
			</td>
		</tr>

		<tr>
			<td height="40" align="center" valign="top" colspan="2">
				<html:form action="studentAction.do?method=class4Search">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>

						<tbody>
							<tr align="center" valign="middle">
								<td width="24" height="24" valign="middle" class="tableHeader">
									<input type="checkbox" name="checkSwitch" onclick="selectIns();">
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="studentsearch.studentNo" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="studentsearch.stuName" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="studentsearch.gender" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="studentsearch.nationality" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="studentsearch.majorin" />
								</td>
							</tr>
							<logic:present name="abroadmodels" scope="request">
								<logic:iterate name="abroadmodels" id="abroadstu">
									<tr align="center" valign="middle">
										<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<input type="checkbox" name="deleteX" value="'<bean:write name="abroadstu" property="studentId"/>'">
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="abroadstu" property="studentNo" />
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="abroadstu" property="stuName" />
											&nbsp;
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="abroadstu" property="gender" />
											&nbsp;
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="abroadstu" property="nationality" />
											&nbsp;
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="abroadstu" property="majorin" />
											&nbsp;
										</td>

									</tr>
								</logic:iterate>
							</logic:present>
						</tbody>
					</table>
					<tr>
						<td height="30" align="right" valign="middle" colspan="2">
							<html:submit property="next" styleClass="button_nor" onclick="return ondelete();">
								<bean:message bundle="classmanage" key="abroadDistribution.nextStep" />
							</html:submit>
						</td>
					</tr>
				</html:form>
			</td>
		</tr>
		<tr>
			<td align="left" valign="middle" colspan="2">
				&nbsp;
			</td>
		</tr>
	</table>
</body>
<script language="JavaScript">
	  function ondelete(){ 
	 	if(document.all.deleteX!=null){
	 		if(document.all.deleteX.length==null){
	 			if(document.all.deleteX.checked==true){
	 				return true;
	 			}else{	 
	 				alert("请选择要分配的留学生!");	
	 				return false;
	 			}
	 		}	
			 for(i=0;i<document.all.deleteX.length;i++){
			 	if(document.all.deleteX[i].checked==true){
			 		return true;
			 	}else{
			 		continue;
			 	}	 			
			 }	
			 	alert("请选择要分配的留学生!");
		 		return false;
		 }else{
		 		alert("没有可分配的对象");
		 		return false;
		 }
	 } 

	function showError(){
		if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	}

	 window.onload=showError;	
</script>
