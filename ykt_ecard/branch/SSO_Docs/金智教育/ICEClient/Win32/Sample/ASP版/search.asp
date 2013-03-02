<html>		
<body>
<div align="center">
<%
	Dim idstar
	set idstar = Server.CreateObject("Idstar.IdentityManager")
	'''''''''获取cookie''''''''
	Dim CookieValue
	CookieValue = ""
	IF not ( Request.Cookies("iPlanetDirectoryPro") is nothing ) THEN	
     		CookieValue = Request.Cookies("iPlanetDirectoryPro")	
  	end if	

	'''''''''获取用户名''''''''
	Dim currentUser
	currentUser = ""
	currentUser = idstar.GetCurrentUser( cookieValue )

%>

	<p>查询用户[<%Response.Write(currentUser)%>]的属性 <a href="index.asp">返回</a>
	<form >
		<p> 属性<input type=text name="attr" value=""><input type="submit">
	</form>

<%	
	Dim attr
	Dim i
	attr = Request("attr")
	if ( Len(attr) > 0 ) then
		Dim values
		values = idstar.GetUserAttribute( currentUser, attr )
		Response.Write("<p>属性: " & attr & " 查询结果条数: " & 1+UBound(values) )
		for i =0 to UBound( values )
 			Response.Write "<p>attr[" & i & "]=" & values(i)
		Next
	end if
%>
	
</div>
</body>
</html>