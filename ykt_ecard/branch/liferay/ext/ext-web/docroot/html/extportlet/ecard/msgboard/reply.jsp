<%@ include file="/html/extportlet/ecard/msgboard/init.jsp" %>
<%@ include file="/html/extportlet/ecard/tutorial/permission.jsp" %>
<%
	int id = ParamUtil.getInteger(request, "id");
	EcardMsgboard msg = MsgBoardServiceUtil.getMsg(id);
	SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td ><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardmsgboard.tab.reply" /></td>
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
        <td >&nbsp;</td>
        <td valign="top">
        <!-- content table -->
        <html:form action="/ext/ecardmsgboardreply_result" method="POST"
						onsubmit="javascript:submitPortletForm(this); return false;">
		<html:hidden property="id" value="<%= String.valueOf(msg.getId())%>" />
		
		<input type=hidden name="search_title" value="<%= ParamUtil.getString(request, "search_title")%>" >
		<input type=hidden name="search_content" value="<%= ParamUtil.getString(request, "search_content")%>" >
		<input type=hidden name="page" value="<%= ParamUtil.getString(request, "page")%>" >
		
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td></td>
          </tr>
        </table>
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
          <tr>
            <td width="3%"><img src="/html/extthemes/classic/images/ecard/pic_ask.jpg" width="19" height="24"></td>
            <td width="8%" valign="baseline" class="text_or_12"><bean:message key="ecardmsgboard.content.title" />: 
              </td>
            <td width="60%" valign="baseline" class="text_blue_12">
            <%= msg.getMsgTitle()%> [<bean:message key="ecard.comefrom" />: <%= msg.getPoster()%> <%= format.format(msg.getPostTime())%>]</td>
          </tr>
          <tr>
              <td width="3%">&nbsp;</td>
              <td width="8%" valign="top" class="text_or_12"><bean:message key="ecardmsgboard.content.postcontent" />: </td>
              <td width="89%" valign="baseline" class="text_blue_12">
              <%= msg.getPostContent()%>
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
              <td width="3%">&nbsp;</td>
              <td width="8%" valign="top" class="text_or_12"><bean:message key="ecardmsgboard.content.replycontent" />: </td>
              <td width="74%" valign="baseline" class="text_or_12">
              <html:textarea property="replyContent" style="width:510px" rows="20" /></td>
                          <td width="15%" valign="top" align=left><font  style="font-size: 11;"><html:errors
							property="replyContent" />
							</font></td>
            </tr>
          </table>

          <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td></td>
            </tr>
          </table>
          <table width="99%" height="35"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td align="right">
              	<html:submit styleClass="button_blank" value='<%= LanguageUtil.get(pageContext, "ecard.save") %>'  />
				<html:button property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>' />
				<html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>' onclick="javascript:document.renderadminfm.submit();" />
				</td>
            </tr>
          </table>
          </html:form>
          <!-- content table --></td>
        <td>&nbsp;</td>
      </tr>
    </table>
    <form name=renderadminfm method=post action="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ext/ecardmsgboardsearch_result" /></portlet:renderURL>">
		<input type=hidden name="search_title" value="<%= ParamUtil.getString(request, "search_title")%>" >
		<input type=hidden name="search_content" value="<%= ParamUtil.getString(request, "search_content")%>" >
		<input type=hidden name="page" value="<%= ParamUtil.getString(request, "page")%>" >
	</form>