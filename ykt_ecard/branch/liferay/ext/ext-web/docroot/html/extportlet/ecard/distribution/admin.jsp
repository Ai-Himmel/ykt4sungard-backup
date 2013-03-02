<%@ include file="/html/extportlet/ecard/distribution/init.jsp" %>
<%@ include file="/html/extportlet/ecard/distribution/permission.jsp" %>
<%
String search_title = ParamUtil.getString(request, "search_title");
String search_content = ParamUtil.getString(request, "search_content");
int pageNum = ParamUtil.get(request, "page", 0);
ResultPage curpage = EcardInformationServiceUtil.search(search_title, search_content, 
											EcardConstants.INFORMATION_DISTRIBUTION_TYPE, 
											pageNum, 
											EcardConstants.ADMIN_SIZE);
List list = curpage.getList();
SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>

<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td>
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="2%">&nbsp;</td>
            <td width="72%" class="text_blue_12_c"><bean:message key="distribution.tab.managemaps" /></td>
            <td width="11%" valign="bottom"><table border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td width="13" align="right">   
                <c:if test="<%=curpage.isPreviousPage()%>">                   
                  <a href="javascript:goto('<%=curpage.getPage() - 1%>')">
                  <img align="middle" src="/html/extthemes/classic/images/ecard/left.gif" width="13" height="9" border="0">
                  </a>
		  					</c:if>				                   
                </td>
                <td width="40" align="center" class="text_brown">
                <%= curpage.getPage() + 1%>/<%= curpage.getTotalPage()%></td>
                <td width="13">
                <c:if test="<%=curpage.isNextPage()%>">
                  <a href="javascript:goto('<%=curpage.getPage() + 1%>')">
                  <img align="middle" src="/html/extthemes/classic/images/ecard/right.gif" width="13" height="9" border="0"></a>
               </c:if>
                </td>
              </tr>
            </table></td>
            <td width="15%" align="right" valign="middle" nowrap class="text_brown">
		<bean:message key="ecard.goto" />
              <select name="select2" onchange="goto(this.options[this.selectedIndex].value)">
              	<%for (int i = 1; i <= curpage.getTotalPage(); i++) {%>
                <option value="<%= i - 1%>" 
                <c:if test="<%= i == (curpage.getPage() + 1)%>">
                	selected
                </c:if>
                ><%= i%></option>
                	<%}%>
              </select>
              <bean:message key="ecard.page" /></td>
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
          <td>&nbsp;</td>
          <td valign="top">
          <!-- content table -->
          <form name=InfoDelForm action="<portlet:actionURL><portlet:param name="struts_action" value="/ext/distributiondelete" /></portlet:actionURL>" method="POST"
	onSubmit="javascript:submitForm(this); return false;">
		<input type=hidden name=search_title value="<%= search_title%>">
		<input type=hidden name=search_content value="<%= search_content%>">
          <table border="0" cellpadding="0" cellspacing="0" width="100%">
       <c:if test="<%= SessionErrors.contains(request, EcardConstants.CHOOSE_DEL_CONTENT) %>">		
		<tr>
			<td>				
					<font class="portlet-msg-error" style="font-size: 11;">
					<bean:message key="ecard.error.choosedeleteitems" />
					</font>
			</td>
		</tr>
		</c:if>   
		<c:if test="<%= SessionErrors.contains(request, EcardConstants.DELETE_INFO_SUCCEED) %>">		
		<tr>
			<td>				
					<font class="portlet-msg-success" style="font-size: 11;">
					<bean:message key="ecard.error.deleteinfosucceed" />
					</font>
			</td>
		</tr>
		</c:if>  
		<c:if test="<%= SessionErrors.contains(request, EcardConstants.EDIT_INFO_SUCCESS) %>">		
		<tr>
			<td>				
					<font class="portlet-msg-success" style="font-size: 11;">
					<bean:message key="ecard.error.editinfosuccess" />
					</font>
			</td>
		</tr>
		</c:if>
		<c:if test="<%= SessionErrors.contains(request, EcardConstants.DELETE_INFO_FAILED) %>">		
		<tr>
			<td>				
					<font class="portlet-msg-error" style="font-size: 11;">
					<bean:message key="ecard.error.deleteinfofailed" />
					</font>
			</td>
		</tr>
		</c:if>   		
		<tr>
			<td>				
					<html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.add")%>' onclick="javascript:renderAddPage()" />
				
					<input type="button" name="delete" class="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.delete")%>' 
					onClick="if (confirm('<%= UnicodeLanguageUtil.get(pageContext, "ecard.delete.confirm") %>')) {  submitForm(document.InfoDelForm); }">				
			</td>
		</tr>
		<tr>
			<td>&nbsp;</td>
		</tr>
		</table>
       <table width="100%" class="inside_table">
      <tr class="list_tr">
        <td width=3% >
			<input name="ids_allbox" type="checkbox"
				onClick="
					for (var i = 0; i < InfoDelForm.elements.length; i++) {
						var e = document.InfoDelForm.elements[i];

						if ((e.name == 'ids') && (e.type == 'checkbox')) {
							e.checked = this.checked;
						}
					}"
			>
		</td>
		<td width=70% align=center>
			<a class=text_blue_12_c><bean:message key="ecard.title" /></a>
		</td>
		<td width=15% align=center>
			<a class=text_blue_12_c><bean:message key="ecard.publishtime" /></a>
		</td>
		<td width=12% align=center>
			<a class=text_blue_12_c><bean:message key="ecard.publisher" /></a>
		</td>
      </tr>
      <%java.util.Iterator it = list.iterator();
      				int count = 0;
					while(it.hasNext()) {
						EcardInformation info = (EcardInformation) it.next();
						count++;
						int classId = count % 2 + 1;
					%>
	<tr class="tr_<%= classId%>" style="font-size: x-small;">
		<td width=10>
		<input type="checkbox" name="ids" value="<%= String.valueOf(info.getId())%>" 
						onClick="javascript:checkAllBox(document.InfoDelForm, 'ids', document.InfoDelForm.ids_allbox)" />
		
		</td>		
		<td align=center>
			<a class=blue_link_line href="javascript:setRenderEditForm('<%= info.getId()%>', '<%= search_title%>' , '<%= search_content%>', '<%= pageNum%>');">
			<%= info.getInfoTitle()%>
			</a>
		</td>
		<td align=center>
			<a class=text_blue_12>
			<%= format.format(info.getCreateDate())%>
			</a>
		</td>
		<td align=center>
			<a class=text_blue_12>
			<%= info.getCreater()%>
			</a>
		</td>
	</tr>
	<%}%>

	</table>
</form>
            <!-- content table -->
            </td>
          <td >&nbsp;</td>
        </tr>
      </table>
<form name=rendereditfm method=post action="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ext/distributionedit" /></portlet:renderURL>">
	<input type=hidden name=id value="">
	<input type=hidden name=search_title value="">
	<input type=hidden name=search_content value="">
	<input type=hidden name=page value="">
</form>
<script>
function setRenderEditForm(id, title, content, page) {
	document.rendereditfm.id.value = id;
	document.rendereditfm.search_title.value = title;
	document.rendereditfm.search_content.value = content;
	document.rendereditfm.page.value = page;
	document.rendereditfm.submit();
}
</script>       
<script>
function goto(page) {
	document.InfoSearchForm.page.value = page;
	submitForm(document.InfoSearchForm);
}
</script>
<script>
function renderAddPage() {
	self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ext/distributionadd" /></portlet:renderURL>';
}
</script>