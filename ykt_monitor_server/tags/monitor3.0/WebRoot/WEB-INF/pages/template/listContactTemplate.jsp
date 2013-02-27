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
                url = url + "&templateId=" + id;
            }
            window.location.href = url;
        }
    </script>
</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

<div id="titleDiv" class="pageTitle">
    <strong> <font class="medium"> 联系人模板管理 </font> </strong>
</div>
<html:form action="contactTemplate.do?method=listMonitorContactTemplate" method="post">
    <input type="hidden" name="page" />
    <input type="hidden" name="searchid" />
    <div id="filterDiv" style="width:100%">
        <tr>
            <td>
                &nbsp;模板名称
                <aa:zone name="templateName">
                    <html:text property="monitorContactTemplate.templateName" styleClass="input_box" maxlength="30"/>
                </aa:zone>
                &nbsp;主机通知选项
                <aa:zone name="hostNotificationOptions">
                    <html:text property="monitorContactTemplate.hostNotificationOptions" styleClass="input_box" maxlength="30"/>
                </aa:zone>
                &nbsp;服务通知选项
                <aa:zone name="serviceNotificationOptions">
                    <html:text property="monitorContactTemplate.serviceNotificationOptions" styleClass="input_box" maxlength="30"/>
                </aa:zone>
            </td>
            <td>
                <input name="query" type="submit" class="submitButton" value="查  询">
            </td>
            <td>
                <input name="add" type="button" class="submitButton" value="添  加"
                       onclick="javascript:oper('contactTemplate.do?method=inputMonitorContactTemplate',null,'save');">
            </td>
        </tr>
    </div>
</html:form>
    <div id="tableDiv" align="center" style="width:100%">
        <display:table name="contactTemplates" class="isis" export="true" id="row"
                       requestURI="contactTemplate.do?method=listMonitorContactTemplate" form="monitorContactTemplateForm">
            <display:column property="templateName" title="模板名称" style="width:10%;text-align:center" href="contactTemplate.do?method=viewMonitorContactTemplate" paramId="templateId" paramProperty="templateId"/>
            <display:column property="hostNotificationOptions" title="主机通知选项" style="width:10%;text-align:center"/>
            <display:column property="serviceNotificationOptions" title="服务通知选项" style="width:10%;text-align:center"/>
            <display:column property="hostNotificationCommands" title="主机通知命令" style="width:10%;text-align:center"/>
            <display:column property="serviceNotificationCommands" title="服务通知命令" style="width:10%;text-align:center"/>
            <display:column title="操作" style="width:5%;text-align:center" media="html">
                <a href="javascript:oper('contactTemplate.do?method=editMonitorContactTemplate','<c:out value="${row.templateId}"/>','update');">修改</a>/
                <a href="javascript:oper('contactTemplate.do?method=deleteMonitorContactTemplate','<c:out value="${row.templateId}"/>','delete');">删除</a>
            </display:column>
        </display:table>
    </div>

</body>

</html>
