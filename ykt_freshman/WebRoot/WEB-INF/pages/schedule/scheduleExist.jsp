<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html><body>
<font color="red">
<c:if test="${not empty msg}">
	<c:out value="${msg}"/>
</c:if>
<c:if test="${empty msg}">
操作失败，时间安排出现冲突，请检查日期及时间
</c:if>
</font>
&nbsp;&nbsp;
<a href="javascript:history.back();">返回</a>
</body>
</html>