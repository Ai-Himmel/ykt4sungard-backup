<%@ include file="/commons/init.jsp" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.UserUtil" %>
<%@ page import="com.kingstargroup.advquery.hibernate.user.TLeadqueryFunclist" %>
<%
	List parentList = UserUtil.getUserParentFuncList((String) request.getSession().getAttribute("username"));
%>
<table width="1000" height="75" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td height="70" align="left" valign="top" background="<%= ContextUtil.getCtxPath(request)%>/commons/images/logo.jpg">
    	<table width="100%" height="70" border="0" cellpadding="0" cellspacing="0">
        <tr> 
          <td width="22%">&nbsp;</td>
          <td align="left" valign="top"><table width="100%" height="70" border="0" cellpadding="0" cellspacing="0">
              <tr> 
                <td height="32" align="left" valign="bottom"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                    <tr> 
                      <td align="left" valign="bottom"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/top.jpg" width="198" height="17" /> 
                      </td>
                      <td width="18%"><a href="<%= ContextUtil.getCtxPath(request)%>/usermanage/changepwd.do" target="dataframe" class="topmenu_link"><bean:message
							key="system.edidpwd" /></a> 
                        | <a href="<%= ContextUtil.getCtxPath(request)%>/usermanage/logout.do" target="_parent" class="topmenu_link"><bean:message key="system.unreg" /></a></td>
                    </tr>
                  </table></td>
              </tr>
              <tr> 
                <td align="center" valign="middle"> 
                  <table width="98%" border="0" cellpadding="0" cellspacing="0">
                    <tr> 
					<%for (int i = 0; i < parentList.size(); i++) {
						TLeadqueryFunclist func = (TLeadqueryFunclist) parentList.get(i);%>						
						<td width="18" align="center" valign="middle"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/topmenu.jpg" width="15"
							height="15" /></td>						
						<td nowrap="nowrap">
							<a name="topmenus" class=topmenu_link 
							href="<%= ContextUtil.getCtxPath(request)%>/usermanage/rendersubnav.do?parentId=<%= func.getFuncCode()%>" target="subnavframe" 
							onclick="javascript:processtopmenu(this)">
							<%= func.getFuncName()%></a>
							<input type=hidden name="hidden_topmenus" value="<%= ContextUtil.getCtxPath(request)%>/usermanage/rendersubnav.do?parentId=<%= func.getFuncCode()%>">
						</td>						
					<%}%>
                    </tr>
                  </table>
                </td>
              </tr>
            </table></td>
        </tr>
      </table></td>
  </tr>
  <tr> 
    <td height="4" align="left" valign="top" bgcolor="#39619E"></td>
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
