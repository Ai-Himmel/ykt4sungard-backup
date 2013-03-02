<%@ page contentType="text/html; charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<html>
<head>
<title>补助信息查询</title>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<script language="javascript">
        function addnum(num)
        {
		if(tradeSerialForm.nowinput.value=="1" && tradeSerialForm.begin.value.length < 8 ){
			tradeSerialForm.begin.value+=num;
		}
		else if(tradeSerialForm.nowinput.value=="2" && tradeSerialForm.end.value.length < 8 ){
			tradeSerialForm.end.value+=num;
		}
        }
        function cancelnum()
        {
		if(tradeSerialForm.nowinput.value=="1")
			tradeSerialForm.begin.value=tradeSerialForm.begin.value.substring(0,tradeSerialForm.begin.value.length-1);
		else if(tradeSerialForm.nowinput.value=="2")
			tradeSerialForm.end.value=tradeSerialForm.end.value.substring(0,tradeSerialForm.end.value.length-1);
			
		
        }        
        function tab()
        {
              if(tradeSerialForm.nowinput.value=="1")
                 tradeSerialForm.end.focus();
              else if(tradeSerialForm.nowinput.value=="2")
                 tradeSerialForm.begin.focus();
        }
        function setDate()
        {
            var dDate = new Date();
            var year= dDate.getFullYear();
            var month= dDate.getMonth()+1;
            var day=dDate.getDate();
            if(month<10) month="0"+month;
            if(day<10) day="0" +day;
            tradeSerialForm.end.value=year+""+month+""+day;

            year= dDate.getFullYear();
            month= dDate.getMonth();
            day=dDate.getDate();
            day=day-7;
            dDate=new Date(year,month,day);
            year= dDate.getFullYear();
            month= dDate.getMonth()+1;
            day=dDate.getDate();
            if(month<10) month="0"+month;
            if(day<10) day="0" +day;
            tradeSerialForm.begin.value=year+""+month+""+day;
            

        }
        </script>
<link href="main.css" rel="stylesheet" type="text/css">
		<style type="text/css">
		<!--
		
		.样式12 {
		font-family: "宋体"; 
		color: #000000; 
		font-size: 16; 
		}
		.样式13 {
		font-family: "隶书"; 
		color: #000000; 
		font-size: 18; 
		}
		-->
		</style>
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
<link href="/smartcardweb/pages/css/main.css" rel="stylesheet"
	type="text/css">
