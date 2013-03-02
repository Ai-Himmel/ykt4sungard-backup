<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.dto.TPifAreaDTO"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.List"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<html>
<head>
<title>登录</title>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<script language="javascript">
        function addnum(num)
        {
		if(logonForm.nowinput.value=="1" && logonForm.stuempno.value.length < 10){
			logonForm.stuempno.value+=num;
		}
		else if(logonForm.nowinput.value=="2" && logonForm.password.value.length < 6){
			logonForm.password.value+=num;
		}
        }
        function cancelnum()
        {
		if(logonForm.nowinput.value=="1")
			logonForm.stuempno.value=logonForm.stuempno.value.substring(0,logonForm.stuempno.value.length-1);
		else if(logonForm.nowinput.value=="2")
			logonForm.password.value=logonForm.password.value.substring(0,logonForm.password.value.length-1);


        }
        function tab()
        {
              if(logonForm.nowinput.value=="1")
                 logonForm.password.focus();
              else if(logonForm.nowinput.value=="2")
                 logonForm.stuempno.focus();
        }
       
       
        </script>
<link href="/smartcardweb/pages/css/main.css" rel="stylesheet"
	type="text/css">
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
//-->
</script>
</head>
<!--html:base/-->
<body leftmargin="0" topmargin="0" marginwidth="0" marginheight="0"
	onload="javascript:document.body.style.overflow='hidden';MM_preloadImages('/smartcardweb/pages/images/denglu2.gif','/smartcardweb/pages/images/quxiao2.gif')">
<form action="/smartcardweb/userlogon.do" method="POST" name="logonForm">
<input type="hidden" name="nowinput" value="1" />
<table width="1024" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td align="left" valign="top"><img
			src="/smartcardweb/pages/images/jian1.jpg" width="1024" height="139"></td>
	</tr>
	<tr>
		<td height="280" align="left" valign="top"
			background="/smartcardweb/pages/images/jian2.jpg">
		<TABLE cellSpacing=0 cellPadding=0 width="60%" border=0>
			<TBODY>
				<TR align=left>
					<TD width="30%" align=right vAlign=bottom>&nbsp;</TD>
					<TD height="60" colspan="2" align=left vAlign=middle>&nbsp;</TD>
				</TR>
				<TR align=left>
					<TD vAlign=bottom align=right>&nbsp;</TD>
					<TD align=center vAlign=middle><span class="STYLE2">学/工号</span></TD>
					<TD align="left" vAlign=middle><input type="text" name="stuempno"
						class="info" size="20" maxlength="10"
						onFocus="javascript:logonForm.nowinput.value='1'"></TD>
				</TR>
				<TR align="left">
					<TD align="right">&nbsp;</TD>
					<TD align="center" valign="middle">&nbsp;</TD>
					<TD align="left" valign="middle">&nbsp;</TD>
				</TR>
				<TR align=left>
					<TD vAlign=bottom align=right>&nbsp;</TD>
					<TD vAlign=middle align=center><span class="STYLE2">密&nbsp;&nbsp;&nbsp;码<FONT
						color=#000000 face="Arial, Helvetica, sans-serif"></FONT><FONT
						color=#000000 face="Arial, Helvetica, sans-serif"></FONT></span></TD>
					<TD align="left" vAlign=middle><input name="password"
						type="password" class="info"
						onFocus="javascript:logonForm.nowinput.value='2'" size="20"
						maxlength="6"></TD>
				</TR>
				<TR>
					<TD>&nbsp;</TD>
					<TD height="50" colspan="2" align="left" valign="middle">(注意：初始密码详见使用帮助)</TD>
				</TR>
				<tr>
					<TD align="center">&nbsp;</TD>
					<td class="show" colspan="2"><span class="info"><font color="#FF0033"><html:errors /></font><font
						color="#FF0033"></font></span></td>
				</tr>

				<TR>
					<TD align="center">&nbsp;</TD>
					<TD align="center">&nbsp;</TD>
					<TD align=left valign="top"><IMG height=57
						src="/smartcardweb/pages/images/button_re1.gif" width=57
						onmousedown="javascript:logonForm.submit()" border=0>
					&nbsp;&nbsp;&nbsp;&nbsp;<IMG height=57
						src="/smartcardweb/pages/images/button_ca1.gif" width=57
						onclick="javascript: window.location='/smartcardweb/index.do';"
						border=0></TD>
				</TR>
			</TBODY>
		</TABLE>
		</td>
	</tr>
	<tr>
		<td align="left" valign="top"><img
			src="/smartcardweb/pages/images/jian3.jpg" width="1024" height="350"
			border="0" usemap="#Map"></td>
	</tr>
