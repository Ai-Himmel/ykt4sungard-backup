<%@ include file="/commons/init.jsp" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.UserUtil" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.FuncListUtil" %>
<%@ page import="com.kingstargroup.advquery.hibernate.user.TLeadqueryFunclist" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>
<%
	String parentId = ParamUtil.getString(request, "parentId");
	List childList = UserUtil.getUserChildFuncList((String) request.getSession().getAttribute("username"), parentId);
%>
<body bgcolor="#F6F6F6">
<table width="197" border="0" cellspacing="0" cellpadding="0" >
        <tr> 
          <td height="35" bgcolor="#F6F6F6"><table width="150" height="22" border="0" align="center" cellpadding="0" cellspacing="0">
              <tr> 
                <td width="148" align="center" valign="bottom" bgcolor="#F6F6F6" class="topmenu_on">
				<%= FuncListUtil.getFuncName(parentId)%>
				</td>
              </tr>
            </table></td>
        </tr>
      </table>
      <table width="100%" height="1" border="0" cellpadding="0" cellspacing="0" bgcolor="#FFFFFF">
        <tr> 
          <td></td>
        </tr>
      </table>
      <table width="197" height="1" border="0" cellpadding="0" cellspacing="0" bgcolor="#dadbd5">
        <tr> 
          <td></td>
        </tr>
      </table>
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr> 
          <td>&nbsp;</td>
        </tr>
      </table>
      
      <%for (int i = 0; i < childList.size(); i++) {
      	TLeadqueryFunclist func = (TLeadqueryFunclist) childList.get(i);%>
      <table width="197" border="0" cellspacing="0" cellpadding="0">
      <tr>
      	<td width="7">&nbsp;</td>
      	<td width=172>
	      <table id="table_submenus<%=i%>" align=center background="<%= ContextUtil.getCtxPath(request)%>/commons/images/menu.jpg" width="182" height="31" border="0" align=center cellpadding="0" cellspacing="0"  style="cursor:hand" onclick="">
	        <tr> 	          
	          <td width="172" align=center>
	          <a name="submenus" 
	          href="<%= ContextUtil.getCtxPath(request)%><%= func.getFuncUrl()%>" target="dataframe" 
	          class="topmenu_link_12" onclick="javascript:processtopmenu(this)">
				<%= func.getFuncName()%>
				</a>
				<input type=hidden name="hidden_submenus" value="<%= ContextUtil.getCtxPath(request)%><%= func.getFuncUrl()%>">
				</td>
	        </tr>
	      </table>
      	</td>
      </tr>
      </table>
      <table width="100%" height="9" border="0" cellpadding="0" cellspacing="0">
        <tr> 
          <td></td>
        </tr>
      </table>
      <%}%>
</body>

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
		var hidden_table = document.getElementById("table_" + aObj.name + i);
		//alert(element.href);
		if (element.href == '') {
			hidden_table.background = '<%= ContextUtil.getCtxPath(request)%>/commons/images/menu.jpg';
			element.href = hidden_element.value;
			aObj.removeAttribute('className');
			element.className = 'topmenu_link_12';			
		}
		if (element == aObj) {
			hidden_table.background = '<%= ContextUtil.getCtxPath(request)%>/commons/images/menu_on.jpg';
			hidden_table.style.cursor = 'default';
		}   
	}
	parent.document.all.dataframe.contentWindow.location = aObj.href;
	aObj.removeAttribute('href');	
 } 
</script>