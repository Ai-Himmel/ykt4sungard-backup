<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="ecardPhotoAction.do?method=load4upload" enctype="multipart/form-data">
	<font size="3" color="#990000">����һ��ͨ�����������ɹ���<br>
	<%if(request.getAttribute("notfindstu")!=null&&!(request.getAttribute("notfindstu").equals(""))){%>
	δ�ҵ�����<%=(String)request.getAttribute("notfindstu")%>�����ǵ�һ��ͨ�������δ���£�
	<%}%>
	</font>
<input type="submit" class="button_nor" value="�� ��">
</html:form>
</html:html>