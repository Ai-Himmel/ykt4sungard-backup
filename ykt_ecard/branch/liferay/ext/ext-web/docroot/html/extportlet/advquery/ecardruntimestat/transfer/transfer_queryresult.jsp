<%@ include file="/html/extportlet/advquery/init.jsp"%>
<jsp:include page="transfer_query.jsp"></jsp:include>


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
			String yLabel = request.getAttribute("ylabel").toString();
		%>
		<%
			String picType = request.getAttribute("pictype").toString();
		%>
		<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td>
					<display:table name="result" pagesize="10" class="isis"
						style="width:100%" requestURI="/ext/transfer_queryresult"
						export="false">
						<display:column property="balance_date" title="<%=statTypeShow%>"></display:column>
						<display:column property="inaccount"
							title="<%=LanguageUtil.get(pageContext,
											"tranfer.inaccount")%>"></display:column>
						<display:column property="account"
							title="<%=LanguageUtil.get(pageContext,
											"tranfer.account")%>"></display:column>
						<display:column property="rate"
							title="<%=LanguageUtil.get(pageContext,
											"tranfer.rate")%>"
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
			<cewolf:chart id="line"
				title='<%=LanguageUtil.get(pageContext,
										"transfer.title")%>'
				type="<%=picType%>" yaxislabel="<%=yLabel%>">
				<cewolf:colorpaint
					color='<%=LanguageUtil
										.get(pageContext, "chart.bgcolor")%>' />
				<cewolf:data>
					<cewolf:producer id="transferChart" />
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
	<script>
    function settransferformQueryType(typevalue) {
        document.transferform.querytype.value = typevalue;
        document.transferform.submit();
    }
</script>

