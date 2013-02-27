<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link rel="stylesheet" type="text/css" href="<c:url value="/pages/displaytag/css/screen.css"/>"/>
    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
    <script type="text/javascript" src="<c:url value="/pages/scripts/global.js"/>" ></script>
    <script type="text/javascript" src="<c:url value="/pages/scripts/grid.js"/>" ></script>
    <script type="text/javascript" src="<c:url value="/pages/scripts/render.js"/>" ></script>
    <script type="text/javascript">
        function renderRow(row) {
            switch (row.cells[0].innerText) {
                case "up":
                    break;
                case "down":
                    row.style.background= "#FE3E00";
                    break;
                case "unreachable":
                    row.style.background= "#F9A810";
                    break;
            }
        }
        window.onload = function(){
            renderTable('row');
        }
        function goBack(){
            var timePeriodId = document.getElementById("timePeriodId").value;
            var url = "termdeviceHistoryStatus.do?method=listTermdeviceHistoryStatus&timePeriodId="+timePeriodId;
            window.location.href = url;
        }
    </script>
</head>
<body>
<div style="width:100%;margin:8px 8px 0 10">
    <html:form action="termdeviceHistoryStatus.do?method=viewTermdeviceHistoryStatus" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <html:hidden property="deviceId"/>
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;状态&nbsp;
                    <html:select property="state" >
                        <html:option value="-1">-----请选择-----</html:option>
                        <html:option value="0">up</html:option>
                        <html:option value="1">down</html:option>
                        <html:option value="2">unreachable</html:option>
                    </html:select>
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
                    <input name="back" type="button" class="button_nor" onclick="goBack();" value="返  回">
                </td>
                <td class="listr4">
                    <select name="pageSize" onchange="changePageSize('monitorTermdeviceHistoryStatusForm')">
                        <option value="50" <c:if test="${'50' == pageSize}">selected="selected"</c:if>>50</option>
                        <option value="100" <c:if test="${'100' == pageSize}">selected="selected"</c:if>>100</option>
                        <option value="200" <c:if test="${'200' == pageSize}">selected="selected"</c:if>>200</option>
                    </select>
                </td>
            </tr>
        </table>
    </html:form>
    <display:table name="monitorTermdevchecks" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="termdeviceHistoryStatus.do?method=viewTermdeviceHistoryStatus" form="monitorTermdeviceHistoryStatusForm">
        <display:column property="state"  title="状态" style="width:5%;" decorator="termdeviceStatusDecorator"/>
        <display:column property="startTime" title="开始时间" style="width:8%;" decorator="dateDecorator"/>
        <display:column property="endTime"  title="结束时间" style="width:8%;"  decorator="dateDecorator"/>
        <display:column property="duration"  title="持续时间" style="width:8%;" />
        <display:column property="output" title="状态信息" style="width:10%;white-space: nowrap;cursor:hand;" maxLength="40"/>
        <display:setProperty name="export.decorated" value="true"/>
    </display:table>
</div>
</body>
</html>
