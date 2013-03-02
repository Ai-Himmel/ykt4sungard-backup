<%@ page contentType="text/html;charset=UTF-8" %>
<%@ include file="/pages/common/taglibs.jsp" %>

<%@ include file="/WEB-INF/pages/include/style.jsp"%>

<center>
	<bean:define id="title">
		<bean:message bundle="check" key="department.title" />
	</bean:define>
	<gui:window title="<%=title%>" prototype="boWindow" color="100%">

		<%
String tab = request.getParameter("webGUI.tabbedPanel.tab");
			if (Util.isNull(tab))
				tab = "tab1";
%>
		<gui:tabbedPanel prototype="boTabbedPanel" followUp="usermanag.jsp" color="#f0f0f0" selectedTab="<%=tab %>" width="50">
			<!--********************* add  catalog ******************************************-->
			<bean:define id="tab1_title">
				<bean:message bundle="check" key="department.add" />
			</bean:define>
			<gui:tab prototype="boTab" name="tab1" title="<%=tab1_title%>" followUp="./departmentManager.do?method=load4add">
				<html:form action="addDepartment.do?method=create" onsubmit="return validateDepartmentForm(this);">
					<html:errors />
					<table class="win" CELLPADDING="0" CELLSPACING="0" width="100%">
						<tr>
							<td width="220">
								<html:select property="parentId" size="15" style="width:200 px;">
									<logic:present name="departmenttree" scope="request">
										<html:options collection="departmenttree" labelProperty="deptTitle" property="deptId" />
									</logic:present>
								</html:select>
							</td>
							<td valign="top">
								<html:text property="department.name" size="20" maxlength="50" />
							</td>
						</tr>
						<tr>
							<td colspan="2" align="right">
								<html:submit styleClass="button">
									<bean:message key="button.save" />
								</html:submit>
								<html:cancel styleClass="button">
									<bean:message key="button.cancel" />
								</html:cancel>
							</td>
						</tr>
						<html:hidden property="department.id" value="null" />
						</html:form>
					</table>
			</gui:tab>

			<!--********************* edit  catalog ******************************************-->
			<bean:define id="tab2_title">
				<bean:message bundle="check" key="department.edit" />
			</bean:define>
			<gui:tab prototype="boTab" name="tab2" title="<%=tab2_title%>" followUp="./departmentManager.do?method=load4edit">
				<html:form action="editDepartment?method=update" onsubmit="return validateDepartmentForm(this);">
					<html:errors />
					<table class="win" CELLPADDING="0" CELLSPACING="0" width="100%">
						<tr>
							<td width="220">
								<html:select property="department.id" size="15" style="width:200 px;">
									<logic:present name="departmenttree" scope="request">
										<html:options collection="departmenttree" labelProperty="deptTitle" property="deptId" />
									</logic:present>
								</html:select>
							</td>
							<td valign="top">
								<html:text property="department.name" size="20" maxlength="50" />
							</td>
						</tr>
						<tr>
							<td colspan="2" align="right">
								<html:submit styleClass="button">
									<bean:message key="button.update" />
								</html:submit>
								<html:cancel styleClass="button">
									<bean:message key="button.cancel" />
								</html:cancel>
							</td>
						</tr>
						</html:form>
					</table>
			</gui:tab>
			<!--********************* remove  catalog ******************************************-->
			<bean:define id="tab3_title">
				<bean:message bundle="check" key="department.remove" />
			</bean:define>
			<gui:tab prototype="boTab" name="tab3" title="<%=tab3_title%>" followUp="./departmentManager.do?method=load4remove">
				<html:form action="removeDepartment?method=remove" onsubmit="return validateDepartmentForm(this);">
					<html:errors />
					<table class="win" CELLPADDING="0" CELLSPACING="0" width="100%">
						<tr>
							<td>
								<html:select property="department.id" size="15" style="width:200 px;">
									<logic:present name="departmenttree" scope="request">
										<html:options collection="departmenttree" labelProperty="deptTitle" property="deptId" />
									</logic:present>
								</html:select>
							</td>
						</tr>
						<tr>
							<td align="right">
								<html:submit styleClass="button">
									<bean:message key="button.delete" />
								</html:submit>
								<html:cancel styleClass="button">
									<bean:message key="button.cancel" />
								</html:cancel>
							</td>
						</tr>
						<html:hidden property="department.name" value="null" />
						</html:form>
					</table>
			</gui:tab>
			

		</gui:tabbedPanel>
	</gui:window>

</center>
<html:javascript formName="departmentForm" dynamicJavascript="true" staticJavascript="false" />
<script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>
