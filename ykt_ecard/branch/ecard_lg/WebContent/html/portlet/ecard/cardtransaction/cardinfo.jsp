<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp" %>
<%@ include file="/html/portlet/ecard/cardtransaction/permission_general_user.jsp" %>
<%
HashMap result = null;;
String stuempNo = (String) request.getSession().getAttribute(WebKeys.USER_ID);
String customerId = CustomerUtil.getCustomerByStuempNo(stuempNo).getCutId().toString();
List availableCards = CardUtil.getAvailableCards(customerId);
%>

<table cellpadding="8" cellspacing="0" width="100%">          
          <tr>
            <td>
		<%for (int i = 0; i < availableCards.size(); i++) {
			TPifCard card = (TPifCard) availableCards.get(i);
			result = CustomerUtil.getRelatedCustomerInfo(customerId, card.getCardId());
			String state = (String) result.get("cardState");
			%>			
		<c:if test="<%= i == 0%>">
			<div id=cardcontent<%= i+1%> style="LEFT: 53px; visibility: visible; WIDTH: 274px; POSITION: absolute; TOP: 130px; HEIGHT: 216px">
		</c:if>
		<c:if test="<%= i != 0%>">
			<div id=cardcontent<%= i+1%> style="LEFT: 53px; VISIBILITY: hidden; WIDTH: 274px; POSITION: absolute; TOP: 130px; HEIGHT: 216px">
		</c:if>
		<table cellpadding="0" cellspacing="0" width="63%">
              <tr>
                <td align=left class=text_brown><bean:message key="cardinfo.content.name" />:</td>
                <td><%= result.get("customerName")==null?"":result.get("customerName")%></td>
              </tr>
              <tr>
                <td  align=left class=text_brown><bean:message key="cardinfo.content.personId" />:</td>
                <td  height="20"><%= result.get("customerId")==null?"":result.get("customerId")%></td>
              </tr>
              <tr>
                <td height="20" align="left" class=text_brown><bean:message key="cardinfo.content.department" />:</td>
                <td height="20" width=60%><%= result.get("customerDep")==null?"":result.get("customerDep")%></td>
              </tr>
              <tr>
                <td height="20" align="left" class=text_brown><bean:message key="cardinfo.content.no" />:</td>
                <td height="20" width=60%><%= result.get("accountNo")==null?"":result.get("accountNo")%></td>
              </tr>
              <tr>
                <td height="20" align="left" class=text_brown><bean:message key="cardinfo.content.status" />:</td>
                <td height="20" width=60%><%= result.get("cardStatus")==null?"":result.get("cardStatus")%></td>
              </tr>
              <tr>
                <td height="20" align="left" class=text_brown><bean:message key="cardinfo.content.type" />:</td>
                <td height="20" width=60%><%= result.get("cardType")==null?"":result.get("cardType")%></td>
              </tr>
              <tr>
                <td height="20" align="left" class=text_brown><bean:message key="cardinfo.content.cardbalance" />:</td>
                <td height="20" width=60%><%= result.get("cardbalance")==null?"":result.get("cardbalance")%></td>
              </tr>
              <!--
              <tr>
                <td height="20" align="left" class=text_brown><bean:message key="cardinfo.content.balance" />:</td>
                <td height="20" width=60%><%= result.get("balance")==null?"":result.get("balance")%></td>
              </tr>
              -->
              <tr>
                <td height="20" align="left" class=text_brown><bean:message key="cardinfo.content.opendate" />:</td>
                <td height="20" width=60%><%= result.get("beginTime")==null?"":result.get("beginTime")%></td>
              </tr>
              <tr>
                <td height="20" align="left" class=text_brown><bean:message key="cardinfo.content.expiredate" />:</td>
                <td height="20" width=60%><%= result.get("endTime")==null?"":result.get("endTime")%></td>
              </tr>
            </table>
            
            <c:if test="<%= state.charAt(1) != '1'%>" >
            	<table cellpadding="0" cellspacing="0" width="100%">
              <tr>
                <td height="20" align="left" >&nbsp;</td>
               
                <td align=right  height="20" width=60%>
                <form name=processLostForm<%= i%> 
                action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/ecardtransaction/processCardLost" /></portlet:actionURL>" 
						method=post onSubmit="submitForm(this);return false;">
					<input type=hidden name=cardId value="<%= card.getCardId().toString()%>">
					<input type=button value='<bean:message key="ecardtransaction.button.processlost" />' class="button_blank" 
						onclick="if (confirm('<%= UnicodeLanguageUtil.get(pageContext, "ecard.cardlost.confirm") %>')) {  submitForm(document.processLostForm<%= i%>); }">
				</form>
                </td>
              </tr>
				</table>
			</c:if>
          </div>
          <%}%>
          <div id=portraitDiv style=" LEFT: 231px; VISIBILITY: visible; WIDTH: 130px; POSITION: absolute; TOP: 130px; HEIGHT: 216px">
          <img src="/ecardimage?stempNo=<%=stuempNo%>" height="120" width="90"><br><br>
          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          <a class=blue_link_line href="/ecardimage?cmd=download"><bean:message key="ecardtransaction.downloadphoto" /></a>
          </div>
              </td>

              	</tr>
          </table>