<%@ page pageEncoding="UTF-8"%>
<%@ include file="/WEB-INF/pages/include/style.jsp"%>
<%@ include file="/WEB-INF/pages/tiles/include.jsp"%>
<script type="text/javascript" src="<c:url value='/pages/scripts/selectbox.js'/>" ></script>
<script type="text/javascript" src="<c:url value='/pages/scripts/global.js'/>" charset="gbk"></script>
<script type='text/javascript' src='<s:url value="/dwr/engine.js"/>'> </script>
  
  <script type='text/javascript' src='<s:url value="/dwr/interface/ManagerMaintain.js"/>'></script>
  <script type='text/javascript' src='<s:url value="/dwr/util.js"/>'> </script>
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
					<s:form action="addOrUpdateManager!addOrUpdate" namespace="/quarters">
						
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<tbody>
							    <s:if test="manager != null && manager.id != null">
							       <s:hidden name="manager.id"/>
							   
								<tr align="center" valign="middle">
								
									<td height="24" valign="middle" class="tableHeader2">
										学号/工号
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									 <s:textfield  readonly="true" id="stuNo" name="manager.stuNo" cssClass="input_box_stu"/>
									 
									</td>
								</tr>
								
								<tr align="center" valign="middle">
								
									<td height="24" valign="middle" class="tableHeader2">
										姓名
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									<s:textfield id="userName" name="manager.name" readonly="true" cssClass="input_box_stu"/>
									</td>
								</tr>
								<tr align="center" valign="middle">
								
									<td height="24" valign="middle" class="tableHeader2">
										性别
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									<s:select  id="sex" name="manager.sex" list='#{"1":"男","2":"女"}' disabled="true"/>
									</td>
								</tr>	
						      </s:if>
						      <s:else>
						      
								<tr align="center" valign="middle" >
								<td  colspan="2" valign="middle" align="center">
									<font color="red">
									 <div id ="message" >&nbsp;</div>
									</font>	
								</td>
								</tr>
								<tr align="center" valign="middle">
								
									<td height="24" valign="middle" class="tableHeader2">
										学号/工号
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									 <s:textfield  id="stuNo" name="manager.stuNo" cssClass="input_box_stu"/><font color="red">*</font>
									 <input type="button" value="搜索" onclick="ManagerMaintain.setPersonInfo(dwr.util.getValue($('stuNo')));" class="button_nor"></input>
									</td>
								</tr>
								
								<tr align="center" valign="middle">
								
									<td height="24" valign="middle" class="tableHeader2">
										姓名
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									<s:textfield id="userName" name="manager.name" cssClass="input_box_stu"/>
									</td>
								</tr>
								<tr align="center" valign="middle">
								
									<td height="24" valign="middle" class="tableHeader2">
										性别
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									<s:select id="sex" name="manager.sex" list='#{"1":"男","2":"女"}'/>
									</td>
								</tr>	
							 </s:else>	
								<tr align="center" valign="middle">
								
									<td height="24" valign="middle" class="tableHeader2">
										联系方式
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									<s:textfield name="manager.contact" cssClass="input_box_stu"/>
									</td>
								</tr>	
									
								<tr align="center" valign="middle">
									<td valign="middle" class="tableHeader2">
										宿舍使用部门
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									<s:select name="manager.tabSsDept.id" list='depts'/>
								</td>
								</tr>
								<tr align="center" valign="middle">
									<td valign="middle" class="tableHeader2">
										是否在任
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									<s:select name="manager.inOffice" list='#{true:"在任",false:"不在任"}'/>
								</td>
								</tr>
								<tr align="center" valign="middle">
								
									<td height="24" valign="middle" class="tableHeader2">
										备注
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									<s:textarea name="manager.remark"/><font color="red">(不能超过100个字符)</font>
									</td>
								</tr>	
								
							</tbody>
						</table>
						<tr>
							<td height="30" align="right" valign="middle">
							<s:if test="manager != null && manager.id != null">
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


