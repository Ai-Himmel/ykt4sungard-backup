
<%@page import="com.kingstargroup.ecard.portlet.losecard.service.LoseCardServiceUtil"%><%@ include file="/html/extportlet/ecard/cardtransaction/init.jsp"%>

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
	List availableCards = CardServiceUtil.getAvailableCards(customerId);
%>

<table cellpadding="8" cellspacing="0" width="95%" align="center">
	<tr>
		<td>
			<%
				for (int i = 0; i < availableCards.size(); i++) {
					TCard card = (TCard) availableCards.get(i);
					result = CustomerLocalServiceUtil.getRelatedCustomerInfo(
							customerId, card.getCardno());
					String state = (String) result.get("cardState");
			%>

			<table cellpadding="0" cellspacing="0" width="80%">
				<tr>
					<td align=right class=text_brown width="40%">
						<bean:message key="cardinfo.content.name" />
						:
					</td>
					<td><%=result.get("customerName") == null ? "" : result
						.get("customerName")%></td>
				</tr>
				<tr>
					<td align=right class=text_brown>
						<bean:message key="cardinfo.content.personId" />
						:
					</td>
					<td height="20"><%=result.get("customerId") == null ? "" : result
						.get("customerId")%></td>
				</tr>
				<tr>
					<td height="20" align="right" class=text_brown>
						<bean:message key="cardinfo.content.department" />
						:
					</td>
					<td height="20"><%=result.get("customerDep") == null ? "" : result
						.get("customerDep")%></td>
				</tr>
				<tr>
					<td height="20" align="right" class=text_brown>
						<bean:message key="cardinfo.content.status" />
						:
					</td>
					<td height="20"><%=result.get("cardStatus") == null ? "" : result
						.get("cardStatus")%></td>
				</tr>
				<tr>
					<td height="20" align="right" class=text_brown>
						<bean:message key="cardinfo.content.type" />
						:
					</td>
					<td height="20"><%=result.get("cardType") == null ? "" : result
						.get("cardType")%></td>
				</tr>
				<tr>
					<td height="20" align="right" class=text_brown>
						<bean:message key="cardinfo.content.cardbalance" />
						:
					</td>
					<td height="20"><%=result.get("balance") == null ? "" : result
						.get("balance")%></td>
				</tr>
				<tr>
					<td height="20" align="right" class=text_brown>
						<bean:message key="cardinfo.content.opendate" />
						:
					</td>
					<td height="20"><%=result.get("beginTime") == null ? "" : result
						.get("beginTime")%></td>
				</tr>
				<tr>
					<td height="20" align="right" class=text_brown>
						<bean:message key="cardinfo.content.expiredate" />
						:
					</td>
					<td height="20"><%=result.get("endTime") == null ? "" : result
						.get("endTime")%></td>
				</tr>
				<% 
					Map getGetCardInfo = LoseCardServiceUtil.getGetCardInfo(card.getCardno().toString());
					if (getGetCardInfo!=null){
				%>
				<tr>
					<td height="20" align="right" class="text_or_12">
						<bean:message key="losecard.cardalreadyreg" />
					</td>
				</tr>
				
				<tr>
					<td height="20" align="right" class=text_brown>
						<bean:message key="losecard.addr" />:
					</td>
					<td height="20"><%=getGetCardInfo.get("getcardplace")%></td>
				</tr>
				
				<tr>
					<td height="20" align="right" class=text_brown>
						<bean:message key="losecard.tel" />:
					</td>
					<td height="20"><%=getGetCardInfo.get("tel")%></td>
				</tr>
				<%} %>
			</table>
			<c:if test="<%=state.charAt(1) != '1'%>">
				<table cellpadding="0" cellspacing="0" width="63%">
					<tr>
						<td height="20" align="left">
							&nbsp;
						</td>
						<td align=right height="20">
							<form name="processLostForm<%=i%>"
								action="<portlet:actionURL windowState="<%=WindowState.MAXIMIZED.toString()%>"><portlet:param name="struts_action" value="/ext/ecardtransactionprocessCardLost" /></portlet:actionURL>"
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
					</tr>
				</table>
			</c:if>
			<%
				}
			%>

		</td>




		<td align="left">
			<img src="/ecardimage?stempNo=<%=stuempNo%>" height="120" width="90">
			<br>
			<br>
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			<a class=blue_link_line href="/ecardimage?cmd=download"><bean:message
					key="ecardtransaction.downloadphoto" /> </a>
		</td>

	</tr>
</table>

<%}%>