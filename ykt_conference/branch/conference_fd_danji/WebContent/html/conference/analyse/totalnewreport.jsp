<%@ page pageEncoding="UTF-8"%>
<%@ include file="/html/commons/init.jsp"%>
<%@ include file="/html/commons/top_calendar.jsp"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ page
	import="com.kingstargroup.conference.hibernate.form.TConferenceType"%>
<%@ page import="java.util.HashMap"%>
<head>
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css"
		rel="stylesheet" type="text/css" />
	<html:base />
</head>
<%
	String custno = ParamUtil.getString(request, "custno");
	String custname = ParamUtil.getString(request, "custname");
	String deptCode = ParamUtil.getString(request, "dept");
	String type = ParamUtil.getString(request, "type");
	String begindate = ParamUtil.getString(request, "begindate");
	String enddate = ParamUtil.getString(request, "enddate");
%>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
	<form id="DeleteConferenceForm" name="DeleteConferenceForm"
		action="<%=ContextUtil.getCtxPath(request)%>/totalnewreport.do"
		method="post">
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td>
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="25" align="left" valign="middle"
					background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
					&nbsp;&nbsp;&nbsp;
					<span class="mediumwhite"><strong></strong> </span>&nbsp;
					<span class="mediumwhite"><strong><bean:message
								key="analyse.newtotle.list" /> </strong> </span>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width="100%" border="1" cellspacing="0" cellpadding="2"
						bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
						<tr>
							<td width="15%" height="25" align="right" valign="middle"
								bgcolor="#A9CFE2" class="medium">
								<bean:message key="attendee.custno" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<input id="custno" name="custno" class="input_box"
									style="width: 150" maxlength="15" value="<%=custno%>">
							</td>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="attendee.custname" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<input id="custno" name="custname" class="input_box"
									style="width: 150" maxlength="15" value="<%=custname%>">
							</td>
						</tr>
						<tr>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="attendee.dept" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<select name="dept" class="select01" style="width: 150"
									onChange="changeCounty()">
									<OPTION>
										-
									</OPTION>
									<%
										List deptList = GetDictionary.getDeptList();
										Iterator iter1 = deptList.iterator();
										while (iter1.hasNext()) {
											HashMap deptmap = (HashMap) iter1.next();
											if (deptCode.equals(deptmap.get("deptCode").toString())) {
									%>
									<option value="<%=deptmap.get("deptCode")%>"
										selected="selected">
										<%=deptmap.get("deptName")%>
									</option>
									<%
									} else {
									%>
									<option value="<%=deptmap.get("deptCode")%>">
										<%=deptmap.get("deptName")%>
									</option>
									<%
										}
										}
									%>
								</select>
							</td>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="conference.type" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<select name="type" class="select01" style="width: 150"
									onChange="changeCounty()">
									<OPTION>
										-
									</OPTION>
									<%
										List typeList = GetDictionary.getConfType();
										Iterator iter2 = typeList.iterator();
										while (iter2.hasNext()) {
											TConferenceType row = (TConferenceType) iter2.next();
											if (type.equals(row.getTypeName().toString())) {
									%>
									<option value="<%=row.getTypeName()%>" selected="selected">
										<%=row.getTypeName()%>
									</option>
									<%
									} else {
									%>
									<option value="<%=row.getTypeName()%>">
										<%=row.getTypeName()%>
									</option>
									<%
										}
										}
									%>
								</select>
							</td>
						</tr>
						<tr>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="conference.begindate" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<table width="100%" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td width="130">
											<input name="begindate" class="input_box" style="width: 150"
												maxlength="8" readonly="true" value="<%=begindate%>">
										</td>
										<td>
											&nbsp;&nbsp;
											<a href="#"><img
													src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/date.gif"
													width="16" height="16" border="0" id="f_trigger_begindate">
											</a>
										</td>
									</tr>
								</table>
							</td>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="conference.enddate" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<table width="100%" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td width="130">
											<input name="enddate" class="input_box" style="width: 150"
												maxlength="8" readonly="true" value="<%=enddate%>">
										</td>
										<td>
											&nbsp;&nbsp;
											<a href="#"><img
													src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/date.gif"
													width="16" height="16" border="0" id="f_trigger_enddate">
											</a>
										</td>
									</tr>
								</table>
							</td>
						</tr>

					</table>
				</td>
			</tr>
			<tr>
				<td height="40" align="right" valign="middle">
					<input name="Submit3" type="button" class="button_nor"
						value="<bean:message key="button.query"/>"
						onClick="document.forms[0].submit();">
					&nbsp;&nbsp;&nbsp;
					<input name="Submit2" type="reset" class="button_nor"
						value="<bean:message key="button.reset"/>">
				</td>
			</tr>
			<tr>
				<td align="left" valign="top" class="tdborder02">
					&nbsp;
				</td>
			</tr>
			<tr>
			<tr>
				<td align="center" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td  align="center" valign="top" class="medium">
					<table width="100%" border=1 cellpadding=1 cellspacing=0 align="center"
						bordercolor=#AA817F bordercolordark=#ffffff id="maintable">
						<tbody>
							<tr align="center" valign="middle" class="tableHeader">
								<td align="center" width="180">
									<strong><bean:message key="analyse.deptName" />
									</strong>
								</td><td align="center" width="100">
									<strong><bean:message key="analyse.custno" />
									</strong>
								</td>
								<td align="center" width="100">
									<strong><bean:message key="analyse.cutName" />
									</strong>
								</td>

								<logic:present name="confList" scope="request">
									<logic:iterate name="confList" id="conference">
										<td  valign="middle" 
											id="<bean:write name="conference" property="conId" />">
											<strong><bean:write name="conference"
													property="conName" />
											</strong>
										</td>
									</logic:iterate>
								</logic:present>
								<td valign="middle" width="70">
									<strong><bean:message key="analyse.allCount" />
									</strong>
								</td>
								<td valign="middle" width="80">
									<strong><bean:message key="analyse.shouldCount" />
									</strong>
								</td>
								<td  valign="middle" width="70">
									<strong><bean:message key="analyse.pprate" />
									</strong>
								</td>
							</tr>
							<logic:present name="deptCustList" scope="request">
								<logic:iterate name="deptCustList" id="deptcust" indexId="i">								
								<core:if test="${deptcust.custId!=null}">
									<tr align="center" valign="middle">
										<td  align="center" valign="middle"
											bgcolor="#FFFFFF" class="medium">
											<bean:write name="deptcust" property="deptName" />
										</td>
										<td  align="center" valign="middle"
											bgcolor="#FFFFFF" class="medium" id="<bean:write name="deptcust" property="deptCode" />.<bean:write name="deptcust" property="custId" />">
											&nbsp;
										</td>
										<td  align="center" valign="middle"
											bgcolor="#FFFFFF" class="medium">
											<bean:write name="deptcust" property="custName" />
										</td>
										<logic:present name="confList" scope="request">
											<logic:iterate name="confList" id="conference">
												<td  align="center" valign="middle"
													bgcolor="#FFFFFF" class="medium" id="<bean:write name="conference" property="conId" />.<bean:write name="deptcust" property="deptCode" />.<bean:write name="deptcust" property="custId" />">
													&nbsp;
												</td>
											</logic:iterate>
										</logic:present>
										<td align="center" valign="middle"
											bgcolor="#FFFFFF" class="medium" id="<bean:write name="deptcust" property="custId" />.allcount">
											&nbsp;
										</td>
										<td  align="center" valign="middle"
											bgcolor="#FFFFFF" class="medium" id="<bean:write name="deptcust" property="custId" />.shouldcount">
											&nbsp;
										</td>
										<td align="center" valign="middle"
											bgcolor="#FFFFFF" class="medium" id="<bean:write name="deptcust" property="custId" />.rate">
											&nbsp;
										</td>
									</tr>
									</core:if>
									<core:if test="${deptcust.custId==null}">
									<tr align="center" valign="middle" bgcolor="#dfe4e8">
										<td  align="center" valign="middle"
											 class="medium">
											<bean:write name="deptcust" property="deptName" />
										</td>
										<td  align="center" valign="middle"
											 class="medium">
											<bean:write name="deptcust" property="custId" />&nbsp;
										</td>
										<td  align="center" valign="middle"
											 class="medium">
											<bean:write name="deptcust" property="custName" />
										</td>
										<logic:present name="confList" scope="request">
											<logic:iterate name="confList" id="conference">
												<td  align="center" valign="middle"
													 class="medium" id="<bean:write name="conference" property="conId" />.<bean:write name="deptcust" property="deptCode" />.<bean:write name="deptcust" property="custId" />">
													&nbsp;
												</td>
											</logic:iterate>
										</logic:present>
										<td align="center" valign="middle"
											 class="medium" id="<bean:write name="deptcust" property="custId" />.allcount">
											&nbsp;
										</td>
										<td  align="center" valign="middle"
											 class="medium" id="<bean:write name="deptcust" property="custId" />.shouldcount">
											&nbsp;
										</td>
										<td align="center" valign="middle"
											 class="medium" id="<bean:write name="deptcust" property="custId" />.rate">
											&nbsp;
										</td>
									</tr>
									</core:if>
								</logic:iterate>
								
								<tr align="center" valign="middle" bgcolor="#dfe4e8">
										<td  align="center" valign="middle"
											 class="medium">
											<strong><bean:message key="analyse.mprate" />
											</strong>
										</td>
										<td  align="center" valign="middle"
											 class="medium">
											&nbsp;
										</td>
										<td  align="center" valign="middle"
											 class="medium">
											&nbsp;
										</td>
										<logic:present name="confList" scope="request">
											<logic:iterate name="confList" id="conference">
												<td  align="center" valign="middle"
													 class="medium" id="<bean:write name="conference" property="conId" />.A.">
													&nbsp;
												</td>
											</logic:iterate>
										</logic:present>
										<td align="center" valign="middle"
											 class="medium" >
											&nbsp;
										</td>
										<td  align="center" valign="middle"
											 class="medium" >
											&nbsp;
										</td>
										<td align="center" valign="middle"
											 class="medium" >
											&nbsp;
										</td>
									</tr>
									<tr align="center" valign="middle" bgcolor="#dfe4e8">
										<td  align="center" valign="middle"
											 class="medium">
											<strong><bean:message key="analyse.mlrate" />
											</strong>
										</td>
										<td  align="center" valign="middle"
											 class="medium">
											&nbsp;
										</td>
										<td  align="center" valign="middle"
											 class="medium">
											&nbsp;
										</td>
										<logic:present name="confList" scope="request">
											<logic:iterate name="confList" id="conference">
												<td  align="center" valign="middle"
													 class="medium" id="<bean:write name="conference" property="conId" />.B.">
													&nbsp;
												</td>
											</logic:iterate>
										</logic:present>
										<td align="center" valign="middle"
											 class="medium" >
											&nbsp;
										</td>
										<td  align="center" valign="middle"
											 class="medium" >
											&nbsp;
										</td>
										<td align="center" valign="middle"
											 class="medium" >
											&nbsp;
										</td>
									</tr>
							</logic:present>
						</tbody>
					</table>
				</td>
			</tr>
		</table>
	</form>

	<script language="JavaScript">
	<%
		List result1 = (List)request.getAttribute("result1");
		if(result1!=null){
			for(int i=0;i<result1.size();i++){
				HashMap rs1 = (HashMap)result1.get(i);
				String conId = rs1.get("conId").toString();
				String custId = rs1.get("custId").toString();
				String classdeptNo = rs1.get("classdeptNo").toString();
				String stuempNo = rs1.get("stuempNo").toString();
				String attendSign = rs1.get("attendSign").toString();
				
				%>
				if(document.getElementById("<%=classdeptNo%>.<%=custId%>")!=null){
					document.getElementById("<%=classdeptNo%>.<%=custId%>").innerHTML='<%=stuempNo%>';
				}
				<%				
				if("00".equals(attendSign)){
				%>
			  	if(document.getElementById("<%=conId%>.<%=classdeptNo%>.<%=custId%>")!=null){
					document.getElementById("<%=conId%>.<%=classdeptNo%>.<%=custId%>").innerHTML='×';
				}	
				
				<%
				}else{
				
				%>
				if(document.getElementById("<%=conId%>.<%=classdeptNo%>.<%=custId%>")!=null){
					document.getElementById("<%=conId%>.<%=classdeptNo%>.<%=custId%>").innerHTML='√';
				}
				
				<%		
				
				}
			}
		}
	
	 %>	
	 
	 	 
	 <%
		List result2 = (List)request.getAttribute("result2");
		if(result2!=null){
			for(int j=0;j<result2.size();j++){
				HashMap rs2 = (HashMap)result2.get(j);
				String custId = rs2.get("custId").toString();
				String allcount = rs2.get("allcount").toString();
				String shouldcount = rs2.get("shouldcount").toString();
				float rate = Float.parseFloat(shouldcount)*100/Float.parseFloat(allcount);
				%>
			  	if(document.getElementById("<%=custId%>.allcount")!=null){
					document.getElementById("<%=custId%>.allcount").innerHTML='<%=allcount%>';
				}
				
				if(document.getElementById("<%=custId%>.shouldcount")!=null){
					document.getElementById("<%=custId%>.shouldcount").innerHTML='<%=shouldcount%>';
				}	
				if(document.getElementById("<%=custId%>.rate")!=null){
					document.getElementById("<%=custId%>.rate").innerHTML='<%=rate%>'+'%';
				}		
				<%
			}
		}
	
	 %>
	 <%
		List result3 = (List)request.getAttribute("result3");
		if(result3!=null){
			for(int j=0;j<result3.size();j++){
				HashMap rs3 = (HashMap)result3.get(j);
				String classdeptNo = rs3.get("classdeptNo").toString();
				String conId = rs3.get("conId").toString();
				String allcount = rs3.get("allcount").toString();
				String shouldcount = rs3.get("shouldcount").toString();
				float rate = Integer.parseInt(shouldcount)*10000/Integer.parseInt(allcount)/100.00f;
				%>
			  	if(document.getElementById("<%=conId%>.count<%=classdeptNo%>.")!=null){
					document.getElementById("<%=conId%>.count<%=classdeptNo%>.").innerHTML='<%=rate%>'+'%';
				}
				<%
			}
		}
	
	 %>
	 
	 	 <%
		List result4 = (List)request.getAttribute("result4");
		if(result4!=null){
			for(int j=0;j<result4.size();j++){
				HashMap rs4 = (HashMap)result4.get(j);
				String conId = rs4.get("conId").toString();
				String allcount = rs4.get("allcount").toString();
				String shouldcount = rs4.get("shouldcount").toString();
				String latecount = rs4.get("latecount").toString();
				float rate = Integer.parseInt(shouldcount)*10000/Integer.parseInt(allcount)/100.00f;
				float rate1 = Integer.parseInt(latecount)*10000/Integer.parseInt(allcount)/100.00f;
				%>
			  	if(document.getElementById("<%=conId%>.A.")!=null){
					document.getElementById("<%=conId%>.A.").innerHTML='<%=rate%>'+'%';
				}
				
				if(document.getElementById("<%=conId%>.B.")!=null){
					document.getElementById("<%=conId%>.B.").innerHTML='<%=rate1%>'+'%';
				}
				<%
			}
		}
	
	 %>
	 

	 
	
	</script>

	<script language="JavaScript">
	
	Calendar.setup({
        inputField     :    "begindate",     // id of the input field
        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",
							getServletContext())%>,
    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",
							getServletContext())%>",
        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    
    Calendar.setup({
        inputField     :    "enddate",     // id of the input field
        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",
							getServletContext())%>,
    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",
							getServletContext())%>",
        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
</script>

</body>
