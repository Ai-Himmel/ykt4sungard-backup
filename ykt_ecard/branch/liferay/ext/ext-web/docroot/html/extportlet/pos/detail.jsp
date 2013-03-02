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
<html:form action="/pos/detail_result" method="POST"
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
										<html:text property="detailDeviceId" />	
									</td>
									<td width="20%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="pos.deviceName" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="detailDeviceName" />	
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
										<html:text property="detailBeginDate" />
										<a href="javascript:void(0);"><img src="/html/extthemes/classic/images/calendar/calendar.gif" border="0" id="img_detail_beginDate" />
										</a>&nbsp;<font color="red">*</font>
									</td>
									<td width="20%" nowrap="nowrap" align="left">
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="pos.endDate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="detailEndDate" />
										<a href="javascript:void(0);"><img src="/html/extthemes/classic/images/calendar/calendar.gif"  border="0" id="img_detail_endDate" />
										</a>&nbsp;<font color="red">*</font>
									</td>
									<td nowrap="nowrap">
									</td>
									<script language="JavaScript">
                        
				                        Calendar.setup({
				                            inputField     :    "detailBeginDate",     // id of the input field
				                            weekNumbers     :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "img_detail_beginDate",  // trigger for the calendar (button ID)
				                            ifFormat       :    "<%=LanguageUtil.get(pageContext, "format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                        
				                        Calendar.setup({
				                            inputField     :    "detailEndDate",     // id of the input field
				                            weekNumbers        :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "img_detail_endDate",  // trigger for the calendar (button ID)
				                            ifFormat      :    "<%=LanguageUtil.get(pageContext, "format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                    </script>
								</tr>
								<tr>
									<td height="7%" align="right" nowrap="nowrap">
										<bean:message key="pos.beginTime" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="detailBeginTime" />	
									</td>
									<td width="20%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="pos.endTime" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="detailEndTime" />	
									</td>
									<td nowrap="nowrap">
										&nbsp;
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
									<td width="100%" align="center" colspan="2">
										<input type="button" onclick="queryDetail();" value="<bean:message key="pos.query" />">
										<input type="reset" onclick="resetDetailForm();" value="<bean:message key="pos.reset" />">
										<!-- 
										<input type="button" onclick="printDetail();" value="<bean:message key="pos.print" />">
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

	<!--start print detail-->
	<c:if test='<%=request.getAttribute("detailList") != null%>'>
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>
				<display:table name="detailList" pagesize="20" class="isis" id="row"
				style="width:100%" requestURI="/pos/detail_result"
				export="true">
					<display:column title="<%=LanguageUtil.get(pageContext,"pos.serialno")%>"><%=pageContext.getAttribute("row_rowNum")%></display:column>
					<display:column property="deviceId" title="<%=LanguageUtil.get(pageContext,"pos.deviceId")%>" ></display:column>
					<display:column property="deviceName" title="<%=LanguageUtil.get(pageContext,"pos.deviceName")%>"></display:column>
					<display:column property="date" title="<%=LanguageUtil.get(pageContext,"pos.detail.date")%>"></display:column>
					<display:column property="time" title="<%=LanguageUtil.get(pageContext,"pos.detail.time")%>"></display:column>
					<display:column property="custName" title="<%=LanguageUtil.get(pageContext,"pos.custName")%>"></display:column>
					<display:column property="custNo" title="<%=LanguageUtil.get(pageContext,"pos.custNo")%>"></display:column>
					<display:column property="money" title="<%=LanguageUtil.get(pageContext,"pos.detail.money")%>"></display:column>
				</display:table>				
			</td>
		</tr>
	</table>
	</c:if>
	<!--end print detail-->
</html:form>
<script type="text/javascript">
	function resetDetailForm(){
		var form = document.forms["detailForm"];
		form.detailDeviceId.value = "";
		form.detailDeviceName.value = "";
		form.detailBeginDate.value = "";
		form.detailEndDate.value = "";
		form.detailBeginTime.value = "";
		form.detailEndTime.value = "";
	}
	function queryDetail(){
		var form = document.forms["detailForm"];
		form.submit();
	}
	function printDetail(){
		bdhtml=window.document.body.innerHTML;
		sprnstr="<!--start print detail-->";
		eprnstr="<!--end print detail-->";
		prnhtml=bdhtml.substr(bdhtml.indexOf(sprnstr)+25);
		prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
		window.document.body.innerHTML=prnhtml;
		window.print();
	}
</script>