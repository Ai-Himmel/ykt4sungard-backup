<%@page pageEncoding="UTF-8"%>
<%@ page import="org.king.classmanage.web.help.MajorinWithStuCount"%>
<%@ page import="java.util.List"%>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="org.king.classmanage.domain.Collegemodel" %>
<%@ include file="../tiles/include.jsp"%>
<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<SCRIPT language=javascript>
	 function my_onload(){	 	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		} 	
	 }
	 window.onload=my_onload;
</SCRIPT>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="classmanage" key="dormDistribution.graduateAppDorm" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="right" valign="middle">
					
				</td>
			</tr>
			
			<tr>
				<td align="center" height="10">			
				</td>
			</tr>
			<tr> <INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
				<td height="40" align="center" valign="top">

						<table width=80% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<tbody>

			
								<html:form action="/dormAppAction" method="post">
								
								<logic:present name="graduateList" scope="request">									
								<logic:iterate name="graduateList" id="graduate" indexId="i">
								<tr align="center" valign=center>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										学号
									</td>
									<td width="65%" align="left" valign="middle" bgcolor="#FFFFFF" colspan="3">
										<bean:write name="graduate" property="graduateNo" />
									</td>
								</tr>
								<tr>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										姓名
									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" >
										<bean:write name="graduate" property="graduateName" />
									</td>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										性别
									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" >
						              <c:choose><c:when test="${graduate.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
						              </c:when></c:choose>
						              <c:choose><c:when test="${graduate.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
						              </c:when></c:choose>
									</td>
								</tr>
								<tr>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										学生类别
									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#FFFFFF" >
										<bean:write name="graduate" property="studentType" />
									</td>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										培养方式
									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#FFFFFF" >
										<bean:write name="graduate" property="matriculateType" />
									</td>
								</tr>
								<tr>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										录取院系
									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" >
							              <logic:present name="collegeList" scope="request">            
							               <logic:iterate name="collegeList" id="col" type="org.king.classmanage.domain.Department">
							                <c:choose><c:when test="${col.deptCode == graduate.curCollege}">              
							                <bean:write name="col" property="deptName"/>
							                </c:when></c:choose>
							               </logic:iterate>
							               </logic:present>
							              &nbsp;
									</td>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										录取专业
									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" >
						              <logic:present name="majorinlist" scope="request">            
						               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
						                <c:choose><c:when test="${ml.dictValue == graduate.speciality}">              
						                <bean:write name="ml" property="dictCaption"/>
						                </c:when></c:choose>
						               </logic:iterate>
						               </logic:present>
						              &nbsp;
									</td>
								</tr>
								<tr>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										住宿区域
									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#FFFFFF" >
										<bean:write name="graduate" property="distriction" />
									</td>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										是否需要住宿

									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#FFFFFF" >
												<input type="hidden" name="itemlist" value="<bean:write name="graduate" property="id" />">
												<c:if test="${graduate.residentNeed=='1'}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />" checked>
												</c:if>
												<c:if test="${graduate.residentNeed=='2'||graduate.residentNeed==null}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />">
												</c:if>&nbsp;&nbsp;<font color="red"><bean:message bundle="classmanage" key="student.need" /></font>
									</td>

								</tr>
								<tr class="tableHeader">
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										更新时间
									</td>
									<td width="65%" align="left" valign="middle" bgcolor="#FFFFFF" colspan="3">
										<bean:write name="graduate" property="updateDate" />
									</td>
								</tr>
								<tr class="tableHeader">
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										备注
									</td>
									<td width="65%" align="left" valign="middle" bgcolor="#FFFFFF" colspan="3">
										<textarea name="memo" cols="60" rows="3"><bean:write name="graduate" property="memo"/></textarea>
									</td>
								</tr>
								</logic:iterate>
								</logic:present>
								<logic:notPresent name="graduateList" scope="request">
								<logic:present name="stuinfoList" scope="request">									
								<logic:iterate name="stuinfoList" id="sl" indexId="i">
								<tr class="tableHeader">
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										学号
									</td>
									<td width="65%" align="left" valign="middle" bgcolor="#FFFFFF" colspan="3">
										<bean:write name="sl" property="studentNo" />
									</td>
								</tr>
								<tr>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										姓名
									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" >
										<bean:write name="sl" property="stuName" />
									</td>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										性别
									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" >
							              <c:choose><c:when test="${sl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
							              </c:when></c:choose>
							              <c:choose><c:when test="${sl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
							              </c:when></c:choose>
									</td>
								</tr>
								<tr>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										录取院系
									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#FFFFFF" >
							              <logic:present name="collegeList" scope="request">            
							               <logic:iterate name="collegeList" id="col" type="org.king.classmanage.domain.Department">
							                <c:choose><c:when test="${col.deptCode == sl.curCollege}">              
							                <bean:write name="col" property="deptName"/>
							                </c:when></c:choose>
							               </logic:iterate>
							               </logic:present>
							              &nbsp;
									</td>
									<td width="15%" height="24" valign="middle" class="tableHeader5" >
										录取专业
									</td>
									<td width="25%" align="left" valign="middle" bgcolor="#FFFFFF" >
							              <logic:present name="majorinlist" scope="request">            
							               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
							                <c:choose><c:when test="${ml.dictValue == sl.majorin}">              
							                <bean:write name="ml" property="dictCaption"/>
							                </c:when></c:choose>
							               </logic:iterate>
							               </logic:present>
							              &nbsp;
									</td>
								</tr>								
								</logic:iterate>
								</logic:present>
								</logic:notPresent>
								</html:form>
							</tbody>
							
						</table>
				</td>
			</tr>
			<%if(request.getAttribute("graduateType")!=null){ %>
				<logic:notPresent name="graduateList" scope="request">
				<tr align="center" valign="center"><td><font size="2.5" color="#990000">由于您是<%=request.getAttribute("graduateType")%>类研究生不属于可住宿范围，因此您不能申请住宿</font></td></tr>
				</logic:notPresent>
			<%}else{%>
				<logic:notPresent name="graduateList" scope="request">
				<tr align="center" valign="center"><td><font size="2.5" color="#990000">您不能申请住宿</font></td></tr>
				</logic:notPresent>
			<%}%>
			<logic:present name="graduateList" scope="request">
			<tr>
							<td height="30" align="right" valign="middle">
								<input name="Submit" type="button" class="button_nor" value="确定" onClick="javascript:baocun();">
							</td>
			</tr>
			</logic:present>
		</table>
	</body>
</center>
<SCRIPT language=javascript>

function baocun(){
	if(document.all.memo.value.length>180){
		alert("备注过长，请重输！");

	}else{
		if(document.all.itemList.checked==true){
			dormAppSearchForm.action = "<c:url value="/dormAppAction.do"/>?method=updateGraduateInfo4graduate&tag=1";
			dormAppSearchForm.submit();
		}else{
			dormAppSearchForm.action = "<c:url value="/dormAppAction.do"/>?method=updateGraduateInfo4graduate&tag=2";
			dormAppSearchForm.submit();
		}
	}
}

</SCRIPT>