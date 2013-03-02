<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.Classmodel"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ include file="../tiles/include.jsp"%>
<%@ page import="java.util.HashMap"%>
 <script type='text/javascript' src='<s:url value="/dwr/engine.js"/>'> </script>
  
  <script type='text/javascript' src='<s:url value="/dwr/interface/QuartersMaintain.js"/>'></script>
  <script type='text/javascript' src='<s:url value="/dwr/util.js"/>'> </script>
<script language="JavaScript">
function clearAll(){
	document.all("college").value="";
	document.all("classId").value="";
	document.all("assistant").value="";
	document.all("studentmodel.studentNo").value="";
	document.all("studentmodel.stuName").value="";
	document.all("studentmodel.gender").value="";
	document.all("location").value="";
	document.all("dormitory").value="";
	document.all("roomnumber").value="";
	document.all("studentmodel.fromProvince").value="";
	document.all("studentmodel.nation").value="";
	document.all("studentmodel.polityBg").value="";
	document.all("studentmodel.majorin").value="";
	document.all("studentmodel.nationality").value="";
	document.all("studentmodel.department").value="";		
	document.all("studentmodel.idType").value="";
	document.all("studentmodel.cultureMode").value="";
	document.all("studentmodel.studentChar").value="";
	document.all("checkornot1").value="";
	document.all("schoolornot1").value="";		
	
	
}

function document.onkeydown(){

	var e=event.srcElement;
	if(event.keyCode==13){
	
		document.all("search").click();
		return false;
	}
}
</script>

