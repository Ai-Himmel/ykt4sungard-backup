<%@ include file="/html/extportlet/advquery/init.jsp"%>

<%
	String querytype23 = "bydate";
	String queryType = ParamUtil.getString(request, "statType",
			querytype23);
%>

<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.DEVUSERATE_ERROR_EXIST)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.DEVUSERATE_ERROR_EXIST, SessionErrors.get(
										request, EcardConstants.DEVUSERATE_ERROR_EXIST))%> </font>
</c:if>


<html:form action="/ext/devuserate_queryresult" method="POST"
	onsubmit="submitPortletForm(this); return false;">
	<table width="100%" border="0" align="center" cellpadding="0"
		cellspacing="0">
		<tr>
			<td>
				<html:hidden property="querytype" />
				<table width="94%" border="0" align="center" cellpadding="0"
					cellspacing="0">
					<tr>
						<td nowrap="nowrap">
							<bean:message key="query.type" />
							<html:radio property="statType" value="bydate"
								onclick="javascript:setdevuserateformQueryType('bydate')"></html:radio>
							<bean:message key="query.bydate" />
							<html:radio property="statType" value="bymonth"
								onclick="javascript:setdevuserateformQueryType('bymonth')"></html:radio>
							<bean:message key="query.bymonth" />
						</td>
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
										<td height="25" align="right" nowrap="nowrap">
											<bean:message key="query.savingtype" />
										</td>
										<td nowrap="nowrap">
											<html:select property="seritype">
												<html:option value="240001">
													<bean:message key="dev.serial" />
												</html:option>
												<html:option value="930034">
													<bean:message key="dev.saving" />
												</html:option>
												<html:option value="930031">
													<bean:message key="dev.consume" />
												</html:option>
											</html:select>
										</td>
										<td nowrap="nowrap">
											&nbsp;
										</td>
										<td nowrap="nowrap">
											&nbsp;
										</td>
										<td nowrap="nowrap">
											&nbsp;
										</td>
										<td nowrap="nowrap">
											&nbsp;
										</td>
									</tr>
									<tr>
										<td width="7%" nowrap="nowrap">
											<bean:message key="query.begindate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="devuserate_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'devuserate_begindate'})"
/> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.enddate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="devuserate_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'devuserate_enddate'})"
/> </a>
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
											<button onclick="document.devuserateform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.devuserateform.reset();">
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
										<td height="25" align="right" nowrap="nowrap">
											<bean:message key="query.savingtype" />
										</td>
										<td nowrap="nowrap">
											<html:select property="seritype">
												<html:option value="240001">
													<bean:message key="dev.serial" />
												</html:option>
												<html:option value="930034">
													<bean:message key="dev.saving" />
												</html:option>
												<html:option value="930031">
													<bean:message key="dev.consume" />
												</html:option>
											</html:select>
										</td>
										<td nowrap="nowrap">
											&nbsp;
										</td>
										<td nowrap="nowrap">
											&nbsp;
										</td>
										<td nowrap="nowrap">
											&nbsp;
										</td>
										<td nowrap="nowrap">
											&nbsp;
										</td>
									</tr>
									<tr>
										<td width="7%" nowrap="nowrap">
											<bean:message key="query.beginmonth" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="devuserate_begindate" readonly="true"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'devuserate_begindate',dateFmt:'yyyy-MM'})" /> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.endmonth" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="devuserate_enddate" readonly="true"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'devuserate_enddate',dateFmt:'yyyy-MM'})" /> </a>
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
											<button onclick="document.devuserateform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.devuserateform.reset();">
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
    function setdevuserateformQueryType(typevalue) {
        document.devuserateform.querytype.value = typevalue;
        document.devuserateform.submit();
    }
</script>
</html:form>
