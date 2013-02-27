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

    <script type="text/javascript">
        function oper(url, id, type) {
            if (id != null) {
                url = url + "&id=" + id;
            }
            if('delete'==type){
                if (confirm("您确定要删除该主机服务吗？")) {
                    del(url,document.forms[0]);
                }
            } else {
                window.location.href = url;
            }
        }
    </script>
</head>
<body onload="initEvent('row')">
<div style="width:100%;margin:8px 8px 0 10">
    <html:form action="hostservice.do?method=listMonitorService" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;主机名称&nbsp;<html:text property="monitorService.monitorHost.alias" styleClass="input_box" maxlength="30"/>
                    &nbsp;服务名称&nbsp;<html:text property="monitorService.serviceName" styleClass="input_box" maxlength="30"/>
                    &nbsp;检查命令&nbsp;<html:text property="monitorService.checkCommand.commandName" styleClass="input_box" maxlength="30"/>
                    &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                    &nbsp;<input name="add" type="button" class="button_nor" value="添  加" onclick="javascript:oper('hostservice.do?method=inputMonitorService',null,'save');">
                </td>
                <td class="listr4">
                    <select name="pageSize" onchange="changePageSize('monitorServiceForm')">
                        <option value="50" <c:if test="${'50' == pageSize}">selected="selected"</c:if>>50</option>
                        <option value="100" <c:if test="${'100' == pageSize}">selected="selected"</c:if>>100</option>
                        <option value="200" <c:if test="${'200' == pageSize}">selected="selected"</c:if>>200</option>
                    </select>
                </td>
            </tr>
        </table>
    </html:form>
    <display:table name="hostserviceList" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="hostservice.do?method=listMonitorService" form="monitorServiceForm">
        <display:column property="monitorHost.alias" title="主机名称" style="width:10%;"/>
        <display:column property="serviceName" title="服务名称" style="width:10%;" href="hostservice.do?method=viewMonitorService" paramId="id" paramProperty="serviceId"/>
        <display:column property="checkCommand.commandName" title="检查命令" style="width:10%;"/>
        <display:column title="操作" style="width:5%;" media="html">
            <a href="javascript:oper('hostservice.do?method=editMonitorService','<c:out value="${row.serviceId}"/>','update');">修改</a>/
            <a href="javascript:oper('hostservice.do?method=deleteMonitorService','<c:out value="${row.serviceId}"/>','delete');">删除</a>
        </display:column>
    </display:table>
</div>
</body>

</html>
