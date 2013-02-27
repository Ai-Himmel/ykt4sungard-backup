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
                url = url + "&deviceGroupId=" + id;
            }
            if('delete'==type){
                if (confirm("您确定要删除该组别吗？")) {
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
    <html:form action="group.do?method=listMonitorTopoGroup" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <input type="hidden" name="d-16544-o" />
        <input type="hidden" name="d-16544-s" />
        <input type="hidden" name="d-16544-p" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
                <tr>
                    <td class="listr3">
                        &nbsp;组别名称&nbsp;<html:text property="monitorTopoGroup.devicegroupname" styleClass="input_box" maxlength="30"/>
                        &nbsp;校区&nbsp;
                        <html:select property="monitorTopoGroup.location.locationid" >
                            <html:option value="">-----------请选择-----------</html:option>
                            <html:options collection="locations" property="locationid" labelProperty="locationname"/>
                        </html:select>
                        &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                        &nbsp;<input name="add" type="button" class="button_nor" value="添  加" onclick="javascript:oper('group.do?method=inputMonitorTopoGroup',null,'save');">
                    </td>
                </tr>
        </table>
    </html:form>
    <display:table name="groupList" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="" form="monitorTopoGroupForm">
        <display:column property="devicegroupname" title="组别名称" style="width:35%;" href="group.do?method=viewMonitorTopoGroup" paramId="deviceGroupId" paramProperty="devicegroupid" sortable="true"/>
        <display:column property="groupwidth" title="宽度" style="width:10%;" sortable="true"/>
        <display:column property="groupheight" title="高度" style="width:10%;" sortable="true"/>
        <display:column property="groupxindex" title="水平索引" style="width:10%;" sortable="true"/>
        <display:column property="groupyindex" title="垂直索引" style="width:10%;" sortable="true"/>
        <display:column property="location.locationname" title="校区" style="width:15%;" sortable="true"/>
        <display:column title="操作" style="width:10%;" media="html">
            <a href="javascript:oper('group.do?method=editMonitorTopoGroup','<c:out value="${row.devicegroupid}"/>','update');">修改</a>/
            <a href="javascript:oper('group.do?method=deleteMonitorTopoGroup','<c:out value="${row.devicegroupid}"/>','delete');">删除</a>
        </display:column>
    </display:table>
</div>
</body>

</html>
