<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="bathcardAction.do?method=load4upload" enctype="multipart/form-data">
	<font size="3" color="#990000">����ԡ�����ŵ���ɹ���<br>
	<%if(request.getAttribute("notinclassstu")!=null&&!(request.getAttribute("notinclassstu").equals(""))){%>
	<%=(String)request.getAttribute("notinclassstu")%>�������ڰ༶���������ǵ�ԡ������δ���£�
	<%}%>
	</font>
<input type="submit" class="button_nor" value="�� ��">
</html:form>
</html:html>