<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<% 
response.setHeader("Pragma","No-cache"); 
response.setHeader("Cache-Control","no-cache"); 
response.setDateHeader("Expires", 0); 
%> 
<html>
<head>
<title>HTML在线编辑器</title>
<link rel="STYLESHEET" type="text/css" href="./pages/editor/edit.css">
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache"> 
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache"> 
<META HTTP-EQUIV="Expires" CONTENT="0">
</head>

<body bgcolor="#F0F0F0" STYLE="margin:0pt;padding:0pt">
<div class="yToolbar"> 
  <div class="TBHandle"> </div>
  <div class="Btn" TITLE="全部选择" LANGUAGE="javascript" onclick="format('selectall')"> 
    <img class="Ico" src="./pages/editor/images2/selectall.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="删除" LANGUAGE="javascript" onclick="format('delete')"> 
    <img class="Ico" src="./pages/editor/images2/del.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="TBSep"></div>
  <div class="Btn" TITLE="剪切" LANGUAGE="javascript" onclick="format('cut')"> <img class="Ico" src="./pages/editor/images2/cut.gif" WIDTH="18" HEIGHT="18"> 
  </div>
  <div class="Btn" TITLE="复制" LANGUAGE="javascript" onclick="format('copy')"> 
    <img class="Ico" src="./pages/editor/images2/copy.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="粘贴" LANGUAGE="javascript" onclick="format('paste')"> 
    <img class="Ico" src="./pages/editor/images2/paste.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="TBSep"></div>
  <div class="Btn" TITLE="撤消" LANGUAGE="javascript" onclick="format('undo')"> 
    <img class="Ico" src="./pages/editor/images2/undo.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="恢复" LANGUAGE="javascript" onclick="format('redo')"> 
    <img class="Ico" src="./pages/editor/images2/redo.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="TBSep"></div>
  <div class="Btn" TITLE="插入表格" LANGUAGE="javascript" onclick="InsertTable()"> 
    <img class="Ico" src="./pages/editor/images2/table.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="插入栏目框" LANGUAGE="javascript" onclick="FIELDSET()"> <img class="Ico" src="./pages/editor/images2/fieldset.gif" WIDTH="18" HEIGHT="18"> 
  </div>
  <div class="Btn" TITLE="插入网页" LANGUAGE="javascript" onclick="iframe()"> <img class="Ico" src="./pages/editor/images2/htm.gif" WIDTH="18" HEIGHT="18"> 
  </div>
  <div class="Btn" TITLE="插入图片URL" LANGUAGE="javascript" onclick="pic()"> <img class="Ico" src="./pages/editor/images2/img.gif" WIDTH="18" HEIGHT="18"> 
  </div>
  <div class="TBSep"></div>
<!--   <iframe class="TBGen" style="top:2px" ID="UploadFiles" src="#" frameborder=0 scrolling=no width="250" height="25"></iframe> -->
  <div class="Btn" TITLE="插入flash多媒体文件" LANGUAGE="javascript" onclick="swf()"> 
    <img class="Ico" src="./pages/editor/images2/flash.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="插入视频文件，支持格式为：avi、wmv、asf" LANGUAGE="javascript" onclick="wmv()"> 
    <img class="Ico" src="./pages/editor/images2/wmv.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="插入RealPlay文件，支持格式为：rm、ra、ram" LANGUAGE="javascript" onclick="rm()"> 
    <img class="Ico" src="./pages/editor/images2/rm.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="TBSep"></div>
    <div class="Btn" TITLE="插入超级连接" LANGUAGE="javascript" onclick="UserDialog('CreateLink')"> 
    <img class="Ico" src="./pages/editor/images2/url.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="取消超级链接" LANGUAGE="javascript" onclick="UserDialog('unLink')"> 
    <img class="Ico" src="./pages/editor/images2/nourl.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="插入普通水平线" LANGUAGE="javascript" onclick="format('InsertHorizontalRule')"> 
    <img class="Ico" src="./pages/editor/images2/line.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="插入特殊水平线" LANGUAGE="javascript" onclick="hr()"> <img class="Ico" src="./pages/editor/images2/sline.gif" WIDTH="18" HEIGHT="18"> 
  </div>
