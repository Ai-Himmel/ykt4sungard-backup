<%@ include file="../tiles/include.jsp"%>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

	<table id="classSelect" width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
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
				<html:form action="studentAction.do?method=class4Search">
				<TR><td><html:text property="studentIds"/></td></TR>
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
				<html:form action="studentAction.do?method=abroadDistribution">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
						<TR><td><html:text property="studentIds"/></td></TR>
						<tbody>
							<tr align="center" valign="middle">
								<td width="24" height="24" valign="middle" class="tableHeader">
									<input type="checkbox" name="checkSwitch" onclick="selectIns();">
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="college.name" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="class.name" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="class.assistant" />
								</td>
							</tr>
							
							
							<logic:present name="abroadClasses" scope="request">
								<logic:iterate name="abroadClasses" id="classes">
									<tr align="center" valign="middle">
										<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<input type="checkbox" name="deleteX" value="<bean:write name="classes" property="classId"/>">
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="classes" property="collegeName" />
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="classes" property="className" />
											&nbsp;
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="classes" property="managerName" />
											&nbsp;
										</td>
									</tr>
								</logic:iterate>
							</logic:present>
						</tbody>
					</table>
					<tr>
						<td height="30" align="right" valign="middle">
							<html:submit property="distribution" styleClass="button_nor">
								<bean:message bundle="classmanage" key="abroadDistribution.distribute" />
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
