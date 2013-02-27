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
                url = url + "&id=" + id;
            }
            if('delete'==type){
                if (confirm("您确定要删除该联系人吗？")) {
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
    <html:form action="contact.do?method=listMonitorContact" method="post">
        <input type="hidden" name="page" />
        <input type="hidden" name="searchid" />
        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="search">
                <tr>
                    <td class="listr3">
                        &nbsp;联系人名称&nbsp;<html:text property="monitorContact.contactName" styleClass="input_box" maxlength="50"/>
                        &nbsp;<input name="query" type="submit" class="button_nor" value="查  询">
                        &nbsp;<input name="add" type="button" class="button_nor" value="添  加" onclick="javascript:oper('contact.do?method=inputMonitorContact',null,'save');">
                    </td>
                </tr>
        </table>
    </html:form>
    <display:table name="contactList" class="monitor" export="true" id="row" cellpadding="1" cellspacing="1"
                   requestURI="contact.do?method=listMonitorContact" form="monitorContactForm">
        <display:column property="contactName" title="联系人名称" style="width:10%;" href="contact.do?method=viewMonitorContact" paramId="id" paramProperty="contactId"/>
        <display:column property="emailAddress" title="邮箱" style="width:10%;"/>
        <display:column property="cellphone" title="手机号" style="width:10%;"/>
        <display:column title="操作" style="width:5%;" media="html">
            <a href="javascript:oper('contact.do?method=editMonitorContact','<c:out value="${row.contactId}"/>','update');">修改</a>/
            <a href="javascript:oper('contact.do?method=deleteMonitorContact','<c:out value="${row.contactId}"/>','delete');">删除</a>
        </display:column>
    </display:table>
</div>
</body>

</html>
