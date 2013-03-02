<%@ include file="/html/portlet/ecard/maintain/init.jsp" %>
<%

//String search_title = ParamUtil.getString(request, "search_title");
//String search_content = ParamUtil.getString(request, "search_content");
String beginDate = request.getAttribute("beginDate")==null?"":request.getAttribute("beginDate").toString(); 
String endDate = request.getAttribute("endDate")==null?"":request.getAttribute("endDate").toString(); 
List statusList = new ArrayList();
statusList = MaintainUtil.getMaintainType("002");
List typeList = new ArrayList();
   typeList = MaintainUtil.getMaintainType("001");
List list = new ArrayList();
list = (List)request.getAttribute("result");

%>
 <html:form  action="/maintain/adminTotal_result" method="POST"
					onsubmit="submitPortletForm(this); return false;">
		<input  type="hidden" name ="page" value="0"/>			
       <table width="720" height="29"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg">
              <table width="100%"  border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td width="2%">&nbsp;</td>
                  <td width="72%" class="text_blue_12_c"><bean:message key="maintain.total" /></td>
                  <td width="11%" valign="bottom">
                  </td>
                 </td>
                </tr>
              </table></td>
            </tr>
          </table>
            <table width="619"  border="0" cellspacing="0" cellpadding="0">
              <tr >  
                <td> <font class="portlet-msg-error" style="font-size: 11;">
                  <html:errors property="beginDate"/>  
                  </font>
                </td>
              </tr>
              <tr>
				 <td height="5" width="20%" align="center" >
						<bean:message key="beginDate" />
				</td>
				<td  height="5" width="20%"  >
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td width="80">
						<!--<input name="beginDate" class="input_box" 
						maxlength="8" readonly="true" value="<%=beginDate%>">
						--><html:text property="beginDate" styleClass="input_box" style="width: 80" maxlength="8" readonly="true" value="<%=beginDate%>"/>
						</td>
						<td>
						&nbsp;&nbsp;
						<a href="#"><img
						src="<%=themeDisplay.getPathThemeRoot()%>/images/ecard/portlet/date.gif"
						width="16" height="16" border="0" id="f_trigger_begindate">
							</a>
						</td>
				  	</tr>
					</table>
				</td>
				<td height="5" width="20%" align="center">
					<bean:message key="endDate" />
				</td>
				<td  height="5" width="20%" >
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
					<td width="80">
							<input name="endDate" class="input_box" style="width: 80"
								maxlength="8" readonly="true" value="<%=endDate%>">
					</td>
					<td>
						&nbsp;&nbsp;
						<a href="#"><img
						src="<%=themeDisplay.getPathThemeRoot()%>/images/ecard/portlet/date.gif"
						width="16" height="16" border="0" id="f_trigger_enddate">
						</a>
					</td>
					</tr>
				   </table>
				</td>
				 <td height="5" width="20%" >
                  <html:submit styleClass="button_blank" property="save" value='<%= LanguageUtil.get(pageContext, "maintain.total")%>'/> 
                </td>
			</tr>
            </table>
           
			<table width="619"  border="0" cellspacing="0" cellpadding="0">
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
                   
                     <tr class="list_tr">
                     <td width=60% align=center>
			          <a class=text_blue_12_c><bean:message key="maintain.type" />(<%=beginDate%>--<%=endDate%>)</a>
		             </td>
		              <td width=40% align=center>
			            <a class=text_blue_12_c><bean:message key="maintain.num" /></a>
	                  </td>
		            </td>
                     </tr>
                                    
								    <%  
								       if(list != null){
								       java.util.Iterator it = list.iterator();		
								       int 		alltype=0;
								       int      allsum=0 ;
									   while(it.hasNext()) {
											Map info = (Map) it.next();
											if(!"0".equals(info.get("dicValue"))&& !"1".equals(info.get("dicValue"))){//
											 alltype=alltype+Integer.parseInt((String)info.get("total"));
										%>
										<tr>
											<td class=text_blue_12 align="center" >
					                   <%=info.get("dicCaption")%>
					                  
					                  		</td>
					                  		<td  class=text_blue_12 align="center">
					                  		   <%=info.get("total")%>
					                  		</td>	
					                  	</tr>
					                	<%}%>
					                	
					                	<%
					                	 if("0".equals(info.get("dicValue"))){
					                	  allsum= allsum+Integer.parseInt((String)info.get("total"));
					                	  %>
					                	   <tr>
					                		<td class=text_blue_12 align="center">
					                			<bean:message key="maintain.noanswer" />
					                		</td>
					                		<td class=text_blue_12 align="center">
					                			<%=info.get("total")%>
					                		</td>
					                	</tr>   
					                	<% }%>
					                	 
					                	 <%if("1".equals(info.get("dicValue"))){
					                	  allsum= allsum+Integer.parseInt((String)info.get("total"));
					                	  %>
					                	  <tr>
					                		<td class=text_blue_12 align="center">
					                			<bean:message key="maintain.hasanswer" />
					                		</td>
					                		<td class=text_blue_12 align="center">
					                			<%=info.get("total")%>
					                		</td>
					                	 </tr>   
					                	  <%
					                	  }
					                	  }
					                	 %>
					                	   <tr>
					                		<td class=text_blue_12 align="center">
					                			<bean:message key="maintain.alltype" />
					                		</td>
					                		<td class=text_blue_12 align="center">
					                			<%=alltype%>
					                		</td>
					                	</tr>   
					                	 	<tr>
					                		<td class=text_blue_12 align="center">
					                			<bean:message key="maintain.allsumm" />
					                		</td>
					                		<td class=text_blue_12 align="center">
					                			<%=allsum%>
					                		</td>
					                	</tr> 
					                  <% 
					                 
					                }%>
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
      </html:form>         
<script>

	Calendar.setup({
        inputField     :    "begindate",     // id of the input field
        weekNumbers		:	false,
    	ifFormat	   :	"%Y/%m/%d",
        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    
    Calendar.setup({
        inputField     :    "enddate",     // id of the input field
        weekNumbers		:	false,
    	ifFormat	   :	"%Y/%m/%d",
        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
</script>