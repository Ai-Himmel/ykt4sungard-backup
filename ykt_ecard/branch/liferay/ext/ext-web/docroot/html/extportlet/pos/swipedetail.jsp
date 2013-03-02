<%@ include file="/html/extportlet/pos/init.jsp"%>


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
<html:form action="/pos/swipedetail_result" method="POST"
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
										<bean:message key="pos.custNo" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="swipedetailCustNo" />	
									</td>
									<td width="20%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="pos.custName" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="swipedetailCustName" />	
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
										<html:text property="swipedetailBeginDate" />
										<a href="javascript:void(0);"><img src="/html/extthemes/classic/images/calendar/calendar.gif" border="0" id="img_swipedetail_beginDate" />
										</a>&nbsp;<font color="red">*</font>
									</td>
									<td width="20%" nowrap="nowrap" align="left">
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="pos.endDate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="swipedetailEndDate" />
										<a href="javascript:void(0);"><img src="/html/extthemes/classic/images/calendar/calendar.gif"  border="0" id="img_swipedetail_endDate" />
										</a>&nbsp;<font color="red">*</font>
									</td>
									<td nowrap="nowrap">
									</td>
									<script language="JavaScript">
                        
				                        Calendar.setup({
				                            inputField     :    "swipedetailBeginDate",     // id of the input field
				                            weekNumbers     :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "img_swipedetail_beginDate",  // trigger for the calendar (button ID)
				                            ifFormat       :    "<%=LanguageUtil.get(pageContext, "format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                        
				                        Calendar.setup({
				                            inputField     :    "swipedetailEndDate",     // id of the input field
				                            weekNumbers        :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "img_swipedetail_endDate",  // trigger for the calendar (button ID)
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
										<html:text property="swipedetailBeginTime" />	
									</td>
									<td width="20%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="pos.endTime" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="swipedetailEndTime" />	
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="7%" align="right" nowrap="nowrap">
										<bean:message key="pos.department" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:select property="swipedetailDepartment" style="width:150px">
											<html:option value="">-------------------------</html:option>
											<html:options collection="departments" labelProperty="deptname" property="deptcode" />
										</html:select>
									</td>
									<td width="20%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										
									</td>
									<td width="20%" nowrap="nowrap">
											
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
										<input type="button" onclick="querySwipedetail();" value="<bean:message key="pos.query" />">
										<input type="reset" onclick="resetSwipedetailForm();" value="<bean:message key="pos.reset" />">
										<!-- 
										<input type="button" onclick="printSwipedetail();" value="<bean:message key="pos.print" />">
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
	<!--start print swipedetail-->
	<c:if test='<%=request.getAttribute("swipedetailList") != null%>'>
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>
				<display:table name="swipedetailList" pagesize="20" class="isis" id="row"
						style="width:100%" requestURI="/pos/swipedetail_result"
						export="true">
						<display:column title="<%=LanguageUtil.get(pageContext,"pos.serialno")%>"><%=pageContext.getAttribute("row_rowNum")%></display:column>
						<display:column property="departmentName" title="<%=LanguageUtil.get(pageContext,"pos.department")%>" ></display:column>
						<display:column property="custName" title="<%=LanguageUtil.get(pageContext,"pos.custName")%>"></display:column>
						<display:column property="custNo" title="<%=LanguageUtil.get(pageContext,"pos.custNo")%>"></display:column>
						<display:column property="date" title="<%=LanguageUtil.get(pageContext,"pos.swipedetail.date")%>"></display:column>
						<display:column property="time" title="<%=LanguageUtil.get(pageContext,"pos.swipedetail.time")%>"></display:column>
						<display:column property="device" title="<%=LanguageUtil.get(pageContext,"pos.swipedetail.device")%>"></display:column>
						<display:column property="money" title="<%=LanguageUtil.get(pageContext,"pos.swipedetail.money")%>"></display:column>
					</display:table>
			</td>
		</tr>
	</table>
	</c:if>
	<!--end print swipedetail-->
</html:form>
<script type="text/javascript">
	function resetSwipedetailForm(){
		var form = document.forms["swipedetailForm"];
		form.swipedetailCustNo.value = "";
		form.swipedetailCustName.value = "";
		form.swipedetailBeginDate.value = "";
		form.swipedetailEndDate.value = "";
		form.swipedetailBeginTime.value = "";
		form.swipedetailEndTime.value = "";
		form.swipedetailDepartment.value = "";
	}
	function querySwipedetail(){
		var form = document.forms["swipedetailForm"];
		form.submit();
	}
	function printSwipedetail(){
		bdhtml=window.document.body.innerHTML;
		sprnstr="<!--start print swipedetail-->";
		eprnstr="<!--end print swipedetail-->";
		prnhtml=bdhtml.substr(bdhtml.indexOf(sprnstr)+30);
		prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
		window.document.body.innerHTML=prnhtml;
		window.print();
	}
</script>