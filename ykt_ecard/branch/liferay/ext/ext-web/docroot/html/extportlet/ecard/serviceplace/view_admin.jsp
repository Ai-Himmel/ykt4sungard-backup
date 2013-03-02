<%@ include file="/html/extportlet/ecard/serviceplace/init.jsp"%>
<%@ include file="/html/extportlet/ecard/serviceplace/permission.jsp"%>

<table width="100%" height="29" border="0" cellpadding="0"
	cellspacing="0">
	<tr>
		<td width="166" class="text_brown">
			<a class="txt_or"
				href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/serviceplaceedit" /></portlet:renderURL>">
				<bean:message key="ecard.management" /> </a>
		</td>
	</tr>
</table>
<%
    ResultPage result = EcardInformationServiceUtil
            .list(EcardConstants.INFORMATION_DISTRIBUTION_TYPE);
 List list = result.getList();
if(list!=null&&list.size()>0){
    EcardInformation info = (EcardInformation) list.get(0);
%>

<table width="80%" align=center  border="0" cellspacing="0" cellpadding="0">
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
                <b><%= info.getInfoTitle()==null?"":info.getInfoTitle()%></b>
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
    
       <%}%>