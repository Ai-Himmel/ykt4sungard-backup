﻿<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<% 
response.setHeader("Pragma","No-cache"); 
response.setHeader("Cache-Control","no-cache"); 
response.setDateHeader("Expires", 0); 
%> 
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>JS调用范例</title>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache"> 
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache"> 
<META HTTP-EQUIV="Expires" CONTENT="0"> 
<link href="STYLE.CSS" rel="stylesheet" type="text/css">
</head>

<body>
<p><font size="6">普通文章样式一（只有标题）：</font><br>
<!--代码开始-->
<script language='JavaScript' type='text/JavaScript' src='http://pe.asp163.net/js.asp?ClassID=1&IncludeChild=true&SpecialID=&ArticleNum=10&ShowType=1&ShowCols=1&ShowProperty=true&ShowClassName=false&ShowIncludePic=true&ShowTitle=true&ShowUpdateTime=true&ShowHits=true&ShowAuthor=true&ShowHot=true&ShowMore=true&TitleMaxLen=30&ContentMaxLen=200&Hot=false&Elite=false&DateNum=&OrderField=ArticleID&OrderType=desc'></script>
<!--代码结束-->
</p>
<p> <font size="6">普通文章样式二（标题+内容）：</font><br>
<!--代码开始-->
<script language='JavaScript' type='text/JavaScript' src='http://pe.asp163.net/js.asp?ClassID=1&IncludeChild=true&SpecialID=&ArticleNum=10&ShowType=2&ShowCols=1&ShowProperty=true&ShowClassName=false&ShowIncludePic=true&ShowTitle=true&ShowUpdateTime=false&ShowHits=false&ShowAuthor=false&ShowHot=true&ShowMore=false&TitleMaxLen=30&ContentMaxLen=200&Hot=false&Elite=false&DateNum=&OrderField=ArticleID&OrderType=desc'></script>
<!--代码结束-->
</p>
<p><font size="6">首页图片样式一（图片+标题）：</font><br>
<!--代码开始-->
<script language='JavaScript' type='text/JavaScript' src='http://www.asp163.net/access/js.asp?ClassID=0&IncludeChild=false&ArticleNum=10&ShowType=3&ShowProperty=true&ShowClassName=false&ShowIncludePic=true&ShowTitle=true&ShowUpdateTime=false&ShowHits=false&ShowAuthor=false&ShowHot=true&ShowMore=false&TitleMaxLen=30&ContentMaxLen=200&Hot=false&Elite=false&DateNum=&OrderField=ArticleID&OrderType=desc&ImgWidth=180&ImgHeight=120'></script>
<!--代码结束-->
</p>
<p><font size="6">首页图片样式二（图片+标题+内容）：</font><br>
<!--代码开始-->
<script language='JavaScript' type='text/JavaScript' src='http://www.asp163.net/access/js.asp?ClassID=0&IncludeChild=false&ArticleNum=10&ShowType=4&ShowClassName=false&ShowTitle=true&ShowUpdateTime=false&ShowHits=false&ShowAuthor=false&ShowHot=true&ShowMore=false&TitleMaxLen=30&ContentMaxLen=200&Hot=false&Elite=false&DateNum=&OrderField=ArticleID&OrderType=desc&ImgWidth=180&ImgHeight=120'></script>
<!--代码结束-->
</body>
</html>
