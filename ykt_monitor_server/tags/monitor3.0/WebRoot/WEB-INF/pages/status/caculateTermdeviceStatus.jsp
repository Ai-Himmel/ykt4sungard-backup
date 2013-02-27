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
        String.prototype.Trim = function() {
            return this.replace(/(^\s*)|(\s*$)/g, ""); 
        }
        function renderRow(row) {
            var down = row.cells[3].innerText.Trim();
            var unreachable = row.cells[4].innerText.Trim();
            if("0"!=down){
                row.cells[3].bgColor = "#FE3E00";
            }
            if("0"!=unreachable){
                row.cells[4].bgColor = "#F9A810";
            }
        }
        window.onload = function(){
            renderTable('row');
        }
    </script>
</head>
<body>
<div style="width:100%;margin:8px 8px 0 10">
    <html:form action="termdeviceStatus.do?method=caculateDeviceStatus" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;
                </td>
                <td class="listr4">
                </td>
            </tr>
        </table>                                                            
    </html:form>
    <display:table name="result" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="termdeviceStatus.do?method=caculateDeviceStatus" form="monitorTermdeviceStatusForm">
        <display:column title="类型" style="width:25%;">
            <c:choose>
                <c:when test="${row.name!=''}">
                    <c:out value="${row.caption}"/>
                </c:when>
                <c:otherwise>
                    <a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus&isLeaf=1&devtypecode=<c:out value="${row.code}"/>"><c:out value="${row.caption}"/></a>
                </c:otherwise>
            </c:choose>

        </display:column>
        <display:column title="设备" style="width:30%;">
            <a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus&fdeviceid=<c:out value="${row.id}"/>"><c:out value="${row.name}"/></a>
        </display:column>
        <display:column title="up" style="width:15%;">
            <c:choose>
                <c:when test="${row.up!=0 && row.name!=''}">
                    <a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus&currentState=0&fdeviceid=<c:out value="${row.id}"/>"><c:out value="${row.up}"/></a>
                </c:when>
                <c:when test="${row.up!=0 && row.name==''}">
                    <a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus&isLeaf=1&currentState=0&devtypecode=<c:out value="${row.code}"/>"><c:out value="${row.up}"/></a>
                </c:when>
                <c:otherwise><c:out value="${row.up}"/></c:otherwise>
            </c:choose>
        </display:column>
        <display:column title="down" style="width:15%;" >
            <c:choose>
                <c:when test="${row.down!=0 && row.name!=''}">
                    <a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus&currentState=1&fdeviceid=<c:out value="${row.id}"/>"><c:out value="${row.down}"/></a>
                </c:when>
                <c:when test="${row.down!=0 && row.name==''}">
                    <a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus&isLeaf=1&currentState=1&devtypecode=<c:out value="${row.code}"/>"><c:out value="${row.down}"/></a>
                </c:when>
                <c:otherwise><c:out value="${row.down}"/></c:otherwise>
            </c:choose>
        </display:column>
        <display:column title="unreachable" style="width:15%;" >
            <c:choose>
                <c:when test="${row.unreachable!=0 && row.name!=''}">
                    <a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus&currentState=2&fdeviceid=<c:out value="${row.id}"/>"><c:out value="${row.unreachable}"/></a>
                </c:when>
                <c:when test="${row.unreachable!=0 && row.name==''}">
                    <a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus&isLeaf=1&currentState=2&devtypecode=<c:out value="${row.code}"/>"><c:out value="${row.unreachable}"/></a>
                </c:when>
                <c:otherwise><c:out value="${row.unreachable}"/></c:otherwise>
            </c:choose>
        </display:column>
        <display:setProperty name="export.decorated" value="false"/>
    </display:table>
</div>
</body>
</html>
