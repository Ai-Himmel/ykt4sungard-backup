
<%@page import="java.util.Map"%><%@ include file="/html/common/init.jsp" %>
<%@page pageEncoding="GBK"%>
<%@page import="com.liferay.portal.kernel.language.LanguageUtil"%>
<%@page import="com.liferay.util.servlet.SessionErrors"%>
<%@page import="com.kingstargroup.ecard.util.EcardConstants"%>
<%@page import="com.kingstargroup.ecard.hibernate.losecard.TLosscardshop" %>
<%@ page import="com.kingstargroup.ecard.KSConfiguration"%>
<portlet:defineObjects />
<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.LOSECARD_NOCARD)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.LOSECARD_NOCARD, SessionErrors.get(
										request, EcardConstants.LOSECARD_NOCARD))%> </font>
</c:if>
<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.CARD_DESTORY)%>">
	<font class="portlet-msg-info"> <%=LanguageUtil.format(pageContext,
								EcardConstants.CARD_DESTORY, SessionErrors.get(
										request, EcardConstants.CARD_DESTORY))%> </font>
</c:if>
<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.LOSECARD_SAVESUCC)%>">
	<font class="portlet-msg-info"> <%=LanguageUtil.format(pageContext,
								EcardConstants.LOSECARD_SAVESUCC, SessionErrors.get(
										request, EcardConstants.LOSECARD_SAVESUCC))%> </font>
</c:if>
<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.LOSECARD_RECORDEXIST)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.LOSECARD_RECORDEXIST, SessionErrors.get(
										request, EcardConstants.LOSECARD_RECORDEXIST))%> </font>
</c:if>
<%
	String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port", "0");
%>
<%
	Map stuempInfo = (Map)request.getAttribute("stuempInfo"); 
	String getCardPlace = request.getAttribute("getCardPlace").toString();
	String tel = request.getAttribute("tel").toString();
	String addr = request.getAttribute("addr").toString();
	String regDate = request.getAttribute("regDate").toString();
%>

<script type="text/JavaScript">
	function doCardCharge(){	
   var device_port = '<%=read_card_device_port%>'; 
   losecardregform.all.RFScanner.PortNo=device_port;//读卡器端口设置
   var ret=losecardregform.all.RFScanner.DoScan();
   if(ret==0){
	   //读卡成功
	       var cardid = losecardregform.all.RFScanner.CardNo;
	       losecardregform.all.readPhyId.value=cardid;
	       losecardregform.all.pagesign.value='2';  
	       losecardregform.submit();
	       
	   }else{
	       alert("读卡失败，请放置卡片...");
	       return false;
	   }
	}
	
	function doSave(){
		losecardregform.all.pagesign.value='3';
		losecardregform.submit();
	}
</script>
<html:form action="/ext/losecardreg" method="POST" >
	<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
		<tbody>
			<tr align="center" valign=center>
				<input type="hidden" name="pagesign" value="2"/>
				<input type="hidden" name="readPhyId" value=""/>
				<td width="15%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium">卡号</span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input readonly="true" name="cardno" class="input_box" maxlength=20 value='<%=stuempInfo.get("custid") %>'>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 物理卡号 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input readonly="true" name="cardphyid" class="input_box" maxlength=20 value='<%=stuempInfo.get("cardphyid") %>'>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 显示卡号 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input readonly="true" name="cardshowno" class="input_box" maxlength=20 value='<%=stuempInfo.get("showcardno") %>'>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 学/工号 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input readonly="true" name="stuempno" class="input_box" maxlength=20 value='<%=stuempInfo.get("stuempno") %>'>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 卡状态 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input readonly="true" name="status" class="input_box" maxlength=20 value='<%=stuempInfo.get("dictcaption") %>'>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 卡片所在位置 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input name="getcardplace" class="input_box" maxlength=20 value='<%=getCardPlace %>'>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 联系电话 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input name="tel" class="input_box" maxlength=20 value='<%=tel %>'>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 商户地点 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input name="addr" class="input_box" maxlength=20 value='<%=addr %>'>
				</td>
			</tr>
			<tr>
				<td width="15%" align="right" valign="middle" bgcolor="#D1DAE9">
					<span class="medium"> 登记日期 </span>
				</td>
				<td width="85%" align="left" valign="middle" bgcolor="#E7F1F5">
					<input readonly="true" name="regdate" class="input_box" maxlength=20 value='<%=regDate %>'>
				</td>
			</tr>
			<tr>
				<td height="30" align="right" valign="middle">
				</td>
				<td>
					<input name="Submit22" type="button" value=" 读 卡 " onclick="javascript:doCardCharge();">
					&nbsp;&nbsp;
					<input name="Submit22" type="button" value=" 保 存 " onclick="javascript:doSave();">
				</td>
			</tr>
		</tbody>
	</table>
	<object id="RFScanner"
		classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
		height="0" codebase="/smartcardweb/rf35.cab#version=2,0,0,7" />
</html:form>
