<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="stuEnrollNoAction.do?method=load4upload" enctype="multipart/form-data">
	<font size="3" color="#990000">����¼ȡ֪ͨ��ŵ���ɹ���<br>
	<%if(request.getAttribute("notfindstu")!=null&&!(request.getAttribute("notfindstu").equals(""))){%>
	�Ҳ�������<%=(String)request.getAttribute("notfindstu")%>�����ǵ�¼ȡ֪ͨ���δ���£�<br>
	<%}%>
	<%if(request.getAttribute("dupenrollNostu")!=null&&!(request.getAttribute("dupenrollNostu").equals(""))){%>
	����<%=(String)request.getAttribute("dupenrollNostu")%>�����ǵ�¼ȡ֪ͨ��������������ظ���δ���³ɹ���
	<%}%>
	</font>
<input type="submit" class="button_nor" value="�� ��">
</html:form>
</html:html>