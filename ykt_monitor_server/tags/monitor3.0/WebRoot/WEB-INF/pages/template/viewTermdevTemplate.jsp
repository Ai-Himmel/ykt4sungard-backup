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
                <td colspan="2" style="text-align:left"><p style="font-weight:bold;">查看监控配置模板</p></td>
            </tr>
            <tr>
                <td class="td_title">模板名称：</td>
                <td class="td_value">
                     <bean:write name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.templateName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间域：</td>
                <td class="td_value">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.notificationPeriod.timeperiodId"/>">
                        <bean:write name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.notificationPeriod.alias"/>
                    </a>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间域：</td>
                <td class="td_value">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.checkPeriod.timeperiodId"/>">
                        <bean:write name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.checkPeriod.alias"/>
                    </a>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.checkInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.notificationInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">down是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.notifyOnDown" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.notifyOnDown" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">recovery是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.notifyOnRecovery" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.notifyOnRecovery" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">是否允许主动检查：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.activeChecksEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.activeChecksEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">联系人组：</td>
                <td class="td_value">
                    <bean:write name="monitorTermdevTemplateForm" property="monitorTermdevTemplate.contactGroups.contactgroupName"/>
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
