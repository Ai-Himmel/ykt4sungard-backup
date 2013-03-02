<%@ include file="/html/extportlet/ecard/cardlist/init.jsp"%>


<table width="719" height="29" border="0" cellpadding="0"
	cellspacing="0">
	<tr>
		<td>
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td width="2%">
						&nbsp;
					</td>
					<td width="72%" class="text_blue_12_c">
						<bean:message key="ecardlist.tab.editlist" />
					</td>
					<td width="11%" valign="bottom">
						&nbsp;
					</td>
					<td width="15%" align="right" valign="middle" nowrap
						class="text_brown">
						&nbsp;
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>
<table width="100" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td height="5">

		</td>
	</tr>
</table>
<table width="719" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td>
			&nbsp;
		</td>
		<td valign="top">
			<!-- content table -->
			<%
				String id = request.getParameter("id");
				EcardInformation info = EcardInformationServiceUtil.getInfoById(id);
				Object obj = request.getAttribute("CardlistEditForm");
				String title = info.getInfoTitle();
				String formatContent = info.getInfoContent();
				if (obj != null) {
					formatContent = (String) ((DynaValidatorForm) obj)
							.get("content");
					title = (String) ((DynaValidatorForm) obj).get("title");
				}
			%>
			<html:form action="/ext/ecardlistedit_result" method="POST"
				onsubmit="javascript:setArticleContent(this);submitPortletForm(this); return false;">
				<input type=hidden name="search_title"
					value="<%=ParamUtil.getString(request, "search_title")%>">
				<input type=hidden name="search_content"
					value="<%=ParamUtil.getString(request, "search_content")%>">
				<input type=hidden name="page"
					value="<%=ParamUtil.getString(request, "page")%>">

				<html:hidden property="content" />
				<html:hidden property="id" value="<%=id%>" />
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
				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td width="5%">
							&nbsp;
						</td>
						<td width="95%">
							<c:if
								test="<%=SessionErrors.contains(request,
							EcardConstants.ADD_INFO_SUCCEED)%>">
								<font style="font-size: 11;">
									<bean:message key="ecard.error.addinfosucceed" /> </font>
							</c:if>
						</td>
					</tr>
				</table>
				<table width="100%" border="0" cellspacing="0" cellpadding="0">

					<tr>
						<td width="5%" valign="baseline" class="text_or_12">
							<bean:message key="ecard.title" />
							:
						</td>
						<td width="70%" valign="baseline" class="text_or_12">
							<html:text property="title" size="60" value="<%=title%>" />
						</td>
						<td width="22%" align=left>
							<font style="font-size: 11;"><html:errors
									property="title" /> </font>
						</td>
					</tr>
				</table>
				<table width="100%" height="1" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td bgcolor="#e1e1e2"></td>
					</tr>
				</table>
				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td width="5%" valign="top" class="text_or_12">
							<bean:message key="ecard.content" />
							:
						</td>
						<td width="70%" valign="baseline" class="text_or_12">
							<c:choose>
								<c:when test="<%=BrowserSniffer.is_rtf(request)%>">
									<iframe frameborder="0" height="400"
										id="<portlet:namespace />editor"
										name="<portlet:namespace />editor" scrolling="no"
										src="/html/extjs/editor/editor.jsp" width="100%"></iframe>
								</c:when>
								<c:otherwise>
									<textarea class="form-text" cols="80"
										id="<portlet:namespace />editor"
										name="<portlet:namespace />editor" rows="20" wrap="soft"
										onKeyDown="checkTab(this); disableEsc();"></textarea>
								</c:otherwise>
							</c:choose>
						</td>
						<td width="22%" valign="top" align=left>
							<font style="font-size: 11;"> <html:errors
										property="content" /> </font>
						</td>
					</tr>
				</table>

				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>
				<table width="89%" height="35" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td align="right">
							<html:submit styleClass="button_blank" property="save">
								<bean:message key="ecard.save" />
							</html:submit>
							<html:reset property="reset" styleClass="button_blank"
								onclick="javascript:resetEditBox();">
								<bean:message key="ecard.reset" />
							</html:reset>
							<html:button property="add" styleClass="button_blank"
								onclick="javascript:document.renderadminfm.sumit();" >
				<bean:message key="ecard.goback" />
				</html:button>
						</td>
					</tr>
				</table>
			</html:form>
			<!-- content table -->
		</td>
		<td>
			&nbsp;
		</td>
	</tr>
</table>
<form name=renderadminfm method=post
	action="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardlistadmin" /></portlet:renderURL>">
	<input type=hidden name="search_title"
		value="<%=ParamUtil.getString(request, "search_title")%>">
	<input type=hidden name="search_content"
		value="<%=ParamUtil.getString(request, "search_content")%>">
	<input type=hidden name="page"
		value="<%=ParamUtil.getString(request, "page")%>">
</form>