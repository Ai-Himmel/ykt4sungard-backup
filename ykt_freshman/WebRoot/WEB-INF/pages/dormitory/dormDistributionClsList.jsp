<%@ page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

	<table id="classSelect" width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium"><bean:message bundle="dormitorymanage" key="dormDistribution.dormDistribution" /></font></strong>
			</td>
		</tr>
		<tr>
			<td align="left" valign="middle">
				&nbsp;<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
			</td>
		</tr>

		<tr>
			<td height="20" align="center" valign="middle" class="medium">
				&nbsp;
			</td>
		</tr>

		<tr>
			<td height="40" align="center" valign="top">
				<html:form action="studentAction.do?method=dormDstrbution">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
						<tbody>
							<tr align="center" valign="middle">
								<td width="24" height="24" valign="middle" class="tableHeader">
									<input type="checkbox" name="checkSwitch" onclick="selectIns();">
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="college.name" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="class.name" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="class.assistant" />
								</td>
							</tr>
							
							
							<logic:present name="dormDistributionClslist" scope="request">
								<logic:iterate name="dormDistributionClslist" id="classes">
									<tr align="center" valign="middle">
										<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<input type="checkbox" name="deleteX" value="<bean:write name="classes" property="classId"/>">
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="classes" property="collegeName" />
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="classes" property="classNo" />
											&nbsp;
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="classes" property="managerName" />
											&nbsp;
										</td>
									</tr>
								</logic:iterate>
							</logic:present>
						</tbody>
					</table>
					<tr>
						<td height="30" align="right" valign="middle">
							<html:submit property="distribution" styleClass="button_nor" onclick="return ondelete();">
								<bean:message bundle="classmanage" key="abroadDistribution.distribute" />
							</html:submit>
						</td>
					</tr>
				</html:form>
			</td>
		</tr>
		<tr>
			<td align="left" valign="middle">
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
	 				if(!confirm("是否确定开始分配？")){
			 			return false;
			 		}
	 				return true;
	 			}else{	 
	 				alert("请先选择可以分配的班级");			
	 				return false;
	 			}
	 		}	
			 for(i=0;i<document.all.deleteX.length;i++){
			 	if(document.all.deleteX[i].checked==true){
			 		if(!confirm("是否确定开始分配？")){
			 		return false;
			 		}
			 		return true;
			 	}else{
			 		continue;
			 	}	 			
			 }	
			 	alert("请先选择可以分配的班级");
		 		return false;
		 }else{
		 		alert("没有可分配的班级");
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