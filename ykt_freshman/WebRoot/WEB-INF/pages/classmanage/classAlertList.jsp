<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.Classmodel"%>
<%@ include file="../tiles/include.jsp"%>

<script language="JavaScript">
function clearAll(){
	document.all("studentmodel.studentNo").value="";
	document.all("studentmodel.stuName").value="";
	document.all("studentmodel.gender").value="";
	document.all("studentmodel.fromProvince").value="";
	document.all("studentmodel.nation").value="";
	document.all("studentmodel.majorin").value="";
	document.all("studentmodel.nationality").value="";
	document.all("collegeId").value="";
	document.all("classmodel.classId").value="";
}

function document.onkeydown()
{
	var e=event.srcElement;
	if(event.keyCode==13)
	{
		document.all("search").click();
		return false;
	}
}
</script>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="classmanage" key="classAlert.classAlert" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top" height="10"></td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<html:form action="classAction.do?method=alert4Search">						
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
							<tr>
								<td>
									<INPUT type="hidden" name="export" value="">
								</td>
							</tr>
							<tr>
					<td>
						<%if (request.getAttribute("myclassId") != null) {
				String myclassId = request.getAttribute("myclassId").toString();

				%>
						<INPUT type="hidden" name="myclassId" value="<%=myclassId%>">
						<%} else {

			%>
						<INPUT type="hidden" name="myclassId" value="">

						<%}

			%>
					</td>
				</tr>
							<tbody>
								<tr align="center" valign="middle">
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="studentsearch.studentNo" /></span>
									</td>
									<td width="22%" align="left" valign="middle" class="tableHeader3">
										<html:text property="studentmodel.studentNo" styleClass="input_box" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();" />
									</td>
									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.stuName" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<html:text property="studentmodel.stuName" styleClass="input_box" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();" />
									</td>
									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.gender" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.gender">
											<html:option value="">------------------------</html:option>
											<html:options collection="genderList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.majorin" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.majorin">
											<html:option value="">----------------------------------------</html:option>
											<html:options collection="majorinList" labelProperty="dictCaption" property="dictValue" />
										</html:select>
									</td>
									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.province" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.fromProvince">
											<html:option value="">------------------------</html:option>
											<html:options collection="provinceList" labelProperty="dictCaption" property="dictValue" />
										</html:select>
									</td>
									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.nation" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.nation">
											<html:option value="">------------------------</html:option>
											<html:options collection="nationList" labelProperty="dictCaption" property="dictValue" />
										</html:select>
									</td>

								</tr>
								<tr align="center" valign="middle">
									<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.nationality" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.nationality">
											<html:option value="">----------------------------------------</html:option>
											<html:options collection="nationalityList" labelProperty="dictCaption" property="dictValue" />
										</html:select>
									</td>
									<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="class.college" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="collegeId" onchange="changeCollgeId(this.value)">
											<html:option value="">------------------------</html:option>
											<html:options collection="collegeList" labelProperty="collegeName" property="collegeId" />
										</html:select>
									</td>
									<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="class.name" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="classmodel.classId">
											<html:option value="">------------------------</html:option>
											<html:options collection="classList" labelProperty="classNo" property="classId" />
										</html:select>
									</td>
									
								</tr>
							</tbody>
						</table>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<html:submit property="search" styleClass="button_nor" onclick="javascript:NotExport();">
									<bean:message key="button.query" />
								</html:submit>
								<html:button property="reset" styleClass="button_nor" onclick="clearAll();">
									<bean:message key="button.reset" />
								</html:button>
							</td>
						</tr>
				</td>
			</tr>

			<tr>
				<td height="10" align="left" valign="middle" class="medium">
					<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
				</td>
			</tr>
				<tr>
					<td height="40" align="center" valign="top">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<tbody>
								<tr align="center" valign="middle">
									<td width="30" valign="middle" class="tableHeader">
										<input type="checkbox" name="checkSwitch" onclick="selectIns();">
									</td>
									<td height="24" valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="studentsearch.studentNo" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="studentsearch.stuName" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="studentsearch.gender" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="studentsearch.nation" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="studentsearch.nationality" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="studentsearch.province" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="studentsearch.majorin" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="class.college" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="class.name" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="class.assistant" />
									</td>
								</tr>
								<logic:present name="studentmodels" scope="request">
									<%int itemNo = ((Integer) request.getAttribute("stuCount"))
					.intValue();%>
									<pg:pager url="./classAction.do" items="<%=itemNo%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%=true%>" export="offset,currentPageNumber=pageNumber" scope="request">
										<%-- keep track of preference --%>
										<pg:param name="method" />
										<pg:param name="studentmodel.studentNo" />
										<pg:param name="studentmodel.stuName" />
										<pg:param name="studentmodel.gender" />
										<pg:param name="studentmodel.nation" />
										<pg:param name="studentsearch.province" />
										<pg:param name="studentmodel.nationality" />
										<pg:param name="studentmodel.majorin" />
										<pg:param name="collegeId" />
										<pg:param name="classmodel.classId" />
										<pg:param name="page" />
										<pg:param name="orderby" />
										<pg:param name="sort" />

										<%-- save pager offset during form changes --%>
										<input type="hidden" name="pager.offset" value="<%= offset %>">

										<logic:iterate name="studentmodels" id="studentwithallinfo" indexId="i">
											<pg:item>
												<c:if test="${i%2 == 0}">
													<tr align="center" valign="middle">
														<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
															<input type="checkbox" name="deleteX" value="<bean:write name="studentwithallinfo" property="studentId" />">
														</td>
														<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="studentwithallinfo" property="studentNo" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="studentwithallinfo" property="stuName" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="studentwithallinfo" property="gender" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="studentwithallinfo" property="nation" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="studentwithallinfo" property="nationality" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="studentwithallinfo" property="fromProvince" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="studentwithallinfo" property="majorin" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="studentwithallinfo" property="college" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="studentwithallinfo" property="classId" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="studentwithallinfo" property="assistant" />
															&nbsp;
														</td>
													</tr>
												</c:if>
												<c:if test="${i%2 != 0}">
													<tr align="center" valign="middle" bgcolor="#F6F4F5">
														<td height="24" align="center" valign="middle">
															<input type="checkbox" name="deleteX" value="<bean:write name="studentwithallinfo" property="studentId" />">
														</td>
														<td height="24" align="center" valign="middle">
															<bean:write name="studentwithallinfo" property="studentNo" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="studentwithallinfo" property="stuName" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="studentwithallinfo" property="gender" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="studentwithallinfo" property="nation" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="studentwithallinfo" property="nationality" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="studentwithallinfo" property="fromProvince" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="studentwithallinfo" property="majorin" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="studentwithallinfo" property="college" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="studentwithallinfo" property="classId" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="studentwithallinfo" property="assistant" />
															&nbsp;
														</td>
													</tr>
												</c:if>
											</pg:item>
										</logic:iterate>
										<jsp:include page="./page.jsp" flush="true" />

							</tbody>
						</table>
					</td>
				</tr>
			<tr> 
    			<td>
        		<jsp:include page="./pagenoexcel.jsp" flush="true" />
    			</td>
  			</tr>
		</pg:pager>
	</logic:present>
    <logic:notPresent name="studentmodels" scope="request">	
		  </tbody>
        </table>
      </td>
   </tr>
   </logic:notPresent>  				
				<tr>
					<td height="10" align="center" valign="middle" class="medium"></td>
				</tr>
				<tr>
					<td>
						<%if (request.getAttribute("myclass") != null) {
				String myclass = request.getAttribute("myclass").toString();

				%>
						<INPUT type="hidden" name="myclass" value="<%=myclass%>">
						<%} else {

			%>
						<INPUT type="hidden" name="myclass" value="">

						<%}

			%>
					</td>
				</tr>
  <tr> 
    <td height="40" align="left" valign="middle">
        <%
        int rowcount=0;
        if(request.getAttribute("listcount")!=null){
        	rowcount=((Integer)request.getAttribute("listcount")).intValue();
        %>       
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
        <%} %>
    </td>
  </tr>					
				<tr>
					<td height="30" align="left" valign="middle" class="tdborder02">
						<font class="medium"><bean:message bundle="classmanage" key="classAlert.classAlertTo" /></font>
					</td>
				</tr>
				<tr>
					<td align="center" valign="top" height="10"></td>
				</tr>
				<tr>
					<td height="30" align="left" valign="middle" class="medium">
						<bean:message bundle="classmanage" key="class.college" />
						:
						<html:select styleClass="select01" property="college" onchange="changeCollge(this.value)">
							<html:option value="">------------------------</html:option>
							<html:options collection="collegeList" labelProperty="collegeName" property="collegeId" />
						</html:select>
						&nbsp;&nbsp;&nbsp;&nbsp;
						<bean:message bundle="classmanage" key="class.name" />
						:
						<html:select styleClass="select01" property="classes">
							<html:option value="">------------------------</html:option>
						</html:select>
					</td>
				</tr>
				
				<tr>
					<td height="30" align="right" valign="middle">
						<html:submit property="sureSub" styleClass="button_nor" onclick="javascript: return onSureChange();">
							<bean:message bundle="classmanage" key="studentsearch.sure" />
						</html:submit>
					</td>
				</tr>
			</html:form>
		</table>
	</body>
