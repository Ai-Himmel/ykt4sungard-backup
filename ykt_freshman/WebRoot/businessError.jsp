<%@page pageEncoding="GBK"%>
<%@ include file="WEB-INF/pages/tiles/include.jsp"%>

<%@ page contentType="text/html;charset=UTF-8" isErrorPage="true" %>
<%@ page import="org.king.framework.exception.BusinessException" %>



<html>
<head>
    <title>出错页面</title>
    <%@ include file="/pages/common/meta.jsp" %>
</head>

<body>
<div id="content">
    <%
        exception = (BusinessException) request.getAttribute("exception");
    %>

    <h3>业务错误:</h3>

    <p><%=exception.getMessage()%></p>
    <button onclick="history.back();">返回</button>
</div>
</body>
</html>