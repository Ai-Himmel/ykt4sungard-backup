
<%@ include file="/html/extportlet/ecard/cardtransaction/init.jsp"%>


<link rel="stylesheet" type="text/css" media="all"
	href="/html/js/calendar/calendar-blue.css" title="win2k-cold-1" />

<script type="text/javascript" src="/html/extjs/calendar/calendar.js"></script>

<script type="text/javascript"
	src="/html/extjs/calendar/lang/cn_utf8.js"></script>

<script type="text/javascript"
	src="/html/extjs/calendar/calendar-setup.js"></script>



<%
	SimpleDateFormat format = new SimpleDateFormat("yyyy/MM/dd");
%>
<table width="719" height="29" border="0" cellpadding="0"
	cellspacing="0">
	<tr>
		<td>
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td width="2%">
						&nbsp;
					</td>
					<td width="72%" class="text_blue_12_c">
						<bean:message key="ecardtransaction.tab.carddelay" />
					</td>
					<td width="11%" valign="bottom">
						&nbsp;
					</td>
					<td width="15%" align="right" valign="middle" nowrap
						class="text_brown">
						&nbsp;
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>
<table width="100" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td height="5"></td>
	</tr>
</table>
<table width="719" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td width="9" height="7"></td>
		<td height="7"></td>
		<td width="6" height="7"></td>
	</tr>
	<tr>
		<td>
			&nbsp;
		</td>
		<td valign="top" align=center>
			<!-- content table -->
			<html:form action="/ext/ecardtransactionadd_postpone_result"
				method="POST"
				onsubmit="javascript:submitPortletForm(this); return false;">

				<table width="100%" border="0" cellspacing="0" cellpadding="0">


					<tr>
						<td width="14%" valign="top" class="text_or_12">
							<bean:message key="ecardtransaction.cardpostpone.reason" />
							:
						</td>
						<td width="50%" valign="baseline" class="text_or_12">
							<html:textarea cols="50" rows="10" property="reason" />
						</td>
						<td width="36%" valign=top align=left>
							<font style="font-size: 11;"><html:errors
									property="reason" /> </font>
						</td>

					</tr>

					<tr>
						<td width="14%" valign="baseline" class="text_or_12">
							<bean:message key="ecardtransaction.cardpostpone.date" />
							:
						</td>
						<td width="50%" valign="baseline" class="text_or_12" align="left">
							<html:text styleId="postponeTime" property="postponeTime"
								readonly="true" size="20" value="<%=format.format(new Date())%>"
								maxlength="8" onkeydown="monitorDateInput()" />
							&nbsp;
							<img align="absmiddle" style="cursor: pointer;" border="0"
								hspace="0" id="f_trigger_postponetime"
								src="/html/extthemes/classic/images/calendar/calendar.gif"
								vspace="0" onClick="zgat_jsOnClick('zgat_jsCalendarObj');">
							<script language="JavaScript">
					
					Calendar.setup({
				        inputField     :    "postponeTime",     // id of the input field
				        button         :    "f_trigger_postponetime",  // trigger for the calendar (button ID)
				        align          :    "Tr",           // alignment (defaults to "Bl")
				        singleClick    :    true
				    });
			</script>
						</td>
						<td width="36%" align=left>
							<font style="font-size: 11;"><html:errors
									property="postponeTime" /> </font>
						</td>
					</tr>
				</table>

				<table width="100%" height="1" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td bgcolor="#e1e1e2"></td>
					</tr>
				</table>
				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>
				<table width="70%" height="35" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td align="right">
							<html:submit styleClass="button_blank" property="save"
								value='<%=LanguageUtil.get(pageContext,"ecardtransaction.button.apply")%>' />
							<html:button property="reset" styleClass="button_blank"
								value='<%=LanguageUtil.get(pageContext, "ecard.reset")%>' />
						</td>
					</tr>
				</table>
			</html:form>
			<!-- content table -->
		</td>
		<td>
			&nbsp;
		</td>
	</tr>
	<tr>
		<td width="9" height="7"></td>
		<td height="7"></td>
		<td width="6" height="7"></td>
	</tr>
</table>

<script>

</script>