<center>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="220%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<TABLE width="50%" align="center">
						<tr>
							<td>
								<strong><font class="medium"><bean:message bundle="classmanage" key="studentsearch.studentsearch" /></font></strong>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr align="left">
				<td align="left" valign="top" width="50%">
					<html:form action="studentAction.do?method=load4Search">
						<table width=50% border=1 align="left" cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=resetFrom>
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
								<td>
									<%if (request.getAttribute("mydormitory") != null) {
				String mydormitory = request.getAttribute("mydormitory")
						.toString();

				%>
									<INPUT type="hidden" name="mydormitory" value="<%=mydormitory%>">
									<%} else {

			%>
									<INPUT type="hidden" name="mydormitory" value="">

									<%}

			%>
								</td>
							</tr>
							<tr>
								<td>
									<INPUT type="hidden" name="export" value="">
								</td>
							</tr>
							<tr>
								<td>
									<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
								</td>
							</tr>
							<tbody>
								<tr align="center" valign="middle">
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										书院/学院
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="college" onchange="changeCollge(this.value)">
											<html:option value="">-------------------------</html:option>
											<html:options collection="collegeList" labelProperty="collegeName" property="collegeId" />
										</html:select>
									</td>
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="class.name" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="classId">
											<html:option value="">-------------------------</html:option>
											<html:options collection="classList" labelProperty="classNo" property="classId" />
										</html:select>
									</td>
									<td width="10%" align="right" valign="middle" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="classsearch.assistant" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="assistant">
											<html:option value="">-------------------------</html:option>
											<html:options collection="assistantList" labelProperty="managerName" property="managerId" />
										</html:select>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="studentsearch.studentNo" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:text property="studentmodel.studentNo" styleClass="input_box_stu" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
									</td>

									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.stuName" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<html:text property="studentmodel.stuName" styleClass="input_box_stu" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
									</td>
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.gender" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.gender">
											<html:option value="">-------------------------</html:option>
											<html:options collection="genderList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="classsearch.location" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select  styleId="area" styleClass="select01" property="area" onchange="QuartersMaintain.setLocations(dwr.util.getValue($('area')));">
											<html:option value="">-------------------------</html:option>
											<html:options collection="areaList" labelProperty="name" property="id" />
										</html:select>
									</td>
									<td width="10%" align="right" valign="middle" class="tableHeader2">
										<span class="medium">区域</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										
										<html:select styleId="location" styleClass="select01" property="location" onchange="QuartersMaintain.setDormitory(dwr.util.getValue($('location')));">
											<html:option value="">-------------------------</html:option>
											<html:options collection="locationList" labelProperty="name" property="id" />
										</html:select>
									</td>
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="studentsearch.dormitory" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleId="dormitory" styleClass="select01" property="dormitory">
											<html:option value="">-------------------------</html:option>
											
											<html:options collection="dormitoryList" labelProperty="name" property="id" />
										</html:select>
									</td>
									
								</tr>
								<tr align="right" valign="middle">
								    <td width="10%" align="right" valign="middle" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="studentsearch.roomnumber" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:text property="roomnumber" styleClass="input_box_stu" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
									</td>
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.province" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.fromProvince">
											<html:option value="">-------------------------</html:option>
											<html:options collection="provinceList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
									</td>
									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.nation" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.nation">
											<html:option value="">-------------------------</html:option>
											<html:options collection="nationList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
									</td>
									
								</tr>
								<tr align="right" valign="middle">
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.department" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">			  
										<html:select styleClass="select01" property="studentmodel.department">
											<html:option value="">-------------------------------------</html:option>
											<html:options collection="departmentList" labelProperty="deptName" property="deptCode" />
										</html:select>									  
									</td>
									
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.majorin" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.majorin">
											<html:option value="">-------------------------------------</html:option>
											<html:options collection="majorinList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
									</td>
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.nationality" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.nationality">
											<html:option value="">-----------------------------------------</html:option>
											<html:options collection="nationalityList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
									</td>
								</tr>
								<tr align="right" valign="middle">
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.idType" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">			  
										<html:select styleClass="select01" property="studentmodel.idType">
											<html:option value="">-------------------------</html:option>
											<html:options collection="idTypeList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>									  
									</td>
									
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.cultureMode" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.cultureMode">
											<html:option value="">-------------------------</html:option>
											<html:options collection="cultureModeList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
									</td>
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.studentChar" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.studentChar">
											<html:option value="">-------------------------</html:option>
											<html:options collection="studentCharList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
									</td>
								</tr>	
								<tr align="right" valign="middle">
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.checkornot" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">			  
										<html:select styleClass="select01" property="checkornot1">
											<html:option value="">-------------------------</html:option>
											<html:option value="1"><bean:message bundle="classmanage" key="studentsearch.yes" /></html:option>
											<html:option value="0"><bean:message bundle="classmanage" key="studentsearch.no" /></html:option>
										</html:select>									  
									</td>
									
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.schoolornot" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="schoolornot1">
											<html:option value="">-------------------------</html:option>
											<html:option value="1"><bean:message bundle="classmanage" key="studentsearch.yes" /></html:option>
											<html:option value="0"><bean:message bundle="classmanage" key="studentsearch.no" /></html:option>
										</html:select>
									</td>
									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.politybg" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.polityBg">
											<html:option value="">-------------------------</html:option>
											<html:options collection="polityList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
									</td>
								</tr>																	
							

							</tbody>
						</table>
						<tr>
							<td>
								<table width="50%" align="left">
									<tr align="left">
										<td width="100%" height="40" align="left" valign="middle" class="tdborder02" onclick="javascript:NotExport();">
											<html:submit property="search" styleClass="button_nor">
												<bean:message key="button.query" />
											</html:submit>
											<html:button property="reset" styleClass="button_nor" onclick="clearAll();">
												<bean:message key="button.reset" />
											</html:button>
										</td>
									</tr>
								</table>
							</td>
						</tr>
						<logic:present name="orderby" scope="request">
							<input name="orderby" type="hidden" value="<bean:write name="orderby" />">
						</logic:present>
						<logic:notPresent name="orderby" scope="request">
							<input name="orderby" type="hidden" value="">
						</logic:notPresent>
						<logic:present name="order" scope="request">
							<input name="horder" type="hidden" value="<bean:write name="order" />">
						</logic:present>
						<logic:notPresent name="order" scope="request">
							<input name="horder" type="hidden" value="a">
						</logic:notPresent>
					</html:form>
				</td>
			</tr>
			<tr>
				<td height="20" align="center" valign="middle" class="medium">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="40" align="center" valign="top">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
						<tbody>
							<tr align="center" valign="middle">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('college')">书院/学院</a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('name')"><bean:message bundle="classmanage" key="class.name" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('assistant')"><bean:message bundle="classmanage" key="class.assistant" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')"><bean:message bundle="classmanage" key="studentsearch.studentNo" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('enterenceNo')"><bean:message bundle="classmanage" key="studentsearch.enterenceNo" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('stuName')"><bean:message bundle="classmanage" key="studentsearch.stuName" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('gender')"><bean:message bundle="classmanage" key="studentsearch.gender" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('department')"><bean:message bundle="classmanage" key="studentsearch.department" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('majorin')"><bean:message bundle="classmanage" key="studentsearch.majorin" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('nation')"><bean:message bundle="classmanage" key="studentsearch.nation" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('nationality')"><bean:message bundle="classmanage" key="studentsearch.nationality" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('province')"><bean:message bundle="classmanage" key="studentsearch.province" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('idType')"><bean:message bundle="classmanage" key="studentsearch.idType" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('cultureMode')"><bean:message bundle="classmanage" key="studentsearch.cultureMode" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('studentChar')"><bean:message bundle="classmanage" key="studentsearch.studentChar" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('checkornot')"><bean:message bundle="classmanage" key="studentsearch.checkornot" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('schoolornot')"><bean:message bundle="classmanage" key="studentsearch.schoolornot" /></a>
								</td>																	
					
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('polityBg')"><bean:message bundle="classmanage" key="studentsearch.politybg" /></a>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('area')">校区</a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('location')">区域</a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('dormitory')"><bean:message bundle="classmanage" key="studentsearch.dormitory" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('roomNumber')"><bean:message bundle="classmanage" key="studentsearch.roomnumber" /></a>
								</td>
								<td height="24" valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('birthday')"><bean:message bundle="classmanage" key="studentsearch.birthday" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('homeTelephone')"><bean:message bundle="classmanage" key="studentsearch.homeTelephone" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('tempecardNo')"><bean:message bundle="classmanage" key="studentsearch.tempecardNo" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('bathcardNo')"><bean:message bundle="classmanage" key="studentsearch.bathcardNo" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')"><bean:message bundle="classmanage" key="studentsearch.studentNo" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('stuName')"><bean:message bundle="classmanage" key="studentsearch.stuName" /></a>
								</td>								
							</tr>
							<logic:present name="studentmodels" scope="request">
								<%int itemNo = ((Integer) request.getAttribute("studentCount"))
					.intValue();%>
								<pg:pager url="./studentAction.do" items="<%=itemNo%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%=true%>" export="offset,currentPageNumber=pageNumber" scope="request">
									<%-- keep track of preference --%>
									<pg:param name="method" />
									<pg:param name="studentmodel.studentNo" />
									<pg:param name="studentmodel.stuName" />
									<pg:param name="studentmodel.gender" />
									<pg:param name="studentmodel.nation" />
									<pg:param name="studentmodel.fromProvince" />
									<pg:param name="studentmodel.polityBg" />
									<pg:param name="studentmodel.majorin" />
									<pg:param name="studentmodel.idType" />
									<pg:param name="studentmodel.cultureMode" />
									<pg:param name="studentmodel.studentChar" />
									<pg:param name="checkornot1" />
									<pg:param name="schoolornot1" />									

									<pg:param name="college" />
									<pg:param name="classId" />
									<pg:param name="assistant" />
									<pg:param name="location" />
									<pg:param name="area" />
									<pg:param name="dormitory" />
									<pg:param name="roomnumber" />
									<pg:param name="page" />
									<pg:param name="orderby" />
									<pg:param name="sort" />
									<pg:param name="horder" />

									<%-- save pager offset during form changes --%>
									<input type="hidden" name="pager.offset" value="<%= offset %>">

									<logic:iterate name="studentmodels" id="studentwithallinfo" indexId="k">
										<pg:item>
											<c:if test="${k%2 == 0}">
												<tr align="center" valign="middle" bgcolor="#FFFFFF">
											</c:if>
											<c:if test="${k%2 != 0}">
												<tr align="center" valign="middle" bgcolor="#F6F4F5">
											</c:if>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="college" />
												<logic:empty name="studentwithallinfo" property="college">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="classId" />
												<logic:empty name="studentwithallinfo" property="classId">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="assistant" />
												<logic:empty name="studentwithallinfo" property="assistant">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="studentNo" />
												<logic:empty name="studentwithallinfo" property="studentNo">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="enterenceNo" />
												<logic:empty name="studentwithallinfo" property="enterenceNo">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="stuName" />
												<logic:empty name="studentwithallinfo" property="stuName">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="gender" />
												<logic:empty name="studentwithallinfo" property="gender">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="department" />
												<logic:empty name="studentwithallinfo" property="department">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="majorin" />
												<logic:empty name="studentwithallinfo" property="majorin">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="nation" />
												<logic:empty name="studentwithallinfo" property="nation">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="nationality" />
												<logic:empty name="studentwithallinfo" property="nationality">
														&nbsp;													
													</logic:empty>
											</td>

											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="fromProvince" />
												<logic:empty name="studentwithallinfo" property="fromProvince">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="idType" />
												<logic:empty name="studentwithallinfo" property="idType">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="cultureMode" />
												<logic:empty name="studentwithallinfo" property="cultureMode">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="studentChar" />
												<logic:empty name="studentwithallinfo" property="studentChar">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
											<c:if test="${studentwithallinfo.checkornot==1}">
												<bean:message bundle="classmanage" key="studentsearch.yes" />											
											</c:if>
											<c:if test="${studentwithallinfo.checkornot==0}">
												<bean:message bundle="classmanage" key="studentsearch.no" />											
											</c:if>											
												<logic:empty name="studentwithallinfo" property="checkornot">
														&nbsp;													
												</logic:empty>
											</td>

											<td align="center" valign="middle">
											<c:if test="${studentwithallinfo.schoolornot==1}">
												<bean:message bundle="classmanage" key="studentsearch.yes" />											
											</c:if>
											<c:if test="${studentwithallinfo.schoolornot==0}">
												<bean:message bundle="classmanage" key="studentsearch.no" />											
											</c:if>																						
												<logic:empty name="studentwithallinfo" property="schoolornot">
														&nbsp;													
													</logic:empty>
											</td>											
											
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="polityBg" />
												<logic:empty name="studentwithallinfo" property="polityBg">
														&nbsp;													
													</logic:empty>
											</td>

											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="area" />
												<logic:empty name="studentwithallinfo" property="area">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="location" />
												<logic:empty name="studentwithallinfo" property="location">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="dormitory" />
												<logic:empty name="studentwithallinfo" property="dormitory">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="roomnumber" />
												<logic:empty name="studentwithallinfo" property="roomnumber">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="birthday" />
												<logic:empty name="studentwithallinfo" property="birthday">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="homeTelephone" />
												<logic:empty name="studentwithallinfo" property="homeTelephone">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="tempecardNo" />
												<logic:empty name="studentwithallinfo" property="tempecardNo">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="bathcardNo" />
												<logic:empty name="studentwithallinfo" property="bathcardNo">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="studentNo" />
												<logic:empty name="studentwithallinfo" property="studentNo">
														&nbsp;													
													</logic:empty>
											</td>
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="stuName" />
												<logic:empty name="studentwithallinfo" property="stuName">
														&nbsp;													
													</logic:empty>
											</td>
											</tr>
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
  			<c:if test="${listcount!=null}" >
  <tr> 
    <td height="40" align="left" valign="middle">    
    
        <font color="#000000" size="2.5">记录数:<c:out value="${listcount}" /></font>
    
        
    </td>
  </tr>									
	</c:if>		
		</table>
	</body>
