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
.��ʽ1 {font-size: None}
.��ʽ2 {color: #FFFFFF}
.��ʽ3 {font-size: None; color: #FFFFFF; }
.��ʽ5 {
	color: #000000;
	font-size: 14px;
}
.��ʽ7 {font-size: 14px}
-->
</style>
</head>
<html:base/>
<%
	com.kingstargroup.fdykt.dto.AccountDTO acc = (com.kingstargroup.fdykt.dto.AccountDTO)session.getAttribute("account");
        String state = acc.getState_id();
        String tmp = "";
        if(state.equals("1000")){
        	tmp = "����";
        }else if(state.equals("2000")){
          	tmp = "ע��";
        }else if(state.equals("1100")){
          	tmp = "��ʧ";
        }else if(state.equals("1010")){
          	tmp = "����";
        }else if(state.equals("1001")){
          	tmp = "д��ʧ��";
        }else if(state.equals("1110")){
          	tmp = "��ʧ����";
        }else if(state.equals("1111")){
          	tmp = "��ʧ����д��ʧ��";
        }
        String open_Date=acc.getOpen_Date();
        String close_Date=acc.getClose_Date();
        if(open_Date!=null && open_Date.length()==8) 
           open_Date=open_Date.substring(0,4)+"��"+open_Date.substring(4,6)+"��"+open_Date.substring(6,8)+"��";
        if(close_Date!=null && close_Date.length()==8)
           close_Date=close_Date.substring(0,4)+"��"+close_Date.substring(4,6)+"��"+close_Date.substring(6,8)+"��";
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
                  <div align="center" class="��ʽ1 ��ʽ2">�ͻ���</div></td>
                <td width="226" class="show">
                  <div align="center">
                      <div id="Layer1" style="position:absolute; left:34px; top:168px; width:560px; height:73px; z-index:1;font-size: 24px;"><font face="����">�������Ƿ�ȷ�Ϲ�ʧ�ÿ���</font></div>
                      <bean:write name="account" property="cut_name"/>&nbsp;</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="��ʽ3">�ʺ�</div></td>
                <td width="226">
                  <div align="center" class="��ʽ5 ��ʽ7"><bean:write name="account" property="account_id"/>&nbsp;</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="��ʽ3">����</div></td>
                <td width="226">
                  <div align="center" class="��ʽ5"><bean:write name="account" property="card_id"/>&nbsp;</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="��ʽ3">��״̬</div></td>
                <td width="226">
                  <div align="center" class="��ʽ5"><%=tmp%>&nbsp;</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="��ʽ3">�������</div></td>
                <td width="226">
                  <div align="center" class="��ʽ5"><bean:write name="account" property="cur_FreeBala" format="0.00"/>Ԫ</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="��ʽ3">�������</div></td>
                <td width="226">
                  <div align="center" class="��ʽ5"><bean:write name="account" property="cur_FrozeBala" format="0.00"/>Ԫ</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="��ʽ3">��������</div></td>
                <td width="226">
                  <div align="center" class="��ʽ5"><%=open_Date%>&nbsp;</div></td>
              </tr>
              <tr bordercolor="#3399CC" bgcolor="#FFFFFF">
                <td width="119" height="40" bgcolor="#D8ACCD" class="an">
                  <div align="center" class="��ʽ3">��Ч����</div></td>
                <td width="226">
                  <div align="center" class="��ʽ5"><%=close_Date%>&nbsp;</div></td>
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
