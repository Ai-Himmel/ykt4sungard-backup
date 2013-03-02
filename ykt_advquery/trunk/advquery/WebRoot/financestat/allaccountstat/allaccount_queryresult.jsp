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

<html:form action="/ext/allaccount_queryresult" method="POST"
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
								onclick="javascript:setQueryType('bydate')"></html:radio>

							<bean:message key="query.bydate" />
							<html:radio property="statType" value="byweek"
								onclick="javascript:setQueryType('byweek')"></html:radio>

							<bean:message key="query.byweek" />
							<html:radio property="statType" value="bymonth"
								onclick="javascript:setQueryType('bymonth')"></html:radio>
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
										<td width="7%" nowrap="nowrap">
											<bean:message key="query.begindate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="allaccount_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													id="f_trigger_allaccount_begindate" /> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.enddate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="allaccount_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													id="f_trigger_allaccount_enddate" /> </a>
										</td>
										<script language="JavaScript">
                        
				                        Calendar.setup({
				                            inputField     :    "allaccount_begindate",     // id of the input field
				                            weekNumbers     :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "f_trigger_allaccount_begindate",  // trigger for the calendar (button ID)
				                            ifFormat       :    "<%=LanguageUtil.get(pageContext,
											"format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                        
				                        Calendar.setup({
				                            inputField     :    "allaccount_enddate",     // id of the input field
				                            weekNumbers        :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "f_trigger_allaccount_enddate",  // trigger for the calendar (button ID)
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
											<button onclick="document.allaccountform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.allaccountform.reset();">
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
										<td width="7%" nowrap="nowrap">
											<bean:message key="query.beginmonth" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="allaccount_begindate" readonly="true"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													id="f_trigger_allaccount_begindate" /> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.endmonth" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="allaccount_enddate" readonly="true"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													id="f_trigger_allaccount_enddate" /> </a>
										</td>
										<script language="JavaScript">
                        
				                        Calendar.setup({
				                            inputField     :    "allaccount_begindate",     // id of the input field
				                            weekNumbers        :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "f_trigger_allaccount_begindate",  // trigger for the calendar (button ID)
				                           ifFormat       :    "<%=LanguageUtil.get(pageContext,
											"format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                        
				                        Calendar.setup({
				                            inputField     :    "allaccount_enddate",     // id of the input field
				                            weekNumbers        :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "f_trigger_allaccount_enddate",  // trigger for the calendar (button ID)
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
							<td height="40">
								<table width="96%" border="0" align="center" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="66%" class="red_text">
											<bean:message key="system.note" />
										</td>
										<td width="34%" align="center">
											<button onclick="document.allaccountform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.allaccountform.reset();">
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
							<td height="30">
								<table width="96%" border="0" align="center" cellpadding="0"
									cellspacing="0">
									<tr>
										<td width="7%" nowrap="nowrap">
											<bean:message key="query.begindate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="allaccount_begindate" readonly="true"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													id="f_trigger_allaccount_begindate" /> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.enddate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="allaccount_enddate" readonly="true"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													id="f_trigger_allaccount_enddate" /> </a>
										</td>
										<script language="JavaScript">
			                        
			                        Calendar.setup({
			                            inputField     :    "allaccount_begindate",     // id of the input field
			                           weekNumbers     :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
			                            button         :    "f_trigger_allaccount_begindate",  // trigger for the calendar (button ID)
			                            ifFormat      :    "<%=LanguageUtil.get(pageContext,
											"format.date")%>",
			                            align          :    "Bl",           // alignment (defaults to "Bl")
			                            singleClick    :    true
			                        });
			                        
			                        Calendar.setup({
			                            inputField     :    "allaccount_enddate",     // id of the input field
			                            weekNumbers        :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
			                            button         :    "f_trigger_allaccount_enddate",  // trigger for the calendar (button ID)
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
											<button onclick="document.allaccountform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.allaccountform.reset();">
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
			String dateRange = request.getAttribute("rangedate")
							.toString();
		%>
		<%
			String picType = request.getAttribute("pictype").toString();
		%>
		<%
			String yLabel = request.getAttribute("ylabel").toString();
		%>
		<%
			String yLabel2 = request.getAttribute("ylabel2").toString();
		%>
		<%
			String statType = request.getAttribute("stattype")
							.toString();
		%>
		<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td>
					<display:table name="result" pagesize="10" class="isis"
						style="width:100%" requestURI="/ext/allaccount_queryresult"
						export="true" id="currentRowObject">
						<display:column property="balance_date" title="<%=statTypeShow%>"></display:column>
						<display:column property="saving"
							title="<%=LanguageUtil.get(pageContext,
											"allaccount.saving")%>"
							format="{0,number,0,000.00}"></display:column>
						<display:column property="consume"
							title="<%=LanguageUtil.get(pageContext,
											"allaccount.consume")%>"
							format="{0,number,0,000.00}"></display:column>
						<display:column property="ensure"
							title="<%=LanguageUtil.get(pageContext,
											"allaccount.ensure")%>"
							format="{0,number,0,000.00}"></display:column>
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
			<%
				if (("timeseries".equals(picType))
								&& ("bydate".equals(statType))) {
			%>
			<cewolf:combinedchart id="combinedChart" layout="vertical"
				title='<%=LanguageUtil.get(pageContext,
											"allaccount.title")%>'
				type="combinedxy">
				<cewolf:colorpaint
					color='<%=LanguageUtil.get(pageContext,
											"chart.bgcolor")%>' />

				<cewolf:plot type="xyline" yaxislabel="<%=yLabel%>">
					<cewolf:data>
						<cewolf:producer id="allaccountstatChart" />
					</cewolf:data>
					<cewolf:chartpostprocessor id="dataColor">
						<cewolf:param name="0"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer1")%>' />
						<cewolf:param name="1"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer2")%>' />
						<cewolf:param name="2"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer3")%>' />
						<cewolf:param name="3"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer4")%>' />
						<cewolf:param name="4"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer6")%>' />
						<cewolf:param name="5"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer5")%>' />
					</cewolf:chartpostprocessor>

				</cewolf:plot>

				<cewolf:plot type="xyline" yaxislabel="<%=yLabel2%>">
					<cewolf:data>
						<cewolf:producer id="allaccountstatChart2" />
					</cewolf:data>
					<cewolf:chartpostprocessor id="dataColor">
						<cewolf:param name="0"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer1")%>' />
						<cewolf:param name="1"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer2")%>' />
						<cewolf:param name="2"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer3")%>' />
						<cewolf:param name="3"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer4")%>' />
						<cewolf:param name="4"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer5")%>' />
						<cewolf:param name="5"
							value='<%=LanguageUtil.get(pageContext,
													"chart.customer6")%>' />
					</cewolf:chartpostprocessor>

				</cewolf:plot>
			</cewolf:combinedchart>

			<cewolf:img chartid="combinedChart" renderer="<%=basePath%>"
				width='<%=Integer.parseInt(LanguageUtil.get(
										pageContext, "chart.barwidth"))%>'
				height='<%=Integer.parseInt(LanguageUtil.get(
										pageContext, "chart.barheight"))%>' />
			<%
				} else {
			%>
			<cewolf:chart id="verticalBar"
				title='<%=LanguageUtil.get(pageContext,
											"allaccount.title")%>'
				type="<%=picType%>" yaxislabel="<%=yLabel%>">
				<cewolf:colorpaint
					color='<%=LanguageUtil.get(pageContext,
											"chart.bgcolor")%>' />
				<cewolf:data>
					<cewolf:producer id="allaccountstatChart" />
				</cewolf:data>
				<cewolf:chartpostprocessor id="dataColor">
					<cewolf:param name="0"
						value='<%=LanguageUtil.get(pageContext,
												"chart.customer1")%>' />
					<cewolf:param name="1"
						value='<%=LanguageUtil.get(pageContext,
												"chart.customer2")%>' />
					<cewolf:param name="2"
						value='<%=LanguageUtil.get(pageContext,
												"chart.customer3")%>' />
					<cewolf:param name="3"
						value='<%=LanguageUtil.get(pageContext,
												"chart.customer4")%>' />
					<cewolf:param name="4"
						value='<%=LanguageUtil.get(pageContext,
												"chart.customer5")%>' />
					<cewolf:param name="5"
						value='<%=LanguageUtil.get(pageContext,
												"chart.customer6")%>' />
				</cewolf:chartpostprocessor>

			</cewolf:chart>

			<cewolf:img chartid="verticalBar" renderer="<%=basePath%>"
				width='<%=Integer.parseInt(LanguageUtil.get(
										pageContext, "chart.barwidth"))%>'
				height='<%=Integer.parseInt(LanguageUtil.get(
										pageContext, "chart.barheight"))%>' />
			<%
				}
			%>
		</table>
	</c:if>
</html:form>
<script>
    function setQueryType(typevalue) {
        document.totsavingform.querytype.value = typevalue;
        document.totsavingform.action='/ext/allaccount';
        document.totsavingform.submit();
    }
</script>
