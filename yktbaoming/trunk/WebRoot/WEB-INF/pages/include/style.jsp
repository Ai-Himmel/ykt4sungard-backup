<%
String style = (session!=null && session.getAttribute("STYLE")!=null)?(String)session.getAttribute("STYLE"):"default";
String context = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort() + request.getContextPath();
%>
<link href="<%=context%>/pages/style/<%=style%>/style.css" rel="stylesheet" type="text/css">