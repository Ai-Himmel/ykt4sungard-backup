<%@ include file="/html/portlet/ecard/maintain/init.jsp"%>
<%@ page import="com.kingstargroup.ecard.hibernate.util.MaintainUtil"%>
<%  Maintain maintain = (Maintain)request.getSession().getAttribute("Maintain");%>
<%  List list = MaintainUtil.getMaintainType("001");%>
<%  List typeList = (List)request.getAttribute("TypeList");
    List selectTypeList = (List)request.getAttribute("selectTypeList");
    String contact = maintain.getContactMethod();
%>
<%  String schoolArea = (String)request.getAttribute("schoolArea");%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="equipment.miantain.manage" /></td>
          <td width="11%" valign="bottom">&nbsp;</td>
          <td width="15%" align="right" valign="middle" nowrap class="text_brown">&nbsp;</td>
        </tr>
      </table></td>
    </tr>
  </table>
    <table width="100"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="5">
       
        </td>
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
        <html:form action="/maintain/adminanswer_result" method="POST"
					onsubmit="submitPortletForm(this); return false;">
		<input type="hidden" name="id" value="<%=(String)request.getAttribute("id")%>">
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
          	<td width="5%">&nbsp;
              </td>
            <td width="95%">
            <c:if test="<%= SessionErrors.contains(request, EcardConstants.ADD_INFO_SUCCEED) %>">		
								<font class="portlet-msg-success" style="font-size: 11;">
								<bean:message key="ecard.error.addinfosucceed" />	
								</font>								
			</c:if>
            </td>
          </tr>
        </table>
        
          <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td bgcolor="#e1e1e2"></td>
            </tr>
          </table>    
           
          <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td bgcolor="#e1e1e2"></td>
            </tr>
          </table>        
          
           
         <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.school" />: </td>
               <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="school" styleClass="text_blue_12_c" value="<%=schoolArea%>"  readonly="true"  size="20"/>  
                </td>
              <td width="30%" valign="top" align=left>
              </td>
            </tr>
          </table>
          
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="apply.people" />: </td>
               <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="applyPeople" styleClass="text_blue_12_c"  value="<%=maintain.getApplyPeople()%>"   readonly="true"  size="20"/>  
             </td>
             <td width="30%" valign="top" align=left>
             </td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="apply.email" />: </td>
               <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="applyEmail" styleClass="text_blue_12_c"  value="<%=maintain.getApplyEmail()%>"   readonly="true"  size="20"/>  
             </td>
             <td width="30%" valign="top" align=left>
             </td>
            </tr>
          </table>
          
          
           <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.contactmethod" />: </td>
               <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="contact" styleClass="text_blue_12_c"  value="<%=maintain.getContactMethod()%>"   readonly="true"  size="20"/>  
             </td>
              </td>
                 <td width="30%" valign="top" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors    				property="contact" />  
                 	</font></td>
            </tr>
          </table>
          
             
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.accidentDate" />: </td>
               <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="accidentDate" styleClass="text_blue_12_c"  value="<%=maintain.getAccidentDate()%>"  readonly="true"  size="20"/>  
             </td>
              </td>
                 <td width="30%" valign="top" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   	property="accidentDate" />  	</font></td>
            </tr>
          </table>
          
          
           <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.accidentTime" />: </td>
               <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="accidentTime"  styleClass="text_blue_12_c"  value="<%=maintain.getAccidentTime()%>"   readonly="true"  size="20"/>  
             </td>
              </td>
                 <td width="30%" valign="top" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors    	property="accidentTime" /> </font></td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="apply.info" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
              <textarea  name="applyInfo" class="text_blue_12_c" cols="50" readonly="true"  rows="5" wrap="soft"><%=maintain.getApplyInfo()%></textarea>
              </td>
              </td>
                 <td width="30%" valign="top" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="applyInfo" />
							</font></td>
            </tr>
          </table>
            <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.applyPeopleAnswer" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
              <textarea  name="applyPeopleAnswer"  cols="50" class="text_blue_12_c" readonly="true"
				 rows="5" wrap="soft" ><%=maintain.getApplyPeopleAnswer()==null?"":maintain.getApplyPeopleAnswer()%></textarea>
              </td>
              </td>
                 <td width="35%" valign="top" align=left>
                  <br>
                </td>
            </tr>
          </table>
          
          
          <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td bgcolor="#e1e1e2"></td>
            </tr>
          </table>  
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.operator" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
                <html:text property="operator"  styleClass="text_blue_12_c"  value="<%=maintain.getOperator()%>"    size="20"/>  
              </td>
              </td>
                 <td width="30%" valign="top" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="operator" />
							</font></td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.explain" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
               <html:textarea  property="accidentExplain" styleClass="text_blue_12_c" value="<%=maintain.getAccidentExplain()%>" cols="50"  rows="5" />
              </td>
              </td>
                 <td width="30%" valign="top" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="accidentExplain" />
							</font></td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.depend" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
              <html:textarea  property="operatorDepend" styleClass="text_blue_12_c" cols="50" value="<%=maintain.getOperatorDepend()%>"		 rows="2" />
              </td>
              </td>
                 <td width="30%" valign="top" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="operatorDepend" />
							</font></td>
            </tr>
          </table>
          
            <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.step" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
              <html:textarea   property="operatorStep"  styleClass="text_blue_12_c" cols="50"  value="<%=maintain.getOperatorStep()%>"		 rows="5" />
              </td>
              </td>
                 <td width="30%" valign="top" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="operatorStep" />
				</font>
			</td>
            </tr>
          </table>
          
          
          
          <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
           <tr>
             <td width="15%" valign="baseline" class="text_or_12"><bean:message key="maintain.type" />: 
              </td>
              <td  class="text_blue_12_c">
               <%for(int i=0;i<list.size();i++){
				 WebDictionary info = (WebDictionary) list.get(i);
				 String  checked="";
				 if(selectTypeList != null){
				   if(selectTypeList.contains(info)){
				   		checked="checked";
				   }
				 }
			   %>
                 <input type="checkbox" name="maintainType" value="<%=info.getId().getDicValue()%>" <%=checked%>> <%=info.getDicCaption()%><%if((i+1)%3==0){%><br><%}%>
              <%}%>
            </td>
          <c:if test="<%= SessionErrors.contains(request, EcardConstants.CHOOSE_MAINTAIN_TYPE) %>">		
			<td>				
					<font class="portlet-msg-error" style="font-size: 11;">
					<bean:message key="maintain.error.choosetype" />
					</font>
			</td>
		</c:if>   
             </tr>
          </table>    
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="answer.info" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
              <html:textarea property="answerInfo"  cols="50"  rows="5" styleClass="text_blue_12_c"  value="<%=maintain.getAnswerInfo()%>" />
              </td>
                 <td width="30%" valign="top" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="answerInfo" />
				</font></td>
            </tr>
          </table>
          
         
          

          <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td></td>
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
              <td align="center">
              	<html:submit styleClass="button_blank" property="save" value='<%= LanguageUtil.get(pageContext, "commit") %>'  /> 
				<!--<html:submit property="saveandnext" styleClass="button_blank" value='<%= LanguageUtil.get(pageContext, "ecard.saveandnext") %>' onclick="javascript:setCmdType('saveandnext');" />
				<html:reset property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>'  />-->
				<html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>' onclick="javascript:renderAdminPage();" />
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
    <script>
	function renderAdminPage() {
		self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/maintain/admin" /></portlet:renderURL>';
	}
	</script>