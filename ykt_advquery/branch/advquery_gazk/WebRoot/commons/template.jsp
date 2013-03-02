<%@ include file="/commons/init.jsp" %>
<html style="height:100%;" xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>
<body style="height:100%;overflow-y: scroll;" scrolling=auto>
<tiles:useAttribute id="tilesHead" name="head"
	classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesSubnav" name="subnav"
	classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesContent" name="content"
	classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesBottom" name="bottom"
	classname="java.lang.String" ignore="true" />

<jsp:include page="<%= tilesHead %>" flush="true" />
<table width="1000" height="3" border="0" cellpadding="0" cellspacing="0"></table>
<table width="1000" border="0" style="height:100%;" cellspacing="0" cellpadding="0">
  <tr style="height:100%;">
    <td width="1000" style="height:100%;" valign="top">
	    <table width="1000" border="0" style="height:100%;" cellpadding="0" cellspacing="0">
		  <tr> 
		    <td width="197" style="height:100%;" valign="top">
		    	<iframe name="subnavframe" style="height:100%;" width="197" frameborder="0" src="<%= ContextUtil.getCtxPath(request)%><%= tilesSubnav%>"></iframe>
		    </td>
		    <td align="left" valign="top"> 
				<iframe name="dataframe"    style="height:100%;" width="800" frameborder="0" src="<%= ContextUtil.getCtxPath(request)%><%= tilesContent%>"></iframe> </td>
		  </tr>
		</table>
	</td>
  </tr>
</table>

<table width="1000" height="3" border="0" cellpadding="0" cellspacing="0">
</table>
<jsp:include page="<%= tilesBottom%>" flush="true" />