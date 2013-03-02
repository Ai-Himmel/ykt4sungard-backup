<%@ include file="/html/portlet/ecard/maintain/init.jsp"%>
<%@ page import="com.kingstargroup.ecard.hibernate.util.MaintainUtil"%>
<%@ page import="com.kingstargroup.ecard.hibernate.util.WebDictionaryUtil"%>
<%@ page import="com.kingstargroup.ecard.hibernate.web.WebDictionary"%>
<% //List     list  = WebDictionaryUtil.getDictionaryByDicNo("008");%>
<% 
   List     list = (List)request.getAttribute("list");
   String  service = request.getAttribute("service")==null?"":(String)request.getAttribute("service");
   String  sendEmail  = request.getAttribute("sendEmail")==null?"":(String)request.getAttribute("sendEmail");
   String  username = request.getAttribute("username")==null?"":(String)request.getAttribute("username");
   String  password = request.getAttribute("password")==null?"":(String)request.getAttribute("password");
   //String  password = request.getAttribute("password")==null?"":(String)request.getAttribute("password");
   String  title = request.getAttribute("title")==null?"":(String)request.getAttribute("title");
   String  secondtimes = request.getAttribute("secondtimes")==null?"":(String)request.getAttribute("secondtimes");
   String  beginDate = request.getAttribute("beginDate")==null?"":(String)request.getAttribute("beginDate");
   String  emailReport =request.getAttribute("emailReport")==null?"":(String)request.getAttribute("emailReport");
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="maintain.email.manage" /></td>
          <td width="11%" valign="bottom">&nbsp;</td>
          <td width="15%" align="right" valign="middle" nowrap class="text_brown">&nbsp;</td>
        </tr>
      </table></td>
    </tr>
  </table>
    <table width="100"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="5">
         <font class="portlet-msg-error" style="font-size: 11;">
         <html:messages id="info" name="show">
          <bean:write name="info"/>
         </html:messages>
         </font>
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
        <html:form action="/maintain/editemail" method="POST"
					onsubmit="submitPortletForm(this); return false;">
		<INPUT type='hidden'  name='detailCount' value=1>
		<input type="hidden" name="cmd" />
		  <script>
				function setCmdType(cmd) {
				  editEmailForm.cmd.value = cmd;	
				  
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
              <td width="10%" valign="center" class="text_or_12"><bean:message key="maintain.email.service" />: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 
                 <html:text  property="service"  size="30" value="<%=service%>"/>
              </td>
                 <td width="35%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="service" /></font>
			  </td>
            </tr>
          </table>
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="10%" valign="center" class="text_or_12"><bean:message key="maintain.email.sendaddress" />: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 <html:text  property="sendemail"  size="30"  value="<%=sendEmail%>"/>
              </td>
                 <td width="35%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="sendemail" /></font>
			  </td>
            </tr>
          </table>
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="10%" valign="center" class="text_or_12"><bean:message key="maintain.smtp.user" />: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 <html:text  property="username"  size="30"  value="<%=username%>"/>
              </td>
                 <td width="35%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="username" /></font>
			  </td>
            </tr>
          </table>
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="10%" valign="center" class="text_or_12"><bean:message key="maintain.smtp.pwd" />: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 <html:password  property="password"  size="30" value="<%=password%>"/>
              </td>
                 <td width="35%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="password" /></font>
			  </td>
            </tr>
          </table>
           <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="10%" valign="center" class="text_or_12"><bean:message key="maintain.email.title" />: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 <html:text  property="title"  size="30"   value="<%=title%>" />
              </td>
                 <td width="35%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="title" /></font>
			  </td>
            </tr>
          </table>
          
       
           <table id='addTb' width="100%"  border="0" cellspacing="0" cellpadding="0">
              <%
              
             if(list != null && !list.isEmpty()){
               for(int i=0;i<list.size();i++){   
               %>
            <tr>
              <td width="10%" valign="center" class="text_or_12"><bean:message key="maintain.email.receiveaddress" />: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 <html:text  property="receiveemail"  size="30" value="<%=((WebDictionary)list.get(i)).getDicCaption()%>" />
              </td>
                 <td width="35%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="receiveemail" /></font>
			  </td>
            </tr>
            <%}
            }else{%>
            <tr>
              <td width="10%" valign="center" class="text_or_12"><bean:message key="maintain.email.receiveaddress" />: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 <html:text  property="receiveemail"  size="30" value="" />
              </td>
                 <td width="35%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="receiveemail" /></font>
			  </td>
            </tr>
            <%  
             }
            
            %>
          </table>
          
         <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="10%" valign="center" class="text_or_12"><bean:message key="email.report" />: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                <html:select   property="emailReport" value="<%=emailReport%>" >
                     <html:option value="" ></html:option>
                     <html:option value="0"><bean:message key="email.no"/></html:option>
                     <html:option value="1"><bean:message key="email.yes"/></html:option>
                </html:select>
              </td>
                 <td width="35%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="emailReport" /></font>
			  </td>
            </tr>
          </table>
          
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="10%" valign="center" class="text_or_12"><bean:message key="email.beginDate" />: </td>
              <td width="30%" valign="baseline" class="text_or_12">
               <html:text property="beginDate"  value="<%=beginDate%>" readonly="true"  size="20"/>  <a href="#"><img
						src="<%=themeDisplay.getPathThemeRoot()%>/images/ecard/portlet/clock.gif"
							width="21" height="21" border="0" id="f_trigger_accidentDate">
						</a> 
             </td>
              </td>
                 <td width="35%" valign="top" align=left>
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors 		property="beginDate" />	</font><br>	</td>
            </tr>
          </table>
          
          
           <table width="100%"  border="0" cellspacing="0" cellpadding="0">
            <tr>
              <td width="10%" valign="center" class="text_or_12"><bean:message key="email.days" />: </td>
              <td width="30%" valign="baseline" class="text_or_12">
                 <html:text  property="secondtimes" value="<%=secondtimes%>"  size="5"  />
              </td>
                 <td width="35%" valign="top" align=left><font class="portlet-msg-error" style="font-size: 11;">
                 <font class="portlet-msg-error" style="font-size: 11;">
                 <html:errors   property="secondtimes" /></font>
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
				<html:button  property="saveandnext" styleClass="button_blank" value='<%= LanguageUtil.get(pageContext, "maintain.email.add") %>' onclick="javascript:addRecord();" />
				<html:button  property="saveandnext" styleClass="button_blank" value='<%= LanguageUtil.get(pageContext, "maintain.email.delete") %>' onclick="javascript:delRecord();" />
				<html:reset   property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>'  />
				<!--<html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>' onclick="javascript:renderAdminPage();" />
				--></td>
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
    <script language="javascript">
    function addRecord(){
     		var newTR;
     		var newTD;
     		var tempAddnum=document.all.editEmailForm.detailCount.value;
     		newTR=document.all.addTb.insertRow(document.all.addTb.rows.length);
     		newTR.bgColor="#FFFFFF";
     		newTD=newTR.insertCell();
     		newTD.innerHTML="<td width='15%' valign='center' class='text_or_12'><bean:message key='maintain.email.receiveaddress' /></td>";
     		newTD=newTR.insertCell();
     		newTD.innerHTML="<input  size=30 name=receiveemail >";
     		tempAddnum++;
		    document.all.editEmailForm.detailCount.value=tempAddnum;
		    }
     function delRecord(){
        	if (document.all.addTb.rows.length >1 ) delTR = document.all.addTb.deleteRow(document.all.addTb.rows.length-1);
        }
      Calendar.setup({
        inputField     :    "beginDate",     // id of the input field
        weekNumbers		:	false,
    	ifFormat	   :	"%Y/%m/%d",
        button         :    "f_trigger_accidentDate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    </script> 		
