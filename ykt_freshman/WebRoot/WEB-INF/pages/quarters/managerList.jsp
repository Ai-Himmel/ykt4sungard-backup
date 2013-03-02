<%@ page pageEncoding="UTF-8"%>
<%@ include file="/WEB-INF/pages/include/style.jsp"%>
<%@ include file="/WEB-INF/pages/tiles/include.jsp"%>
<script type="text/javascript" src="<c:url value='/pages/scripts/selectbox.js'/>" ></script>
<script type="text/javascript" src="<c:url value='/pages/scripts/global.js'/>" charset="gbk"></script>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">宿舍管理人员维护</font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			
			<tr>
				<td height="40" align="center" valign="top">
					
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<tbody>
								<tr align="center" valign="middle">
									
									<td height="24" valign="middle" class="tableHeader">
										学号/工号
									</td>
									<td valign="middle" class="tableHeader">
										姓名
									</td>
									<td valign="middle" class="tableHeader">
										性别
									</td>
									<td valign="middle" class="tableHeader">
										联系方式
									</td>
									<td valign="middle" class="tableHeader">
										管理部门
									</td>
									<td valign="middle" class="tableHeader">
										是否在任
									</td>
									<td valign="middle" class="tableHeader">
										备注
									</td>
									
								</tr>
								
								<s:iterator value="managers" status="status">
									
														<s:url id="chuli" action="addOrUpdateManager!input" namespace="/quarters">	
		          		  									<s:param name="manager.id"><s:property value="id"/></s:param>
		          		  								</s:url>
												<s:if test="#status.isEven()">
													<tr align="center" valign="middle" bgcolor="#FFFFFF">
												</s:if>
												<s:else>
													<tr align="center" valign="middle" bgcolor="#F6F4F5">
												</s:else>		
														<td height="24" align="center" valign="middle" >
														
															<s:a href="%{chuli}"><s:property value="stuNo"/></s:a>
															&nbsp;
														</td>
														<td height="24" align="center" valign="middle" >
														
															<s:property value="name"/>
															&nbsp;
														</td>
														<td height="24" align="center" valign="middle" >
														  <s:if test='sex != null && sex.trim().equals("1")'>
															
															&nbsp;男
															</s:if>
															<s:else>
																女
															</s:else>
														</td>
														<td height="24" align="center" valign="middle" >
														
															<s:property value="contact"/>
															&nbsp;
														</td>
														<td height="24" align="center" valign="middle" >
														
															<s:property value="deptName"/>
															&nbsp;
														</td>
														<td height="24" align="center" valign="middle" >
														
															<s:if test="inOffice">
																在任
															</s:if>
															<s:else>
																不在任
															</s:else>
															&nbsp;
														</td>
														<td height="24" align="center" valign="middle">
														
															<s:property value="remark"/>
															&nbsp;
														</td>
													</tr>
												
												
										</s:iterator>
						
							</tbody>
						</table>
						
				</td>
			</tr>
			
			 <tr>
					<td  height="30"  align="right" valign="middle">
								<html:submit property="add" styleClass="button_nor" onclick="javascript:window.open('addOrUpdateManager!input.action','_self');"> 
									<bean:message key="button.add" />
								</html:submit>
								
							</td>
						</tr>
		</table>
	</body>
</center>

