<%@ include file="/html/extportlet/advquery/init.jsp"%>

<%
	String querytype23 = "bydate";
	String queryType = ParamUtil.getString(request, "statType",
			querytype23);
%>

<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.DEPTACCOUNT_ERROR_EXIST)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.DEPTACCOUNT_ERROR_EXIST, SessionErrors.get(
										request, EcardConstants.DEPTACCOUNT_ERROR_EXIST))%> </font>
</c:if>

<html:form action="/ext/deptaccount_queryresult" method="POST"
	onsubmit="submitPortletForm(this); return false;">

	<table width="100%" border="0" align="center" cellpadding="0"
		cellspacing="0">
		<tr>
			<td>
				<html:hidden property="querytype" />
				<table width="94%" border="0" align="center" cellpadding="0"
					cellspacing="0">
					<tr>
						<td nowrap="nowrap" width="50%">
							<bean:message key="query.type" />
							<html:radio property="statType" value="bydate"
								onclick="javascript:setdeptaccountformQueryType('bydate')"></html:radio>

							<bean:message key="query.bydate" />
							<html:radio property="statType" value="byweek"
								onclick="javascript:setdeptaccountformQueryType('byweek')"></html:radio>

							<bean:message key="query.byweek" />
							<html:radio property="statType" value="bymonth"
								onclick="javascript:setdeptaccountformQueryType('bymonth')"></html:radio>
							<bean:message key="query.bymonth" />
						</td>
						<TD nowrap="nowrap" align="left" width="50%">
							<bean:message key="showtitle.type" />
							<bean:message key="showtitle.type" />
							<html:radio property="showType" value="line"></html:radio>
							<bean:message key="showpic.line" />
							<html:radio property="showType" value="bar"></html:radio>
							<bean:message key="showpic.bar" />
							<html:radio property="showType" value="stack"></html:radio>
							<bean:message key="showpic.stack" />

						</TD>
					</tr>
				</table>
				<c:if test='<%=queryType.equals("bydate")%>'>
					<table width="98%" border="0" align="center" cellpadding="0"
						cellspacing="0">
						<tr>
							<td height="40">
								<table width="96%" border="0" align="center" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="9%" height="25" align="right" nowrap>
											<bean:message key="query.depno" />
										</td>
										<td width="91%">
											<html:select property="depno">
												
												<html:options collection="deptList" labelProperty="deptname"
													property="deptcode" />
											</html:select>
										</td>
									</tr>
								</table>
								<table width="96%" border="0" align="center" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="7%" nowrap="nowrap">
											<bean:message key="query.begindate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="deptaccount_begindate" styleId="deptaccount_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'deptaccount_begindate'})"/> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.enddate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="deptaccount_enddate" styleId="deptaccount_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'deptaccount_enddate'})" /> </a>
										</td>
										
									</tr>
								</table>
							</td>
						</tr>
					</table>
					<table width="98%" border="0" align="center" cellpadding="0"
						cellspacing="0" bgcolor="#f8f8f8">
						<tr>
							<td height="30">
								<table width="96%" border="0" align="center" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="66%" class="red_text">
											<bean:message key="system.note" />
										</td>
										<td width="34%" align="center">
											<button onclick="document.deptaccountform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.deptaccountform.reset();">
												<bean:message key="btn.clear" />
											</button>
										
										</td>
									</tr>
								</table>
							</td>
						</tr>
					</table>
				</c:if>
				<c:if test='<%=queryType.equals("bymonth")%>'>
					<table width="98%" border="0" align="center" cellpadding="0"
						cellspacing="0">
						<tr>
							<td height="40">
								<table width="96%" border="0" align="center" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="8%" height="25" align="right" nowrap>
											<bean:message key="query.depno" />
										</td>
										<td width="92%">
											<html:select property="depno">
												
												<html:options collection="deptList" labelProperty="deptname"
													property="deptcode" />
											</html:select>
										</td>
									</tr>
								</table>
								<table width="96%" border="0" align="center" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="7%" nowrap="nowrap">
											<bean:message key="query.beginmonth" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="deptaccount_begindate" styleId="deptaccount_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'deptaccount_begindate',dateFmt:'yyyy-MM'})"/> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.endmonth" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="deptaccount_enddate" styleId="deptaccount_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'deptaccount_enddate',dateFmt:'yyyy-MM'})"/> </a>
										</td>
										
									</tr>
								</table>
							</td>
						</tr>
					</table>
					<table width="98%" border="0" align="center" cellpadding="0"
						cellspacing="0" bgcolor="#f8f8f8">
						<tr>
							<td height="30">
								<table width="96%" border="0" align="center" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="66%" class="red_text">
											<bean:message key="system.note" />
										</td>
										<td width="34%" align="center">
											<button onclick="document.deptaccountform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.deptaccountform.reset();">
												<bean:message key="btn.clear" />
											</button>
											
										</td>
									</tr>
								</table>
							</td>
						</tr>
					</table>
				</c:if>
				<c:if test='<%=queryType.equals("byweek")%>'>
					<table width="98%" border="0" align="center" cellpadding="0"
						cellspacing="0">
						<tr>
							<td height="40">
								<table width="96%" border="0" align="center" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="8%" height="25" align="right" nowrap>
											<bean:message key="query.depno" />
										</td>
										<td width="92%">

											<html:select property="depno">
												
												<html:options collection="deptList" labelProperty="deptname"
													property="deptcode" />
											</html:select>
										</td>
									</tr>
								</table>
								<table width="96%" border="0" align="center" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="7%" nowrap="nowrap">
											<bean:message key="query.begindate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="deptaccount_begindate" styleId="deptaccount_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'deptaccount_begindate'})"/> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.enddate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="deptaccount_enddate" styleId="deptaccount_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'deptaccount_enddate'})"/> </a>
										</td>
										
									</tr>
								</table>
							</td>
						</tr>
					</table>
					<table width="98%" border="0" align="center" cellpadding="0"
						cellspacing="0" bgcolor="#f8f8f8">
						<tr>
							<td height="30">
								<table width="96%" border="0" align="center" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="66%" class="red_text">
											<bean:message key="system.note" />
										</td>
										<td width="34%" align="center">
											<button onclick="document.deptaccountform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.deptaccountform.reset();">
												<bean:message key="btn.clear" />
											</button>
										</td>
									</tr>
								</table>
							</td>
						</tr>
					</table>
				</c:if>
			</td>
		</tr>
	</table>
	<script>
    function setdeptaccountformQueryType(typevalue) {
        document.deptaccountform.querytype.value = typevalue;
        document.deptaccountform.submit();
    }
</script>

</html:form>
