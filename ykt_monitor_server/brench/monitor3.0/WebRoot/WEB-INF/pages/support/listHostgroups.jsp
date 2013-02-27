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
                url = url + "&groupId=" + id;
            }
            if(type=="delete"){
                if (confirm("您确定要删除该主机组吗？")) {
                    del(url,document.forms[0]);
                }
            } else {
                window.open (url, "", "height=150, width=450, scrollbars=no, resizable=no,top=300,left=400");
            }
        }
    </script>
</head>
<body onload="initEvent('row')">
<div style="width:100%;margin:8px 8px 0 10">
    <html:form action="hostgroups.do?method=listMonitorHostgroups" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;主机组名称&nbsp;<html:text property="monitorHostgroups.groupName" styleClass="input_box" maxlength="30"/>
                    &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                    &nbsp;<input name="add" type="button" class="button_nor" value="添  加" onclick="javascript:oper('hostgroups.do?method=inputMonitorHostgroups',null,'save');">
                </td>
            </tr>
         </table>
    </html:form>
    <display:table name="groupList" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="hostgroups.do?method=listMonitorHostgroups" form="monitorHostgroupsForm">
        <display:column property="hostgroupId" title="ID" style="width:10%;"/>
        <display:column property="groupName" title="组名" style="width:10%;"/>
        <display:column title="操作" style="width:5%;" media="html">
            <a href="javascript:oper('hostgroups.do?method=editMonitorHostgroups','<c:out value="${row.hostgroupId}"/>','update');">修改</a>/
            <a href="javascript:oper('hostgroups.do?method=deleteMonitorHostgroups','<c:out value="${row.hostgroupId}"/>','delete');">删除</a>
        </display:column>
    </display:table>
</div>
</body>

</html>
