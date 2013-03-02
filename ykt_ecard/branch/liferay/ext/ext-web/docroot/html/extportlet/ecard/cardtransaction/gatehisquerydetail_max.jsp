<%@ include file="/html/extportlet/ecard/cardtransaction/init.jsp"%>


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



<%String gbeginDate = DateFormatUtil.getDateLaterNow();
String gendDate = DateFormatUtil.getNowDate();
Object obj = request.getAttribute("GateHisTradeDetailQueryForm");
if (obj != null) {
	gbeginDate = (String) ((DynaValidatorForm) obj).get("gbeginDate");
	gendDate = (String) ((DynaValidatorForm) obj).get("gendDate");	
}

%>

    <table width="100%"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td width="9" height="7">&nbsp;</td>
        <td height="7"></td>
        <td width="6" height="7">&nbsp;</td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td valign="top">
        <!-- content table -->
       <html:form action="/ext/ecardtransactiongatehisquerydetail_result" 
				method="POST" onsubmit="javascript:setgatehisFormAction(this);submitPortletForm(this);return false;">
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td></td>
          </tr>
        </table>
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>
            <td width="3%"></td>
            <td width="20%" valign="baseline" class="text_or_12"><bean:message key="ecard.beginDate" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12">            
				<html:text styleId="gbeginDate" property="gbeginDate" readonly="true" size="30" value="<%= gbeginDate%>" maxlength="10" onkeydown="monitorDateInput()" />	
				&nbsp;
				<img align="absmiddle" style="cursor: pointer;" border="0" hspace="0" id="f_trigger_begindate_g" src="/html/extthemes/classic/images/calendar/calendar.gif" vspace="0" onClick="zgat_jsOnClick('zgat_jsCalendarObj');">
            </td>
            <td width="20%" align=left><font  style="font-size: 11;"><html:errors
							property="beginDate" />
							</font></td>
          </tr>
          <tr>
          	<td width="3%"></td>
            <td width="20%" valign="baseline" class="text_or_12"><bean:message key="ecard.endDate" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12">
            	<html:text styleId="gendDate" property="gendDate" size="30" readonly="true" value="<%= gendDate%>" maxlength="10" onkeydown="monitorDateInput()" />	
            	&nbsp;            	
            	<img align="absmiddle" style="cursor: pointer;" border="0" hspace="0" id="f_trigger_enddate_g" src="/html/extthemes/classic/images/calendar/calendar.gif" vspace="0" onClick="lnqb_jsOnClick('lnqb_jsCalendarObj');">
            </td>
    
            <td width="20%" align=left><font style="font-size: 11;"><html:errors
							property="gendDate" />
							</font></td>
          </tr>
          
          <tr>
            <td width="3%"></td>
            <td width="20%" valign="baseline" class="text_or_12">&nbsp;
              </td>
            <td width="60%" valign="baseline" class="text_or_12"> 
            	&nbsp;       				
            </td>
            <td width="20%" align=left><font style="font-size: 11;">&nbsp;
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
				</td>
            </tr>
          </table>
          </html:form>
          <!-- content table --></td>
        <td >&nbsp;</td>
      </tr>
      <tr>
        <td width="9" height="7">&nbsp;</td>
        <td height="7"></td>
        <td width="6" height="7">&nbsp;</td>
      </tr>
    </table>
      <script language="JavaScript">
                    
                Calendar.setup({
                    inputField     :    "gbeginDate",     // id of the input field
                    button         :    "f_trigger_begindate_g",  // trigger for the calendar (button ID)
                    align          :    "Bl",           // alignment (defaults to "Bl")
                    singleClick    :    true
                });
                
                Calendar.setup({
                    inputField     :    "gendDate",     // id of the input field
                    button         :    "f_trigger_enddate_g",  // trigger for the calendar (button ID)
                    align          :    "Bl",           // alignment (defaults to "Bl")
                    singleClick    :    true
                });
            </script>
    
    <script>
function setgatehisFormAction(form) {
	form.action = '<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/ext/ecardtransactiongatehisquerydetail_result" /></portlet:actionURL>';	
}

</script>
<%}%>