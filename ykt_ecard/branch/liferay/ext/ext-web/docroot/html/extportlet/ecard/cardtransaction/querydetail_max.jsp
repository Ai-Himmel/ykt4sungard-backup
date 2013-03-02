<%@ include file="/html/extportlet/ecard/cardtransaction/init.jsp" %>
<%@ include file="/html/extportlet/ecard/cardtransaction/permission_general_user.jsp" %>


<%String beginDate = DateFormatUtil.getDateLaterNow();
String endDate = DateFormatUtil.getNowDate();
Object obj = request.getAttribute("TradeDetailQueryForm");
if (obj != null) {
	beginDate = (String) ((DynaValidatorForm) obj).get("beginDate");
	endDate = (String) ((DynaValidatorForm) obj).get("endDate");	
}
Long realUserId = (Long)request.getSession().getAttribute(WebKeys.USER_ID);
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
List availableCards = CardServiceUtil.getAllCards(customerId);
%>

<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.DETAIL_QUERY_DAYS_NUM)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.DETAIL_QUERY_DAYS_NUM, SessionErrors.get(
										request, EcardConstants.DETAIL_QUERY_DAYS_NUM))%> </font>
</c:if>
<table width="100%" height="29"  border="0" cellpadding="0" cellspacing="0">
    <table width="100%"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="5"></td>
      </tr>
    </table>
    <table width="100%"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td width="9" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_l_1.jpg" width="9" height="7"></td>
        <td height="7" background="/html/extthemes/classic/images/ecard/portlet/k_top.jpg"></td>
        <td width="6" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_r_1.jpg" width="6" height="7"></td>
      </tr>
      <tr>
        <td background="/html/extthemes/classic/images/ecard/portlet/k_l_2.jpg"></td>
        <td valign="top" >
        <!-- content table -->
       <html:form action="/ext/ecardtransactionquerydetail_result" 
				method="POST" onsubmit="javascript:setquerydetailFormAction(this);submitPortletForm(this);return false;">
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td></td>
          </tr>
        </table>
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>
            <td width="3%"></td>
            <td width="25%" valign="baseline" class="text_or_12"><bean:message key="ecard.beginDate" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12">            
				<html:text styleId="beginDate" property="beginDate" readonly="true" size="30" value="<%= beginDate%>" maxlength="10" onkeydown="monitorDateInput()" />	
				&nbsp;
				<img align="absmiddle" style="cursor: pointer;" border="0" hspace="0" id="f_trigger_begindate" src="/html/extthemes/classic/images/calendar/calendar.gif" vspace="0" onClick="zgat_jsOnClick('zgat_jsCalendarObj');">
            </td>
            <td width="20%" align=left><font style="font-size: 11;"><html:errors
							property="beginDate" />
							</font></td>
          </tr>
          <tr>
          	<td width="3%"></td>
            <td width="25%" valign="baseline" class="text_or_12"><bean:message key="ecard.endDate" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12">
            	<html:text styleId="endDate" property="endDate" size="30" readonly="true" value="<%= endDate%>" maxlength="10" onkeydown="monitorDateInput()" />	
            	&nbsp;            	
            	<img align="absmiddle" style="cursor: pointer;" border="0" hspace="0" id="f_trigger_enddate" src="/html/extthemes/classic/images/calendar/calendar.gif" vspace="0" onClick="lnqb_jsOnClick('lnqb_jsCalendarObj');">
            </td>         
            <td width="20%" align=left><font style="font-size: 11;"><html:errors
							property="endDate" />
							</font></td>
          </tr>
          
          <tr>
            <td width="3%"></td>
            <td width="25%" valign="baseline" class="text_or_12"><bean:message key="ecardtransaction.querydetail.chooseaccount" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12"> 
            	<html:select property="cardId">
            		<%for (int i = 0; i < availableCards.size(); i++) {
            			TCard card = (TCard) availableCards.get(i);%>
            		<html:option value="<%= card.getCardno().toString()%>">
            		<bean:message key="ecard.account" /><%= i + 1%>
            		</html:option>
            		<%}%>
            	</html:select>  <bean:message key="ecard.allaccount" />        				
            </td>
            
            <td width="20%" align=left><font style="font-size: 11;"><html:errors
							property="cardId" />
							</font></td>
          </tr>
          <tr>
            <td width="3%"></td>
            <td width="25%" valign="baseline" class="text_or_12"><bean:message key="serial.type" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12"> 
            	<html:select property="serialType">
            		<html:option value="1">
            		<bean:message key="serial.consume" />
            		</html:option>
            		<html:option value="2">
            		<bean:message key="serial.checkatt" />
            		</html:option>
            		<html:option value="3">
            		<bean:message key="serial.checkatt_td" />
            		</html:option>
            	</html:select> 				
            </td>
            
            <td width="20%" align=left><font style="font-size: 11;"><html:errors
							property="cardId" />
							</font></td>
          </tr>

        </table>
          <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td><html:hidden property="serialType" value="1"/></td>
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
        <td background="/html/extthemes/classic/images/ecard/portlet/k_r_2.jpg"></td>
      </tr>
      <tr>
        <td width="9" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_l_3.jpg" width="9" height="7"></td>
        <td height="7" background="/html/extthemes/classic/images/ecard/portlet/k_foot.jpg"></td>
        <td width="6" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_r_3.jpg" width="6" height="7"></td>
      </tr>
    </table>
          <script language="JavaScript">
                    
                Calendar.setup({
                    inputField     :    "beginDate",     // id of the input field
                    button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
                    align          :    "Bl",           // alignment (defaults to "Bl")
                    singleClick    :    true
                });
                
                Calendar.setup({
                    inputField     :    "endDate",     // id of the input field
                    button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
                    align          :    "Bl",           // alignment (defaults to "Bl")
                    singleClick    :    true
                });
            </script>
    <script>
function setquerydetailFormAction(form) {
	form.action = '<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/ext/ecardtransactionquerydetail_result" /></portlet:actionURL>';	
}

</script>

<%}%>