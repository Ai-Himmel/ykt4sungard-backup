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
            if("0.000%"!=row.cells[2].innerText){
                row.cells[2].bgColor = "#FE3E00";
            }
            if("0.000%"!=row.cells[3].innerText){
                row.cells[3].bgColor = "#F9A810";
            }
        }
        window.onload = function(){
            //initEvent('row');
            renderTable('row');
        }
        function viewHistory(hostId){
            var timePeriodId = document.getElementById("timePeriodId").value;
            window.location.href = "hostHistoryStatus.do?method=viewHostHistoryStatus&hostId=" + hostId + "&timePeriodId=" + timePeriodId;
        }
        function viewChart(hostId){
            var timePeriodId = document.getElementById("timePeriodId").value;
            window.location.href = "hostHistoryStatus.do?method=viewHostHistoryChart&hostId=" + hostId + "&timePeriodId=" + timePeriodId;
        }
    </script>
</head>
<body>
<div style="width:100%;margin:8px 8px 0 10">
    <html:form action="hostHistoryStatus.do?method=listHostHistoryStatus" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;主机&nbsp;<html:text property="displayName" styleClass="input_box" maxlength="50"/>
                    &nbsp;主机组&nbsp;
                    <html:select property="hostgroupId">
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorHostgroups" property="hostgroupId" labelProperty="groupName"/>
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
                    <select name="pageSize" onchange="changePageSize('monitorHostHistoryStatusForm')">
                        <option value="50" <c:if test="${'50' == pageSize}">selected="selected"</c:if>>50</option>
                        <option value="100" <c:if test="${'100' == pageSize}">selected="selected"</c:if>>100</option>
                        <option value="200" <c:if test="${'200' == pageSize}">selected="selected"</c:if>>200</option>
                    </select>
                </td>
            </tr>
        </table>
    </html:form>
    <display:table name="hostHistoryStatus" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="hostHistoryStatus.do?method=listHostHistoryStatus" form="monitorHostHistoryStatusForm">
        <display:column title="主机" style="width:5%;" media="html">
            <a href="javascript:viewHistory('<c:out value="${row.hostId}"/>');"><c:out value="${row.displayName}"/></a>
        </display:column>
        <display:column property="displayName"  title="主机" style="width:5%;" media="excel"/>
        <display:column property="up" title="up" style="width:5%;"/>
        <display:column property="down"  title="down" style="width:5%;" />
        <display:column property="unreachable" title="unreachable" style="width:5%;" />
        <display:column property="pending" title="pending" style="width:5%;"/>
        <display:column title="操作" style="width:5%;" media="html">
            <a href="javascript:viewChart('<c:out value="${row.hostId}"/>');">趋势图</a>
        </display:column>
        <display:setProperty name="export.decorated" value="true"/>
    </display:table>
</div>
</body>
</html>
