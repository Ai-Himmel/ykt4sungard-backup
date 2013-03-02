<%@ include file="/html/extportlet/advquery/init.jsp"%>

<%
	String querytype23 = "bydate";
	String queryType = ParamUtil.getString(request, "statType",
			querytype23);
%>

<html:form action="/ext/allconsume_queryresult" method="POST"
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
								onclick="javascript:setallconsumeformQueryType('bydate')"></html:radio>

							<bean:message key="query.bydate" />
							<html:radio property="statType" value="byweek"
								onclick="javascript:setallconsumeformQueryType('byweek')"></html:radio>

							<bean:message key="query.byweek" />
							<html:radio property="statType" value="bymonth"
								onclick="javascript:setallconsumeformQueryType('bymonth')"></html:radio>
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
											<html:text property="allconsume_begindate" styleId="allconsume_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'allconsume_begindate'})"
 /> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.enddate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="allconsume_enddate" styleId="allconsume_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'allconsume_enddate'})"
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
											<button onclick="document.allconsumeform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.allconsumeform.reset();">
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
											<html:text property="allconsume_begindate" readonly="true" styleId="allconsume_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'allconsume_begindate',dateFmt:'yyyy-MM'})"/> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.endmonth" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="allconsume_enddate" readonly="true" styleId="allconsume_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
												onclick="WdatePicker({el:'allconsume_enddate',dateFmt:'yyyy-MM'})" /> </a>
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
											<button onclick="document.allconsumeform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.allconsumeform.reset();">
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
										<td width="7%" nowrap="nowrap">
											<bean:message key="query.begindate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="allconsume_begindate" readonly="true" styleId="allconsume_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'allconsume_begindate'})"
 /> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.enddate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="allconsume_enddate" readonly="true" styleId="allconsume_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'allconsume_enddate'})"
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
											<button onclick="document.allconsumeform.submit();">
												<bean:message key="btn.query" />
											</button>
											<button onclick="document.allconsumeform.reset();">
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
			String dateRange = request.getAttribute("daterange")
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
						style="width:100%" requestURI="/ext/allconsume_queryresult"
						export="false">
						<display:column property="balance_date" title="<%=statTypeShow%>"></display:column>
						<display:column property="tradeamt"
							title="<%=LanguageUtil.get(pageContext,
											"allconsume.tradeamt")%>"
							format="{0,number,#,##0.00}"></display:column>
						<display:column property="mngamt"
							title="<%=LanguageUtil.get(pageContext,
											"allconsume.mngamt")%>"
							format="{0,number,#,##0.00}"></display:column>
						<display:column property="tradenum"
							title="<%=LanguageUtil.get(pageContext,
											"allconsume.tradenum")%>"></display:column>
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
											"allconsume.title")%>'
				type="combinedxy">
				<cewolf:colorpaint
					color='<%=LanguageUtil.get(pageContext,
											"chart.bgcolor")%>' />

				<cewolf:plot type="xyline" yaxislabel="<%=yLabel%>">
					<cewolf:data>
						<cewolf:producer id="allConsumeStatChart" />
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

				<cewolf:plot type="xyline" yaxislabel="<%=yLabel2%>">
					<cewolf:data>
						<cewolf:producer id="allConsumeStatChart2" />
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
											"allconsume.title")%>'
				type="<%=picType%>" yaxislabel="<%=yLabel%>">

				<cewolf:colorpaint
					color='<%=LanguageUtil.get(pageContext,
											"chart.bgcolor")%>' />
				<cewolf:data>
					<cewolf:producer id="allConsumeStatChart" />
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
		<script>
		    function setallconsumeformQueryType(typevalue) {
		        document.allconsumeform.querytype.value = typevalue;
		        document.allconsumeform.submit();
		    }
		</script>
</html:form>

