<%@ page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<html:form action="classAction.do?method=save&&getrole=2">
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium"><bean:message bundle="classmanage" key="class.classmanage" /></font></strong>
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
								<html:hidden property="classmodel.classId" />
								<tr align="center" valign="middle">
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="class.name" />
									</td>
									<td align="left" valign="middle" class="tableHeader3" height="26">
										<%
											if("Add".equals(request.getAttribute("actionFlag"))){
										%>
											<html:text property="classmodel.classNo" styleClass="input_box" maxlength="40" />
										<%
											}else{											
										%>
											<html:text property="classmodel.classNo" styleClass="input_box" maxlength="40" readonly="true"/>
										<%
											}
										%>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="class.assistant" />
									</td>
									<td align="left" valign="middle" class="tableHeader3" colspan="3">
										<html:select styleClass="select01" property="assistant">
											<html:option value="" >-----------------------</html:option>
											<html:options collection="assistantList" labelProperty="managerName" property="managerId" />
										</html:select>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="class.tutor" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3" colspan="3">
										<html:select styleClass="select01" property="tutor1">
											<html:option value="" >-----------------------</html:option>
											<html:options collection="tutorList" labelProperty="managerName" property="managerId" />
										</html:select>
									</td>
								</tr>

								<tr align="center" valign="middle">
									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="class.introduction" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3" colspan="3">
										<html:textarea property="classmodel.introduction" cols="80" rows="4"/>(100字以内)
									</td>
								</tr>
							</tbody>
						</table>
					</td>
				</tr>
				<tr>
					<td height="40" align="right" valign="middle" class="tdborder02">
						<html:submit property="save" styleClass="button_nor" onclick="javascript: return validate();">
							<bean:message key="button.save" />
						</html:submit>
						<input type="button" name="goback" class="button_nor" value="<bean:message bundle="classmanage" key="class.return" />" onclick="javascript:howtoreturn();">
					</td>
				</tr>
			</html:form>
		</table>
	</body>

</center>


<script language="javascript">
	function validate(){
		if(document.all("classmodel.classNo").value==""){
			alert("班级编号不可为空");
			document.all("classmodel.classNo").focus();
			return false;
		}
//		if(fucCheckNUMABC(document.all("classmodel.classNo").value)){
//			return true;
//		}else{
//			alert("班级编号必须是数字或者字母");
//			document.all("classmodel.classNo").focus();
//			return false;
//		}
		
		if(document.all("assistant").value==""){
			alert("辅导员不可为空");
			document.all("assistant").focus();
			return false;
		}

		
		if(document.all("tutor1").value==""){
			alert("导师不可为空");
			document.all("tutor1").focus();
			return false;
		}
   var len = getStrLength(document.all("classmodel.classNo").value);
   if(len>40){  
       alert("班级编号小于40个字符或13个汉字");
       return false;
   
   }	
   		
   if(document.all("classmodel.introduction").value.length>300){  
       alert("备注过长!");
       return false;
   
   }		


		return true;
	}
	
function getStrLength(str){
	var len = 0;
	var ch;
	if(str==null)
		return len;
	for(var i = 0; i<str.length;i++){
		ch=str.charCodeAt(i);
		if(ch>255)
			len+=3;
		else
			len++;
	}
	return len;
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
			window.location.href='classAction.do?method=load4Search&getrole=2';
		}else{
			window.location.href='classAction.do?method=load4Search&getrole=2';
		}
	}
	function showError(){
		if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	}

	 window.onload=showError;	
</script>

