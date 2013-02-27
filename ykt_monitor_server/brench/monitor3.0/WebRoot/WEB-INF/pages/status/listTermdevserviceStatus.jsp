<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link rel="stylesheet" type="text/css" href="<c:url value="/pages/displaytag/css/screen.css"/>"/>
    <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>

</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

<div id="titleDiv" class="pageTitle">
    <strong> <font class="medium"> 设备服务状态信息 </font> </strong>
</div>
<html:form action="termdevserviceStatus.do?method=listMonitorTermdevserviceStatus" method="post">
    <input type="hidden" name="page" />
    <input type="hidden" name="searchid" />
    <div id="filterDiv" style="width:100%">
        <tr>
            <td>
                &nbsp;设备服务
                <aa:zone name="devserviceId">
                    <html:text property="monitorTermdevserviceStatus.devserviceId" styleClass="input_box" maxlength="30"/>
                </aa:zone>
                &nbsp;状态
                <aa:zone name="currentState">
                    <html:select property="monitorTermdevserviceStatus.currentState" >
                        <html:option value="-1">-----请选择-----</html:option>
                        <html:option value="0">ok</html:option>
                        <html:option value="1">warning</html:option>
                        <html:option value="2">critical</html:option>
                    </html:select>
                </aa:zone>
            </td>
            <td>
                <input name="query" type="submit" class="submitButton" value="查  询">
            </td>
        </tr>
    </div>
 </html:form>
    <div id="countDiv" style="width:40%" align="center">
        <table border="1">
            <tr bgcolor="#9999ff">
                <c:forEach var="count" items="${result}">
                    <td width="25%" align="center"><c:out value="${count[0]}"></c:out></td>
                </c:forEach>
            </tr>
            <tr>
                <c:forEach var="count" items="${result}">
                    <td align="center"><c:out value="${count[1]}"></c:out></td>
                </c:forEach>
            </tr>
        </table>
    </div>
    <div id="tableDiv" align="center" style="width:100%">
        <display:table name="termdevserviceStatusList" class="isis" export="true" id="row"
                       requestURI="termdevserviceStatus.do?method=listMonitorTermdevserviceStatus" form="monitorTermdevserviceStatusForm">
            <display:column property="devserviceId" title="设备服务" style="width:5%;text-align:center;font-size:14" />
            <display:column property="currentState" title="状态" style="width:5%;text-align:center;font-size:14" decorator="termdevserviceStatusDecorator"/>
            <display:column property="lastCheck" title="上次检查" style="width:10%;text-align:center;font-size:14" decorator="dateDecorator" />
            <display:column property="lastStateChange" title="持续时间" style="width:10%;text-align:center;font-size:14"/>
            <display:column property="output" title="状态信息" style="width:20%;text-align:center;font-size:14"/>
        </display:table>
    </div>
</body>
</html>
