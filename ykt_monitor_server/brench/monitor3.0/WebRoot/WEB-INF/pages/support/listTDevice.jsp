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
    <script type="text/javascript" src="<c:url value="/pages/scripts/render.js"/>" ></script>

    <script type="text/javascript">
        function oper(url, id, type) {
            if (id != null) {
                url = url + "&deviceid=" + id;
            }
            window.open (url, "", "height=150, width=450, scrollbars=no, resizable=no,top=300,left=400");
        }
        window.onload = function(){
            initEvent('row');
            //mergeTable('row',0);
        }
    </script>
</head>
<body>
<div style="width:100%;margin:8px 8px 0 10">
    <html:form action="tdevice.do?method=listTDevice" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;父设备名称&nbsp;<html:text property="fdeviceName" styleClass="input_box" maxlength="50"/>
                    &nbsp;设备名称&nbsp;<html:text property="deviceName" styleClass="input_box" maxlength="50"/>
                    &nbsp;类型&nbsp;
                    <html:select property="devtypecode" >
                        <html:option value="">-------请选择-------</html:option>
                        <html:options collection="deviceType" property="key" labelProperty="value"/>
                    </html:select>
                    &nbsp;模板&nbsp;
                    <html:select property="templateId" >
                        <html:option value="">-------请选择-------</html:option>
                        <html:options collection="templateList" property="templateId" labelProperty="templateName"/>
                    </html:select>
                    &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                </td>
                <td class="listr4">
                    <select name="pageSize" onchange="changePageSize('monitorDevtemForm')">
                        <option value="50" <c:if test="${'50' == pageSize}">selected="selected"</c:if>>50</option>
                        <option value="100" <c:if test="${'100' == pageSize}">selected="selected"</c:if>>100</option>
                        <option value="200" <c:if test="${'200' == pageSize}">selected="selected"</c:if>>200</option>
                    </select>
                </td>
            </tr>
        </table>
    </html:form>
    <display:table name="tdeviceList" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="tdevice.do?method=listTDevice" form="monitorDevtemForm">
        <display:column property="fdevicename" title="父设备" style="width:10%;"/>
        <display:column property="devicename" title="名称" style="width:10%;"/>
        <display:column property="dictcaption" title="类型" style="width:10%;"/>
        <display:column property="templateName" title="模板" style="width:10%;"/>
        <display:column title="操作" style="width:5%;" media="html">
            <a href="javascript:oper('tdevice.do?method=editMonitorDevtem','<c:out value="${row.deviceid}"/>','');">修改模板</a>
        </display:column>
        <display:setProperty name="export.decorated" value="true"/>
    </display:table>
</div>
</body>

</html>
