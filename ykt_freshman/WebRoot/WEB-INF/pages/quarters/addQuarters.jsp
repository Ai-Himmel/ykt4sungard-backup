<%@ page pageEncoding="UTF-8"%>
<%@ include file="/WEB-INF/pages/include/style.jsp"%>
<%@ include file="/WEB-INF/pages/tiles/include.jsp"%>
<html>
<head>

<META http-equiv="Content-Type" content="text/html; charset=UTF-8">
<script type="text/javascript" src="<c:url value='/pages/scripts/selectbox.js'/>" ></script>
<script type="text/javascript" src="<c:url value='/pages/scripts/global.js'/>"></script>
<script type='text/javascript' src='<s:url value="/dwr/engine.js"/>'> </script>
  
  <script type='text/javascript' src='<s:url value="/dwr/interface/QuartersMaintain.js"/>'></script>
  <script type='text/javascript' src='<s:url value="/dwr/util.js"/>'> </script>
</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium"><bean:message bundle="dormitorymanage" key="dormitoryResource.dormitoryResource" /></font></strong>
			</td>
		</tr>
		
		<tr>
			<td align="center" valign="top">
				<s:form action="addOrUpdateQuarters!addOrUpdate" namespace="/quarters">
						<s:if test="model != null && model.dormitoryId != null">
							<s:hidden name="model.dormitoryId"/>
						</s:if>
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
						
						<tbody>
							<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">校区</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<s:select id="area" name="model.area" 
										 headerKey="" 
										headerValue="-----------------------"
										listKey="id" listValue="name"  list="areas==null?{}:areas"
										 onchange="QuartersMaintain.setLocations(dwr.util.getValue($('area')));"/>
										 <font color="red"><s:property value='fieldErrors["model.area"][0]'/></font>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">区域</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:select id="location" name="model.location" headerKey="" 
										headerValue="-----------------------" listKey="id" listValue="name" list='locations== null ?{}:locations'
										 onchange="QuartersMaintain.setDormitory(dwr.util.getValue($('location')));"/>
										 <font color="red"><s:property value='fieldErrors["model.location"][0]'/></font>
									</td>
								</tr>
								
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">楼号</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<s:select id="dormitory" name="model.dormitory" headerKey="" 
										headerValue="-----------------------" listKey="id" listValue="name" list='dormitorys==null?{}:dormitorys'/>
										<font color="red"><s:property value='fieldErrors["model.dormitory"][0]'/></font>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">单元号</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.unit"/>
									</td>
								</tr>
								
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">层号</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<s:select id="dormitory" name="model.level" listKey="id" listValue="name" list='levels==null?{}:levels'/>
										<font color="red"><s:property value='fieldErrors["model.level"][0]'/></font>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">电话</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.telphone"/>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">朝向</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<s:select id="dormitory" name="model.direction"  listKey="id" listValue="name" list='directions==null?{}:directions'/>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">费用</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.fee"/>
									</td>
								</tr>

								<tr align="center" valign="middle">

									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">入住性别</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:select  name="model.gender" 
										listKey="id" listValue="name"
										 list="sexs"/>
									</td>
									<td align="left" valign="middle" class="tableHeader2">
										宿舍号
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.roomNumber"/>
										<font color="red"><s:property value='fieldErrors["model.roomNumber"][0]'/></font>
									</td>
								</tr>
								
								<tr align="center" valign="middle">

									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">床位数</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.accomodation" />
									</td>
									<td align="left" valign="middle" class="tableHeader2">
										可分配床数
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.distributeNum"/>
										<font color="red"><s:property value='actionErrors[0]'/></font>
									</td>
								</tr>
								<tr align="center" valign="middle">

									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">使用部门</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:select name="model.curDormDept" list='depts'/>
									</td>
									<td align="left" valign="middle" class="tableHeader2">
										&nbsp;
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										&nbsp;
										
									</td>
								</tr>
						</tbody>
					</table>
					<tr>
						<td height="40" align="right" valign="middle" class="tdborder02">
							<s:if test="model != null && model.dormitoryId  != null">
								<s:submit value="修改" cssClass="button_nor"></s:submit>
							</s:if>
							<s:else>
								<html:submit property="add" styleClass="button_nor" >
									<bean:message key="button.add" />
								</html:submit>
							</s:else>
							
						</td>
					</tr>
				</s:form>
			</td>
		</tr>
	</table>
</body>
</html>