<style type="text/css">
<!--
.样式1 {color: #000000}
-->
</style>
</head>
<!--html:base/-->
<body leftmargin="0" topmargin="0" marginwidth="0" marginheight="0"
	onLoad="javascript:document.body.style.overflow='hidden';MM_preloadImages('/smartcardweb/pages/images/denglu2.gif','/smartcardweb/pages/images/quxiao2.gif');javascript:setDate()">
<form action="/smartcardweb/queryassistance.do" method="POST"
	name="tradeSerialForm"><input type="hidden" name="nowinput" value="1" />
<table width="1024" height="768" border="0" cellpadding="0"
	cellspacing="0">
	<tr>
		<td width="332" height="593">
		<table width="332" height="768" border="0" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="332" height="242"><img src="/smartcardweb/pages/images/login_l_5_1.jpg"
					name="Image1" width="332" height="242" id="Image1"></td>
			</tr>
			<tr>
				<td height="324">
				<table width="332" height="324" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td width="52" height="324"><img src="/smartcardweb/pages/images/login_l_2_1.jpg"
							width="60" height="324"></td>
						<td width="280" height="324">
						<table width="100%" border="0" cellpadding="0" cellspacing="0">
							<tr align="left">
								<td width="42%" align="center" valign="bottom" class="info">开始日期</td>
								<td width="58%" valign="middle"><input type="text" name="begin"
									size="20" maxlength="8"
									onFocus="javascript:tradeSerialForm.nowinput.value='1'"></td>
							</tr>
							<tr align="center" >
								<td width="42%" class="info">&nbsp;</td>
								<td width="58%" class="info">&nbsp;</td>
							</tr>
							<tr align="left">
								<td width="42%" align="center" valign="bottom" class="info">截至日期</td>
								<td width="58%" height="50%" valign="middle"><input name="end"
									type="text"
									onFocus="javascript:tradeSerialForm.nowinput.value='2'"
									size="20" maxlength="8"></td>
							</tr>
							<tr>
								<td width="42%" class="info">&nbsp;</td>
								<td width="58%" class="info">&nbsp;</td>
							</tr>
							<tr>
								<td width="42%" height="18" align="center" class="info">&nbsp;</td>
								<td width="58%" class="info">&nbsp;</td>
							</tr>
							<tr>
								<td width="42%" height="50" align="center"><img
									src="/smartcardweb/pages/images/button_re.jpg" width="57" height="57" border="0"
									usemap="#Map2"></td>
								<td width="58%" height="50" align="center"><img
									src="/smartcardweb/pages/images/button_ca.jpg" width="57" height="57" border="0"
									usemap="#Map3"></td>
							</tr>
							<tr>
								<td width="42%" class="info"> &nbsp;</td>
								<td width="58%" class="info">&nbsp;</td>
							</tr>
						</table>
						<table width="100%" border="0" cellpadding="0" cellspacing="0">
							<tr>
								<td class="info"><strong>例如:</strong></td>
							</tr>
							<tr>
								<td><span class="info">日期:</span>2005年1月1日 <br />
								<span class="info">输入格式：</span>20050101</td>
							</tr>
							<tr>
								<td class="show">&nbsp;</td>
							</tr>
							<tr>
								<td class="show">&nbsp;</td>
							</tr>
						</table>
						</td>
					</tr>
				</table>
				</td>
			</tr>
			<tr>
				<td height="202"><img src="/smartcardweb/pages/images/login_l_3_1.jpg" width="332"
					height="202"></td>
			</tr>
		</table>
		</td>
		<td width="692">
		<table width="692" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td width="174" align="left"><img name="login_r_1_r1_c1"
					src="/smartcardweb/pages/images/login_r_1_r1_c1.jpg" width="174" height="96" border="0"></td>
				<td width="185" align="left"><img name="login_r_1_r1_c2"
					src="/smartcardweb/pages/images/login_r_1_r1_c2.jpg" width="185" height="96" border="0"></td>
				<td width="174" align="left"><img name="login_r_1_r1_c3"
					src="/smartcardweb/pages/images/login_r_1_r1_c3.jpg" width="174" height="96" border="0"></td>
				<td align="left"><img name="login_r_1_r1_c4"
					src="/smartcardweb/pages/images/login_r_1_r1_c4.jpg" width="159" height="96" border="0"></td>
			</tr>
			<tr>
				<td align="left"><img name="login_r_1_r2_c1"
					src="/smartcardweb/pages/images/login_r_1_r2_c1.jpg" width="174" height="94" border="0"></td>
				<td align="left"><img name="login_r_1_r2_c2"
					src="/smartcardweb/pages/images/login_r_1_r2_c2.jpg" width="185" height="94" border="0"></td>
				<td align="left"><img name="login_r_1_r2_c3"
					src="/smartcardweb/pages/images/login_r_1_r2_c3.jpg" width="174" height="94" border="0"></td>
				<td align="left"><img name="login_r_1_r2_c4"
					src="/smartcardweb/pages/images/login_r_1_r2_c4.jpg" width="159" height="94" border="0"></td>
			</tr>
			<tr>
				<td colspan="2" rowspan="4" align="left"><img
					src="/smartcardweb/pages/images/login_r_1_r3_c1.jpg" name="login_r_1_r3_c1" width="359"
					height="404" border="0" usemap="#login_r_1_r3_c1Map"></td>
				<td align="left"><img name="login_r_1_r3_c3"
					src="/smartcardweb/pages/images/login_r_1_r3_c3.jpg" width="174" height="95" border="0"></td>
				<td align="left"><img name="login_r_1_r3_c4"
					src="/smartcardweb/pages/images/login_r_1_r3_c4.jpg" width="159" height="95" border="0"></td>
			</tr>
			<tr>
				<td align="left"><img name="login_r_1_r4_c3"
					src="/smartcardweb/pages/images/login_r_1_r4_c3.jpg" width="174" height="108"
					border="0"></td>
				<td align="left"><img name="login_r_1_r4_c4"
					src="/smartcardweb/pages/images/login_r_1_r4_c4.jpg" width="159" height="108"
					border="0"></td>
			</tr>
			<tr>
				<td align="left"><img name="login_r_1_r5_c3"
					src="/smartcardweb/pages/images/login_r_1_r5_c3.jpg" width="174" height="99" border="0"></td>
				<td align="left"><img name="login_r_1_r5_c4"
					src="/smartcardweb/pages/images/login_r_1_r5_c4.jpg" width="159" height="99" border="0"></td>
			</tr>
			<tr>
				<td align="left"><img name="login_r_1_r6_c3"
					src="/smartcardweb/pages/images/login_r_1_r6_c3.jpg" width="174" height="102"
					border="0"></td>
				<td align="left"><img name="login_r_1_r6_c4"
					src="/smartcardweb/pages/images/login_r_1_r6_c4.jpg" width="159" height="102"
					border="0"></td>
			</tr>
			<tr>
				<td align="left"><img name="login_r_1_r7_c1"
					src="/smartcardweb/pages/images/login_r_1_r7_c1.jpg" width="174" height="93" border="0"></td>
				<td align="left"><img name="login_r_1_r7_c2"
					src="/smartcardweb/pages/images/login_r_1_r7_c2.jpg" width="185" height="93" border="0"></td>
				<td align="left"><img name="login_r_1_r7_c3"
					src="/smartcardweb/pages/images/login_r_1_r7_c3.jpg" width="174" height="93" border="0"></td>
				<td align="left"><img name="login_r_1_r7_c4"
					src="/smartcardweb/pages/images/login_r_1_r7_c4.jpg" width="159" height="93" border="0"></td>
			</tr>
			<tr>
				<td align="left"><img name="login_r_1_r8_c1"
					src="/smartcardweb/pages/images/login_r_1_r8_c1.jpg" width="174" height="81" border="0"></td>
				<td align="left"><img name="login_r_1_r8_c2"
					src="/smartcardweb/pages/images/login_r_1_r8_c2.jpg" width="185" height="81" border="0"></td>
				<td align="left"><img name="login_r_1_r8_c3"
					src="/smartcardweb/pages/images/login_r_1_r8_c3.jpg" width="174" height="81" border="0"></td>
				<td align="left"><img name="login_r_1_r8_c4"
					src="/smartcardweb/pages/images/login_r_1_r8_c4.jpg" width="159" height="81" border="0"></td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</form>
<map name="Map2">
	<area shape="circle" coords="28,28,27"
		onMouseDown="javascript:tradeSerialForm.submit()">
</map>
<map name="Map3">
	<area shape="circle" coords="29,29,28"
		onMouseDown="javascript: window.location='/smartcardweb/main.do';">
</map>

<map name="login_r_1_r3_c1Map">
	<area shape="circle" coords="299,331,29" onmousedown="javascript:tab()">
	<area shape="circle" coords="212,330,29"
		onmousedown="javascript:cancelnum()">
	<area shape="circle" coords="125,331,29"
		onmousedown="javascript:addnum(0)">
	<area shape="circle" coords="299,243,29"
		onmousedown="javascript:addnum(3)">
	<area shape="circle" coords="211,243,29"
		onmousedown="javascript:addnum(2)">
	<area shape="circle" coords="122,242,29"
		onmousedown="javascript:addnum(1)">
	<area shape="circle" coords="122,153,29"
		onmousedown="javascript:addnum(4)">
	<area shape="circle" coords="210,156,29"
		onmousedown="javascript:addnum(5)">
	<area shape="circle" coords="299,156,29"
		onmousedown="javascript:addnum(6)">
	<area shape="circle" coords="296,70,29"
		onmousedown="javascript:addnum(9)">
	<area shape="circle" coords="208,71,29"
		onmousedown="javascript:addnum(8)">
	<area shape="circle" coords="124,72,29"
		onmousedown="javascript:addnum(7)">
</map>
</body>
</html>

