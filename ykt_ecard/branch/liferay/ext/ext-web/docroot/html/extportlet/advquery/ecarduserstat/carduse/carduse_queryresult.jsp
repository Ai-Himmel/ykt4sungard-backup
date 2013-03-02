<%@ include file="/html/extportlet/advquery/init.jsp"%>
<jsp:include page="carduse_query.jsp"></jsp:include>

<%
				String basePath = request.getScheme() + "://"
								+ request.getServerName() + ":"
								+ request.getServerPort() + "/delegate/cewolf";
%>

<%List result = (List) request.getAttribute("result");%>
<c:if test='<%=request.getAttribute("result") != null%>'>
<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td>
					<display:table name="result" pagesize="10" class="isis"
						style="width:100%" requestURI="/ext/carduse_queryresult"
						export="false">
						<display:column property="typename"
							title="<%=LanguageUtil.get(pageContext,
											"carduse.cardtype")%>"></display:column>
						<display:column property="cardnum"
							title="<%=LanguageUtil.get(pageContext,
											"carduse.num")%>"></display:column>
						<display:column property="rate"
							title="<%=LanguageUtil.get(pageContext,
											"carduse.prop")%>"></display:column>
						
					</display:table>
				</td>
			</tr>
		</table>
<table>
<cewolf:chart 
	id="verticalBar" 
	title='<%= LanguageUtil.get(pageContext,"carduse.title")%>'
	type="verticalBar3D"> 
	             
	<cewolf:colorpaint color='<%=LanguageUtil.get(pageContext, "chart.bgcolor")%>'/>
	<cewolf:data>
		<cewolf:producer id="cardUseVBarData" />
	</cewolf:data>
    <cewolf:chartpostprocessor id="dataColor">
        <cewolf:param name="0" value='<%=LanguageUtil.get(pageContext,"chart.customer1")%>' />
        <cewolf:param name="1" value='<%=LanguageUtil.get(pageContext,"chart.customer2")%>' />
        <cewolf:param name="2" value='<%=LanguageUtil.get(pageContext,"chart.customer3")%>' />
        <cewolf:param name="3" value='<%=LanguageUtil.get(pageContext,"chart.customer4")%>' />
        <cewolf:param name="4" value='<%=LanguageUtil.get(pageContext,"chart.customer5")%>' />
        <cewolf:param name="5" value='<%=LanguageUtil.get(pageContext,"chart.customer6")%>' />
    </cewolf:chartpostprocessor>

</cewolf:chart>

<cewolf:img 
	chartid="verticalBar" 
	renderer="<%=basePath%>" 
	width='<%=Integer.parseInt(LanguageUtil.get(pageContext,
									"chart.barwidth"))%>'
				height='<%=Integer.parseInt(LanguageUtil.get(pageContext,
									"chart.barheight"))%>' />

<cewolf:chart id="pieChart"
    title='<%= LanguageUtil.get(pageContext,"cardues.scale")%>'
	type="pie">
	<cewolf:colorpaint
	    color='<%=LanguageUtil.get(pageContext, "chart.bgcolor")%>'
		 />
		<cewolf:data>
			<cewolf:producer id="cardUsePieData" />
		</cewolf:data>
		<cewolf:chartpostprocessor id="dataColorPie">
		</cewolf:chartpostprocessor>
	</cewolf:chart>

	<cewolf:img chartid="pieChart" renderer="<%=basePath%>"
	width='<%=Integer.parseInt(LanguageUtil.get(pageContext,
									"chart.barwidth"))%>'
	height='<%=Integer.parseInt(LanguageUtil.get(pageContext,
									"chart.barheight"))%>' />
	
</table>
</c:if>