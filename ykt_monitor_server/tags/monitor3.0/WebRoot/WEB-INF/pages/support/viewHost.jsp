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
        <html:errors  property="addMonitorHost"/>
        <table width=100% border=1 cellpadding=1 cellspacing=0 bordercolor="#FFFFFF">
            <tbody>
            <tr class="toptitle">
                <td colspan="2" style="text-align:left">查看主机</td>
            </tr>
            <tr>
                <td class="td_title">主机名称：</td>
                <td class="td_value">
                    <bean:write name="monitorHostForm" property="monitorHost.alias"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">显示名称：</td>
                <td class="td_value">
                    <bean:write name="monitorHostForm" property="monitorHost.displayName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">主机地址：</td>
                <td class="td_value">
                    <bean:write name="monitorHostForm" property="monitorHost.hostAddress"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查命令：</td>
                <td class="td_value">
                    <bean:write name="monitorHostForm" property="monitorHost.checkCommand.commandName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查命令参数：</td>
                <td class="td_value">
                    <bean:write name="monitorHostForm" property="monitorHost.checkCommandArgs"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间域：</td>
                <td class="td_value">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorHostForm" property="monitorHost.checkTimeperiod.timeperiodId"/>">
                        <bean:write name="monitorHostForm" property="monitorHost.checkTimeperiod.alias"/>
                    </a>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorHostForm" property="monitorHost.checkInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">重试时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorHostForm" property="monitorHost.retryInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">最大尝试次数：</td>
                <td class="td_value">
                    <bean:write name="monitorHostForm" property="monitorHost.maxCheckAttempts"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">是否允许主动检查：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorHostForm" property="monitorHost.activeChecksEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorHostForm" property="monitorHost.activeChecksEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间域：</td>
                <td class="td_value">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorHostForm" property="monitorHost.notificationTimeperiod.timeperiodId"/>">
                        <bean:write name="monitorHostForm" property="monitorHost.notificationTimeperiod.alias"/>
                    </a>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorHostForm" property="monitorHost.notificationInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">down机是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorHostForm" property="monitorHost.notifyOnDown" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorHostForm" property="monitorHost.notifyOnDown" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">主机recovery是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorHostForm" property="monitorHost.notifyOnRecovery" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorHostForm" property="monitorHost.notifyOnRecovery" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">联系人组：</td>
                <td class="td_value">
                    <bean:write name="monitorHostForm" property="monitorHost.contactGroups.contactgroupName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">主机组：</td>
                <td class="td_value">
                    <bean:write name="monitorHostForm" property="monitorHost.hostgroups.groupName"/>
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
