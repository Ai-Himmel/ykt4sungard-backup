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
            if("0.000%"!=row.cells[3].innerText){
                row.cells[3].bgColor = "#FE3E00";
            }
            if("0.000%"!=row.cells[4].innerText){
                row.cells[4].bgColor = "#F9A810";
            }
        }
        window.onload = function(){
            renderTable('row');
            //mergeTable('row',0);
        }
        function viewHistory(deviceId){
            var timePeriodId = document.getElementById("timePeriodId").value;
            window.location.href = "termdeviceHistoryStatus.do?method=viewTermdeviceHistoryStatus&deviceId=" + deviceId + "&timePeriodId=" + timePeriodId;
        }
        function viewChart(deviceId){
            var timePeriodId = document.getElementById("timePeriodId").value;
            window.location.href = "termdeviceHistoryStatus.do?method=viewTermdeviceHistoryChart&deviceId=" + deviceId + "&timePeriodId=" + timePeriodId;
        }
    </script>
</head>
<body>
<div style="width:100%;margin:8px 8px 0 10">
    <html:form action="termdeviceHistoryStatus.do?method=listTermdeviceHistoryStatus" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;父设备&nbsp;<html:text property="fdevicename" styleClass="input_box" maxlength="50"/>
                    &nbsp;设备&nbsp;<html:text property="devicename" styleClass="input_box" maxlength="50"/>
                    &nbsp;模板&nbsp;
                    <html:select property="templateId" >
                        <html:option value="">-------请选择-------</html:option>
                        <html:options collection="templateList" property="templateId" labelProperty="templateName"/>
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
    <display:table name="termdevHistoryStatus" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="termdeviceHistoryStatus.do?method=listTermdeviceHistoryStatus" form="monitorTermdeviceHistoryStatusForm">
        <display:column property="fdevicename"  title="父设备" style="width:5%;"/>
        <display:column title="设备" style="width:5%;" media="html">
            <a href="javascript:viewHistory('<c:out value="${row.deviceId}"/>');"><c:out value="${row.devicename}"/></a>
        </display:column>
        <display:column property="devicename"  title="设备" style="width:5%;" media="excel"/>
        <display:column property="up" title="up" style="width:5%;"/>
        <display:column property="down"  title="down" style="width:5%;" />
        <display:column property="unreachable" title="unreachable" style="width:5%;" />
        <display:column title="操作" style="width:5%;" media="html">
            <a href="javascript:viewChart('<c:out value="${row.deviceId}"/>');">趋势图</a>
        </display:column>
        <display:setProperty name="export.decorated" value="true"/>
    </display:table>
</div>
</body>
</html>
