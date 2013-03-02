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
<div class="pageTitle">�����Ű�����-ѡ����</div>
<form name="clerkForm"  action="department.do?method=addConfStep1" method="post" >
<jodd:form bean="request">
       <%@ include file="/pages/common/messages.jsp" %>
        <table class="border" width=100% cellSpacing=0 cellPadding=2 align="center">
             <tr>
                <td class="left" width="20%">����:</td>
                <td class="right">
                    <IFRAME name='DataFrame' src="departmentManager.do?method=loadDepartmentTree" width="220" height="200" SCROLLING="auto"></IFRAME>
                    <input type="hidden" name ="new_department"/>
                </td>
            </tr>
            <tr>
                <td colspan="2" class="bottom">
                    <input type="submit" class="submitButton" name="submitButton" value="��һ��"  style="margin-right:60px" onclick="return onSubmit();"/>
                    <BUTTON onclick="history.back();">����</BUTTON>
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
       alert("��ѡ���ţ�");
       return false;
    }
    var sSelKey	= "#$#$#$" ;	// ���ݷָ���(��ʾֵtext������ֵvalue)
    
    var aCheckdata	= m_sCheckKey.split(sSelKey);
    sVal	= aCheckdata[1];
    sText	= aCheckdata[0];

    document.clerkForm.new_department.value = sVal;   
    
}
</script>