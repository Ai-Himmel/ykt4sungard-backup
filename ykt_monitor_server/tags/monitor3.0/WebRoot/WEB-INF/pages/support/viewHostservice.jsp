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
                <td colspan="2" style="text-align:left"><p style="font-weight:bold;">查看主机服务</p></td>
            </tr>
            <tr>
                <td class="td_title">服务名称：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceForm" property="monitorService.serviceName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">主机：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceForm" property="monitorService.monitorHost.alias"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查命令：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceForm" property="monitorService.checkCommand.commandName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查命令参数：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceForm" property="monitorService.checkCommandArgs"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间域：</td>
                <td class="td_value">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorServiceForm" property="monitorService.checkTimeperiod.timeperiodId"/>">
                        <bean:write name="monitorServiceForm" property="monitorService.checkTimeperiod.alias"/>
                    </a>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceForm" property="monitorService.checkInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">重试时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceForm" property="monitorService.retryInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">最大尝试次数：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceForm" property="monitorService.maxCheckAttempts"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">是否允许主动检查：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorServiceForm" property="monitorService.activeChecksEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorServiceForm" property="monitorService.activeChecksEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间域：</td>
                <td class="td_value">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorServiceForm" property="monitorService.notificationTimeperiod.timeperiodId"/>">
                        <bean:write name="monitorServiceForm" property="monitorService.notificationTimeperiod.alias"/>
                    </a>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceForm" property="monitorService.notificationInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">warning是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorServiceForm" property="monitorService.notifyOnWarning" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorServiceForm" property="monitorService.notifyOnWarning" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">unknown是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorServiceForm" property="monitorService.notifyOnUnknown" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorServiceForm" property="monitorService.notifyOnUnknown" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">critical是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorServiceForm" property="monitorService.notifyOnCritical" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorServiceForm" property="monitorService.notifyOnCritical" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">recovery是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorServiceForm" property="monitorService.notifyOnRecovery" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorServiceForm" property="monitorService.notifyOnRecovery" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">联系人组：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceForm" property="monitorService.contactGroups.contactgroupName"/>
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
