<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript">
        function submitTemplate(){
            var templateId = document.getElementsByName("contactTemplate")[0].value;
            if(templateId==""){
                window.close();
            } else {
                var contactForm = window.opener.document.forms[0];
                var templateForm = window.document.forms[0];
                contactForm("monitorContact.hostTimeperiod.timeperiodId").value = templateForm("hostNotificationPeriod.timeperiodId").value;
                contactForm("monitorContact.serviceTimeperiod.timeperiodId").value = templateForm("serviceNotificationPeriod.timeperiodId").value;
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
            window.location.href = "contact.do?method=selectMonitorContactTemplate&templateId="+selectObj.value;
        }
    </script>
</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
    <div id="titleDiv" class="pageTitle">
        <strong> <font class="medium"> 选择联系人模板 </font> </strong>
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
            联系人模板：
            <select name="contactTemplate" onchange="selectTemplate(this);">
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
                <html:hidden property="hostNotificationPeriod.timeperiodId" name="monitorContactTemplate"/>
                <html:hidden property="serviceNotificationPeriod.timeperiodId" name="monitorContactTemplate"/>
                <html:hidden property="hostNotificationOptions" name="monitorContactTemplate"/>
                <html:hidden property="serviceNotificationOptions" name="monitorContactTemplate"/>
                <html:hidden property="hostNotificationCommands" name="monitorContactTemplate"/>
                <html:hidden property="serviceNotificationCommands" name="monitorContactTemplate"/>
            </form>
        <table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
            <tbody>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">模板名称：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorContactTemplate" property="templateName"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">主机通知时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorContactTemplate" property="hostNotificationPeriod.timeperiodId"/>">
                        <bean:write name="monitorContactTemplate" property="hostNotificationPeriod.alias"/>
                    </a>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">服务通知时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <a href="timePeriods.do?method=viewMonitorTimePeriods&periodId=<bean:write name="monitorContactTemplate" property="serviceNotificationPeriod.timeperiodId"/>">
                        <bean:write name="monitorContactTemplate" property="serviceNotificationPeriod.alias"/>
                    </a>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">主机通知选项：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorContactTemplate" property="hostNotificationOptions"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">服务通知选项：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorContactTemplate" property="serviceNotificationOptions"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">主机通知命令：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorContactTemplate" property="hostNotificationCommands"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">服务通知命令：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <bean:write name="monitorContactTemplate" property="serviceNotificationCommands"/>
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
