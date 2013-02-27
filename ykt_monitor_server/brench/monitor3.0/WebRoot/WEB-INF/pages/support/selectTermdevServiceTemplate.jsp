<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript">
        function submitTemplate(){
            var templateId = document.getElementsByName("termdevTemplate")[0].value;
            if(templateId==""){
                window.close();
            } else {
                var hostForm = window.opener.document.forms[0];
                var templateForm = window.document.forms[0];
                updateCheckbox(hostForm("monitorHost.notificationsEnabled"),templateForm("notificationsEnabled").value);
                updateCheckbox(hostForm("monitorHost.eventHandlerEnabled"),templateForm("eventHandlerEnabled").value);
                updateCheckbox(hostForm("monitorHost.flapDetectionEnabled"),templateForm("flapDetectionEnabled").value);
                updateCheckbox(hostForm("monitorHost.retainStatusInformation"),templateForm("retainStatusInformation").value);
                updateCheckbox(hostForm("monitorHost.retainNonstatusInformation"),templateForm("retainNonstatusInformation").value);
                hostForm("monitorHost.notificationTimeperiod.timeperiodId").value = templateForm("notificationPeriod.timeperiodId").value;
                hostForm("monitorHost.checkTimeperiod.timeperiodId").value = templateForm("checkPeriod.timeperiodId").value;
                hostForm("monitorHost.checkInterval").value = templateForm("checkInterval").value;
                hostForm("monitorHost.retryInterval").value = templateForm("retryInterval").value;
                hostForm("monitorHost.maxCheckAttempts").value = templateForm("maxCheckAttempts").value;
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
            window.location.href = "termdevService.do?method=selectMonitorTermdevTemplate&templateId="+selectObj.value;
        }
    </script>
</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
    <div id="titleDiv" class="pageTitle">
        <strong> <font class="medium"> 选择监控配置模板 </font> </strong>
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
        <td>
            监控配置模板：
            <select name="termdevTemplate" onchange="selectTemplate(this);">
                <option value="">-----------请选择-----------</option>
                <logic:iterate id="item" name="list" indexId="index">
                    <bean:write name="item" property="templateId"/>
                    <option value="<bean:write name="item" property="templateId"/>" <c:if test="${item.templateId==templateId}">selected="selected"</c:if>><bean:write name="item" property="templateName"/></option>
                </logic:iterate>
            </select>
            &nbsp;&nbsp;&nbsp;&nbsp;<input type="button" value="确定" onclick="submitTemplate();">
        </td>
    </tr>
    <tr>
        <td>
        <logic:notEmpty name="templateId">
            <form action="" name="templateForm">
                <html:hidden property="notificationsEnabled" name="monitorTermdevTemplate"/>
                <html:hidden property="notificationPeriod.timeperiodId" name="monitorTermdevTemplate"/>
                <html:hidden property="checkPeriod.timeperiodId" name="monitorTermdevTemplate"/>
                <html:hidden property="checkInterval" name="monitorTermdevTemplate"/>
                <html:hidden property="retryInterval" name="monitorTermdevTemplate"/>
                <html:hidden property="maxCheckAttempts" name="monitorTermdevTemplate"/>
                <html:hidden property="checkCommand" name="monitorTermdevTemplate"/>
                <html:hidden property="notificationInterval" name="monitorTermdevTemplate"/>
                <html:hidden property="notificationOptions" name="monitorTermdevTemplate"/>
                <html:hidden property="contactGroups.contactgroupId" name="monitorTermdevTemplate"/>
            </form>
        <table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
            <tbody>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">模板名称：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                     <bean:write name="monitorTermdevTemplate" property="templateName"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevTemplate" property="notificationsEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevTemplate" property="notificationsEnabled" >否</logic:notEqual>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">通知时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorTermdevTemplate" property="notificationPeriod.timeperiodId"/>">
                        <bean:write name="monitorTermdevTemplate" property="notificationPeriod.alias"/>
                    </a>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">检查时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorTermdevTemplate" property="checkPeriod.timeperiodId"/>">
                        <bean:write name="monitorTermdevTemplate" property="checkPeriod.alias"/>
                    </a>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">检查时间间隔：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevTemplate" property="checkInterval"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">重试时间间隔：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevTemplate" property="retryInterval"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">最大重试次数：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevTemplate" property="maxCheckAttempts"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">检查命令：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevTemplate" property="checkCommand"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">通知时间间隔：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevTemplate" property="notificationInterval"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">通知选项：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevTemplate" property="notificationOptions"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">联系人组：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorTermdevTemplate" property="contactGroups.contactgroupName"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否启用：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <logic:equal value="1" name="monitorTermdevTemplate" property="templateEnabled" >是</logic:equal>
                    <logic:notEqual value="1" name="monitorTermdevTemplate" property="templateEnabled" >否</logic:notEqual>
                </td>
            </tr>
            </tbody>
        </table>
        </logic:notEmpty>
        </td>
    </tr>
</table>
</body>

</html>
