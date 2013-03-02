<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.Classmodel"%>
<%@ include file="../tiles/include.jsp"%>
<script language="JavaScript">
function clearAll(){
	document.all("college").value="";
	document.all("classId").value="";
}

</script>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

	<table id="classSelect" width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium"><bean:message bundle="classmanage" key="abroadDistribution.abroadDistribution" /></font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="middle">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="top" colspan="2">
				<html:form action="studentAction.do?method=class4Search">
					<table width=100% border=1 align="center" cellpadding="1" cellspacing="0" bordercolor="#FFFFFF" id="submenu1">

						<tbody>
							<tr align="center" valign="middle">
								<td width="15%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<html:hidden property="studentIds" />
									<span class="medium"><bean:message bundle="classmanage" key="studentsearch.college" /></span>
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="college" onchange="changeCollge(this.value)">
										<html:option value="">-------------------------</html:option>
										<html:options collection="collegeList" labelProperty="collegeName" property="collegeId" />
									</html:select>
								</td>

								<td width="15%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<bean:message bundle="classmanage" key="class.name" />
								</td>
								<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
									<html:select styleClass="select01" property="classId">
										<html:option value="">-------------------------</html:option>
										<html:options collection="classList" labelProperty="classNo" property="classId" />
									</html:select>
								</td>
							</tr>
						</tbody>
					</table>
					<tr>
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
			<td height="20" align="left" valign="middle" class="medium">
				<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
			</td>
		</tr>

		<tr>
			<td height="40" align="center">
				<html:form action="studentAction.do?method=abroadDistribution">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolordark=#AA817F bordercolor=#ffffff id=submenu1>
						<tbody>
							<tr align="center" valign="middle">
								<td width="24" valign="middle" class="tableHeader">
									<html:hidden property="studentIds" />
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
							<logic:present name="abroadClasses" scope="request">
								<logic:iterate name="abroadClasses" id="classes" indexId="i">
									<c:if test="${i%2 == 0}">
										<tr align="center" valign="middle">
											<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
												<input type="checkbox" name="deleteX" value="<bean:write name="classes" property="classId"/>">
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="classes" property="collegeName" />
												&nbsp;
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
									</c:if>
									<c:if test="${i%2 != 0}">
										<tr align="center" valign="middle" bgcolor="#F6F4F5">
											<td height="24" align="center" valign="middle">
												<input type="checkbox" name="deleteX" value="<bean:write name="classes" property="classId"/>">
											</td>
											<td align="center" valign="middle">
												<bean:write name="classes" property="collegeName" />
												&nbsp;
											</td>
											<td align="center" valign="middle">
												<bean:write name="classes" property="classNo" />
												&nbsp;
											</td>
											<td align="center" valign="middle">
												<bean:write name="classes" property="managerName" />
												&nbsp;
											</td>
										</tr>
									</c:if>

								</logic:iterate>
							</logic:present>
						</tbody>
					</table>
					<tr>
						<td height="30" align="right" valign="middle">
							<INPUT type="button" name="goback" value="<bean:message bundle="classmanage" key="abroadDistribution.preStep" />" class="button_nor" onclick="javascript:history.go(-1);">
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
	 				return true;
	 			}else{	 
	 				alert("请选择要分配的班级!");
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
			 	alert("请选择要分配的班级!");
		 		return false;
		 }else{
		 		alert("没有可分配的对象");
		 		return false;
		 }
	 } 
	 
<!-- class list -->
	var classescount;
	classescount = 0;
	classesArr = new Array(); 
	<%	
		ArrayList classeslist=(ArrayList)request.getAttribute("classList");		
		int i = 0;
		for(i=0;i<classeslist.size();i++){
			Classmodel classmodel = (Classmodel)classeslist.get(i);
			String classid=classmodel.getClassId();
			String classNo=classmodel.getClassNo();	
			String collegeId = classmodel.getYxCollege().getCollegeId();
	%>
			classesArr[<%=i%>]= new Array("<%=classid%>","<%=classNo%>","<%=collegeId%>"); 
	<%	
		}	
	%>
	classescount=<%=classeslist.size()%>
	

	function changeCollge(college){
	 	document.all("classId").length=0;
	 	var collegeId=college; 
		var j; 
		document.all("classId").options[document.all("classId").length]=new Option("-------------------------","");
		for (j=0; j<classescount; j++) 
		{ 
			if (classesArr[j][2] == collegeId) 
			{ 
				document.all("classId").options[document.all("classId").length]= new Option(classesArr[j][1],classesArr[j][0]);
			} 
		} 
		
	 }
	 
	 	function showError(){
		if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	}

	 window.onload=showError;	
	 

</script>



