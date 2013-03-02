<html><body><center>
<%
	
	set idstar = Server.CreateObject("Idstar.IdentityManager")

	Dim login,gotoURL,serverUrl,loginUrl,logout,logoutUrl
	login = idstar.GetLoginURL()
	logout = idstar.GetLogoutURL()
	serverUrl = "http://cxiao.wiscom.com.cn"
	gotoUrl = serverUrl & Request.ServerVariables("SCRIPT_NAME")
	loginUrl = login & "?goto=" & Server.UrlEncode(gotoUrl)
	logoutUrl = logout & "?goto=" & Server.UrlEncode(gotoUrl)

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

	if currentUser = "" then
		Response.Write("<p>您没有登录,请登录")
		Response.Write("<a href=" & loginUrl & ">login</a>")
	else
		Response.Write("cookie 值:" & cookieValue)
		Response.Write("<p>")
		Response.Write("已登录")
		Response.Write("<p>当前用户:"  & currentUser )
		Response.Write("<p><a href='search.asp'>属性查询</a>")
		Response.Write("<p><a href='" & logoutUrl & "'>注销</a>")
	end if
	
%>
</center></body></html>
