<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp" %>

<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0" class="box">
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
<table width="719"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="9" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_1.jpg" width="9" height="7"></td>
          <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_top.jpg"></td>
          <td width="6" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_1.jpg" width="6" height="7"></td>
        </tr>
        <tr>
          <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_2.jpg">&nbsp;</td>
          <td valign="top" bgcolor="#FFFFFF">
      <table width="100%" class="inside_table">
      <tr class="list_tr">    
          <td align=center><bean:message key="numberNo"/>
          <td align=center><bean:message key="yearName" /></td>
          <td align=center><bean:message key="termNo" /></td>
          <td align=center><bean:message key="courseName" /></td>
          <td align=center><bean:message key="score" /></td>
       </tr>
       <logic:present name="studentScore">
        <logic:notEmpty name="studentScore">
          <%int i=0;%>
          <logic:iterate  name="studentScore" id="score" indexId="No">
                 <%
                    i++;
                    int classId = i % 2 + 1;
                 %>
             	<tr class="tr_<%= classId%>" style="font-size: x-small;">		
                  <td align=center width=10><bean:write name="No"/></td>
                  <td align=center width=30%><bean:write name="score"  property="firstYear"/>
                   --<bean:write name="score"  property="endYear"/></td>
                   <td align=center width=10%><bean:write name="score" property="termNo"/></td>
                   <td align=center width=40% ><bean:write name="score" property="courseName"/></td>
                   <td align=center width=10% > <bean:write name="score" property="totalScoreName"/></td>
                </tr>
          </logic:iterate>
         </logic:notEmpty>
         <logic:empty  name="studentScore">
            <bean:message key="no.student.score"/>
         </logic:empty>  
         </logic:present>
</table>
 </td>
       <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_2.jpg">&nbsp;</td>
        </tr>
        <tr>
          <td width="9" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_l_3.jpg" width="9" height="7"></td>
          <td height="7" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_foot.jpg"></td>
          <td width="6" height="7"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/portlet/k_r_3.jpg" width="6" height="7"></td>
        </tr>
      </table>