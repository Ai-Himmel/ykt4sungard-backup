<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="medium">
				<strong>����ͳ��</strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="top" height="10"><%=request.getAttribute("dormInfo")%></td>
		</tr>
		<tr>
			<td align="center" valign="top" height="10">&nbsp;</td>
		</tr>
		<%String cw = (String)request.getAttribute("cw");
		String yzrs = (String)request.getAttribute("yzrs");
		String kxcw = (String)request.getAttribute("kxcw");
		String wbdcw = (String)request.getAttribute("wbdcw");%>
		<tr>
			<td align="center" valign="top">
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
					<tbody>
						<tr align="center" valign="middle" bgcolor="#D6B3B1">
							<td width="20%" height="24" valign="middle">
								�����
							</td>
							<td width="10%" height="24" valign="middle">
								����
							</td>
							<td width="10%" height="24" valign="middle">
								��ס�Ա�
							</td>														
							<td width="15%" valign="middle">
								��λ
							</td>
							<td width="15%" valign="middle">
								��ס����
							</td>
							<td width="15%" valign="middle">
								���д�λ
							</td>
							<td width="15%" valign="middle">
								δ������λ
							</td>
						</tr>
						<logic:present name="notcheckinroomStat" scope="request">							
								<logic:iterate name="notcheckinroomStat" id="roomStat">
									<tr align="center" valign="middle" bgcolor="#FFFFFF">
										<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="roomStat" property="roomNumber" />&nbsp;
										</td>
										<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="roomStat" property="direction" />&nbsp;
										</td>
										<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="roomStat" property="gender" />&nbsp;
										</td>																				
										<td align="center" valign="middle">
											<bean:write name="roomStat" property="totalNum" />&nbsp;
										</td>
										<td align="center" valign="middle">
											<bean:write name="roomStat" property="allotNum" />&nbsp;
										</td>
										<td align="center" valign="middle">
											<bean:write name="roomStat" property="nonNum" />&nbsp;
										</td>	
										<td align="center" valign="middle">
											<bean:write name="roomStat" property="notcheckinNum" />&nbsp;
										</td>										
									</tr>
								</logic:iterate>
								<tr align="center" valign="middle" bgcolor="#FF9999">
										<td height="24" align="center" valign="middle" >
											С��
										</td>
										<td height="24" align="center" valign="middle" >
											--
										</td>
										<td height="24" align="center" valign="middle" >
											--
										</td>																				
										<td align="center" valign="middle">
											<%=cw%>
										</td>
										<td align="center" valign="middle">
											<%=yzrs%>
										</td>
										<td align="center" valign="middle">
											<%=kxcw%>
										</td>
										<td align="center" valign="middle">
											<%=wbdcw%>
										</td>										
									</tr>								
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
					<input name="goback" type="button" class="button_nor" value="<bean:message bundle="dormitorymanage"  key="dormStat.sure"/>" onclick="location.href='DormitoryAction.do?method=showDormStat'">
				</td>
			</tr>
	</table>
</body>
