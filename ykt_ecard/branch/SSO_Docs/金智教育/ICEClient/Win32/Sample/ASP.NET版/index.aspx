<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML>
<HEAD>
<TITLE> New Document </TITLE>
<META NAME="Generator" CONTENT="EditPlus">
<META NAME="Author" CONTENT="">
<META NAME="Keywords" CONTENT="">
<META NAME="Description" CONTENT="">
</HEAD>

<Script Language="VB" Runat="Server">
Function getCookie()
	Dim cookieValue
	CookieValue=""
	IF not ( Request.Cookies("iPlanetDirectoryPro") is nothing ) THEN
 		CookieValue = Request.Cookies("iPlanetDirectoryPro").value
	end if
	Return cookieValue 
End Function
</Script>
<BODY><center>

<%
	Dim login,gotoURL,serverUrl,loginUrl,logout,logoutUrl
	Dim idstar
	idstar = Server.CreateObject("Idstar.IdentityManager")
	login = idstar.GetLoginURL()
	logout = idstar.GetLogoutURL()
	serverUrl = "http://cxiao.wiscom.com.cn"
	gotoUrl = serverUrl & Request.RawUrl
	loginUrl = login & "?goto=" & Server.UrlEncode(gotoUrl)
	logoutUrl = logout & "?goto=" & Server.UrlEncode(gotoUrl)

	Dim cookieValue
	Dim currentUser

	cookieValue = getCookie()
	currentUser = ""
	currentUser = idstar.GetCurrentUser( "" & Server.UrlDecode(cookieValue) )
	
	If ( Len(currentUser) <> 0 ) Then
		Response.Write( "cookies值是：" & Server.UrlDecode(cookieValue))
		Response.Write("<p>已登录")
		%>
		<p>当前用户: <%= currentUser %>
		<p><a href="search.aspx">属性查询</a>
		<p><a href="<%= logoutUrl %>">注销</a>
		<%
	Else
		%>
		<p>您没有登录,请登录  <a href="<%= loginUrl %>">Login</a>
		<%
	End If
	
%>
</center>
</BODY>
</HTML>
