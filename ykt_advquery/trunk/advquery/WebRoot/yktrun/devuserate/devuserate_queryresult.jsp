<%@ include file="/html/extportlet/advquery/init.jsp"%>

<%
	String querytype23 = "bydate";
	String queryType = ParamUtil.getString(request, "querytype",
			querytype23);
%>

<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.ERROR_EXIST)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.ERROR_EXIST, SessionErrors.get(
										request, EcardConstants.ERROR_EXIST))%> </font>
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
								onclick="javascript:setQueryType('bydate')"></html:radio>
							<bean:message key="query.bydate" />
							<html:radio property="statType" value="bymonth"
								onclick="javascript:setQueryType('bymonth')"></html:radio>
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
													id="f_trigger_devuserate_begindate" /> </a>
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
													id="f_trigger_devuserate_enddate" /> </a>
										</td>
										<script language="JavaScript">
                        
				                        Calendar.setup({
				                            inputField     :    "devuserate_begindate",     // id of the input field
				                            weekNumbers     :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "f_trigger_devuserate_begindate",  // trigger for the calendar (button ID)
				                            ifFormat       :    "<%=LanguageUtil.get(pageContext,
											"format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                        
				                        Calendar.setup({
				                            inputField     :    "devuserate_enddate",     // id of the input field
				                            weekNumbers        :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "f_trigger_devuserate_enddate",  // trigger for the calendar (button ID)
				                            ifFormat      :    "<%=LanguageUtil.get(pageContext,
											"format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                    </script>
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
													id="f_trigger_devuserate_begindate" /> </a>
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
													id="f_trigger_devuserate_enddate" /> </a>
										</td>
										<script language="JavaScript">
                        
				                        Calendar.setup({
				                            inputField     :    "devuserate_begindate",     // id of the input field
				                            weekNumbers        :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "f_trigger_devuserate_begindate",  // trigger for the calendar (button ID)
				                           ifFormat       :    "<%=LanguageUtil.get(pageContext,
											"format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                        
				                        Calendar.setup({
				                            inputField     :    "devuserate_enddate",     // id of the input field
				                            weekNumbers        :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "f_trigger_devuserate_enddate",  // trigger for the calendar (button ID)
				                            ifFormat      :    "<%=LanguageUtil.get(pageContext,
											"format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                    </script>
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

	<c:if test='<%=request.getAttribute("result") != null%>'>
		<%
			String statTypeShow = request.getAttribute("stattypeshow")
							.toString();
		%>
		<%
			List result = (List) request.getAttribute("result");
		%>
		<%
			String picType = request.getAttribute("pictype").toString();
		%>
		<%
			String dateRange = request.getAttribute("daterange")
							.toString();
		%>
		<%
			String devName = request.getAttribute("devname").toString();
		%>
		<%
			String yLabel = request.getAttribute("ylabel").toString();
		%>
		<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td>

					<display:table name="result" pagesize="10" class="isis"
						style="width:100%" requestURI="/ext/photo_queryresult"
						export="true" id="currentRowObject">
						<display:column property="balance_date" title="<%=statTypeShow%>"></display:column>
						<display:column property="devuse"
							title="<%=LanguageUtil.get(pageContext, "dev.use")%>"></display:column>
						<display:column property="total"
							title="<%=LanguageUtil
											.get(pageContext, "dev.totle")%>"></display:column>
						<display:column property="rate"
							title="<%=LanguageUtil.get(pageContext,
													"dev.rate")%>"></display:column>
					</display:table>
				</td>
			</tr>
		</table>
		<table>
			<%
				String basePath = request.getScheme() + "://"
								+ request.getServerName() + ":"
								+ request.getServerPort() + "/delegate/cewolf";
			%>
			<cewolf:chart id="line"
				title='<%=devName
								+ LanguageUtil.get(pageContext, "dev.title")%>'
				type="<%=picType%>" yaxislabel="<%=yLabel%>">
				<cewolf:colorpaint
					color='<%=LanguageUtil
										.get(pageContext, "chart.bgcolor")%>' />
				<cewolf:data>
					<cewolf:producer id="devUseRateChart" />
				</cewolf:data>
				<cewolf:chartpostprocessor id="dataColor">
				</cewolf:chartpostprocessor>

			</cewolf:chart>

			<cewolf:img chartid="line" renderer="<%=basePath%>"
				width='<%=Integer.parseInt(LanguageUtil.get(pageContext,
									"chart.barwidth"))%>'
				height='<%=Integer.parseInt(LanguageUtil.get(pageContext,
									"chart.barheight"))%>' />
		</table>
	</c:if>
</html:form>
<script>
    function setQueryType(typevalue) {
        document.devuserateform.querytype.value = typevalue;
        document.devuserateform.action='/ext/devuserate';
        document.devuserateform.submit();
    }
</script>