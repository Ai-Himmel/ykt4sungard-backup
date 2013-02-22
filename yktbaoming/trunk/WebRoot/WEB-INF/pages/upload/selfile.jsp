<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="uploadAction.do?method=importExcelFile" enctype="multipart/form-data">
	<html:file property="theFile"/>
<html:submit/>
</html:form>
</html:html> 