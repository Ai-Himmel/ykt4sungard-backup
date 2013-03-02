<%@ page language="java" pageEncoding="utf-8"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://"
			+ request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<base href="<%=basePath%>">

		<title>My JSP 'AdminLogin.jsp' starting page</title>

		<meta http-equiv="pragma" content="no-cache">
		<meta http-equiv="cache-control" content="no-cache">
		<meta http-equiv="expires" content="0">
		<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
		<meta http-equiv="description" content="This is my page">
		<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	</head>

	<body leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">
		<form action="/smartcardweb/adminlogon.do" method="POST" name="adminlogonForm">
			<table width="1024" height="768" border="0" cellpadding="0"
				cellspacing="0">
				<tr>
					<td width="100%" height="593">
						<table width="100%" height="768" border="0" cellpadding="0"
							cellspacing="0">
							<tr>
								<td height="324">
									<table width="100%" height="324" border="0" cellpadding="0"
										cellspacing="0">
										<tr>

											<td width="100%" height="324">
												<table width="100%" border="0" cellpadding="0"
													cellspacing="0">
													<tr align="left">
														<td width="42%" align="right" valign="bottom">
															<font color="#000000" size="4"
																face="Arial, Helvetica, sans-serif" class="info">用户名:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font>
														</td>
														<td width="100%" valign="middle">
															<input type="text" name="username" size="20"
																maxlength="11">
														</td>
													</tr>
													<tr align="center">
														<td width="42%">
															&nbsp;
														</td>
														<td width="58%">
															&nbsp;
														</td>
													</tr>
													<tr align="left">
														<td width="42%" align="right" valign="bottom">
															<font color="#000000" size="4"
																face="Arial, Helvetica, sans-serif" class="info">密
																码:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font>
														</td>
														<td width="100%" height="50%" valign="middle">
															<span class="info"><input name="password"
																	type="password" size="20" axlength="6"> </span>
														</td>
													</tr>
												</table>

											</td>
										</tr>
									</table>
								</td>
							</tr>

						</table>
					</td>
				</tr>
			</table>
		</form>

	</body>
</html>
