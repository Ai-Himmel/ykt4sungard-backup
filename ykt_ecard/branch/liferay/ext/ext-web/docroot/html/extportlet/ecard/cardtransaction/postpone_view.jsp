<%@ include file="/html/extportlet/ecard/cardtransaction/init.jsp"%>
<%
Long realUserId = (Long) request.getSession().getAttribute(
			WebKeys.USER_ID);
	User myuser = UserLocalServiceUtil.getUserById(realUserId);
	String stuempNo = myuser.getScreenName();
	EcardPostponeApply apply = PostponeServiceUtil.getPostponeByStuempNo(stuempNo);
	SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>

    <table width="100%"  border="0" cellspacing="0" cellpadding="0">
      	<c:if test="<%=PermissionUtil.hasCardTransactionAdmin(request)%>">
		<tr>
			<td width="166" class="text_brown">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ext/ecardtransactionpostpone_admin" /></portlet:renderURL>" >
			<bean:message key="ecardtransaction.tab.processcarddelay" />
			</a>
			</td>
		</tr>
	</c:if>
    </table>
    <table width="100%"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td width="9" height="7"></td>
        <td height="7" ></td>
        <td width="6" height="7"></td>
      </tr>
      <tr>
        <td >&nbsp;</td>
        <td valign="top" align=left >
        <!-- content table -->
        <%if (apply == null) {%>
			<form name=postponeForm action="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/ext/ecardtransactionadd_postpone" /></portlet:renderURL>" 
						method=post onSubmit="submitForm(this);return false;">
         
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td align=left valign="baseline" class="text_blue_12">
            <bean:message key="ecardtransaction.cardpostpone.noapply" /></td>
            
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
       
        <table class="tdclass" width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="20%" align="left" valign="baseline" class="text_or_12">
              <bean:message key="ecardtransaction.cardpostpone.reason" />:
              </td>
            <td valign=baseline>&nbsp;</td>
            <td width="80%" align=left valign="baseline" class="text_blue_12">
            <%= apply.getReason()%> </td>
          </tr>
          
          <tr>            
            <td width="20%" align="left" valign="baseline" class="text_or_12">
              <bean:message	key="ecardtransaction.cardpostpone.date" />:
              </td>
              <td valign=baseline>&nbsp;</td>
            <td width="80%" align=left valign="baseline" class="text_blue_12">
            <%= DateFormatUtil.format(apply.getPostponeTime())%> </td>
          </tr>
          
          <tr>            
            <td width="20%" align="left" valign="baseline" class="text_or_12">
              <bean:message	key="ecardtransaction.cardpostpone.applytime" />:
              </td>
              <td valign=baseline>&nbsp;</td>
            <td width="80%" align=left valign="baseline" class="text_blue_12">
            <%= format.format(apply.getApplyTime())%></td>
          </tr>
          
          <tr>            
            <td width="20%" align="left" valign="baseline" class="text_or_12">
              <bean:message key="ecardtransaction.cardpostpone.status" />:
              </td>
              <td valign=baseline>&nbsp;</td>
            <td width="80%" align=left valign="baseline" class="text_blue_12">
            <%= LanguageUtil.get(pageContext, "ecardtransaction.processstatus." + apply.getStatus()) %></td>
          </tr>
          
          <tr>            
            <td width="20%" align="left" valign="baseline" class="text_or_12">
              <bean:message key="ecardtransaction.cardpostpone.checkResult" />:
              </td>
              <td valign=baseline>&nbsp;</td>
            <td width="80%" align=left valign="baseline" class="text_blue_12">
            <%= apply.getCheckResult()==null?"":apply.getCheckResult() %></td>            
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
          <table width="40%" height="35"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td align="right">
            <c:if test="<%= apply.getStatus().equals(EcardConstants.POSTPONE_STATUS_UNACCEPTED)%>">
              <form name=cancelForm action="<portlet:actionURL><portlet:param name="struts_action" value="/ext/ecardtransactioncancelPostpone" /></portlet:actionURL>" 
							method=post onSubmit="javascript:submitForm(this);return false;">
					<input type=hidden name=id value="<%= apply.getId()%>">
              		<input type="submit" value='<bean:message key="ecardtransaction.button.cancelapply" />' class="button_blank">
              </form>
			</c:if>
			<c:if test="<%= apply.getStatus().equals(EcardConstants.POSTPONE_STATUS_REJECTED)%>">
              <form name=postponeForm action="<portlet:renderURL><portlet:param name="struts_action" value="/ext/ecardtransactionadd_postpone" /></portlet:renderURL>" 
						method=post onSubmit="submitForm(this);return false;">
              		<input type="submit" value='<bean:message key="ecardtransaction.button.reapply" />' class="button_blank">
              </form>
			</c:if>
			<c:if test="<%= apply.getStatus().equals(EcardConstants.POSTPONE_STATUS_ACCEPTED)%>">
              <form name=postponeForm action="<portlet:renderURL><portlet:param name="struts_action" value="/ext/ecardtransactionadd_postpone" /></portlet:renderURL>" 
						method=post onSubmit="submitForm(this);return false;">
              		<input type="submit" value='<bean:message key="ecardtransaction.button.apply" />' class="button_blank">
              </form>
			</c:if>
				</td>
            </tr>
          </table>
          <%}%>
          <!-- content table --></td>
        <td >&nbsp;</td>
      </tr>
      <tr>
        <td width="9" height="7"></td>
        <td height="7" ></td>
        <td width="6" height="7"></td>
      </tr>
    </table>