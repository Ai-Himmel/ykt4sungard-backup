<html>		
<body>
<div align="center">
<%
	Dim idstar
	set idstar = Server.CreateObject("Idstar.IdentityManager")
	'''''''''��ȡcookie''''''''
	Dim CookieValue
	CookieValue = ""
	IF not ( Request.Cookies("iPlanetDirectoryPro") is nothing ) THEN	
     		CookieValue = Request.Cookies("iPlanetDirectoryPro")	
  	end if	

	'''''''''��ȡ�û���''''''''
	Dim currentUser
	currentUser = ""
	currentUser = idstar.GetCurrentUser( cookieValue )

%>

	<p>��ѯ�û�[<%Response.Write(currentUser)%>]������ <a href="index.asp">����</a>
	<form >
		<p> ����<input type=text name="attr" value=""><input type="submit">
	</form>

<%	
	Dim attr
	Dim i
	attr = Request("attr")
	if ( Len(attr) > 0 ) then
		Dim values
		values = idstar.GetUserAttribute( currentUser, attr )
		Response.Write("<p>����: " & attr & " ��ѯ�������: " & 1+UBound(values) )
		for i =0 to UBound( values )
 			Response.Write "<p>attr[" & i & "]=" & values(i)
		Next
	end if
%>
	
</div>
</body>
</html>