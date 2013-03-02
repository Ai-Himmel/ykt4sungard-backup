<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.Classmodel"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ include file="../tiles/include.jsp"%>
<%@ page import="java.util.HashMap"%>
<script language="JavaScript">
function clearAll(){
	document.all("classId").value="";
	document.all("assistant").value="";
	document.all("studentmodel.enterenceNo").value="";
	document.all("studentmodel.studentNo").value="";
	document.all("studentmodel.stuName").value="";
	document.all("studentmodel.gender").value="";
	document.all("area").value="";
	document.all("location").value="";
	document.all("dormitory").value="";
	document.all("roomnumber").value="";
	document.all("studentmodel.nation").value="";
	document.all("studentmodel.polityBg").value="";
	document.all("studentmodel.nationality").value="";
	document.all("studentmodel.idCard").value="";
	document.all("studentmodel.cultureMode").value="";
	document.all("studentmodel.studentChar").value="";
	document.all("checkornot1").value="";
	document.all("schoolornot1").value="";	
	
}
function newpage(){
	window.open ('studentAction.do?method=load4StudenthlxyListColumnSelect','studentListColumnSelect','height=400,width=600,top=0,left=0,toolbar=no,menubar=no,scrollbars=no, resizable=no,location=no, status=no'); 
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
		<table width="<bean:write name="width"/>" border="0" align="center" cellpadding="0" cellspacing="0">
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
					<html:form action="studentAction.do?method=load4Search&getrole=2">
						<table width=900px border=1 align="left" cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=resetFrom>
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
									
									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.nation" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.nation">
											<html:option value="">-------------------------</html:option>
											<html:options collection="nationList" labelProperty="dictCaption" property="dictValue" />
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
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.area" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select property="area" styleClass="select01" onchange="javascript:changeArea(this.value);" style="width:120">
											<html:option value="">---------------------</html:option>
											<html:options collection="areaList1" property="dictValue" labelProperty="dictCaption" />
										</html:select>
									</td>								
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.location1" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="location" onchange="changeLocation(this.value)">
											<html:option value="">-------------------------</html:option>
											<html:options collection="locationList1" labelProperty="dictCaption" property="dictValue" />
										</html:select>
									</td>
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="studentsearch.dormitory" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="dormitory">
											<html:option value="">-------------------------</html:option>
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
									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.politybg" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.polityBg">
											<html:option value="">-------------------------</html:option>
											<html:options collection="polityList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
									</td>
									
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.nationality" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="studentmodel.nationality">
											<html:option value="">-----------------------------------------</html:option>
											<html:options collection="nationalityList" labelProperty="dictCaption" property="dictValue" />
										</html:select>
									</td>									
								</tr>
								<tr align="right" valign="middle">
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.idCard" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">			  
										<html:text property="studentmodel.idCard" styleClass="input_box_stu" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();"/>									  
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
									<td align="left" valign="middle" class="tableHeader3" >
										<html:select styleClass="select01" property="schoolornot1">
											<html:option value="">-------------------------</html:option>
											<html:option value="1"><bean:message bundle="classmanage" key="studentsearch.yes" /></html:option>
											<html:option value="0"><bean:message bundle="classmanage" key="studentsearch.no" /></html:option>
										</html:select>
									</td>
									<td width="12%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="studentsearch.enterenceNo" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:text property="studentmodel.enterenceNo" styleClass="input_box_stu" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
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
											<html:button property="columnselect" styleClass="button_nor"
												onclick="newpage();">
												<bean:message key="button.columnselect" />
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
				<td height="20" align="left" valign="middle" class="medium">
				    <logic:present name="studentmodels" scope="request">
					<a href="javascript:DoExport()">导出Excel<IMG src="./pages/style/default/images/xls.gif" border="0"></a>
					</logic:present>
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="40" align="center" valign="top">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
						<tbody>
							<tr align="center" valign="middle">
							<logic:equal name="studentlc" value="1" property="classId">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('name')"><bean:message bundle="classmanage" key="class.name" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="assistant">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('assistant')"><bean:message bundle="classmanage" key="class.assistant" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="studentNo">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')"><bean:message bundle="classmanage" key="studentsearch.studentNo" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="enterenceNo">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('enterenceNo')"><bean:message bundle="classmanage" key="studentsearch.enterenceNo" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="stuName">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('stuName')"><bean:message bundle="classmanage" key="studentsearch.stuName" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="gender">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('gender')"><bean:message bundle="classmanage" key="studentsearch.gender" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="nation">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('nation')"><bean:message bundle="classmanage" key="studentsearch.nation" /></a>
								</td>
								
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="nationality">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('nationality')"><bean:message bundle="classmanage" key="studentsearch.nationality" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="idType">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('idType')"><bean:message bundle="classmanage" key="studentsearch.idType" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="idCard">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('idCard')"><bean:message bundle="classmanage" key="studentsearch.idCard" /></a>
								</td>	
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="cultureMode">							
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('cultureMode')"><bean:message bundle="classmanage" key="studentsearch.cultureMode" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="studentChar">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('studentChar')"><bean:message bundle="classmanage" key="studentsearch.studentChar" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="checkornot">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('checkornot')"><bean:message bundle="classmanage" key="studentsearch.checkornot" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="schoolornot">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('schoolornot')"><bean:message bundle="classmanage" key="studentsearch.schoolornot" /></a>
								</td>		
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="polityBg">						
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('polityBg')"><bean:message bundle="classmanage" key="studentsearch.politybg" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="area">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('area')"><bean:message bundle="classmanage" key="studentsearch.location" /></a>
								</td>
									</logic:equal>
									
									<logic:equal name="studentlc" value="1" property="location">							
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('location')"><bean:message bundle="classmanage" key="studentsearch.location1" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="dormitory">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('dormitory')"><bean:message bundle="classmanage" key="studentsearch.dormitory" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="roomnumber">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('roomNumber')"><bean:message bundle="classmanage" key="studentsearch.roomnumber" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="birthday">
								<td height="24" valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('birthday')"><bean:message bundle="classmanage" key="studentsearch.birthday" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="homeTelephone">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('homeTelephone')"><bean:message bundle="classmanage" key="studentsearch.homeTelephone" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="tempecardNo">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('tempecardNo')"><bean:message bundle="classmanage" key="studentsearch.tempecardNo" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="studentNo">

								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')"><bean:message bundle="classmanage" key="studentsearch.studentNo" /></a>
								</td>
								</logic:equal>
								
								<logic:equal name="studentlc" value="1" property="stuName">
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('stuName')"><bean:message bundle="classmanage" key="studentsearch.stuName" /></a>
								</td>	
								</logic:equal>							
							</tr>
							<logic:present name="studentmodels" scope="request">
								<%int itemNo = ((Integer) request.getAttribute("studentCount"))
					.intValue();%>
								<pg:pager url="./studentAction.do" items="<%=itemNo%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%=true%>" export="offset,currentPageNumber=pageNumber" scope="request">
									<%-- keep track of preference --%>
									<pg:param name="method" />
									<pg:param name="studentmodel.enterenceNo" />									
									<pg:param name="studentmodel.studentNo" />
									<pg:param name="studentmodel.stuName" />
									<pg:param name="studentmodel.gender" />
									<pg:param name="studentmodel.nation" />
									<pg:param name="studentmodel.fromProvince" />
									<pg:param name="studentmodel.polityBg" />
									<pg:param name="studentmodel.majorin" />
									
									<pg:param name="studentmodel.idCard" />								
									<pg:param name="studentmodel.cultureMode" />
									<pg:param name="studentmodel.studentChar" />
									<pg:param name="checkornot1" />
									<pg:param name="schoolornot1" />
									
									<pg:param name="college" />
									<pg:param name="classId" />
									<pg:param name="assistant" />
									<pg:param name="area" />
									<pg:param name="location" />
									<pg:param name="dormitory" />
									<pg:param name="roomnumber" />
									<pg:param name="page" />
									<pg:param name="orderby" />
									<pg:param name="sort" />
									<pg:param name="horder" />
									<pg:param name="getrole" />
									
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
											<logic:equal name="studentlc" value="1" property="classId">

											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="classId" />
												<logic:empty name="studentwithallinfo" property="classId">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="assistant">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="assistant" />
												<logic:empty name="studentwithallinfo" property="assistant">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="studentNo">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="studentNo" />
												<logic:empty name="studentwithallinfo" property="studentNo">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="enterenceNo">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="enterenceNo" />
												<logic:empty name="studentwithallinfo" property="enterenceNo">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="stuName">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="stuName" />
												<logic:empty name="studentwithallinfo" property="stuName">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="gender">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="gender" />
												<logic:empty name="studentwithallinfo" property="gender">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="nation">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="nation" />
												<logic:empty name="studentwithallinfo" property="nation">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="nationality">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="nationality" />
												<logic:empty name="studentwithallinfo" property="nationality">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											
											<logic:equal name="studentlc" value="1" property="idType">
											
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="idType" />
												<logic:empty name="studentwithallinfo" property="idType">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="idCard">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="idCard" />
												<logic:empty name="studentwithallinfo" property="idCard">
														&nbsp;													
													</logic:empty>
											</td>	
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="cultureMode">										
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="cultureMode" />
												<logic:empty name="studentwithallinfo" property="cultureMode">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="studentChar">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="studentChar" />
												<logic:empty name="studentwithallinfo" property="studentChar">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="checkornot">
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
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="schoolornot">

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
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="polityBg">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="polityBg" />
												<logic:empty name="studentwithallinfo" property="polityBg">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="area">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="area" />
												<logic:empty name="studentwithallinfo" property="area">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="location">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="location" />
												<logic:empty name="studentwithallinfo" property="location">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="dormitory">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="dormitory" />
												<logic:empty name="studentwithallinfo" property="dormitory">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="roomnumber">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="roomnumber" />
												<logic:empty name="studentwithallinfo" property="roomnumber">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="birthday">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="birthday" />
												<logic:empty name="studentwithallinfo" property="birthday">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="homeTelephone">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="homeTelephone" />
												<logic:empty name="studentwithallinfo" property="homeTelephone">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											<logic:equal name="studentlc" value="1" property="tempecardNo">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="tempecardNo" />
												<logic:empty name="studentwithallinfo" property="tempecardNo">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="studentNo">

											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="studentNo" />
												<logic:empty name="studentwithallinfo" property="studentNo">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											<logic:equal name="studentlc" value="1" property="stuName">
											<td align="center" valign="middle">
												<bean:write name="studentwithallinfo" property="stuName" />
												<logic:empty name="studentwithallinfo" property="stuName">
														&nbsp;													
													</logic:empty>
											</td>
											</logic:equal>
											
											</tr>
										</pg:item>
									</logic:iterate>
									<jsp:include page="./pagenoexcel.jsp" flush="true" />

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
    <td height="40" align="left" valign="middle">    
    <c:if test="${listcount!=null}" >
        <font color="#000000" size="2.5"><bean:message bundle="classmanage" key="studentsearch.sum" /><c:out value="${listcount}" /><bean:message bundle="classmanage" key="studentsearch.count" /></font>
    </c:if>
        
    </td>
  </tr>	  								
			<tr>
				<td>
					&nbsp;
				</td>
			<tr>
		</table>
	</body>
</center>

<script language="JavaScript">
	 	 <!-- location list -->
 
		var locationcount;
		locationcount = 0;
		locations = new Array(); 
	<%	
		ArrayList locationlist=(ArrayList)request.getAttribute("locationList1");
		int l1 = 0;
		for(l1=0;l1<locationlist.size();l1++){
			HashMap map1 = (HashMap)locationlist.get(l1);
			String locationid = (String)map1.get("dictValue");
			String locationname = (String)map1.get("dictCaption");
			String area = (String)map1.get("area");
	%>
		locations[<%=l1%>]= new Array("<%=locationid%>","<%=locationname%>","<%=area%>"); 
	<%	
		}	
	%>

	locationcount=<%=locationlist.size()%> 
 
	function changeArea(area){
		document.all["location"].length=0;
		var areaId=area;
		var j1; 
		document.all["location"].options[document.all["location"].length]= new Option("-------------------------","");
			for (j1=0;j1 < locationcount; j1++) 
			{ 
				if (locations[j1][2] == areaId) 
				{ 
					document.all["location"].options[document.all["location"].length]= new Option(locations[j1][1],locations[j1][0]);
				} 
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
	

	 
	 
	 	 <!-- dormitory list -->
 
		var dormcount;
		dormcount = 0;
		dormitorys = new Array(); 
	<%	
		ArrayList dromitorylist=(ArrayList)request.getAttribute("buildingList1");
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

	 	
	 	if(document.all("location").value!=""){	 	
	 		document.all["dormitory"].length=0;
			var j; 
			document.all["dormitory"].options[document.all["dormitory"].length]= new Option("-------------------------","");
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all("location").value) 
				{ 
					document.all["dormitory"].options[document.all["dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("mydormitory").value){
					document.all("dormitory").options[document.all("dormitory").length-1].selected=true;
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
      
  document.studentForm.action="studentAction.do?method=load4Search&getrole=2";
  document.studentForm.submit();
}

</script>
