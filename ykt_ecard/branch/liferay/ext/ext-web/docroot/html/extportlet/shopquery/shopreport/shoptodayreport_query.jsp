<%@ include file="/html/extportlet/shopquery/init.jsp"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccBgInfoException"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccException"%>
	
<c:if test="<%= SessionErrors.contains(request,EcardConstants.TIME_PERIOD_TOO_LONG) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="shop_time_period_too_long"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.SHOPID_NOT_SELECTED) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="shopid_not_select"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.DATE_NOT_SELECTED) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="date_not_selected"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,BccBgInfoException.class.getName()) %>">
<font class="portlet-msg-info">
    <%=LanguageUtil.format(pageContext, EcardConstants.ERROR_EXIST,((BccBgInfoException)SessionErrors.get(request,BccBgInfoException.class.getName())).getMessage()) %>
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,BccException.class.getName()) %>">
<font class="portlet-msg-info">
    <%= LanguageUtil.format(pageContext, EcardConstants.ERROR_EXIST,((BccException)SessionErrors.get(request,BccException.class.getName())).getMessage()) %>
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,Exception.class.getName()) %>">
<font class="portlet-msg-error">
    <%= LanguageUtil.format(pageContext, EcardConstants.ERROR_EXIST,((Exception)SessionErrors.get(request,Exception.class.getName())).getMessage()) %>
 </font>
