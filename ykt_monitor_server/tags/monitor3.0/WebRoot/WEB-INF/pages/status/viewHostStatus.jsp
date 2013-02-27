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
                <td colspan="2" style="text-align:left">查看主机状态</td>
            </tr>
            <tr>
                <td class="td_title">主机状态：</td>
                <td class="td_value">
                    <sys:status type="1" defaultValue="11"><bean:write name="monitorHostStatusForm" property="monitorHostStatus.currentState"/></sys:status><bean:write name="statusDuration" />
                </td>
            </tr>
            <tr>
                <td class="td_title">主机名称：</td>
                <td class="td_value">
                    <bean:write name="monitorHost" property="alias"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">主机地址：</td>
                <td class="td_value">
                    <bean:write name="monitorHost" property="hostAddress"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">主机组：</td>
                <td class="td_value">
                    <bean:write name="monitorHost" property="hostgroups.groupName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">状态信息：</td>
                <td class="td_value">
                    <bean:write name="monitorHostStatusForm" property="monitorHostStatus.output"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">性能指标：</td>
                <td class="td_value">
                    <bean:write name="monitorHostStatusForm" property="monitorHostStatus.perfdata"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">尝试次数：</td>
                <td class="td_value">
                    <bean:write name="monitorHostStatusForm" property="monitorHostStatus.currentCheckAttempt"/>/<bean:write name="monitorHostStatusForm" property="monitorHostStatus.maxCheckAttempts"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">上次检查：</td>
                <td class="td_value">
                    <sys:format><bean:write name="monitorHostStatusForm" property="monitorHostStatus.lastCheck"/></sys:format>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查延时：</td>
                <td class="td_value">
                    <bean:write name="monitorHostStatusForm" property="monitorHostStatus.latency"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">下次检查：</td>
                <td class="td_value">
                    <sys:format><bean:write name="monitorHostStatusForm" property="monitorHostStatus.nextCheck"/></sys:format>
                </td>
            </tr>
            <tr>
                <td class="td_title">上次状态变更：</td>
                <td class="td_value">
                    <sys:format><bean:write name="monitorHostStatusForm" property="monitorHostStatus.lastStateChange"/></sys:format>
                </td>
            </tr>
            <tr>
                <td class="td_title">上次通知：</td>
                <td class="td_value">
                    <sys:format defaultValue="N/A"><bean:write name="monitorHostStatusForm" property="monitorHostStatus.lastNotification"/></sys:format>(notification 0)
                </td>
            </tr>
            <tr>
                <td class="td_title">最近更新：</td>
                <td class="td_value">
                    <sys:format><bean:write name="monitorHostStatusForm" property="monitorHostStatus.statusUpdateTime"/></sys:format><bean:write name="updateDuration" />
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
