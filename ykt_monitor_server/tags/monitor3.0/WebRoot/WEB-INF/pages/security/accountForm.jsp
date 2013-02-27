<%@ include file="../tiles/include.jsp"%>

<bean:define id="title">

	<bean:message bundle="security" key="account.title" />

</bean:define>

<bean:define id="tabTitle">
	<c:choose>
		<c:when test="${param.opType == 'add'}">
			<bean:message bundle="security" key="account.add" />
		</c:when>
		<c:otherwise>
			<bean:message bundle="security" key="account.edit" />
		</c:otherwise>
	</c:choose>
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
		<gui:tabbedPanel prototype="boTabbedPanel" followUp="accountManager.do?method=loadAccount4Add" color="#f0f0f0" selectedTab="tab1" width="70">
			<gui:tab prototype="boTab" name="tab1" title="<%=tabTitle%>" followUp="accountManager.do?method=loadAccount4Add">
				<html:form action="<%=formAction%>" focus="account.name" onsubmit="return validateAccountForm(this);">
					<html:errors />
					<br>

					<table class="win" CELLPADDING="0" CELLSPACING="0" WIDTH="100%">
						<tr>
							<td>
								<bean:message bundle="security" key="account.name" />
							</td>

							<td>
								<html:text property="account.name" size="20" maxlength="32" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.code" />
							</td>

							<td>
								<html:text property="account.person.personCode" size="20" maxlength="32" />
							<td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="person.name" />
							</td>

							<td>
								<html:text property="account.person.personName" size="20" maxlength="32" />
							<td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="account.password" />
							</td>

							<td>
								<html:password property="account.password" size="20" maxlength="32" redisplay="true" onchange="passwordChanged(this)" style="width:132"/>
							</td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="account.repassword" />
							</td>

							<td>
								<html:password property="account.repassword" size="20" maxlength="32" redisplay="true" style="width:132"/>
							</td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="person.sex" />
							</td>

							<td>
								<html:radio property="account.person.sex" value="1" />
								<bean:message bundle="security" key="person.male" />
								<html:radio property="account.person.sex" value="2" />
								<bean:message bundle="security" key="person.female" />
							<td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="person.email" />
							</td>

							<td>
								<html:text property="account.person.email" size="20" maxlength="50" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.qq" />
							</td>

							<td>
								<html:text property="account.person.qq" size="20" maxlength="32" />
							<td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="person.phone" />
							</td>

							<td>
								<html:text property="account.person.phone" size="20" maxlength="32" />
							<td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="person.cardId" />
							</td>

							<td>
								<html:text property="account.person.cardId" size="20" maxlength="32" />
							<td>
						</tr>
						
						<tr>
							<td>
								<bean:message bundle="security" key="person.card" />
							</td>

							<td>
								<html:text property="account.person.card" size="20" maxlength="32" />
							<td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="person.birthday" />
							</td>

							<td>
								<html:text property="account.person.birthday" size="20" maxlength="8" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.dept" />
							</td>

							<td>
								<html:text property="account.person.dept" size="20" maxlength="32" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.post" />
							</td>

							<td>
								<html:text property="account.person.post" size="20" maxlength="32" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.postDate" />
							</td>

							<td>
								<html:text property="account.person.postDate" size="20" maxlength="8" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.workPlace" />
							</td>

							<td>
								<html:text property="account.person.workPlace" size="20" maxlength="100" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.office" />
							</td>

							<td>
								<html:text property="account.person.office" size="20" maxlength="100" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.officephone" />
							</td>

							<td>
								<html:text property="account.person.officePhone" size="20" maxlength="32" />
							<td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="person.address" />
							</td>

							<td>
								<html:text property="account.person.address" size="20" maxlength="100" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.postalcode" />
							</td>

							<td>
								<html:text property="account.person.postalcode" size="20" maxlength="10" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.msn" />
							</td>

							<td>
								<html:text property="account.person.msn" size="20" maxlength="32" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.polity" />
							</td>

							<td>
								<html:text property="account.person.polity" size="20" maxlength="32" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.nation" />
							</td>

							<td>
								<html:text property="account.person.nation" size="20" maxlength="32" />
							<td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="person.workdate" />
							</td>

							<td>
								<html:text property="account.person.workDate" size="20" maxlength="8" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.techpost" />
							</td>

							<td>
								<html:text property="account.person.techPost" size="20" maxlength="32" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.seminary" />
							</td>

							<td>
								<html:text property="account.person.seminary" size="20" maxlength="32" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.graducation" />
							</td>

							<td>
								<html:text property="account.person.graducation" size="20" maxlength="8" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.education" />
							</td>

							<td>
								<html:text property="account.person.education" size="20" maxlength="32" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.degree" />
							</td>

							<td>
								<html:text property="account.person.degree" size="20" maxlength="32" />
							<td>
						</tr>
						<tr>
							<td>
								<bean:message bundle="security" key="person.remark" />
							</td>

							<td>
								<html:text property="account.person.remark" size="20" maxlength="100" />
							<td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="person.college" />
							</td>

							<td>
								<html:text property="account.person.college" size="20" maxlength="100" />
							<td>
						</tr>

						<tr>
							<td>
								<bean:message bundle="security" key="person.department" />
							</td>

							<td>
								<html:text property="account.person.department" size="20" maxlength="32" />
							<td>
						</tr>
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

<html:javascript formName="accountForm" dynamicJavascript="true" staticJavascript="false" />
<script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>
