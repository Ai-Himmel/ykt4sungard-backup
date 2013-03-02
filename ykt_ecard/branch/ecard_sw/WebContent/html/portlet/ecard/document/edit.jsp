<%@ include file="/html/portlet/ecard/document/init.jsp"%>
<%@ include file="/html/portlet/ecard/document/permission.jsp" %>
<%
String id= request.getParameter("id");
EcardInformation info = InformationUtil.getInfoById(id);
UploadFiles file = UploadFileUtil.getFileById(StringUtil.split(info.getAttachments())[0]);
Object obj = request.getAttribute("FileInfoEditForm");
String title = info.getInfoTitle();
if (obj != null) {
	title = (String) ((DynaValidatorForm) obj).get("title");
}
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecarddoc.tab.editdoc" /></td>
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
        <html:form action="/ecarddoc/edit_result" method="POST" enctype="multipart/form-data"
						onsubmit="javascript:submitPortletForm(this); return false;">
						<input type=hidden name="search_title" value="<%= ParamUtil.getString(request, "search_title")%>" >

					<input type=hidden name="page" value="<%= ParamUtil.getString(request, "page")%>" >
						<html:hidden property="id" value="<%= id%>" />
				<html:hidden property="attachments" value="<%= info.getAttachments()%>" />
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td></td>
          </tr>
        </table>
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="12%" valign="baseline" class="text_or_12"><bean:message key="ecard.title" />: 
              </td>
            <td width="53%" valign="baseline" class="text_or_12">
            <html:text property="title" size="60" value="<%= title%>" /></td>
            <td width="35%" align=left><font class="portlet-msg-error" style="font-size: 11;"><html:errors
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
            <td width="12%" valign="baseline" class="text_or_12"><bean:message key="ecarddoc.content.uploaded_attachments" />: 
              </td>
            <td width="53%" valign="baseline" class="text_or_12">
            <%= file.getOldFilename()%></td>
            <td width="35%" align=left>&nbsp;</td>
          </tr>
        </table>
          
          <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td></td>
            </tr>
          </table>                  
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="14%" valign="baseline" class="text_or_12">
              <bean:message key="ecarddoc.content.replace_attachments" />: </td>
              <td width="53%" valign="baseline" class="text_or_12">
              <input type=file styleClass="text_or_12" size="50" name="file_location" ></td>
                          <td width="33%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
							<c:if test="<%= SessionErrors.contains(request, FileSizeException.class.getName()) %>">										
								<bean:message key="ecard.error.filesize" arg0="<%= String.valueOf(EcardConstants.DOC_MAX_SIZE) %>" />
							</c:if>
							<c:if test="<%= SessionErrors.contains(request, FileNameException.class.getName()) %>">										
								<bean:message key="ecard.error.filename" arg0='<%= PropsUtil.get("info.upload.document.extension") %>' />
							</c:if>
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
    <form name=renderadminfm method=post action="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecarddoc/admin" /></portlet:renderURL>">
		<input type=hidden name="search_title" value="<%= ParamUtil.getString(request, "search_title")%>" >
		<input type=hidden name="page" value="<%= ParamUtil.getString(request, "page")%>" >
	</form>