
<%@ include file="/html/extportlet/ecard/faq/init.jsp"%>
<%@ include file="/html/extportlet/ecard/faq/permission.jsp" %>

<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardfaq.tab.editsubtype" /></td>
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
        <td>&nbsp;</td>
        <td valign="top" align=center bgcolor="#FFFFFF">
        <!-- content table -->
        <%
        String id= request.getParameter("id");
				InfoType info = InfoTypeServiceUtil.getTypeById(id);
        Object obj = request.getAttribute("TypeEditForm");
				String typeName = info.getInfoName();
				if (obj != null) {
					typeName = (String) ((DynaValidatorForm) obj).get("typeName");
				}%>
			<html:form action="/ext/ecardfaqedit_type_result" method="POST"
					onsubmit="javascript:submitPortletForm(this); return false;">
					<html:hidden property="id" value="<%= id%>" />
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
          	<td>
            </td>
          </tr>
        </table>
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="10%" valign="baseline" class="text_or_12"><bean:message key="ecard.subtype" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12">
            <html:text property="typeName" size="60" value="<%= typeName%>" /></td>
            <td width="27%" align=left><font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="typeName" />
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
          <table width="89%" height="35"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td align="right">
              	<html:submit styleClass="button_blank" property="save" value='<%= LanguageUtil.get(pageContext, "ecard.save") %>' /> 
				<html:reset property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>' />
				<html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>' onclick="javascript:renderAdminPage();" />
				</td>
            </tr>
          </table>
          </html:form>
          <!-- content table --></td>
        <td>&nbsp;</td>
      </tr>
    </table>
    <script>
function renderAdminPage() {	
	self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ext/ecardfaqadmin_type" /></portlet:renderURL>';
}
</script>