</table>
</FORM>

<map name="Map">
	<area shape="rect" coords="776,218,831,273" onmousedown="javascript:cancelnum()">
	<area shape="rect" coords="192,217,248,275" onmousedown="javascript:tab()">
	<area shape="rect" coords="158,19,213,75" onmousedown="javascript:addnum(1)">
	<area shape="rect" coords="230,18,287,76" onmousedown="javascript:addnum(2)">
	<area shape="rect" coords="305,21,360,75" onmousedown="javascript:addnum(3)">
	<area shape="rect" coords="378,19,435,76" onmousedown="javascript:addnum(4)">
	<area shape="rect" coords="449,19,507,75" onmousedown="javascript:addnum(5)">	
	<area shape="rect" coords="523,18,581,75" onmousedown="javascript:addnum(6)">
	<area shape="rect" coords="596,19,654,76" onmousedown="javascript:addnum(7)">
	<area shape="rect" coords="670,19,727,77" onmousedown="javascript:addnum(8)">
	<area shape="rect" coords="742,16,800,76" onmousedown="javascript:addnum(9)">	
	<area shape="rect" coords="814,18,873,76" onmousedown="javascript:addnum(0)">
	
	<area shape="rect" coords="598,85,654,141" onmousedown="javascript:addnum('U')">
	<area shape="rect" coords="815,84,874,140" onmousedown="javascript:addnum('P')">
	<area shape="rect" coords="742,85,801,141" onmousedown="javascript:addnum('O')">
	<area shape="rect" coords="451,85,508,140" onmousedown="javascript:addnum('T')">
	<area shape="rect" coords="380,85,435,142" onmousedown="javascript:addnum('R')">
	<area shape="rect" coords="669,83,726,140" onmousedown="javascript:addnum('I')">
	<area shape="rect" coords="306,85,361,140" onmousedown="javascript:addnum('E')">
	<area shape="rect" coords="233,84,287,141" onmousedown="javascript:addnum('W')">
	<area shape="rect" coords="158,84,216,141" onmousedown="javascript:addnum('Q')">
	<area shape="rect" coords="524,84,579,140" onmousedown="javascript:addnum('Y')">

	<area shape="rect" coords="776,151,832,206" onmousedown="javascript:addnum('L')">
	<area shape="rect" coords="702,151,759,209" onmousedown="javascript:addnum('K')">
	<area shape="rect" coords="629,151,686,207" onmousedown="javascript:addnum('J')">
	<area shape="rect" coords="556,150,615,208" onmousedown="javascript:addnum('H')">
	<area shape="rect" coords="483,151,540,206" onmousedown="javascript:addnum('G')">
	<area shape="rect" coords="410,151,467,207" onmousedown="javascript:addnum('F')">
	<area shape="rect" coords="337,151,397,207" onmousedown="javascript:addnum('D')">
	<area shape="rect" coords="264,151,325,207" onmousedown="javascript:addnum('S')">
	<area shape="rect" coords="191,151,248,208" onmousedown="javascript:addnum('A')">
	<area shape="rect" coords="704,217,759,272" onmousedown="javascript:addnum('M')">
	<area shape="rect" coords="629,218,686,275" onmousedown="javascript:addnum('N')">
	<area shape="rect" coords="556,217,614,274" onmousedown="javascript:addnum('B')">
	<area shape="rect" coords="483,217,540,273" onmousedown="javascript:addnum('V')">
	<area shape="rect" coords="410,218,469,274" onmousedown="javascript:addnum('C')">
	<area shape="rect" coords="337,217,397,275" onmousedown="javascript:addnum('X')">
	<area shape="rect" coords="264,217,320,275" onmousedown="javascript:addnum('Z')">
</map>
</BODY>
</html>
