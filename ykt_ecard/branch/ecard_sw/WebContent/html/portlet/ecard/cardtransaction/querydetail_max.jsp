<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp" %>
<%@ include file="/html/portlet/ecard/cardtransaction/permission_general_user.jsp" %>
<%String beginDate = DateFormatUtil.getDateLaterNow();
String endDate = DateFormatUtil.getNowDate();
Object obj = request.getAttribute("TradeDetailQueryForm");
if (obj != null) {
	beginDate = (String) ((DynaValidatorForm) obj).get("beginDate");
	endDate = (String) ((DynaValidatorForm) obj).get("endDate");	
}
String stuempNo = (String) request.getSession().getAttribute(WebKeys.USER_ID);
String customerId = CustomerUtil.getCustomerByStuempNo(stuempNo).getCutId().toString();
List availableCards = CardUtil.getAvailableCards(customerId);
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardtransaction.tab.querydetail" /></td>
          <td width="11%" valign="bottom">&nbsp;</td>
          <td width="15%" align="right" valign="middle" nowrap class="text_brown">&nbsp;</td>
        </tr>
      </table></td>
    </tr>
  </table>
    <table width="100"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="5"></td>
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
       <html:form action="/ecardtransaction/querydetail_result" 
				method="POST" onsubmit="javascript:submitPortletForm(this);return false;">
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td></td>
          </tr>
        </table>
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
           <tr>
            <td width="3%"></td>
            <td width="12%" valign="baseline" class="text_or_12"><bean:message key="ecard.beginDate" />: 
              </td>
            <td width="45%" valign="baseline" class="text_or_12">            
				<html:text styleId="beginDate" property="beginDate" readonly="true" size="30" value="<%= beginDate%>" maxlength="10" onkeydown="monitorDateInput()" />	
				&nbsp;
				<img align="absmiddle" style="cursor: pointer;" border="0" hspace="0" id="f_trigger_begindate" src="<%= themeDisplay.getPathThemeRoot() %>/images/calendar/calendar.gif" vspace="0" onClick="zgat_jsOnClick('zgat_jsCalendarObj');">
            </td>
            <td width="40%" align=left><font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="beginDate" />
							</font></td>
          </tr>
          <tr>
          	<td width="3%"></td>
            <td width="12%" valign="baseline" class="text_or_12"><bean:message key="ecard.endDate" />: 
              </td>
            <td width="45%" valign="baseline" class="text_or_12">
            	<html:text styleId="endDate" property="endDate" size="30" readonly="true" value="<%= endDate%>" maxlength="10" onkeydown="monitorDateInput()" />	
            	&nbsp;            	
            	<img align="absmiddle" style="cursor: pointer;" border="0" hspace="0" id="f_trigger_enddate" src="<%= themeDisplay.getPathThemeRoot() %>/images/calendar/calendar.gif" vspace="0" onClick="lnqb_jsOnClick('lnqb_jsCalendarObj');">
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
            <td width="40%" align=left><font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="endDate" />
							</font></td>
          </tr>
           
          <tr>
            <td width="3%"></td>
            <td width="12%" valign="baseline" class="text_or_12"><bean:message key="ecardtransaction.querydetail.chooseaccount" />: 
              </td>
            <td width="45%" valign="baseline" class="text_or_12"> 
            	<html:select property="cardId">
            		<%for (int i = 0; i < availableCards.size(); i++) {
            			TPifCard card = (TPifCard) availableCards.get(i);%>
            		<html:option value="<%= card.getCardId().toString()%>">
            		<bean:message key="ecard.account" /><%= i + 1%>
            		</html:option>
            		<%}%>
            	</html:select>           				
            </td>
            <td width="40%" align=left><font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="cardId" />
							</font></td>
          </tr>
        </table>
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
          <table width="99%" height="35"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td align="center">
              	<html:submit styleClass="button_blank" value='<%= LanguageUtil.get(pageContext, "ecard.query") %>'  />
				<html:reset property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>' />
				</td>
            </tr>
          </table>
          </html:form>
          <!-- content table --></td>
        <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_2.jpg">&nbsp;</td>
      </tr>
      <tr>
        <td width="9" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_3.jpg" width="9" height="7"></td>
        <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_foot.jpg"></td>
        <td width="6" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_3.jpg" width="6" height="7"></td>
      </tr>
    </table>