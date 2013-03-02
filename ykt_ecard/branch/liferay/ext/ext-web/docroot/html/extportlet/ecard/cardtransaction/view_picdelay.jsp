<%@ include file="/html/extportlet/ecard/cardtransaction/init.jsp"%>
<%
	Long realUserId = (Long) request.getSession().getAttribute(
			WebKeys.USER_ID);
	User myuser = UserLocalServiceUtil.getUserById(realUserId);
	String stuempNo = myuser.getScreenName();
	EcardPicDelay apply = PicDelayServiceUtil.getDelayById(stuempNo);
	SimpleDateFormat format = new SimpleDateFormat("yyyyMMdd");
%>
<table width="100%" border="0" cellspacing="0" cellpadding="0">

	<c:if test="<%=PermissionUtil.hasCardTransactionAdmin(request)%>">
		<tr>
			<td width="166" class="text_brown">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ext/ecardtransactionadmin_picdelay" /></portlet:renderURL>" >
			<bean:message key="ecardtransaction.tab.processpicdelay" />
			</a>
			</td>
		</tr>
	</c:if>

</table>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td width="9" height="7">

		</td>
		<td height="7"></td>
		<td width="6" height="7">

		</td>
	</tr>
	<tr>
		<td>
			&nbsp;
		</td>
		<td valign="top" align=left>
			<!-- content table -->
			<%
				if (apply == null) {
			%>
			<form name="postponeForm"
				action="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/ext/ecardtransactionadd_picdelay" /></portlet:renderURL>"
				method=post onSubmit="submitPortletForm(this);return false;">

				<table width="100%" border="0" cellspacing="0" cellpadding="0">

					<tr>
						<td align=left valign="baseline" class="text_blue_12">
							<bean:message key="ecardtransaction.picdelay.noapply" />
						</td>

					</tr>
				</table>

				<table width="100%" height="1" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td bgcolor="#e1e1e2"></td>
					</tr>
				</table>
				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>
				<table width="30%" height="35" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td align="right">
							<input type=submit
								value='<bean:message key="ecardtransaction.button.apply" />'
								class="button_blank">

						</td>
					</tr>
				</table>
			</form>
			<%
				} else {
			%>

			<table class="tdclass" width="100%" border="0" cellspacing="0"
				cellpadding="0">

				<tr>
					<td width="30%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="ecardtransaction.picdelay.curStuempNo" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td width="65%" align=left valign="baseline" class="text_blue_12">
						<%=apply.getCurStuempNo()%></td>
				</tr>

				<tr>
					<td width="30%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="ecardtransaction.picdelay.oldStuempNo" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td width="65%" align=left valign="baseline" class="text_blue_12">
						<%=apply.getOldStuempNo()%></td>
				</tr>

				<tr>
					<td width="30%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="ecardtransaction.cardpostpone.status" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td width="65%" align=left valign="baseline" class="text_blue_12">
						<%=LanguageUtil.get(pageContext,
								"ecardtransaction.processstatus."
										+ apply.getStatus())%></td>
				</tr>



				<table width="100%" height="1" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td bgcolor="#e1e1e2"></td>
					</tr>
				</table>
				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>
				<table width="40%" height="35" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td align="right">
							<c:if
								test="<%=!apply.getStatus().equals(
								EcardConstants.POSTPONE_STATUS_ACCEPTED)%>">
								<form name=cancelForm
									action="<portlet:actionURL><portlet:param name="struts_action" value="/ext/ecardtransactioncancelPicDelay" /></portlet:actionURL>"
									method=post
									onSubmit="javascript:submitForm(this);return false;">
									<input type=submit
										value='<bean:message key="ecardtransaction.button.cancelapply" />'
										class="button_blank">
								</form>
							</c:if>
						</td>
					</tr>
				</table>
				<%
					}
				%>
				<!-- content table -->
				<tr>
					<td width="9" height="7"></td>
					<td height="7"></td>
					<td width="6" height="7">

					</td>
				</tr>
			</table>