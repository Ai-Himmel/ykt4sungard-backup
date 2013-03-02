<jsp:directive.page
	import="com.kingstargroup.conference.hibernate.form.TConference" />
<%@ include file="/html/commons/init.jsp"%>
<%@ include file="/html/commons/top_calendar.jsp"%>
<head>
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css"
		rel="stylesheet" type="text/css">
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css"
		rel="stylesheet" type="text/css">
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css"
		rel="stylesheet" type="text/css">
</head>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
	<html:form action="backdbsynchronize.do" method="post">
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
					<span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<span
							class="mediumwhite"><strong></strong> </span> <bean:message
								key="datasynchronize.backsynchronize" /> </strong> </span>
				</td>
			</tr>
			<tr>
				<td align="left" valign="top" class="medium">
					&nbsp;&nbsp;&nbsp;&nbsp;
					<a class="portlet-msg-error"><html:errors property="errorinfo" /> </a>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width="100%" border="1" cellspacing="0" cellpadding="2"
						bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
						<tr>
							<td width="15%" height="25" align="right" valign="middle"
								bgcolor="#A9CFE2" class="medium">
								<bean:message key="datasynchronize.conferenceurl" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<html:text property="url" styleClass="input_box1"
									maxlength="80" readonly="true"/><html:hidden property="dbconfigure" />
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a class="portlet-msg-error"><html:errors
										property="url" /> </a>
							</td>
						</tr>
						
						<tr>
							<td width="15%" height="25" align="right" valign="middle"
								bgcolor="#A9CFE2" class="medium">
								<bean:message key="datasynchronize.username" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<html:text property="username" styleClass="input_box"
									maxlength="30" readonly="true"/>
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a class="portlet-msg-error"><html:errors
										property="username" /> </a>
							</td>
						</tr>
						<tr>
							<td width="15%" height="25" align="right" valign="middle"
								bgcolor="#A9CFE2" class="medium">
								<bean:message key="datasynchronize.password" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<html:password property="password" styleClass="input_box"
									maxlength="20" readonly="true"/>
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a class="portlet-msg-error"><html:errors
										property="password" /> </a>
							</td>
						</tr>
						<tr>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="datasynchronize.conference" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<html:select property="conference" multiple="true" size="4">
									<%
										List confList = (List) request.getAttribute("confList");
										if (confList != null) {
											Iterator iter = confList.iterator();
											while (iter.hasNext()) {
												TConference conf = (TConference) iter.next();
									%>
									<html:option value="<%=conf.getConId().toString()%>">
										<%=conf.getConName()%>
									</html:option>
									<%
										}
										}
									%>
								</html:select>
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a class="portlet-msg-error"><html:errors
										property="meet" /> </a>
							</td>
						</tr>

					</table>
				</td>
			</tr>
			<tr>
				<td height="50" align="right" valign="middle" class="tdborder02">
					<html:submit>
						<bean:message key="datasynchronize.ok" />
					</html:submit>
				<html:button property="cancel" onclick="javascript:cancelPage();"><bean:message key="datasynchronize.cancel" /></html:button>
				</td>
			</tr>

		</table>
	</html:form>
	


</body>

	<script language="JavaScript">
	function cancelPage(){
		self.location = '<%=ContextUtil.getCtxPath(request)%>/backdbconfigure.do';
	}
	
	</script>
