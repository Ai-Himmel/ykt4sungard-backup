
<%@ include file="/html/extportlet/ecard/cardtransaction/init.jsp"%>
<%@ include file="/html/extportlet/ecard/cardtransaction/permission.jsp" %>
<%
String id= request.getParameter("id");
EcardPostponeApply apply = PostponeUtil.getPostpone(id);
SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td background="/html/extthemes/classic/images/ecard/top_menu.jpg"><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardtransaction.tab.editcardpostpone" /></td>
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
        <td width="9" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_l_1.jpg" width="9" height="7"></td>
        <td height="7" background="/html/extthemes/classic/images/ecard/portlet/k_top.jpg"></td>
        <td width="6" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_r_1.jpg" width="6" height="7"></td>
      </tr>
      <tr>
        <td background="/html/extthemes/classic/images/ecard/portlet/k_l_2.jpg">&nbsp;</td>
        <td valign="top" align=center bgcolor="#FFFFFF">
        <!-- content table -->
			<html:form action="/ext/ecardtransactionedit_postpone_result" method="POST" enctype="multipart/form-data"
				onsubmit="javascript:submitPortletForm(this); return false;">
				<html:hidden property="id" value="<%= id%>" />
        
        <table width="100%" class="tdclass" border="0" cellspacing="0" cellpadding="0">
        	
          <tr>            
            <td width="10%" valign="baseline" class="text_or_12"><bean:message key="ecardtransaction.cardpostpone.reason" />: 
              </td>
            <td width="60%" valign="baseline" class="text_blue_12">
            <%= apply.getReason()%></td>
            <td width="27%" align=left></td>
          </tr>
          
          <tr>            
            <td width="10%" valign="baseline" class="text_or_12"><bean:message key="ecardtransaction.cardpostpone.date" />: 
              </td>
            <td width="60%" valign="baseline" class="text_blue_12">
            <%= DateFormatUtil.format(apply.getPostponeTime())%></td>
            <td width="27%" align=left></td>
          </tr>
          
           <tr>            
            <td width="10%" valign="baseline" class="text_or_12"><bean:message key="ecardtransaction.cardpostpone.applytime" />: 
              </td>
            <td width="60%" valign="baseline" class="text_blue_12">
            <%= format.format(apply.getApplyTime())%></td>
            <td width="27%" align=left></td>
          </tr>
          
          <tr>            
            <td width="10%" valign="top" class="text_or_12"><bean:message key="ecardtransaction.cardpostpone.checkResult" />: 
              </td>
            <td width="50%" valign="baseline" class="text_or_12">
            <html:textarea property="checkResult" cols="40" rows="10" /></td>
            <td width="40%" valign=top align=left>
            <font class="portlet-msg-error" style="font-size: 11;"><html:errors
							property="checkResult" /></font>
            </td>
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
          <table width="55%" height="35"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td align="right">
        <html:submit styleClass="button_blank" property="save" value='<%= LanguageUtil.get(pageContext, "ecard.save") %>' /> 
				<html:reset property="reset" styleClass="button_blank"	value='<%= LanguageUtil.get(pageContext, "ecard.reset") %>' />
				</td>
            </tr>
          </table>
          </html:form>
          <!-- content table --></td>
        <td background="/html/extthemes/classicimages/ecard/portlet/k_r_2.jpg">&nbsp;</td>
      </tr>
      <tr>
        <td width="9" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_l_3.jpg" width="9" height="7"></td>
        <td height="7" background="/html/extthemes/classic/images/ecard/portlet/k_foot.jpg"></td>
        <td width="6" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_r_3.jpg" width="6" height="7"></td>
      </tr>
    </table>