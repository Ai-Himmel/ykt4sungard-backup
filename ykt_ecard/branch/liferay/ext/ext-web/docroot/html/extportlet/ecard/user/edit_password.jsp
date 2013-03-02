<%@ include file="/html/extportlet/ecard/user/init.jsp"%>

<table width="100%" border="0" cellspacing="0" cellpadding="0">

	<tr>
		<td>
			&nbsp;
		</td>
		<td valign="top" align=center>
			<!-- content table -->
			<html:form action="/ext/ecarduseredit_password_result" method="POST"
				enctype="multipart/form-data"
				onsubmit="javascript:submitPortletForm(this); return false;">
				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td width="18%">
							&nbsp;
						</td>
						<td width="92%">
							<c:if test="<%=SessionErrors.contains(request,
							EcardConstants.EDIT_PASSWORD_SUCCEED)%>">
								<font  style="font-size: 11;">
									<bean:message key="ecard.error.editpasswordsucceed" /> </font>
							</c:if>
						</td>
					</tr>
				</table>
				<table width="100%" border="0" cellspacing="0" cellpadding="0">

					<tr>
						<td width="18%" valign="baseline">
							<bean:message key="ecard.oldpassword" />
							:
						</td>
						<td width="60%" valign="baseline">
							<html:password property="oldpassword" size="40" />
						</td>
						<td width="29%" align=left>
							<a ><html:errors
									property="oldpassword" /> <c:if
									test="<%=SessionErrors.contains(request,
							OldPwdErrorException.class.getName())%>">
									<bean:message key="ecard.error.oldpassworderror" />
								</c:if> </a>
						</td>
					</tr>
				</table>

				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>
				<table width="100%" border="0" cellspacing="0" cellpadding="0">

					<tr>
						<td width="18%" valign="baseline">
							<bean:message key="ecard.newpassword" />
							:
						</td>
						<td width="60%" valign="baseline">
							<html:password property="newpassword" size="40"/>
						</td>
						<td width="29%" align=left>
							<a ><html:errors
									property="newpassword" /> <c:if
									test="<%=SessionErrors.contains(request,
							UnpairedPwdException.class.getName())%>">
									<bean:message key="ecard.error.unpairedpassword" />
								</c:if> </a>
						</td>
					</tr>
				</table>
				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>

				<table width="100%" border="0" cellspacing="0" cellpadding="0">

					<tr>
						<td width="18%" valign="baseline">
							<bean:message key="ecard.confirmpassword" />
							:
						</td>
						<td width="60%" valign="baseline">
							<html:password property="confirmpassword" size="40"/>
						</td>
						<td width="29%" align=left>
							<a> <html:errors property="confirmpassword" /> </a>
						</td>
					</tr>
				</table>
				<table width="100%" height="1" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>
				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>
				<table width="99%" height="35" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td align="center">
							<html:submit property="save"><bean:message key="ecard.save" /></html:submit>
							<html:button property="reset"><bean:message key="ecard.reset" /></html:button>
						</td>
					</tr>
				</table>
			</html:form>
			<!-- content table -->
		</td>
		<td>
			&nbsp;
		</td>
	</tr>
</table>