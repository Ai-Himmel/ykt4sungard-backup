<%@ page contentType="text/html;charset=GBK"%>
<%@page import="com.kingstargroup.fdykt.KSConfiguration"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>

		<%
			com.kingstargroup.fdykt.dto.AccountDTO acc = (com.kingstargroup.fdykt.dto.AccountDTO) request
					.getAttribute("account");
			Boolean istrans = (Boolean) request.getAttribute("istrans");
			String state = acc.getCardstatus();
			String tmp = "";
			if (state.equals("0000000000")) {
				tmp = "����";
			} else if (state.equals("0100000000")) {
				tmp = "��ʧ";
			} else if (state.equals("0010000000")) {
				tmp = "����";
			} else if (state.equals("0001000000")) {
				tmp = "д��ʧ��";
			} else if (state.equals("0000100000")) {
				tmp = "����";
			}

			com.kingstargroup.fdykt.dto.NetAccDTO netacc = (com.kingstargroup.fdykt.dto.NetAccDTO) request
					.getAttribute("netacc");
			String netaccstate = netacc.getStatus();
			double netbalance = netacc.getBalance();
			String accstate = "";
			if (netaccstate
					.equals(com.kingstargroup.fdykt.KSConstant.NETACC_STAT_INI)) {
				accstate = "������";
			} else if (netaccstate
					.equals(com.kingstargroup.fdykt.KSConstant.NETACC_STAT_NORMAL)) {
				accstate = "����";
			} else if (netaccstate
					.equals(com.kingstargroup.fdykt.KSConstant.NETACC_STAT_LOCK)) {
				accstate = "����";
			}
		%>

		<title>�����˻���Ϣ</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<script type="text/JavaScript">
<!--
function MM_swapImgRestore() { //v3.0
  var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;
}

function MM_preloadImages() { //v3.0
  var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
    var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
    if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
}

function MM_findObj(n, d) { //v4.01
  var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
  if(!x && d.getElementById) x=d.getElementById(n); return x;
}

function MM_swapImage() { //v3.0
  var i,j=0,x,a=MM_swapImage.arguments; document.MM_sr=new Array; for(i=0;i<(a.length-2);i+=3)
   if ((x=MM_findObj(a[i]))!=null){document.MM_sr[j++]=x; if(!x.oSrc) x.oSrc=x.src; x.src=a[i+2];}
}

function redirectqtc(){
    epaytransForm.submit();
		}
//-->
</script>
		<style type="text/css">
.��ʽ12 {
	font-family: "����";
	color: #000000;
	font-size: 16px;
}

.��ʽ13 {
	font-family: "����";
	color: #000000;
	font-size: 18px;
}

.��ʽ14 {
	font-family: "����";
	color: #ff0000;
	font-size: 18px;
}
}
</style>
	</head>



	<body scroll="no">
		<form action="/smartcardweb/ptcepayputin.do" method="post"
			name="epaytransForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/zz.gif" width="314"
									height="82" />
							</div>

							<div id="content_input">
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">

									<tr>
										<td height="30" class="��ʽ13">
											�����˺�
										</td>
										<td>
											<bean:write name="netacc" property="accno" />
											&nbsp;
										</td>
									</tr>
									<tr>
										<td width="320" height="30" class="��ʽ13">
											��&nbsp;��&nbsp;��
										</td>
										<td>
											<bean:write name="netacc" property="accname" />
											&nbsp;
										</td>
									</tr>
									<tr>
										<td height="30" class="��ʽ13">
											��&nbsp;��&nbsp;��
										</td>
										<td>
											<%
												if (acc.getCustid() > 0) {
											%>
											<bean:write name="account" property="custid" />
											&nbsp;
											<%
												} else {
											%>
											&nbsp;
											<%
												}
											%>
										</td>
									</tr>

									<tr>
										<td height="30" class="��ʽ13">
											��&nbsp;&nbsp;&nbsp;&nbsp;��
										</td>
										<td>
											<bean:write name="account" property="cardno" />
											&nbsp;
										</td>
									</tr>
									<tr>
										<td height="30" class="��ʽ13">
											��&nbsp;״&nbsp;̬
										</td>
										<td><%=tmp%>&nbsp;
										</td>
									</tr>
									<tr>
										<td height="35" class="��ʽ13">
											�����˻�״̬
										</td>
										<td>
											<%=accstate%>
											&nbsp;
										</td>
									</tr>
									<tr>
										<td height="30" class="��ʽ13">
											��&nbsp;��&nbsp;��
										</td>
										<td>
											<bean:write name="account" property="availbal" format="0.00" />
											Ԫ
										</td>
									</tr>


									<tr>
										<td height="35" class="��ʽ13">
											�����˻����
										</td>
										<td>
											<bean:write name="netacc" property="balance" format="0.00" />
											Ԫ
											<input type="hidden" name="netbalance" value="<%=netbalance%>" />
										</td>
									</tr>
									<tr style="<%if (istrans) {out.print(" display:none; ");}%>">
										<td height="50" align="center" class="��ʽ14" id="errmsg" colspan="2">
											<b> <html:errors /> <br /><%=request.getAttribute("errmsg") == null ? "" : request.getAttribute("errmsg")%></b>
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript: window.location='/smartcardweb/pages/epay/ctpepayputin.jsp';"
												style="<%if (!istrans) {out.print(" display:none; ");}%>"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/kzqa.gif',1)"><img
													src="/smartcardweb/pages/images/kzq.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td align="center">
											<a onclick="javascript: redirectqtc();"
												style="<%if (!istrans) {out.print(" display:none; ");}%>"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send1','','/smartcardweb/pages/images/qzka.gif',1)"><img
													src="/smartcardweb/pages/images/qzk.gif" name="send1"
													width="109" height="48" border="0" id="send1" /> </a>
										</td>
										<td>
											<a onclick="javascript: window.location='/smartcardweb/g_zzyw.do';"
											   onmouseup="MM_swapImgRestore()"
											   onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/backa.gif',1)"><img
											   src="/smartcardweb/pages/images/back.gif" name="cancel"
											   width="109" height="48" border="0" id="cancel" /> </a>
										</td>
									</tr>
								</table>
							</div>
						</div>
						<div id="content_right"></div>
					</div>
				</div>
			</div>
			<div id="bottom"></div>
			<object id="RFScanner"
				classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
				height="0"></object>
		</form>
	</body>
</html>

