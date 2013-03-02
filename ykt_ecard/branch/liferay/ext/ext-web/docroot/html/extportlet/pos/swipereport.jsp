<%@ include file="/html/extportlet/pos/init.jsp"%>

<c:if test="<%= SessionErrors.contains(request,EcardConstants.TIME_PERIOD_TOO_LONG) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="shop_time_period_too_long"  />
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
<html:form action="/pos/swipereport_result" method="POST"
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
									<td colspan="6" align="left" nowrap="nowrap">
										<bean:message key="pos.swipereport.tips" />
									</td>
								</tr>
								<tr>
									<td colspan="6" align="left" nowrap="nowrap">
										&nbsp;
									</td>
								</tr>
								<tr>
									<td width="7%" align="right" nowrap="nowrap">
										<bean:message key="pos.custNo" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="swipereportCustNo" />	
									</td>
									<td width="20%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="pos.custName" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="swipereportCustName" />	
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="7%" align="right" nowrap="nowrap">
										<bean:message key="pos.beginMonth" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="swipereportBeginMonth" maxlength="6"/>&nbsp;<font color="red">*</font>
									</td>
									<td width="20%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="pos.endMonth" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="swipereportEndMonth" maxlength="6"/>&nbsp;<font color="red">*</font>
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="7%" align="right" nowrap="nowrap">
										<bean:message key="pos.swipereport.type" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:select property="swipereportType" style="width:150px">
											<html:option value="0"><bean:message key="pos.swipereport.type.all" /></html:option>
											<html:option value="1"><bean:message key="pos.swipereport.type.cust" /></html:option>
											<html:option value="2"><bean:message key="pos.swipereport.type.others" /></html:option>
											<html:option value="3"><bean:message key="pos.swipereport.type.allType" /></html:option>
										</html:select>	
									</td>
									<td width="20%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="pos.department" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:select property="swipereportDepartment" style="width:150px">
											<html:option value="">-------------------------</html:option>
											<html:options collection="departments" labelProperty="deptname" property="deptcode" />
										</html:select>
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
										<input type="button" onclick="querySwipereport();" value="<bean:message key="pos.query" />">
										<input type="reset" onclick="resetSwipereportForm();" value="<bean:message key="pos.reset" />">
										<!-- 
										<input type="button" onclick="printSwipereport();" value="<bean:message key="pos.print" />">
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
	<!--start print swipereport-->
	<c:if test='<%=request.getAttribute("swipereportList") != null%>'>
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>
			<display:table name="swipereportList" pagesize="20" class="isis"
						style="width:100%" requestURI="/pos/swipereport_result"
						export="true">
						<display:column property="lserial1" title="<%=LanguageUtil.get(pageContext,"pos.serialno")%>" ></display:column>
						<display:column property="sdate0" title="<%=LanguageUtil.get(pageContext,"pos.month")%>"></display:column>
						<display:column property="departmentName" title="<%=LanguageUtil.get(pageContext,"pos.department")%>"></display:column>
						<display:column property="custName" title="<%=LanguageUtil.get(pageContext,"pos.custName")%>"></display:column>
						<display:column property="custNo" title="<%=LanguageUtil.get(pageContext,"pos.custNo")%>"></display:column>
						<display:column property="chargeType" title="<%=LanguageUtil.get(pageContext,"pos.swipereport.chargeType")%>"></display:column>
						<display:column property="totalCount" title="<%=LanguageUtil.get(pageContext,"pos.swipereport.totalCount")%>"></display:column>
						<display:column property="dayCount" title="<%=LanguageUtil.get(pageContext,"pos.swipereport.dayCount")%>"></display:column>
						<display:column property="money" title="<%=LanguageUtil.get(pageContext,"pos.swipereport.money")%>"></display:column>
					</display:table>
					<br>
			</td>
		</tr>
	</table>
	</c:if>
	<!--end print swipereport-->
</html:form>
<script type="text/javascript">
	function resetSwipereportForm(){
		var form = document.forms["swipereportForm"];
		form.swipereportCustNo.value = "";
		form.swipereportCustName.value = "";
		form.swipereportBeginMonth.value = "";
		form.swipereportEndMonth.value = "";
		form.swipereportDepartment.value = "";
		form.swipereportType.value = "0";
	}
	function querySwipereport(){
		var form = document.forms["swipereportForm"];
		form.submit();
	}
	function printSwipereport(){
		bdhtml=window.document.body.innerHTML;
		sprnstr="<!--start print swipereport-->";
		eprnstr="<!--end print swipereport-->";
		prnhtml=bdhtml.substr(bdhtml.indexOf(sprnstr)+30);
		prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
		window.document.body.innerHTML=prnhtml;
		window.print();
	}
</script>