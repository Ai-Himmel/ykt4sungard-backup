<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript" src="<c:url value="/pages/scripts/setTme.js"/>" ></script>
    <script type="text/javascript">
        function check(){
            var alias = document.getElementById("monitorTimePeriods.alias").value;
            if(alias==null || alias==""){
                return false;
            }
            return true;
        }
        function submitForm(){
            var editForm = document.forms[0];
            if(!check()){
                alert('名称必须输入！');
                document.getElementById("monitorTimePeriods.alias").focus();
                return;
            }
            var type = document.getElementById("type").value;
            if(type=="edit"){
                editForm.action = "timePeriods.do?method=updateMonitorTimePeriods";
            } else if(type=="add"){
                editForm.action = "timePeriods.do?method=addMonitorTimePeriods";
            }
            editForm.submit();
        }
    </script>
</head>
<body>
<html:form action="timePeriods.do?method=addMonitorTimePeriods" method="post">
<html:hidden property="monitorTimePeriods.timeperiodId" />
<html:hidden property="type" />
    <div style="width:100%;margin:8px 8px 0 10">
        <html:errors  property="addMonitorTimePeriods"/>
        <table width=100% border=1 cellpadding=1 cellspacing=0 bordercolor="#FFFFFF">
            <tbody>
            <tr class="toptitle">
                <td colspan="2" style="text-align:left"><p style="font-weight:bold;"><logic:equal name="monitorTimePeriodsForm" property="type" value="edit">修改</logic:equal><logic:equal name="monitorTimePeriodsForm" property="type" value="add">增加</logic:equal>时间域</p></td>
            </tr>
            <tr>
                <td class="td_title">名称：</td>
                <td class="td_value">
                    <html:text property="monitorTimePeriods.alias" styleClass="input_box" maxlength="100"/>
                    <font color="#ff0000">*</font>
                </td>
            </tr>
            <logic:notEmpty name="monitorTimePeriodsForm" property="timerangers">
                <nested:iterate  id="timerangervo" property="timerangers" type="org.king.template.util.TimerangerVO" indexId="index">
                    <tr>
                        <td class="td_title"><nested:write  property="dayAlias"/>：</td>
                        <td class="td_value">
                            <nested:text  property="monitorTimeranger.startTime" onclick="_SetTime(this)" readonly="true" >
                            </nested:text>
                            ------------------
                            <nested:text  property="monitorTimeranger.endTime" onclick="_SetTime(this)" readonly="true">
                            </nested:text>
                            <nested:hidden  property="monitorTimeranger.timeperiodDay"/>
                        <nested:hidden  property="monitorTimeranger.timerangerId"/>
                        </td>
                    </tr>
                </nested:iterate>
            </logic:notEmpty>
            <tr>
                <td colspan="2" align="center">
                    &nbsp;&nbsp;
                    <input type="button" class="button_nor" onclick="javascript:submitForm();" value=" 保 存 " />
                    <input type="reset" class="button_nor" value=" 重 置 " />
                    <input  type="button" class="button_nor" value=" 返 回 " onclick="history.back();">
                </td>
            </tr>
            </tbody>
        </table>
    </div>
</html:form>
</body>

</html>
