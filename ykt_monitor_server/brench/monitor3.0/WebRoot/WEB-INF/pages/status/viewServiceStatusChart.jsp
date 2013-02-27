<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">
    <meta http-equiv="pragma" content="no-cache" />

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript">
        function goBack(){
            var timePeriodId = document.getElementById("timePeriodId").value;
            var url = "serviceHistoryStatus.do?method=listServiceHistoryStatus&timePeriodId="+timePeriodId;
            window.location.href = url;
        }
    </script>
</head>
<body>
<div style="width:100%;margin:8px 8px 0 10">
    <table width="100%" border="0" cellpadding="0" cellspacing="0" bgcolor="#EEEEEE">
        <tr>
            <td>
                <html:form action="serviceHistoryStatus.do?method=viewServiceHistoryChart" method="post">
                <html:hidden property="serviceId"/>
                <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
                    <tr>
                        <td class="listr3">
                            &nbsp;时间周期&nbsp;
                            <html:select property="timePeriodId">
                                <html:option value="0">今天</html:option>
                                <html:option value="1">最近24小时</html:option>
                                <html:option value="2">昨天</html:option>
                                <html:option value="3">本周</html:option>
                                <html:option value="4">最近7天</html:option>
                                <html:option value="5">上周</html:option>
                                <html:option value="6">本月</html:option>
                                <html:option value="7">最近31天</html:option>
                                <html:option value="8">上月</html:option>
                                <html:option value="9">本年</html:option>
                                <html:option value="10">去年</html:option>
                            </html:select>
                            &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                            &nbsp;<input name="back" type="button" class="button_nor" onclick="goBack();" value="返  回">
                        </td>
                    </tr>
                </table>
                </html:form>
            </td>
        </tr>
        <tr>
            <td>
                <table width="100%" border="0" cellpadding="0" cellspacing="0" align="center">
                    <tr>
                        <td align="center" height="440"><img id="bar" src="<c:url value="/displayChart.do?method=display&filename="/><c:out value="${filename}"/>" border=0 usemap="#<c:out value="${filename}"/>" width="800" height="320"></td>
                    </tr>
                </table>
            </td>
        </tr>
    </table>
</div>
</body>
</html>
