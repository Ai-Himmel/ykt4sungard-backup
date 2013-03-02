<%
String style = (session!=null && session.getAttribute("STYLE")!=null)?(String)session.getAttribute("STYLE"):"default";
String context = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort() + request.getContextPath();
%>
<meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
<meta http-equiv="Cache-Control" content="no-store"/>
<meta http-equiv="Pragma" content="no-cache"/>
<meta http-equiv="Expires" content="0"/>
<link href="<c:url value="/pages/styles/default.css"/>" type="text/css" rel=stylesheet>
<script src="<c:url value="/pages/scripts/prototype.js"/>" type="text/javascript"></script>
<script src="<c:url value="/pages/scripts/aa.js"/>" type="text/javascript"></script>
<%@ taglib uri="http://ajaxanywhere.sourceforge.net/" prefix="aa"%>


