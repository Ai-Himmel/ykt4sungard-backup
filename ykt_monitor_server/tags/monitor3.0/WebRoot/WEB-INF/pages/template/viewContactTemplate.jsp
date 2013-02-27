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
        <strong> <font class="medium"> 查看联系人模板 </font> </strong>
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
        <table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
            <tbody>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">模板名称：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorContactTemplateForm" property="monitorContactTemplate.templateName"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">主机通知时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorContactTemplateForm" property="monitorContactTemplate.hostNotificationPeriod.timeperiodId"/>">
                        <bean:write name="monitorContactTemplateForm" property="monitorContactTemplate.hostNotificationPeriod.alias"/>
                    </a>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">服务通知时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorContactTemplateForm" property="monitorContactTemplate.serviceNotificationPeriod.timeperiodId"/>">
                        <bean:write name="monitorContactTemplateForm" property="monitorContactTemplate.serviceNotificationPeriod.alias"/>
                    </a>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">主机通知选项：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorContactTemplateForm" property="monitorContactTemplate.hostNotificationOptions"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">服务通知选项：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorContactTemplateForm" property="monitorContactTemplate.serviceNotificationOptions"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">主机通知命令：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorContactTemplateForm" property="monitorContactTemplate.hostNotificationCommands"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">服务通知命令：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorContactTemplateForm" property="monitorContactTemplate.serviceNotificationCommands"/>
                </td>
            </tr>
            <tr>
                <td height="30" align="right" valign="middle">
                </td>
                <td>
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
