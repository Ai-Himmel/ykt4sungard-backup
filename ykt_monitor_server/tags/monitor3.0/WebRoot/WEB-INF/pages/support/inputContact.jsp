<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <html:javascript formName="monitorContactForm"/>
    <script type="text/javascript">
        function submitForm(){
            var editForm = document.forms[0];
            if(!validateMonitorContactForm(editForm)){
                return false;
            }
            var type = document.getElementById("type").value;
            if(type=="edit"){
                editForm.action = "updateContact.do?method=updateMonitorContact";
            } else if(type=="add"){
                editForm.action = "addContact.do?method=addMonitorContact";
            }
            generateNotifyCommand();
            editForm.submit();
        }
        function parseNotifyCommand(){
            var notifyCommandValue = document.getElementById("monitorContact.notifyCommand").value;
            if(notifyCommandValue!=null && notifyCommandValue!=""){
                var array = notifyCommandValue.split(",");
                for(var i=0;i<array.length;i++){
                    if(array[i]=="EMAIL"){
                        document.getElementById("email").checked = true;
                    } else if(array[i]=="SMS"){
                        document.getElementById("sms").checked = true;
                    }
                }
            }
        }
        function generateNotifyCommand(){
            var email = document.getElementById("email");
            var sms = document.getElementById("sms");
            var notifyCommandValue = "";
            if(email.checked){
                notifyCommandValue = notifyCommandValue + email.value + ",";
            }
            if(sms.checked){
                notifyCommandValue = notifyCommandValue + sms.value + ",";
            }
            if(notifyCommandValue!=""){
                notifyCommandValue = notifyCommandValue.substring(0,notifyCommandValue.length-1);
            }
            document.getElementById("monitorContact.notifyCommand").value = notifyCommandValue;
        }
        window.onload = function(){
            parseNotifyCommand();
        }
    </script>
</head>
<body>
<html:form action="contact.do?method=addMonitorContact" method="post">
<html:hidden property="monitorContact.contactId" />
<html:hidden property="type" />
    <div style="width:100%;margin:8px 8px 0 10">
        <%--<html:errors  property="addMonitorContact"/>--%>
        <html:errors/>
        <table width=100% border=1 cellpadding=1 cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
            <tbody>
            <tr class="toptitle">
                <td colspan="2" style="text-align:left"><p style="font-weight:bold;"><logic:equal name="monitorContactForm" property="type" value="edit">修改</logic:equal><logic:equal name="monitorContactForm" property="type" value="add">增加</logic:equal>联系人</p></td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">联系人名称：</span>
                <td class="td_value">
                    <html:text property="monitorContact.contactName" styleClass="input_box" maxlength="100"/>
                    <font color="#ff0000">*</font>
                </td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">邮箱：</span>
                <td class="td_value">
                    <html:text property="monitorContact.emailAddress" styleClass="input_box" maxlength="100"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">联系电话：</span>
                <td class="td_value">
                    <html:text property="monitorContact.cellphone" styleClass="input_box" maxlength="50"/>
                </td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">联系人组：</span>
                <td class="td_value">
                    <html:select property="monitorContact.contactGroups.contactgroupId" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorContactgroups" property="contactgroupId" labelProperty="contactgroupName"/>
                    </html:select>
                </td>
            </tr>
            <tr>
                <td class="td_title">
                    <span class="medium">通知方式：</span>
                <td class="td_value">
                    <html:hidden property="monitorContact.notifyCommand"/>
                    <input type="checkbox" id="email" name="email" value="EMAIL" />EMAIL&nbsp;&nbsp;<input type="checkbox" id="sms" name="sms" value="SMS" />SMS
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
