<%@ include file="init.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/util.js"></script>
<script>
	function renderLogin() {
		setTimeout("parent.location.href = '<%= ContextUtil.getCtxPath(request)%>/conference.do'", 3000);
	}
</script>
</head>
<body onLoad="javascript:renderLogin()">
<bean:message key="conference.renderlogin" />
<a href="javascript:parent.location.href = '<%= ContextUtil.getCtxPath(request)%>/conference.do';">
<bean:message key="conference.here" />
</a>
</body>

