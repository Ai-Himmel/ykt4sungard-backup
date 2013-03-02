<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
<head>
    <%@ include file="/pages/common/meta.jsp" %>
    <%@ include file="/pages/components/calendar/calendar.jsp" %>
    <link href="<c:url value="/pages/styles/admin.css"/>" type=text/css rel=stylesheet>
    <script type="text/javascript" src="<c:url value="/pages/scripts/admin.js"/>"></script>
    <script type="text/javascript" src="<c:url value="/pages/scripts/validator.jsp"/>"></script>

</head>

<body>
<div class="pageTitle">部门排班设置-选择部门</div>
<form name="clerkForm"  action="department.do?method=addConfStep1" method="post" >
<jodd:form bean="request">
       <%@ include file="/pages/common/messages.jsp" %>
        <table class="border" width=100% cellSpacing=0 cellPadding=2 align="center">
             <tr>
                <td class="left" width="20%">部门:</td>
                <td class="right">
                    <IFRAME name='DataFrame' src="departmentManager.do?method=loadDepartmentTree" width="220" height="200" SCROLLING="auto"></IFRAME>
                    <input type="hidden" name ="new_department"/>
                </td>
            </tr>
            <tr>
                <td colspan="2" class="bottom">
                    <input type="submit" class="submitButton" name="submitButton" value="下一步"  style="margin-right:60px" onclick="return onSubmit();"/>
                    <BUTTON onclick="history.back();">返回</BUTTON>
                </td>
            </tr>
        </table>
		</jodd:form>
</form>   
</body>
</html>
<script>
function onSubmit(){
    m_sCheckKey	= DataFrame.GetAllCheckData();
    if(m_sCheckKey==""){
       alert("请选择部门！");
       return false;
    }
    var sSelKey	= "#$#$#$" ;	// 数据分隔符(显示值text与数据值value)
    
    var aCheckdata	= m_sCheckKey.split(sSelKey);
    sVal	= aCheckdata[1];
    sText	= aCheckdata[0];

    document.clerkForm.new_department.value = sVal;   
    
}
</script>