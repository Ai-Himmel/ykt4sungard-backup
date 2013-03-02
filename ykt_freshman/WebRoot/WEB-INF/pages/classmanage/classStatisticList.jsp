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
							<td>
								报到前统计：
							</td>
							<td>
								<a href="classAction.do?method=classStatististic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.studentStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=majorinStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.majorinStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nativeplaceStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.fromprovincStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationalityStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationalityStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=daleiStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.daleiStatistic" /></a>
							</td>
						</tr>
						<tr>
							<td>
								报到后统计：
							</td>
							<td>
								<a href="classAction.do?method=classCheckInStatististic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.studentCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=majorinCheckInStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.majorinCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nativeplaceCheckInStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.fromprovincCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationCheckInStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationalityCheckInStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationalityCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=daleiCheckInStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.daleiStatistic" /></a>
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