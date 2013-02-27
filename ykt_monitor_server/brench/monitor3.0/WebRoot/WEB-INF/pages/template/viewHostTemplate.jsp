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
                <td colspan="2" style="text-align:left"><p style="font-weight:bold;">查看主机模板</p></td>
            </tr>
            <tr>
                <td class="td_title">模板名称：</td>
                <td class="td_value">
                    <bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.templateName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查命令：</td>
                <td class="td_value">
                    <bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.checkCommand.commandName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查命令参数：</td>
                <td class="td_value">
                    <bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.checkCommandArgs"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间域：</td>
                <td class="td_value">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.checkTimeperiod.timeperiodId"/>">
                        <bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.checkTimeperiod.alias"/>
                    </a>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.checkInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">重试时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.retryInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">最大重试次数：</td>
                <td class="td_value">
                    <bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.maxCheckAttempts"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">是否允许主动检查：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorHostTemplateForm" property="monitorHostTemplate.activeChecksEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorHostTemplateForm" property="monitorHostTemplate.activeChecksEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间域：</td>
                <td class="td_value">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.notificationTimeperiod.timeperiodId"/>">
                        <bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.notificationTimeperiod.alias"/>
                    </a>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.notificationInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">down机是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorHostTemplateForm" property="monitorHostTemplate.notifyOnDown" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorHostTemplateForm" property="monitorHostTemplate.notifyOnDown" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">主机recovery是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorHostTemplateForm" property="monitorHostTemplate.notifyOnRecovery" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorHostTemplateForm" property="monitorHostTemplate.notifyOnRecovery" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">联系人组：</td>
                <td class="td_value">
                    <bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.contactGroups.contactgroupName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">主机组：</td>
                <td class="td_value">
                    <bean:write name="monitorHostTemplateForm" property="monitorHostTemplate.hostgroups.groupName"/>
                </td>
            </tr>
            <tr>
                <td colspan="2" align="center">
                    &nbsp;&nbsp;
                    <input  type="button" class="button_nor" value=" 返 回 " onclick="history.back();">
                </td>
            </tr>
            </tbody>
        </table>
    </div>
</body>

</html>
