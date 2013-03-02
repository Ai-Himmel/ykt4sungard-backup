<%@ include file="/html/common/init.jsp" %>
<%@page pageEncoding="GBK"%>
<%@page import="com.liferay.portal.kernel.language.LanguageUtil"%>
<%@page import="com.liferay.util.servlet.SessionErrors"%>
<%@page import="com.kingstargroup.ecard.util.EcardConstants"%>
<%@page import="com.kingstargroup.ecard.hibernate.losecard.TLosscardshop" %>
<portlet:defineObjects />
<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.EDIT_INFO_SUCCESS)%>">
	<font class="portlet-msg-info"> <%=LanguageUtil.format(pageContext,
								EcardConstants.EDIT_INFO_SUCCESS, SessionErrors.get(
										request, EcardConstants.EDIT_INFO_SUCCESS))%> </font>
</c:if>
<%TLosscardshop shopinfo = (TLosscardshop)request.getAttribute("lossCardShop"); %>
<html:form action="/ext/losecardshopedit" method="post" onsubmit="submitPortletForm(this); return false;">
	<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
		<tbody>
			<tr align="center" valign=center>
				<td width="15%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
				<input type="hidden" value='<%=shopinfo.getShopcode() %>' name="shopCode" />
					<span class="medium">登录编号</span>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<%=shopinfo.getShopcode() %>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 登录名称 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input name="shopName" class="input_box" maxlength=20 value='<%=shopinfo.getShopname() %>'>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 卡片所在位置 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input name="getCardPlace" class="input_box" maxlength=20 value='<%=shopinfo.getGetcardplace() %>'>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 联系电话 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input name="tel" class="input_box" maxlength=20 value='<%=shopinfo.getTel() %>'>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 商户地址 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input name="addr" class="input_box" maxlength=20 value='<%=shopinfo.getAddr() %>'>
				</td>
			</tr>
			<tr>
				<td height="30" align="right" valign="middle">
				</td>
				<td>
					&nbsp;&nbsp;
					<input name="Submit22" type="button" value=" 修 改 " onclick="document.losecardshopform.submit();">
				</td>
			</tr>
		</tbody>
	</table>
</html:form>
<script>
    function submit22() {
        //document.losecardshopeditform.querytype.value = typevalue;
        document.losecardshopform.action='/ext/losecardshopedit';
        document.losecardshopform.submit();
    }
</script>

