<%@ include file="/html/extportlet/advquery/init.jsp"%>
<jsp:include page="allaccount_query.jsp"></jsp:include>

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
						export="false">
						<display:column property="balance_date" title="<%=statTypeShow%>"></display:column>
						<display:column property="saving"
							title="<%=LanguageUtil.get(pageContext,
											"allaccount.saving")%>"
							format="{0,number,#,##0.00}"></display:column>
						<display:column property="consume"
							title="<%=LanguageUtil.get(pageContext,
											"allaccount.consume")%>"
							format="{0,number,#,##0.00}"></display:column>
						<display:column property="ensure"
							title="<%=LanguageUtil.get(pageContext,
											"allaccount.ensure")%>"
							format="{0,number,#,##0.00}"></display:column>
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
				type="combinedxy" antialias="false">
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
				type="<%=picType%>" yaxislabel="<%=yLabel%>" antialias="false">
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
	<script>
    function setallaccountformQueryType(typevalue) {
        document.allaccountform.querytype.value = typevalue;
        document.allaccountform.submit();
    }
</script>


