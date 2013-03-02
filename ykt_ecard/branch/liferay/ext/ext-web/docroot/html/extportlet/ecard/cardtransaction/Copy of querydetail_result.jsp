<%@ include file="/html/extportlet/ecard/cardtransaction/init.jsp"%>

<%
	ResultPage curpage = (ResultPage) request.getAttribute("result");
	List list = curpage.getList();
	SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>

<table width="100%" height="29" border="0" cellpadding="0"
	cellspacing="0">
	<tr>
		<td>
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td width="2%">
						&nbsp;
					</td>
					<td width="72%" class="text_blue_12_c">
						<bean:message key="ecard.queryresult" />
					</td>
					<td width="11%" valign="bottom">
						<table border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td width="13" align="right">
									<c:if test="<%=curpage.isPreviousPage()%>">
										<a href="javascript:goto('<%=curpage.getPage() - 1%>')"> <img
												align="middle"
												src="/html/extthemes/classic/images/ecard/left.gif"
												width="13" height="9" border="0"> </a>
									</c:if>
								</td>
								<td width="40" align="center" class="text_brown">
									<%=curpage.getPage() + 1%>/<%=curpage.getTotalPage()%></td>
								<td width="13">
									<c:if test="<%=curpage.isNextPage()%>">
										<a href="javascript:goto('<%=curpage.getPage() + 1%>')"> <img
												align="middle"
												src="/html/extthemes/classic/images/ecard/right.gif"
												width="13" height="9" border="0">
										</a>
									</c:if>
								</td>
							</tr>
						</table>
					</td>
					<td width="15%" align="right" valign="middle" nowrap
						class="text_brown">
						<bean:message key="ecard.goto" />
						<select name="select2"
							onchange="goto(this.options[this.selectedIndex].value)">
							<%
								for (int i = 1; i <= curpage.getTotalPage(); i++) {
							%>
							<option value="<%=i - 1%>"
								<c:if test="<%=i == (curpage.getPage() + 1)%>">
                	selected
                </c:if>><%=i%></option>
							<%
								}
							%>
						</select>
						<bean:message key="ecard.page" />
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td height="5"></td>
	</tr>
</table>
<table width="100%" border="0" cellspacing="0" cellpadding="0">

	<tr>
		<td>
			&nbsp;
		</td>
		<td valign="top">
			<!-- content table -->
			<html:form action="/ext/ecardtransactionquerydetail_result"
				method="POST"
				onsubmit="javascript:submitPortletForm(this); return false;">
				<html:hidden property="beginDate" />
				<html:hidden property="endDate" />
				<html:hidden property="cardId" />
				<html:hidden property="page" />


				<table width="100%" >
					<tr class="list_tr">
						<td align=left class="tableHeader"  >
							<bean:message
									key="ecardtransaction.tradetable.tradename" />
						</td>
						<td align=left class="tableHeader"  >
							<bean:message
									key="ecardtransaction.gatehistrade.devicename" />
						</td>
						<td align=left class="tableHeader"  >
							<bean:message
									key="ecardtransaction.tradetable.tradetime" />
						</td>
						<td align=right class="tableHeader"  >
							<bean:message
									key="ecardtransaction.tradetable.tradeamount" />
						</td>
						<td align=right class="tableHeader"  >
							<bean:message
									key="ecardtransaction.tradetable.balance" />
						</td>
					</tr>
					<%
						java.util.Iterator it = list.iterator();
						int count = 0;
						while (it.hasNext()) {
							HashMap detail = (HashMap) it.next();
							count++;
							int classId = count % 2 + 1;
					%>
					<tr class="tr_<%=classId%>">
						<td align=left>
							<a class=text_blue_12> <%=(String) detail.get("tradeName")%>
							</a>
						</td>
						<td align=left>
							<a class=text_blue_12> <%=(String) detail.get("tradePlace")%>
							</a>
						</td>
						<td align=left>
							<a class=text_blue_12> <%=(String) detail.get("tradeTime")%>
							</a>
						</td>
						<td align=right>
							<a class=text_blue_12> <%=(String) detail.get("tradeAmount")%>
							</a>
						</td>
						<td align=right>
							<a class=text_blue_12> <%=(String) detail.get("balance")%> </a>
						</td>
					</tr>
					<%
						}
					%>

				</table>
			</html:form>
			<!-- content table -->
		</td>
		<td>
		    
			&nbsp;
		</td>
	</tr>
</table>
<script>
function goto(page) {
	document.TradeDetailQueryForm.page.value = page;
	document.TradeDetailQueryForm.submit();
}
</script>