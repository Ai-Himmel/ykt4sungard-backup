<%@ include file="/html/portlet/ecard/cardlist/init.jsp" %>
<%
ResultPage curpage = (ResultPage) request.getAttribute("result");
List list = curpage.getList();
SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg">
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="2%">&nbsp;</td>
            <td width="72%" class="text_blue_12_c"><bean:message key="ecard.searchresult" /></td>
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
          
            <table cellpadding="4" cellspacing="0" width="100%">
		
				
		                  <%java.util.Iterator it = list.iterator();				
							while(it.hasNext()) {
								EcardInformation info = (EcardInformation) it.next();
								String[] attachIds = StringUtil.split(info.getAttachments(), EcardConstants.DELIMITER);
							%>
							<tr>
								<td >
						<img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/jiantou.jpg" width="8" height="8">
		                  <a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardlist/view" /></portlet:renderURL>&id=<%= info.getId()%>" class=blue_link_line>
		                  	<%= info.getInfoTitle()%>(<%= format.format(info.getCreateDate())%>)</a>
		                  		</td>
		                  	</tr>
		                	<%}%>   
		                	<tr>
		                		<td>
		                			&nbsp;
		                		</td>
		                	</tr>
		</table>
            <!-- content table -->
            </td>
          <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_2.jpg">&nbsp;</td>
        </tr>
        <tr>
          <td width="9" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_3.jpg" width="9" height="7"></td>
          <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_foot.jpg"></td>
          <td width="6" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_3.jpg" width="6" height="7"></td>
        </tr>
      </table>
<script>
function goto(page) {
	document.InfoSearchForm.page.value = page;
	submitForm(document.InfoSearchForm);
}
</script>