<%@ include file="/html/commons/init.jsp"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ page
	import="com.kingstargroup.conference.hibernate.form.TConference"%>
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
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
	<%
		String custno = ParamUtil.getString(request, "custno");
		String custname = ParamUtil.getString(request, "custname");
		String duty = ParamUtil.getString(request, "duty");
		String username = GetterUtil.get((String) request.getSession()
				.getAttribute("username"), "");
	%>
	<form name="AllotInformForm"
			action="<%=ContextUtil.getCtxPath(request)%>/attendeeinform/list.do"
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
				<span class="mediumwhite"> <strong>&nbsp;&nbsp;&nbsp;<span
						class="mediumwhite"><strong></strong> </span> <bean:message
							key="attendee.statusquery" /> </strong> </span>
			</td>
		</tr>
		<tr>
			<td align="left" valign="top">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				<table width="100%" border="1" cellspacing="0" cellpadding="2"
					bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
					<tr>
						<td width="15%" height="25" align="right" valign="middle"
							bgcolor="#A9CFE2" class="medium">
							<bean:message key="conference.name" />
						</td>
						<td align="left" valign="middle" bgcolor="#E6ECF2">
							<select name=confid style="width:200" class="select01">
								<%
									List list = GetDictionary.getConfList(username);
									if (null != list) {
										Iterator iter = list.iterator();
										String confid = "";
										if (null != request.getAttribute("confid")) {
											confid = request.getAttribute("confid").toString();
										}
										while (iter.hasNext()) {
											TConference conf = (TConference) iter.next();
											if (String.valueOf(conf.getConId()).equals(confid)) {
								%>
								<option value="<%=conf.getConId()%>" selected="selected">
									<%=conf.getConName()%>
								</option>
								<%
								} else {
								%>
								<option value="<%=conf.getConId()%>">
									<%=conf.getConName()%>
								</option>
								<%
										}
										}
									}
								%>
							</select>
						</td>
					</tr>
					<tr>
						<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
							class="medium">
							<bean:message key="attendee.custno" />
						</td>
						<td align="left" valign="middle" bgcolor="#E6ECF2">
							<input name=custno style="width:200" style="width:200"
								class="input_box" value="<%=custno%>" maxlength=50>
						</td>
					</tr>
					<tr>
						<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
							class="medium">
							<bean:message key="attendee.custname" />
						</td>
						<td align="left" valign="middle" bgcolor="#E6ECF2">
							<input name=custname style="width:200" value="<%=custname%>"
								class="input_box" maxlength=50>
						</td>
					</tr>
					<tr>
						<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
							class="medium">
							<bean:message key="attendee.dept" />
						</td>
						<td align="left" valign="middle" bgcolor="#E6ECF2">
							<select name=dept style="width:200" class="select01">
								<OPTION>
									-
								</OPTION>
								<%
									Iterator iter2 = GetDictionary.getDeptList().iterator();
									String deptcode = "";
									if (null != request.getAttribute("dept")) {
										deptcode = request.getAttribute("dept").toString();
									}
									while (iter2.hasNext()) {
										HashMap dept = (HashMap) iter2.next();
										if (dept.get("deptCode").toString().equals(deptcode)) {
								%>
								<option value="<%=dept.get("deptCode")%>" selected="selected">
									<%=dept.get("deptName")%>
								</option>
								<%
								} else {
								%>
								<option value="<%=dept.get("deptCode")%>">
									<%=dept.get("deptName")%>
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
							<bean:message key="attendee.duty" />
						</td>
						<td align="left" valign="middle" bgcolor="#E6ECF2">
							<input name=duty style="width:200" value="<%=duty%>"
								class="input_box" maxlength=50>
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
		<tr>
			<td height="50" align="right" valign="middle" class="tdborder02">
				<input name="Submit3" type="submit" class="button_nor"
					value="<bean:message key="button.query"/>">
				&nbsp;&nbsp;&nbsp;
				<input name="Submit2" type="reset" class="button_nor"
					value="<bean:message key="button.reset"/>" onClick="reset">
			</td>
		</tr>		
	</table>
	</form>
</body>
