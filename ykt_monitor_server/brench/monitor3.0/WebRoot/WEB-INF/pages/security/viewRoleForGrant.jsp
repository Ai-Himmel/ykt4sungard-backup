<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<bean:define id="title">
	<bean:message bundle="security" key="security.roleMenu" />
</bean:define>
<bean:define id="roleTitle">
	<bean:message bundle="security" key="role.list" />
</bean:define>
<center>
	<gui:window title="<%=title%>" prototype="boWindow" color="100%">
		<gui:tabbedPanel prototype="boTabbedPanel" followUp="listAccount.do" color="#f0f0f0" selectedTab="tab1" width="52">
			<gui:tab prototype="boTab" name="tab1" title="<%=roleTitle%>" followUp="listGroup.do?method=listRole">
				<html:form action="menuSecurityManager.do?method=loadRoleMenu4Grant" onsubmit="return onSubmit(this);">
					<html:errors />
					<table class="sort-table" cellSpacing="1" cellPadding="1" width="100%" border="0">
						<thead>
							<tr>
								<td colspan="5">
									<bean:message bundle="security" key="role.list" />
								</td>
							</tr>
						</thead>
						<tr>
							<logic:iterate name="roles" id="role" indexId="index">
								<c:if test="${index%5==0}">
						</tr>
						<tr>
						<td>
									<input type="checkbox" name="id" value="<bean:write  name="role" property="id" />" onclick="radio(this)">
									<a href="menuSecurityManager.do?method=loadRoleMenu4Grant&id=<bean:write  name="role" property="id" />"><bean:write name="role" property="name" /></a>
								</td>
							</c:if>
							<c:if test="${index%5!=0}">
								<td>
									<input type="checkbox" name="id" value="<bean:write  name="role" property="id" />" onclick="radio(this)">
									<a href="menuSecurityManager.do?method=loadRoleMenu4Grant&id=<bean:write  name="role" property="id" />"><bean:write name="role" property="name" /></a>
								</td>
							</c:if>
							</logic:iterate>
						</tr>

						<tr>
							<td align="right" colspan="5">
								<html:submit styleClass="button">
									<bean:message key="button.view" />
								</html:submit>

								<html:reset styleClass="button">
									<bean:message key="button.reset" />
								</html:reset>
							</td>
						</tr>
						</html:form>
					</table>
			</gui:tab>

		</gui:tabbedPanel>
	</gui:window>
</center>
<script type="text/javascript">
<!--

<!-- This method is used to check save or delete button clicked and submit the form -->
function onSubmit(theForm) {
		//submit the form
		var isSelected = 0;
		 for(i=0;i<theForm.id.length;i++){
         if(theForm.id[i].checked==true){
              isSelected = 1; 
         }
	  }
	  if(isSelected==0){
	     alert("请选择角色！");
	     return false;
	  }
	  
      return true;
}

function radio(clicked){
   		var isSelected = 0;
		 for(i=0;i<document.forms[0].id.length;i++){
         if(document.forms[0].id[i].checked==true){
              isSelected += 1; 
         }
	  }
	  if(isSelected>1){
	    alert("对不起，只能选择一个角色");
	    clicked.checked=false;
	  return false;
	  
	  }
      return true;
}

// -->
</script>
