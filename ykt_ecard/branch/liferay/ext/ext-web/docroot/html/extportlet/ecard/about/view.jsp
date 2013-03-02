<%@ include file="/html/extportlet/ecard/about/init.jsp"%>
<%ResultPage result = EcardInformationServiceUtil.list(EcardConstants.INFORMATION_ABOUT_TYPE);
EcardInformation info = (EcardInformation) result.getList().get(0);%>
    <table width="90%"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="5"></td>
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