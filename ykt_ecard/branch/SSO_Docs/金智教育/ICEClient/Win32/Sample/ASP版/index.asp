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

	if currentUser = "" then
		Response.Write("<p>��û�е�¼,���¼")
		Response.Write("<a href=" & loginUrl & ">login</a>")
	else
		Response.Write("cookie ֵ:" & cookieValue)
		Response.Write("<p>")
		Response.Write("�ѵ�¼")
		Response.Write("<p>��ǰ�û�:"  & currentUser )
		Response.Write("<p><a href='search.asp'>���Բ�ѯ</a>")
		Response.Write("<p><a href='" & logoutUrl & "'>ע��</a>")
	end if
	
%>
</center></body></html>
