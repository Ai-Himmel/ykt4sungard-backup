<%@ page contentType="text/html;charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>card</title>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<link href="main.css" rel="stylesheet" type="text/css">
<%
		String cardNo = (String) session.getAttribute("cardno");
%>
<script language="JavaScript" type="text/JavaScript">
<!--
function writeCard(){
	/*
    cancelLossForm.RFScanner.PortNo=2;
    var ret=cancelLossForm.RFScanner.DoScan();
    var cardNo = cancelLossForm.RFScanner.CardNo;
    var tokenNo = "<%=cardNo%>";
    if(cardNo == tokenNo){
	    if(ret==1 )//��鿨
	    {
	         cancelLossForm.submit();
	    }
    }
    */
    cancelLossForm.submit();
}

function MM_reloadPage(init) {  //reloads the window if Nav4 resized
  if (init==true) with (navigator) {if ((appName=="Netscape")&&(parseInt(appVersion)==4)) {
    document.MM_pgW=innerWidth; document.MM_pgH=innerHeight; onresize=MM_reloadPage; }}
  else if (innerWidth!=document.MM_pgW || innerHeight!=document.MM_pgH) location.reload();
}
MM_reloadPage(true);

function MM_preloadImages() { //v3.0
  var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
    var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
    if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
}
//-->
</script>
<link href="css/main.css" rel="stylesheet" type="text/css">
<style type="text/css">
<!--
.��ʽ1 {font-size: None}
.��ʽ2 {color: #FFFFFF}
.��ʽ3 {font-size: None; color: #FFFFFF; }
.��ʽ4 {color: #000000}
.��ʽ6 {font-size: 14px}
-->
</style>
</head>
<!--html:base/-->
<%
		com.kingstargroup.fdykt.dto.AccountDTO acc = (com.kingstargroup.fdykt.dto.AccountDTO) session
				.getAttribute("account");
		String state = acc.getState_id();
		String tmp = "";
		if (state.equals("1000")) {
			tmp = "����";
		} else if (state.equals("2000")) {
			tmp = "ע��";
		} else if (state.equals("1100")) {
			tmp = "��ʧ";
		} else if (state.equals("1010")) {
			tmp = "����";
		} else if (state.equals("1001")) {
			tmp = "д��ʧ��";
		} else if (state.equals("1110")) {
			tmp = "��ʧ����";
		} else if (state.equals("1111")) {
			tmp = "��ʧ����д��ʧ��";
		}
		String open_Date = acc.getOpen_Date();
		String close_Date = acc.getClose_Date();
		if (open_Date != null && open_Date.length() == 8)
			open_Date = open_Date.substring(0, 4) + "��"
					+ open_Date.substring(4, 6) + "��"
					+ open_Date.substring(6, 8) + "��";
		if (close_Date != null && close_Date.length() == 8)
			close_Date = close_Date.substring(0, 4) + "��"
					+ close_Date.substring(4, 6) + "��"
					+ close_Date.substring(6, 8) + "��";
%>
<form action="/smartcardweb/cancelresult.do" method="POST"
	name="cancelLossForm"><input type="hidden" name="cardno"
	value="<%=cardNo%>"> <OBJECT id=RFScanner
	classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
	height="0" codebase="/smartcardweb/rf35.cab#version=2,0,0,7"> </OBJECT>
<body leftmargin="0" topmargin="0" marginwidth="0" marginheight="0"
	onload="javascript:document.body.style.overflow='hidden'">
<table width="1024" height="768" border="0" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="768" valign="top"
			background="/smartcardweb/pages/images/login_no.jpg">
		<table width="525" height="768" border="0" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="85" height="51">&nbsp;</td>
				<td width="440">&nbsp;</td>
			</tr>
			<tr>
				<td>&nbsp;</td>
				<td valign="top">
				<table width="432" height="662" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td width="432" height="98">&nbsp;</td>
					</tr>
					<tr>
						<td height="482" align="center">
						<div id="Layer1"
							style="position:absolute; left:29px; top:154px; width:560px; height:73px; z-index:1; color: #000000;font-size: 24px;"><font
							face="����">�������Ƿ�ȷ�Ͻ�Ҹÿ���</font></div>
						<div id="Layer2"
							style="position:absolute; left:104px; top:200px; width:407px; height:505px; z-index:2">
						<table width="377" border="1" cellpadding="0" cellspacing="0"
							bordercolor="#6699FF">
							<tr bordercolor="#3399CC" bgcolor="#FFFFFF">
								<td width="119" height="40" bgcolor="#D8ACCD" class="an">
								<div align="center" class="��ʽ1 ��ʽ2">�ͻ���</div>
								</td>
								<td width="226">
								<div align="center" class="��ʽ4 ��ʽ6"><bean:write name="account"
									property="cut_name" />&nbsp;</div>
								</td>
							</tr>
							<tr bordercolor="#3399CC" bgcolor="#FFFFFF">
								<td width="119" height="40" bgcolor="#D8ACCD" class="an">
								<div align="center" class="��ʽ3">�ʺ�</div>
								</td>
								<td width="226">
								<div align="center" class="text_d ��ʽ4 ��ʽ6">&nbsp;<bean:write
									name="account" property="account_id" />&nbsp;</div>
								</td>
							</tr>
							<tr bordercolor="#3399CC" bgcolor="#FFFFFF">
								<td width="119" height="40" bgcolor="#D8ACCD" class="an">
								<div align="center" class="��ʽ3">����</div>
								</td>
								<td width="226">
								<div align="center" class="text_d ��ʽ4 ��ʽ6">&nbsp;<bean:write
									name="account" property="card_id" />&nbsp;</div>
								</td>
							</tr>
							<tr bordercolor="#3399CC" bgcolor="#FFFFFF">
								<td width="119" height="40" bgcolor="#D8ACCD" class="an">
								<div align="center" class="��ʽ3">��״̬</div>
								</td>
								<td width="226">
								<div align="center" class="text_d ��ʽ4 ��ʽ6"><%=tmp%>&nbsp;</div>
								</td>
							</tr>
							<tr bordercolor="#3399CC" bgcolor="#FFFFFF">
								<td width="119" height="40" bgcolor="#D8ACCD" class="an">
								<div align="center" class="��ʽ3">�������</div>
								</td>
								<td width="226">
								<div align="center" class="text_d ��ʽ4 ��ʽ6"><bean:write
									name="account" property="cur_FreeBala" format="0.00" />Ԫ</div>
								</td>
							</tr>
							<tr bordercolor="#3399CC" bgcolor="#FFFFFF">
								<td width="119" height="40" bgcolor="#D8ACCD" class="an">
								<div align="center" class="��ʽ3">�������</div>
								</td>
								<td width="226">
								<div align="center" class="text_d ��ʽ4 ��ʽ6"><bean:write
									name="account" property="cur_FrozeBala" format="0.00" />Ԫ</div>
								</td>
							</tr>
							<tr bordercolor="#3399CC" bgcolor="#FFFFFF">
								<td width="119" height="40" bgcolor="#D8ACCD" class="an">
								<div align="center" class="��ʽ3">��������</div>
								</td>
								<td width="226">
								<div align="center" class="text_d ��ʽ4 ��ʽ6"><%=open_Date%>&nbsp;</div>
								</td>
							</tr>
							<tr bordercolor="#3399CC" bgcolor="#FFFFFF">
								<td width="119" height="40" bgcolor="#D8ACCD" class="an">
								<div align="center" class="��ʽ3">��Ч����</div>
								</td>
								<td width="226">
								<div align="center" class="text_d ��ʽ4 ��ʽ6"><%=close_Date%>&nbsp;</div>
								</td>
							</tr>
							<tr bordercolor="#3399CC" bgcolor="#FFFFFF">
								<td height="40" class="an" colspan="2">
								<div align="center" class="text_d ��ʽ4 ��ʽ6">����ȷ�Ϸźÿ���</div>
								</td>
							</tr>
						</table>
						<html:errors />
						<table width="100%" border="0" cellpadding="0" cellspacing="0"
							height="4%">
							<tr>
								<td width="34%" height="85" align="center">&nbsp;</td>
								<td width="66%" height="85" align="right"><img
									src="/smartcardweb/pages/images/jiegua.jpg" width="57"
									height="57" border="0" usemap="#Map"></td>
								<td width="34%" height="85" align="center"><img
									src="/smartcardweb/pages/images/fanhui.jpg" width="57"
									height="57" border="0" usemap="#Map2"></td>
							</tr>
						</table>
						</div>
						</td>
					</tr>
					<tr>
						<td height="78" align="center">&nbsp;</td>
					</tr>
				</table>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
<map name="Map">
	<area shape="circle" coords="30,29,27"
		onmousedown="javascript:writeCard();">
</map>
<map name="Map2">
	<area shape="circle" coords="29,28,27"
		onmousedown="javascript: window.location='/smartcardweb/main.do';">
</map>
</body>
</form>
</html>
