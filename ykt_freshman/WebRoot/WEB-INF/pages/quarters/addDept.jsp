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
					<strong><font class="medium">宿舍使用部门维护</font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			
			<tr>
				<td height="40" align="center" valign="top">
					<s:form action="addOrUpdateDept!addOrUpdate" namespace="/quarters">
						<s:if test="dept != null && dept.id != null">
							<s:hidden name="dept.id"/>
						</s:if>
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<tbody>
								<tr align="center" valign="middle">
								
									<td height="24" valign="middle" class="tableHeader2">
										部门名称
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									<s:textfield name="dept.name" cssClass="input_box_stu"/>
									</td>
								</tr>
									
								<tr align="center" valign="middle">
									<td valign="middle" class="tableHeader2">
										数据权限
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									<s:select name="dept.right" list='{"高职","本科","研究生"}'/>
								</td>
								</tr>
								
							</tbody>
						</table>
						<tr>
							<td height="30" align="right" valign="middle">
							<s:if test="dept != null && dept.id != null">
								<s:submit value="修改" cssClass="button_nor"></s:submit>
							</s:if>
							<s:else>
								<html:submit property="add" styleClass="button_nor" >
									<bean:message key="button.add" />
								</html:submit>
							</s:else>	
								<html:reset property="delete" styleClass="button_nor" >
									重置
								</html:reset>
							</td>
						</tr>
					</s:form>
				</td>
			</tr>
		</table>
	</body>
</center>


