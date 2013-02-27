<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<%@ taglib prefix="sys" tagdir="/WEB-INF/tags" %>
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
                <td colspan="2" style="text-align:left">查看服务状态</td>
            </tr>
            <tr>
                <td class="td_title">服务状态：</td>
                <td class="td_value">
                    <sys:status type="2"><bean:write name="monitorServiceStatusForm" property="monitorServiceStatus.currentState"/></sys:status><bean:write name="statusDuration" />
                </td>
            </tr>
            <tr>
                <td class="td_title">服务名称：</td>
                <td class="td_value">
                    <bean:write name="monitorService" property="serviceName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">主机名称：</td>
                <td class="td_value">
                    <bean:write name="monitorService" property="monitorHost.alias"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">主机地址：</td>
                <td class="td_value">
                    <bean:write name="monitorService" property="monitorHost.hostAddress"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">状态信息：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceStatusForm" property="monitorServiceStatus.output"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">性能指标：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceStatusForm" property="monitorServiceStatus.perfdata"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">尝试次数：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceStatusForm" property="monitorServiceStatus.currentCheckAttempt"/>/<bean:write name="monitorServiceStatusForm" property="monitorServiceStatus.maxCheckAttempts"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">上次检查：</td>
                <td class="td_value">
                    <sys:format><bean:write name="monitorServiceStatusForm" property="monitorServiceStatus.lastCheck"/></sys:format>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查延时：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceStatusForm" property="monitorServiceStatus.latency"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">下次检查：</td>
                <td class="td_value">
                    <sys:format><bean:write name="monitorServiceStatusForm" property="monitorServiceStatus.nextCheck"/></sys:format>
                </td>
            </tr>
            <tr>
                <td class="td_title">上次状态变更：</td>
                <td class="td_value">
                    <sys:format><bean:write name="monitorServiceStatusForm" property="monitorServiceStatus.lastStateChange"/></sys:format>
                </td>
            </tr>
            <tr>
                <td class="td_title">上次通知：</td>
                <td class="td_value">
                    <sys:format defaultValue="N/A"><bean:write name="monitorServiceStatusForm" property="monitorServiceStatus.lastNotification"/></sys:format>(notification 0)
                </td>
            </tr>
            <tr>
                <td class="td_title">最近更新：</td>
                <td class="td_value">
                    <sys:format><bean:write name="monitorServiceStatusForm" property="monitorServiceStatus.statusUpdateTime"/></sys:format><bean:write name="updateDuration" />
                </td>
            </tr>
            <tr>
                <td colspan="2"  align="center">
                    &nbsp;&nbsp;
                    <input  type="button" class="button_nor" value=" 返 回 " onclick="history.back();">
                </td>
            </tr>
            </tbody>
        </table>
    </div>
</body>

</html>
