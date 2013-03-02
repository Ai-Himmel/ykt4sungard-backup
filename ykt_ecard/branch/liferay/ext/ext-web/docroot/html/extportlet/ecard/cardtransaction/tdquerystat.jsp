<%@ include file="/html/extportlet/shopquery/init.jsp"%>
<%@ page import="com.kingstargroup.ecard.util.DateFormatUtil" %>
<%
String beginDate = DateFormatUtil.getDateLaterNow("yyyy/MM/dd");
String endDate = DateFormatUtil.getNowDate("yyyy/MM/dd");
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
<html:form action="/ext/tdquerystat_result" method="POST"
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
									<td width="10%" nowrap="nowrap" align="right">
										<bean:message key="tdcheckserial.begindate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="tdcheckserial_begindate" styleId="tdcheckserial_begindate" size="30"  maxlength="10" />	
										<a href="javascript:void(0);"><img src="/html/extthemes/classic/images/calendar/calendar.gif"  border="0" id="f_trigger_begindate" /></a>
										&nbsp;<font color="red">*</font>
									</td>
									<td width="15%" nowrap="nowrap" align="left">
									</td>
									<td width="10%" nowrap="nowrap" align="right">
										<bean:message key="tdcheckserial.begindate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="tdcheckserial_enddate" styleId="tdcheckserial_enddate" size="30"  maxlength="10" />	           	
						            	<a href="javascript:void(0);"><img src="/html/extthemes/classic/images/calendar/calendar.gif"  border="0" id="f_trigger_enddate" /></a>
						            	&nbsp;<font color="red">*</font>
									</td>
									<td nowrap="nowrap">
									</td>
								 <script language="JavaScript">                    
					                Calendar.setup({
					                    inputField     :    "tdcheckserial_begindate",     // id of the input field
					                    button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					                    align          :    "Bl",           // alignment (defaults to "Bl")
					                    singleClick    :    true
					                });
					                
					                Calendar.setup({
					                    inputField     :    "tdcheckserial_enddate",     // id of the input field
					                    button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
					                    align          :    "Bl",           // alignment (defaults to "Bl")
					                    singleClick    :    true
					                });
					            </script>
								</tr>
								<tr>
									<td width="10%" align="right" nowrap="nowrap">
										<bean:message key="tdcheckserial.classno" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="tdcheckserial_classno" size="30"  maxlength="20" />
									</td>
									<td width="15%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="10%" nowrap="nowrap" align="right">
										<bean:message key="tdcheckserial.stuempno" />
									</td>
									<td width="20%" nowrap="nowrap">
											<html:text property="tdcheckserial_stuempno" size="30"  maxlength="20" />		
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
								</tr>
								<tr>
									<td width="10%" align="right" nowrap="nowrap">
										<bean:message key="tdcheckserial.custname" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="tdcheckserial_custname" size="30"  maxlength="20" />
									</td>
									<td width="15%" nowrap="nowrap" align="left">
										&nbsp;
									</td>
									<td width="10%" nowrap="nowrap" align="right">
										
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
										<input type="button" onclick="tdquerystat();" value="<bean:message key="ecard.query" />">
										<input type="reset" onclick="resettdquerystatForm();" value="<bean:message key="ecard.reset" />">
									</td>
								</tr>
							</table>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<c:if test='<%=request.getAttribute("tdquerystatList") != null%>'>
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>
				<display:table name="tdquerystatList" pagesize="60" class="isis" id="row"
						style="width:100%" requestURI="/ext/tdquerystat_result"
						export="true">
						<display:column title="<%=LanguageUtil.get(pageContext,"pos.serialno")%>"><%=pageContext.getAttribute("row_rowNum")%></display:column>
						<display:column property="classname" title="<%=LanguageUtil.get(pageContext,"tdcheckserial.classno")%>" ></display:column>
						<display:column property="stuempno" title="<%=LanguageUtil.get(pageContext,"tdcheckserial.stuempno")%>"></display:column>
						<display:column property="custname" title="<%=LanguageUtil.get(pageContext,"tdcheckserial.custname")%>"></display:column>
						<display:column property="count" title="<%=LanguageUtil.get(pageContext,"ecardtransaction.gatehistrade.attnumtd")%>"></display:column>
						<display:column property="valiCount" title="<%=LanguageUtil.get(pageContext,"ecardtransaction.gatehistrade.attvalinum")%>"></display:column>
					</display:table>
			</td>
		</tr>
	</table>
	</c:if>
</html:form>
<script type="text/javascript">
	function resetdetailForm(){
		var form = document.forms["tdquerystatForm"];
		form.tdcheckserial_begindate.value = '<%=beginDate%>';
		form.tdcheckserial_enddate.value = '<%=endDate%>';
		form.tdcheckserial_classno.value = "";
		form.tdcheckserial_stuempno.value = "";
		form.tdcheckserial_custname.value = "";
	}
	function tdquerystat(){
		var form = document.forms["tdquerystatForm"];
		form.submit();
	}
</script>