</c:if>
	<html:form action="/ext/shoptodayreport_result" method="POST" 
		onsubmit="submitPortletForm(this); return false;">
		<table cellpadding="8" border=0 cellspacing="0" width="400">
			<tr>
				<td>
					<table border="0" align="left" cellpadding="0" cellspacing="0"
						width="100%">
						<tr>
							<td height="40">
								<table border="0" align="left" cellpadding="0" cellspacing="0"
									width="100%">
									<tr>
										<td>
											<bean:message key="shop.query.rootshop" />
										</td>

										<td>
											<bean:message key="shop.query.shoplevel" />
										</td>

									</tr>
									<tr>
										<td nowrap="nowrap">
											<select name="shopid" style="" >
												<%
												    if(request.getSession().getAttribute(
                                                            WebKeys.USER_ID)!=null&&!"".equals(request.getSession().getAttribute(
                                                            WebKeys.USER_ID))){
													Long realUserId = (Long) request.getSession().getAttribute(
															WebKeys.USER_ID);
													List shoplist = ShopServiceUtil.getShopList(realUserId);
													long shopId = -1;
													if (null != request.getAttribute("shopid")&&!"".equals(request.getAttribute("shopid"))) {
														shopId = Long.parseLong(request.getAttribute("shopid")
																.toString());
													}
													Iterator iter = shoplist.iterator();
													while (iter.hasNext()) {
														TShop tshop = (TShop) iter.next();
														if (shopId == tshop.getShopid()) {
												%>
												<option value="<%=tshop.getShopid()%>" selected="selected"><%=tshop.getShopname()%></option>

												<%
													} else {
												%>
												<option value="<%=tshop.getShopid()%>"><%=tshop.getShopname()%></option>
												<%
													}
													}
													}
												%>
											</select>
										</td>
										<td>
                                            <select name="shoplevel" style="">
                                                <%
                                                    int shoplevel = 1;
                                                    if (null != request.getAttribute("shoplevel")&&!"".equals(request.getAttribute("shoplevel"))) {
                                                        shoplevel = Integer.parseInt(request.getAttribute("shoplevel")
                                                                .toString());
                                                    }
                                                    for (int i = 1; i <= 5; i++) {
                                                        if (shoplevel == i) {
                                                %>
                                                <option value="<%=i%>" selected="selected">
                                                    <bean:message key="shop.query.number" /><%=i%><bean:message
                                                        key="shop.query.level" />
                                                </option>
                                                <%
                                                    } else {
                                                %>
                                                <option value="<%=i%>">
                                                    <bean:message key="shop.query.number" /><%=i%><bean:message
                                                        key="shop.query.level" />
                                                </option>
                                                <%
                                                    }
                                                    }
                                                %>
                                            </select>
                                        </td>
			
									</tr>


								</table>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td>
					&nbsp;
				</td>
			</tr>
			<tr >
				<td>
					<table border="0" align="center" cellpadding="0" cellspacing="0"
						width="100%">
						<tr>
							<td>
								<table border="0" align="center" cellpadding="0" cellspacing="0"
									width="100%">
									<tr>
										<td width="100%" align="right" colspan="2">
											<input type="button" onclick="javascript:shoptodayreportvalidateAllData();"
												value="<bean:message key="shop.query.query" />">
											<input type="button" onclick="document.ShopTodayReportForm.reset();"
												value="<bean:message key="shop.query.reset" />">
											<input type="button" onclick="javascript:shoptodayreportdoprintpreview();"
                                                value="<bean:message key="shop.query.print" />">	

										</td>
									</tr>
								</table>
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>

		<!--startprintshoptodayreport_query.jsp-->
		<table border="0" cellpadding="0" cellspacing="0" width="100%" >
			<tr>
				<td>

					<ec:table var="shoptodaydinnerpres" items="shoptodaydinnerresult" filterable="false"
						imagePath="/html/extcommon/ximages/*.gif" 
						action="/ext/shoptodayreport_result" form="ShopTodayReportForm" showPagination="false" autoIncludeParameters="false">
						<ec:row highlightRow="true" >
							<ec:column property="shopname" headerStyle="text-align:left"
								style="text-align:left" filterable="false" sortable="false"
								title="<%=LanguageUtil.get(pageContext, "shop.query.shopname")%>" width="25%" />
							<ec:column property="summary" headerStyle="text-align:left"
								style="text-align:left" filterable="false" sortable="false"
								title='<%=LanguageUtil.get(pageContext, "shop.query.summary")%>' width="30%"/>
							<ec:column property="transcnt" headerStyle="text-align:right"
								style="text-align:right" filterable="false" sortable="false"
								title='<%=LanguageUtil.get(pageContext, "shop.query.tradecnt")%>' width="10%"/>
							<ec:column property="cramt" headerStyle="text-align:right"
								cell="currency" format="###,###,###,##0.00"
								style="text-align:right" filterable="false" sortable="false"
								title='<%=LanguageUtil.get(pageContext, "shop.query.income")%>' width="10%"/>
							<ec:column property="dramt" headerStyle="text-align:right"
								cell="currency" format="###,###,###,##0.00"
								style="text-align:right" filterable="false" sortable="false"
								title='<%=LanguageUtil.get(pageContext, "shop.query.pay")%>' width="10%"/>
							<ec:column property="damt3" headerStyle="text-align:right"
								cell="currency" format="###,###,###,##0.00"
								style="text-align:right" filterable="false" sortable="false"
								title='<%=LanguageUtil.get(pageContext, "shop.query.account")%>' />
						</ec:row>

					</ec:table>
				</td>
			</tr>
		</table>
		<!--endprintstartshoptodayreport_query.jsp-->
</html:form>

	<script>
function shoptodayreportvalidateAllData() {
    if(document.ShopTodayReportForm.shopid.value==""){
        alert("<%=LanguageUtil.get(pageContext, "shop.query.alert.shopnotselected")%>");
        return false;
    }
    document.ShopTodayReportForm.submit();
}

</script>

<script language="javascript">
function shoptodayreportdoprintpreview()
{
bdhtml=window.document.body.innerHTML;
sprnstr="<!--startprintstartshoptodayreport_query.jsp-->";
eprnstr="<!--endprintstartshoptodayreport_query.jsp-->";
prnhtml=bdhtml.substr(bdhtml.indexOf(sprnstr)+47);
prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
window.document.body.innerHTML=prnhtml;
window.print();
}
</script>