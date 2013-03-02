<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="medium">
				<strong>宿舍统计</strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				<form method="post" name="form1">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
						<tbody>
							<tr align="center" valign="middle" bgcolor="#D6B3B1">
								<td width="20%" valign="middle">
									宿舍所属校区
								</td>							
								<td width="20%" valign="middle">
									宿舍所属区域
								</td>
								<td width="20%" height="24" valign="middle">
									宿舍楼号
								</td>
								<td width="15%" valign="middle">
									宿舍可住总人数
								</td>
								<td width="15%" valign="middle">
									已住人数
								</td>
								<td width="20%" valign="middle">
									空闲床位数
								</td>
							</tr>
							<logic:present name="dormStat" scope="request">
								<!--page offset start -->
								<%int dormStatCount = ((Integer) request
					.getAttribute("dormStatCount")).intValue();%>
								<pg:pager url="./DormitoryAction.do" items="<%=dormStatCount%>" index="center" maxPageItems="<%=dormStatCount+1%>" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
									<%-- keep track of preference --%>
									<pg:param name="page" />
									<pg:param name="orderby" />
									<pg:param name="sort" />
									<pg:param name="method" />
									<%-- save pager offset during form changes --%>
									<input type="hidden" name="pager.offset" value="<%= offset %>">
									<logic:iterate name="dormStat" id="dormStat">
									<c:if test="${dormStat.location=='ALLLOC'}">
										<tr align="center" valign="middle" bgcolor="#FF9999">
											<td height="24" align="center" valign="middle">
												总计
											</td>
											<td align="center" valign="middle">
												－－
											</td>											
											<td align="center" valign="middle">
												－－
											</td>
											<td align="center" valign="middle">
												<bean:write name="dormStat" property="totalNumber" />
											</td>
											<td align="center" valign="middle">
												<bean:write name="dormStat" property="studentInCount" />
											</td>
											<td align="center" valign="middle">
												<bean:write name="dormStat" property="nonCount" />
											</td>
										</tr>
									</c:if>
									<c:if test="${dormStat.location!='ALLLOC'}">
										<tr align="center" valign="middle" bgcolor="#FFFFFF">
											<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="dormStat" property="area" />
											</td>										
											<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="dormStat" property="location" />
											</td>
											<td align="center" valign="middle">
												<a href='DormitoryAction.do?method=showRoomStat&getrole=3&Area=<bean:write name="dormStat" property="areaId"/>&Location=<bean:write name="dormStat" property="locationId"/>&Dorm=<bean:write name="dormStat" property="dormitoryId"/>&cw=<bean:write name="dormStat" property="totalNumber"/>&yzrs=<bean:write name="dormStat" property="studentInCount"/>&kxcw=<bean:write name="dormStat" property="nonCount"/>'><bean:write name="dormStat" property="dormitory" /></a>
											</td>
											<td align="center" valign="middle">
												<bean:write name="dormStat" property="totalNumber" />
											</td>
											<td align="center" valign="middle">
												<bean:write name="dormStat" property="studentInCount" />
											</td>
											<td align="center" valign="middle">
												<bean:write name="dormStat" property="nonCount" />
											</td>
										</tr>
									</c:if>
										
									</logic:iterate>
									<jsp:include page="../security/page.jsp" flush="true" />
								</pg:pager>
								<!-- page offset end -->
							</logic:present>
						</tbody>
					</table>
				</form>
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td height="40" align="right" valign="middle">

			</td>
		</tr>
	</table>
</body>
