<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="left" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align=center valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="classmanage" key="classStatistic.classStatistic" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>

			<tr>
				<td height="30" align="left" valign="middle">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff >
						<tr>
							<td width="20%">
								����ǰͳ�ƣ�
							</td>
							<td width="20%">
								<a href="classAction.do?method=classStatististic&getrole=2" class="topmenu_link">��������ͳ��</a>
							</td>
							<td>
								<a href="classAction.do?method=majorinStatistic&getrole=2" class="topmenu_link">�Ա�ͳ��</a>
							</td>
						</tr>
						<tr>
							<td>
								������ͳ�ƣ�
							</td>
							<td>
								<a href="classAction.do?method=classCheckInStatististic&getrole=2" class="topmenu_link">��������ͳ��</a>
							</td>
							<td>
								<a href="classAction.do?method=majorinCheckInStatistic&getrole=2" class="topmenu_link">�Ա�ͳ��</a>
							</td>							
						</tr>
					</table>					
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>
		</table>
	</body>