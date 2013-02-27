<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <link href="<c:url value="/pages/style/default/info.css"/>" type="text/css" rel=stylesheet>
    <html:javascript formName="monitorServiceTemplateForm"/>
    <script type="text/javascript">
        function submitForm(){
            var editForm = document.forms[0];
            if(!validateMonitorServiceTemplateForm(editForm)){
                return false;
            }
            var type = document.getElementById("type").value;
            if(type=="edit"){
                editForm.action = "updateServiceTemplate.do?method=updateMonitorServiceTemplate";
            } else if(type=="add"){
                editForm.action = "addServiceTemplate.do?method=addMonitorServiceTemplate";
            }
            editForm.submit();
        }
        function showtuna_jmpinfo(tt,content){
			 var ttop = tt.offsetTop;    //TT控件的定位点高
			    var thei = tt.clientHeight;    //TT控件本身的高
			    var tleft = tt.offsetLeft;    //TT控件的定位点宽
			    while (tt = tt.offsetParent) {
			        ttop += tt.offsetTop;
			        tleft += tt.offsetLeft;
			    }
			    document.getElementById("tuna_jmpinfo").style.top = ttop + thei;
			    document.getElementById("tuna_jmpinfo").style.left = tleft;
			    document.getElementById("pubJumInfo_content").innerHTML =content;
			    document.getElementById("tuna_jmpinfo").style.visibility = "visible";		
		 }
		 function showself(){
			    document.getElementById("tuna_jmpinfo").style.visibility = "visible";		
		 }
		 function notshowself(){
			    document.getElementById("tuna_jmpinfo").style.visibility = "hidden";		
		 }
		 function notshowtuna_jmpinfo(){
			    document.getElementById("tuna_jmpinfo").style.visibility = "hidden";		
		 }
    </script>
