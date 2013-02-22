<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<% 
response.setHeader("Pragma","No-cache"); 
response.setHeader("Cache-Control","no-cache"); 
response.setDateHeader("Expires", 0); 
%> 
<html><HEAD><TITLE>RealPlay文件</TITLE>
<META HTTP-EQUIV="Pragma" CONTENT="no-cache"> 
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache"> 
<META HTTP-EQUIV="Expires" CONTENT="0"> 
<link rel="stylesheet" type="text/css" href="site.css">
<SCRIPT event=onclick for=Ok language=JavaScript>
  window.returnValue = path.value+"*"+selrow.value+"*"+selcol.value
  window.close();
</SCRIPT>
<script>
function IsDigit()
{
  return ((event.keyCode >= 48) && (event.keyCode <= 57));
}
</script>
<body bgColor=menu topmargin=15 leftmargin=15 >
<CENTER><BR>
<table width=100%><tr><td>
<FIELDSET align=left>
<LEGEND align=left>插入网上RealPlay文件</LEGEND>
<table>
<tr><td >地址：<input id=path size=35  value="http://"></td></tr>
<tr><td >宽度：<input id=selrow ONKEYPRESS="event.returnValue=IsDigit();" value=500 size=7 maxlength="4" > &nbsp;&nbsp;高度：<input id=selcol ONKEYPRESS="event.returnValue=IsDigit();" value=300 size=7 maxlength="4"></td></tr>
<tr><td align=center>支持格式为：rm、ra、ram</td></tr>
 </table></fieldset></td><td width=80 align="center"><input type=submit value='   确定   ' id=Ok><br><br><input type=button value='   取消   ' onclick="window.close();"></td></tr></table>
