<%@ include file="../tiles/include.jsp"%>

<script language="JavaScript">
function clearAll(){
	document.all("studentmodel.studentNo").value="";
	document.all("studentmodel.stuName").value="";
	document.all("classes").value="";
	document.all("operatorTime1").value="";
	document.all("operatorTime2").value="";
}

function document.onkeydown(){

	var e=event.srcElement;
	if(event.keyCode==13){
	
		document.all("search").click();
		return false;
	}
}

	function on_validate(){
	 	var startDate = document.all("operatorTime1").value;
	 	var endDate = document.all("operatorTime2").value;
	 	if(startDate!=""&&endDate!=""&&startDate>endDate){
	 		alert('<bean:message bundle="classmanage" key="classAlert.operator_timeComp" />');
	 		return false;
	 	}else{
		return true;
		}
	}
</script>
<center>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<html:form action="classAction.do?method=load4AlertSearch" onsubmit="javascript:return on_validate();">
			<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium"><bean:message bundle="classmanage" key="classAlert.classAlertHisRec" /></font></strong>
					</td>
				</tr>
				<tr>
					<td align="center" valign="top" height="10"></td>
				</tr>
				<tr>
					<td>
						<INPUT type="hidden" name="export" value="">
					</td>
				</tr>
				<tr>
					<td align="center" valign="top">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
							<tbody>
								<tr align="center" valign="middle">
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="studentsearch.studentNo" /></span>
									</td>
									<td width="23%" align="left" valign="middle" class="tableHeader3">
										<html:text property="studentmodel.studentNo" styleClass="input_box" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
									</td>
									<td width="10%" align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.stuName" />
									</td>
									<td width="23%" align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<html:text property="studentmodel.stuName" styleClass="input_box" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
									</td>
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="class.name" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="classes" onchange="">
											<html:option value="">------------------------</html:option>
											<html:options collection="classList" labelProperty="classNo" property="classId" />
										</html:select>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="classAlert.operator_time1" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
										<table width="100%" border="0" cellspacing="0" cellpadding="0">
											<tr>
												<td width="130">
													<html:text property="operatorTime1" styleClass="input_box" maxlength="14" readonly="true" />
												</td>
												<td>
													<img name="sd" class="img_nor" width="21" height="21" border="0" onclick="setday(this,document.all.operatorTime1)">
												</td>
											</tr>
										</table>
									</td>
									<td align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="classAlert.operator_time2" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" colspan="3">
										<table width="100%" border="0" cellspacing="0" cellpadding="0">
											<tr>
												<td width="130">
													<html:text property="operatorTime2" styleClass="input_box" maxlength="14" readonly="true" />
												</td>
												<td>
													<img name="sd" class="img_nor" width="21" height="21" border="0" onclick="setday(this,document.all.operatorTime2)">
												</td>
											</tr>
										</table>
									</td>
								</tr>
							</tbody>
						</table>
					</td>
				</tr>
				<tr>
					<td height="40" align="right" valign="middle" class="tdborder02" >
						<html:submit property="search" styleClass="button_nor" onclick="javascript:NotExport();">
							<bean:message key="button.query" />
						</html:submit>
						<html:button property="reset" styleClass="button_nor" onclick="clearAll();">
							<bean:message key="button.reset" />
						</html:button>
					</td>
				</tr>
				<tr>
					<td align="center" valign="middle" class="medium">
						&nbsp;
					</td>
				</tr>
				<tr>
					<td height="40" align="center" valign="top">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<tbody>
								<tr align="center" valign="middle">
									<td height="24" valign="middle" class="tableHeader">
										<a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')"><bean:message bundle="classmanage" key="studentsearch.studentNo" /></a>
									</td>
									<td valign="middle" class="tableHeader">
										<a style="font-size:14px;color: black" href="javascript:DoSort('stuName')"><bean:message bundle="classmanage" key="studentsearch.stuName" /></a>
									</td>
									<td valign="middle" class="tableHeader">
										<a style="font-size:14px;color: black" href="javascript:DoSort('collegeO')"><bean:message bundle="classmanage" key="classAlert.college_o" /></a>
									</td>
									<td valign="middle" class="tableHeader">
										<a style="font-size:14px;color: black" href="javascript:DoSort('classO')"><bean:message bundle="classmanage" key="classAlert.class_o" /></a>
									</td>
									<td valign="middle" class="tableHeader">
										<a style="font-size:14px;color: black" href="javascript:DoSort('assistantO')"><bean:message bundle="classmanage" key="classAlert.assistant_o" /></a>
									</td>	
									<td valign="middle" class="tableHeader">
										<a style="font-size:14px;color: black" href="javascript:DoSort('collegeN')"><bean:message bundle="classmanage" key="classAlert.college_n" /></a>
									</td>								
									<td valign="middle" class="tableHeader">
										<a style="font-size:14px;color: black" href="javascript:DoSort('classN')"><bean:message bundle="classmanage" key="classAlert.class_n" /></a>
									</td>
									<td valign="middle" class="tableHeader">
										<a style="font-size:14px;color: black" href="javascript:DoSort('assistantN')"><bean:message bundle="classmanage" key="classAlert.assistant_n" /></a>
									</td>									
									<td valign="middle" class="tableHeader">
										<a style="font-size:14px;color: black" href="javascript:DoSort('operator')"><bean:message bundle="classmanage" key="classAlert.operator" /></a>
									</td>
									<td valign="middle" class="tableHeader">
										<a style="font-size:14px;color: black" href="javascript:DoSort('operatetime')"><bean:message bundle="classmanage" key="classAlert.operator_time" /></a>
									</td>
								</tr>
								<logic:present name="classAlertHis" scope="request">
									<%int itemNo = ((Integer) request.getAttribute("hisCount"))
					.intValue();%>
									<pg:pager url="./classAction.do" items="<%=itemNo%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%=true%>" export="offset,currentPageNumber=pageNumber" scope="request">
										<%-- keep track of preference --%>
										<pg:param name="method" />
										<pg:param name="studentmodel.studentNo" />
										<pg:param name="studentmodel.stuName" />
										<pg:param name="classes" />
										<pg:param name="operatorTime1" />
										<pg:param name="operatorTime2" />
										<pg:param name="page" />
										<pg:param name="orderby" />
										<pg:param name="sort" />										
							            <pg:param name="horder" />

										<%-- save pager offset during form changes --%>
										<input type="hidden" name="pager.offset" value="<%= offset %>">

										<logic:iterate name="classAlertHis" id="alerthistory">
											<pg:item>
												<c:if test="${i%2 == 0}">
													<tr align="center" valign="middle">
														<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="alerthistory" property="studentNo" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="alerthistory" property="stuName" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="alerthistory" property="collegeO" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="alerthistory" property="classO" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="alerthistory" property="assistantO" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<font color="#990000"><bean:write name="alerthistory" property="collegeN" /></font>
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<font color="#990000"><bean:write name="alerthistory" property="classN" /></font>
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<font color="#990000"><bean:write name="alerthistory" property="assistantN" /></font>
															&nbsp;
														</td>														
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="alerthistory" property="operator" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="alerthistory" property="operatorTime" />
															&nbsp;
														</td>
													</tr>
												</c:if>
												<c:if test="${i%2 != 0}">
													<tr align="center" valign="middle" bgcolor="#F6F4F5">
														<td height="24" align="center" valign="middle">
															<bean:write name="alerthistory" property="studentNo" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="alerthistory" property="stuName" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="alerthistory" property="collegeO" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="alerthistory" property="classO" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="alerthistory" property="assistantO" />
															&nbsp;
														</td>	
														<td align="center" valign="middle">
															<bean:write name="alerthistory" property="collegeN" />
															&nbsp;
														</td>													
														<td align="center" valign="middle">
															<bean:write name="alerthistory" property="classN" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="alerthistory" property="assistantN" />
															&nbsp;
														</td>														
														<td align="center" valign="middle">
															<bean:write name="alerthistory" property="operator" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="alerthistory" property="operatorTime" />
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
    <logic:notPresent name="classAlertHis" scope="request">	
		  </tbody>
        </table>
      </td>
   </tr>
   </logic:notPresent>  														
								
				
  <tr> 
    <td height="40" align="left" valign="middle">    
    <c:if test="${hisCount!=null}" >
        <font color="#000000" size="2.5"><bean:message bundle="classmanage" key="classAlert.sum" /><c:out value="${hisCount}" /><bean:message bundle="classmanage" key="classAlert.count" /></font>
    </c:if>
        
    </td>
  </tr>						
							
				<jsp:include page="./dateSelect.jsp" flush="true" />
				<tr>
					<td height="30" align="right" valign="middle">
						&nbsp;
					</td>
				</tr>
				<br>
			</table>
<input name="orderby" type="hidden" value="">
<logic:present name="order" scope="request">
  <input name="horder" type="hidden" value="<bean:write name="order" />"> 
  </logic:present>
  <logic:notPresent name="order" scope="request">
  <input name="horder" type="hidden" value="a"> 
</logic:notPresent>
		</html:form>
	</body>
</center>  
<script language="JavaScript">	 
	function DoExport(){
	 	document.all("export").value='export';
	 	document.forms[0].submit();
	 }
	function NotExport(){
		if(document.forms[0].elements["pager.offset"]!=null){
			document.forms[0].elements["pager.offset"].value="0";
	 	}
	 	document.all("export").value='';
	 }

function DoSort(col){
  document.all("export").value='';
  document.all.orderby.value=col;  
  if(document.all.horder.value=='a')
      document.all.horder.value='d';
  else if(document.all.horder.value=='d')
      document.all.horder.value='a';
      
  document.classForm.action="classAction.do?method=load4AlertSearch";
  document.classForm.submit();
}	 
</script>