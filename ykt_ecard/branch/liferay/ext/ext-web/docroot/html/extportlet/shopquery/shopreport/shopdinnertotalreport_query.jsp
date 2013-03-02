<%@ include file="/html/extportlet/shopquery/init.jsp"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccBgInfoException"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccException"%>


  
<%
String shopdinnertotalreport_begindate = request.getAttribute("shopdinnertotalreport_begindate")==null?"":request.getAttribute("shopdinnertotalreport_begindate").toString();
String shopdinnertotalreport_enddate = request.getAttribute("shopdinnertotalreport_enddate")==null?"":request.getAttribute("shopdinnertotalreport_enddate").toString();
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
	
	<html:form action="/ext/shopdinnertotalreport_result" method="POST" 
		onsubmit="submitPortletForm(this); return false;">
		<table cellpadding="8" border=0 cellspacing="0" width="400" class="Noprint">
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
											<input type="text" name="shopdinnertotalreport_begindate" readonly="readonly"
												value="<%=shopdinnertotalreport_begindate %>" />
											<a href="#"><img
													src="/html/extthemes/classic/images/calendar/calendar.gif"
													border="0" id="f_trigger_shopdinnertotalreport_begindate"/> </a>
										</td>
										<td>
											<input type="text" name="shopdinnertotalreport_enddate" readonly="readonly"
												value="<%=shopdinnertotalreport_enddate %>" />
											<a href="#"><img
													src="/html/extthemes/classic/images/calendar/calendar.gif"
													border="0" id="f_trigger_shopdinnertotalreport_enddate"/> </a>
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
											<input type="button" onclick="javascript:shopdinnertotalreportvalidateAllData();"
												value="<bean:message key="shop.query.query" />">
											<input type="button" onclick="document.ShopDinnerTotalReportForm.reset();"
												value="<bean:message key="shop.query.reset" />">
											<input type="button" onclick="javascript:shopdinnertotalreportdoprintpreview();"
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
		<!--startprintshopdinnertotalreport_query.jsp-->
		<table border="0" cellpadding="0" cellspacing="0" width="100%" >
			<tr>
				<td>

					<ec:table var="shopdinnertotalreportpres" items="shopdinnertotalreportresult" filterable="false"
						imagePath="/html/extcommon/ximages/*.gif" 
						action="/ext/shopdinnertotalreport_result" form="ShopDinnerTotalReportForm" showPagination="false" autoIncludeParameters="false">
						<ec:row highlightRow="true" >
							<ec:column property="shopname" headerStyle="text-align:left"
								style="text-align:left" filterable="false" sortable="false"
								title="<%=LanguageUtil.get(pageContext, "shop.dinner.total.query.shopname")%>" width="20%" />								
							<ec:column property="transcnt1" headerStyle="text-align:right"				
								style="text-align:right" filterable="false" sortable="false"
								title='<%=LanguageUtil.get(pageContext, "shop.dinner.total.query.transcnt1")%>' width="6%"/>
							<ec:column property="transamt1" headerStyle="text-align:right"
                                cell="currency" format="###,###,###,##0.00"
                                style="text-align:right" filterable="false" sortable="false"
                                title='<%=LanguageUtil.get(pageContext, "shop.dinner.total.query.transamt1")%>' width="10%"/>
                            <ec:column property="transcnt2" headerStyle="text-align:right"              
                                style="text-align:right" filterable="false" sortable="false"
                                title='<%=LanguageUtil.get(pageContext, "shop.dinner.total.query.transcnt2")%>' width="6%"/>
                            <ec:column property="transamt2" headerStyle="text-align:right"
                                cell="currency" format="###,###,###,##0.00"
                                style="text-align:right" filterable="false" sortable="false"
                                title='<%=LanguageUtil.get(pageContext, "shop.dinner.total.query.transamt2")%>' width="10%"/>
                                <ec:column property="transcnt3" headerStyle="text-align:right"              
                                style="text-align:right" filterable="false" sortable="false"
                                title='<%=LanguageUtil.get(pageContext, "shop.dinner.total.query.transcnt3")%>' width="6%"/>
                            <ec:column property="transamt3" headerStyle="text-align:right"
                                cell="currency" format="###,###,###,##0.00"
                                style="text-align:right" filterable="false" sortable="false"
                                title='<%=LanguageUtil.get(pageContext, "shop.dinner.total.query.transamt3")%>' width="10%"/>
                                
                                <ec:column property="transcnt4" headerStyle="text-align:right"              
                                style="text-align:right" filterable="false" sortable="false"
                                title='<%=LanguageUtil.get(pageContext, "shop.dinner.total.query.transcnt4")%>' width="6%"/>
                            <ec:column property="transamt4" headerStyle="text-align:right"
                                cell="currency" format="###,###,###,##0.00"
                                style="text-align:right" filterable="false" sortable="false"
                                title='<%=LanguageUtil.get(pageContext, "shop.dinner.total.query.transamt4")%>' width="10%"/>
                                
                                <ec:column property="totalcnt" headerStyle="text-align:right"              
                                style="text-align:right" filterable="false" sortable="false"
                                title='<%=LanguageUtil.get(pageContext, "shop.dinner.total.query.totalcnt")%>' width="6%"/>
                            <ec:column property="totalamt" headerStyle="text-align:right"
                                cell="currency" format="###,###,###,##0.00"
                                style="text-align:right" filterable="false" sortable="false"
                                title='<%=LanguageUtil.get(pageContext, "shop.dinner.total.query.totalamt")%>' width="10%"/>
						</ec:row>

					</ec:table>
				</td>
			</tr>
		</table>
		<!--endprintshopdinnertotalreport_query.jsp-->
</html:form>
 <script language="JavaScript">
                    
                Calendar.setup({
                    inputField     :    "shopdinnertotalreport_begindate",     // id of the input field
                    button         :    "f_trigger_shopdinnertotalreport_begindate",  // trigger for the calendar (button ID)
                    align          :    "Bl",           // alignment (defaults to "Bl")
                    singleClick    :    true
                });
                
                Calendar.setup({
                    inputField     :    "shopdinnertotalreport_enddate",     // id of the input field
                    button         :    "f_trigger_shopdinnertotalreport_enddate",  // trigger for the calendar (button ID)
                    align          :    "Bl",           // alignment (defaults to "Bl")
                    singleClick    :    true
                });
            </script>
	<script>
function shopdinnertotalreportvalidateAllData() {
    if(document.ShopDinnerTotalReportForm.shopdinnertotalreport_begindate.value==""){
        alert("<%=LanguageUtil.get(pageContext, "shop.query.alert.nobegindate")%>");
        return false;
    }
    if(document.ShopDinnerTotalReportForm.shopdinnertotalreport_enddate.value==""){
        alert("<%=LanguageUtil.get(pageContext, "shop.query.alert.noenddate")%>");
        return false;
    }
    if(document.ShopDinnerTotalReportForm.shopid.value==""){
        alert("<%=LanguageUtil.get(pageContext, "shop.query.alert.shopnotselected")%>");
        return false;
    }
    document.ShopDinnerTotalReportForm.submit();
}

</script>

<script language="javascript">
function shopdinnertotalreportdoprintpreview()
{
bdhtml=window.document.body.innerHTML;
sprnstr="<!--startprintshopdinnertotalreport_query.jsp-->";
eprnstr="<!--endprintshopdinnertotalreport_query.jsp-->";
prnhtml=bdhtml.substr(bdhtml.indexOf(sprnstr)+48);
prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
window.document.body.innerHTML=prnhtml;
window.print();
}
</script>