</center>
<script language="JavaScript">
	function DoExport(){

	 	document.all("export").value='export';
	 	document.forms[0].submit();
	 }
	function NotExport(){
		if(document.all("pager.offset")!=null){
			document.all("pager.offset").value='0';
		}
	 	document.all("export").value='';
	 }
<!-- class list -->
	var classescount;
	classescount = 0;
	classes = new Array(); 
	<%	
		ArrayList classeslist=(ArrayList)request.getAttribute("classList");		
		int i = 0;
		for(i=0;i<classeslist.size();i++){
			Classmodel classmodel = (Classmodel)classeslist.get(i);
			String classid=classmodel.getClassId();
			String className=classmodel.getClassName();	
			String classNo=classmodel.getClassNo();
			String collegeId = classmodel.getYxCollege().getCollegeId();
	%>
			classes[<%=i%>]= new Array("<%=classid%>","<%=classNo%>","<%=collegeId%>"); 
	<%	
		}	
	%>
	classescount=<%=classeslist.size()%>
	

	function changeCollge(college){
	 	document.all("classes").length=0;
	 	var collegeId=college; 
		var j; 
		document.all("classes").options[document.all("classes").length]=new Option("------------------------","");
		for (j=0; j<classescount; j++) 
		{ 
			if (classes[j][2] == collegeId) 
			{ 
				document.all("classes").options[document.all("classes").length]= new Option(classes[j][1],classes[j][0]);
			} 
		} 
		
	 }
	 	function changeCollgeId(college){
	 	document.all("classmodel.classId").length=0;
	 	var collegeId=college; 
		var j; 
		document.all("classmodel.classId").options[document.all("classmodel.classId").length]=new Option("------------------------","");
		for (j=0; j<classescount; j++) 
		{ 
			if (classes[j][2] == collegeId) 
			{ 
				document.all("classmodel.classId").options[document.all("classmodel.classId").length]= new Option(classes[j][1],classes[j][0]);
			} 
		} 
		
	 }
	 function onSureChange(){ 
	 document.all("export").value='';
	 	if(document.all.deleteX!=null){	 	
	 		if(document.all.deleteX.length==null){
	 			if(document.all.deleteX.checked==true){
	 				if(document.all("classes").value==""){
				 	 	if(!confirm("此操作将取消其班级属性，是否继续？")){
			 				return false;
			 			}else{
			 				document.forms[0].action="classAction.do?method=saveAlert";
	 						return true;
			 			}
				 	 }
	 				if(!confirm("是否确定要调整？")){
			 			return false;
			 		}
			 		document.forms[0].action="classAction.do?method=saveAlert";
	 				return true;
	 			}else{	 
	 				alert("请先选择要调整的对象");			
	 				return false;
	 			}
	 		}	
			 for(i=0;i<document.all.deleteX.length;i++){
			 	if(document.all.deleteX[i].checked==true){
			 		if(document.all("classes").value==""){
				 	 	if(!confirm("此操作将取消学生的班级属性，是否继续？")){
				 	 		return false;
				 	 	}else{
				 	 		document.forms[0].action="classAction.do?method=saveAlert";
				 	 		return true;
				 	 	}
				 	 }
			 		if(!confirm("是否确定要调整？")){
			 			return false;
			 		}
			 		
			 		document.forms[0].action="classAction.do?method=saveAlert";
			 		return true;
			 	}else{
			 		continue;
			 	}	 			
			 }	
			 	alert("请先选择要调整的对象");
		 		return false;
		 }else{
		 		alert("没有可调整的对象");
		 		return false;
		 }
	 }
	 
	 
	  function my_onload(){

	 	if(document.all("college").value!=""){
		 	document.all("classes").length=0;
			var j; 
			document.all("classes").options[document.all("classes").length]=new Option("------------------------","");
			for (j=0; j<classescount; j++) 
			{ 
				if (classes[j][2] == document.all("college").value) 
				{ 
					document.all("classes").options[document.all("classes").length]= new Option(classes[j][1],classes[j][0]);
					if(classes[j][0]==document.all("myclass").value){
						document.all("classes").options[document.all("classes").length-1].selected=true;
					}
				} 
			} 
	 	}
	 	if(document.all("collegeId").value!=""){
		 	document.all("classmodel.classId").length=0;
			var j; 
			document.all("classmodel.classId").options[document.all("classmodel.classId").length]=new Option("------------------------","");
			for (j=0; j<classescount; j++) 
			{ 
				if (classes[j][2] == document.all("collegeId").value) 
				{ 
					document.all("classmodel.classId").options[document.all("classmodel.classId").length]= new Option(classes[j][1],classes[j][0]);
					if(classes[j][0]==document.all("myclassId").value){
						document.all("classmodel.classId").options[document.all("classmodel.classId").length-1].selected=true;
					}
				} 
			} 
	 	}
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	 	
	 	}
	 	
	 
	 window.onload=my_onload;	
	 
	 </script>
