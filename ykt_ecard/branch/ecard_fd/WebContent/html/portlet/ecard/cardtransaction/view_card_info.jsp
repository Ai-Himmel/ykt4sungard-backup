<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp" %>
<%@ include file="/html/portlet/ecard/cardtransaction/permission_general_user.jsp" %>
<%
HashMap result = null;
String stuempNo = (String) request.getSession().getAttribute(WebKeys.USER_ID);
String customerId = CustomerUtil.getCustomerByStuempNo(stuempNo).getCutId().toString();
List availableCards = CardUtil.getAvailableCards(customerId);
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardtransaction.tab.cardlost" /></td>
          <td width="11%" valign="bottom">&nbsp;</td>
          <td width="15%" align="right" valign="middle" nowrap class="text_brown">&nbsp;</td>
        </tr>
      </table></td>
    </tr>
  </table>
    <table width="100"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="5">
       
        </td>
      </tr>
    </table>
    <table width="719"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td width="9" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_1.jpg" width="9" height="7"></td>
        <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_top.jpg"></td>
        <td width="6" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_1.jpg" width="6" height="7"></td>
      </tr>
      <tr>
        <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_2.jpg">&nbsp;</td>
        <td valign="top" bgcolor="#FFFFFF">
        
        <!-- content table -->
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
          	<td width="5%">
              </td>
            <td width="95%">
	            <c:if test="<%= SessionErrors.contains(request, ProcessCardLossException.class.getName()) %>">
							
							<a class="portlet-msg-error">
							<bean:message key="ecard.errors.processcardloss" />
							</a>
	
				</c:if>
				<c:if test="<%= SessionErrors.contains(request, CardAlreadyOffException.class.getName()) %>">
			
							<a class="portlet-msg-error">
							<bean:message key="ecard.errors.alreadywriteoff" />
							</a>
				</c:if>
				<c:if test="<%= SessionErrors.contains(request, CardAlreadyLostException.class.getName()) %>">
				
							<a class="portlet-msg-error">
							<bean:message key="ecard.errors.alreadyloss" />
							</a>
	
				</c:if>
				<c:if test="<%= SessionErrors.contains(request, DBSystemException.class.getName()) %>">
				
							<a class="portlet-msg-error">
							<bean:message key="ecard.errors.busydbsystem" />
							</a>

				</c:if>
            </td>
          </tr>
        </table>
		
		<%for (int i = 0; i < availableCards.size(); i++) {
			TPifCard card = (TPifCard) availableCards.get(i);
			result = CustomerUtil.getRelatedCustomerInfo(customerId, card.getCardId());
			String state = (String) result.get("cardState");
			%>
		
		<table class="tdclass"  width="100%"  border="0" cellspacing="0" cellpadding="0">
        	<tr>         
            <td width="10%" valign="baseline" class="text_blue_12">
            <img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/jiantou.jpg" width="8" height="8">
            <bean:message key="ecard.account" /><%= i+1%>
              </td><td valign=baseline>&nbsp;</td>
            <td width="88%" valign="baseline" class="text_blue_12">
            </td>
            
          </tr>
          <tr>            
            <td width="10%" align=right valign="baseline" class="text_or_12"><bean:message key="cardinfo.content.name" />: 
              </td><td valign=baseline>&nbsp;</td>
            <td width="88%" valign="baseline" class="text_blue_12">
            	<%= result.get("customerName")%>
            </td>
            
          </tr>
		 <tr>            
            <td width="10%" align=right valign="baseline" class="text_or_12"><bean:message key="cardinfo.content.personId" />: 
              </td><td valign=baseline>&nbsp;</td>
            <td width="88%" valign="baseline" class="text_blue_12">
            	<%= result.get("customerId")%>
            </td>
            
          </tr>
          
          <tr>            
            <td width="10%" align=right valign="baseline" class="text_or_12"><bean:message key="cardinfo.content.department" />: 
              </td><td valign=baseline>&nbsp;</td>
            <td width="88%" valign="baseline" class="text_blue_12">
            	<%= result.get("customerDep")%>
            </td>
            
          </tr>
          
          <tr>            
            <td width="10%" align=right valign="baseline" class="text_or_12"><bean:message key="cardinfo.content.no" />: 
              </td><td valign=baseline>&nbsp;</td>
            <td width="88%" valign="baseline" class="text_blue_12">
            	<%= result.get("accountNo")%>
            </td>
            
          </tr>
          
          <tr>            
            <td width="10%" align=right valign="baseline" class="text_or_12"><bean:message key="cardinfo.content.status" />: 
              </td><td valign=baseline>&nbsp;</td>
            <td width="88%" valign="baseline" class="text_blue_12">
            	<%= result.get("cardStatus")%>
            </td>
            
          </tr>
          
          <tr>            
            <td width="10%" align=right valign="baseline" class="text_or_12"><bean:message key="cardinfo.content.type" />: 
              </td><td valign=baseline>&nbsp;</td>
            <td width="88%" valign="baseline" class="text_blue_12">
            	<%= result.get("cardType")%>
            </td>
            
          </tr>
           <tr>            
            <td width="10%" align=right valign="baseline" class="text_or_12"><bean:message key="cardinfo.content.cardbalance" />: 
              </td><td valign=baseline>&nbsp;</td>
            <td width="88%" valign="baseline" class="text_blue_12">
            	<%= result.get("cardbalance")%>
            </td>
            
          </tr>
          
          <tr>            
            <td width="10%" align=right valign="baseline" class="text_or_12"><bean:message key="cardinfo.content.balance" />: 
              </td><td valign=baseline>&nbsp;</td>
            <td width="88%" valign="baseline" class="text_blue_12">
            	<%= result.get("balance")%>
            </td>
            
          </tr>
          <tr>            
            <td width="10%" align=right valign="baseline" class="text_or_12"><bean:message key="cardinfo.content.opendate" />: 
              </td><td valign=baseline>&nbsp;</td>
            <td width="88%" valign="baseline" class="text_blue_12">
            	<%= result.get("beginTime")%>
            </td>
            
          </tr>
          
          <tr>            
            <td width="10%" align=right valign="baseline" class="text_or_12"><bean:message key="cardinfo.content.expiredate" />: 
              </td><td valign=baseline>&nbsp;</td>
            <td width="88%" valign="baseline" class="text_blue_12">
            	<%= result.get("endTime")%>
            </td>
            
          </tr>                     
                             
            </table>
            <c:if test="<%= state.charAt(1) != '1'%>" >
              <table class="tdclass"  width="100%"  border="0" cellspacing="0" cellpadding="0">
              <tr>
              	<td width="25%" valign="baseline" class="text_or_12"> 
	              </td>
	            <td width="75%" valign="baseline" align=left class="text_blue_12">
	            	<form name=processLostForm<%= i%> action="<portlet:renderURL><portlet:param name="struts_action" value="/ecardtransaction/processCardLost" /></portlet:renderURL>" 
						method=post onSubmit="submitForm(this);return false;">
					<input type=hidden name=cardId value="<%= card.getCardId().toString()%>">
					<input type=button value='<bean:message key="ecardtransaction.button.processlost" />' class="button_blank" 
						onclick="if (confirm('<%= UnicodeLanguageUtil.get(pageContext, "ecard.cardlost.confirm") %>')) {  submitForm(document.processLostForm<%= i%>); }">
				</form>
	            </td>
	            <td width="15%" align=left></td>                
              </tr>
				</table>
			</c:if>
            <c:if test="<%= i != (availableCards.size() -1)%>">
            <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
	            <tr>
	              <td bgcolor="#e1e1e2"></td>
	            </tr>
	          </table>
	          <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
	            <tr>
	              <td></td>
	            </tr>
	          </table>
	          </c:if>
          <%}%>
              <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_2.jpg">&nbsp;</td>
      </tr>
      <tr>
        <td width="9" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_3.jpg" width="9" height="7"></td>
        <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_foot.jpg"></td>
        <td width="6" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_3.jpg" width="6" height="7"></td>
      </tr>
    </table>