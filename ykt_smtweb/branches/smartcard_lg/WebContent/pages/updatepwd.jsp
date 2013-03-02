<%@ page contentType="text/html; charset=GBK" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>
<html>
<head>
<title>卡密码修改</title>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<script language="javascript">
        function addnum(num)
        {
		if(customerPwdUpdateForm.nowinput.value=="1" && customerPwdUpdateForm.pwd.value.length < 6){
			customerPwdUpdateForm.pwd.value+=num;
		}
		else if(customerPwdUpdateForm.nowinput.value=="2"  && customerPwdUpdateForm.newPwd.value.length < 6){
			customerPwdUpdateForm.newPwd.value+=num;
		}
 		else if(customerPwdUpdateForm.nowinput.value=="3" && customerPwdUpdateForm.againPwd.value.length < 6){
			customerPwdUpdateForm.againPwd.value+=num;
		}
        }
        function cancelnum()
        {
		if(customerPwdUpdateForm.nowinput.value=="1")
			customerPwdUpdateForm.pwd.value=customerPwdUpdateForm.pwd.value.substring(0,customerPwdUpdateForm.pwd.value.length-1);
		else if(customerPwdUpdateForm.nowinput.value=="2")
			customerPwdUpdateForm.newPwd.value=customerPwdUpdateForm.newPwd.value.substring(0,customerPwdUpdateForm.newPwd.value.length-1);
		else if(customerPwdUpdateForm.nowinput.value=="3")
			customerPwdUpdateForm.againPwd.value=customerPwdUpdateForm.againPwd.value.substring(0,customerPwdUpdateForm.againPwd.value.length-1);
        }       
        function tab()
        {
               if(customerPwdUpdateForm.nowinput.value=="1")
                   customerPwdUpdateForm.newPwd.focus();
               else if(customerPwdUpdateForm.nowinput.value=="2")
                   customerPwdUpdateForm.againPwd.focus();
               else if(customerPwdUpdateForm.nowinput.value=="3")
                   customerPwdUpdateForm.pwd.focus();
        } 
        function writeCard()
        {
              customerPwdUpdateForm.RFScanner.PortNo=0;//读卡器端口设置
              if(customerPwdUpdateForm.pwd.value==''||customerPwdUpdateForm.newPwd.value==''||customerPwdUpdateForm.againPwd.value==''){
              	msg.innerHTML = '密码不能为空';
              	return false;
              }
              var ret=customerPwdUpdateForm.RFScanner.ChangePassWord(
              	customerPwdUpdateForm.paramKey.value,
              	customerPwdUpdateForm.newPwd.value,
              	customerPwdUpdateForm.cardno.value);
              if(ret==1)//修改密码成功
              {
                 customerPwdUpdateForm.submit();
              }   
        }

        </script>
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
<link href="/smartcardweb/pages/css/main.css" rel="stylesheet" type="text/css">
</head>
<!--html:base/-->
<body leftmargin="0" topmargin="0" marginwidth="0" marginheight="0" onload="javascript:document.body.style.overflow='hidden';MM_preloadImages('/smartcardweb/pages/images/denglu2.jpg')">
<form action="/smartcardweb/editpwd.do" method="POST" name="customerPwdUpdateForm">
<input type="hidden" name="nowinput" value="1">
<input type="hidden" name="paramKey" value="<%=session.getAttribute("paramKey")==null ? "" : session.getAttribute("paramKey")%>">
<input type="hidden" name="cardno" value="<%=session.getAttribute("cardno")==null ? "" : session.getAttribute("cardno")%>">
<OBJECT id=RFScanner classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0" height="0"
codebase="/smartcardweb/rf35.cab#version=2,0,0,7"> </OBJECT>
<table width="1024" height="768" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td width="332" height="593"><table width="332" height="768" border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td width="332" height="242"><img src="/smartcardweb/pages/images/login_l_6.jpg" width="332" height="242"></td>
        </tr>
        <tr>
          <td height="324"><table width="332" height="324" border="0" cellpadding="0" cellspacing="0">
              <tr>
                <td width="52" height="324"><img src="/smartcardweb/pages/images/login_l_2.jpg" width="60" height="324"></td>
                <td width="280" height="324">
                  <table width="100%" border="0" cellpadding="0" cellspacing="0">
                    <tr> 
                      <td width="42%" align="center" valign="bottom" class="info">                        <font color="#000000" size="4" face="Arial, Helvetica, sans-serif" class="info">旧   密  码</font></td>
                      <td width="58%" align="left" valign="middle" class="info"> 
                        <input type="password" name="pwd" size="20" maxlength="6" onfocus="javascript:customerPwdUpdateForm.nowinput.value='1';msg.innerHTML='';">
                      </td>
                    </tr>
                    <tr> 
                      <td width="42%" align="center" valign="bottom" class="info">&nbsp;</td>
                      <td width="58%" align="left" class="info">&nbsp;</td>
                    </tr>
                    <tr> 
                      <td width="42%" align="center" valign="bottom" class="info">                        <font color="#000000" face="Arial, Helvetica, sans-serif" class="info">新  密  码</font></td>
                      <td width="58%" height="50%" align="left" valign="middle" class="info"> 
                        <input type="password" name="newPwd" maxlength="6" size="20" onfocus="javascript:customerPwdUpdateForm.nowinput.value='2';msg.innerHTML='';">
                      </td>
                    </tr>
                     <tr> 
                      <td width="42%" align="center" valign="bottom" class="info">&nbsp;</td>
                      <td width="58%" align="left" class="info">&nbsp;</td>
                    </tr>
                      <tr> 
                      <td width="42%" align="center" valign="bottom" class="info">                        <font color="#000000" face="Arial, Helvetica, sans-serif">重复</font><strong><font color="#000000" face="Arial, Helvetica, sans-serif" class="tt"><font color="#000000" face="Arial, Helvetica, sans-serif" class="info">新密码</font></font></strong></td>
                      <td width="58%" align="left" class="info"> 
                        <input type="password" name="againPwd" maxlength="6" size="20" onFocus="javascript:customerPwdUpdateForm.nowinput.value='3';msg.innerHTML='';">
                      </td>
                    </tr>
                    <tr> 
                      <td width="42%" align="center">&nbsp;</td>
                      <td width="58%">&nbsp;</td>
                    </tr>
                    <tr>
                      <td height="50" align="center"><div align="right"><img src="/smartcardweb/pages/images/button_re.jpg" width="57" height="57" border="0" usemap="#Map2"></div></td>
                      <td height="50" align="center"><img src="/smartcardweb/pages/images/button_ca.jpg" width="57" height="57" border="0" usemap="#Map3"></td>
                    </tr>
                    <tr>
                      <td width="42%">&nbsp;</td>
                      <td width="58%">&nbsp;</td>
                    </tr>
                  </table>
                  <table width="100%" border="0" cellpadding="0" cellspacing="0">
                    <tr align="center"> 
                     <td >
                          <p >请 放 入 卡</p>
                        </td>
                    </tr>
                    <tr> 
                      <td class="show" id="msg"><font color="#FF0033"><html:errors/></font></td>
                    </tr>
                  </table>
                </td>
              </tr>
            </table></td>
        </tr>
        <tr>
          <td height="202"><img src="/smartcardweb/pages/images/login_l_3.jpg" width="332" height="202"></td>
        </tr>
      </table></td>
    <td width="692"><img src="/smartcardweb/pages/images/login_r.jpg" width="692" height="768" border="0" usemap="#Map"></td>
  </tr>
