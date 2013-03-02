
<%@page import="com.kingstargroup.ecard.hibernate.customer.TCustomer"%><%@ include
	file="/html/extportlet/ecard/cardtransaction/init.jsp"%>

<%
	HashMap result = null;
	Long realUserId = (Long) request.getSession().getAttribute(
			WebKeys.USER_ID);
	User myuser = UserLocalServiceUtil.getUserById(realUserId);
	String stuempNo = myuser.getScreenName();
	TCustomer tcustomer = CustomerLocalServiceUtil
			.getCustomerByStuempno(stuempNo);
	if (tcustomer == null) {
%>
<%@ include
	file="/html/extportlet/ecard/cardtransaction/permission_general_user.jsp"%>

<%
	} else {
		String customerId = tcustomer.getCustid().toString();
		List availableCards = CardServiceUtil
				.getAvailableCards(customerId);
%>
<table width="95%" border="0" cellspacing="0" cellpadding="0" align="center">
	<tr>

		<td valign="top" width="60%" align="left">

			<!-- content table -->
			<table width="100%" height="5" border="0" cellpadding="0"
				cellspacing="0" >
				<tr>
					<td width="5%">
					</td>
					<td width="95%">
						<c:if
							test="<%=SessionErrors.contains(request,
								ProcessCardLossException.class.getName())%>">

							<a> <bean:message key="ecard.errors.processcardloss" /> </a>

						</c:if>
						<c:if
							test="<%=SessionErrors.contains(request,
								CardAlreadyOffException.class.getName())%>">

							<a> <bean:message key="ecard.errors.alreadywriteoff" /> </a>
						</c:if>
						<c:if
							test="<%=SessionErrors.contains(request,
								CardAlreadyLostException.class.getName())%>">

							<a> <bean:message key="ecard.errors.alreadyloss" /> </a>

						</c:if>
						<c:if
							test="<%=SessionErrors.contains(request,
								DBSystemException.class.getName())%>">

							<a> <bean:message key="ecard.errors.busydbsystem" /> </a>

						</c:if>
					</td>
				</tr>
			</table>

			<%
				for (int i = 0; i < availableCards.size(); i++) {
						TCard card = (TCard) availableCards.get(i);
						result = CustomerLocalServiceUtil.getRelatedCustomerInfo(
								customerId, card.getCardno());
						String state = (String) result.get("cardState");
						
			%>
			
			<table class="tdclass" width="100%" border="0" cellspacing="0"
				cellpadding="0">
				<tr>
					<td width="40%" valign="baseline" class="text_blue_12">
						<img src="/html/extthemes/classic/images/ecard/jiantou.jpg"
							width="8" height="8">
						<bean:message key="ecard.account" /><%=i + 1%>
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td  valign="baseline" class="text_blue_12">
					</td>

				</tr>
				<tr>
					<td width="40%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="cardinfo.content.name" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td  valign="baseline" class="text_blue_12">
						<%=result.get("customerName")%>
					</td>

				</tr>
				<tr>
					<td width="40%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="cardinfo.content.personId" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td  valign="baseline" class="text_blue_12">
						<%=result.get("customerId")%>
					</td>

				</tr>

				<tr>
					<td width="40%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="cardinfo.content.department" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td  valign="baseline" class="text_blue_12">
						<%=result.get("customerDep")%>
					</td>

				</tr>

				<tr>
					<td width="40%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="cardinfo.content.status" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td  valign="baseline" class="text_blue_12">
						<%=result.get("cardStatus")%>
					</td>

				</tr>

				<tr>
					<td width="40%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="cardinfo.content.type" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td  valign="baseline" class="text_blue_12">
						<%=result.get("cardType")%>
					</td>

				</tr>
				<tr>
					<td width="40%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="cardinfo.content.cardbalance" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td  valign="baseline" class="text_blue_12">
						<%=result.get("cardbalance")%>
					</td>

				</tr>

				<tr>
					<td width="40%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="cardinfo.content.balance" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td  valign="baseline" class="text_blue_12">
						<%=result.get("balance")%>
					</td>

				</tr>
				<tr>
					<td width="40%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="cardinfo.content.opendate" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td  valign="baseline" class="text_blue_12">
						<%=result.get("beginTime")%>
					</td>

				</tr>

				<tr>
					<td width="40%" align="left" valign="baseline" class="text_or_12">
						<bean:message key="cardinfo.content.expiredate" />
						:
					</td>
					<td valign=baseline>
						&nbsp;
					</td>
					<td  valign="baseline" class="text_blue_12">
						<%=result.get("endTime")%>
					</td>

				</tr>

			</table>
			<c:if test="<%=state.charAt(1) != '1'%>">
				<table class="tdclass" width="63%" border="0" cellspacing="0"
					cellpadding="0">
					<tr>
						<td width="25%" valign="baseline" class="text_or_12">
						</td>
						<td width="75%" valign="baseline" align=left class="text_blue_12">
							<form name="processLostForm<%=i%>"
								action="<portlet:renderURL><portlet:param name="struts_action" value="/ext/ecardtransactionprocessCardLost" /></portlet:renderURL>"
								method=post onSubmit="submitForm(this);return false;">
								<input type=hidden name=cardId
									value="<%=card.getCardno().toString()%>">
								<input type=button
									value='<bean:message key="ecardtransaction.button.processlost" />'
									class="button_blank"
									onclick="if (confirm('<%=UnicodeLanguageUtil.get(pageContext,
									"ecard.cardlost.confirm")%>')) {  submitForm(document.processLostForm<%=i%>); }">
							</form>
						</td>
						<td width="15%" align="left"></td>
					</tr>
				</table>
			</c:if>
			<c:if test="<%=i != (availableCards.size() - 1)%>">
				<table width="70%" height="1" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td bgcolor="#e1e1e2"></td>
					</tr>
				</table>
				<table width="70%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>
			</c:if>
			<%
				}
			%>
		
		<td width="40%" align="left">
            <br>
			<img src="/ecardimage?stempNo=<%=stuempNo%>" height="120" width="90">
			<br>		
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			<a class=blue_link_line href="/ecardimage?cmd=download"><bean:message
					key="ecardtransaction.downloadphoto" /> </a>
		</td>

	</tr>
	<tr>
		<td width="9" height="7">
			&nbsp;
		</td>
		<td height="7"></td>
		<td width="6" height="7">
			&nbsp;
		</td>
	</tr>
</table>

<%
	}
%>