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
			<td align="center" valign="top" height="10"><%=request.getAttribute("dormInfo")%></td>
		</tr>
		<tr>
			<td align="center" valign="top" height="10">&nbsp;</td>
		</tr>
		<%String cw = request.getParameter("cw");
		String yzrs = request.getParameter("yzrs");
		String kxcw = request.getParameter("kxcw");%>
		<tr>
			<td align="center" valign="top">
				<table width=96% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
					<tbody>
						<tr align="center" valign="middle" bgcolor="#D6B3B1">
							<td width="12%" height="24" valign="middle">
								层号
							</td>
							<td width="12%" height="24" valign="middle">
								单元号
							</td>						
							<td width="12%" height="24" valign="middle">
								宿舍号
							</td>
							<td width="12%" height="24" valign="middle">
								入住性别
							</td>
							<td width="12%" height="24" valign="middle">
								朝向
							</td>
							<td width="12%" valign="middle">
								床位
							</td>
							<td width="12%" valign="middle">
								已住人数
							</td>
							<td width="12%" valign="middle">
								空闲床位
							</td>
						</tr>
						<logic:present name="roomStat" scope="request">
							<%int roomStatCount = ((Integer) request
					.getAttribute("roomStatCount")).intValue();%>
							<!--page offset start -->
							<pg:pager url="./DormitoryAction.do" items="<%=roomStatCount%>" index="center" maxPageItems="<%=roomStatCount+1%>" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
								<%-- keep track of preference --%>
								<pg:param name="page" />
								<pg:param name="orderby" />
								<pg:param name="sort" />
								<pg:param name="method" />
								<pg:param name="getrole" />
								
								<%-- save pager offset during form changes --%>
								<input type="hidden" name="pager.offset" value="<%= offset %>">
								<logic:iterate name="roomStat" id="roomStat">
									<tr align="center" valign="middle" bgcolor="#FFFFFF">
										<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="roomStat" property="level" />&nbsp;
										</td>
										<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="roomStat" property="unit" />&nbsp;
										</td>									
										<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="roomStat" property="roomNumber" />
										</td>
																				<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="roomStat" property="gender" />
										</td>
																				<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="roomStat" property="direction" />
										</td>
										<td align="center" valign="middle">
											<bean:write name="roomStat" property="totalNum" />
										</td>
										<td align="center" valign="middle">
											<bean:write name="roomStat" property="allotNum" />
										</td>
										<td align="center" valign="middle">
											<bean:write name="roomStat" property="nonNum" />
										</td>										
									</tr>
								</logic:iterate>
								<tr align="center" valign="middle" bgcolor="#FF9999">
										<td height="24" align="center" valign="middle" >
											小计
										</td>
										<td height="24" align="center" valign="middle" >
											--
										</td>
																				<td height="24" align="center" valign="middle" >
											--
										</td>
																				<td height="24" align="center" valign="middle" >
											--
										</td>
																				<td height="24" align="center" valign="middle" >
											--
										</td>										
										<td align="center" valign="middle">
											<%=cw%>
											<input name="Area" type="hidden" value="<c:out value="${area}"/>">
											<input name="Location" type="hidden" value="<c:out value="${location}"/>">
											<input name="Dorm" type="hidden" value="<c:out value="${dorm}"/>">
											<input name="cw" type="hidden" value="<c:out value="${cw}"/>">
											<input name="yzrs" type="hidden" value="<c:out value="${yzrs}"/>">
											<input name="kxcw" type="hidden" value="<c:out value="${kxcw}"/>">											
										</td>
										<td align="center" valign="middle">
											<%=yzrs%>
										</td>
										<td align="center" valign="middle">
											<%=kxcw%>
										</td>										
									</tr>
								<jsp:include page="../security/page.jsp" flush="true" />
							</pg:pager>
							<!-- page offset end -->
						</logic:present>
					</tbody>
				</table>
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
				<td height="30" align="right" valign="middle">				
					<input name="goback" type="button" class="button_nor" value="<bean:message bundle="dormitorymanage"  key="dormStat.sure"/>" onclick="location.href='DormitoryAction.do?method=showDormStat&getrole=3'">
				</td>
			</tr>
	</table>
</body>
