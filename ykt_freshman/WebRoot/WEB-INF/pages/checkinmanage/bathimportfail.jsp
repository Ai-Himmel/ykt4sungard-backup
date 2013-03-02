<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="bathcardAction.do?method=load4upload" enctype="multipart/form-data">
	<font size="4" color="#990000">新生浴卡卡号导入失败！<br>
	<%if(request.getAttribute("msg")!=null&&request.getAttribute("msg").equals("notmanager")){%>
	您不是今年的班级辅导员！
	<%}else{%>
	请检查导入文件是否正确。
	<%}%></font><br>
<input type="submit" class="button_nor" value="返 回">
</html:form>
</html:html>
