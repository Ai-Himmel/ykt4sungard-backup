<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="bathcardAction.do?method=load4upload" enctype="multipart/form-data">
	<font size="4" color="#990000">����ԡ�����ŵ���ʧ�ܣ�<br>
	<%if(request.getAttribute("msg")!=null&&request.getAttribute("msg").equals("notmanager")){%>
	�����ǽ���İ༶����Ա��
	<%}else{%>
	���鵼���ļ��Ƿ���ȷ��
	<%}%></font><br>
<input type="submit" class="button_nor" value="�� ��">
</html:form>
</html:html>
