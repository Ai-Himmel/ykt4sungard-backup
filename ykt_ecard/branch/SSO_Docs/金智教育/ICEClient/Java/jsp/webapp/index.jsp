<%@page 
	language="java"
	contentType="text/html; charset=GB2312"
	pageEncoding="GB2312"
	import="com.wiscom.is.*, java.net.*"
%>

<%
	String is_config = request.getRealPath("/client.properties");
    Cookie all_cookies[] = request.getCookies();
    Cookie myCookie;
    String decodedCookieValue = null;
    if (all_cookies != null) {
        for(int i=0; i< all_cookies.length; i++) {
            myCookie = all_cookies[i];
            if( myCookie.getName().equals("iPlanetDirectoryPro") ) {
                decodedCookieValue = URLDecoder.decode(myCookie.getValue(),"GB2312");
            }
        }
    }

	IdentityFactory factory = IdentityFactory.createFactory( is_config );
	IdentityManager im = factory.getIdentityManager();
	
	String curUser = "";
	if (decodedCookieValue != null ) {
    	curUser = im.getCurrentUser( decodedCookieValue );
    }
	
%>
<html>
<body>

<div align="center">
<p>��ǰ�û�: <%= curUser %>
<%
	if ( curUser.length()==0 ){
		String gotoURL = HttpUtils.getRequestURL(request).toString();
		String loginURL = im.getLoginURL() +"?goto=" + java.net.URLEncoder.encode(gotoURL);
		%>
		<p>��û�е�¼,���¼<a href="<%= loginURL %>"> Login</a>
		<%
	}else{
		String gotoURL = HttpUtils.getRequestURL(request).toString();
		String logoutURL = im.getLogoutURL() +"?goto=" + java.net.URLEncoder.encode(gotoURL);
		%>
		<p><a href="<%= logoutURL %>">ע��</a>
		<%
	}
%>

<p>
<p> <a href="search.jsp">���Բ�ѯ</a>

</div>
</body>
</html>