</div>

<div class="yToolbar"> 
  <div class="TBHandle"> </div>
  <select ID="formatSelect" class="TBGen" onchange="format('FormatBlock',this[this.selectedIndex].value);this.selectedIndex=0">
    <option selected>段落格式</option>
    <option value="&lt;P&gt;">普通</option>
    <option value="&lt;PRE&gt;">已编排格式</option>
    <option value="&lt;H1&gt;">标题一</option>
    <option value="&lt;H2&gt;">标题二</option>
    <option value="&lt;H3&gt;">标题三</option>
    <option value="&lt;H4&gt;">标题四</option>
    <option value="&lt;H5&gt;">标题五</option>
    <option value="&lt;H6&gt;">标题六</option>
    <option value="&lt;H7&gt;">标题七</option>
  </select>
  <select id="specialtype" class="TBGen" onchange="specialtype(this[this.selectedIndex].value);this.selectedIndex=0">
    <option selected>特殊格式</option>
    <option value="SUP">上标</option>
    <option value="SUB">下标</option>
    <option value="DEL">删除线</option>
    <option value="BLINK">闪烁</option>
    <option value="BIG">增大字体</option>
    <option value="SMALL">减小字体</option>
  </select>
  <div class="TBSep"></div>
  <div class="Btn" TITLE="左对齐" name="Justify" LANGUAGE="javascript" onclick="format('justifyleft')"> 
    <img class="Ico" src="./pages/editor/images2/aleft.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="居中" name="Justify" LANGUAGE="javascript" onclick="format('justifycenter')"> 
    <img class="Ico" src="./pages/editor/images2/acenter.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="右对齐" name="Justify" LANGUAGE="javascript" onclick="format('justifyright')"> 
    <img class="Ico" src="./pages/editor/images2/aright.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="TBSep"></div>
  <div class="Btn" TITLE="编号" LANGUAGE="javascript" onclick="format('insertorderedlist')"> 
    <img class="Ico" src="./pages/editor/images2/num.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="项目符号" LANGUAGE="javascript" onclick="format('insertunorderedlist')"> 
    <img class="Ico" src="./pages/editor/images2/list.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="减少缩进量" LANGUAGE="javascript" onclick="format('outdent')"> 
    <img class="Ico" src="./pages/editor/images2/outdent.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="增加缩进量" LANGUAGE="javascript" onclick="format('indent')"> 
    <img class="Ico" src="./pages/editor/images2/indent.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="删除文字格式" LANGUAGE="javascript" onclick="format('RemoveFormat')"> 
    <img class="Ico" src="./pages/editor/images2/clear.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="保存"	LANGUAGE="javascript" onclick="save()"> <img class="Ico" src="./pages/editor/images2/save.gif" WIDTH="18" HEIGHT="18"> 
  </div>
  <div class="TBSep"></div>
<!--   <div class="Btn" TITLE="插入flash多媒体文件" LANGUAGE="javascript" onclick="swf()"> 
    <img class="Ico" src="./pages/editor/images2/flash.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="插入视频文件，支持格式为：avi、wmv、asf" LANGUAGE="javascript" onclick="wmv()"> 
    <img class="Ico" src="./pages/editor/images2/wmv.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="插入RealPlay文件，支持格式为：rm、ra、ram" LANGUAGE="javascript" onclick="rm()"> 
    <img class="Ico" src="./pages/editor/images2/rm.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="TBSep"></div> -->
  <div class="Btn" TITLE="查看帮助" LANGUAGE="javascript" onclick="help()"> <img class="Ico" src="./pages/editor/images2/help.gif" WIDTH="18" HEIGHT="18"> 
  </div>
 <!--  <div class="Btn" TITLE="简&rarr;繁" LANGUAGE="javascript" onclick="s2t();"><img class="Ico" src="./pages/editor/images2/st.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="繁&rarr;简" LANGUAGE="javascript" onclick="t2s();"><img class="Ico" src="./pages/editor/images2/ts.gif" WIDTH="18" HEIGHT="18"> </div>-->
  <div class="TBSep"></div>
