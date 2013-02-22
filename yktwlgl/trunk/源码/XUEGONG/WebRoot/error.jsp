<%@page pageEncoding="GBK"%>

<%@ page contentType="text/html;charset=UTF-8" isErrorPage="true" %>
<%@ page import="org.apache.commons.logging.LogFactory" %>



<html>
<head>
    <title>����ҳ��</title>
    <%@ include file="/pages/common/meta.jsp" %>

</head>

<body>

<div id="content">
    <%

        if (exception != null) //from JSP
        {
            //Exception from JSP didn't log yet ,should log it here.
            String requestUri = (String) request.getAttribute("javax.servlet.error.request_uri");
            LogFactory.getLog(requestUri).error(exception.getMessage(), exception);
        }
        else if (request.getAttribute("exception") != null) //from Spring
        {
            exception = (Exception) request.getAttribute("exception");
        }
    %>

    <h3>ϵͳ�����ڴ���: <br><%=exception.getMessage()%></h3>
    <br>
     <script language="javascript">
        function showDetail()
        {
            if (detail_error_msg.style.display == 'none')
                detail_error_msg.style.display = '';
            else
                detail_error_msg.style.display = 'none';
        }
    </script>
    <button onclick="history.back();">����</button>
    <br>

    <p><a href="#" onclick="showDetail();">������Ա����˴���ȡ��ϸ������Ϣ</a></p>

    <div id="detail_error_msg" style="display:none">
        <pre><%exception.printStackTrace(new java.io.PrintWriter(out));%></pre>
    </div>
</div>
</body>
</html>