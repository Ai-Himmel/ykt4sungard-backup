<%@ include file="/html/extportlet/ecard/about/init.jsp"%>
<%@ include file="/html/extportlet/ecard/about/permission.jsp"%>
<%
	ResultPage result = EcardInformationServiceUtil
			.list(EcardConstants.INFORMATION_ABOUT_TYPE);
	EcardInformation info = (EcardInformation) result.getList().get(0);
%>
<table width="719" height="29" border="0" cellpadding="0"
	cellspacing="0">
	<tr>
		<td width="166" class="text_brown">
			<a class="txt_or"
				href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardaboutedit" /></portlet:renderURL>">
				<bean:message key="ecard.management" /> </a>
		</td>
	</tr>
</table>
<table width="70%" align=center  border="0" cellspacing="0" cellpadding="0">

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
                <%= info.getInfoTitle()==null?"":info.getInfoTitle()%>
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
            <td valign="bottom">
                <%= info.getInfoContent()==null?"":info.getInfoContent()%>
              </td>            
          </tr>
        </table>
          <!-- content table --></td>
        <td>&nbsp;</td>
      </tr>
    </table>