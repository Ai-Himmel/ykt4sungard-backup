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
        function selectAll(selectAll, name) {
            var array = document.getElementsByName('id');
            if (selectAll.checked) {
                for (var i = 0; i < array.length; i++) {
                    array[i].checked = true;
                }
            } else {
                for (var i = 0; i < array.length; i++) {
                    array[i].checked = false;
                }
            }
        }
        function oper(url, id, type) {
            if (id != null) {
                url = url + "&id=" + id;
            }
            if('delete'==type){
                if (confirm("您确定要删除该主机吗？")) {
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
    <html:form action="host.do?method=listMonitorHost" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;主机名称&nbsp;<html:text property="monitorHost.alias" styleClass="input_box" maxlength="30"/>
                    &nbsp;主机显示名&nbsp;<html:text property="monitorHost.displayName" styleClass="input_box" maxlength="30"/>
                    &nbsp;主机地址&nbsp;<html:text property="monitorHost.hostAddress" styleClass="input_box" maxlength="30"/>
                    &nbsp;主机组&nbsp;
                    <html:select property="monitorHost.hostgroups.hostgroupId">
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorHostgroups" property="hostgroupId" labelProperty="groupName"/>
                    </html:select>
                    &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                    &nbsp;<input name="add" type="button" class="button_nor" value="添  加" onclick="javascript:oper('host.do?method=inputMonitorHost',null,'save');">
                </td>
            </tr>
        </table>
     </html:form>
    <display:table name="hostList" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="host.do?method=listMonitorHost" form="monitorHostForm">
        <display:column property="alias" title="主机名称" style="width:15%;" href="host.do?method=viewMonitorHost" paramId="id" paramProperty="hostId"/>
        <display:column property="displayName" title="主机显示名" style="width:15%;"/>
        <display:column property="hostAddress" title="主机地址" style="width:15%;"/>
        <display:column property="checkCommand.commandName" title="检查命令" style="width:15%;"/>
        <display:column property="hostgroups.groupName" title="主机组" style="width:15%;"/>
        <display:column property="hostType" title="主机类型" style="width:15%;" decorator="hostTypeDecorator"/>
        <display:column title="操作" style="width:10%;" media="html">
            <a href="javascript:oper('host.do?method=editMonitorHost','<c:out value="${row.hostId}"/>','update');">修改</a>/
            <a href="javascript:oper('host.do?method=deleteMonitorHost','<c:out value="${row.hostId}"/>','delete');">删除</a>
        </display:column>
        <display:setProperty name="export.decorated" value="true"/>
    </display:table>
</div>
</body>

</html>
