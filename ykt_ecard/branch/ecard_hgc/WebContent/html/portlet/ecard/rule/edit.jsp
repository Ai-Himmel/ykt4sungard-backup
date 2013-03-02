<%@ include file="/html/portlet/ecard/rule/init.jsp" %>
<%@ include file="/html/portlet/ecard/rule/permission.jsp" %>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardrule.tab.editrule" /></td>
          <td width="11%" valign="bottom">&nbsp;</td>
          <td width="15%" align="right" valign="middle" nowrap class="text_brown">&nbsp;</td>
        </tr>
      </table></td>
    </tr>
  </table>
    <table width="100"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="5">
       
        </td>
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
        <td valign="top" bgcolor="#FFFFFF">
        <!-- content table -->
        <%
        	String id= request.getParameter("id");
			EcardInformation info = InformationUtil.getInfoById(id); 
			Object obj = request.getAttribute("InfoEditForm");
			String title = info.getInfoTitle();
			String formatContent = info.getInfoContent();
			if (obj != null) {
				formatContent = (String) ((DynaValidatorForm) obj).get("content");
				title = (String) ((DynaValidatorForm) obj).get("title");
			}
			
		%>
        <html:form action="/ecardrule/edit_result" method="POST"
					onsubmit="javascript:setArticleContent(this);submitPortletForm(this); return false;">
					<html:hidden property="content" />
					<input type=hidden name="search_title" value="<%= ParamUtil.getString(request, "search_title")%>" >
					<input type=hidden name="search_content" value="<%= ParamUtil.getString(request, "search_content")%>" >
					<input type=hidden name="page" value="<%= ParamUtil.getString(request, "page")%>" >
					<html:hidden property="id" value="<%= id%>" />					
						<script>
							function initEditor() {		
								return "<%= UnicodeFormatter.toString(formatContent)%>";
							}
							function resetEditBox() {
								<c:if test="<%= BrowserSniffer.is_rtf(request) %>">
									parent.<portlet:namespace />editor.resetHTML("<%= UnicodeFormatter.toString(formatContent)%>");
								</c:if>
							}
							//save the editor's content to hidden field "content"
								function setArticleContent(form) {
											<c:choose>
												<c:when test="<%= BrowserSniffer.is_rtf(request) %>">
													form.content.value = parent.<portlet:namespace />editor.getHTML();
												</c:when>
												<c:otherwise>
													form.content.value = form.<portlet:namespace />editor.value;
												</c:otherwise>
											</c:choose>
								}
								function setCmdType(cmd) {
									InfoInputForm.cmd.value = cmd;
								}
						</script>
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
          	<td width="5%">&nbsp;
              </td>
            <td width="95%">
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
            <td width="5%" valign="baseline" class="text_or_12"><bean:message key="ecard.title" />: 
              </td>
            <td width="70%" valign="baseline" class="text_or_12">
            <html:text property="title" size="60" value="<%= title%>" /></td>
            <td width="22%" align=left><font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="title" />
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
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="5%" valign="top" class="text_or_12"><bean:message key="ecard.content" />: </td>
              <td width="70%" valign="baseline" class="text_or_12">
              <c:choose>
					<c:when test="<%= BrowserSniffer.is_rtf(request) %>">
						<iframe frameborder="0" height="400"
							id="<portlet:namespace />editor"
							name="<portlet:namespace />editor" scrolling="no"
							src="<%= themeDisplay.getPathJavaScript() %>/editor/editor.jsp"
							width="100%"></iframe>
					</c:when>
					<c:otherwise>
						<textarea class="form-text" cols="80"
							id="<portlet:namespace />editor"
							name="<portlet:namespace />editor" rows="20" wrap="soft"
							onKeyDown="checkTab(this); disableEsc();"></textarea>
					</c:otherwise>
				</c:choose></td>
                 <td width="22%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="content" />
							</font></td>
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
              	<html:submit styleClass="button_blank" property="save" value='<%= LanguageUtil.get(pageContext, "ecard.save") %>'  /> 				
				<html:reset property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>' onclick="javascript:resetEditBox();" />
				<html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>' onclick="javascript:document.renderadminfm.submit();" />
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
    <form name=renderadminfm method=post action="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardrule/admin" /></portlet:renderURL>">
		<input type=hidden name="search_title" value="<%= ParamUtil.getString(request, "search_title")%>" >
		<input type=hidden name="search_content" value="<%= ParamUtil.getString(request, "search_content")%>" >
		<input type=hidden name="page" value="<%= ParamUtil.getString(request, "page")%>" >
	</form>