<%@ include file="/html/extportlet/ecard/cardtransaction/init.jsp"%>

<link rel="stylesheet" type="text/css"
	href="/html/extcommon/styles/mystyle.css" />

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
<table width="100" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td height="5"></td>
	</tr>
</table>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td width="9" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_l_1.jpg"width="9" height="7"></td>
		<td height="7"background="/html/extthemes/classic/images/ecard/portlet/k_top.jpg"></td>
		<td width="6" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_r_1.jpg"width="6" height="7"></td>
	</tr>
	<tr>
		<td background="/html/extthemes/classic/images/ecard/portlet/k_l_2.jpg"></td>
		<td valign="top">
			<!-- content table -->
			<html:form action="/ext/ecardtransactionquerydetail_result"
				method="POST"
				onsubmit="javascript:submitPortletForm(this); return false;">
				<html:hidden property="beginDate" />
				<html:hidden property="endDate" />
				<html:hidden property="cardId" />
				<html:hidden property="page" />
				<html:hidden property="serialType" />


				<table width="100%" class="inside_table">
					<tr class="list_tr">
						<td align=left width="20%" class="text_blue_12_c">
							<bean:message key="ecardtransaction.tradetable.tradetime" />
						</td>
						<td align=left width="30%"  class="text_blue_12_c">
                            <bean:message key="ecardtransaction.tradetable.tradeplace" />
                        </td>
						<td align=left width="30%"  class="text_blue_12_c">
							<bean:message key="ecardtransaction.tradetable.tradename" />
						</td>	
						<td align=right width="20%"  class="text_blue_12_c">
							<bean:message key="ecardtransaction.tradetable.tradeamount" />
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
					<tr class="tr_<%=classId%>" style="font-size: x-small;">
						<td align=left class="text_blue_12">
							<%=(String) detail.get("tradeTime")%>
						</td>
						<td align=left class="text_blue_12">
                            <%=(String) detail.get("tradePlace")%>
                        </td>
						<td align=left class="text_blue_12">
							<%=(String) detail.get("tradeName")%>
						</td>						
						<td align=right class="text_blue_12">
							<%=(String) detail.get("tradeAmount")%>
						</td>
					</tr>
					<%
						}
					%>

				</table>
			</html:form>
			<!-- content table -->
		</td>
		<td background="/html/extthemes/classic/images/ecard/portlet/k_r_2.jpg"></td>
	</tr>
	<tr>
		<td width="9" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_l_3.jpg" width="9" height="7"></td>
		<td height="7" background="/html/extthemes/classic/images/ecard/portlet/k_foot.jpg"></td>
		<td width="6" height="7"><img src="/html/extthemes/classic/images/ecard/portlet/k_r_3.jpg"width="6" height="7"></td>
	</tr>
	 <tr>            
            <td align=right valign="bottom" colspan="3">
            	<html:button property="add" styleClass="button_blank" value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>' onclick="javascript:renderView();" />
              </td>            
          </tr>   
</table>

<script>
function goto(page) {
    document.TradeDetailQueryForm.page.value = page;
    document.TradeDetailQueryForm.submit();
}

function renderView() {
	self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ext/ecardtransactionview" /></portlet:renderURL>';
}
</script>