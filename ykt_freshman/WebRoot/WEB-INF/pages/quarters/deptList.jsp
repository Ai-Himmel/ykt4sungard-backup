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
					<s:form action="listDept!delete" namespace="/quarters">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<tbody>
								<tr align="center" valign="middle">
									<td width="24" height="24" valign="middle" class="tableHeader2">
										<input type="checkbox" name="checkSwitch" onclick="selectIns();">
									</td>
									<td height="24" valign="middle" class="tableHeader">
										部门名称
									</td>
									<td valign="middle" class="tableHeader">
										数据权限
									</td>
									
								</tr>
								
								<s:iterator value="depts" status="status">
									
														<s:url id="chuli" action="addOrUpdateDept!input" namespace="/quarters">	
		          		  									<s:param name="dept.id"><s:property value="id"/></s:param>
		          		  								</s:url>
												<s:if test="#status.isEven()">
													<tr align="center" valign="middle" bgcolor="#FFFFFF">
														<td align="center" valign="middle" >
															<input type="checkbox" name="deleteX" value='<s:property value="id"/>' />
														</td>
														<td height="24" align="center" valign="middle" >
														
															<s:a href="%{chuli}"><s:property value="name"/></s:a>
															&nbsp;
														</td>
														<td height="24" align="center" valign="middle">
															<s:property value="right"/>
															&nbsp;
														</td>
													</tr>
												</s:if>
												<s:else>
													<tr align="center" valign="middle" bgcolor="#F6F4F5">
														<td align="center" valign="middle">
															<input type="checkbox" name="deleteX" value='<s:property value="id"/>'  />
														</td>
														<td height="24" align="center" valign="middle">
															<s:a href="%{chuli}"><s:property value="name"/></s:a>
															&nbsp;
														</td>
														<td height="24" align="center" valign="middle">
															<s:property value="right"/>
															&nbsp;
														</td>
													</tr>
												</s:else>
										</s:iterator>
							</tbody>
						</table>
						<tr>
							<td height="30" align="right" valign="middle">
								<html:submit property="add" styleClass="button_nor" onclick="document.forms[0].action='addOrUpdateDept!input.action'"> 
									<bean:message key="button.add" />
								</html:submit>
								<html:submit property="delete" styleClass="button_nor" onclick="javascript:return ondelete();">
									<bean:message key="button.delete" />
								</html:submit>
							</td>
						</tr>
					</s:form>
				</td>
			</tr>
		</table>
	</body>
</center>


<script language="JavaScript">
	 	
	
 
	 function ondelete(){ 
	 	if(document.all.deleteX!=null){
	 		if(document.all.deleteX.length==null){
	 			if(document.all.deleteX.checked==true){
	 				if(!confirm("是否确定要删除？")){
			 			return false;
			 		}
	 				return true;
	 			}else{	 
	 				alert("请先选择要删除的对象");			
	 				return false;
	 			}
	 		}	
			 for(i=0;i<document.all.deleteX.length;i++){
			 	if(document.all.deleteX[i].checked==true){
			 		if(!confirm("是否确定要删除？")){
			 		return false;
			 		}
			 		return true;
			 	}else{
			 		continue;
			 	}	 			
			 }	
			 	alert("请先选择要删除的对象");
		 		return false;
		 }else{
		 		alert("没有可删除的对象");
		 		return false;
		 }
	 } 
	 
	

</script>
