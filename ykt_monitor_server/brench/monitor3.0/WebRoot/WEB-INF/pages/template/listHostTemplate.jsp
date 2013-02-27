<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link rel="stylesheet" type="text/css" href="<c:url value="/pages/displaytag/css/screen.css"/>"/>
    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
    <script type="text/javascript" src="<c:url value="/pages/scripts/global.js"/>" ></script>
    <script type="text/javascript" src="<c:url value="/pages/scripts/grid.js"/>" ></script>

    <script type="text/javascript">
        function oper(url, id, type) {
            if (id != null) {
                url = url + "&templateId=" + id;
            }
            if('delete'==type){
                if (confirm("您确定要删除该主机模板吗？")) {
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
    <html:form action="hostTemplate.do?method=listMonitorHostTemplate" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
            <tr>
                <td class="listr3">
                    &nbsp;模板名称&nbsp;<html:text property="monitorHostTemplate.templateName" styleClass="input_box"maxlength="30"/>
                    &nbsp;主机组&nbsp;
                    <html:select property="monitorHostTemplate.hostgroups.hostgroupId">
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorHostgroups" property="hostgroupId" labelProperty="groupName"/>
                    </html:select>
                    &nbsp;联系人组&nbsp;
                    <html:select property="monitorHostTemplate.contactGroups.contactgroupId" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorContactgroups" property="contactgroupId" labelProperty="contactgroupName"/>
                    </html:select>
                    &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                    &nbsp;<input name="add" type="button" class="button_nor" value="添  加" onclick="javascript:oper('hostTemplate.do?method=inputMonitorHostTemplate',null,'save');">
                </td>
            </tr>
        </table>
    </html:form>
    <display:table name="hostTemplates" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="hostTemplate.do?method=listMonitorHostTemplate" form="monitorHostTemplateForm">
        <display:column property="templateName" title="模板名称" style="width:10%;"
                        href="hostTemplate.do?method=viewMonitorHostTemplate" paramId="templateId"
                        paramProperty="templateId"/>
        <display:column property="checkCommand.commandName" title="检查命令" style="width:10%;"/>
        <display:column property="hostgroups.groupName" title="主机组" style="width:10%;"/>
        <display:column property="contactGroups.contactgroupName" title="联系人组" style="width:10%;"/>
        <display:column title="操作" style="width:5%;" media="html">
            <a href="javascript:oper('hostTemplate.do?method=editMonitorHostTemplate','<c:out value="${row.templateId}"/>','update');">修改</a>/
            <a href="javascript:oper('hostTemplate.do?method=deleteMonitorHostTemplate','<c:out value="${row.templateId}"/>','delete');">删除</a>
        </display:column>
    </display:table>
</div>
</body>

</html>
