<%@ include file="/html/portlet/ecard/maintain/init.jsp"%>
<%@ page import="com.kingstargroup.ecard.hibernate.util.MaintainUtil"%>
<%@ page import="com.liferay.portal.model.User"%>
<%  List list = MaintainUtil.getMaintainType("001");%>
<%  List typeList = MaintainUtil.getMaintainType("009");%>
<%  String userId = (String) request.getSession().getAttribute(WebKeys.USER_ID);%>
<%  User   users =  UserLocalServiceUtil.getUserById(userId);%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="equipment.maintain" /></td>
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
        <html:form action="/maintain/useradd_result" method="POST"
					onsubmit="submitPortletForm(this); return false;">
			<html:hidden property="cmd" />
						<script>
								function setCmdType(cmd) {
									InputmaintainForm.cmd.value = cmd;	
								 }
						</script>
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
              <td width="15%" align="center" class="text_or_12"><bean:message key="maintain.school" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
                
        
              <select  name="school">
                <option>  </option>
                 <%java.util.Iterator t = typeList.iterator();
                    while(t.hasNext()){
                            WebDictionary wd =(WebDictionary)t.next();
                  %> 
                     <option value="<%=wd.getId().getDicValue()%>" ><%=wd.getDicCaption()%></option>
                  <%}%> 
               
              </select>
             </td>
              </td>
                 <td width="30%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors  	property="school" />  </font><br>   </td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" align="center" class="text_or_12"><bean:message key="apply.people" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="applyPeople"   size="10" value="<%=users.getFirstName()%>" />  
             </td>
              </td>
                 <td width="30%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors  		property="applyPeople" />
							</font><br>
							</td>
            </tr>
          </table>
             <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" align="center" class="text_or_12"><bean:message key="apply.email" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="applyEmail"   size="30" />  
             </td>
              </td>
                 <td width="30%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors  		property="applyEmail" />
							</font><br>
							</td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" align="center" class="text_or_12"><bean:message key="maintain.contactmethod" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="contact"   size="30" />   <bean:message key="maintain.contactTel"/>
             </td>
              </td>
                 <td width="30%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors
							property="contact" />
							</font><br>
							</td>
            </tr>
          </table>
          
           <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" align="center" class="text_or_12"><bean:message key="maintain.accidentDate" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="accidentDate"  readonly="true"  size="20"/>  <a href="#"><img
						src="<%=themeDisplay.getPathThemeRoot()%>/images/ecard/portlet/clock.gif"
							width="21" height="21" border="0" id="f_trigger_accidentDate">
						</a> 
             </td>
              </td>
                 <td width="30%" valign="top" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors 		property="accidentDate" />	</font><br>	</td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" align="center" class="text_or_12"><bean:message key="maintain.accidentTime" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="accidentTime" readonly="true"  size="20"/>  
               <a href="#"><img
						src="<%=themeDisplay.getPathThemeRoot()%>/images/ecard/portlet/clock.gif"
							width="21" height="21" border="0" id="f_trigger_accidentTime">
						</a>
             </td>
            
                 <td width="30%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors  property="accidentTime" /> </font><br>	</td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              
              <td width="15%" align="center" class="text_or_12"><bean:message key="apply.info" />: </td>
              <td width="60%" valign="baseline" class="text_or_12">
              <html:textarea property="applyInfo"  cols="50"  rows="10" styleClass="form-text"  />
              </td>
              </td>
                 <td width="30%" valign="center" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors
							property="applyInfo" />
							</font><br>
							  <bean:message key="maintain.remark" />
							</td>
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
              <td align="right">
              	<html:submit styleClass="button_blank" property="save" value='<%= LanguageUtil.get(pageContext, "ecard.save") %>' onclick="javascript:setCmdType('save');" /> 
				<!--<html:submit property="saveandnext" styleClass="button_blank" value='<%= LanguageUtil.get(pageContext, "ecard.saveandnext") %>' onclick="javascript:setCmdType('saveandnext');" />
				--><html:reset property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>'  />
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
		self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/maintain/view" /></portlet:renderURL>';
	}
	
	Calendar.setup({
        inputField     :    "accidentTime",     // id of the input field
        weekNumbers		:	false,
    	ifFormat	   :	"%H%M",
        button         :    "f_trigger_accidentTime",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true,
        showsTime	   :	true,
        timeFormat	   :	"24"
    });
    Calendar.setup({
        inputField     :    "accidentDate",     // id of the input field
        weekNumbers		:	false,
    	ifFormat	   :	"%Y/%m/%d",
        button         :    "f_trigger_accidentDate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
	</script>