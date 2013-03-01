<%@ include file="/commons/init.jsp" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.UserUtil" %>
<%@ page import="com.kingstargroup.advquery.hibernate.user.TLeadqueryOperator" %>
<%@ page import="com.kingstargroup.advquery.util.StringUtil" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/js/util.js"></script>
</head>
<table width="100%" height="5" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td></td>
  </tr>
</table>
<table>
<tr>
<td width=5%>&nbsp;</td>
<td>


  <form name=UserDelForm action="<%= ContextUtil.getCtxPath(request)%>/usermanage/delete.do" method="POST">
          <table border="0" cellpadding="0" align=center cellspacing="0" width="92%"> 		   
		<c:if test='<%= SessionErrors.contains(request, "eadvquery.error.createusersuccess") %>'>		
		<tr>
			<td>				
					<font class="portlet-msg-success" style="font-size: 11;">
					<bean:message key="eadvquery.error.createusersuccess" />
					</font>
			</td>
		</tr>
		</c:if>
		<c:if test='<%= SessionErrors.contains(request, "eadvquery.error.editusersuccess") %>'>		
		<tr>
			<td>				
					<font class="portlet-msg-success" style="font-size: 11;">
					<bean:message key="eadvquery.error.editusersuccess" />
					</font>
			</td>
		</tr>
		</c:if> 
       <c:if test='<%= SessionErrors.contains(request, "eadvquery.error.choosedeleteusers") %>'>		
		<tr>
			<td>				
					<font class="portlet-msg-error" style="font-size: 11;">
					<bean:message key="eadvquery.error.choosedeleteusers" />
					</font>
			</td>
		</tr>
		</c:if>   
       <c:if test='<%= SessionErrors.contains(request, "eadvquery.error.deleteusersucceed") %>'>		
		<tr>
			<td>				
					<font class="portlet-msg-success" style="font-size: 11;">
					<bean:message key="eadvquery.error.deleteusersucceed" />
					</font>
			</td>
		</tr>
		</c:if> 		
		<c:if test='<%= SessionErrors.contains(request, "eadvquery.error.deleteuserfailed") %>'>		
		<tr>
			<td>				
					<font class="portlet-msg-error" style="font-size: 11;">
					<bean:message key="eadvquery.error.deleteuserfailed" />
					</font>
			</td>
		</tr>
		</c:if>
		<c:if test='<%= SessionErrors.contains(request, "eadvquery.error.restusersucceed") %>'>		
		<tr>
			<td>				
					<font class="portlet-msg-success" style="font-size: 11;">
					<bean:message key="eadvquery.error.restusersucceed" />
					</font>
			</td>
		</tr>
		</c:if>
		<c:if test='<%= SessionErrors.contains(request, "eadvquery.error.chooserestusers") %>'>		
		<tr>
			<td>				
					<font class="portlet-msg-error" style="font-size: 11;">
					<bean:message key="eadvquery.error.chooserestusers" />
					</font>
			</td>
		</tr>
		</c:if>
		<c:if test='<%= SessionErrors.contains(request, "eadvquery.error.restuserfailed") %>'>		
		<tr>
			<td>				
					<font class="portlet-msg-error" style="font-size: 11;">
					<bean:message key="eadvquery.error.restuserfailed" />
					</font>
			</td>
		</tr>
		</c:if>
		</table>
		<table width="96%" height="40" border="0" cellpadding="0" cellspacing="0">
		  <tr>
		    <td height="15">
			&nbsp;	
					<button onclick="javascript:renderAddPage();"><bean:message key="eadvquery.add" /></button>
					&nbsp;
					<button onclick="if (confirm('<bean:message key="eadvquery.delete.confirm" />')) {  document.UserDelForm.submit();}">
						<bean:message key="eadvquery.delete" />
					</button>						
					&nbsp;
					<button onclick="if (confirm('<bean:message key="eadvquery.reset.confirm" />')) {  document.UserDelForm.action='<%= ContextUtil.getCtxPath(request)%>/usermanage/resetpwd.do';document.UserDelForm.submit();}">
						<bean:message key="eadvquery.resetpwd" />
					</button>
			</td>
		  </tr>
		</table>
		
		<table border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td><table width="763" border="0" align="center" cellpadding="0" cellspacing="0" class="data">
        <tr>
          <td width="23" height="21" class="title"><input name="ids_allbox" type="checkbox"
				onClick="
					for (var i = 0; i < UserDelForm.elements.length; i++) {
						var e = document.UserDelForm.elements[i];

						if ((e.name == 'ids') && (e.type == 'checkbox')) {
							e.checked = this.checked;
						}
					}"
			></td>
          <td align=center width="400" class="title"><bean:message key="eadvquery.userid" /></td>
          <td align=center width="300" class="title"><bean:message key="eadvquery.username" /></td>
          <td align=center width="200" class="title"><bean:message key="eadvquery.isshopowner" /></td>
        </tr>
              <% List  result = (List)request.getAttribute("result");
                 java.util.Iterator it = result.iterator();      				
					while(it.hasNext()) {
						TLeadqueryOperator user = (TLeadqueryOperator) it.next();
					%>
        <tr>
          <td class="data"><span class="title">
            
			<input type="checkbox" name="ids" value="<%= user.getOperCode()%>" 
						onClick="javascript:checkAllBox(document.UserDelForm, 'ids', document.UserDelForm.ids_allbox)" />
          </span></td>
          <td align=center class="data"><a class=link_12_line href="<%= ContextUtil.getCtxPath(request)%>/usermanage/edit.do?userid=<%= user.getOperCode()%>">
			<%= user.getOperCode()%>
			</a></td>
          <td align=center class="data">
			<%= user.getOperName()%>
			</td>
          <td align=center class="data">
			<%= StringUtil.ifShopOwner(user.getIsShopOwner())%>
			</td>
        </tr>
        <%}%>   

	</table></td>
  </tr>
</table>
</td>
	</tr>
		</table>
</form>
<script>
function renderAddPage() {
	self.location = '<%= ContextUtil.getCtxPath(request)%>/usermanage/add.do';
}
</script>