<%@ include file="/html/extportlet/advquery/init.jsp"%>
<jsp:include page="shopcompare_query.jsp"></jsp:include>

	<c:if test='<%=request.getAttribute("result") != null%>'>
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
		<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td>
					<display:table name="result" pagesize="10" class="isis"
						style="width:100%" requestURI="/ext/shopcompare_queryresult"
						export="false">
						<display:column property="shopid"
							title="<%=LanguageUtil.get(pageContext,
											"shopcompare.shopid")%>"></display:column>
						<display:column property="shopname"
							title="<%=LanguageUtil.get(pageContext,
											"shopcompare.shopname")%>"></display:column>
						<display:column property="tradenum"
							title="<%=LanguageUtil.get(pageContext,
											"shopcompare.tradenum")%>"></display:column>
						<display:column property="tradeamt"
							title="<%=LanguageUtil.get(pageContext,
											"shopcompare.tradeamt")%>"
							format="{0,number,0,000.00}"></display:column>
						<display:column property="mngamt"
							title="<%=LanguageUtil.get(pageContext,
											"shopcompare.mngamt")%>"
							format="{0,number,0,000.00}"></display:column>
						<display:column property="totalamt"
							title="<%=LanguageUtil.get(pageContext,
											"shopcompare.totalamt")%>"
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
			<cewolf:chart id="verticalBar"
				title='<%=LanguageUtil.get(pageContext,
										"shopcompare.title")%>'
				type="<%=picType%>" yaxislabel="<%=yLabel%>">
				<cewolf:colorpaint
					color='<%=LanguageUtil
										.get(pageContext, "chart.bgcolor")%>' />
				<cewolf:data>
					<cewolf:producer id="shopCompareData" />
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

		<table width="98%" border="0" align="center" cellpadding="0"
			cellspacing="0" bgcolor="#f8f8f8">
			<tr>
				<td height="30">
					<table width="96%" border="0" align="center" cellpadding="0"
						cellspacing="0">
						<tr>
							<td width="85%" class="red_text"></td>
							<td width="15%" align="center">
								<button onclick="javascript:renderCancelPage();">
									<bean:message key="btn.return" />
								</button>
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
	</c:if>

	<script>
    function setQueryType(typevalue) {
        document.shopcompareform.querytype.value = typevalue;
        document.shopcompareform.submit();
    }
</script>
<script>
      	function setCmdValue(cmd) {      		
      		var childs = document.all;
      		var storelimit = '';
      		for (var i = 0; i < childs.length; i++) {
      			var element = childs.item(i);      			

      			if (element.type == 'checkbox' &&       				
      				element.id.indexOf('box') == 0 &&
      				element.checked) {      				
      				storelimit = storelimit + element.value + ',';
				}
      		}
      		if (storelimit.length != 0) {
      			storelimit = storelimit.substring(0, storelimit.length -1);
      		}
      		document.shopcompareform.storeLimitString.value = storelimit;
      		document.shopcompareform.submit();
      	}
      	function renderCancelPage() {
        document.shopcompareform.action='/ext/shopcompare';
        document.shopcompareform.submit();
	}
	//inital tree select status
	
</script>

