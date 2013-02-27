<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript">
        function submitTemplate(){
            var templateId = document.getElementsByName("serviceTemplate")[0].value;
            if(templateId==""){
                window.close();
            } else {
                var serviceForm = window.opener.document.forms[0];
                var templateForm = window.document.forms[0];
                serviceForm("monitorService.checkTimeperiod.timeperiodId").value = templateForm("checkTimeperiod.timeperiodId").value;
                serviceForm("monitorService.checkInterval").value = templateForm("checkInterval").value;
                serviceForm("monitorService.retryInterval").value = templateForm("retryInterval").value;
                serviceForm("monitorService.maxCheckAttempts").value = templateForm("maxCheckAttempts").value;
                updateCheckbox(serviceForm("monitorService.activeChecksEnabled"),templateForm("activeChecksEnabled").value);
                serviceForm("monitorService.notificationTimeperiod.timeperiodId").value = templateForm("notificationTimeperiod.timeperiodId").value;
                serviceForm("monitorService.notificationInterval").value = templateForm("notificationInterval").value;
                updateCheckbox(serviceForm("monitorService.notifyOnWarning"),templateForm("notifyOnWarning").value);
                updateCheckbox(serviceForm("monitorService.notifyOnUnknown"),templateForm("notifyOnUnknown").value);
                updateCheckbox(serviceForm("monitorService.notifyOnCritical"),templateForm("notifyOnCritical").value);
                updateCheckbox(serviceForm("monitorService.notifyOnRecovery"),templateForm("notifyOnRecovery").value);
                serviceForm("monitorService.contactGroups.contactgroupId").value = templateForm("contactGroups.contactgroupId").value;
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
            window.location.href = "hostservice.do?method=selectMonitorServiceTemplate&templateId="+selectObj.value;
        }
    </script>
</head>
<body>
    <div style="width:100%;margin:8px 8px 0 10">
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;主机服务模板&nbsp;
                    <select name="serviceTemplate" onchange="selectTemplate(this);">
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
                    <bean:write name="monitorServiceTemplate" property="templateName"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间域：</td>
                <td class="td_value">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorServiceTemplate" property="checkTimeperiod.timeperiodId"/>">
                        <bean:write name="monitorServiceTemplate" property="checkTimeperiod.alias"/>
                    </a>
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceTemplate" property="checkInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">重试时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceTemplate" property="retryInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">最大重试次数：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceTemplate" property="maxCheckAttempts"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">是否允许主动检查：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorServiceTemplate" property="activeChecksEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorServiceTemplate" property="activeChecksEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间域：</td>
                <td class="td_value">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorServiceTemplate" property="notificationTimeperiod.timeperiodId"/>">
                        <bean:write name="monitorServiceTemplate" property="notificationTimeperiod.alias"/>
                    </a>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间间隔：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceTemplate" property="notificationInterval"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">warning是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorServiceTemplate" property="notifyOnWarning" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorServiceTemplate" property="notifyOnWarning" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">unknown是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorServiceTemplate" property="notifyOnUnknown" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorServiceTemplate" property="notifyOnUnknown" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">critical是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorServiceTemplate" property="notifyOnCritical" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorServiceTemplate" property="notifyOnCritical" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">recovery是否通知：</td>
                <td class="td_value">
                    <logic:equal value="1" name="monitorServiceTemplate" property="notifyOnRecovery" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorServiceTemplate" property="notifyOnRecovery" >否</logic:notEqual>
                </td>
            </tr>
            <tr>
                <td class="td_title">联系人组：</td>
                <td class="td_value">
                    <bean:write name="monitorServiceTemplate" property="contactGroups.contactgroupName"/>
                </td>
            </tr>
            </tbody>
        </table>
        <form action="" name="templateForm">
            <html:hidden property="checkTimeperiod.timeperiodId" name="monitorServiceTemplate"/>
            <html:hidden property="checkInterval" name="monitorServiceTemplate"/>
            <html:hidden property="retryInterval" name="monitorServiceTemplate"/>
            <html:hidden property="maxCheckAttempts" name="monitorServiceTemplate"/>
            <html:hidden property="activeChecksEnabled" name="monitorServiceTemplate"/>
            <html:hidden property="notificationTimeperiod.timeperiodId" name="monitorServiceTemplate"/>
            <html:hidden property="notificationInterval" name="monitorServiceTemplate"/>
            <html:hidden property="notifyOnWarning" name="monitorServiceTemplate"/>
            <html:hidden property="notifyOnUnknown" name="monitorServiceTemplate"/>
            <html:hidden property="notifyOnCritical" name="monitorServiceTemplate"/>
            <html:hidden property="notifyOnRecovery" name="monitorServiceTemplate"/>
            <html:hidden property="contactGroups.contactgroupId" name="monitorServiceTemplate"/>
        </form>
        </logic:notEmpty>
    </div>
</body>

</html>
