<%@ include file="/html/extportlet/ecard/about/init.jsp" %>
<%@ include file="/html/extportlet/ecard/about/permission.jsp" %>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardabout.tab.edit" /></td>
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
        <%        	
			ResultPage result = EcardInformationServiceUtil.list(EcardConstants.INFORMATION_ABOUT_TYPE);
			EcardInformation info = (EcardInformation) result.getList().get(0);
			Object obj = request.getAttribute("AboutEditForm");
			String formatContent = (info.getInfoContent()==null?"":info.getInfoContent());
			if (obj != null) {
				formatContent = (String) ((DynaValidatorForm) obj).get("content");
			}
			
		%>
        <html:form action="/ext/ecardaboutedit_result" method="POST"
					onsubmit="javascript:setArticleContent(this);submitPortletForm(this); return false;">
					<html:hidden property="content" />
					<html:hidden property="id" value="<%= String.valueOf(info.getId())%>" />					
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
						</script>
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
                 <td width="22%" valign="top" align=left><font style="font-size: 11;">
                 <font  style="font-size: 11;"><html:errors
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
				<html:button property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>' onclick="javascript:resetEditBox();" />				
				</td>
            </tr>
          </table>
          </html:form>
          <!-- content table --></td>
        <td>&nbsp;</td>
      </tr>
    </table>