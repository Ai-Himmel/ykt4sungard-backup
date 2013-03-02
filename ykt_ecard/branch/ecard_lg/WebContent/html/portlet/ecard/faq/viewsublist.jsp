<%@ include file="/html/portlet/ecard/faq/init.jsp" %>

<%
	ResultPage result = (ResultPage) request.getAttribute("result");
	List subList = result.getList();
	
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg">
              <table width="100%"  border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td width="2%">&nbsp;</td>
                  <td width="72%" class="text_blue_12_c"><bean:message key="ecardfaq.tab.viewsublist" /></td>
                  <td width="11%" valign="bottom"><table border="0" cellspacing="0" cellpadding="0">
                    <tr>
                      <td width="13" align="right">   
                     				                   
                      </td>
                      <td width="40" align="center" class="text_brown">
                      
                      <td width="13">
                      
                      </td>
                    </tr>
                  </table></td>
                  <td width="15%" align="right" valign="middle" nowrap class="text_brown">
					</td>
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
					
							
	                  <%java.util.Iterator it = subList.iterator();				
							while(it.hasNext()) {
								InfoType type = (InfoType) it.next();
							%>
						<tr>
							<td >
					<img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/jiantou.jpg" width="8" height="8">
	                  <a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardfaq/view" /></portlet:renderURL>&subid=<%= type.getInfoType()%>" class=blue_link_line>
	                  	<%= type.getInfoName()%></a>
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