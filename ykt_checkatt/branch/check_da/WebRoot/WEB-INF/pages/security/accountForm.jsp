<%@ include file="../tiles/include.jsp"%>

<bean:define id="title">

	<bean:message bundle="security" key="account.title" />

</bean:define>

<bean:define id="tabTitle">
	<%--<c:choose>
		<c:when test="${param.opType == 'add'}">
			<bean:message bundle="security" key="account.add" />
		</c:when>
		<c:otherwise>
			<bean:message bundle="security" key="account.edit" />
		</c:otherwise>
	</c:choose>--%>
    <bean:message bundle="security" key="account.view" />
</bean:define>

<bean:define id="formAction">
	<c:choose>
		<c:when test="${param.opType == 'add'}">
               addAccount.do?method=addAccount
		</c:when>
		<c:otherwise>
               editAccount.do?method=editAccount
		</c:otherwise>
	</c:choose>
</bean:define>


<center>
	<gui:window title="<%=title%>" prototype="boWindow" color="100%">
		<gui:tabbedPanel prototype="boTabbedPanel" followUp="accountManager.do?method=loadAccount4Add" color="#f0f0f0" selectedTab="tab1" width="78">
			<gui:tab prototype="boTab" name="tab1" title="<%=tabTitle%>" followUp="accountManager.do?method=loadAccount4Add">
				<html:form action="<%=formAction%>" focus="account.name" onsubmit="return validateAccountForm(this);">
					<html:errors />
					<br>

					<table class="win" CELLPADDING="0" CELLSPACING="0" WIDTH="100%">
						<tr height="25">
							<td >
								<bean:message bundle="security" key="person.code" />
							</td>

							<td>
                                <bean:write name="accountForm" property="account.person.stuempno"/>
							<td>
						</tr>

						<tr height="25">
							<td>
								<bean:message bundle="security" key="person.name" />
							</td>

							<td>
                                <bean:write name="accountForm" property="account.person.custname"/>
							<td>
						</tr>
                        <tr height="25">
                            <td>
                                <bean:message bundle="security" key="person.sex" />
                            </td>

                            <td>
                                <logic:equal value="1" name="accountForm" property="account.person.sex">
                                    <bean:message bundle="security" key="person.male" />
                                </logic:equal>
                                <logic:equal value="2" name="accountForm" property="account.person.sex">
                                    <bean:message bundle="security" key="person.female" />
                                </logic:equal>
                            <td>
                        </tr>
						<tr height="25">
							<td>
								<bean:message bundle="security" key="person.email" />
							</td>

							<td>
                                <bean:write name="accountForm" property="account.person.email"/>
							<td>
						</tr>
						<tr height="25">
							<td>
								<bean:message bundle="security" key="person.dept" />
							</td>

							<td>
                                <bean:write name="accountForm" property="deptname"/>
							<td>
						</tr>
			             <%--<tr>
			                <td class="left" width="20%"><bean:message bundle="security" key="account.deptLimit"/></td>
			                <td class="right">
			                    <IFRAME name='DataFrame' src="departmentManager.do?method=loadDepartmentTree&accountId=<bean:write name="accountForm" property="account.id"/>" width="400" height="150" SCROLLING="auto"></IFRAME>
			                    <input type="hidden" name ="deptLimit"/>
			                </td>
			            </tr>--%>
						
						<tr>
							<td colspan="2" align="right">
								<%--<html:submit styleClass="button">
									<bean:message key="button.save" />
								</html:submit>
								<input type="submit" class="button" name="submitButton" value="<bean:message key="button.save" />"  style="margin-right:60px" onclick="return onSubmit();"/>
								<html:reset styleClass="button">
									<bean:message key="button.reset" />
								</html:reset>--%>
                                <input type="button" class="button" style="margin-right:60px" value="<bean:message key="button.back" />"  onclick="javascript:window.history.back();">
							</td>
						</tr>
						<html:hidden property="account.id" />
						</html:form>
					</table>
			</gui:tab>

		</gui:tabbedPanel>
	</gui:window>
</center>
<script type="text/javascript">

    function passwordChanged(passwordField) {
        var origPassword = "<c:out value="${accountForm.map.account.password}"/>";
        if (passwordField.value != origPassword) {
            createFormElement("input", "hidden",
                              "encryptPass", "encryptPass",
                              "true", passwordField.form);
        }
    }
</script>

<script>
function onSubmit(){
    m_sCheckKey	= DataFrame.GetAllCheckDataNoText();
    if(m_sCheckKey==""){
       alert("please select department");
       return false;
    }

    document.accountForm.deptLimit.value = m_sCheckKey;   
    
}
</script>
<html:javascript formName="accountForm" dynamicJavascript="true" staticJavascript="false" />
<script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>
