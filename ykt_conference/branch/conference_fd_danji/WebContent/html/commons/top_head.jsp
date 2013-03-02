<%@ page import="com.kingstargroup.conference.util.OperatorUtil" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TFuncList" %>
<%@ include file="init.jsp" %>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
<style media="print">
.noprint{display:none}
</style>
<%
	List parentList = OperatorUtil.getUserParentFuncList((String) request.getSession().getAttribute("username"));
%>
<table id="top" width="100%" height="88" border="0" cellpadding="0" cellspacing="0" class="noprint">
  <tr> 
    <td height="88" align="left" valign="top" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/top_bg1.jpg">
	<table width="997" height="88" border="0" cellpadding="0" cellspacing="0" 
			background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/top_bg.jpg" >
		<tr>
          <td height="50">&nbsp;</td>
        </tr>
        <tr>
          <td>
          	<table width="100%" border="0" cellspacing="0" cellpadding="0">
              <tr> 
                <td width="19%">&nbsp;</td>
              	<%	Iterator iter = parentList.iterator();
              		while (iter.hasNext()){
              			TFuncList func = (TFuncList)iter.next();
              	%>
                <td class="medium">
                	<a href="<%= ContextUtil.getCtxPath(request)%>/rendersubnav.do?parentId=<%= func.getFuncCode()%>" target="subnavframe" class="topmenu_link"
                	onclick="javascript:processtopmenu(this)"><%= func.getFuncName()%></a>&nbsp;|
                	<input type=hidden name="hidden_topmenus" value="<%= ContextUtil.getCtxPath(request)%>/rendersubnav.do?parentId=<%= func.getFuncCode()%>">
                </td>
                <%}%>
                <td>&nbsp;</td>
                <td width="18%" align="center" valign="middle" class="medium"><a href="<%= ContextUtil.getCtxPath(request)%>/user/modifypwd.do" target="dataframe" class="topmenu_link_2"><bean:message key="system.top.edtpwd"/></a> 
                  <font color="#634D21">|</font> <a href="<%= ContextUtil.getCtxPath(request)%>/logout.do" target="_parent" class="topmenu_link_2"><bean:message key="system.top.logout"/></a></td>
              </tr>
            </table>
          </td>
		</tr>
	</table>
    </td>
  </tr>
</table>

<script>
	function processtopmenu(aObj) {
	if (aObj.href == '') {
		return;
	}
	var topmenus = document.getElementsByName(aObj.name);
	var hidden_topmenus = document.getElementsByName("hidden_" + aObj.name);
	for (var i = 0; i < topmenus.length; i++) {
		var element = topmenus.item(i);
		var hidden_element = hidden_topmenus.item(i);
		if (element.href == '') {
			element.href = hidden_element.value;
			aObj.removeAttribute('className');
			element.className = 'topmenu_link';			
			break;
		}   
	}
	aObj.className = 'topmenu_on';
	document.all.subnavframe.contentWindow.location = aObj.href;
	aObj.removeAttribute('href');	
 } 
</script>
