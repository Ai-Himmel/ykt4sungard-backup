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
</head>
<body onload="initEvent('row')">
<div style="width:100%;margin:8px 8px 0 10">
    <html:form action="deviceGroup.do?method=listMonitorTopoDeviceGroup" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <input type="hidden" name="d-16544-o" />
        <input type="hidden" name="d-16544-s" />
        <input type="hidden" name="d-16544-p" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
                <tr>
                    <td class="listr3">
                        &nbsp;设备名称&nbsp;<html:text property="devicename" styleClass="input_box" maxlength="30"/>
                        &nbsp;组别名称&nbsp;<html:text property="devicegroupname" styleClass="input_box" maxlength="30"/>
                        &nbsp;校区&nbsp;<html:text property="locationname" styleClass="input_box" maxlength="30"/>
                        &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                    </td>
                </tr>
        </table>
    </html:form>
    <display:table name="deviceGroupList" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="" form="monitorDeviceGroupForm">
        <display:column property="devicename" title="设备名称" style="width:25%;" sortable="true" sortProperty="devicename"/>
        <display:column property="dictcaption" title="设备类型" style="width:25%;" sortable="true"/>
        <display:column property="devicegroupname" title="组别名称" style="width:25%;" sortable="true"/>
        <display:column property="locationname" title="校区" style="width:25%;" sortable="true"/>
    </display:table>
</div>
</body>

</html>
