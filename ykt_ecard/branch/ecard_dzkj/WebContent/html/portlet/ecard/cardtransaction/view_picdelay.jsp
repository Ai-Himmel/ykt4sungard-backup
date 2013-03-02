
<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp"%>
<%@ include file="/html/portlet/ecard/cardtransaction/permission_delay_user.jsp" %>
<%
	String customerId = (String) request.getSession().getAttribute(WebKeys.USER_ID);
	EcardPicDelay apply = PicDelayUtil.getDelayById(customerId);
	SimpleDateFormat format = new SimpleDateFormat("yyyyMMdd");
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardtransaction.tab.applyinfo" /></td>
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
        <td valign="top" align=left bgcolor="#FFFFFF">
        <!-- content table -->
        <%if (apply == null) {%>
			<form name=postponeForm action="<portlet:renderURL><portlet:param name="struts_action" value="/ecardtransaction/add_picdelay" /></portlet:renderURL>" 
						method=post onSubmit="submitForm(this);return false;">
       
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>                        
            <td align=left valign="baseline" class="text_blue_12">
            <bean:message key="ecardtransaction.picdelay.noapply" /></td>
            
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
          <table width="30%" height="35"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td align="right">
              	<input type=submit value='<bean:message key="ecardtransaction.button.apply" />' class="button_blank">
				
				</td>
            </tr>
          </table>
          </form>
          <%} else {%>          
       
        <table class="tdclass"  width="40%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="35%" align=right valign="baseline" class="text_or_12">
              <bean:message key="ecardtransaction.picdelay.curStuempNo" />:
              </td>
             <td valign=baseline>&nbsp;</td>
            <td width="60%" align=left valign="baseline" class="text_blue_12">
            <%= apply.getCurStuempNo()%></td>            
          </tr>
          
          <tr>            
            <td width="35%" align=right valign="baseline" class="text_or_12">
              <bean:message	key="ecardtransaction.picdelay.oldStuempNo" />:
              </td>
              <td valign=baseline>&nbsp;</td>
            <td width="60%" align=left valign="baseline" class="text_blue_12">
            <%= apply.getOldStuempNo()%></td>
          </tr>
          
          <tr>            
            <td width="35%" align=right valign="baseline" class="text_or_12">
              <bean:message	key="ecardtransaction.cardpostpone.status" />:
              </td>
              <td valign=baseline>&nbsp;</td>
            <td width="60%" align=left valign="baseline" class="text_blue_12">
            <%= LanguageUtil.get(pageContext, "ecardtransaction.processstatus." + apply.getStatus()) %></td>
          </tr>
          
               
          
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
          <table width="40%" height="35"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td align="right">
              <c:if test="<%= !apply.getStatus().equals(EcardConstants.POSTPONE_STATUS_ACCEPTED)%>">
              <form name=cancelForm action="<portlet:actionURL><portlet:param name="struts_action" value="/ecardtransaction/cancelPicDelay" /></portlet:actionURL>" 
			method=post onSubmit="javascript:submitForm(this);return false;">
              		<input type=submit value='<bean:message key="ecardtransaction.button.cancelapply" />' class="button_blank">
              </form>
							</c:if>
				</td>
            </tr>
          </table>
          <%}%>
          <!-- content table --></td>
        <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_2.jpg">&nbsp;</td>
      </tr>
      <tr>
        <td width="9" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_3.jpg" width="9" height="7"></td>
        <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_foot.jpg"></td>
        <td width="6" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_3.jpg" width="6" height="7"></td>
      </tr>
    </table>