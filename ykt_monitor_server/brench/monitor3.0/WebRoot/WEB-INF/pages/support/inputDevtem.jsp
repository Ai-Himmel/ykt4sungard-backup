<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
    <script type="text/javascript">
        function submitForm() {
            var editForm = document.forms[0];
            var url = "tdevice.do?method=addMonitorDevtem";

            new Ajax.Request(url,
            {
                method:'post',
                parameters: Form.serialize(document.forms[0]),
                onSuccess: function(result) {
                    alert(result.responseText);
                    if (result.responseText.indexOf("error:") != 0) {
                        window.close();
                        window.opener.document.forms[0].submit();
                    }
                }
            });
        }
    </script>
</head>
<body>
<form action="tdevice.do?method=addMonitorDevtem" method="post">
<input type="hidden" name="monitorDevtem.deviceid" value="<bean:write  name="deviceid"/>">
    <div style="width:100%;margin:8px 8px 0 10">
        <html:errors  property="addMonitorDevtem"/>
        <table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor="#FFFFFF">
            <tbody>
            <tr class="toptitle">
                <td colspan="2" style="text-align:left"><p style="font-weight:bold;">分配设备模板</p></td>
            </tr>
            <tr>
                <td class="td_title">设备名称：</td>
                <td class="td_value">
                    <bean:write  name="devicename"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">模板：</td>
                <td class="td_value">
                    <select name="monitorDevtem.templateid">
                        <option value="">-------请选择-------</option>
                        <c:forEach var="template" items="${templateList}">
                            <c:choose>
                                <c:when test="${template.templateId==templateId}">
                                    <option value="<c:out value="${template.templateId}" />" selected="selected"><c:out value="${template.templateName}" /></option>
                                </c:when>
                                <c:otherwise>
                                    <option value="<c:out value="${template.templateId}" />"><c:out value="${template.templateName}" /></option>
                                </c:otherwise>
                            </c:choose>
                        </c:forEach>
                    </select>
                </td>
            </tr>
            <tr>
                <td colspan="2"  align="center">
                    &nbsp;&nbsp;
                    <input type="button" class="button_nor" onclick="javascript:submitForm();" value=" 保 存 " />
                    <input  type="button" class="button_nor" value=" 关 闭 " onclick="window.close();">
                </td>
            </tr>
            </tbody>
        </table>
    </div>
</form>
</body>

</html>
