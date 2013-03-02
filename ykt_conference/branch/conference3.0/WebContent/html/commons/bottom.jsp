<%@ page import="com.kingstargroup.conference.common.ContextUtil" %>
<%@ include file="init.jsp" %>
<style media="print">
.noprint{display:none}
</style>
<table id="bottom" width="100%" height="29" border="0" cellpadding="0" cellspacing="0" class="noprint">
  <tr> 
    <td height="25" align="center" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/bottom_bg.jpg">
    	<font color="#FFFFFF"><bean:message key="system.bottom.tip"/>
    	</font>
    </td>
  </tr>
</table>