</center>

<script language="JavaScript">
<!-- class list -->
	var classescount;
	classescount = 0;
	classesArr = new Array(); 
	
	assitantCount = 0;
	assitantArr = new Array();
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
	 
	 
	 	 <!-- dormitory list -->
 
		var dormcount;
		dormcount = 0;
		dormitorys = new Array(); 
	<%	
		ArrayList dromitorylist=(ArrayList)request.getAttribute("buildingList");
		int l = 0;
		for(l=0;l<dromitorylist.size();l++){
			HashMap map = (HashMap)dromitorylist.get(l);
			String dormitoryid = (String)map.get("dictValue");
			String dormtioryname = (String)map.get("dictCaption");
			String location = (String)map.get("location");	
	%>
		dormitorys[<%=l%>]= new Array("<%=dormitoryid%>","<%=dormtioryname%>","<%=location%>"); 
	<%	
		}	
	%>

	dormcount=<%=dromitorylist.size()%> 
 
	function changeLocation(location){
		document.all["dormitory"].length=0;
		var locationId=location;
		var j; 
		document.all["dormitory"].options[document.all["dormitory"].length]= new Option("-------------------------","");
			for (j=0;j < dormcount; j++) 
			{ 
				if (dormitorys[j][2] == locationId) 
				{ 
					document.all["dormitory"].options[document.all["dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
			} 
	}
	
	function DoExport(){
	 	document.all("export").value='export';
	 	document.forms[0].submit();
	 }
	 function NotExport(){
	 	document.all("export").value='';
	 }
	 	 
	 
	 function my_onload(){

	 	if(document.all("college").value!=""){
		 	document.all("classId").length=0;
			var j; 
			document.all("classId").options[document.all("classId").length]=new Option("-------------------------","");
			for (j=0; j<classescount; j++) 
			{ 
				if (classesArr[j][2] == document.all("college").value) 
				{ 
					document.all("classId").options[document.all("classId").length]= new Option(classesArr[j][1],classesArr[j][0]);
					if(classesArr[j][0]==document.all("myclass").value){
						document.all("classId").options[document.all("classId").length-1].selected=true;
					}
				} 
			} 
	 	}
	 	
	 	
	 	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	 }
	 
	 window.onload=my_onload;	 
	 
	 
function DoSort(col){
 NotExport();
  document.all.orderby.value=col;
  if(document.all.horder.value=='a')
      document.all.horder.value='d';
  else if(document.all.horder.value=='d')
      document.all.horder.value='a';
      
  document.studentForm.action="studentAction.do?method=load4Search";
  document.studentForm.submit();
}

</script>
