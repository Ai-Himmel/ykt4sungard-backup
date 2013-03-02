<%@ include file="/html/extportlet/ecard/lostfound/init.jsp" %>
<%@ include file="/html/extportlet/ecard/lostfound/permission.jsp" %>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="lostfound.tab.addlostfound" /></td>
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
        <td>&nbsp;</td>
        <td valign="top">
        <!-- content table -->
        <html:form action="/ext/lostfoundadd_result" method="POST"
					onsubmit="javascript:setArticleContent(this);submitPortletForm(this); return false;">					
					<html:hidden property="content" />
					<html:hidden property="cmd" />
					<%Object obj = request.getAttribute("InfoInputForm");
						String formatContent = "";
						if (obj != null) {
							formatContent = (String) ((DynaValidatorForm) obj).get("content");
						}
						%>
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
								<font style="font-size: 11;">
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
            <html:text property="title" size="60" /></td>
            <td width="22%" align=left ><html:errors	property="title" />
							</td>
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
              <td width="80%" valign="baseline" class="text_or_12">
              <c:choose>
					<c:when test="<%= BrowserSniffer.is_rtf(request) %>">
						<iframe frameborder="0" height="400"
							id="<portlet:namespace />editor"
							name="<portlet:namespace />editor" scrolling="no"
							src="/html/extjs/editor/editor.jsp"
							width="100%"></iframe>
					</c:when>
					<c:otherwise>
						<textarea class="form-text" cols="80"
							id="<portlet:namespace />editor"
							name="<portlet:namespace />editor" rows="20" wrap="soft"
							onKeyDown="checkTab(this); disableEsc();"></textarea>
					</c:otherwise>
				</c:choose></td>
                 <td width="15%" valign="top" align=left><font style="font-size: 11;">
                 <font style="font-size: 11;"><html:errors
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
              	<html:submit styleClass="button_blank" property="save" value='<%= LanguageUtil.get(pageContext, "ecard.save") %>'  onclick="javascript:setCmdType('save');" /> 
				<html:submit property="saveandnext" styleClass="button_blank" value='<%= LanguageUtil.get(pageContext, "ecard.saveandnext") %>' onclick="javascript:setCmdType('saveandnext');" />
				<html:button property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>' onclick="javascript:resetEditBox();" />
				<html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>' onclick="javascript:renderAdminPage();" />
				</td>
            </tr>
          </table>
          </html:form>
          <!-- content table --></td>
        <td >&nbsp;</td>
      </tr>
    </table>
    <script>
function renderAdminPage() {
	self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ext/lostfoundadmin" /></portlet:renderURL>';
}
</script>