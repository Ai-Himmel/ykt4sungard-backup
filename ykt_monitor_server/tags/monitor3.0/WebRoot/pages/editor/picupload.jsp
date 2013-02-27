<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="/tags/struts-tiles" prefix="tiles" %>
<%@ taglib uri="/tags/struts-bean" prefix="bean" %>
<%@ taglib uri="/tags/struts-html" prefix="html" %>
<%@ taglib uri="/tags/struts-logic" prefix="logic" %>
<%@ taglib uri="/tags/struts-nested" prefix="nested" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jstl/core" %>
<% 
response.setHeader("Pragma","No-cache"); 
response.setHeader("Cache-Control","no-cache"); 
response.setDateHeader("Expires", 0); 
%> 
<html><HEAD><TITLE>插入图片文件</TITLE>
<link rel="stylesheet" type="text/css" href="site.css">

<script>
function IsDigit()
{
  return ((event.keyCode >= 48) && (event.keyCode <= 57));
}

function btnClick(){
    
    if(document.feeuploadForm.elements["theFile"].value!=''){
        var fileext=document.feeuploadForm.elements["theFile"].value.substring(document.feeuploadForm.elements["theFile"].value.length-4,document.feeuploadForm.elements["theFile"].value.length)
		fileext=fileext.toLowerCase()
		if (fileext!='.gif'&&fileext!='.jpg')
		{
			alert("对不起，不正确的文件类型,必须为.gif或.jpg ！");			
			return;
		}
        else{
        document.feeuploadForm.action="<c:url value="/picUploadAction.do"/>?method=picUpload";
	    document.feeuploadForm.submit();
	    }
	}
    else{
        alert("请选择要插入的图片文件！");
        return;
    
    }
 	// window.returnValue = a.value+"*"+b.value+"*"+c.value+"*"+d.value+"*"+e.value+"*"+f.value+"*"+g.value+"*"+h.value+"*"+i.value
    //window.close();
}
</script>
<base target="_self"> 
</HEAD>

<body bgColor=menu topmargin=15 leftmargin=15 ><br>
<DIV align=center>
<table width=100%><tr><td>
<FIELDSET align=left>
<LEGEND align=left>输入图片参数</LEGEND>

<html:form action="picUploadAction.do?method=picUpload" enctype="multipart/form-data">  
<table align=center>
<tr><td>图片地址：<input type="file" name="theFile" id=a  size=30 value=""></td></tr><tr>
          <td>说明文字：
<input name ="b" id=b size=20>图片边框：<input ONKEYPRESS="event.returnValue=IsDigit();" name ="i" id=i  value="0" size=2 maxlength="2"></td></tr><tr><td>
特殊效果：<select  id=c name ="c">
              <option>不应用</option>
              <option value="filter:Alpha(Opacity=50)">半透明效果</option>
              <option value="filter:Alpha(Opacity=0, FinishOpacity=100, Style=1, StartX=0, StartY=0, FinishX=100, FinishY=140)">线型透明效果</option>
              <option value="filter:Alpha(Opacity=10, FinishOpacity=100, Style=2, StartX=30, StartY=30, FinishX=200, FinishY=200)">放射透明效果</option>
              <option value="filter:blur(add=1,direction=14,strength=15)">模糊效果</option>
              <option value="filter:blur(add=true,direction=45,strength=30)">风动模糊效果</option>
              <option value="filter:Wave(Add=0, Freq=60, LightStrength=1, Phase=0, Strength=3)">正弦波纹效果</option>
              <option value="filter:gray">黑白照片效果</option>
              <option value="filter:Chroma(Color=#FFFFFF)">白色为透明</option>
              <option value="filter:DropShadow(Color=#999999, OffX=7, OffY=4, Positive=1)">投射阴影效果</option>
              <option value="filter:Shadow(Color=#999999, Direction=45)">阴影效果</option>
              <option value="filter:Glow(Color=#ff9900, Strength=5)">发光效果</option>
              <option value="filter:flipv">垂直翻转显示</option>
              <option value="filter:fliph">左右翻转显示</option>
              <option value="filter:grays">降低彩色度</option>
              <option value="filter:xray">X光照片效果</option>
              <option value="filter:invert">底片效果</option>
            </select>
图片位置：<select id=h><option>默认位置<option value="left">居左<option value="right" >居右
<option value="top">顶部<option value="middle">中部<option value="bottom">底部<option value="absmiddle">绝对居中<option value="absbottom">绝对底部<option value="baseline">基线<option value="texttop">文本顶部</select></td></tr><tr><td>
图片宽度：<input id=d name="d" ONKEYPRESS="event.returnValue=IsDigit();" value="800" size=4 maxlength="4">图片高度：<input id=e name="e" ONKEYPRESS="event.returnValue=IsDigit();"  value="800" size=4 maxlength="4"></td></tr><tr><td>上下间距：<input id=f  ONKEYPRESS="event.returnValue=IsDigit();" value="0" size=4 maxlength="2">左右间距：<input id=g ONKEYPRESS="event.returnValue=IsDigit();"  value="0" size=4 maxlength="2">
</td></tr></table>
</html:form>

</fieldset></td><td width=80 align="center"><input type=button value='  确定  ' id=Ok onclick="btnClick();"><br><br><input type=button value='  取消  ' onclick="window.close();"></td></tr>
</table>

</DIV>
</body>

<% String msg=(String)request.getAttribute("msg");
	String fileName = (String)request.getAttribute("fileName");
	String b = (String)request.getAttribute("b");
	String c = (String)request.getAttribute("c");
	String d = (String)request.getAttribute("d");
	String e = (String)request.getAttribute("e");
	String f = (String)request.getAttribute("f");
	String g = (String)request.getAttribute("g");
	String h = (String)request.getAttribute("h");
	String i = (String)request.getAttribute("i");
	if(msg!=null && msg.equals("success"))
	{
	%>
		<script >
		window.returnValue = "<%=fileName%>*<%=b%>*<%=c%>*<%=d%>*<%=e%>*<%=f%>*<%=g%>*<%=h%>*<%=i%>";
 		 window.close();
	</script>
	<%}%>