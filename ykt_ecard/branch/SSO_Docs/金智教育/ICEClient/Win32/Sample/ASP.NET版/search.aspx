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
	<p> 查询用户<%Response.Write(currentUser)%>属性 <a href="index.aspx">返回</a>
	<form >
		<p> 属性<input type=text name="attr"  value=""><input type=submit>
	</form>

<%
	Dim attr
	Dim i
	attr = Request("attr")
	if ( Len(attr) > 0 ) then
		Dim values
		values= idstar.GetUserAttribute( "" & currentUser, "" & attr )
		Response.Write("<p>属性: " & attr & " 查询结果条数 " & 1+UBound(values) )
		for i = 0 to UBound(values)
			Response.Write("<li>" & values(i))
		next
	end if
%>		
</div>
</body>
</html>