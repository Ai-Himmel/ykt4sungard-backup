<%@ include file="/html/extportlet/ecard/lostfound/init.jsp"%>
<%EcardInformation info = (EcardInformation) request.getAttribute("result");%>
<table width="100%" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c">&nbsp;</td>
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
    <table width="100%"  border="0" cellspacing="0" cellpadding="0">

      <tr>
        <td>&nbsp;</td>
        <td valign="top" align=center>
        <!-- content table -->
        
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
          	<td width="8%">&nbsp;
              </td>
            <td width="92%">
							&nbsp;
            </td>
          </tr>
        </table>
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td align=center valign="baseline" class=text_blue_15_c>
            	<%= info.getInfoTitle()%>
              </td>
            
          </tr>
        </table>
          
          <table width="100%" height="10px"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td>&nbsp;</td>
            </tr>
          </table>                  
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">        	
          <tr>            
            <td valign="bottom">
            	<%= info.getInfoContent()%>
              </td>            
          </tr>
          <tr>            
            <td align=right valign="bottom">
            	<html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>' onclick="javascript:renderView();" />
              </td>            
          </tr>          
        </table>
          <!-- content table --></td>
        <td>&nbsp;</td>
      </tr>
    </table>
    <script>
function renderView() {
	self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ext/lostfoundview" /></portlet:renderURL>'+'&filter=true';
}
</script>