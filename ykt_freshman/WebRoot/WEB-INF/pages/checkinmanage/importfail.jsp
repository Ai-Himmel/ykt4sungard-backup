<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="stufeeAction.do?method=load4upload" enctype="multipart/form-data">
	<font size="4" color="#990000">新生缴费数据导入失败！<br>请检查导入文件是否正确。</font><br>
<input type="submit" class="button_nor" value="返 回">
</html:form>
</html:html>
