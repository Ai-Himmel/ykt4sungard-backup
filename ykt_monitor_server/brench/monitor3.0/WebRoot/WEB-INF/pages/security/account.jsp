<%@ include file="../tiles/include.jsp"%>
<bean:define id="title">
	<bean:message key="security.title" />
</bean:define>
<bean:define id="accountTitle">
	<bean:message key="security.account" />
</bean:define>
<bean:define id="groupTitle">
	<bean:message key="security.group" />
</bean:define>
<bean:define id="rightTitle">
	<bean:message key="security.right" />
</bean:define>
<center>
	<gui:window title="<%=title%>" prototype="boWindow" color="100%">
		<gui:tabbedPanel prototype="boTabbedPanel" followUp="listAccount.do" color="#f0f0f0" selectedTab="tab1" width="60">
			<gui:tab prototype="boTab" name="tab1" title="<%=accountTitle%>" followUp="./listAccount.do?method=listAccount">
				<table class="win" CELLPADDING="2" CELLSPACING="0" width="100%">
					<html:form action="listAccount.do?method=listAccount">
						<tr align="right">
							<td>

								<bean:message key="register.number" />
								<input type="text" name="para" value="">
								<bean:message key="register.name" />
								<input type="text" name="paraPersonName" value="">
								<html:submit styleClass="button">
									<bean:message key="button.search" />
								</html:submit>
							</td>
						</tr>
				</table>
				</html:form>
				<logic:present name="accounts" scope="request">
				<html:form action="removeAccountAction?method=removeAccount" onsubmit="return validateListAccountForm(this);">
					<html:errors />
					<table class="sort-table" cellSpacing="1" cellPadding="1" width="99%" border="0">
						
							<thead>
								<tr>
									<td>
										<bean:message key="security.account" />
									</td>
										<td>
										<bean:message key="register.name" />
									</td>
									<td>
										<bean:message key="security.group" />
									</td>
								</tr>
							</thead>

							<!--page offset start -->
							<pg:pager url="./listAccount.do" items="<%=((Integer)request.getAttribute("accountCount")).intValue()%>" index="center" maxPageItems="10" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
								<%-- keep track of preference --%>
								<pg:param name="para" />
								<pg:param name="page" />
								<pg:param name="orderby" />
								<pg:param name="sort" />
								<pg:param name="method" />

								<%-- save pager offset during form changes --%>
								<input type="hidden" name="pager.offset" value="<%= offset %>">

								<logic:iterate name="accounts" id="account">
									<pg:item>
										<tr>
											<td>
												<input type="checkbox" name="id" value="<bean:write  name="account" property="id" />">
												<bean:write name="account" property="name" />
											</td>
											<td>
												<bean:write name="account" property="person.name" />
											</td>
											<td>
												<bean:write name="account" property="group.desc" />
											</td>
										</tr>

									</pg:item>
								</logic:iterate>
					</table>

					<jsp:include page="./page.jsp" flush="true" />
					</pg:pager>
					<!-- page offset end -->

					<table class="sort-table" cellSpacing="1" cellPadding="1" width="100%" border="0">



						<tr>
							<td colspan="2" align="right">
								<html:submit styleClass="button">
									<bean:message key="button.delete" />
								</html:submit>

								<html:reset styleClass="button">
									<bean:message key="button.reset" />
								</html:reset>
							</td>
						</tr>

						</html:form>

					</table>

					<html:form action="changeAccountGroup?method=changeAccountGroup">
						<table class="sort-table" cellSpacing="1" cellPadding="1" width="100%" border="0">
							<thead>
								<tr>
									<td>
										<bean:message key="security.account" />
									</td>
									<td>
										<bean:message key="security.group" />
									</td>
								</tr>
							</thead>
							<tr>
								<td>
									<html:select property="accountId" style="width:200px;">
										<html:options collection="accounts" labelProperty="name" property="id" />
									</html:select>
								</td>
								<td>
									<html:select property="groupId" style="width:200px;">
										<html:options collection="groups" labelProperty="desc" property="id" />
									</html:select>
								</td>
							</tr>
							<tr>
								<td align="right" colspan="2">
									<html:submit styleClass="button">
										<bean:message key="button.save" />
									</html:submit>
								</td>
							</tr>
							</html:form>

						</table>
												</logic:present>
						<logic:notPresent name="accounts" scope="request">

									<bean:message key="person.no" />
	
						</logic:notPresent>
			</gui:tab>
			<gui:tab prototype="boTab" name="tab2" title="<%=groupTitle%>" followUp="listGroup.do?method=listRole">
    group
   </gui:tab>

			<gui:tab prototype="boTab" name="tab2" title="<%=rightTitle%>" followUp="listRight.do?method=listRight">
    right
   </gui:tab>

		</gui:tabbedPanel>
	</gui:window>
</center>
<html:javascript formName="listAccountForm" dynamicJavascript="true" staticJavascript="false" />
<script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>
