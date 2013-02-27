<%@page pageEncoding="UTF-8" %>
<jsp:useBean id="now" class="java.util.Date" />
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
        function flushCallback(pe){
            document.forms[0].submit();
            pe.stop();
        }
        function initTimer(){
            new PeriodicalExecuter(flushCallback,60);
        }
        function renderRow(row) {
            switch (row.cells[2].innerText) {
                case "up":
                    break;
                case "down":
                    row.style.background= "#FE3E00";
                    break;
                case "unreachable":
                    row.style.background= "#F9A810";
                    break;
                case "pending":
                    break;
            }
        }
        window.onload = function(){
            initTimer();
            //initEvent('row');
            renderTable('row');
        }
    </script>
</head>
<body>
<div style="width:100%;margin:8px 8px 0 10">
    <table width="100%" cellpadding="0" cellspacing="0" style="border:0" >
        <tr align="left">
            <td width="35%" align="left">
                <table class="search" style="border:0">
                    <tr class="toptitle">
                        <td width="100%">
                           一卡通运行情况
                        </td>
                    </tr>
                    <tr class="toptitle1">
                        <td width="100%" height="50" style="text-align:left;">
                                最新更新：<fmt:setLocale value="en"/><fmt:formatDate value="${now}" type="both" dateStyle="long" pattern="EEE yyyy-MM-dd HH:mm:ss" /><br>
                                更新间隔：60 秒
                        </td>
                    </tr>
                </table>
            </td>
            <td width="35%" align="left">
                <table class="search">
                    <tr class="toptitle"><td colspan="4">主机状态统计</td></tr>
                    <tr class="toptitle0">
                        <c:forEach var="count" items="${result}">
                            <td width="25%" style="text-align:center;"><c:out value="${count[0]}"></c:out></td>
                        </c:forEach>
                    </tr>
                    <tr class="toptitle1">
                        <c:forEach var="count" items="${result}">
                            <c:choose>
                                <c:when test="${count[1]=='0'}">
                                    <td style="text-align:center;"><c:out value="${count[1]}"></c:out></td>
                                </c:when>
                                <c:when test="${count[0]=='down'}">
                                    <td bgcolor="#FE3E00" style="text-align:center;"><c:out value="${count[1]}"></c:out></td>
                                </c:when>
                                <c:when test="${count[0]=='unreachable'}">
                                    <td bgcolor="#F9A810" style="text-align:center;"><c:out value="${count[1]}"></c:out></td>
                                </c:when>
                                <c:otherwise>
                                    <td style="text-align:center;"><c:out value="${count[1]}"></c:out></td>
                                </c:otherwise>
                            </c:choose>
                        </c:forEach>
                    </tr>
                </table>
            </td>
            <td width="30%"></td>
        </tr>
    </table>
    <html:form action="hostStatus.do?method=listMonitorHostStatus" method="post">
        <input type="hidden" name="page"  value="<c:out value='${currentPage}'/>"/>
        <input type="hidden" name="searchid"/>
        <input type="hidden" name="sort" value="<c:out value='${sort}'/>"/>
        <input type="hidden" name="dir" value="<c:out value='${dir}'/>"/>
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;主机&nbsp;<html:text property="displayName" styleClass="input_box" maxlength="50"/>
                    &nbsp;主机地址&nbsp;<html:text property="hostAddress" styleClass="input_box" maxlength="50"/>
                    &nbsp;状态&nbsp;
                    <html:select property="currentState" >
                        <html:option value="-1">-----请选择-----</html:option>
                        <html:option value="0">up</html:option>
                        <html:option value="1">down</html:option>
                        <html:option value="2">unreachable</html:option>
                        <html:option value="3">pending</html:option>
                    </html:select>
                    &nbsp;主机组&nbsp;
                    <html:select property="hostgroupId">
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorHostgroups" property="hostgroupId" labelProperty="groupName"/>
                    </html:select>
                    &nbsp;<input name="query" type="button" onclick="changePageSize('monitorHostStatusForm')" class="button_nor" value="查  询">
                </td>  
                <td class="listr4">
                    <select name="pageSize" onchange="changePageSize('monitorHostStatusForm')">
                        <option value="50" <c:if test="${'50' == pageSize}">selected="selected"</c:if>>50</option>
                        <option value="100" <c:if test="${'100' == pageSize}">selected="selected"</c:if>>100</option>
                        <option value="200" <c:if test="${'200' == pageSize}">selected="selected"</c:if>>200</option>
                    </select>
                </td>
            </tr>
        </table>
    </html:form>
    <display:table name="hostStatusList" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="hostStatus.do?method=listMonitorHostStatus" form="monitorHostStatusForm">
        <display:column property="displayName"  title="主机" style="width:8%;" media="html" href="hostStatus.do?method=viewMonitorHostStatus" paramId="hostId" paramProperty="hostId" sortable="true" sortProperty="h.displayName"/>
        <display:column property="displayName" title="主机" style="width:8%;" media="excel" />
        <display:column property="hostAddress"  title="主机地址" style="width:8%;" sortable="true" sortProperty="h.hostAddress"/>
        <display:column property="currentState" title="状态" style="width:5%;" decorator="hostStatusDecorator" sortable="true" sortProperty="s.currentState" defaultorder="descending"/>
        <display:column property="lastCheck" title="上次检查" style="width:8%;" decorator="dateDecorator" sortable="true" sortProperty="s.lastCheck"/>
        <display:column property="lastStateChange" title="持续时间" style="width:8%;" decorator="dateIntervalDecorator" sortable="true" sortProperty="s.lastStateChange"/>
        <display:column property="output" title="状态信息" style="width:17%;white-space: nowrap;cursor:hand" maxLength="45"/>
        <display:setProperty name="export.decorated" value="true"/>
    </display:table>
</div>
</body>
</html>
