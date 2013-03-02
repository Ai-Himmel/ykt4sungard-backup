<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.List"%>
<%@ page import="org.king.classmanage.web.help.ClassStatistic"%>
<%@ page import="org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount"%>
<%@ page import="java.util.Map"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium"><bean:message bundle="yangongdormmanage" key="dormDistribution.result" /></font></strong>
					</td>
				</tr>
				<tr>
					<td align="left" valign="middle">
						&nbsp;
					</td>
				</tr>
				<tr>
					<td height="40" align="center" valign="top" class="medium">

						<table width=100% border=0 align="center" cellpadding=1 cellspacing=0 >
							<tbody>
							<tr align="center" valign="middle" height="40">
									<td valign="middle" align="center">
										<bean:message bundle="yangongdormmanage" key="dormDistribution.success" />
									</td>
									
								</tr>
								<tr align="center" valign="middle">
									<td valign="middle" align="center">
										&nbsp;
									</td>									
								</tr>
								<tr>
									<td valign="middle" align="center" height="40">
										<html:errors bundle="yangongdormmanage" />
									</td>
									
								</tr>
		
							</tbody>
						</table>
					</td>
				</tr>
				
		</table>
	</body>
</center>