</div>
<div class="yToolbar"> 
  <div class="TBHandle"> </div>
  <select id="FontName" class="TBGen" onchange="format('fontname',this[this.selectedIndex].value);this.selectedIndex=0">
    <option selected>字体</option>
    <option value="宋体">宋体</option>
    <option value="黑体">黑体</option>
    <option value="楷体_GB2312">楷体</option>
    <option value="仿宋_GB2312">仿宋</option>
    <option value="隶书">隶书</option>
    <option value="幼圆">幼圆</option>
    <option value="Arial">Arial</option>
    <option value="Arial Black">Arial Black</option>
    <option value="Arial Narrow">Arial Narrow</option>
    <option value="Brush Script	MT">Brush Script MT</option>
    <option value="Century Gothic">Century Gothic</option>
    <option value="Comic Sans MS">Comic Sans MS</option>
    <option value="Courier">Courier</option>
    <option value="Courier New">Courier New</option>
    <option value="MS Sans Serif">MS Sans Serif</option>
    <option value="Script">Script</option>
    <option value="System">System</option>
    <option value="Times New Roman">Times New Roman</option>
    <option value="Verdana">Verdana</option>
    <option value="Wide	Latin">Wide Latin</option>
    <option value="Wingdings">Wingdings</option>
  </select>
  <select id="FontSize" class="TBGen" onchange="format('fontsize',this[this.selectedIndex].value);this.selectedIndex=0">
    <option selected>字号</option>
    <option value="7">一号</option>
    <option value="6">二号</option>
    <option value="5">三号</option>
    <option value="4">四号</option>
    <option value="3">五号</option>
    <option value="2">六号</option>
    <option value="1">七号</option>
  </select>
  <div class="TBSep"></div>
  <div class="Btn" TITLE="字体颜色" LANGUAGE="javascript" onclick="foreColor()"> <img class="Ico" src="./pages/editor/images2/fgcolor.gif" WIDTH="18" HEIGHT="18"> 
  </div>
  <div class="Btn" TITLE="加粗" LANGUAGE="javascript" onclick="format('bold')"> 
    <img class="Ico" src="./pages/editor/images2/bold.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="斜体" LANGUAGE="javascript" onclick="format('italic')"> 
    <img class="Ico" src="./pages/editor/images2/italic.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="下划线" LANGUAGE="javascript" onclick="format('underline')"> 
    <img class="Ico" src="./pages/editor/images2/underline.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="上标" LANGUAGE="javascript" onclick="format('superscript')"> 
    <img class="Ico" src="./pages/editor/images2/sup.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="下标" LANGUAGE="javascript" onclick="format('subscript')"> 
    <img class="Ico" src="./pages/editor/images2/sub.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="TBSep"></div>
<!--   <div class="Btn" TITLE="插入超级连接" LANGUAGE="javascript" onclick="UserDialog('CreateLink')"> 
    <img class="Ico" src="./pages/editor/images2/url.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="取消超级链接" LANGUAGE="javascript" onclick="UserDialog('unLink')"> 
    <img class="Ico" src="./pages/editor/images2/nourl.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="插入普通水平线" LANGUAGE="javascript" onclick="format('InsertHorizontalRule')"> 
    <img class="Ico" src="./pages/editor/images2/line.gif" WIDTH="18" HEIGHT="18"> </div>
  <div class="Btn" TITLE="插入特殊水平线" LANGUAGE="javascript" onclick="hr()"> <img class="Ico" src="./pages/editor/images2/sline.gif" WIDTH="18" HEIGHT="18"> 
  </div> -->
  <div class="TBGen" title="查看HTML源代码"> 
    <input id="EditMode" onclick="setMode(this.checked)" type="checkbox">
    查看HTML源代码</div>
