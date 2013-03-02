<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp" %>
<%@ include file="/html/portlet/ecard/cardtransaction/permission_general_user.jsp" %>
<input type=hidden id=hiddenURL value='<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/ecardtransaction/querydetail_result" /></portlet:actionURL>'>
<%String beginDate = DateFormatUtil.getDateLaterNow();
String endDate = DateFormatUtil.getNowDate();
String stuempNo = (String) request.getSession().getAttribute(WebKeys.USER_ID);
String customerId = CustomerUtil.getCustomerByStuempNo(stuempNo).getCutId().toString();
List availableCards = CardUtil.getAvailableCards(customerId);
%>
<html:form action="/ecardtransaction/querydetail_result" 
		method="POST" onsubmit="javascript:setFormAction(this);submitForm(this);return false;">
<table cellpadding="8" border=0 cellspacing="0" width="100%">          
          <tr>
            <td class=gamma>
            <table cellpadding="0" cellspacing="0" class=text_brown>
            <tr>				
				<td width="35%" align=left>
				<bean:message key="ecard.beginDate" />:
				</td>
				<td width="50%" >
				<html:text styleId="beginDate" readonly="true" property="beginDate"  value="<%= beginDate%>" size="15" maxlength="10" onkeydown="monitorDateInput()" />	
				</td>
				<td width="15%" align=center>
				<img align="absmiddle" border="0" hspace="0" id="f_trigger_begindate" 
				style="cursor: pointer;" 
     			src="/html/themes/classic/images/calendar/calendar.gif" vspace="0" >
				</td>
			</tr>
			 <tr>
				<td width="35%" align=left>
				<bean:message key="ecard.endDate" />:
				</td>
				<td width="50%" >
				<html:text styleId="endDate" readonly="true" property="endDate" value="<%= endDate%>" size="15" maxlength="10" onkeydown="monitorDateInput()" />
				</td>
				<td width="15%" align=center>
				<img align="absmiddle" border="0" hspace="0" id="f_trigger_enddate" 
					style="cursor: pointer;" 
      				src="/html/themes/classic/images/calendar/calendar.gif" vspace="0" >			
				</td>
				<script language="JavaScript">
					
					Calendar.setup({
				        inputField     :    "beginDate",     // id of the input field
				        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
				        align          :    "Tr",           // alignment (defaults to "Bl")
				        singleClick    :    true
				    });
				    
				    Calendar.setup({
				        inputField     :    "endDate",     // id of the input field
				        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
				        align          :    "Tr",           // alignment (defaults to "Bl")
				        singleClick    :    true
				    });
				</script>
			</tr>
			 
			<tr>				
				<td width="35%" align=left>
				<bean:message key="ecardtransaction.querydetail.chooseaccount" />:
				</td>
				<td width="50%" >
				<html:select property="cardId">
            		<%for (int i = 0; i < availableCards.size(); i++) {
            			TPifCard card = (TPifCard) availableCards.get(i);%>
            		<html:option value="<%= card.getCardId().toString()%>">
            		<bean:message key="ecard.account" /><%= i + 1%>
            		</html:option>
            		<%}%>
            	</html:select> 
				</td>
				<td width="15%" align=center>
				&nbsp;
				</td>
			</tr>   
			
			          
			<tr>
				<td width="30%" align=left>
				&nbsp;
				</td>
				<td colspan=2 width=70% align=right>
					<div style="LEFT: 53px; VISIBILITY: visible; WIDTH: 274px; POSITION: absolute; TOP: 540px; HEIGHT: 216px">
						<html:submit styleClass="button_blank" value='<%= LanguageUtil.get(pageContext, "ecard.query") %>' />				
					</div>
				</td>
			</tr>
            </table>
             
              </td>

              	</tr>
          </table>
</html:form>
<script>
function setFormAction(form) {
	form.action = hiddenURL.value;	
}

</script>