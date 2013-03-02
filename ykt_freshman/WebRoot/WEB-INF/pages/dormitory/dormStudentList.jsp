<%@ include file="../tiles/include.jsp"%>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table id="stuSelect" width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium"><bean:message bundle="classmanage" key="abroadDistribution.abroadDistribution" /></font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="middle">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				<html:form action="studentAction.do?method=abroad4Search">
					<tr>
						<td height="40" align="right" valign="middle" class="tdborder02">
							<html:submit property="search" styleClass="button_nor">
								<bean:message key="button.query" />
							</html:submit>
						</td>
					</tr>
				</html:form>
			</td>
		</tr>
		<tr>
			<td height="20" align="center" valign="middle" class="medium">
				&nbsp;
			</td>
		</tr>

		<tr>
			<td height="40" align="center" valign="top">
				<html:form action="studentAction.do?method=class4List">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>

						<tbody>
							<tr align="center" valign="middle">
								<td width="24" height="24" valign="middle" class="tableHeader">
									<input type="checkbox" name="checkSwitch" onclick="selectIns();">
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="studentsearch.studentNo" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="studentsearch.stuName" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="studentsearch.gender" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="studentsearch.nationality" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="studentsearch.majorin" />
								</td>
							</tr>
							<logic:present name="abroadmodels" scope="request">
								<logic:iterate name="abroadmodels" id="abroadstu">
									<tr align="center" valign="middle">
										<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<input type="checkbox" name="deleteX" value="<bean:write name="abroadstu" property="studentId"/>">
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="abroadstu" property="studentNo" />
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="abroadstu" property="stuName" />
											&nbsp;
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="abroadstu" property="gender" />
											&nbsp;
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="abroadstu" property="nationality" />
											&nbsp;
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="abroadstu" property="majorin" />
											&nbsp;
										</td>

									</tr>
								</logic:iterate>
							</logic:present>
						</tbody>
					</table>
					<tr>
						<td height="30" align="right" valign="middle">
							<html:submit property="next" styleClass="button_nor">
								<bean:message bundle="classmanage" key="abroadDistribution.nextStep" />
							</html:submit>
						</td>
					</tr>
				</html:form>
			</td>
		</tr>
		<tr>
			<td align="left" valign="middle">
				&nbsp;
			</td>
		</tr>
	</table>
</body>
