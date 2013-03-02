<%@ page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<center>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<html:form action="collegeAction.do?method=save">
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium"><bean:message bundle="classmanage" key="college.collegemanage" /></font></strong>
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
							<html:hidden property="collegemodel.collegeId" />
							<tbody>
								<tr align="center" valign="middle">
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="college.id" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<%if ("Add".equals(request.getAttribute("actionFlag"))) {%>
										<html:text property="collegemodel.collegeNo" styleClass="input_box" maxlength="10"/>
										<%} else {%>
										<html:text property="collegemodel.collegeNo" styleClass="input_box" readonly="true" maxlength="10"/>
										<%}
										%>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="college.name" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:text property="collegemodel.collegeName" styleClass="input_box" maxlength="15"/>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="college.leader" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="collegeleader">
											<html:option value="" />
											<html:options collection="managermodel" labelProperty="managerName" property="managerId" />
										</html:select>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="college.introduction" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:textarea property="collegemodel.introduction" cols="80" rows="12" />(200字以内)
									</td>
								</tr>
							</tbody>
						</table>
					</td>
				</tr>
				<tr>
					<td height="40" align="right" valign="middle" class="tdborder02">
						<html:submit property="save" styleClass="button_nor" onclick="javascript: return check_save();">
							<bean:message key="button.save" />
						</html:submit>
						<%if (!"Add".equals(request.getAttribute("actionFlag"))) {%>
						<html:submit property="delete" styleClass="button_nor" onclick="javascript:return check_delete();">
							<bean:message key="button.delete" />
						</html:submit>
						<%}
						%>
						<input type="button" name="goback" class="button_nor" value="<bean:message bundle="classmanage" key="class.return" />" onclick="javascript:howtoreturn();">
					</td>
				</tr>
			</html:form>
		</table>
	</body>
</center>

<script language="javascript">
	function check_save(){
		var reg = /<[^>]*>/g;
		var introduction = document.all("collegemodel.introduction").value.replace(reg,"");
		if(document.all("collegemodel.collegeNo").value==""){
			alert("学院编号不可为空");
			document.all("collegemodel.collegeNo").focus();
			return false;
		}
		if(fucCheckNUMABC(document.all("collegemodel.collegeNo").value)){
			return true;
		}else{
			alert("学院编号必须是数字或者字母");
			document.all("collegemodel.collegeNo").focus();
			return false;
		}

		if(document.all("collegemodel.collegeName").value==""){
			alert("学院名称不可为空");
			document.all("collegemodel.collegeName").focus();
			return false;
		}
		if(document.all("collegeleader").value==""){
			alert("学工组组长不可为空");
			document.all("collegeleader").focus();
			return false;
		}
		if (introduction.length>=200){
			alert("书院简介不能超过200个字符");
			document.all("collegemodel.introduction").focus();
			return false;
		}
		
		return true;
	}
	
	function check_delete(){
		if(!confirm("是否确定要删除？")){
	 		return false;
	 	}	
		if(document.all("collegemodel.collegeNo").value==""){
			alert("没有可删除的对象");
			return false;
		}
		document.forms[0].action='collegeAction.do?method=delete'
		return true;
	}
	
	function fucCheckNUMABC(NUM)
	{
	 var i,j,strTemp;
	 strTemp="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	 if ( NUM.length== 0)
	  return true
	 for (i=0;i<NUM.length;i++)
	 {
	  j=strTemp.indexOf(NUM.charAt(i)); 
	  if (j==-1)
	  {
	  //说明有字符不是数字
	   return false;
	  }
	 }
	 //说明是数字
	 return true;
	}
		function howtoreturn(){
		if(document.all.myerror.value != ""){
			window.location.href='collegeAction.do?method=load4List';
		}else{
			window.location.href='collegeAction.do?method=load4List';
		}
	}
	function showError(){
		if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	}

	 window.onload=showError;	
</script>
