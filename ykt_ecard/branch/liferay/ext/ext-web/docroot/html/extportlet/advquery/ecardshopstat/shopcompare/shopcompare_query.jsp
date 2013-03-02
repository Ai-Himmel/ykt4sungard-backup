<%@ include file="/html/extportlet/advquery/init.jsp"%>
<%
	String querytype23 = "bydate";
	String queryType = ParamUtil.getString(request, "statType",
			querytype23);
%>
<%
	String storeLimitString = ParamUtil.getString(request,
			"storeLimitString");
%>

<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.SHOPCOMPARE_ERROR_EXIST)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.SHOPCOMPARE_ERROR_EXIST, SessionErrors.get(
										request, EcardConstants.SHOPCOMPARE_ERROR_EXIST))%> </font>
</c:if>
<html:form action="/ext/shopcompare_queryresult" method="POST"
	onsubmit="submitPortletForm(this); return false;">

	<table width="100%" border="0" align="center" cellpadding="0"
		cellspacing="0">
		<tr>
			<td>
				<html:hidden property="querytype" />
				<input type=hidden name=storeLimitString
					value='<%=storeLimitString%>'>
				<table width="94%" border="0" align="center" cellpadding="0"
					cellspacing="0">
					<tr>
						<td nowrap="nowrap" width="50%">
							<bean:message key="query.type" />
							<html:radio property="statType" value="bydate"
								onclick="javascript:setQueryType('bydate')"></html:radio>
							<bean:message key="query.bydate" />
							<html:radio property="statType" value="bymonth"
								onclick="javascript:setQueryType('bymonth')"></html:radio>
							<bean:message key="query.bymonth" />
						</td>
						<TD nowrap="nowrap" align="left" width="50%">
							<bean:message key="showtitle.type" />
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
										<td width="8%" align="right" nowrap="nowrap">
											<bean:message key="query.begindate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="shopcompare_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'shopcompare_begindate'})"
													 /> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.enddate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="shopcompare_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'shopcompare_enddate'})"
													 /> </a>
										</td>
									

									</tr>
								</table>
							</td>
						</tr>
					</table>

					<table width="94%" border="0" align="center" cellpadding="0"
						cellspacing="0">
						<tr>
							<td>
								<%@ include file="/html/extportlet/advquery/ecardshopstat/shopcompare/shop_tree.jsp"%>
							</td>
						</tr>
					</table>
					<table width="98%" height="1" border="0" align="center"
						cellpadding="0" cellspacing="0">
						<tr>
							<td bgcolor="#e1e1e2"></td>
						</tr>
					</table>

					<table width="98%" height="5" border="0" align="center"
						cellpadding="0" cellspacing="0">
						<tr>
							<td></td>
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
											<bean:message key="shopcompare.tip" />
										</td>
										<td width="34%" align="center">
											<button onclick="javascript:setCmdValue('query');">
												<bean:message key="btn.query" />
											</button>
											<button onclick="javascript:renderCancelPage();">
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
										<td width="8%" align="right" nowrap="nowrap">
											<bean:message key="query.beginmonth" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="shopcompare_begindate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'shopcompare_begindate',dateFmt:'yyyy-MM'})"/> </a>
										</td>
										<td width="8%" nowrap="nowrap">
											<bean:message key="query.enddate" />
										</td>
										<td width="20%" nowrap="nowrap">
											<html:text property="shopcompare_enddate"></html:text>
										</td>
										<td width="20%" nowrap="nowrap">
											<a href="#"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'shopcompare_enddate',dateFmt:'yyyy-MM'})"
													/> </a>
										</td>

										

									</tr>
								</table>
							</td>
						</tr>
					</table>
					<table width="94%" border="0" align="center" cellpadding="0"
						cellspacing="0">
						<tr>
							<td>
								<%@ include file="/html/extportlet/advquery/ecardshopstat/shopcompare/shop_tree.jsp"%>
							</td>
						</tr>
					</table>
					<table width="98%" height="1" border="0" align="center"
						cellpadding="0" cellspacing="0">
						<tr>
							<td bgcolor="#e1e1e2"></td>
						</tr>
					</table>

					<table width="98%" height="5" border="0" align="center"
						cellpadding="0" cellspacing="0">
						<tr>
							<td></td>
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
											<bean:message key="shopcompare.tip" />
										</td>
										<td width="34%" align="center">
											<button onclick="javascript:setCmdValue('query');">
												<bean:message key="btn.query" />
											</button>
											<button onclick="javascript:renderCancelPage();">
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
</html:form>

