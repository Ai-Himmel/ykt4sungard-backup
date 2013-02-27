<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <%--<html:javascript formName="monitorTopoLocationForm"/>--%>
    <script type="text/javascript">
        function submitForm(){
            var editForm = document.forms[0];
            /*if(!validateMonitorTopoLocationForm(editForm)){
                return false;
            }*/
            var type = document.getElementById("type").value;
            if(type=="edit"){
                editForm.action = "updateLocation.do?method=updateMonitorTopoLocation";
            } else if(type=="add"){
                editForm.action = "addLocation.do?method=addMonitorTopoLocation";
            }
            editForm.submit();
        }
    </script>
</head>
<body>
<html:form action="location.do?method=addMonitorTopoGroup" method="post">
<html:hidden property="monitorTopoLocation.locationid" />
<html:hidden property="type" />
    <div style="width:100%;margin:8px 8px 0 10">
        <%--<html:errors  property="addMonitorTopoLocation"/>--%>
        <html:errors/>
        <table width=100% border=1 cellpadding=1 cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
            <tbody>
            <tr class="toptitle">
                <td colspan="2" style="text-align:left"><p style="font-weight:bold;"><logic:equal name="monitorTopoLocationForm" property="type" value="edit">修改</logic:equal><logic:equal name="monitorTopoLocationForm" property="type" value="add">增加</logic:equal>校区</p></td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">校区名称：</span>
                <td class="td_value">
                    <html:text property="monitorTopoLocation.locationname" styleClass="input_box" maxlength="100"/>
                    <font color="#ff0000">*</font>
                </td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">校区索引：</span>
                <td class="td_value">
                    <html:text property="monitorTopoLocation.locationindex" styleClass="input_box" maxlength="100"/>
                </td>
            </tr>
            <tr>
                <td colspan="2"  align="center">
                    &nbsp;&nbsp;
                    <input type="button" class="button_nor" onclick="javascript:submitForm();" value=" 保 存 " />
                    <input type="reset" class="button_nor" value=" 重 置 " />
                    <input  type="button" class="button_nor" value=" 返 回 " onclick="history.back();">
                </td>
            </tr>
            </tbody>
        </table>
    </div>
</html:form>
</body>

</html>
