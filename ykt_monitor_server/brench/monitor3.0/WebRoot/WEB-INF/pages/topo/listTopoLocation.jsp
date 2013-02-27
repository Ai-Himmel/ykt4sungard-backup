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
                url = url + "&locationId=" + id;
            }
            if('delete'==type){
                if (confirm("您确定要删除该校区吗？")) {
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
    <html:form action="location.do?method=listMonitorTopoLocation" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <input type="hidden" name="d-16544-o" />
        <input type="hidden" name="d-16544-s" />
        <input type="hidden" name="d-16544-p" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
                <tr>
                    <td class="listr3">
                        &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                        &nbsp;<input name="add" type="button" class="button_nor" value="添  加" onclick="javascript:oper('location.do?method=inputMonitorTopoLocation',null,'save');">
                    </td>
                </tr>
        </table>
    </html:form>
    <display:table name="locationList" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="" form="monitorTopoLocationForm">
        <display:column property="locationname" title="校区名称" style="width:70%;" href="location.do?method=viewMonitorTopoLocation" paramId="locationId" paramProperty="locationid" sortable="true"/>
        <display:column property="locationindex" title="校区索引" style="width:20%;" sortable="true"/>
        <display:column title="操作" style="width:10%;" media="html">
            <a href="javascript:oper('location.do?method=editMonitorTopoLocation','<c:out value="${row.locationid}"/>','update');">修改</a>/
            <a href="javascript:oper('location.do?method=deleteMonitorTopoLocation','<c:out value="${row.locationid}"/>','delete');">删除</a>
        </display:column>
    </display:table>
</div>
</body>

</html>