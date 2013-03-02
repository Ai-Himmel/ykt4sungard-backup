<%@ include file="/html/extportlet/ecard/tutorial/init.jsp" %>

<%EcardInformation info = (EcardInformation) request.getAttribute("result");%>

    <table width="80%"  border="0" cellspacing="0" cellpadding="0" align="center">
      <tr>
        <td>&nbsp;</td>
        <td valign="top" align=center>
        <!-- content table -->
        

        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td align=center valign="baseline" class=text_blue_15_c>
            	<b><%= info.getInfoTitle()%></b>
              </td>
            
          </tr>
        </table>
                <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="8%">&nbsp;
              </td>
            <td width="92%">
                            &nbsp;
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
            <td valign="baseline">
            	<%= info.getInfoContent()%>
              </td>
            
          </tr>
          <tr>            
            <td align=right valign="baseline">
	          <html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>' onclick="javascript:history.go(-1);" />
			</td>            
          </tr>
        </table>
          <!-- content table --></td>
        <td >&nbsp;</td>
      </tr>
    </table>