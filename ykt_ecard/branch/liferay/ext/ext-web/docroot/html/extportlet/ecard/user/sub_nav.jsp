<%@ include file="/html/extportlet/ecard/user/init.jsp" %>	 
    
    <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td></td>
      </tr>
    </table>
    <table width="242"  border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td align="right" valign="top">
		
		<table width="100%"  border="0" cellspacing="0" cellpadding="0" >
          <tr>
            <td width="27%" height="29">&nbsp;</td>
			<td width="73%" class="txt_or" style="cursor:hand" onClick="">
			<a class="txt_or" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecarduser/edit_password" /></portlet:renderURL>" >
			<bean:message key="ecard.editpassword" />
			</a></td>
          </tr>
        </table>
		       
		</td>

      </tr>
    </table>
	 <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td></td>
      </tr>
    </table>