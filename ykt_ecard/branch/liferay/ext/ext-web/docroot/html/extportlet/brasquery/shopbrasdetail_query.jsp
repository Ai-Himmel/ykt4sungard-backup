<%@ include file="/html/extportlet/shopquery/init.jsp"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccException"%>
<%@page
	import="com.kingstargroup.ecard.exceptions.BccResultToomuchException"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccBgInfoException"%>

<c:if
	test="<%=SessionErrors.contains(request,
							EcardConstants.NET_TRANS_ERROR_OCCURANCE)%>">
	<font class="portlet-msg-error"> <liferay-ui:message
			key="net_trans_error_occurance" /> </font>
</c:if>

<c:if
	test="<%=SessionErrors.contains(request,
							EcardConstants.DATE_NOT_SELECTED)%>">
	<font class="portlet-msg-error"> <liferay-ui:message
			key="date_not_selected" /> </font>
</c:if>
<c:if
	test="<%=SessionErrors.contains(request, BccBgInfoException.class
							.getName())%>">
	<font class="portlet-msg-info"> <%=LanguageUtil.format(pageContext,
							EcardConstants.ERROR_EXIST,
							((BccBgInfoException) SessionErrors.get(request,
									BccBgInfoException.class.getName()))
									.getMessage())%> </font>
</c:if>
<c:if
	test="<%=SessionErrors.contains(request, BccException.class
							.getName())%>">
	<font class="portlet-msg-info"> <%=LanguageUtil
							.format(pageContext, EcardConstants.ERROR_EXIST,
									((BccException) SessionErrors.get(request,
											BccException.class.getName()))
											.getMessage())%> </font>
</c:if>
<c:if
	test="<%=SessionErrors
							.contains(request, Exception.class.getName())%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
							EcardConstants.ERROR_EXIST,
							((Exception) SessionErrors.get(request,
									Exception.class.getName())).getMessage())%> </font>
