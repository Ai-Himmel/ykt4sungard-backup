<%@ include file="/html/extportlet/advquery/init.jsp"%>
<jsp:include page="devuserate_query.jsp"></jsp:include>


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
						export="false">
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
	<script>
    function setdevuserateformQueryType(typevalue) {
        document.devuserateform.querytype.value = typevalue;
        document.devuserateform.submit();
    }
</script>

