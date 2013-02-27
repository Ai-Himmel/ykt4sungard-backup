<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<bean:define id="title">
	<bean:message bundle="security" key="security.title" />
</bean:define>
<bean:define id="accountTitle">
	<bean:message bundle="security" key="security.account" />
</bean:define>
<bean:define id="roleTitle">
	<bean:message bundle="security" key="security.role" />
</bean:define>
<bean:define id="resourceTitle">
	<bean:message bundle="security" key="security.resource" />
</bean:define>
<center>
	<gui:window title="<%=title%>" prototype="boWindow" color="100%">
		<gui:tabbedPanel prototype="boTabbedPanel" followUp="listAccount.do" color="#f0f0f0" selectedTab="tab2" width="52">
			<gui:tab prototype="boTab" name="tab1" title="<%=accountTitle%>" followUp="accountSecurityManager.do?method=searchAccount">
	account manager
   </gui:tab>

			<gui:tab prototype="boTab" name="tab2" title="<%=roleTitle%>" followUp="roleManager.do?method=loadRole">
				<html:form action="editRole?method=updateRole" onsubmit="return validateRoleForm(this);">
					<html:errors />
					<table class="sort-table" cellSpacing="1" cellPadding="1" width="100%" border="0">
						<thead>
							<tr>
								<td colspan="2">
									<bean:message bundle="security" key="role.create" />
								</td>
							</tr>
						</thead>

						<tr>
							<td>
								<bean:message bundle="security" key="role.name" />
							</td>
							<td>
								<html:text property="role.name" size="20" maxlength="64" />
							</td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="role.desc" />
							</td>
							<td>
								<html:text property="role.remark" size="20" />
							</td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="role.type" />
							</td>
							<td>
								<html:select property="role.type">
									<html:option value="0">系统角色</html:option>
									<html:option value="1">一般角色</html:option>
								</html:select>
							</td>
						</tr>
						<thead>
						<tr>
							<td colspan="2">
								<bean:message bundle="security" key="resource.currentTitle" />
							</td>
						</tr>
						</thead>
						<logic:iterate name="removeresources" id="resource" indexId="i">
							<tr>
								<td>
									<input type="checkbox" name="removeResource" value="<bean:write  name="resource" property="id" />">
									<bean:write name="resource" property="code" /> --- <bean:write name="resource" property="name" />
								</td>

							</tr>
						</logic:iterate>
						<br>
						<thead>
						<tr>
							<td colspan="2">
								<bean:message bundle="security" key="resource.availableTitle" />
							</td>
						</tr>
						</thead>
						<logic:iterate name="resources" id="resource" indexId="j">
							<tr>
								<td>
									<input type="checkbox" name="addResource" value="<bean:write  name="resource" property="id" />">
									<bean:write name="resource" property="code" /> --- <bean:write name="resource" property="name" />
								</td>

							</tr>
						</logic:iterate>
						<tr>
							<td colspan="2" align="right">
								<html:submit styleClass="button">
									<bean:message key="button.save" />
								</html:submit>
								<html:reset styleClass="button">
									<bean:message key="button.reset" />
								</html:reset>
							</td>
						</tr>
						<html:hidden property="role.id" />
						</html:form>
					</table>
			</gui:tab>

			<gui:tab prototype="boTab" name="tab3" title="<%=resourceTitle%>" followUp="resourceManager.do?method=loadResource">
              resource
            </gui:tab>

		</gui:tabbedPanel>
	</gui:window>
</center>
<html:javascript formName="roleForm" dynamicJavascript="true" staticJavascript="false" />
<script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>
