<%@ page contentType="text/html;charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<title>写卡失败</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK">
		<link href="main.css" rel="stylesheet" type="text/css">
		<script language="JavaScript" type="text/JavaScript">
<!--

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
	</head>
	<html:base />
	<body leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
		<form action="" method="POST" name="writeCardForm">
			<table width="1024" height="768" border="0" cellpadding="0"
				cellspacing="0">
				<tr>
					<td height="768" valign="top"
						background="/smartcardweb/pages/images/login_no.jpg">
						<table width="525" height="768" border="0" cellpadding="0"
							cellspacing="0">
							<tr>
								<td width="85" height="51">
									&nbsp;
								</td>
								<td width="440">
									&nbsp;
									<OBJECT id=RFScanner
										classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
										width="0" height="0"
										codebase="/smartcardweb/rf35.cab#version=2,0,0,7">
									</OBJECT>
								</td>
							</tr>
							<tr>
								<td>
									&nbsp;
								</td>
								<td valign="top">
									<table width="432" height="376" border="0" cellpadding="0"
										cellspacing="0">
										<tr>
											<td width="432" height="184">
												&nbsp;
											</td>
										</tr>
										<tr>
											<td height="61" align="center" class="show" id="msg">
												写卡失败！请到卡务中心补写！
											</td>
										</tr>
										<tr>
											<td height="78" align="center"><img
														src="/smartcardweb/pages/images/button_re.jpg" width="57"
														height="57" border="0" onclick="javascript: window.location='/smartcardweb/main.do';">
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
				</tr>
			</table>
		</form>
	</body>
</html>
