<%@ include file="/html/extportlet/pos/init.jsp"%>

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
<html:form action="/pos/report_result" method="POST"
	onsubmit="submitPortletForm(this); return false;">
	<table cellpadding="8" border=0 cellspacing="0" width="100%">
		<tr>
			<td>
				<table border="0" align="left" cellpadding="0" cellspacing="0"
					width="100%">
					<tr>
						<td height="40">
							<table border="0" align="left" cellpadding="0" cellspacing="0"
								width="100%">
								<tr>
									<td width="7%" align="right" nowrap="nowrap">
										<bean:message key="pos.deviceId" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="reportDeviceId" />	
									</td>
									<td width="20%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="pos.deviceName" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="reportDeviceName" />	
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
								</tr>
								<tr>
									<td width="7%" nowrap="nowrap" align="right">
										<bean:message key="pos.beginDate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="reportBeginDate" />
										<a href="javascript:void(0);"><img src="/html/extthemes/classic/images/calendar/calendar.gif" border="0" id="img_report_beginDate" />
										</a>&nbsp;<font color="red">*</font>
									</td>
									<td width="20%" nowrap="nowrap" align="left">
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="pos.endDate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="reportEndDate" />
										<a href="javascript:void(0);"><img src="/html/extthemes/classic/images/calendar/calendar.gif"  border="0" id="img_report_endDate" />
										</a>&nbsp;<font color="red">*</font>
									</td>
									<td nowrap="nowrap">
									</td>
									<script language="JavaScript">
                        
				                        Calendar.setup({
				                            inputField     :    "reportBeginDate",     // id of the input field
				                            weekNumbers     :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "img_report_beginDate",  // trigger for the calendar (button ID)
				                            ifFormat       :    "<%=LanguageUtil.get(pageContext, "format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                        
				                        Calendar.setup({
				                            inputField     :    "reportEndDate",     // id of the input field
				                            weekNumbers        :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "img_report_endDate",  // trigger for the calendar (button ID)
				                            ifFormat      :    "<%=LanguageUtil.get(pageContext, "format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                    </script>
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
									<td width="100%" align="center" colspan="2">
										<input type="button" onclick="queryReport();" value="<bean:message key="pos.query" />">
										<input type="reset" onclick="resetReportForm();" value="<bean:message key="pos.reset" />">
										<!-- 
										<input type="button" onclick="printReport();" value="<bean:message key="pos.print" />">
										 -->
									</td>
								</tr>
							</table>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<!--start print report-->
	<c:if test='<%=request.getAttribute("reportList") != null%>'>
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>
			<display:table name="reportList" pagesize="20" class="isis" id="row"
				style="width:100%" requestURI="/pos/report_result"
				export="true">
				<display:column title="<%=LanguageUtil.get(pageContext,"pos.serialno")%>"><%=pageContext.getAttribute("row_rowNum")%></display:column>
				<display:column property="deviceId" title="<%=LanguageUtil.get(pageContext,"pos.deviceId")%>" ></display:column>
				<display:column property="deviceName" title="<%=LanguageUtil.get(pageContext,"pos.deviceName")%>"></display:column>
				<display:column property="date" title="<%=LanguageUtil.get(pageContext,"pos.report.date")%>"></display:column>
				<display:column property="pegCount" title="<%=LanguageUtil.get(pageContext,"pos.report.pegCount")%>"></display:column>
				<display:column property="chargeCount" title="<%=LanguageUtil.get(pageContext,"pos.report.chargeCount")%>"></display:column>
				<display:column property="totalCount" title="<%=LanguageUtil.get(pageContext,"pos.report.totalCount")%>"></display:column>
			</display:table>
			</td>
		</tr>
	</table>
	</c:if>
	<!--end print report-->
</html:form>
<script type="text/javascript">
	function resetReportForm(){
		var form = document.forms["reportForm"];
		form.reportDeviceId.value = "";
		form.reportDeviceName.value = "";
		form.reportBeginDate.value = "";
		form.reportEndDate.value = "";
	}
	function queryReport(){
		var form = document.forms["reportForm"];
		form.submit();
	}
	function printReport(){
		bdhtml=window.document.body.innerHTML;
		sprnstr="<!--start print report-->";
		eprnstr="<!--end print report-->";
		prnhtml=bdhtml.substr(bdhtml.indexOf(sprnstr)+25);
		prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
		window.document.body.innerHTML=prnhtml;
		window.print();
	}
</script>