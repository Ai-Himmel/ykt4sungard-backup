<%@ include file="WEB-INF/pages/tiles/include.jsp"%>
<html:html locale="true">
<head>

<!-- ++++++++++ Document Info ++++++++++ -->
<META http-equiv="Content-Type" content="text/html; charset=UTF-8">
<META name="keywords" CONTENT="king,java">
<META name="description" CONTENT="king,java">
<META name="abstract" CONTENT="king,java">

<!-- ++++++++++ Author's Information ++++++++++ -->
<META name="author" CONTENT="m_ljf@msn.com">
<META name="publisher" CONTENT="king">
<META name="copyright" CONTENT="king. See the legal notice.">
<META name="generator" CONTENT="Eclipse">
<META name="editor" CONTENT="ljf">
<META name="DownloadOptions" content="noopen">

<META name="page-topic" CONTENT="product info">
<META name="page-type" CONTENT="company page">
<!--<META name="content-language" CONTENT="en-GB">-->

<!-- ++++++++++ Browser Extentions ++++++++++ -->
<!--<META HTTP-EQUIV="expires" CONTENT="now">
<META HTTP-EQUIV="pragma" CONTENT="no-cache">
<META HTTP-EQUIV="cache-control" CONTENT="no-cache">
<META HTTP-EQUIV="cache-control" CONTENT="no-store">-->

<!-- ++++++++++ Search Engines ++++++++++ -->
<META name="audience" CONTENT="all">
<META name="resource-type" CONTENT="product info">
<META name="distribution" CONTENT="global">
<META name="rating" CONTENT="general">
<META name="robots" CONTENT="all">
<META name="robots" CONTENT="INDEX, FOLLOW">
<META name="revisit-after" CONTENT="1 weeks">


<!-- ++++++++++ Style Sheet ++++++++++ -->
<META http-equiv="Content-Style-Type" content="text/css">
<%@ include file="WEB-INF/pages/include/style.jsp"%>


<tiles:importAttribute name="title"/>
<title><bean:message name="title"/></title>
<script type="text/javascript" src="<c:url value='/pages/scripts/selectbox.js'/>" ></script>
<script type="text/javascript" src="<c:url value='/pages/scripts/global.js'/>" charset="gbk"></script>
<link rel="icon" href="./pages/images/favicon.ico" type="image/x-icon" />
<link rel="shortcut icon" href="./pages/images/favicon.ico" type="image/x-icon" />
</head>

<body topmargin="0" leftmargin="0" rightmargin="0" bottommargin="0" marginwidth="0" marginheight="0" onkeydown="KeyDown()">
    <!---------------------- include header start --------------------------->
    <tiles:insert attribute="header"/>
    <!---------------------- include header end ----------------------------->
    
    <!---------------------- include body start ----------------------------->
    <tiles:insert attribute="body"/>
    <!---------------------- include body end ------------------------------->
    
    <!---------------------- include footer start --------------------------->
    <tiles:insert attribute="footer"/>
    <!---------------------- include footer end ----------------------------->
</body>
</html:html>