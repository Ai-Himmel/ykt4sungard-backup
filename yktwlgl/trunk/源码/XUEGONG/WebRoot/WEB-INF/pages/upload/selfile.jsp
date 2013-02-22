<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="/inschool/dlxlcs.do?method=importExcelFile" enctype="multipart/form-data">
	<html:file property="theFile"/>
<html:submit/>
</html:form>
</html:html> 