</c:if>
<html:form action="/ext/shopbrasdetail_result" method="POST"
	onsubmit="submitPortletForm(this); return false;">
	<table cellpadding="8" border=0 cellspacing="0" width="500">
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
										<bean:message key="shop.bras.detail.query.bras_begindate" />
									</td>

									<td>
										<bean:message key="shop.bras.detail.query.bras_enddate" />
									</td>
									<td>
										&nbsp;
									</td>
								</tr>

								<tr>
									<td>
										<html:text property="bras_begindate" />
										<a href="#"><img
												src="/html/extthemes/classic/images/calendar/calendar.gif"
												border="0" id="f_trigger_bras_begindate" /> </a>
									</td>
									<td>
										<html:text property="bras_enddate" />
										<a href="#"><img
												src="/html/extthemes/classic/images/calendar/calendar.gif"
												border="0" id="f_trigger_bras_enddate" /> </a>
									</td>
									<td>
										&nbsp;
									</td>
									<td>
                                        &nbsp;
                                    </td>
								</tr>

                                <tr>
                                    <td>
                                        <bean:message key="shop.bras.detail.query.refno" />
                                    </td>

                                    <td>
                                       <bean:message key="shop.bras.detail.query.stuempno" /> 
                                    </td>
                                    <td>
                                       <bean:message key="shop.bras.detail.query.custname" />
                                    </td>
                                    <td>
                                        &nbsp;
                                    </td>
                                </tr>

                                <tr>
                                    <td>
                                        <html:text property="refno" />
                                    </td>
                                    <td>
                                       <html:text property="stuempno" /> 
                                    </td>
                                    <td>
                                        <html:text property="custname" />
                                    </td>
                                    <td>
                                        &nbsp;
                                    </td>
                                </tr>

								<tr>
									<td>
										<bean:message key="shop.bras.detail.query.oppaccno" />
									</td>

									<td>
										<bean:message key="shop.bras.detail.query.oppaccname" />
									</td>
									<td>
										<bean:message key="shop.bras.detail.query.status" />
									</td>
									<td>
                                        <bean:message key="shop.bras.detail.query.brastype" />
                                    </td>
								</tr>

								<tr>
									<td>
										<html:text property="oppaccno" />
									</td>
									<td>
										<html:text property="oppaccname" />
									</td>
									<td>
										<html:select property="status">
                                            <html:option value="-">-</html:option>
                                            <html:option value="0">
                                                <bean:message key="shop.bras.detail.query.status.success" />
                                            </html:option>
                                            <html:option value="1">
                                                <bean:message key="shop.bras.detail.query.status.failure" />
                                            </html:option>
                                        </html:select>
									</td>
									<td>
                                       <html:select property="brastype">
                                            <html:option value="-">-</html:option>
                                            <html:option value="0">
                                                <bean:message key="shop.bras.detail.query.brastype.uncheck" />
                                            </html:option>
                                            <html:option value="1">
                                                <bean:message key="shop.bras.detail.query.brastype.checked" />
                                            </html:option>
                                        </html:select>
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
										<html:submit styleClass="button_blank" property="save"
											value='<%=LanguageUtil.get(pageContext, "shop.query.query")%>'
											onclick="javascript:brasValidateAllData();" />
										<html:button property="reset" styleClass="button_blank"
											value='<%=LanguageUtil.get(pageContext, "shop.query.reset")%>'
											onclick="document.ShopBrasDetailForm.reset();" />
										<html:button property="print" styleClass="button_blank"
											value='<%=LanguageUtil.get(pageContext, "shop.query.print")%>'
											onclick="javascript:shopbrasprintpreview();" />
									</td>
								</tr>
							</table>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>

	<!--startprintshopbrasdetail_query.jsp-->
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>
				<ec:table var="shopbraspres" items="shopbrasresult"
					filterable="false" imagePath="/html/extcommon/ximages/*.gif"
					action="/ext/shopbrasdetail_result" form="ShopBrasDetailForm"
					showPagination="false" autoIncludeParameters="false">
					<ec:row highlightRow="true">
						<ec:column property="refno" headerStyle="text-align:left"
							style="text-align:left" filterable="false" sortable="false"
							title="<%=LanguageUtil.get(pageContext,
							"shop.bras.detail.query.refno")%>"
							width="8%" />
						<ec:column property="cardno" headerStyle="text-align:left"
							style="text-align:left" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext,
							"shop.bras.detail.query.cardno")%>'
							width="6%" />
					   <ec:column property="stuempno" headerStyle="text-align:left"
                            style="text-align:left" filterable="false" sortable="false"
                            title='<%=LanguageUtil.get(pageContext,
                            "shop.bras.detail.query.stuempno")%>'
                            width="10%" />
						<ec:column property="custname" headerStyle="text-align:left"
							style="text-align:left" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext,
							"shop.bras.detail.query.custname")%>'
							width="8%" />
						<ec:column property="oppaccno" headerStyle="text-align:left"
							style="text-align:left" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext,
							"shop.bras.detail.query.oppaccno")%>'
							width="10%" />

						<ec:column property="oppaccname" headerStyle="text-align:left"
							style="text-align:left" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext,
							"shop.bras.detail.query.oppaccname")%>'
							width="8%" />
						<ec:column property="transdate" headerStyle="text-align:left"
							style="text-align:left" filterable="false" sortable="false"
							title="<%=LanguageUtil.get(pageContext,
							"shop.bras.detail.query.transdate")%>"
							width="6%" />
						<ec:column property="transtime" headerStyle="text-align:left"
							style="text-align:left" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext,
							"shop.bras.detail.query.transtime")%>'
							width="6%" />
                        <ec:column property="status" headerStyle="text-align:left"
                            style="text-align:left" filterable="false" sortable="false"
                            title='<%=LanguageUtil.get(pageContext,
                            "shop.bras.detail.query.status")%>'
                            width="6%">
                            <c:if test="${shopbraspres.status== '0'}"> 
                                <%=LanguageUtil.get(pageContext,
                            "shop.bras.detail.query.status.success")%>
                                                        </c:if>
                            <c:if test="${shopbraspres.status== '1'}">    
                               <%=LanguageUtil.get(pageContext,
                            "shop.bras.detail.query.status.failure")%>
                             </c:if>
                        </ec:column>
						<ec:column property="remark" headerStyle="text-align:left"
							style="text-align:left" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext,
							"shop.bras.detail.query.remark")%>'
							width="18%" />
							
						<ec:column property="chkflag" headerStyle="text-align:left"
							style="text-align:left" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext,
							"shop.bras.detail.query.chkflag")%>'
							width="6%">
							<c:if test="${shopbraspres.chkflag== '0'}"> 
                                <%=LanguageUtil.get(pageContext,
                            "shop.bras.detail.query.brastype.uncheck")%>
                                                        </c:if>
							<c:if test="${shopbraspres.chkflag== '1'}">    
                               <%=LanguageUtil.get(pageContext,
                            "shop.bras.detail.query.brastype.checked")%>
                             </c:if>

						</ec:column>
						<ec:column property="transamt" headerStyle="text-align:right"
							cell="currency" format="###,###,###,##0.00"
							style="text-align:right" filterable="false" sortable="false"
							title='<%=LanguageUtil.get(pageContext,
							"shop.bras.detail.query.transamt")%>'
							width="6%" />


					</ec:row>

				</ec:table>
			</td>
		</tr>
	</table>
	<!--endprintshopbrasdetail_query.jsp-->
</html:form>
<script language="JavaScript">                                        
    Calendar.setup({
        inputField     :    "bras_begindate",     // id of the input field
        button         :    "f_trigger_bras_begindate",  // trigger for the calendar (button ID)
        align          :    "Bl",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    
    Calendar.setup({
        inputField     :    "bras_enddate",     // id of the input field
        button         :    "f_trigger_bras_enddate",  // trigger for the calendar (button ID)
        align          :    "Bl",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
</script>
<script>
function brasValidateAllData() {
    document.ShopBrasDetailForm.submit();
}

</script>

<script language="javascript">
function shopbrasprintpreview()
{
bdhtml=window.document.body.innerHTML;
sprnstr="<!--startprintshopbrasdetail_query.jsp-->";
eprnstr="<!--endprintshopbrasdetail_query.jsp-->";
prnhtml=bdhtml.substr(bdhtml.indexOf(sprnstr)+41);
prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
window.document.body.innerHTML=prnhtml;
window.print();
}
</script>