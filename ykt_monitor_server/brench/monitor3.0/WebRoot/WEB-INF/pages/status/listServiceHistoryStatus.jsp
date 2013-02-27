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
                row.cells[3].bgColor = "#F9A810";
            }
            if("0.000%"!=row.cells[4].innerText){
                row.cells[4].bgColor = "#B1C9D3";
            }
            if("0.000%"!=row.cells[5].innerText){
                row.cells[5].bgColor = "#FE3E00";
            }
        }
        window.onload = function(){
            renderTable('row');
            //mergeTable('row',0);
        }
        function viewHistory(serviceId){
            var timePeriodId = document.getElementById("timePeriodId").value;
            window.location.href = "serviceHistoryStatus.do?method=viewServiceHistoryStatus&serviceId=" + serviceId + "&timePeriodId=" + timePeriodId;
        }
        function viewChart(serviceId){
            var timePeriodId = document.getElementById("timePeriodId").value;
            window.location.href = "serviceHistoryStatus.do?method=viewServiceHistoryChart&serviceId=" + serviceId + "&timePeriodId=" + timePeriodId;
        }
    </script>
</head>
<body>
<div style="width:100%;margin:8px 8px 0 10">
    <html:form action="serviceHistoryStatus.do?method=listServiceHistoryStatus" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;主机&nbsp;<html:text property="displayName" styleClass="input_box" maxlength="50"/>
                    &nbsp;服务&nbsp;<html:text property="serviceName" styleClass="input_box" maxlength="50"/>
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
                    <select name="pageSize" onchange="changePageSize('monitorServiceHistoryStatusForm')">
                        <option value="50" <c:if test="${'50' == pageSize}">selected="selected"</c:if>>50</option>
                        <option value="100" <c:if test="${'100' == pageSize}">selected="selected"</c:if>>100</option>
                        <option value="200" <c:if test="${'200' == pageSize}">selected="selected"</c:if>>200</option>
                    </select>
                </td>
            </tr>
        </table>
    </html:form>
    <display:table name="serviceHistoryStatus" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="serviceHistoryStatus.do?method=listServiceHistoryStatus" form="monitorServiceHistoryStatusForm">
        <display:column property="displayName"  title="主机" style="width:5%;"/>
        <display:column title="服务" style="width:5%;" media="html">
            <a href="javascript:viewHistory('<c:out value="${row.serviceId}"/>');"><c:out value="${row.serviceName}"/></a>
        </display:column>
        <display:column property="serviceName"  title="服务" style="width:5%;" media="excel"/>
        <display:column property="ok" title="ok" style="width:5%;"/>
        <display:column property="warning"  title="warning" style="width:5%;" />
        <display:column property="unknow" title="unknow" style="width:5%;" />
        <display:column property="critical" title="critical" style="width:5%;"/>
        <display:column property="pending" title="pending" style="width:5%;"/>
        <display:column title="操作" style="width:5%;" media="html">
            <a href="javascript:viewChart('<c:out value="${row.serviceId}"/>');">趋势图</a>
        </display:column>
        <display:setProperty name="export.decorated" value="true"/>
    </display:table>
</div>
</body>
</html>
