<%@ include file="/html/extportlet/advquery/init.jsp"%>
<jsp:include page="cardusebydept_query.jsp"></jsp:include>
<%List result = (List) request.getAttribute("result");%>
<%String deptName = request.getAttribute("deptname").toString();
   
%>
<%
			String basePath = request.getScheme() + "://"
						+ request.getServerName() + ":" + request.getServerPort()
						+ "/delegate/cewolf";
%>
<c:if test='<%=request.getAttribute("result") != null%>'>

<table border="0"  cellpadding="0"  cellspacing="0"  width="100%">
<tr><td>

<display:table name="result" pagesize="20" class="isis"
						style="width:100%" requestURI="/ext/cardusebydept_queryresult"
						export="false">
			<display:column property="deptname"
			     title="<%=LanguageUtil.get(pageContext, "title.deptname")%>"></display:column>
			<display:column property="cardtypename"
			     title="<%=LanguageUtil.get(pageContext, "carduseby.dictcaption")%>"></display:column>
			<display:column property="cardnum"
							title="<%=LanguageUtil.get(pageContext, "carduseby.num")%>"></display:column>
							
</display:table>			
</td></tr></table>
<table>
	<cewolf:chart id="verticalBar"
		title='<%=deptName+LanguageUtil.get(pageContext, "cardusedby.title")%>'

				type="verticalBar3D" >
		<cewolf:colorpaint
			color='<%=LanguageUtil.get(pageContext, "chart.bgcolor")%>' />
		<cewolf:data>
			<cewolf:producer id="cardUseStatByDept" />
		</cewolf:data>

         <cewolf:chartpostprocessor id="dataColor">
					<cewolf:param name="0"
						value='<%=LanguageUtil.get(pageContext, "chart.customer1")%>' />
					<cewolf:param name="1"
						value='<%=LanguageUtil.get(pageContext, "chart.customer2")%>' />
					<cewolf:param name="2"
						value='<%=LanguageUtil.get(pageContext, "chart.customer3")%>' />
					<cewolf:param name="3"
						value='<%=LanguageUtil.get(pageContext, "chart.customer4")%>' />
					<cewolf:param name="4"
						value='<%=LanguageUtil.get(pageContext, "chart.customer5")%>' />
					<cewolf:param name="5"
						value='<%=LanguageUtil.get(pageContext, "chart.customer6")%>' />
				</cewolf:chartpostprocessor>
	</cewolf:chart>

 <cewolf:img chartid="verticalBar" renderer="<%=basePath%>"
				width='<%=Integer.parseInt(LanguageUtil.get(pageContext,
							"chart.barwidth"))%>'
				height='<%=Integer.parseInt(LanguageUtil.get(pageContext,
							"chart.barheight"))%>' />

</table>
</c:if>