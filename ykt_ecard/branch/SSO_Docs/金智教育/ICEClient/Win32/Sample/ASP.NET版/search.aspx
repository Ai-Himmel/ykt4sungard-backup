<html>
<Script Language="VB" Runat="Server">
Function getCookie()
	Dim cookieValue
	cookieValue=""
	IF not ( Request.Cookies("iPlanetDirectoryPro") is nothing ) THEN
 		CookieValue = Request.Cookies("iPlanetDirectoryPro").value
	end if
	Return cookieValue
End Function
</Script>

<%
	Dim idstar
	idstar = Server.CreateObject("Idstar.IdentityManager")
	Dim cookieValue
	Dim currentUser
	cookieValue = getCookie()
	currentUser = idstar.GetCurrentUser( "" & Server.UrlDecode(cookieValue) )		
%>

<body>
	<div align="center">
	<p> ��ѯ�û�<%Response.Write(currentUser)%>���� <a href="index.aspx">����</a>
	<form >
		<p> ����<input type=text name="attr"  value=""><input type=submit>
	</form>

<%
	Dim attr
	Dim i
	attr = Request("attr")
	if ( Len(attr) > 0 ) then
		Dim values
		values= idstar.GetUserAttribute( "" & currentUser, "" & attr )
		Response.Write("<p>����: " & attr & " ��ѯ������� " & 1+UBound(values) )
		for i = 0 to UBound(values)
			Response.Write("<li>" & values(i))
		next
	end if
%>		
</div>
</body>
</html>