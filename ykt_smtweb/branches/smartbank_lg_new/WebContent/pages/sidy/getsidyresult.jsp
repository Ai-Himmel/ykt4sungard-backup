<%@ page contentType="text/html;charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html>
	<head>
		<title>card</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK">
		<link href="main.css" rel="stylesheet" type="text/css">
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet" type="text/css" />
		<%
		String count = (String)request.getAttribute("count");
		String cardId = (String)request.getAttribute("cardno");
		%>
<script language="JavaScript" type="text/JavaScript">
function showmess(){
	document.body.style.overflow='hidden';
	var t_count = '<%=count%>';	
	var t_amount = writeCardForm.RFScanner.GetRequestRetInfo("amount");
	var t_outCardAmount = writeCardForm.RFScanner.GetRequestRetInfo("outcardamount");
	var msg = document.getElementById("msg");
	if(t_count==0){
		msg.innerHTML = "<b>补助领取成功！</b><br> <br>补助金额："+t_amount+"元<br> <br>卡余额："+t_outCardAmount/100+"元<br> <br> 所有补助领取完毕！按 <b>确定</b> 返回";
	}else{
		msg.innerHTML = "<b>补助领取成功！</b><br> <br>补助金额："+t_amount+"元<br> <br>卡余额："+t_outCardAmount/100+"元<br> <br> 您还有<b> "+t_count+" </b>条补助未领取！<br> <br>按 <b>继续</b> 可以继续领取";
	}
	
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


</script>
	</head>
	<html:base />
	<body scroll="no" onload="javascript:showmess();" onkeydown="return (event.keyCode!=8)">
		<form action="<%=path%>/goonGetSidy.do" method="post"
			name="writeCardForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<table width="100%" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td height="80">
											<input type="hidden" name="cardno" value="<%=cardId%>" />

										</td>
									</tr>
								</table>
							</div>

							<div id="content_input">
								<table width="50%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">

									<tr>
										<td height="320" align="center" class="样式13" id="msg">
										</td>
									</tr>

								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript: document.writeCardForm.submit();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','<%=path%>/pages/images/continuea.gif',1)"><img
													src="<%=path%>/pages/images/continue.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='<%=path%>/index.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('back','','<%=path%>/pages/images/backa.gif',1)"><img
													src="<%=path%>/pages/images/back.gif" name="back"
													width="109" height="48" border="0" id="back" /> </a>
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
				height="0" codebase="<%=path%>/rf35.cab#version=2,0,0,7" />
		</form>
	</body>
</html>
