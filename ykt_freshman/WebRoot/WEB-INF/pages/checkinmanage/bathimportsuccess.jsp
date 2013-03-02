<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="bathcardAction.do?method=load4upload" enctype="multipart/form-data">
	<font size="3" color="#990000">新生浴卡卡号导入成功！<br>
	<%if(request.getAttribute("notinclassstu")!=null&&!(request.getAttribute("notinclassstu").equals(""))){%>
	<%=(String)request.getAttribute("notinclassstu")%>非您所在班级新生，他们的浴卡卡号未更新！
	<%}%>
	</font>
<input type="submit" class="button_nor" value="返 回">
</html:form>
</html:html>