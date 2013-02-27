<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript">
        function submitTemplate(){
            var templateId = document.getElementsByName("hostTemplate")[0].value;
            if(templateId==""){
                window.close();
            } else {
                var hostForm = window.opener.document.forms[0];
                var templateForm = window.document.forms[0];
                hostForm("monitorHost.checkCommand.commandId").value = templateForm("checkCommand.commandId").value;
                hostForm("monitorHost.checkCommandArgs").value = templateForm("checkCommandArgs").value;
                hostForm("monitorHost.checkTimeperiod.timeperiodId").value = templateForm("checkTimeperiod.timeperiodId").value;
                hostForm("monitorHost.checkInterval").value = templateForm("checkInterval").value;
                hostForm("monitorHost.retryInterval").value = templateForm("retryInterval").value;
                hostForm("monitorHost.maxCheckAttempts").value = templateForm("maxCheckAttempts").value;
                updateCheckbox(hostForm("monitorHost.activeChecksEnabled"),templateForm("activeChecksEnabled").value);
                hostForm("monitorHost.notificationTimeperiod.timeperiodId").value = templateForm("notificationTimeperiod.timeperiodId").value;
                hostForm("monitorHost.notificationInterval").value = templateForm("notificationInterval").value;
                updateCheckbox(hostForm("monitorHost.notifyOnDown"),templateForm("notifyOnDown").value);
                updateCheckbox(hostForm("monitorHost.notifyOnRecovery"),templateForm("notifyOnRecovery").value);
                hostForm("monitorHost.contactGroups.contactgroupId").value = templateForm("contactGroups.contactgroupId").value;
                hostForm("monitorHost.hostgroups.hostgroupId").value = templateForm("hostgroups.hostgroupId").value;
                window.close();
            }
        }
        function updateCheckbox(checkboxObj,value){
            if(value==1){
                checkboxObj.checked = "checked";
            } else {
                checkboxObj.checked = "";
            }
        }
        function selectTemplate(selectObj){
            window.location.href = "host.do?method=selectMonitorHostTemplate&templateId="+selectObj.value;
        }
    </script>
</head>
<body>
    <div style="width:100%;margin:8px 8px 0 10">
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;主机模板&nbsp;
                    <select name="hostTemplate" onchange="selectTemplate(this);">
                        <option value="">-----------请选择-----------</option>
                        <logic:iterate id="item" name="list" indexId="index">
                            <bean:write name="item" property="templateId"/>
                            <option value="<bean:write name="item" property="templateId"/>" <c:if test="${item.templateId==templateId}">selected="selected"</c:if>><bean:write name="item" property="templateName"/></option>
                        </logic:iterate>
                    </select>
                    &nbsp;&nbsp;&nbsp;&nbsp;<input type="button" value="确定" class="button_nor" onclick="submitTemplate();">
                </td>
            </tr>
        </table>
        <logic:notEmpty name="templateId">
            <table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor="#FFFFFF">
                <tbody>
                <tr>
                    <td class="td_title">模板名称：</td>
                    <td class="td_value">
                        <label id="templateName"><bean:write name="monitorHostTemplate" property="templateName"/></label>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">检查命令：</td>
                    <td class="td_value">
                        <bean:write name="monitorHostTemplate" property="checkCommand.commandName"/>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">检查命令参数：</td>
                    <td class="td_value">
                        <bean:write name="monitorHostTemplate" property="checkCommandArgs"/>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">检查时间域：</td>
                    <td class="td_value">
                        <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorHostTemplate" property="checkTimeperiod.timeperiodId"/>">
                            <bean:write name="monitorHostTemplate" property="checkTimeperiod.alias"/>
                        </a>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">检查时间间隔：</td>
                    <td class="td_value">
                        <bean:write name="monitorHostTemplate" property="checkInterval"/>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">重试时间间隔：</td>
                    <td class="td_value">
                        <bean:write name="monitorHostTemplate" property="retryInterval"/>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">最大重试次数：</td>
                    <td class="td_value">
                        <bean:write name="monitorHostTemplate" property="maxCheckAttempts"/>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">是否允许主动检查：</td>
                    <td class="td_value">
                        <logic:equal value="1" name="monitorHostTemplate" property="activeChecksEnabled" >是</logic:equal>
                        <logic:notEqual value="1" name="monitorHostTemplate" property="activeChecksEnabled" >否</logic:notEqual>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">通知时间域：</td>
                    <td class="td_value">
                        <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorHostTemplate" property="notificationTimeperiod.timeperiodId"/>">
                            <bean:write name="monitorHostTemplate" property="notificationTimeperiod.alias"/>
                        </a>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">通知时间间隔：</td>
                    <td class="td_value">
                        <bean:write name="monitorHostTemplate" property="notificationInterval"/>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">down机是否通知：</td>
                    <td class="td_value">
                        <logic:equal value="1" name="monitorHostTemplate" property="notifyOnDown" >是</logic:equal>
                        <logic:notEqual value="1" name="monitorHostTemplate" property="notifyOnDown" >否</logic:notEqual>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">主机recovery是否通知：</td>
                    <td class="td_value">
                        <logic:equal value="1" name="monitorHostTemplate" property="notifyOnRecovery" >是</logic:equal>
                        <logic:notEqual value="1" name="monitorHostTemplate" property="notifyOnRecovery" >否</logic:notEqual>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">联系人组：</td>
                    <td class="td_value">
                        <bean:write name="monitorHostTemplate" property="contactGroups.contactgroupName"/>
                    </td>
                </tr>
                <tr>
                    <td class="td_title">主机组：</td>
                    <td class="td_value">
                        <bean:write name="monitorHostTemplate" property="hostgroups.groupName"/>
                    </td>
                </tr>
                </tbody>
            </table>
            <form action="" name="templateForm">
                <html:hidden property="checkCommand.commandId" name="monitorHostTemplate"/>
                <html:hidden property="checkCommandArgs" name="monitorHostTemplate"/>
                <html:hidden property="checkTimeperiod.timeperiodId" name="monitorHostTemplate"/>
                <html:hidden property="checkInterval" name="monitorHostTemplate"/>
                <html:hidden property="retryInterval" name="monitorHostTemplate"/>
                <html:hidden property="maxCheckAttempts" name="monitorHostTemplate"/>
                <html:hidden property="activeChecksEnabled" name="monitorHostTemplate"/>
                <html:hidden property="notificationTimeperiod.timeperiodId" name="monitorHostTemplate"/>
                <html:hidden property="notificationInterval" name="monitorHostTemplate"/>
                <html:hidden property="notifyOnDown" name="monitorHostTemplate"/>
                <html:hidden property="notifyOnRecovery" name="monitorHostTemplate"/>
                <html:hidden property="contactGroups.contactgroupId" name="monitorHostTemplate"/>
                <html:hidden property="hostgroups.hostgroupId" name="monitorHostTemplate"/>
            </form>
        </logic:notEmpty>
    </div>
</body>

</html>
