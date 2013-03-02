<%@ include file="/html/portlet/ecard/hitinfo/init.jsp"%>
<%@ include file="/html/portlet/ecard/hitinfo/permission.jsp" %>
<%
	Object obj = request.getAttribute("HitInputForm");
	String mapInfoTitle = "";
	if (obj != null) {
		String mapInfoId = (String) ((DynaValidatorForm) obj).get("mapInfoId");
		if (!mapInfoId.equals("")) {
			mapInfoTitle = InformationUtil.getInfoById(mapInfoId).getInfoTitle();
		}
	}
	
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardhit.tab.add" /></td>
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
			<html:form action="/ecardhit/add_result" method="POST"
				onsubmit="javascript:submitPortletForm(this); return false;">	
				<html:hidden property="cmd" />
				<html:hidden property="mapInfoId" />				
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
          	<td width="8%">&nbsp;
              </td>
            <td width="92%">
            <c:if test="<%= SessionErrors.contains(request, EcardConstants.ADD_INFO_SUCCEED) %>">		
								<font class="portlet-msg-success" style="font-size: 11;">
								<bean:message key="ecard.error.addinfosucceed" />	
								</font>								
			</c:if>
            </td>
          </tr>
        </table>
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="10%" valign="baseline" class="text_or_12"><bean:message key="ecard.title" />: 
              </td>
            <td align=left width="70%" valign="baseline" class="text_or_12">
            <html:text property="title" size="60" /></td>
            <td width="20%" align=left><font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="title" />
							</font></td>
          </tr>
        </table>          
          

          <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td></td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="10%" valign="baseline" class="text_or_12"><bean:message key="ecardhit.content.mapinfo" />: 
              </td>
            <td align=left width="70%" valign="baseline" class="text_blue_12">
            	<%= mapInfoTitle%>
            </td>
            <td width="20%" align=left><font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="mapInfoId" />
							</font></td>
          </tr>
        </table>          
          

          <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td></td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="10%" valign="top" class="text_or_12">&nbsp; 
              </td>
            <td align=left width="75%" valign="baseline" class="text_or_12">
            <iframe name="mapidframe" height="275" width="520" frameborder="0" src="/html/portlet/ecard/hitinfo/inner_infolist.jsp"></iframe>
            </td>
            <td width="15%" align=left valign=top><font class="portlet-msg-error" style="font-size: 11;">
							</font></td>
          </tr>
        </table>
			<table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td bgcolor="#e1e1e2"></td>
            </tr>
          </table>
          <table width="89%" height="35"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td align="right">
              	<html:submit styleClass="button_blank" property="save" value='<%= LanguageUtil.get(pageContext, "ecard.save") %>'  onclick="javascript:setCmdType('save');" /> 
				<html:submit property="saveandnext" styleClass="button_blank" value='<%= LanguageUtil.get(pageContext, "ecard.saveandnext") %>' onclick="javascript:setCmdType('saveandnext');" />
				<html:reset property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>' />
				<html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>' onclick="javascript:renderAdminPage();" />
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
	<script>			
		function setCmdType(cmd) {
			document.HitInputForm.cmd.value = cmd;
		}
		function renderAdminPage() {
			self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardhit/admin" /></portlet:renderURL>';
		}
	</script>