<%@ page contentType="text/html;charset=GBK" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>card</title>
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
<style type="text/css">
<!--
.样式1 {font-size: None}
.样式2 {color: #FFFFFF}
.样式3 {font-size: None; color: #FFFFFF; }
.样式5 {
	color: #000000;
	font-size: 14px;
}
.样式7 {font-size: 14px}
-->
</style>
</head>
<html:base/>
<%
	com.kingstargroup.fdykt.dto.AccountDTO acc = (com.kingstargroup.fdykt.dto.AccountDTO)session.getAttribute("account");
        String state = acc.getState_id();
        String tmp = "";
        if(state.equals("1000")){
        	tmp = "正常";
        }else if(state.equals("2000")){
          	tmp = "注销";
        }else if(state.equals("1100")){
          	tmp = "挂失";
        }else if(state.equals("1010")){
          	tmp = "冻结";
        }else if(state.equals("1001")){
          	tmp = "写卡失败";
        }else if(state.equals("1110")){
          	tmp = "挂失冻结";
        }else if(state.equals("1111")){
          	tmp = "挂失冻结写卡失败";
        }
        String open_Date=acc.getOpen_Date();
        String close_Date=acc.getClose_Date();
        if(open_Date!=null && open_Date.length()==8) 
           open_Date=open_Date.substring(0,4)+"年"+open_Date.substring(4,6)+"月"+open_Date.substring(6,8)+"日";
        if(close_Date!=null && close_Date.length()==8)
           close_Date=close_Date.substring(0,4)+"年"+close_Date.substring(4,6)+"月"+close_Date.substring(6,8)+"日";
%>
<body leftmargin="0" topmargin="0" marginwidth="0" marginheight="0" onload="javascript:document.body.style.overflow='hidden'">
<table width="1024" height="768" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td height="768" valign="top" background="images/login_no.jpg"><table width="525" height="768" border="0" cellpadding="0" cellspacing="0">
      <tr>
        <td width="85" height="51">&nbsp;</td>
        <td width="440">&nbsp;</td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td valign="top"><table width="432" height="662" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="432" height="98">&nbsp;</td>
          </tr>
          <tr>
            <td height="482" align="center" class="show"><table width="377" border="1" cellpadding="0" cellspacing="0" bordercolor="#6699FF">
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="样式1 样式2">客户名</div></td>
                <td width="226" class="show">
                  <div align="center">
                      <div id="Layer1" style="position:absolute; left:34px; top:168px; width:560px; height:73px; z-index:1;font-size: 24px;"><font face="隶书">请问您是否确认挂失该卡？</font></div>
                      <bean:write name="account" property="cut_name"/>&nbsp;</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="样式3">帐号</div></td>
                <td width="226">
                  <div align="center" class="样式5 样式7"><bean:write name="account" property="account_id"/>&nbsp;</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="样式3">卡号</div></td>
                <td width="226">
                  <div align="center" class="样式5"><bean:write name="account" property="card_id"/>&nbsp;</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="样式3">卡状态</div></td>
                <td width="226">
                  <div align="center" class="样式5"><%=tmp%>&nbsp;</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="样式3">可用余额</div></td>
                <td width="226">
                  <div align="center" class="样式5"><bean:write name="account" property="cur_FreeBala" format="0.00"/>元</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="样式3">冻结余额</div></td>
                <td width="226">
                  <div align="center" class="样式5"><bean:write name="account" property="cur_FrozeBala" format="0.00"/>元</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="样式3">开户日期</div></td>
                <td width="226">
                  <div align="center" class="样式5"><%=open_Date%>&nbsp;</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="样式3">有效期至</div></td>
                <td width="226">
                  <div align="center" class="样式5"><%=close_Date%>&nbsp;</div></td>
              </tr>
            </table> 
          <html:errors/>
          </td>
          </tr>
          <tr>
            <td height="78" align="center"><table width="100%" border="0" cellpadding="0" cellspacing="0" height="4%">
              <tr>
                <td width="80%" height="85" align="right"><img src="images/guashi.jpg" width="57" height="57" border="0" usemap="#Map2"><img src="images/fanhui.jpg" width="57" height="57" border="0" usemap="#Map"></td>
              </tr>
            </table>
         </td>
          </tr>
        </table></td>
      </tr>
    </table></td>
  </tr>
</table>
<map name="Map">
  <area shape="circle" coords="29,29,26" onmousedown="javascript: window.location='/smartcardweb/usrexit.do';">
</map>
<map name="Map2">
  <area shape="circle" coords="29,28,27" onmousedown="javascript: window.location='/smartcardweb/lossresult.do';">
</map>
</body>
</html>