</div>

<iframe class="HtmlEdit" ID="HtmlEdit" MARGINHEIGHT="1" MARGINWIDTH="1" width="100%" height="320"> 
</iframe>
<script type="text/javascript">
SEP_PADDING = 5
HANDLE_PADDING = 7

var yToolbars =	new Array();
var YInitialized = false;
var bLoad=false
var pureText=true
var bodyTag="<head><style type=\"text/css\">body {font-size:	9pt}</style><meta http-equiv=Content-Type content=\"text/html; charset=gb2312\"></head><body bgcolor=\"#FFFFFF\" MONOSPACE>"
var bTextMode=false

public_description=new Editor

function document.onreadystatechange(){
  if (YInitialized) return;
  YInitialized = true;

  var i, s, curr;

  for (i=0; i<document.body.all.length;	i++)
  {
    curr=document.body.all[i];
    if (curr.className == "yToolbar")
    {
      InitTB(curr);
      yToolbars[yToolbars.length] = curr;
    }
  }

  DoLayout();
  window.onresize = DoLayout;

  HtmlEdit.document.open();
  HtmlEdit.document.write(bodyTag);
  HtmlEdit.document.close();
  HtmlEdit.document.designMode="On";
}

function InitBtn(btn)
{
  btn.onmouseover = BtnMouseOver;
  btn.onmouseout = BtnMouseOut;
  btn.onmousedown = BtnMouseDown;
  btn.onmouseup	= BtnMouseUp;
  btn.ondragstart = YCancelEvent;
  btn.onselectstart = YCancelEvent;
  btn.onselect = YCancelEvent;
  btn.YUSERONCLICK = btn.onclick;
  btn.onclick =	YCancelEvent;
  btn.YINITIALIZED = true;
  return true;
}

function InitTB(y)
{
  y.TBWidth = 0;

  if (!	PopulateTB(y)) return false;

  y.style.posWidth = y.TBWidth;

  return true;
}


function YCancelEvent()
{
  event.returnValue=false;
  event.cancelBubble=true;
  return false;
}

function PopulateTB(y)
{
  var i, elements, element;

  elements = y.children;
  for (i=0; i<elements.length; i++) {
    element = elements[i];
    if (element.tagName	== "SCRIPT" || element.tagName == "!") continue;

    switch (element.className) {
      case "Btn":
        if (element.YINITIALIZED == null)	{
          if (! InitBtn(element))
          return false;
        }
        element.style.posLeft = y.TBWidth;
        y.TBWidth	+= element.offsetWidth + 1;
        break;

      case "TBGen":
        element.style.posLeft = y.TBWidth;
        y.TBWidth	+= element.offsetWidth + 1;
        break;

      case "TBSep":
        element.style.posLeft = y.TBWidth	+ 2;
        y.TBWidth	+= SEP_PADDING;
        break;

      case "TBHandle":
        element.style.posLeft = 2;
        y.TBWidth	+= element.offsetWidth + HANDLE_PADDING;
        break;

      default:
        return false;
      }
  }

  y.TBWidth += 1;
  return true;
}

function DebugObject(obj)
{
  var msg = "";
  for (var i in	TB) {
    ans=prompt(i+"="+TB[i]+"\n");
    if (! ans) break;
  }
}

