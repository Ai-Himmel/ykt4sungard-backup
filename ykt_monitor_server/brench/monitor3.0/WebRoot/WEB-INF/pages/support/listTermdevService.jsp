<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link rel="stylesheet" type="text/css" href="<c:url value="/pages/displaytag/css/screen.css"/>"/>
    <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>

    <script type="text/javascript">
        function oper(url, id, type) {
            if (id != null) {
                url = url + "&id=" + id;
            }
            window.location.href = url;
        }
    </script>
</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

<div id="titleDiv" class="pageTitle">
    <strong> <font class="medium"> 设备服务管理 </font> </strong>
</div>
<html:form action="termdevService.do?method=listMonitorTermdevService" method="post">
    <input type="hidden" name="page" />
    <input type="hidden" name="searchid" />
    <div id="filterDiv" style="width:100%">
        <tr>
            <td>
                &nbsp;设备服务名称
                <aa:zone name="devserviceName">
                    <html:text property="monitorTermdevService.devserviceName" styleClass="input_box" maxlength="30"/>
                </aa:zone>
                &nbsp;检查命令
                <aa:zone name="checkCommand.commandName">
                    <html:text property="monitorTermdevService.checkCommand.commandName" styleClass="input_box" maxlength="30"/>
                </aa:zone>
            </td>
            <td>
                <input name="query" type="submit" class="submitButton" value="查  询">
            </td>
            <td>
                <input name="add" type="button" class="submitButton" value="添  加"
                       onclick="javascript:oper('termdevService.do?method=inputMonitorTermdevService',null,'save');">
            </td>
        </tr>
    </div>
</html:form>
    <div id="tableDiv" align="center" style="width:100%">
        <display:table name="termdevServiceList" class="isis" export="true" id="row"
                       requestURI="termdevService.do?method=listMonitorTermdevService" form="monitorTermdevServiceForm">
            <display:column property="deviceId" title="设备" style="width:10%;text-align:center"/>
            <display:column property="devserviceName" title="名称" style="width:10%;text-align:center" href="termdevService.do?method=viewMonitorTermdevService" paramId="id" paramProperty="devserviceId"/>
            <display:column property="checkCommand.commandName" title="检查命令" style="width:10%;text-align:center"/>
            <display:column title="操作" style="width:5%;text-align:center" media="html">
                <a href="javascript:oper('termdevService.do?method=editMonitorTermdevService','<c:out value="${row.devserviceId}"/>','update');">修改</a>/
                <a href="javascript:oper('termdevService.do?method=deleteMonitorTermdevService','<c:out value="${row.devserviceId}"/>','delete');">删除</a>
            </display:column>
        </display:table>
    </div>

</body>

</html>
