<%@ include file="/html/portlet/ecard/msgboard/init.jsp" %>
<%
	
	int passPage = ParamUtil.getInteger(request, "page");
	ResultPage curpage = MsgBoardUtil.list(passPage);
	List list = curpage.getList();
	SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg">
              <table width="100%"  border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td width="2%">&nbsp;</td>
                  <td width="72%" class="text_blue_12_c"><bean:message key="ecardmsgboard.tab.gross" /></td>
                  <td width="11%" valign="bottom"><table border="0" cellspacing="0" cellpadding="0">
                    <tr>
                      <td width="13" align="right">   
                      <c:if test="<%=curpage.isPreviousPage()%>">                   
	                      <a href="javascript:goto('<%=curpage.getPage() - 1%>')">
	                      <img align="middle" src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/left.gif" width="13" height="9" border="0">
	                      </a>
					  </c:if>				                   
                      </td>
                      <td width="40" align="center" class="text_brown">
                      <%= curpage.getPage() + 1%>/<%= curpage.getTotalPage()%></td>
                      <td width="13">
                      <c:if test="<%=curpage.isNextPage()%>">
	                      <a href="javascript:goto('<%=curpage.getPage() + 1%>')">
	                      <img align="middle" src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/right.gif" width="13" height="9" border="0"></a>
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
	
                <!-- content table -->
                <c:if test="<%= SessionErrors.contains(request, EcardConstants.REPLY_MSG_SUCCESS) %>">		
                	<script>
							alert('<bean:message key="ecard.error.replymsgsuccess" />');
					</script>
				</c:if>
                 <%java.util.Iterator it = list.iterator();				
					while(it.hasNext()) {
						EcardMsgboard msg = (EcardMsgboard) it.next();						
					%>
			<table width="719"  border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td width="9" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_1.jpg" width="9" height="7"></td>
                <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_top.jpg"></td>
                <td width="6" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_1.jpg" width="6" height="7"></td>
              </tr>
              <tr>
                <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_2.jpg">&nbsp;</td>
                <td valign="top" bgcolor="#FFFFFF">
                  <table width="100%"  border="0" cellspacing="0" cellpadding="0">
                  <tr>
                    <td width="3%"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/pic_ask.jpg" width="19" height="24"></td>
                    <td width="88%" valign="baseline" class="text_or_12">
						<%= msg.getMsgTitle()%> [<bean:message key="ecard.comefrom" />: <%= msg.getPoster()%> <%= format.format(msg.getPostTime())%>]</td>
                    <td width="9%" valign="baseline" class="text_or_12">
                    
                    <c:if test="<%= msg.getStatus().equals(EcardConstants.MSG_NO_REPLY) 
                    				&& PermissionUtil.hasMsgboardAdmin(request)%>">
                    <a class=blue_link_line href="javascript:setRenderEditForm('<%= msg.getId()%>', '' , '', '<%= passPage%>');">                    
                    <img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/button.jpg" width="58" height="16" border="0"></a>
                    </c:if>
                    
                    </td>
                    
                  </tr>
                </table>
                  <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
                    <tr>
                      <td bgcolor="#e1e1e2"></td>
                    </tr>
                  </table>
                  <table width="100%" height="25"  border="0" cellpadding="0" cellspacing="0">
                    <tr>
                      <td width="3%">&nbsp;</td>
                      <td width="97%" class="text_or_12">
                      <%= msg.getPostContent()%></td>
                    </tr>
                  </table>
                  
                  <c:if test="<%= !msg.getStatus().equals(EcardConstants.MSG_NO_REPLY)%>">
		           <table width="100%"  border="0" cellspacing="0" cellpadding="0">
                      <tr>
                        <td width="3%"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/pic_an.jpg" width="20" height="24"></td>
                        <td width="88%" valign="baseline" class="text_blue_12">
                        <bean:message key="ecard.reply" />: 
                        [<bean:message key="ecard.comefrom" />: <%= msg.getReplyer()%> <%= format.format(msg.getReplyTime())%>]</td>
                        <td width="9%" valign="baseline" class="text_or_12">&nbsp;</td>
                      </tr>
                    </table>
                    <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
                      <tr>
                        <td bgcolor="#e1e1e2"></td>
                      </tr>
                    </table>
                    <table width="100%" height="25"  border="0" cellpadding="0" cellspacing="0">
                      <tr>
                        <td width="3%">&nbsp;</td>
                        <td width="97%" class="text_blue_12">
						<%= msg.getReplyContent()%>
						</td>
                      </tr>
                  </table>
                  </c:if>
		            </td>
	                <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_2.jpg">&nbsp;</td>
	              </tr>
	              <tr>
	                <td width="9" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_3.jpg" width="9" height="7"></td>
	                <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_foot.jpg"></td>
	                <td width="6" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_3.jpg" width="6" height="7"></td>
	              </tr>
	            </table>
	            <table width="100%" height="8"  border="0" cellpadding="0" cellspacing="0">
		              <tr>
		                <td></td>
		              </tr>
		           </table>
                  <%}%>
                  <!-- content table -->
 <form name=rendereditfm method=post action="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardmsgboard/reply" /></portlet:renderURL>">
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
	self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardmsgboard/view" /></portlet:renderURL>&page=' + page;
}
</script>