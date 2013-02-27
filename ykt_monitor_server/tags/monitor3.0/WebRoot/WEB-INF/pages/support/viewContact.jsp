<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
</head>
<body>
    <div style="width:100%;margin:8px 8px 0 10">
        <table width=100% border=1 cellpadding=1 cellspacing=0 bordercolor="#FFFFFF">
            <tbody>
            <tr class="toptitle">
                <td colspan="2" style="text-align:left"><p style="font-weight:bold;">查看联系人</p></td>
            </tr>
            <tr>
                <td class="td_title">联系人名称：</td>
                <td class="td_value">
                    <bean:write name="monitorContactForm" property="monitorContact.contactName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">邮箱：</td>
                <td class="td_value">
                    <bean:write name="monitorContactForm" property="monitorContact.emailAddress"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">联系电话：</td>
                <td class="td_value">
                    <bean:write name="monitorContactForm" property="monitorContact.cellphone"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">联系电话：</td>
                <td class="td_value">
                    <bean:write name="monitorContactForm" property="monitorContact.contactGroups.contactgroupName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知方式：</td>
                <td class="td_value">
                    <bean:write name="monitorContactForm" property="monitorContact.notifyCommand"/>
                </td>
            </tr>
            <tr>
                <td colspan="2">
                    &nbsp;&nbsp;
                    <input  type="button" class="button_nor" value=" 返 回 " onclick="history.back();">
                </td>
            </tr>
            </tbody>
        </table>
    </div>
</body>

</html>
