<% // reference gatehisquerydetail_max.jsp %>
<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp"%>
<%@ include file="/html/portlet/ecard/cardtransaction/permission_general_user.jsp"%>
<%
  Integer beginDate =(Integer)request.getAttribute("beginDate");//current year
  Integer endDate =(Integer)request.getAttribute("endDate");  //next year
  
%> 
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardtransaction.tab.studentscore" /></td>
          <td width="11%" valign="bottom">&nbsp;</td>
          <td width="15%" align="right" valign="middle" nowrap class="text_brown">&nbsp;</td>
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
       <html:form action="/ecardtransaction/studentscore_result" 
				method="POST" onsubmit="javascript:submitPortletForm(this);return false;">
        <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td></td>
          </tr>
        </table>
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
        	
        
          <tr>
            <td width="3%"></td>
            <td width="12%" valign="baseline" class="text_or_12"><bean:message key="ecardtransaction.selectyear" />: 
              </td>
            <td width="45%" valign="baseline" class="text_or_12"> 
            	<html:select  property="studentYear" >
            	 <logic:notEmpty  name="yearList">
            	       <html:options  collection="yearList" property="value" labelProperty="label"/>
            	 </logic:notEmpty>
            	</html:select>       
            	<font class="portlet-msg-error" style="font-size: 11;">
							<logic:empty name="yearList"> 
							<bean:message key="ecardtransaction.jw.noscore" />
							</logic:empty>
							</font>    				
            </td>
           
          <tr>
            <td width="3%"></td>
            <td width="12%" valign="baseline" class="text_or_12"><bean:message key="ecardtransaction.selectterm" />: 
              </td>
            <td width="45%" valign="baseline" class="text_or_12"> 
            	<html:select property="termNo">
            		<html:option value="1">
            		<bean:message key="ecardtransaction.oneterm" />
            		</html:option>
            		<html:option value="2">
            		<bean:message key="ecardtransaction.secondterm" />
            		</html:option>
            		
            	</html:select>           				
            </td>
            <td width="30%" align=center><font class="portlet-msg-error" style="font-size: 11;">
							
							</font></td>
          </tr>
          
          <tr>
            <td width="3%"></td>
            <td width="12%" valign="baseline" class="text_or_12">&nbsp;
              </td>
            <td width="45%" valign="baseline" class="text_or_12"> 
            	&nbsp;       				
            </td>
            <td width="40%" align=left><font class="portlet-msg-error" style="font-size: 11;">&nbsp;
							</font></td>
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
          <table width="99%" height="35"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td align="center">
              	<html:submit styleClass="button_blank" value='<%= LanguageUtil.get(pageContext, "ecard.query") %>'  />
				<html:reset property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>' />
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
