<%@ page contentType="text/html;charset=UTF-8" %>
<%@ include file="/pages/common/taglibs.jsp" %>

<html>
<head>
    <%@ include file="/pages/common/meta.jsp" %>
    <%@ include file="/pages/components/calendar/calendar.jsp" %>
    <link href="<c:url value="/pages/styles/admin.css"/>" type=text/css rel=stylesheet>
    <script type="text/javascript" src="<c:url value="/pages/scripts/admin.js"/>"></script>
    <script type="text/javascript" src="<c:url value="/pages/scripts/validator.jsp"/>"></script>

</head>

<body>
<div class="pageTitle">考勤人员设置</div>
<jodd:form bean="request">
<form name="clerkForm"  action="setupClerk.do?method=setupClerk" method="post" >
       <%@ include file="/pages/common/messages.jsp" %>
        <table class="border" width=100% cellSpacing=0 cellPadding=2 align="center">

            <tr>
                <td class="left">所属部门:</td>
                <td class="right">
                    <select name="department" style="width: 150">
					<c:forEach var="deptList" items="${deptList}">
							<option value="<c:out value="${deptList.deptId}"/>">
								<c:out value="${deptList.deptName}" />
							</option>
						</c:forEach>
                    </select>
                </td>
            </tr>
			<tr>
                <td class="left" width="20%">坐班:</td>
                <td class="right">
                     <input type="radio" name="isSeat" value="1"/>坐班 <input type="radio" name="isSeat" value="2" checked/>不坐班
                </td>
            </tr>
             <!-- <tr>
                <td class="left" width="20%">部门:</td>
                <td class="right">
                    <IFRAME name='DataFrame' src="departmentManager.do?method=loadDepartmentTree" width="220" height="200" SCROLLING="auto"></IFRAME>
                    <input type="hidden" name ="department"/>
                </td>
            </tr>-->
            <tr>
                <td colspan="2" class="bottom">
                    <input type="submit" class="submitButton" name="submitButton" value=" 确 定 "  style="margin-right:60px" onclick="return onSubmit();"/>
                    <input type="button" class="submitButton" name="submitButton" value=" 返 回 "  style="margin-right:60px" onclick="history.back();"/>
                </td>
            </tr>
        </table>
</form>   
</jodd:form>
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

    document.clerkForm.department.value = sVal;

    
    return true;
    
}
function changed()
{
	clerkForm.submitButton.disabled="true";
	clerkForm.action='clerkManager.do?method=getConfDetail';
	clerkForm.submit();
}
</script>