</head>
<body>
<html:form action="serviceTemplate.do?method=addMonitorServiceTemplate" method="post">
<html:hidden property="monitorServiceTemplate.templateId" />
<html:hidden property="type" />
    <div style="width:100%;margin:8px 8px 0 10">
        <%--<html:errors  property="addMonitorServiceTemplate"/>--%>
        <html:errors/>
        <table width=100% border=1 cellpadding=1 cellspacing=0 bordercolor="#FFFFFF">
            <tbody>
            <tr class="toptitle">
                <td colspan="3" style="text-align:left"><p style="font-weight:bold;"><logic:equal name="monitorServiceTemplateForm" property="type" value="edit">修改</logic:equal><logic:equal name="monitorServiceTemplateForm" property="type" value="add">增加</logic:equal>服务模板 </p></td>
            </tr>
            <tr>
                <td class="td_title">模板名称：</td>
                <td class="td_value">
                    <html:text property="monitorServiceTemplate.templateName" styleClass="input_box" maxlength="100"/>
                    <font color="#ff0000">*</font>
                </td>
                 <td class="td_value1">
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间域：</td>
                <td class="td_value">
                    <html:select property="monitorServiceTemplate.checkTimeperiod.timeperiodId" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorTimePeriods" property="timeperiodId" labelProperty="alias"/>
                    </html:select>
                </td>
                 <td class="td_value1">
                </td>
            </tr>
            <tr>
                <td class="td_title">检查时间间隔：</td>
                <td class="td_value">
                    <html:text property="monitorServiceTemplate.checkInterval" styleClass="input_box" maxlength="50"/>
                </td>
                 <td class="td_value1">
                </td>
            </tr>
            <tr>
                <td class="td_title">重试时间间隔：</td>
                <td class="td_value">
                    <html:text property="monitorServiceTemplate.retryInterval" styleClass="input_box" maxlength="50"/>
                </td>
                 <td class="td_value1">
                (说明：系统首次发现服务异常后(包括warnning,critical,unknow)，为确认服务是否真实异常所进行重复检查的时间间隔.)
                </td>
            </tr>
            <tr>
                <td class="td_title">最大重试次数：</td>
                <td class="td_value">
                    <html:text property="monitorServiceTemplate.maxCheckAttempts" styleClass="input_box" maxlength="50"/>
                </td>
                 <td class="td_value1">
                (说明：系统首次发现服务异常后(包括warnning,critical,unknow)，为确认服务是否真实异常所进行重复检查的次数.)
                </td>
            </tr>
            <tr>
                <td class="td_title">是否允许主动检查：</td>
                <td class="td_value">
                    <html:checkbox property="monitorServiceTemplate.activeChecksEnabled" value="1"/>
                </td>
                  <td class="td_value1">
                &nbsp;<span class="searchresult_fltlist_bgblue" onmousemove="javascript:showtuna_jmpinfo(this,'主动检查：由监控系统自主进行的服务是否为正常状态的检查');" onmouseout="javascript:notshowtuna_jmpinfo();">说明</span>
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间域：</td>
                <td class="td_value">
                    <html:select property="monitorServiceTemplate.notificationTimeperiod.timeperiodId" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorTimePeriods" property="timeperiodId" labelProperty="alias"/>
                    </html:select>
                </td>
                 <td class="td_value1">
                </td>
            </tr>
            <tr>
                <td class="td_title">通知时间间隔：</td>
                <td class="td_value">
                    <html:text property="monitorServiceTemplate.notificationInterval" styleClass="input_box" maxlength="50"/>
                </td>
                 <td class="td_value1">
                &nbsp;<span class="searchresult_fltlist_bgblue" onmousemove="javascript:showtuna_jmpinfo(this,'服务持续异常,监控系统重复通知的时间间隔.')" onmouseout="javascript:notshowtuna_jmpinfo();">说明</span>
                </td>
            </tr>
            <tr>
                <td class="td_title">warning是否通知：</td>
                <td class="td_value">
                    <html:checkbox property="monitorServiceTemplate.notifyOnWarning" value="1"/>
                </td>
                 <td class="td_value1">
                </td>
            </tr>
            <tr>
                <td class="td_title">unknown是否通知：</td>
                <td class="td_value">
                    <html:checkbox property="monitorServiceTemplate.notifyOnUnknown" value="1"/>
                </td>
                 <td class="td_value1">
                </td>
            </tr>
            <tr>
                <td class="td_title">critical是否通知：</td>
                <td class="td_value">
                    <html:checkbox property="monitorServiceTemplate.notifyOnCritical" value="1"/>
                </td>
                 <td class="td_value1">
                </td>
            </tr>
            <tr>
                <td class="td_title">recovery是否通知：</td>
                <td class="td_value">
                    <html:checkbox property="monitorServiceTemplate.notifyOnRecovery" value="1"/>
                </td>
                 <td class="td_value1">
                &nbsp;<span class="searchresult_fltlist_bgblue" onmousemove="javascript:showtuna_jmpinfo(this,'recovery:服务从异常状态恢复.')" onmouseout="javascript:notshowtuna_jmpinfo();">说明</span>
                </td>
            </tr>
            <tr>
                <td class="td_title">联系人组：</td>
                <td class="td_value">
                    <html:select property="monitorServiceTemplate.contactGroups.contactgroupId" >
                        <html:option value="">-----------请选择-----------</html:option>
                        <html:options collection="monitorContactgroups" property="contactgroupId" labelProperty="contactgroupName"/>
                    </html:select>
                </td>
                 <td class="td_value1">
                </td>
            </tr>
            <tr>
                <td colspan="3"  align="center">
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
<div style="visible; visibility: hidden; position: absolute; z-index: 120; display: block; width: 300px; height: 133px;" id="tuna_jmpinfo" onmouseover="showself()" onmouseout="notshowself()">
	<table width="300px" cellspacing="0" cellpadding="0" class="pubJmpInfo_jmpInfo01" id="main">
        <tbody><tr>
            <td class="top_l"></td><td class="top_m"></td><td class="top_r"></td>
        </tr>
        <tr>
            <td class="middle_l"></td>
            <td class="middle_m">
                 <div class="middle_content">
                    <h1 style="background: transparent none repeat scroll 0% 0%; -moz-background-clip: border; -moz-background-origin: padding; -moz-background-inline-policy: continuous;">说明信息</h1>                
                    <div class="pubJmpInfo_horizontal"></div>
                    <div id="pubJumInfo_content"></div>
                 </div>
            </td>
            <td class="middle_r"></td>
        </tr>
        <tr>
            <td class="bottom_l"></td><td class="bottom_m"></td><td class="bottom_r"></td>
        </tr>
    </tbody></table>
</div>
</body>

</html>