</table>
</form>
<map name="Map">
  <area shape="circle" coords="123,261,27"  onmousedown="javascript:addnum(7)">
  <area shape="circle" coords="296,260,27"  onmousedown="javascript:addnum(9)">
  <area shape="circle" coords="209,261,27"  onmousedown="javascript:addnum(8)">
  <area shape="circle" coords="296,346,27"  onmousedown="javascript:addnum(6)">
  <area shape="circle" coords="210,347,27"  onmousedown="javascript:addnum(5)">
  <area shape="circle" coords="121,344,27"  onmousedown="javascript:addnum(4)">
  <area shape="circle" coords="298,434,27"  onmousedown="javascript:addnum(3)">
  <area shape="circle" coords="211,434,27"  onmousedown="javascript:addnum(2)">
  <area shape="circle" coords="123,433,27"  onmousedown="javascript:addnum(1)">
  <area shape="circle" coords="299,521,27"  onmousedown="javascript:tab()">
  <area shape="circle" coords="213,521,27"  onmousedown="javascript:cancelnum()">
  <area shape="circle" coords="124,522,27"  onmousedown="javascript:addnum(0)">
</map>
<map name="Map2">
  <area shape="circle" coords="30,29,27" onmousedown="javascript:writeCard();">
</map>
<map name="Map3">
  <area shape="circle" coords="31,28,28" onmousedown="javascript: window.location='/smartcardweb/main.do';">
</map>
</body>
</html>
