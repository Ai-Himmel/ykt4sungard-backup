<%@ page contentType="text/html; charset=GBK" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>
<html>
<head>
<title>登录</title>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<script language="javascript">
        function addnum(num)
        {
		if(logonForm.password.value.length < 6){
			logonForm.password.value+=num;
		}
        }
        function cancelnum()
        {
		logonForm.password.value=logonForm.password.value.substring(0,logonForm.password.value.length-1);
        }
        function tab()
        {
                 logonForm.password.focus();
        }
        function readCard()
        {
                 //logonForm.RFScanner.PortNo=2;
                 var ret=logonForm.RFScanner.DoScan();
                 if(ret==1){//读卡成功
                    logonForm.cardno.value=logonForm.RFScanner.CardNo;
                    logonForm.submit();
                 }
        }


        </script>
<link href="/smartcardweb/pages/css/main.css" rel="stylesheet" type="text/css">
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

<body leftmargin="0" topmargin="0" marginwidth="0" marginheight="0" onload="javascript:document.body.style.overflow='hidden';MM_preloadImages('/smartcardweb/pages/images/denglu2.gif','/smartcardweb/pages/images/quxiao2.gif')">
<form action="/smartcardweb/logon.do" method="POST" name="logonForm">
<input type="hidden" name="nowinput" value="1"/>
<table width="1024" height="768" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td width="332" height="593"><table width="332" height="768" border="0" cellpadding="0" cellspacing="0">
        <tr>
            <td width="332" height="242"><img src="pages/images/login_l_1.jpg" name="Image1" width="332" height="242" id="Image1"></td>
        </tr>
        <tr>
          <td height="324"><table width="332" height="324" border="0" cellpadding="0" cellspacing="0">
              <tr>
                  <td width="52" height="324"><img src="pages/images/login_l_2.jpg" width="60" height="324"></td>
                <td width="280" height="324"> <table width="100%" border="0" cellpadding="0" cellspacing="0">   
                    <tr align="left">
                      <td width="42%" align="center" valign="bottom"> <font color="#000000" size="4" face="Arial, Helvetica, sans-serif" class="info">&nbsp;</font></td>
                      <td width="58%" valign="middle"> 
                       <OBJECT id=RFScanner classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0" height="0"> </OBJECT>
                       请 放 入 卡
                       <input type="hidden" name="cardno">
                      </td>
                    </tr>
                    <tr align="center">
                      <td width="42%">&nbsp;</td>
                      <td width="58%">&nbsp;</td>
                    </tr>
                    <tr align="left">
                      <td width="42%" align="center" valign="bottom"><font color="#000000" size="4" face="Arial, Helvetica, sans-serif" class="info">密码</font></td>
                      <td width="58%" height="50%" valign="middle"> <span class="info"><input name="password" type="password"  class="info" onFocus="javascript:logonForm.nowinput.value='2'" size="20" maxlength="6">
                      </span></td>
                    </tr>
                    <tr>
                      <td width="58%">&nbsp;</td>
                    </tr>
                    <tr>
                       <td width="58%">&nbsp;</td>
                    </tr>
                    <tr>
                      <td width="42%" height="50" align="center"><div align="right"><span class="info"><img src="pages/images/button_re.jpg" width="57" height="57" border="0" usemap="#Map2" ></span></div></td>
                        <td width="58%" height="50" align="center"><span class="info"><img src="pages/images/button_ca.jpg"  width="57" height="57" border="0" usemap="#Map3"></span></td>
                    </tr>
                    <tr>
                      <td width="58%">&nbsp;</td>
                    </tr>
                  </table>
                  <table width="100%" border="0" cellpadding="0" cellspacing="0">
                    <tr>
                        <td >
                          <p >注意：初始密码为666666</p>
                        </td>
                    </tr>
                    <tr>
                      <td class="show"><span class="info"><font color="#FF0033"><html:errors/></font><font color="#FF0033"></font></span></td>
                    </tr>
                  </table>
                  </td>
              </tr>
            </table></td>
        </tr>
        <tr>
            <td height="202"><span class="info"><img src="pages/images/login_l_3.jpg" width="332" height="202"></span></td>
        </tr>
      </table></td>
      <td width="692"><span class="info"><img src="pages/images/login_r.jpg" width="692" height="768" border="0" usemap="#Map"></span></td>
  </tr>
</table>
</form>
<span class="info"><map name="Map">
  
  <area shape="circle" coords="123,261,27"  onmousedown="javascript:addnum(7)">
  <area shape="circle" coords="296,260,27"  onmousedown="javascript:addnum(9)">
  <area shape="circle" coords="209,261,27"  onmousedown="javascript:addnum(8)">
  <area shape="circle" coords="296,346,27"  onmousedown="javascript:addnum(6)">
  <area shape="circle" coords="210,347,27"  onmousedown="javascript:addnum(5)">
  <area shape="circle" coords="121,344,27"  onmousedown="javascript:addnum(4)">
  <area shape="circle" coords="298,434,27"  onmousedown="javascript:addnum(3)">
  <area shape="circle" coords="211,434,27"  onmousedown="javascript:addnum(2)">
  <area shape="circle" coords="122,433,27"  onmousedown="javascript:addnum(1)">
  <area shape="circle" coords="299,521,27"  onmousedown="javascript:tab()">
  <area shape="circle" coords="213,521,27"  onmousedown="javascript:cancelnum()">
  <area shape="circle" coords="124,522,27"  onmousedown="javascript:addnum(0)">
  
</map>
</span>
<map name="Map2">
  <area shape="circle" coords="28,28,26"  onmousedown="javascript:readCard();">
</map>
<map name="Map3">
  <area shape="circle" coords="29,28,27" onmousedown ="javascript: window.location='/smartcardweb/index.do';">
</map>
</body>
</html>
