<%@ include file="/html/extportlet/ecard/cardtransaction/init.jsp"%>
<%
	String beginDate = DateFormatUtil.getDateLaterNow();
	String endDate = DateFormatUtil.getNowDate();
	//String stuempNo = (long) request.getSession().getAttribute(WebKeys.USER_ID);
	Long realUserId = (Long) request.getSession().getAttribute(
			WebKeys.USER_ID);
	User myuser = UserLocalServiceUtil.getUserById(realUserId);
	String stuempNo = myuser.getScreenName();
	TCustomer tcustomer = CustomerLocalServiceUtil
			.getCustomerByStuempno(stuempNo);
	if (tcustomer == null) {
%>
<%@ include
	file="/html/extportlet/ecard/cardtransaction/permission_general_user.jsp"%>

<%
	} else {
		String customerId = tcustomer.getCustid().toString();
		List availableCards = CardServiceUtil
				.getAvailableCards(customerId);
%>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.DATE_NOT_SELECTED) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="date_not_selected"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,Exception.class.getName()) %>">
<font class="portlet-msg-error">
    <%= LanguageUtil.format(pageContext, EcardConstants.ERROR_EXIST,((Exception)SessionErrors.get(request,Exception.class.getName())).getMessage()) %>
 </font>
</c:if>
<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.DETAIL_QUERY_DAYS_NUM)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.DETAIL_QUERY_DAYS_NUM, SessionErrors.get(
										request, EcardConstants.DETAIL_QUERY_DAYS_NUM))%> </font>
</c:if>
<html:form action="/ext/ecardtransactionquerydetail_result" method="POST"
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
									<td width="7%" nowrap="nowrap" align="right">
										<bean:message key="ecard.beginDate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="beginDate"  size="30"  maxlength="10" />	
										<a href="javascript:void(0);"><img src="/html/extthemes/classic/images/calendar/calendar.gif"  border="0" id="f_trigger_begindate" />
										</a>&nbsp;<font color="red">*</font>
									</td>
									<td width="20%" nowrap="nowrap" align="left">
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="ecard.endDate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="endDate" size="30"  maxlength="10" />	           	
						            	<a href="javascript:void(0);"><img src="/html/extthemes/classic/images/calendar/calendar.gif"  border="0" id="f_trigger_enddate" />
										</a>&nbsp;<font color="red">*</font>
									</td>
									<td nowrap="nowrap">
									</td>
								 <script language="JavaScript">                    
					                Calendar.setup({
					                    inputField     :    "beginDate",     // id of the input field
					                    button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					                    align          :    "Bl",           // alignment (defaults to "Bl")
					                    singleClick    :    true
					                });
					                
					                Calendar.setup({
					                    inputField     :    "endDate",     // id of the input field
					                    button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
					                    align          :    "Bl",           // alignment (defaults to "Bl")
					                    singleClick    :    true
					                });
					            </script>
								</tr>
								<tr>
									<td width="7%" align="right" nowrap="nowrap">
										<bean:message key="ecardtransaction.querydetail.chooseaccount" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:select property="cardId">
						            		<%for (int i = 0; i < availableCards.size(); i++) {
						            			TCard card = (TCard) availableCards.get(i);%>
						            		<html:option value="<%= card.getCardno().toString()%>">
						            		<bean:message key="ecard.account" /><%= i + 1%>
						            		</html:option>
						            		<%}%>
						            	</html:select>  <bean:message key="ecard.allaccount" /> 
									</td>
									<td width="20%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="serial.type" />
									</td>
									<td width="20%" nowrap="nowrap">
											<html:select property="serialType">
							            		<html:option value="1">
							            		<bean:message key="serial.consume" />
							            		</html:option>
							            		<html:option value="2">
							            		<bean:message key="serial.checkatt" />
							            		</html:option>
							            		<html:option value="3">
							            		<bean:message key="serial.checkatt_td" />
							            		</html:option>
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
										<input type="button" onclick="querydetail();" value="<bean:message key="ecard.query" />">
										<input type="reset" onclick="resetdetailForm();" value="<bean:message key="ecard.reset" />">
									</td>
								</tr>
							</table>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<c:if test='<%=request.getAttribute("detailList") != null%>'>
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>
				<display:table name="detailList" pagesize="20" class="isis" id="row"
						style="width:100%" requestURI="/ext/ecardtransactionquerydetail_result"
						export="false">
						<display:column title="<%=LanguageUtil.get(pageContext,"pos.serialno")%>"><%=pageContext.getAttribute("row_rowNum")%></display:column>
						<display:column property="tradeTime" title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.tradetime")%>" ></display:column>
						<display:column property="tradePlace" title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.tradeplace")%>"></display:column>
						<display:column property="tradeName" title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.tradename")%>"></display:column>
						<display:column property="tradeAmount" title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.tradeamount")%>"></display:column>
					</display:table>
			</td>
		</tr>
	</table>
	</c:if>
	<c:if test='<%=request.getAttribute("checkattDetailList") != null%>'>
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>
				<display:table name="checkattDetailList" pagesize="20" class="isis" id="row"
						style="width:100%" requestURI="/ext/ecardtransactionquerydetail_result"
						export="false">
						<display:column title="<%=LanguageUtil.get(pageContext,"pos.serialno")%>"><%=pageContext.getAttribute("row_rowNum")%></display:column>
						<display:column property="devid" title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.deviceid")%>" ></display:column>
						<display:column property="devname" title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.devicename")%>"></display:column>
						<display:column property="attdate" title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.checkdate")%>"></display:column>
						<display:column property="atttime" title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.checktime")%>"></display:column>
					</display:table>
			</td>
		</tr>
	</table>
	</c:if>
		<c:if test='<%=request.getAttribute("checkatt_tdDetailList") != null%>'>
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>
				<display:table name="checkatt_tdDetailList" pagesize="20" class="isis" id="row"
						style="width:100%" requestURI="/ext/ecardtransactionquerydetail_result"
						export="false">
						<display:column title="<%=LanguageUtil.get(pageContext,"ecardtransaction.gatehistrade.attnum")%>"><%=pageContext.getAttribute("row_rowNum")%></display:column>
						<display:column property="transdate" format="{0,date,yyyy-MM-dd}"  title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.tddate")%>" ></display:column>
						<display:column property="transtime"  title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.tdtime")%>" ></display:column>
						<display:column property="squtime"  title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.tdsqutime")%>" ></display:column>
						<display:column property="isValidate" title="<%=LanguageUtil.get(pageContext,"ecardtransaction.tradetable.tdValidate")%>"></display:column>
					</display:table>
			</td>
		</tr>
	</table>
	</c:if>

</html:form>
<script type="text/javascript">
	function resetdetailForm(){
		var form = document.forms["TradeDetailQueryForm"];
		form.beginDate.value = '<%=beginDate%>';
		form.endDate.value = '<%=endDate%>';
		form.cardId.value = "";
		form.serialType.value = "";
	}
	function querydetail(){
		var form = document.forms["TradeDetailQueryForm"];
		form.submit();
	}
</script>
<%}%>