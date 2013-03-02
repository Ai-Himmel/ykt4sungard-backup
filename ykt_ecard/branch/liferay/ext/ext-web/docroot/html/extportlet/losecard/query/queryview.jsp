<%@ include file="/html/common/init.jsp" %>
<%@ page import="com.kingstargroup.ecard.KSConfiguration"%>
<%@page import="com.liferay.portal.kernel.language.LanguageUtil"%>
<%@page import="com.liferay.util.servlet.SessionErrors"%>
<%@page import="com.kingstargroup.ecard.util.EcardConstants"%>
<%@page pageEncoding="GBK"%>
<portlet:defineObjects />
<%
	String beginDate = request.getAttribute("beginDate").toString();
	String endDate = request.getAttribute("endDate").toString();
	String custName = request.getAttribute("custName").toString();
	String stuempNO = request.getAttribute("stuempNO").toString();
	String cardShowNo = request.getAttribute("cardShowNo").toString();
	String lossCardStatus = request.getAttribute("lossCardStatus").toString();
%>
<html:form action="/ext/losecardqueryresult" method="POST" >
	<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
		<tr align="center" valign=center>
			<td width="15%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
				<span class="medium">开始日期</span>
			</td>
			<td width="35%" align="left" valign="middle" bgcolor="#E7F1F5">
				<input name="beginDate" class="input_box" maxlength=20 value='<%=beginDate %>'>
			</td>
			<td width="15%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
				<span class="medium">结束日期</span>
			</td>
			<td width="35%" align="left" valign="middle" bgcolor="#E7F1F5">
				<input name="endDate" class="input_box" maxlength=20 value='<%=endDate %>'>
			</td>		
		</tr>
		<tr align="center" valign=center>
			<td width="15%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
				<span class="medium">姓名</span>
			</td>
			<td width="35%" align="left" valign="middle" bgcolor="#E7F1F5">
				<input name="custName" class="input_box" maxlength=20 value='<%=custName %>'>
			</td>
			<td width="15%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
				<span class="medium">学/工号</span>
			</td>
			<td width="35%" align="left" valign="middle" bgcolor="#E7F1F5">
				<input name="stuempNO" class="input_box" maxlength=20 value='<%=stuempNO %>'>
			</td>		
		</tr>
		<tr align="center" valign=center>
			<td width="15%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
				<span class="medium">显示卡号</span>
			</td>
			<td width="35%" align="left" valign="middle" bgcolor="#E7F1F5">
				<input name="cardShowNo" class="input_box" maxlength=20 value='<%=cardShowNo %>'>
			</td>		
			<td width="15%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
				<span class="medium">遗失卡状态</span>
			</td>
			<td width="35%" align="left" valign="middle" bgcolor="#E7F1F5">
				<select name="lossCardStatus" style="width: 240">
					<option value="">--</option>
					<c:forEach var="lossCardStatus" items="${lossCardStatus}">
						<option value="<c:out value="${lossCardStatus.dictval}"/>">
							<c:out value="${lossCardStatus.dictcaption}" />
						</option>
					</c:forEach>
				</select>
			</td>
		</tr>
	</table>
	<table width=100% border=0 align=center cellpadding=0 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
		<tr >
			<td align="center" valign="middle" bgcolor="#E7F1F5">
				<input name="Submit22" type="button" value=" 查 询 " onclick="document.losecardqueryform.submit();">
			</td>
		</tr>
	</table>
</html:form>