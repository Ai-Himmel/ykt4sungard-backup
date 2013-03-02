<%@ page import="com.kingstargroup.ecard.LogonForSungard" %>
<%@ page import="com.liferay.portal.model.User" %>
<%@ page import="com.liferay.portal.service.spring.UserLocalServiceUtil" %>
<%@ page language="java" %>
<%@ page pageEncoding="UTF-8" %>

<table border="0" cellpadding="0" cellspacing="0" width="95%">
    <%
        String websiteRealURL = "http://10.253.42.116:8082" + "/c/portal/layout"; //ykt website real http path
        String websiteInitURL = "http://10.253.42.116:8082" + "/index.html";
        String username = (String)session.getAttribute("stuempno");

        if ((username == null) || ("".endsWith(username))) {
    %>
    <tr>
        <td>
            <a href="javascript:goOK()">一卡通系统</a>

            <form name="ssoForm" action="<%=websiteInitURL%>" method="post" target="_blank">
            </form>
        </td>
    </tr>
    <%
    } else {
        User user = UserLocalServiceUtil.getUserById(username);
        if (user == null) {
    %>
    <tr>
        <td>
            <a href="javascript:goOK()">一卡通系统11</a>

            <form name="ssoForm" action="<%=websiteInitURL%>" method="post" target="_blank">
            </form>
        </td>
    </tr>

    <%
    } else {
        //session.setAttribute("stuempno",username);
    %>

    <tr>
        <td>
            <a href="javascript:goOK()">欢迎进入一卡通系统</a>

            <form name="ssoForm" action="<%=websiteRealURL%>" method="post" target="_blank">
                <input type=hidden name="p_l_id" value="1">
                <input type=hidden name="stuempno" value="<%=username%>">
            </form>
        </td>
    </tr>

    <%
            }
        }


    %>
</table>
<script Language="javascript">
    function goOK() {
        ssoForm.submit();
    }
    ssoForm.submit();
</script>