<%@ include file="/html/portlet/ecard/maintain/init.jsp" %>
<%
String search_title = ParamUtil.getString(request, "search_title");
//String search_content = ParamUtil.getString(request, "search_content");
int pageNum = ParamUtil.get(request, "page", 0);
String status ="userQuery";
String userId = (String)request.getSession().getAttribute(WebKeys.USER_ID);
ResultPage curpage = 
  MaintainUtil.list(search_title,userId,status,pageNum, EcardConstants.LIST_MORE_SIZE);

List list = curpage.getList();
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg">
              <table width="100%"  border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td width="2%">&nbsp;</td>
                  <td width="72%" class="text_blue_12_c"><bean:message key="equipment.maintain" /></td>
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
                    <tr>
                      <td>
                     <html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.add")%>' onclick="javascript:renderAddPage()" />
                       </td>
                     <tr>
                     <tr class="list_tr">
                     <td width=10% align=center>
			          <a class=text_blue_12_c><bean:message key="maintain.Num" /></a>
		             </td>
                     <td width=70% align=center>
			          <a class=text_blue_12_c><bean:message key="apply.info" /></a>
		             </td>
		              <td width=10% align=center>
			            <a class=text_blue_12_c><bean:message key="apply.time" /></a>
	                  </td>
		             <td width=10% align=center>
		             	<a class=text_blue_12_c><bean:message key="apply.people" /></a>
		          </td>
                     </tr>
                                        <%java.util.Iterator it = list.iterator();				
										while(it.hasNext()) {
											Maintain info = (Maintain) it.next();
										%>
										<tr>
										<td  class=text_blue_12 align="left">
					                  		  <img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/jiantou.jpg" width="8" height="8">   <%=info.getId()%>
					                  		</td>
											<td >
									
					                  <a href="#" class=blue_link_line onclick="javascript:submit(<%=info.getId()%>)">
					                        <%if(info.getApplyInfo().length()>=30){
					                           out.print(info.getApplyInfo().substring(0,40)+"......");
					                           }else{
					                           out.print(info.getApplyInfo());
					                           }
					                        %>
					                  	</a>
					                  	<img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/hot.gif" width="17" height="8">
					                  
					                  		</td>
					                  		   
					                  		<td  class=text_blue_12 align="center"><%= info.getApplyTime()%>
					                  		</td>
					                  		<td  class=text_blue_12 align="center">
					                  		     <%=UserUtil.findByPrimaryKey(info.getApplyPeople()).getFirstName ()%>
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
function submit(id){
self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/maintain/userdetail" /></portlet:renderURL>&id=' + id;
}
function goto(page) {
	self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/maintain/view" /></portlet:renderURL>&page=' + page;
}
function renderAddPage() {
	self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/maintain/userAdd" /></portlet:renderURL>';
}
</script>