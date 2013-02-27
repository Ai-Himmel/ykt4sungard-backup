<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link rel="stylesheet" type="text/css" href="<c:url value="/pages/displaytag/css/screen.css"/>"/>
    <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
    <link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>

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
    <strong> <font class="medium"> 运行变量管理 </font> </strong>
</div>
<html:form action="runtimevariables.do?method=listMonitorRuntimevariables" method="post">
    <input type="hidden" name="page" />
    <input type="hidden" name="searchid" />
    <div id="filterDiv" style="width:100%">
        <tr>
            <td>
                &nbsp;变量名称
                <aa:zone name="varname">
                    <html:text property="monitorRuntimevariables.varname" styleClass="input_box" maxlength="30"/>
                </aa:zone>
            </td>
            <td>
                <input name="query" type="submit" class="submitButton" value="查  询">
            </td>
            <td>
                <input name="add" type="button" class="submitButton" value="添  加"
                       onclick="javascript:oper('runtimevariables.do?method=inputMonitorRuntimevariables',null,'save');">
            </td>
        </tr>
    </div>
</html:form>
    <div id="tableDiv" align="center" style="width:100%">
        <display:table name="runtimevariablesList" class="isis" export="true" id="row"
                       requestURI="runtimevariables.do?method=listMonitorRuntimevariables"
                        form="monitorRuntimevariablesForm">
            <display:column property="varname" title="变量名称" style="width:10%;text-align:center"  href="runtimevariables.do?method=viewMonitorRuntimevariables" paramId="id" paramProperty="runtimevariableId"/>
            <display:column property="varnameZh" title="变量中文名" style="width:10%;text-align:center"/>
            <display:column property="varvalue" title="变量值" style="width:10%;text-align:center"/>
            <display:column title="操作" style="width:5%;text-align:center" media="html">
                <a href="javascript:oper('runtimevariables.do?method=editMonitorRuntimevariables','<c:out value="${row.runtimevariableId}"/>','update');">修改</a>/
                <a href="javascript:oper('runtimevariables.do?method=deleteMonitorRuntimevariables','<c:out value="${row.runtimevariableId}"/>','delete');">删除</a>
            </display:column>
        </display:table>
    </div>

</body>

</html>
