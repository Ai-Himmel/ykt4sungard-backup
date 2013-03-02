<%@ page import="com.kingstargroup.conference.common.ParamUtil" %>
<%@ page import="com.kingstargroup.conference.util.OperatorUtil" %>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TFuncList" %>
<%@ include file="init.jsp" %>
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
</head>
<%
	String parentId = ParamUtil.getString(request, "parentId");
	List childList = OperatorUtil.getUserChildFuncList((String) request.getSession().getAttribute("username"), parentId);
%>
<body  bgcolor="#F7F7F7" leftmargin="0" topmargin="0">
<table width="138" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td align="center" valign="top">&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top"><img src="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/left_menutop.gif" width="138" height="5"></td>
  </tr>
  <tr>
    <td height="30" align="center" valign="middle" class="medium"><strong><%= GetDictionary.getFuncName(parentId)%></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top">
	<%	Iterator iter = childList.iterator();
		while (iter.hasNext()) {
			TFuncList func = (TFuncList)iter.next();
	%>
  <tr> 
    <td align="center" valign="top"><img src="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/left_menu_touming.gif" width="10" height="10"></td>
  </tr>
  <tr> 
    <td align="center" valign="top"><table width="132" height="32" border="0" cellpadding="0" cellspacing="0">
        <tr> 
          <td align="center" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/left_menu.gif" class="medium"><a href="<%= ContextUtil.getCtxPath(request)%><%= func.getFuncUrl()%>" target="dataframe" class="topmenu_link"  onclick="javascript:processtopmenu(this)" ><%= func.getFuncName()%></a>
					<input type=hidden name="hidden_submenus" value="<%= ContextUtil.getCtxPath(request)%><%= func.getFuncUrl()%>">          	
          </td>
        </tr>
      </table></td>
  </tr>
	
	<%}%>
    </td>
   </tr>
  <tr> 
    <td height="32" align="center" valign="top">&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top"><img src="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/left_menutop.gif" width="138" height="5"></td>
  </tr>
</table>
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
			hidden_table.background = '<%= ContextUtil.getCtxPath(request)%>/html/commons/images/left_menu.jpg';
			element.href = hidden_element.value;
			aObj.removeAttribute('className');
			element.className = 'topmenu_link_12';			
		}
		if (element == aObj) {
			hidden_table.background = '<%= ContextUtil.getCtxPath(request)%>/html/commons/images/left_menu.jpg';
			hidden_table.style.cursor = 'default';
		}   
	}
	parent.document.all.dataframe.contentWindow.location = aObj.href;
	aObj.removeAttribute('href');	
 } 
</script>