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
	
	if ( curUser.length()==0 ){
%>
	<jsp:forward page="index.jsp"/>		
<%	
		return;
	}
%>
<html>
<body>
<div align="center">
<p> ��ѯ�û�<%= curUser %>���� <a href="index.jsp">����</a>
<form >
	<p> ����<input type=text name=attr value=""><input type=submit>
</form>

<%
	String attr = request.getParameter("attr");
	if ( attr != null ){
		String[] values = im.getUserAttribute( curUser, attr );
		out.println("<p>����: " + attr + " ��ѯ������� " + values.length );
		for ( int i=0; i< values.length; i++)
		{
			out.println("<li>" + values[i]);
		}
	}
%>	
</div>
</body>
</html>