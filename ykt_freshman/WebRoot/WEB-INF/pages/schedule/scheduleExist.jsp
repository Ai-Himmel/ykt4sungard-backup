<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html><body>
<font color="red">
<c:if test="${not empty msg}">
	<c:out value="${msg}"/>
</c:if>
<c:if test="${empty msg}">
����ʧ�ܣ�ʱ�䰲�ų��ֳ�ͻ���������ڼ�ʱ��
</c:if>
</font>
&nbsp;&nbsp;
<a href="javascript:history.back();">����</a>
</body>
</html>