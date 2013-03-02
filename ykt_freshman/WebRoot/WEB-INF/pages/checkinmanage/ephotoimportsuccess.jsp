<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="ecardPhotoAction.do?method=load4upload" enctype="multipart/form-data">
	<font size="3" color="#990000">新生一卡通拍照情况导入成功！<br>
	<%if(request.getAttribute("notfindstu")!=null&&!(request.getAttribute("notfindstu").equals(""))){%>
	未找到新生<%=(String)request.getAttribute("notfindstu")%>，他们的一卡通拍照情况未更新！
	<%}%>
	</font>
<input type="submit" class="button_nor" value="返 回">
</html:form>
</html:html>