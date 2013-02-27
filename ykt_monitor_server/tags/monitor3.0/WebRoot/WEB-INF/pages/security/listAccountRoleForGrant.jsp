<%@ include file="../tiles/include.jsp"%>
<center>
	<bean:define id="title">
		<bean:message bundle="security" key="role.list" />
	</bean:define>
	<gui:window title="<%=title%>" prototype="boWindow" color="100%">
		<gui:tabbedPanel prototype="boTabbedPanel" followUp="usermanag.jsp" color="#f0f0f0" selectedTab="tab1" width="50">
			<gui:tab prototype="boTab" name="tab1" title="<%=title%>">
				<html:form action="grantAccountRole?method=grantAccountRole" onsubmit="return onFormSubmit(this);">
					<html:errors />
					<table class="sort-table" cellSpacing="1" cellPadding="1" width="100%" border="0">
						<thead>
							<tr>
								<td>
									<bean:message bundle="security" key="security.selectRole" />
								</td>
							</tr>
						</thead>
						<tr>
							<td>
								<bean:message bundle="security" key="person.name" /> :&nbsp;&nbsp;<c:out value="${currentAccount.person.personName}"/>
							</td>
						</tr>
						<tr>
							<td>
								<table>
									<tr>
										<th>
											<bean:message bundle="security" key="security.availableRole" />
										</th>
										<th>
											&nbsp;
										</th>
										<th>
											<bean:message bundle="security" key="security.currentRole" />
										</th>
									</tr>
									<c:set var="leftList" value="${availableRole}" scope="request" />
									<c:set var="rightList" value="${currentRole}" scope="request" />
									<c:import url="/WEB-INF/pages/pickList.jsp">
										<c:param name="listCount" value="6" />
										<c:param name="leftId" value="availableRole" />
										<c:param name="rightId" value="currentRole" />
										<c:param name="listSize" value="12" />
										<c:param name="listWidth" value="200px" />
									</c:import>
								</table>
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
					</table>
					<input type="hidden" name="id" value='<c:out value="${currentAccount.id}"/>'>
				</html:form>



			</gui:tab>
		</gui:tabbedPanel>
	</gui:window>

</center>
<script type="text/javascript">
function onFormSubmit(theForm) {
	selectAll('currentRole');
    return true;
}
</script>