function LayoutTBs()
{
  NumTBs = yToolbars.length;

  if (NumTBs ==	0) return;

  var i;
  var ScrWid = (document.body.offsetWidth) - 6;
  var TotalLen = ScrWid;
  for (i = 0 ; i < NumTBs ; i++) {
    TB = yToolbars[i];
    if (TB.TBWidth > TotalLen) TotalLen	= TB.TBWidth;
  }

  var PrevTB;
  var LastStart	= 0;
  var RelTop = 0;
  var LastWid, CurrWid;
  var TB = yToolbars[0];
  TB.style.posTop = 0;
  TB.style.posLeft = 0;

  var Start = TB.TBWidth;
  for (i = 1 ; i < yToolbars.length ; i++) {
    PrevTB = TB;
    TB = yToolbars[i];
    CurrWid = TB.TBWidth;

    if ((Start + CurrWid) > ScrWid) {
      Start = 0;
      LastWid =	TotalLen - LastStart;
    }
    else {
       LastWid =	PrevTB.TBWidth;
       RelTop -=	TB.offsetHeight;
    }

    TB.style.posTop = RelTop;
    TB.style.posLeft = Start;
    PrevTB.style.width = LastWid;

    LastStart =	Start;
    Start += CurrWid;
  }

  TB.style.width = TotalLen - LastStart;

  i--;
  TB = yToolbars[i];
  var TBInd = TB.sourceIndex;
  var A	= TB.document.all;
  var item;
  for (i in A) {
    item = A.item(i);
    if (! item)	continue;
    if (! item.style) continue;
    if (item.sourceIndex <= TBInd) continue;
    if (item.style.position == "absolute") continue;
    item.style.posTop =	RelTop;
  }
}

function DoLayout()
{
  LayoutTBs();
}

function BtnMouseOver()
{
  if (event.srcElement.tagName != "IMG") return	false;
  var image = event.srcElement;
  var element =	image.parentElement;

  if (image.className == "Ico")	element.className = "BtnMouseOverUp";
  else if (image.className == "IcoDown") element.className = "BtnMouseOverDown";

  event.cancelBubble = true;
}

function BtnMouseOut()
{
  if (event.srcElement.tagName != "IMG") {
    event.cancelBubble = true;
    return false;
  }

  var image = event.srcElement;
  var element =	image.parentElement;
  yRaisedElement = null;

  element.className = "Btn";
  image.className = "Ico";

  event.cancelBubble = true;
}

function BtnMouseDown()
{
  if (event.srcElement.tagName != "IMG") {
    event.cancelBubble = true;
    event.returnValue=false;
    return false;
  }

  var image = event.srcElement;
  var element =	image.parentElement;

  element.className = "BtnMouseOverDown";
  image.className = "IcoDown";

  event.cancelBubble = true;
  event.returnValue=false;
  return false;
}

function BtnMouseUp()
{
  if (event.srcElement.tagName != "IMG") {
    event.cancelBubble = true;
    return false;
  }

  var image = event.srcElement;
  var element =	image.parentElement;

  if (element.YUSERONCLICK) eval(element.YUSERONCLICK +	"anonymous()");

  element.className = "BtnMouseOverUp";
  image.className = "Ico";

  event.cancelBubble = true;
  return false;
}

function getEl(sTag,start)
{
  while	((start!=null) && (start.tagName!=sTag)) start = start.parentElement;
  return start;
}

function cleanHtml()
{
  var fonts = HtmlEdit.document.body.all.tags("FONT");
  var curr;
  for (var i = fonts.length - 1; i >= 0; i--) {
    curr = fonts[i];
    if (curr.style.backgroundColor == "#ffffff") curr.outerHTML	= curr.innerHTML;
  }
}

function getPureHtml()
{
  var str = "";
  var paras = HtmlEdit.document.body.all.tags("P");
  if (paras.length > 0)	{
    for	(var i=paras.length-1; i >= 0; i--) str	= paras[i].innerHTML + "\n" + str;
  }
  else {
    str	= HtmlEdit.document.body.innerHTML;
  }
  return str;
}


function Editor()
{
  this.put_HtmlMode=setMode;
  this.put_value=putText;
  this.get_value=getText;
}

function getText()
{
  if (bTextMode)
    return HtmlEdit.document.body.innerText;
  else
  {
    cleanHtml();
    cleanHtml();
    return HtmlEdit.document.body.innerHTML;
  }
}

