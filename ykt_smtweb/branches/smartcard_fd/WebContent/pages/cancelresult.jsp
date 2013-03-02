<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<title>card</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK">
		<link href="pages/css/css.css" rel="stylesheet" type="text/css" />
		<%
			String paramKey = (String) request.getAttribute("paramKey");
			String cardNo = (String) request.getAttribute("cardno");
			String blkVersion = (String) request.getAttribute("blkversion");
			
		%>
		<script language="JavaScript" type="text/JavaScript">
<!--
function writeCard(){
	document.body.style.overflow='hidden';
	var blkVersion = "<%=blkVersion%>";
	var msg = document.getElementById("msg");
	if( blkVersion == '' ){
		msg.innerHTML = "写卡失败！ 请点击&quot;<strong>确定</strong>&quot;返回,并重新解挂。";
	}else{
	    writeCardForm.RFScanner.PortNo=2;
	    var ret=writeCardForm.RFScanner.UndoLoss("<%=paramKey%>"
	    	,"<%=cardNo%>",blkVersion);
	    
	    if(ret==0)//解挂成功
	    {
	    	msg.innerHTML = "解挂成功！ 请点击 &quot;<strong>确定</strong>&quot; 返回";
	    }
	    else
	    {
	    	msg.innerHTML = "写卡失败！ 请点击&quot;<strong>确定</strong>&quot;返回,并重新解挂。";
	    }
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
//-->
</script>
	<style type="text/css">
		.样式5 {
			font-family: "宋体"; 
			color: #000000;
			font-size: 18px;
		}
		.样式13 {
			font-family: "黑体"; 
			color: #ff0000; 
			font-size: 18px; 
			}
		</style>
	</head>
	<html:base />
	<body scroll="no" onload="javascript:writeCard();">
		<form action="" method="post" name="writeCardForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<table width="100%" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td height="80"></td>
									</tr>
								</table>
							</div>

							<div id="content_input">
								<table width="50%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									<tr>
										<td height="320" align="center" id="msg" class="样式13">
											<strong>正在写卡 。。。</strong>
										</td>
									</tr>


								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/xykw.do';"
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
