<%@ include file="/html/portlet/ecard/maintain/init.jsp"%>
<%@ page import="com.kingstargroup.ecard.hibernate.util.MaintainUtil"%>
<%  String schoolArea = (String)session.getAttribute("schoolArea");%>
<%  Maintain maintain = (Maintain)session.getAttribute("Maintain");%>
<%  List list = MaintainUtil.getMaintainType("001");%>
<%  List typeList = (List)session.getAttribute("TypeList");%>
<%  String id = (String)session.getAttribute("id");%>
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
        <html:form action="/maintain/userupdate_result" method="POST" 	onsubmit="submitPortletForm(this); return false;">
					<html:hidden property="cmd" />
					<html:hidden property="id" value="<%=id%>"/>
						<script>
								function setCmdType(cmd) {
								    UpdatemaintainForm.cmd.value = cmd;	
									submitPortletForm(UpdatemaintainForm);
								 }
						</script>
     
            <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
          	<td width="5%">&nbsp;
              </td>
            <td width="95%">
             <font class="portlet-msg-error" style="font-size: 11;">
              <html:messages id="a" message="true">
                  <bean:write name="a"/>
              </html:messages>
              </font>
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
               <html:text property="school" styleClass="text_blue_12_c"  value="<%=schoolArea%>"  readonly="true"  size="20"/>  
             </td>
              </td>
                 <td width="30%" valign="top" align=left></td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="apply.people" />: </td>
               <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="applyPeople" styleClass="text_blue_12_c"  value="<%=maintain.getApplyPeople()%>"   readonly="true"  size="20"/>  
             </td>
              </td>
                 <td width="30%" valign="top" align=left></td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="apply.email" />: </td>
               <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="applyPeople" styleClass="text_blue_12_c"  value="<%=maintain.getApplyEmail()%>"   readonly="true"  size="20"/>  
             </td>
              </td>
                 <td width="30%" valign="top" align=left></td>
            </tr>
          </table>
          
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.contactmethod" />: </td>
               <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="contact" styleClass="text_blue_12_c"  value="<%=maintain.getContactMethod()%>"   readonly="true"  size="20"/>  
             </td>
              </td>
                 <td width="30%" valign="top" align=left></td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.accidentDate" />: </td>
               <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="accidentDate" styleClass="text_blue_12_c"  value="<%=maintain.getAccidentDate()%>"  readonly="true"  size="20"/>  
             </td>
              </td>
                 <td width="30%" valign="top" align=left></td>
            </tr>
          </table>
          
       
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.accidentTime" />: </td>
               <td width="60%" valign="baseline" class="text_or_12">
               <html:text property="accidentTime"  styleClass="text_blue_12_c"  value="<%=maintain.getAccidentTime()%>"   readonly="true"  size="20"/>  
             </td>
              </td>
                 <td width="30%" valign="top" align=left></td>
            </tr>
          </table>
          
            
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="apply.info" />: </td>
              <td width="70%" valign="baseline" class="text_or_12">
              <textarea  name="applyInfo" class="text_blue_12_c" cols="57" readonly="true" 
				 rows="10" wrap="soft"><%=maintain.getApplyInfo()%></textarea>
              </td>
              </td>
                 <td width="30%" valign="top" align=left></td>
            </tr>
          </table>
          
            <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="answer.info" />: </td>
              <td width="70%" valign="baseline" class="text_or_12">
              <textarea  name="answerInfo" class="text_or_12" cols="57"
				 rows="5" wrap="soft"  readonly="true"><%=maintain.getAnswerInfo()==null?"":maintain.getAnswerInfo()%></textarea>
              </td>
              </td>
                 <td width="30%" valign="top" align=left></td>
            </tr>
          </table>
          
           <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="15%" valign="center" class="text_or_12"><bean:message key="maintain.applyPeopleAnswer" />: </td>
              <td width="70%" valign="baseline" class="text_or_12">
              <textarea  name="applyPeopleAnswer"  cols="57" class="text_blue_12_c"
				 rows="5" wrap="soft" ><%=maintain.getApplyPeopleAnswer()==null?"":maintain.getApplyPeopleAnswer()%></textarea>
              </td>
              </td>
                 <td width="35%" valign="top" align=left>
                  <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors 		property="applyPeopleAnswer" />	</font><br>
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
              <td align="center">
              	<html:submit styleClass="button_blank" property="save" value='<%= LanguageUtil.get(pageContext, "ecard.save") %>' onclick="javascript:setCmdType('update');" /> 
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

	</script>