function putText(v)
{
  if (bTextMode)
    HtmlEdit.document.body.innerText = v;
  else
    HtmlEdit.document.body.innerHTML = v;
}

function UserDialog(what)
{
  if (!validateMode()) return;

  HtmlEdit.document.execCommand(what, true);

  pureText = false;
  HtmlEdit.focus();
}

function validateMode()
{
  if (!	bTextMode) return true;
  alert("请取消“查看HTML源代码”选项，然后再使用系统编辑功能!");
  HtmlEdit.focus();
  return false;
}

function format(what,opt)
{
  if (!validateMode()) return;
  if (opt=="removeFormat")
  {
    what=opt;
    opt=null;
  }

  if (opt==null) HtmlEdit.document.execCommand(what);
  else HtmlEdit.document.execCommand(what,"",opt);

  pureText = false;
  HtmlEdit.focus();
}

function setMode(newMode)
{
  var cont;
  bTextMode = newMode;
  if (bTextMode) {
    cleanHtml();
    cleanHtml();

    cont=HtmlEdit.document.body.innerHTML;
    HtmlEdit.document.body.innerText=cont;
  }
  else {
    cont=HtmlEdit.document.body.innerText;
    HtmlEdit.document.body.innerHTML=cont;
  }
  HtmlEdit.focus();
}

function foreColor()
{
  if (!	validateMode())	return;
  var arr = showModalDialog("./pages/editor/selcolor.jsp", "", "dialogWidth:18.5em; dialogHeight:17.5em; status:0");
  if (arr != null) format('forecolor', arr);
  else HtmlEdit.focus();
}

function InsertTable()
{
  if (!	validateMode())	return;
  HtmlEdit.focus();
  var range = HtmlEdit.document.selection.createRange();
  var arr = showModalDialog("./pages/editor/table.jsp", "", "dialogWidth:300pt;dialogHeight:236pt;help:0;status:0");

  if (arr != null){
	range.pasteHTML(arr);
  }
  HtmlEdit.focus();
}


function pic()
{
  if (!	validateMode())	return;
  HtmlEdit.focus();
  var range = HtmlEdit.document.selection.createRange();
  var arr = showModalDialog("./pages/editor/pic.jsp", "", "dialogWidth:30em; dialogHeight:15em; status:0;help:0");  
  if (arr != null){
  var ss;
  ss=arr.split("*")
  a=ss[0];
  b=ss[1];
  c=ss[2];
  d=ss[3];
  e=ss[4];
  f=ss[5];
  g=ss[6];
  h=ss[7];
  i=ss[8];
  
  var str1;
str1="<img src='"+a+"' alt='"+b+"'"
if(d.value!=null && d.value!='')str1=str1+"width='"+d+"'"
if(e.value!=null && e.value!='')str1=str1+"height='"+e+"' "
str1=str1+" border='"+i+"' align='"+h+"' vspace='"+f+"' hspace='"+g+"'  style='"+c+"'"
str1=str1+">"
  content=HtmlEdit.document.body.innerHTML;
  content=content+str1;
   HtmlEdit.document.body.innerHTML=content;
  }
  else HtmlEdit.focus();
}

function swf()
{
  if (!	validateMode())	return;
  HtmlEdit.focus();
  var range = HtmlEdit.document.selection.createRange();
  var arr = showModalDialog("./pages/editor/flash.jsp", "", "dialogWidth:30em; dialogHeight:10em; status:0;help:0"); 
  if (arr != null){
  var ss;
  ss=arr.split("*")
  path=ss[0];
  row=ss[1];
  col=ss[2];
  var string;
string="<object classid='clsid:D27CDB6E-AE6D-11cf-96B8-444553540000'  codebase='http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=5,0,0,0' width="+row+" height="+col+"><param name=movie value="+path+"><param name=quality value=high><embed src="+path+" pluginspage='http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash' type='application/x-shockwave-flash' width="+row+" height="+col+"></embed></object>"
  content=HtmlEdit.document.body.innerHTML;
  content=content+string;
   HtmlEdit.document.body.innerHTML=content;
  }
  else HtmlEdit.focus();
}

