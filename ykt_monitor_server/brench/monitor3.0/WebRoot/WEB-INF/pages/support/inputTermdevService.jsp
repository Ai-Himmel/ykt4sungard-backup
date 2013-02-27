<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
    <link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript">
        function check(){
            var devserviceName = document.getElementById("monitorTermdevService.devserviceName").value;
            if(devserviceName==null || devserviceName==""){
                return false;
            }
            return true;
        }
        function submitForm(){
            var editForm = document.forms[0];
            if(!check()){
                alert('设备服务名称必须输入！');
                document.getElementById("monitorTermdevService.devserviceName").focus();
                return;
            }
            var type = document.getElementById("type").value;
            if(type=="edit"){
                editForm.action = "termdevService.do?method=updateMonitorTermdevService";
            } else if(type=="add"){
                editForm.action = "termdevService.do?method=addMonitorTermdevService";
            }
            editForm.submit();
        }
    </script>
</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<html:form action="termdevService.do?method=addMonitorTermdevService" method="post">
<html:hidden property="monitorTermdevService.devserviceId" />
<html:hidden property="type" />
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
    <div id="titleDiv" class="pageTitle">
        <strong> <font class="medium"> <logic:equal name="monitorTermdevServiceForm" property="type" value="edit">修改</logic:equal><logic:equal name="monitorTermdevServiceForm" property="type" value="add">增加</logic:equal>设备服务 </font> </strong>
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
                    <html:text property="monitorTermdevService.devserviceName" styleClass="input_box" maxlength="30"/>
                    <font color="#ff0000">*</font>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">设备：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.deviceId" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">检查命令：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:select property="monitorTermdevService.checkCommand.commandId" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="termdevServiceCommands" property="commandId" labelProperty="commandName"/>
                    </html:select>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">检查命令参数：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.checkCommandArgs" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">事件处理命令id：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.eventhandlerCommandId" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">事件命令处理参数：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.eventhandlerCommandArgs" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">通知时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:select property="monitorTermdevService.notificationTimeperiod.timeperiodId" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorTimePeriods" property="timeperiodId" labelProperty="alias"/>
                    </html:select>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">工作时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:select property="monitorTermdevService.checkTimeperiod.timeperiodId" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorTimePeriods" property="timeperiodId" labelProperty="alias"/>
                    </html:select>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">检查时间间隔：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.checkInterval" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">重试时间间隔：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.retryInterval" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">最大尝试次数：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.maxCheckAttempts" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">通知时间间隔：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.notificationInterval" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">warning是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.notifyOnWarning" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">unknow是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.notifyOnUnknown" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">critical是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.notifyOnCritical" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">recovery是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.notifyOnRecovery" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">抖动是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.notifyOnFlapping" value="1"/>
                </td>
            </tr>

            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">downtime是否通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.notifyOnDowntime" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否抖动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.flapDetectionEnabled" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否ok抖动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.flapDetectionOnOk" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否warning抖动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.flapDetectionOnWarning" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否unknow抖动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.flapDetectionOnUnknown" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否critical抖动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.flapDetectionOnCritical" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">抖动域低值：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.lowFlapThreshold" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">抖动域高值：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.highFlapThreshold" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否及时性检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.freshnessChecksEnabled" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">及时性检查允许域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.freshnessThreshold" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否允许被动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.passiveChecksEnabled" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否允许事件处理：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.eventHandlerEnabled" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否允许主动检查：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.activeChecksEnabled" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">保留状态信息：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.retainStatusInformation" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">保留非状态信息：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.retainNonstatusInformation" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">是否需要通知：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:checkbox property="monitorTermdevService.notificationsEnabled" value="1"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">便签：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.notes" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">便签url：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.notesUrl" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">actionurl：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorTermdevService.actionurl" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr>
                <td  align="center" colspan="2">
                    &nbsp;&nbsp;
                    <input type="button" class="submitButton" onclick="javascript:submitForm();" value=" 保 存 " />
                    <input type="reset" class="submitButton" value=" 重 置 " />
                    <input  type="button" class="submitButton" value=" 返 回 " onclick="history.back();">
                </td>
            </tr>
            </tbody>
        </table>
    </tr>
</table>
</html:form>
</body>

</html>
