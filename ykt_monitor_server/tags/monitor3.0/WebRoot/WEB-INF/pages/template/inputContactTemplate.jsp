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
            var templateName = document.getElementById("monitorContactTemplate.templateName").value;
            if(templateName==null || templateName==""){
                return false;
            }
            return true;
        }
        function submitForm(){
            var editForm = document.forms[0];
            if(!check()){
                alert('模板名称必须输入！');
                document.getElementById("monitorContactTemplate.templateName").focus();
                return;
            }
            var type = document.getElementById("type").value;
            if(type=="edit"){
                editForm.action = "contactTemplate.do?method=updateMonitorContactTemplate";
            } else if(type=="add"){
                editForm.action = "contactTemplate.do?method=addMonitorContactTemplate";
            }
            editForm.submit();
        }
    </script>
</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<html:form action="contactTemplate.do?method=addMonitorContactTemplate" method="post">
<html:hidden property="monitorContactTemplate.templateId" />
<html:hidden property="type" />
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
    <div id="titleDiv" class="pageTitle">
        <strong> <font class="medium"> <logic:equal name="monitorContactTemplateForm" property="type" value="edit">修改</logic:equal><logic:equal name="monitorContactTemplateForm" property="type" value="add">增加</logic:equal>联系人模板 </font> </strong>
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
        <html:errors  property="addMonitorContactTemplate"/>
        <table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
            <tbody>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">模板名称：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">

                    <html:text property="monitorContactTemplate.templateName" styleClass="input_box" maxlength="30"/>
                    <font color="#ff0000">*</font>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">主机通知时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:select property="monitorContactTemplate.hostNotificationPeriod.timeperiodId" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorTimePeriods" property="timeperiodId" labelProperty="alias"/>
                    </html:select>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">服务通知时间域：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:select property="monitorContactTemplate.serviceNotificationPeriod.timeperiodId" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorTimePeriods" property="timeperiodId" labelProperty="alias"/>
                    </html:select>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">主机通知选项：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorContactTemplate.hostNotificationOptions" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">服务通知选项：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorContactTemplate.serviceNotificationOptions" styleClass="input_box" maxlength="30"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">主机通知命令：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:select property="monitorContactTemplate.hostNotificationCommands" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options name="hostCommands" labelName="hostCommands"/>
                    </html:select>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">服务通知命令：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:select property="monitorContactTemplate.serviceNotificationCommands" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options name="serviceCommands" labelName="serviceCommands"/>
                    </html:select>
                </td>
            </tr>
            <tr>
                <td height="30" align="center" valign="middle">
                </td>
                <td>
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
