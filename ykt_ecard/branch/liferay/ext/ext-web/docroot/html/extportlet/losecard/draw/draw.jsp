<%@ include file="/html/common/init.jsp" %>
<portlet:defineObjects />
<%String tess = request.getAttribute("mytest").toString(); %>

<html>
	<head>
		<title>dds</title>
		<meta http-equiv="Content-Type" content="text/html;">
	</head>
	<body>
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

			<form name="addConf" action="workTime.do?method=addworkTime" method="post" onsubmit="return check_worktime();">
				<div id="titleDiv" class="pageTitle">
					<strong> <font class="medium"> <%=tess %> </font> </strong>
				</div>
				<div id=lineDiv class="hrLine">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td class="tdborderLine"></td>
						</tr>
					</table>
				</div>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
						<tr>
							<td height="30" align="right" valign="middle">
							</td>
							<td>
								&nbsp;&nbsp;
								<input name="Submit22" type="submit" class="submitButton" value=" create " >&nbsp;&nbsp;&nbsp;&nbsp;
								<input name="Submit22" type="button" class="submitButton" value=" cancle " onclick="">

							</td>
						</tr>
					</tbody>
				</table>
			</tr>
	</body>
	</form>
	</table>
</html>
