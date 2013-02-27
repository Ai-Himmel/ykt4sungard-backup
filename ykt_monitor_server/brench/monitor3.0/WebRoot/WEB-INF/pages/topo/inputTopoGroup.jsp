<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <%--<html:javascript formName="monitorTopoGroupForm"/>--%>
    <script type="text/javascript">
        function submitForm(){
            var editForm = document.forms[0];
            /*if(!validateMonitorTopoGroupForm(editForm)){
                return false;
            }*/
            var type = document.getElementById("type").value;
            if(type=="edit"){
                editForm.action = "updateGroup.do?method=updateMonitorTopoGroup";
            } else if(type=="add"){
                editForm.action = "addGroup.do?method=addMonitorTopoGroup";
            }
            editForm.submit();
        }
        function selectDevice(){
            var deviceGroupId = document.getElementById("monitorTopoGroup.devicegroupid").value;
            var url = "group.do?method=editMonitorDeviceGroup&deviceGroupId="+deviceGroupId;
            window.open (url, "", "height=400, width=800, scrollbars=no, resizable=no,top=200,left=300");
        }
    </script>
</head>
<body>
<html:form action="group.do?method=addMonitorTopoGroup" method="post">
<html:hidden property="monitorTopoGroup.devicegroupid" />
<html:hidden property="type" />
    <div style="width:100%;margin:8px 8px 0 10">
        <%--<html:errors  property="addMonitorTopoGroup"/>--%>
        <html:errors/>
        <table width=100% border=1 cellpadding=1 cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
            <tbody>
            <tr class="toptitle">
                <td colspan="2" style="text-align:left"><p style="font-weight:bold;"><logic:equal name="monitorTopoGroupForm" property="type" value="edit">修改</logic:equal><logic:equal name="monitorTopoGroupForm" property="type" value="add">增加</logic:equal>组别</p></td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">组别名称：</span>
                <td class="td_value">
                    <html:text property="monitorTopoGroup.devicegroupname" styleClass="input_box" maxlength="100"/>
                    <font color="#ff0000">*</font>
                    <logic:equal name="monitorTopoGroupForm" property="type" value="edit"><input type="button" onclick="selectDevice();" value="选择设备" class="button_nor"/></logic:equal>
                </td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">宽度：</span>
                <td class="td_value">
                    <html:text property="monitorTopoGroup.groupwidth" styleClass="input_box" maxlength="100"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">高度：</span>
                <td class="td_value">
                    <html:text property="monitorTopoGroup.groupheight" styleClass="input_box" maxlength="100"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">水平索引：</span>
                <td class="td_value">
                    <html:text property="monitorTopoGroup.groupxindex" styleClass="input_box" maxlength="100"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">垂直索引：</span>
                <td class="td_value">
                    <html:text property="monitorTopoGroup.groupyindex" styleClass="input_box" maxlength="100"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">校区：</span>
                <td class="td_value">
                    <html:select property="monitorTopoGroup.location.locationid" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="locationList" property="locationid" labelProperty="locationname"/>
                    </html:select>
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
