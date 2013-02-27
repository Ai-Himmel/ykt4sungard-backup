<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
</head>
<body>
    <div style="width:100%;margin:8px 8px 0 10">
        <table width=100% border=1 cellpadding=1 cellspacing=0 bordercolor="#FFFFFF">
            <tbody>
            <tr class="toptitle">
                <td colspan="2" style="text-align:left"><p style="font-weight:bold;">查看时间域</p></td>
            </tr>
            <tr>
                <td class="td_title">名称：</td>
                <td class="td_value">
                    <bean:write name="monitorTimePeriodsForm" property="monitorTimePeriods.alias"/>
                </td>
            </tr>
            <logic:iterate id="timerangervo" name="monitorTimePeriodsForm" property="timerangers" type="org.king.template.util.TimerangerVO">
                <tr>
                        <td class="td_title"><nested:write name="timerangervo"  property="dayAlias"/>：</td>
                        <td class="td_value">
                            <bean:write name="timerangervo" property="monitorTimeranger.startTime" />
                            ------------------
                            <bean:write name="timerangervo" property="monitorTimeranger.endTime" />
                        </td>
                    </tr>
            </logic:iterate>
            <tr>
                <td colspan="2" align="center">
                    &nbsp;&nbsp;
                    <input  type="button" class="button_nor" value=" 返 回 " onclick="history.back();">
                </td>
            </tr>
            </tbody>
        </table>
    </div>
</body>

</html>
