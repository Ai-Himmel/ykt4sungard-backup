<%@ include file="/html/extportlet/advquery/init.jsp"%>
<%
	String querytype23 = "bydate";
	String queryType = ParamUtil.getString(request, "statType",
			querytype23);
%>

<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.SAVINGSORT_ERROR_EXIST)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.SAVINGSORT_ERROR_EXIST, SessionErrors.get(
										request, EcardConstants.SAVINGSORT_ERROR_EXIST))%> </font>
</c:if>

<html:form action="/ext/savingsort_queryresult" method="POST"
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
								onclick="javascript:setsavingsortformQueryType('bydate')"></html:radio>
							<bean:message key="query.bydate" />
							<html:radio property="statType" value="bymonth"
								onclick="javascript:setsavingsortformQueryType('bymonth')"></html:radio>
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
											<html:select property="seritype" style="width:155">
												<html:option value="204">
													<bean:message key="saving.seri" />
												</html:option>
												<html:option value="202">
													<bean:message key="saving.pos" />
												</html:option>
												<html:option value="201">
													<bean:message key="saving.cash" />
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
											<html:text property="savingsort_begindate" styleId="savingsort_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'savingsort_begindate'})"
													/> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.enddate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="savingsort_enddate" styleId="savingsort_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'savingsort_enddate'})"
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
											<button onclick="document.savingsortform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.savingsortform.reset();">
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
											<html:select property="seritype" style="width:155">
												<html:option value="204">
													<bean:message key="saving.seri" />
												</html:option>
												<html:option value="202">
													<bean:message key="saving.pos" />
												</html:option>
												<html:option value="201">
													<bean:message key="saving.cash" />
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
											<html:text property="savingsort_begindate" styleId="savingsort_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'savingsort_begindate',dateFmt:'yyyy-MM'})"
													 /> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.endmonth" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="savingsort_enddate" styleId="savingsort_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'savingsort_enddate',dateFmt:'yyyy-MM'})"
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
											<button onclick="document.savingsortform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.savingsortform.reset();">
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
    function setsavingsortformQueryType(typevalue) {
        document.savingsortform.querytype.value = typevalue;
        document.savingsortform.submit();
    }
</script>
</html:form>
