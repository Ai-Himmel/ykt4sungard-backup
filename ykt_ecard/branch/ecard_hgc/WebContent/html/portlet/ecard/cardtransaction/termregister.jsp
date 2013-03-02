<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp" %>
<%@ page import="java.util.HashMap"%>
<%@ page import="com.kingstargroup.ecard.hibernate.customer.TCifCustomer"%>
<%@ include file="/html/portlet/ecard/cardtransaction/permission_general_user.jsp" %>
<%

//ResultPage curpage = (ResultPage)request.getAttribute("result");
List list = (List)request.getAttribute("result");
SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
TCifCustomer cust = (TCifCustomer)request.getAttribute("cust");
%>

<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/top_menu.jpg">
        <table width="100%"  border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td width="2%">&nbsp;</td>
            <td width="72%" class="text_blue_12_c"><bean:message key="ecardtransaction.tab.termregisterresult" /></td>
            <td width="11%" valign="bottom">
           </td>
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
          <html:form action="/ecardtransaction/termregister" method="POST"
						onsubmit="javascript:submitPortletForm(this); return false;">
					
					<html:hidden property="userid" />
					
					
         
       <table width="100%" class="inside_table">
      <tr class="list_tr">    
		<td align=center>
			<a class=text_blue_12_c><bean:message key="ecardtransaction.gatehistrade.custname" /></a>
		</td>
		<td align=center>
			<a class=text_blue_12_c><bean:message key="ecardtransaction.tab.termname" /></a>
		</td>
		<td align=center>
			<a class=text_blue_12_c><bean:message key="ecardtransaction.tab.flag" /></a>
		</td>
		<td align=center>
			<a class=text_blue_12_c><bean:message key="ecardtransaction.tab.date" /></a>
		</td>
      </tr>
      <%java.util.Iterator it = list.iterator();
      				int count = 0;
					while(it.hasNext()) {
						HashMap detail = (HashMap)it.next();
						count++;
						int classId = count % 2 + 1;
					%>
	<tr class="tr_<%= classId%>" style="font-size: x-small;">	
	   <td align=center>
			<a class=text_blue_12>
			 <%= (String)cust.getCutName()%>
			</a>
		</td>	
		<td align=center>
			<a class=text_blue_12>
			<%= (String) detail.get("termName")%>
			</a>
		</td>
		<td align=center>
			<a class=text_blue_12>
			<% if("1".equals((String)detail.get("regFlag"))){
			%>
			      <bean:message key="ecardtransaction.tab.confirmcome"/>
			<%  
			   }else if("0".equals((String)detail.get("regFlag"))){
			 %>
			    <bean:message key="ecardtransaction.tab.nocome"/>
			 <%    
			   }
			%>
			</a>
		</td>
		<td align=center>
			<a class=text_blue_12>
			<%= (String)detail.get("txDate")==null?"":(String)detail.get("txDate")%>
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
//	document.GateHisTradeDetailQueryForm.page.value = page;
//	submitPortletForm(document.termRegisterForm);
}
</script>