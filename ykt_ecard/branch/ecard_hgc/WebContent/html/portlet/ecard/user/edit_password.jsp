
<%@ include file="/html/portlet/ecard/user/init.jsp"%>

<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecard.editpassword" /></td>
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
        <html:form action="/ecarduser/edit_password_result" method="POST" enctype="multipart/form-data"
					onsubmit="javascript:submitPortletForm(this); return false;">	
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
          	<td width="8%">&nbsp;
              </td>
            <td width="92%">
            <c:if test="<%= SessionErrors.contains(request, EcardConstants.EDIT_PASSWORD_SUCCEED) %>">		
								<font class="portlet-msg-success" style="font-size: 11;">
								<bean:message key="ecard.error.editpasswordsucceed" />	
								</font>								
			</c:if>
            </td>
          </tr>
        </table>
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="8%" valign="baseline" class="text_or_12"><bean:message key="ecard.oldpassword" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12">
            <html:password property="oldpassword" size="40" value="" /></td>
            <td width="29%" align=left><a class="portlet-msg-error"><html:errors
							property="oldpassword" />
							<c:if test="<%= SessionErrors.contains(request, OldPwdErrorException.class.getName()) %>">
							<bean:message key="ecard.error.oldpassworderror" />
							</c:if>
							</a></td>
          </tr>
        </table>
          
          <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td></td>
            </tr>
          </table>                  
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="8%" valign="baseline" class="text_or_12"><bean:message key="ecard.newpassword" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12">
            <html:password property="newpassword" size="40" value="" /></td>
            <td width="29%" align=left><a class="portlet-msg-error"><html:errors
							property="newpassword" />
							<c:if test="<%= SessionErrors.contains(request, UnpairedPwdException.class.getName()) %>">
							<bean:message key="ecard.error.unpairedpassword" />
							</c:if>
							</a>
			</td>
          </tr>
        </table>
		<table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td></td>
            </tr>
          </table>                  
        
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="8%" valign="baseline" class="text_or_12"><bean:message key="ecard.confirmpassword" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12">
            <html:password property="confirmpassword" size="40" value="" /></td>
            <td width="29%" align=left><a class="portlet-msg-error"><html:errors
							property="confirmpassword" />
							</a></td>
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
              	<html:submit styleClass="button_blank" property="save" value='<%= LanguageUtil.get(pageContext, "ecard.save") %>' /> 
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