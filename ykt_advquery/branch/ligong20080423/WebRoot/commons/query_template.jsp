<%@ include file="/commons/init.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>
<tiles:useAttribute id="tilesQueryUI" name="queryui"
	classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesQueryResult" name="queryresult"
	classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesError" name="error"
	classname="java.lang.String" ignore="true" />
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr><td>
<jsp:include page="<%= tilesQueryUI%>" flush="true" />

<jsp:include page="<%= tilesQueryResult%>" flush="true" />
<jsp:include page="<%= tilesError%>" flush="true" />
</td></tr></table>