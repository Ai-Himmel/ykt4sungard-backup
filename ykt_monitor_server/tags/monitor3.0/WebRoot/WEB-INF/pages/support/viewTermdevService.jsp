<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
    <div id="titleDiv" class="pageTitle">
        <strong> <font class="medium"> 查看设备服务 </font> </strong>
    </div>
    <div id="lineDiv" class="hrLine">
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td class="tdborderLine"></td>
            </tr>
        </table>
    </div>
    <tr>
        <td align="center" valign="middle">
            &nbsp;
        </td>
    </tr>
    <tr>
        <html:errors  property="addMonitorTermdevService"/>
        <table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
            <tbody>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">设备服务名称：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.devserviceName"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">设备：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.deviceId"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">检查命令：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.checkCommand.commandName"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">检查命令参数：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.checkCommandArgs"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">事件处理命令id：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.eventhandlerCommandId"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">事件命令处理参数：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.eventhandlerCommandArgs"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">通知时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.notificationTimeperiod.timeperiodId"/>">
                        <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.notificationTimeperiod.alias"/>
                    </a>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">工作时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.checkTimeperiod.timeperiodId"/>">
                        <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.checkTimeperiod.alias"/>
                    </a>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">检查时间间隔：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.checkInterval"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">重试时间间隔：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.retryInterval"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">最大尝试次数：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.maxCheckAttempts"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">通知时间间隔：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.notificationInterval"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">warning是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnWarning" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnWarning" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">unknow是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnUnknown" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnUnknown" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">critical是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnCritical" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnCritical" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">recovery是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnRecovery" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnRecovery" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">抖动是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnFlapping" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnFlapping" >否</logic:notEqual>
                </td>
            </tr>

            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">downtime是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnDowntime" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notifyOnDowntime" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否抖动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.flapDetectionEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.flapDetectionEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否ok抖动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.flapDetectionOnOk" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.flapDetectionOnOk" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否warning抖动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.flapDetectionOnWarning" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.flapDetectionOnWarning" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否unknow抖动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.flapDetectionOnUnknown" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.flapDetectionOnUnknown" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否critical抖动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.flapDetectionOnCritical" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.flapDetectionOnCritical" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">抖动域低值：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.lowFlapThreshold"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">抖动域高值：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.highFlapThreshold"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否及时性检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.freshnessChecksEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.freshnessChecksEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">及时性检查允许域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.freshnessThreshold"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否允许被动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.passiveChecksEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.passiveChecksEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否允许事件处理：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.eventHandlerEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.eventHandlerEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否允许主动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.activeChecksEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.activeChecksEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">保留状态信息：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.retainStatusInformation" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.retainStatusInformation" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">保留非状态信息：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.retainNonstatusInformation" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.retainNonstatusInformation" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否需要通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notificationsEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevServiceForm" property="monitorTermdevService.notificationsEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">便签：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.notes"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">便签url：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.notesUrl"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">actionurl：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevServiceForm" property="monitorTermdevService.actionurl"/>
                </td>
            </tr>
            <tr>
                <td colspan="2"  align="center">
                    &nbsp;&nbsp;
                    <input  type="button" class="submitButton" value=" 返 回 " onclick="history.back();">
                </td>
            </tr>
            </tbody>
        </table>
    </tr>
</table>
</body>

</html>
