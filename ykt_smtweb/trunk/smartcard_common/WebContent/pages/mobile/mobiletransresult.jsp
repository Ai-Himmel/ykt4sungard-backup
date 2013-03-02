<%@ page contentType="text/html;charset=GBK"
	errorPage="/smartcardweb/index.do"%>
<jsp:directive.page import="com.kingstargroup.fdykt.dto.AssistanceDTO" />
<jsp:directive.page import="com.kingstargroup.fdykt.dto.TTifSubsidyDTO" />
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<title>补助明细查询结果</title>
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

function MM_swapImgRestore() { //v3.0
  var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;
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
function gotoNextPage(page){
	document.pagequery.page.value = page;
	document.pagequery.submit();
}
//-->
</script>
		<link href="css/main.css" rel="stylesheet" type="text/css">
		<style type="text/css">
<!--
.style2 {font-family: "新宋体"}
.样式1 {font-size: None}
.样式2 {font-style: normal; font-weight: normal; font-size: None;}
.样式4 {font-size: 12px}
.样式7 {font-family: "新宋体"; color: #FFFFFF; font-size: 12px; }
.样式9 {font-size: 12}
.样式10 {color: #FFFFFF; font-size: 12; }
.样式11 {font-family: "新宋体"; color: #FFFFFF; font-size: 12; }
.样式14 {font-family: "新宋体"; font-size: 12px; color: #000000; }
.样式15 {color: #000000}
-->
</style>
	</head>
	<html:base />
	<%
		int p = ((Integer) session.getAttribute("page")).intValue();
		String begin = (String) session.getAttribute("begin");
		String end = (String) session.getAttribute("end");
		if (begin != null && begin.length() == 8)
			begin = begin.substring(0, 4) + "年" + begin.substring(4, 6)
			+ "月" + begin.substring(6, 8) + "日";
		if (end != null && end.length() == 8)
			end = end.substring(0, 4) + "年" + end.substring(4, 6) + "月"
			+ end.substring(6, 8) + "日";
	%>
	<form name="pagequery" action="/smartcardweb/sidypagequery.do"
		method="post">
		<input name="page" type="hidden" value="1">

	</form>
	<body leftmargin="0" topmargin="0" marginwidth="0" marginheight="0"
		onLoad="javascript:document.body.style.overflow='hidden';MM_preloadImages('images/down2.jpg','images/up2.jpg','images/fanhui2.jpg')">
		<table width="1024" height="768" border="0" cellpadding="0"
			cellspacing="0">
			<tr>
				<td height="768" valign="top"
					background="/smartcardweb/pages/images/big_info.jpg">
					<table width="876" height="768" border="0" cellpadding="0"
						cellspacing="0">
						<tr>
							<td width="85" height="51">
								&nbsp;
							</td>
							<td width="791">
								&nbsp;
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;
							</td>
							<td valign="top">
								<table width="784" border="0" cellpadding="0" cellspacing="0">

									<tr>
										<td width="784" height="482" align="center" class="show">
											<div id="Layer3"
												style="position:absolute; left:136px; top:211px; width:712px; height:329px; z-index:3">

												<table width="680" border="1" cellpadding="1"
													cellspacing="1" class="td">
													<tr align="center" bgcolor="#D8ACCD" class="td">
														<td width="120">
															<div align="center" class="样式11">
																补助批次号
															</div>
														</td>
														<td width="60">
															<div align="center" class="样式11">
																客户号
															</div>
														</td>
														<td width="60">
															<div align="center" class="样式11">
																补助类型
															</div>
														</td>
														<td width="60">
															<div align="center" class="样式11">
																发生时间
															</div>
														</td>
														<td width="120">
															<div align="center" class="样式11">
																领取时间
															</div>
														</td>
														<td width="60">
															<div align="center" class="样式11">
																截至日期
															</div>
														</td>
														<td width="100">
															<div align="center" class="样式11">
																补助金额（元）
															</div>
														</td>
														<td width="60">
															<div align="center" class="样式11">
																状态
															</div>
														</td>

													</tr>
													<%
													int serial_no = 1;
													%>
													<logic:iterate id="ttifsidy" name="ttifsidys" offset="0">
														<%
																TTifSubsidyDTO ts = (TTifSubsidyDTO) ttifsidy;
																String tx_date = ts.getTxDate();
																String tx_time = ts.getTxTime();
																String get_date = ts.getGetDate() == null ? "" : ts
																.getGetDate();
																String get_time = ts.getGetTime() == null ? "&nbsp;&nbsp;" : ts
																.getGetTime();
																String expire_date = ts.getExpireDate();
																if (tx_date != null && tx_date.length() == 8)
																	tx_date = tx_date.substring(0, 4) + "-"
																	+ tx_date.substring(4, 6) + "-"
																	+ tx_date.substring(6, 8);
																if (tx_time != null && tx_time.length() == 6)
																	tx_time = tx_time.substring(0, 2) + ":"
																	+ tx_time.substring(2, 4) + ":"
																	+ tx_time.substring(4, 6);
																if (get_date != null && get_date.length() == 8)
																	get_date = get_date.substring(0, 4) + "-"
																	+ get_date.substring(4, 6) + "-"
																	+ get_date.substring(6, 8) + "&nbsp;&nbsp;";
																if (get_time != null && get_time.length() == 6)
																	get_time = get_time.substring(0, 2) + ":"
																	+ get_time.substring(2, 4) + ":"
																	+ get_time.substring(4, 6);
																if (expire_date != null && expire_date.length() == 8)
																	expire_date = expire_date.substring(0, 4) + "-"
																	+ expire_date.substring(4, 6) + "-"
																	+ expire_date.substring(6, 8);
														%>
														<tr align="center" bordercolor="#CCCCCC">
															<td height="20">
																<div align="center" class="样式11">
																	<bean:write name="ttifsidy" property="batchNo" />
																	&nbsp;
																</div>
															</td>
															<td height="20">
																<div align="center" class="样式11">
																	<bean:write name="ttifsidy" property="custNo" />
																	&nbsp;
																</div>
															</td>
															<td height="20">
																<div align="center" class="样式11">
																	<bean:write name="ttifsidy" property="subsidytype" />
																	&nbsp;
																</div>
															</td>
															<td height="20">
																<div align="center" class="样式11">
																	<%=tx_date%>
																</div>
															</td>
															<td height="20">
																<div align="center" class="样式11">
																	<%=get_date%>
																	<%=get_time%>
																</div>
															</td>
															<td height="20">
																<div align="center" class="样式11">
																	<%=expire_date%>
																</div>
															</td>
															<td height="20">
																<div align="center" class="样式11">
																	<bean:write name="ttifsidy" property="amount"
																		format="0.00" />
																	&nbsp;
																</div>
															</td>
															<td height="20">
																<div align="center" class="样式11">
																	<bean:write name="ttifsidy" property="status" />
																	&nbsp;
																</div>
															</td>
														</tr>
													</logic:iterate>
												</table>
												<table width="100%" height="20" border="0" cellpadding="0"
													cellspacing="0">
													<tr>
														<td width="20%" height="52" class="样式2">
															<%
																Integer val = (Integer) session.getAttribute("all");
																if (null == val) {
																	pageContext.forward("/smartcardweb/index.do");
																	return;
																}
																int max = val.intValue();
																if (max - (max / 10) * 10 > 0)
																	max = max / 10 + 1;
																else
																	max = max / 10;
															%>
															<div align="center" class="text_d 样式1">
																总共
																<%=max%>
																页
															</div>
														</td>
														<td width="20%" class="td">
															<div align="center" class="text_d 样式1">
																当前第
																<%=session.getAttribute("page")%>
																页
															</div>
														</td>
														<%
															int cur = ((Integer) session.getAttribute("page")).intValue();
															int currows = ((java.util.ArrayList) session
																	.getAttribute("ttifsidys")).size();
															if (cur > 1) {
														%>
														<td width="15%" align="center" class="td style2">
															<a onMouseDown="javascript:gotoNextPage(<%=p - 1%>)"
																onMouseOver="MM_swapImage('Image1141','','/smartcardweb/pages/images/up2.jpg',1)"
																onMouseOut="MM_swapImgRestore()"><img
																	src="/smartcardweb/pages/images/up1.jpg"
																	name="Image1141" width="60" height="30" border="0"
																	id="Image1">
															</a>
														</td>
														<%
															}
															;
															if (cur < max) {
														%>
														<td width="13%" align="center" class="td style2">
															<a onMouseDown="javascript:gotoNextPage(<%=p + 1%>)"
																onMouseOver="MM_swapImage('Image122','','/smartcardweb/pages/images/down2.jpg',1)"
																onMouseOut="MM_swapImgRestore()"><img
																	src="/smartcardweb/pages/images/down1.jpg"
																	name="Image122" width="60" height="30" border="0"
																	id="Image1">
															</a>
														</td>
														<%
														}
														%>
														<td width="18%" align="right" class="td style2">
															<a
																onMouseDown="javascript: window.location='/smartcardweb/main.do'"
																onMouseOver="MM_swapImage('Image1111','','/smartcardweb/pages/images/fanhui2.jpg',1)"
																onMouseOut="MM_swapImgRestore()"><img
																	src="/smartcardweb/pages/images/fanhui1.jpg"
																	name="Image1111" width="60" height="30" border="0"
																	id="Image1">
															</a>
														</td>
														<td width="14%" align="left" class="td style2">
															<!--div align="center"><a href="/smartcardweb/usrexit.do"><img src="/smartcardweb/pages/images/zx.jpg" width="60" height="30" border="0"></a> </div-->
														</td>
														<!--max=<%=max%>;cur=<%=cur%>;currows=<%=currows%>-->
													</tr>
												</table>
											</div>
											<div id="Layer1"
												style="position:absolute; left:91px; top:155px; width:758px; height:57px; z-index:1; color: #000000;">
												<font size="5" face="隶书">您<%=begin%>~<%=end%>的补助明细如下：</font>
											</div>
										</td>
									</tr>
									<tr>
										<td height="78" align="center">
											<img src="/smartcardweb/pages/images/button.login_ca.jpg"
												width="57" height="57" border="0" usemap="#Map">
										</td>
									</tr>
								</table>
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>

		<map name="Map">
			<area shape="circle" coords="29,27,27"
				onMouseDown="javascript: window.location='/smartcardweb/usrexit.do';">
		</map>

	</body>
</html>
