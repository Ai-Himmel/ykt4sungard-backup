<%@ include file="/html/portlet/ecard/maintain/init.jsp" %>
<%

//String search_title = ParamUtil.getString(request, "search_title");
//String search_content = ParamUtil.getString(request, "search_content");
String  status = request.getAttribute("status")==null?"0":request.getAttribute("status").toString();
        
String  type = request.getAttribute("type")==null?"":request.getAttribute("type").toString();
int     pageNum = request.getAttribute("page")==null?0:Integer.parseInt(request.getAttribute("page").toString());
String  appBeginDate = request.getAttribute("appBeginDate")==null?"":request.getAttribute("appBeginDate").toString(); 
String  appEndDate = request.getAttribute("appEndDate")==null?"":request.getAttribute("appEndDate").toString(); 
String  asrBeginDate = request.getAttribute("asrBeginDate")==null?"":request.getAttribute("asrBeginDate").toString(); 
String  asrEndDate = request.getAttribute("asrEndDate")==null?"":request.getAttribute("asrEndDate").toString(); 
List statusList = new ArrayList();
statusList = MaintainUtil.getMaintainType("002");
List typeList = new ArrayList();
   typeList = MaintainUtil.getMaintainType("001");
String userId = (String)request.getSession().getAttribute(WebKeys.USER_ID);
ResultPage curpage = (ResultPage)request.getAttribute("curpage");
if(curpage == null){
		 curpage =  MaintainUtil.adminQry(userId,status,type,appBeginDate,appEndDate,asrBeginDate,asrEndDate,pageNum, EcardConstants.LIST_MORE_SIZE);
}
List list = curpage.getList();

