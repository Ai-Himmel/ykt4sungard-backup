<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp" %>
<%@ include file="/html/portlet/ecard/cardtransaction/permission_general_user.jsp" %>
<%
ResultPage curpage = (ResultPage) request.getAttribute("result");
List list = curpage.getList();
String resultsize = (String)request.getAttribute("resultsize");
%>

<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg">
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="2%">&nbsp;</td>
            <td width="72%" class="text_blue_12_c"><bean:message key="ecard.handtraderesult" />&nbsp; <bean:message key="ecard.gong" /><%=resultsize %><bean:message key="ecard.liushui" /></td>
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
                <%= curpage.getPage() + 1%>/<%= curpage.getTotalPage()%>
                </td>
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
          <html:form action="/ecardtransaction/queryhandtrade_result" method="POST"
						onsubmit="javascript:submitPortletForm(this); return false;">
					<html:hidden property="beginDate" />
					<html:hidden property="endDate" />
					<html:hidden property="page" />
					
         
       <table width="100%" class="inside_table">
      <tr class="list_tr">    
		<td align=center>
			<a class=text_blue_12_c><bean:message key="ecardtransaction.gatehistrade.custid" /></a>
		</td>
		<td align=center>
			<a class=text_blue_12_c><bean:message key="ecardtransaction.gatehistrade.custname" /></a>
		</td>
		<td align=center>
			<a class=text_blue_12_c><bean:message key="ecardtransaction.gatehistrade.stuempno" /></a>
		</td>
		<td align=center>
			<a class=text_blue_12_c><bean:message key="ecardtransaction.gatehistrade.attdate" /></a>
		</td>
		<td align=center>
			<a class=text_blue_12_c><bean:message key="ecardtransaction.gatehistrade.attnum" /></a>
		</td>
      </tr>
      <%java.util.Iterator it = list.iterator();
      				int count = 0;
					while(it.hasNext()) {
						HashMap detail = (HashMap) it.next();
						count++;
						int classId = count % 2 + 1;
					%>
	<tr class="tr_<%= classId%>" style="font-size: x-small;">		
		<td align=center>
			<a class=text_blue_12>
			<%= (Integer) detail.get("custId")%>
			</a>
		</td>
		<td align=center>
			<a class=text_blue_12>
			<%= (String) detail.get("cutName")%>
			</a>
		</td>
		<td align=center>
			<a class=text_blue_12>
			<%= (String) detail.get("stuempNo")%>
			</a>
		</td>
		<td align=center>
			<a class=text_blue_12>
			<%= (String) detail.get("attDate")%>
			</a>
		</td>
		<td align=center>
			<a class=text_blue_12>
			<%= (Integer) detail.get("attnum")%>
			</a>
		</td>
	</tr>
	<%}%>

	</table>
</html:form>
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
function goto(page) {
	document.HandTradeQueryForm.page.value = page;
	submitPortletForm(document.HandTradeQueryForm);
}
</script>