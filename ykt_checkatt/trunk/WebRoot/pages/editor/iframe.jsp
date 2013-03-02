<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<% 
response.setHeader("Pragma","No-cache"); 
response.setHeader("Cache-Control","no-cache"); 
response.setDateHeader("Expires", 0); 
%> 
<html><HEAD><title>插入网页文件</title>
<META content="text/html; charset=UTF-8" http-equiv=Content-Type>
<META HTTP-EQUIV="Pragma" CONTENT="no-cache"> 
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache"> 
<META HTTP-EQUIV="Expires" CONTENT="0"> 
<link rel="stylesheet" type="text/css" href="site.css">
<SCRIPT event=onclick for=Ok language=JavaScript>
window.returnValue = a.value+"*"+b.value+"*"+c.value+"*"+d.value+"*"+e.value+"*"+f.value+"*"+g.value
window.close();
</script>
<script>
function IsDigit()
{
  return ((event.keyCode >= 48) && (event.keyCode <= 57));
}
</script>
<body bgcolor=menu topmargin=15 leftmargin=15 ><CENTER><br>
<table width="100%" border="0"><tr><td><FIELDSET align=left><LEGEND align=left>插入网页文件</LEGEND>
<table width="100%" border="0"><tr><td align="right">文件地址：</td><td><input id=a value='http://' size=35></td></tr>
<tr><td align=right>滚动条：</td><td><select id=b><option value=noshade>无<option value=yes>有</select>&nbsp;&nbsp;边框线：<select id=c><option value=0>无 <option value=1>有</select></td></tr>
<tr><td align=right>上下边距：</td><td ><input id=d size=4 maxlength=2 value="0" ONKEYPRESS="event.returnValue=IsDigit();">左右边距：<input  id=e size=4 maxlength=2 value="0" ONKEYPRESS="event.returnValue=IsDigit();"></td></tr>
<tr><td align="right">文件宽度：</td><td ><input id=f size=4 maxlength=4 value=500 ONKEYPRESS="event.returnValue=IsDigit();">文件高度：<input id=g size=4 maxlength=4 value=400 ONKEYPRESS="event.returnValue=IsDigit();"></td></tr>
<tr><td colspan="2">&nbsp;</td></tr></table>
</fieldset></td><td width=80 align="center"><input type=submit value='   确定   ' id=Ok><br><br><input type=button value='   取消   ' onclick="window.close();"></td>
  </tr>
</table>


