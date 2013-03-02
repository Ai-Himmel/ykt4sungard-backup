
<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp"%>
<%@ include file="/html/portlet/ecard/cardtransaction/permission_delay_user.jsp" %>
<%SimpleDateFormat format = new SimpleDateFormat("yyyy/MM/dd");%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardtransaction.tab.carddelay" /></td>
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
        <td valign="top" align=center bgcolor="#FFFFFF">
        <!-- content table -->
			<html:form action="/ecardtransaction/add_postpone_result" method="POST" enctype="multipart/form-data"
	onsubmit="javascript:submitPortletForm(this); return false;">
       
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="14%" valign="baseline" class="text_or_12"><bean:message key="ecardtransaction.cardpostpone.date" />: 
              </td>
            <td width="50%" valign="baseline" class="text_or_12">            
            <html:text styleId="postponeTime" property="postponeTime" readonly="true" size="20" value="<%= format.format(new Date())%>" maxlength="8" onkeydown="monitorDateInput()" />
            &nbsp;
            <img align="absmiddle" style="cursor: pointer;" border="0" hspace="0" id="f_trigger_postponetime" src="<%= themeDisplay.getPathThemeRoot() %>/images/calendar/calendar.gif" vspace="0" onClick="zgat_jsOnClick('zgat_jsCalendarObj');">
            <script language="JavaScript">
					
					Calendar.setup({
				        inputField     :    "postponeTime",     // id of the input field
				        button         :    "f_trigger_postponetime",  // trigger for the calendar (button ID)
				        align          :    "Tr",           // alignment (defaults to "Bl")
				        singleClick    :    true
				    });
			</script>
            </td>
            <td width="36%" align=left><font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="postponeTime" />
							</font></td>
          </tr>
          <tr>            
            <td width="14%" valign="top" class="text_or_12"><bean:message key="ecardtransaction.cardpostpone.reason" />: 
              </td>
            <td width="50%" valign="baseline" class="text_or_12">
            <html:textarea cols="50" rows="10" property="reason" />
            </td>
            <td width="36%" valign=top align=left>
            <font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="reason" />
							</font></td>
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
          <table width="70%" height="35"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td align="right">
              	<input type=button class="button_blank" value='<%= LanguageUtil.get(pageContext, "ecardtransaction.button.apply") %>'  
						onclick="if (confirm('<%= UnicodeLanguageUtil.get(pageContext, "ecard.cardpostpone.confirm") %>')) {  submitPortletForm(document.PostponeInputForm); }">
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