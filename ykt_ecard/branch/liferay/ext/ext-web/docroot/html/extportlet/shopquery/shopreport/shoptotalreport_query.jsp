<%@ include file="/html/extportlet/shopquery/init.jsp"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccBgInfoException"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccException"%>
  
<%
	String shoptotalreport_begindate = request
			.getAttribute("shoptotalreport_begindate") == null ? ""
			: request.getAttribute("shoptotalreport_begindate").toString();
	String shoptotalreport_enddate = request
			.getAttribute("shoptotalreport_enddate") == null ? "" : request
			.getAttribute("shoptotalreport_enddate").toString();
%>

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
<html:form action="/ext/shoptotalreport_result" method="POST"
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
										&nbsp;
									</td>
									<td>
										&nbsp;
									</td>

								</tr>
								<tr>
									<td nowrap="nowrap">
										<select name="shopid" style="">
											<%
												if (request.getSession().getAttribute(WebKeys.USER_ID) != null
														&& !"".equals(request.getSession().getAttribute(
																WebKeys.USER_ID))) {
													Long realUserId = (Long) request.getSession().getAttribute(
															WebKeys.USER_ID);
													List shoplist = ShopServiceUtil.getShopList(realUserId);
													long shopId = -1;
													if (null != request.getAttribute("shopid")
															&& !"".equals(request.getAttribute("shopid"))) {
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
									<td nowrap="nowrap">

									</td>
								</tr>
								<tr>
									<td>
										<bean:message key="shop.query.begindate" />
									</td>

									<td>
										<bean:message key="shop.query.enddate" />
									</td>
									<td>
										<bean:message key="shop.query.shoplevel" />
									</td>
								</tr>

								<tr>
									<td>
										<input type="text" name="shoptotalreport_begindate"
											id="shoptotalreport_begindate" value="<%=shoptotalreport_begindate%>" />
										<a href="#"><img
												src="/html/extthemes/classic/images/calendar/calendar.gif"
												border="0" id="f_trigger_shoptotalreport_begindate" /> </a>
									</td>
									<td>
										<input type="text" name="shoptotalreport_enddate"
											id="shoptotalreport_enddate" value="<%=shoptotalreport_enddate%>" />
										<a href="#"><img
												src="/html/extthemes/classic/images/calendar/calendar.gif"
												border="0" id="f_trigger_shoptotalreport_enddate" /> </a>
									</td>
									<td>
										<select name="shoplevel" style="">
											<%
												int shoplevel = 1;
												if (null != request.getAttribute("shoplevel")
														&& !"".equals(request.getAttribute("shoplevel"))) {
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
		<tr>
			<td>
				<table border="0" align="center" cellpadding="0" cellspacing="0"
					width="100%">
					<tr>
						<td>
							<table border="0" align="center" cellpadding="0" cellspacing="0"
								width="100%">
								<tr>
									<td width="100%" align="right" colspan="2">
										<input type="button"
											onclick="javascript:shoptotalreportvalidateAllData();"
											value="<bean:message key="shop.query.query" />">
										<input type="button"
											onclick="document.ShopTotalReportForm.reset();"
											value="<bean:message key="shop.query.reset" />">
										<input type="button"
											onclick="javascript:shoptotalreportdoprintpreview();"
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

	<!--startprintshoptotalreport_query.jsp-->
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>

				<ec:table var="shoptotalpres" items="shoptotalreportresult"
					filterable="false" imagePath="/html/extcommon/ximages/*.gif"
					action="/ext/shoptotalreport_result" form="ShopTotalReportForm"
					showPagination="false" autoIncludeParameters="false">
					<ec:row highlightRow="true">
						<ec:column property="shopname" headerStyle="text-align:left"
							filterable="false" sortable="false" escapeAutoFormat="true"
							title="<%=LanguageUtil.get(pageContext,
									"shop.query.shopname")%>"
							width="40%" />
						<ec:column property="transcnt" headerStyle="text-align:right"
							style="text-align:right" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext,
									"shop.query.tradecnt")%>'
							width="15%" />
						<ec:column property="num" headerStyle="text-align:right"
							cell="currency" format="###,###,###,##0"
							style="text-align:right" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext, "shop.catalog.query.times")%>'
							width="10%" />
						<ec:column property="dramt" headerStyle="text-align:right"
							cell="currency" format="###,###,###,##0.00"
							style="text-align:right" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext, "shop.query.income")%>'
							width="15%" />
						<ec:column property="cramt" headerStyle="text-align:right"
							cell="currency" format="###,###,###,##0.00"
							style="text-align:right" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext, "shop.query.pay")%>'
							width="10%" />
						<ec:column property="damt3" headerStyle="text-align:right"
							cell="currency" format="###,###,###,##0.00"
							style="text-align:right" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext, "shop.query.account")%>' 
							width="10%" />
					</ec:row>

				</ec:table>
			</td>
		</tr>
	</table>
	<!--endprintshoptotalreport_query.jsp-->
</html:form>
<script language="JavaScript">                                        
    Calendar.setup({
        inputField     :    "shoptotalreport_begindate",     // id of the input field
        button         :    "f_trigger_shoptotalreport_begindate",  // trigger for the calendar (button ID)
        align          :    "Bl",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    
    Calendar.setup({
        inputField     :    "shoptotalreport_enddate",     // id of the input field
        button         :    "f_trigger_shoptotalreport_enddate",  // trigger for the calendar (button ID)
        align          :    "Bl",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
</script>
<script>
function shoptotalreportvalidateAllData() {
    if(document.ShopTotalReportForm.shoptotalreport_begindate.value==""){
        alert("<%=LanguageUtil.get(pageContext,
							"shop.query.alert.nobegindate")%>");
        return false;
    }
    if(document.ShopTotalReportForm.shoptotalreport_enddate.value==""){
        alert("<%=LanguageUtil.get(pageContext,
							"shop.query.alert.noenddate")%>");
        return false;
    }
    if(document.ShopTotalReportForm.shopid.value==""){
        alert("<%=LanguageUtil.get(pageContext,
							"shop.query.alert.shopnotselected")%>");
        return false;
    }
    document.ShopTotalReportForm.submit();
}

</script>

<script language="javascript">
function shoptotalreportdoprintpreview()
{
bdhtml=window.document.body.innerHTML;
sprnstr="<!--startprintshoptotalreport_query.jsp-->";
eprnstr="<!--endprintshoptotalreport_query.jsp-->";
prnhtml=bdhtml.substr(bdhtml.indexOf(sprnstr)+42);
prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
window.document.body.innerHTML=prnhtml;
window.print();
}
</script>