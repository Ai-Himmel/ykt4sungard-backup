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
		Response.Write( "cookiesֵ�ǣ�" & Server.UrlDecode(cookieValue))
		Response.Write("<p>�ѵ�¼")
		%>
		<p>��ǰ�û�: <%= currentUser %>
		<p><a href="search.aspx">���Բ�ѯ</a>
		<p><a href="<%= logoutUrl %>">ע��</a>
		<%
	Else
		%>
		<p>��û�е�¼,���¼  <a href="<%= loginUrl %>">Login</a>
		<%
	End If
	
%>
</center>
</BODY>
</HTML>