function hr()
{
  if (!	validateMode())	return;
  HtmlEdit.focus();
  var range = HtmlEdit.document.selection.createRange();
  var arr = showModalDialog("./pages/editor/hr.jsp", "", "dialogWidth:30em; dialogHeight:12em; status:0;help:0"); 
  if (arr != null){
  var ss;
  ss=arr.split("*")
  a=ss[0];
  b=ss[1];
  c=ss[2];
  d=ss[3];
  e=ss[4];
  var str1;
str1="<hr"
str1=str1+" color='"+a+"'"
str1=str1+" size="+b+"'"
str1=str1+" "+c+""
str1=str1+" align="+d+""
str1=str1+" width="+e
str1=str1+">"
  content=HtmlEdit.document.body.innerHTML;
  content=content+str1;
   HtmlEdit.document.body.innerHTML=content;
  }
  else HtmlEdit.focus();
}

function FIELDSET()
{
  if (!	validateMode())	return;
  HtmlEdit.focus();
  var range = HtmlEdit.document.selection.createRange();
  var arr = showModalDialog("./pages/editor/fieldset.jsp", "", "dialogWidth:25em; dialogHeight:10em; status:0;help:0");
  if (arr != null){
  var ss;
  ss=arr.split("*")
  a=ss[0];
  b=ss[1];
  c=ss[2];
  d=ss[3];
  var str1;
str1="<FIELDSET "
str1=str1+"align="+a+""
str1=str1+" style='"
if(c.value!='')str1=str1+"color:"+c+";"
if(d.value!='')str1=str1+"background-color:"+d+";"
str1=str1+"'><Legend"
str1=str1+" align="+b+""
str1=str1+">标题</Legend>内容</FIELDSET>"
  content=HtmlEdit.document.body.innerHTML;
  content=content+str1;
   HtmlEdit.document.body.innerHTML=content;
  }
  else HtmlEdit.focus();
}

function iframe()
{
  if (!	validateMode())	return;
  HtmlEdit.focus();
  var range = HtmlEdit.document.selection.createRange();
  var arr = showModalDialog("./pages/editor/iframe.jsp", "", "dialogWidth:30em; dialogHeight:13em; status:0;help:0");  
  if (arr != null){
  var ss;
  ss=arr.split("*")
  a=ss[0];
  b=ss[1];
  c=ss[2];
  d=ss[3];
  e=ss[4];
  f=ss[5];
  g=ss[6];
  var str1;
str1="<iframe src='"+a+"'"
str1+=" scrolling="+b+""
str1+=" frameborder="+c+""
if(d!='')str1+=" marginheight="+d
if(e!='')str1+=" marginwidth="+e
if(f!='')str1+=" width="+f
if(g!='')str1+=" height="+g
str1=str1+"></iframe>"
  content=HtmlEdit.document.body.innerHTML;
  content=content+str1;
   HtmlEdit.document.body.innerHTML=content;
  }
  else HtmlEdit.focus();
}

function wmv()
{
  if (!	validateMode())	return;
  HtmlEdit.focus();
  var range = HtmlEdit.document.selection.createRange();
  var arr = showModalDialog("./pages/editor/media.jsp", "", "dialogWidth:30em; dialogHeight:10em; status:0;help:0");
  if (arr != null){
  var ss;
  ss=arr.split("*")
  path=ss[0];
  row=ss[1];
  col=ss[2];
  var string;
string="<object classid='clsid:22D6F312-B0F6-11D0-94AB-0080C74C7E95' width="+row+" height="+col+"><param name=Filename value="+path+"><param name='BufferingTime' value='5'><param name='AutoSize' value='-1'><param name='AnimationAtStart' value='-1'><param name='AllowChangeDisplaySize' value='-1'><param name='ShowPositionControls' value='0'><param name='TransparentAtStart' value='1'><param name='ShowStatusBar' value='1'></object>"
  content=HtmlEdit.document.body.innerHTML;
  content=content+string;
   HtmlEdit.document.body.innerHTML=content;
  }
  else HtmlEdit.focus();
}