%>
 <html:form  action="/maintain/adminQry" method="POST"
					onsubmit="submitPortletForm(this); return false;">
		<input  type="hidden" name ="page" value="0"/>			
       <table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg">
              <table width="100%"  border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td width="2%">&nbsp;</td>
                  <td width="72%" class="text_blue_12_c"><bean:message key="maintain.answer" /></td>
                  <td width="11%" valign="bottom">
                  </td>
                 </td>
                </tr>
              </table></td>
            </tr>
          </table>
            <table width="719"  border="0" cellspacing="0" cellpadding="0">
              <tr>
                <td height="5" width="20%" align="center"><bean:message key="answer.status"/></td>
                <td height="5" width="25%"><!--
                  <html:select  property="status" value="">
                     <logic:notEmpty name="statusList">
                      <html:option  value=""></html:option>
                      <html:options collection="statusList" property="id.dicValue" labelProperty="dicCaption" />
                     </logic:notEmpty>
                  </html:select>
                -->
                <select name="status" >
                 <option value=""></option>
                  <%java.util.Iterator s = statusList.iterator();
                    while(s.hasNext()){
                            WebDictionary wd =(WebDictionary)s.next();
                            String  selected="";
                            if(status.equals(wd.getId().getDicValue())){
                              selected="selected";
                            }
                  %>  
                     <option value="<%=wd.getId().getDicValue()%>" <%=selected%> ><%=wd.getDicCaption()%></option>
                  <%}%> 
                  
                </select>
                 
                </td>
                <td height="5" width="20%" align="center"><bean:message key="maintain.type"/></td>
                <td height="5" width="25%" ><!--
                  <html:select  property="type" value="">
                   <logic:notEmpty name="MaintainType">
                     <html:option  value=""></html:option>
                     <html:options  collection="MaintainType" property="id.dicValue" labelProperty="dicCaption" />
                   </logic:notEmpty>
                  </html:select>
                -->
                 <select name="type" value="type">
                  <option value=""></option>
                 <%java.util.Iterator t = typeList.iterator();
                    while(t.hasNext()){
                            WebDictionary wd =(WebDictionary)t.next();
                            String  select="";
                            if(type.equals(wd.getId().getDicValue())){
                              select="selected";
                    }
                  %> 
                     <option value="<%=wd.getId().getDicValue()%>" <%=select%>><%=wd.getDicCaption()%></option>
                  <%}%> 
                  </select>
                </td>
               
              </tr>
              <tr>
				 <td height="5" width="20%" align="center" >
						<bean:message key="apply.time" />
				</td>
				<td  height="5" width="10%"  >
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td width="80">
						<input name="appBeginDate" class="input_box" style="width: 80"
						maxlength="8" readonly="true" value="<%=appBeginDate%>">
						</td>
						<td>
						&nbsp;&nbsp;
						<a href="#"><img
						src="<%=themeDisplay.getPathThemeRoot()%>/images/ecard/portlet/date.gif"
						width="16" height="16" border="0" id="f_trigger_appBeginDate">
							</a>
						</td>
				  	</tr>
					</table>
				</td>
				
				<td height="5" width="10%" align="left">
					----&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					  <bean:message key="apply.time" />
				</td>
				<td  height="5" width="10%" align="left">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
					<td width="80">
							<input name="appEndDate" class="input_box" style="width: 80"
								maxlength="8" readonly="true" value="<%=appEndDate%>">
					</td>
					<td>
						&nbsp;&nbsp;
						<a href="#"><img
						src="<%=themeDisplay.getPathThemeRoot()%>/images/ecard/portlet/date.gif"
						width="16" height="16" border="0" id="f_trigger_appEndDate">
						</a>
					</td>
					</tr>
				   </table>
				</td>
				 <td height="5" width="20%" >
                 
                </td>
			</tr>
		
			 <tr>
				 <td height="5" width="20%" align="center" >
						<bean:message key="answer.time" />
				</td>
				<td  height="5" width="20%"  >
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td width="80">
						<input name="asrBeginDate" class="input_box" style="width: 80"
						maxlength="8" readonly="true" value="<%=asrBeginDate%>">
						</td>
						<td>
						&nbsp;&nbsp;
						<a href="#"><img
						src="<%=themeDisplay.getPathThemeRoot()%>/images/ecard/portlet/date.gif"
						width="16" height="16" border="0" id="f_trigger_asrBeginDate">
							</a>
						</td>
				  	</tr>
					</table>
				</td>
				
				<td height="5" width="10%" align="left">
					----&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<bean:message key="answer.time" />
				</td>
				<td  height="5" width="20%" >
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
					<td width="80">
							<input name="asrEndDate" class="input_box" style="width: 80"
								maxlength="8" readonly="true" value="<%=asrEndDate%>">
					</td>
					<td>
						&nbsp;&nbsp;
						<a href="#"><img
						src="<%=themeDisplay.getPathThemeRoot()%>/images/ecard/portlet/date.gif"
						width="16" height="16" border="0" id="f_trigger_asrEnddate">
						</a>
					</td>
					</tr>
				   </table>
				</td>
				
				 <td height="5" width="20%" >
                  <html:submit styleClass="button_blank" property="save" value='<%= LanguageUtil.get(pageContext, "maintain.query")%>'/> 
                </td>
                
			</tr>
			
            </table>
            <table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td>
              <table width="100%"  border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td width="2%">&nbsp;</td>
                  <td width="72%" class="text_blue_12_c"></td>
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
                  </table>
                  </td>
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
                   
                     <tr class="list_tr">
                     <td width=10% align=center>
			          <a class=text_blue_12_c><bean:message key="maintain.Num" /></a>
		             </td>
                     <td width=70% align=center>
			          <a class=text_blue_12_c><bean:message key="apply.title" /></a>
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
									
					                  <a href="#" class=blue_link_line onclick="javascript:adminAnswer(<%=info.getId()%>)">
					                  <%if(info.getApplyInfo().length()>=30){
					                           out.print(info.getApplyInfo().substring(0,40)+"......");
					                           }else{
					                           out.print(info.getApplyInfo());
					                           }
					                        %>	 
                                      </a>
					                  	<img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/hot.gif" width="17" height="8">
					                  		</td>
					                  		<td  class=text_blue_12  align="center"><%= info.getApplyTime()%>
					                  		</td>
					                  		<td  class=text_blue_12  align="center">
					                  		     <%=UserUtil.findByPrimaryKey(info.getApplyPeople()).getFirstName()%>
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
      </html:form>         
<script>
function query(){
  self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/maintain/admin" /></portlet:renderURL>';
}
function adminAnswer(id){
    self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/maintain/adminAnswer" /></portlet:renderURL>&id=' + id;
}
function goto(page) {
   AdminQryForm.all.page.value=page;
   submitPortletForm(AdminQryForm);
}

	Calendar.setup({
        inputField     :    "appBeginDate",     // id of the input field
        weekNumbers		:	false,
    	ifFormat	   :	"%Y/%m/%d",
        button         :    "f_trigger_appBeginDate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    
    Calendar.setup({
        inputField     :    "appEndDate",     // id of the input field
        weekNumbers		:	false,
    	ifFormat	   :	"%Y/%m/%d",
        button         :    "f_trigger_appEndDate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    	Calendar.setup({
        inputField     :    "asrBeginDate",     // id of the input field
        weekNumbers		:	false,
    	ifFormat	   :	"%Y/%m/%d",
        button         :    "f_trigger_asrBeginDate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    
    Calendar.setup({
        inputField     :    "asrEndDate",     // id of the input field
        weekNumbers		:	false,
    	ifFormat	   :	"%Y/%m/%d",
        button         :    "f_trigger_asrEndDate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    

</script>