<%@ include file="/html/extportlet/advquery/init.jsp"%>
<jsp:include page="accounttransdtl_query.jsp"></jsp:include>
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
					<display:table name="result" pagesize="20" class="isis"
						style="width:100%" requestURI="/ext/accounttransdtl_queryresult"
						export="false">
						<display:column property="transdate"
							title="<%=LanguageUtil.get(pageContext,
											"oneaccount.detail.date")%>"></display:column>
						<display:column property="transtime"
							title="<%=LanguageUtil.get(pageContext,
											"oneaccount.detail.time")%>"></display:column>
						<display:column property="custid"
							title="<%=LanguageUtil.get(pageContext,
											"title.custId")%>"></display:column>
						<display:column property="custname"
							title="<%=LanguageUtil.get(pageContext,
											"title.name")%>"></display:column>	
						<display:column property="TRANSNAME"
							title="<%=LanguageUtil.get(pageContext,
											"title.transtype")%>"></display:column>							
						<display:column property="cardbefbal"
							title="<%=LanguageUtil.get(pageContext,
											"title.cardbefmoney")%>"></display:column>	
						<display:column property="amount"
							title="<%=LanguageUtil.get(pageContext,
											"title.cardamount")%>"></display:column>											
						<display:column property="cardaftbal"
							title="<%=LanguageUtil.get(pageContext,
											"title.cardaftmoney")%>"></display:column>	
									
					</display:table>
				</td>
			</tr>
		</table>
</c:if>


