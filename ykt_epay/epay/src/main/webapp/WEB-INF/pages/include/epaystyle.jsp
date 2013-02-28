<%
String style = (session!=null && session.getAttribute("STYLE")!=null)?(String)session.getAttribute("STYLE"):"epay";
String context = request.getScheme() + "://" + request.getServerName() + ":" + request.getServerPort() + request.getContextPath();
%>
<link href="<%=context%>/theme/style/<%=style%>/style.css" rel="stylesheet" type="text/css">