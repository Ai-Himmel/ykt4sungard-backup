<%@ include file="/commons/init.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/js/util.js"></script>
<script>
	function renderLogin() {
		setTimeout("parent.location.href = '<%= ContextUtil.getCtxPath(request)%>/usermanage/login.do'", 3000);
	}
</script>
</head>
<body onLoad="javascript:renderLogin()">
<bean:message key="eadvquery.renderlogin" />
<a href="javascript:parent.location.href = '<%= ContextUtil.getCtxPath(request)%>/usermanage/login.do';">
<bean:message key="eadvquery.here" />
</a>
</body>
</html>
