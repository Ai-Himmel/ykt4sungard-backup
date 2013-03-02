<%@ include file="/html/extportlet/advquery/init.jsp"%>
<jsp:include page="photo_query.jsp"></jsp:include>

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
			String cutType = request.getAttribute("cuttype").toString();
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
						<display:column property="photo_date" title="<%=statTypeShow%>"></display:column>
						<display:column property="photonum"
							title="<%=LanguageUtil
											.get(pageContext, "photo.num")%>"></display:column>
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
			<cewolf:chart id="verticalBar"
				title='<%=LanguageUtil.get(pageContext, "photo.title")%>'
				type="verticalBar" yaxislabel="<%=yLabel%>">
				<cewolf:colorpaint
					color='<%=LanguageUtil
										.get(pageContext, "chart.bgcolor")%>' />
				<cewolf:data>
					<cewolf:producer id="photoChart" />
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
				width='<%=Integer.parseInt(LanguageUtil.get(pageContext,
									"chart.barwidth"))%>'
				height='<%=Integer.parseInt(LanguageUtil.get(pageContext,
									"chart.barheight"))%>' />
		</table>
	</c:if>
	<script>
    function setphotoformQueryType(typevalue) {
        document.photoform.querytype.value = typevalue;
        document.photoform.submit();
    }
</script>