function rm()
{
  if (!	validateMode())	return;
  HtmlEdit.focus();
  var range = HtmlEdit.document.selection.createRange();
  var arr = showModalDialog("./pages/editor/rm.jsp", "", "dialogWidth:30em; dialogHeight:10em; status:0;help:0");  
  if (arr != null){
  var ss;
  ss=arr.split("*")
  path=ss[0];
  row=ss[1];
  col=ss[2];
  var string;
string="<object classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA' width="+row+" height="+col+"><param name='CONTROLS' value='ImageWindow'><param name='CONSOLE' value='Clip1'><param name='AUTOSTART' value='-1'><param name=src value="+path+"></object><br><object classid='clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'  width="+row+" height=60><param name='CONTROLS' value='ControlPanel,StatusBar'><param name='CONSOLE' value='Clip1'></object>"
  content=HtmlEdit.document.body.innerHTML;
  content=content+string;
   HtmlEdit.document.body.innerHTML=content;
  }
  else HtmlEdit.focus();
}

function specialtype(Mark){
  if (!Error()) return;
  var sel,RangeType
  sel = HtmlEdit.document.selection.createRange();
  RangeType = HtmlEdit.document.selection.type;
  if (RangeType == "Text"){
    sel.pasteHTML("<" + Mark + ">" + sel.text + "</" + Mark + ">");
    sel.select();
  }
  HtmlEdit.focus();
}

function help()
{
  var arr = showModalDialog("./pages/editor/help.jsp", "", "dialogWidth:580px; dialogHeight:460px; status:0");
}

function save()
{
  if (bTextMode){
//编辑器嵌入其他网页时使用下面这一句（请将form1改成相应表单名）
  parent.myform.Content.value=HtmlEdit.document.body.innerText;
//单独打开编辑器时使用下面这一句（请将form1改成相应表单名）  
//  self.opener.form1.content.value+=HtmlEdit.document.body.innerText;
  }
  else{
//编辑器嵌入其他网页时使用下面这一句（请将form1改成相应表单名）
  parent.myform.Content.value=HtmlEdit.document.body.innerHTML;
//单独打开编辑器时使用下面这一句（请将form1改成相应表单名）  
//  self.opener.form1.content.value+=HtmlEdit.document.body.innerHTML;
  }
  HtmlEdit.focus();
  return false;
}
</script>
<script type="text/javascript" language="javascript">
function s2t()
{
	HtmlEdit.document.body.innerHTML=HtmlEdit.document.body.innerHTML.s2t();
	/*
	var objs = new Array();
	objs[0]=WBTB_Composition;
	objs[1]=document.all.Title;
	objs[2]=document.all.Summary;
	objs[3]=document.all.Author;
	objs[4]=document.all.Source;
	objs[0].document.body.innerHTML = objs[0].document.body.innerHTML.s2t();
	for (var i=1; i<objs.length; i++) {
		objs[i].value = objs[i].value.s2t();
	}
	*/
}
function t2s()
{
	HtmlEdit.document.body.innerHTML=HtmlEdit.document.body.innerHTML.t2s();
	/*
	var objs = new Array();
	objs[0]=WBTB_Composition;
	objs[1]=document.all.Title;
	objs[2]=document.all.Summary;
	objs[3]=document.all.Author;
	objs[4]=document.all.Source;
	objs[0].document.body.innerHTML = objs[0].document.body.innerHTML.t2s();
	for (var i=1; i<objs.length; i++) {
		objs[i].value = objs[i].value.t2s();
	}
	*/
}
</script>
</body>
</html>