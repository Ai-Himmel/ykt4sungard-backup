<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript">
        function check(){
            var varName = document.getElementById("monitorRuntimevariables.varname").value;
            if(varName==null || varName==""){
                return false;
            }
            return true;
        }
        function submitForm(){
            var editForm = document.forms[0];
            if(!check()){
                alert('变量名称必须输入！');
                document.getElementById("monitorRuntimevariables.varname").focus();
                return;
            }
            var type = document.getElementById("type").value;
            if(type=="edit"){
                editForm.action = "runtimevariables.do?method=updateMonitorRuntimevariables";
            } else if(type=="add"){
                editForm.action = "runtimevariables.do?method=addMonitorRuntimevariables";
            }
            editForm.submit();
        }
    </script>
</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<html:form action="runtimevariables.do?method=addMonitorRuntimevariables" method="post">
<html:hidden property="monitorRuntimevariables.runtimevariableId" />
<html:hidden property="type" />
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
    <div id="titleDiv" class="pageTitle">
        <strong> <font class="medium"><logic:equal name="monitorRuntimevariablesForm" property="type" value="edit">修改</logic:equal><logic:equal name="monitorRuntimevariablesForm" property="type" value="add">增加</logic:equal>运行变量 </font> </strong>
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
        <html:errors  property="addMonitorRuntimevariables"/>
        <table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
            <tbody>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">变量名称：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">

                    <html:text property="monitorRuntimevariables.varname" styleClass="input_box" maxlength="50"/>
                    <font color="#ff0000">*</font>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">变量中文名：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorRuntimevariables.varnameZh" styleClass="input_box" maxlength="100"/>
                </td>
            </tr>
            <tr align="center" valign="center">
                <td width="22%" height="26" align="right" valign="middle" bgcolor="#D1DAE9">
                    <span class="medium">变量值：</span>
                <td width="78%" align="left" valign="middle" bgcolor="#E7F1F5">
                    <html:text property="monitorRuntimevariables.varvalue" styleClass="input_box" maxlength="100"/>
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
