<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="stuEnrollNoAction.do?method=load4upload" enctype="multipart/form-data">
	<font size="3" color="#990000">新生录取通知书号导入成功！<br>
	<%if(request.getAttribute("notfindstu")!=null&&!(request.getAttribute("notfindstu").equals(""))){%>
	找不到新生<%=(String)request.getAttribute("notfindstu")%>，他们的录取通知书号未更新！<br>
	<%}%>
	<%if(request.getAttribute("dupenrollNostu")!=null&&!(request.getAttribute("dupenrollNostu").equals(""))){%>
	新生<%=(String)request.getAttribute("dupenrollNostu")%>，他们的录取通知书号与其他新生重复，未更新成功！
	<%}%>
	</font>
<input type="submit" class="button_nor" value="返 回">
</html:form>
</html:html>