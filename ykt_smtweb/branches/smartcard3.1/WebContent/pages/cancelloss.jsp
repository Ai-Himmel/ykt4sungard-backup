<%@ page contentType="text/html;charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>卡片解挂</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
			String cardNo = (String) session.getAttribute("cardno");
		%>
		<script language="JavaScript" type="text/JavaScript">
		function writeCard(){
		    cancelLossForm.submit();
		}
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
		</script>
		<style type="text/css">
.样式5 {
	font-family: "宋体";
	color: #ff0000;
	font-size: 18px;
}

.样式13 {
	font-family: "黑体";
	color: #000000;
	font-size: 18px;
}
</style>
	</head>
	<%
		com.kingstargroup.fdykt.dto.AccountDTO acc = (com.kingstargroup.fdykt.dto.AccountDTO) session
				.getAttribute("account");
		String state = acc.getCardstatus();
		String tmp = "";
		if (state.equals("0000000000")) {
			tmp = "正常";
		} else if (state.equals("0100000000")) {
			tmp = "挂失";
		} else if (state.equals("0010000000")) {
			tmp = "冻结";
		} else if (state.equals("0001000000")) {
			tmp = "写卡失败";
		} else if (state.equals("0000100000")) {
			tmp = "坏卡";
		}
		String open_Date = acc.getOpendate();
		String close_Date = acc.getExpiredate();
		if (open_Date != null && open_Date.length() == 8)
			open_Date = open_Date.substring(0, 4) + "年"
					+ open_Date.substring(4, 6) + "月"
					+ open_Date.substring(6, 8) + "日";
		if (close_Date != null && close_Date.length() == 8)
			close_Date = close_Date.substring(0, 4) + "年"
					+ close_Date.substring(4, 6) + "月"
					+ close_Date.substring(6, 8) + "日";
	%>
	<body scroll="no">
		<form action="/smartcardweb/cancelresult.do" method="post"
			name="cancelLossForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/jiegua.gif" width="314"
									height="82" />
							</div>

							<div id="content_input">
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									<tr>
										<td height="30" class="样式13">
											帐&nbsp;户&nbsp;号
										</td>
										<td>
											<bean:write name="account" property="accno" />
											&nbsp;
										</td>
									</tr>
									<tr>
										<td width="162" height="30" class="样式13">
											客&nbsp;户&nbsp;号
										</td>

										<td width="162">
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
										<td width="162" height="30" class="样式13">
											客&nbsp;户&nbsp;名
										</td>
										<td width="162">
											<bean:write name="account" property="custname" />
											&nbsp;
											<input type="hidden" name="cardno" value="<%=cardNo%>" />
										</td>
									</tr>
									<tr>
										<td height="30" class="样式13">
											卡&nbsp;&nbsp;&nbsp;&nbsp;号
										</td>
										<td>
											<bean:write name="account" property="cardno" />
											&nbsp;
										</td>
									</tr>
									<tr>
										<td height="30" class="样式13">
											卡&nbsp;状&nbsp;态
										</td>
										<td><%=tmp%>&nbsp;
										</td>
									</tr>
									<tr>
										<td height="30" class="样式13">
											可用余额
										</td>
										<td>
											<bean:write name="account" property="availbal" format="0.00" />
											元
										</td>
									</tr>
									<tr>
										<td height="30" class="样式13">
											待领补助
										</td>
										<td>
											<bean:write name="account" property="frozebal" format="0.00" />
											元
										</td>
									</tr>
									<tr>
										<td height="30" class="样式13">
											开户日期
										</td>
										<td><%=open_Date%>&nbsp;
										</td>
									</tr>
									<tr>
										<td height="30" class="样式13">
											有效期至
										</td>
										<td><%=close_Date%>&nbsp;
										</td>
									</tr>
									<tr>
										<td colspan="2" align="center" class="样式5">
											&nbsp;请确认放好卡! <html:errors />
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:writeCard();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/jga.gif',1)"><img
													src="/smartcardweb/pages/images/jg.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/main.do';"
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
				height="0" codebase="/smartcardweb/rf35.cab#version=2,0,0,7" />
		</form>
	</body>
</html>

