<%@ page pageEncoding="UTF-8"%>

<%@ page import="com.opensymphony.xwork.ActionContext"%>
<%@ include file="/WEB-INF/pages/include/style.jsp"%>
<%@ include file="/WEB-INF/pages/tiles/include.jsp"%>
<script type="text/javascript" src="<c:url value='/pages/scripts/selectbox.js'/>" ></script>
<script type="text/javascript" src="<c:url value='/pages/scripts/global.js'/>"></script>
 <script type='text/javascript' src='<s:url value="/dwr/engine.js"/>'> </script>
  
  <script type='text/javascript' src='<s:url value="/dwr/interface/QuartersMaintain.js"/>'></script>
  <script type='text/javascript' src='<s:url value="/dwr/util.js"/>'> </script>

<script language="JavaScript">
function clearAll(){

	document.all("dormitory.location").value="";
	document.all("dormitory.dormitory").value="";
	document.all("dormitory.gender").value="";
	document.all("dormitory.roomNumber").value="";
}

function document.onkeydown(){

	var e=event.srcElement;
	if(event.keyCode==13){
	
		document.all("search").click();
		return false;
	}
}
</script>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" >
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><s:property value="dept.name"/>通知单管理</font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<s:form action="listNoticeStudent!search" namespace="/quarters" >
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
							
							<tbody>
								
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">校区</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<s:select id="area" name="model.area" 
										listKey="id" listValue="name" headerKey="" 
										headerValue="-----------------------" list="areas==null?{}:areas"
										 onchange="QuartersMaintain.setLocations(dwr.util.getValue($('area')));"/>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">区域</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:select id="location" name="model.location" headerKey="" 
										headerValue="-----------------------" listKey="id" listValue="name" list='locations== null ?{}:locations'
										 onchange="QuartersMaintain.setDormitory(dwr.util.getValue($('location')));"/>
									</td>
								</tr>
								
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">楼号</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
									 <s:select id="dormitory" name="model.dormitory" headerKey="" 
										headerValue="-----------------------" listKey="id" listValue="name" list='dormitorys==null?{}:dormitorys'/>
										
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">单元号</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.unit" cssClass="input_box_stu"/>
									</td>
								</tr>
								
								<tr align="center" valign="middle">

									
									<td align="left" valign="middle" class="tableHeader2">
										宿舍号
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.roomNumber" cssClass="input_box_stu"/>
									</td>
									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">&nbsp;每页显示行数</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="pageSize" cssClass="input_box_stu"/>
									</td>
								</tr>
								<tr align="center" valign="middle">

									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">院系</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										
										<s:select id="college" name="model.college" 
										listKey="id" listValue="name" headerKey="" 
										headerValue="-----------------------" list="depts==null?{}:depts" 
										
										/>
									</td>
									<td align="left" valign="middle" class="tableHeader2">
										专业
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:select id="majors" name="model.majors" 
										 listKey="id" listValue="name" headerKey="" 
										 headerValue="-----------------------"
										 list="majorList==null?{}:majorList"/>
									</td>
								</tr>
								<tr align="center" valign="middle">

									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">学号</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.stuNo" cssClass="input_box_stu"/>
									</td>
									<td align="left" valign="middle" class="tableHeader2">
										姓名
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.name" cssClass="input_box_stu"/>
									</td>
								</tr>
								
							</tbody>
						</table>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<html:submit property="search" styleClass="button_nor">
									<bean:message key="button.query" />
								</html:submit>
								<html:button property="reset" styleClass="button_nor" onclick="clearAll();">
									<bean:message key="button.reset" />
								</html:button>
							</td>
						</tr>
					</s:form>
				</td>
			</tr>
			<s:if test="count > 0">
			<tr>
				<td height="40" align="center" valign="top">
					&nbsp;
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<s:form action="printNotice!printNotice" namespace="/quarters" target="_blank">
							<input type="hidden" name="type"/>
							<tbody>
								<tr align="center" valign="middle">
								     <td width="24" height="24" valign="middle" class="tableHeader2">
										<input type="checkbox" name="checkSwitch" onclick="selectIns();">
									</td>
								    <td height="24" valign="middle" class="tableHeader">
										学号
									</td>
									<td height="24" valign="middle" class="tableHeader">
										姓名
									</td>
									<td valign="middle" class="tableHeader">
										院系
									</td>
									<td valign="middle" class="tableHeader">
										专业
									</td>
									
									<td height="24" valign="middle" class="tableHeader">
										校区
									</td>
									<td height="24" valign="middle" class="tableHeader">
										区域
									</td>
									<td valign="middle" class="tableHeader">
										楼号
									</td>
									<td valign="middle" class="tableHeader">
										单元号
									</td>
									<td valign="middle" class="tableHeader">
										宿舍号
									</td>
									
									<td valign="middle" class="tableHeader">
										住宿费
									</td>
									
									
								</tr>
								
									<!--page offset start -->
									<%
										Integer count = (Integer)request.getAttribute("count");
										Integer pageSize = (Integer)request.getAttribute("pageSize");
									%>
									
									<pg:pager url='listNoticeStudent!search.action'
									 items='<%=count.intValue()%>'
									  index="center"
									   maxPageItems="<%=pageSize.intValue()%>" 
									   maxIndexPages="10"
									     export="currentPageNumber=pageNumber" scope="request">
										<%-- keep track of preference --%>
										<pg:param name="model.location"/>
										<pg:param name="model.area"/>
										<pg:param name="model.dormitory"/>
										<pg:param name="model.unit"/>
										<pg:param name="model.roomNumber"/>
										<pg:param name="model.college"/>
										<pg:param name="model.majors"/>
										<pg:param name="model.stuNo"/>
										<pg:param name="model.name"/>
										<pg:param name="pageSize"/>

										
										<s:iterator value="students" status="status">
											
												<s:if test="#status.isEven()">
													<tr align="center" valign="middle" bgcolor="#FFFFFF">
												</s:if>		
												<s:else>
													<tr align="center" valign="middle" bgcolor="#F6F4F5">
												</s:else>
												        <td align="center" valign="middle">
															<input type="checkbox" name="deleteX" value='<s:property value="id"/>' />
														</td>
														<td height="24" align="center" valign="middle">
															<s:property value="stuNo"/>
															&nbsp;
														</td>
														<td height="24" align="center" valign="middle">
															<s:property value="name"/>
															&nbsp;
														</td>
														<td height="24" align="center" valign="middle">
															<s:property value="college"/>
															&nbsp;
														</td>
														<td height="24" align="center" valign="middle">
															<s:property value="majors"/>
															&nbsp;
														</td>
														<td height="24" align="center" valign="middle">
															<s:property value="area"/>
															&nbsp;
														</td>
														<td align="center" valign="middle">
															&nbsp;
														   <s:property value="location"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="dormitory"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="unit"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="roomNumber"/>
														</td>
														
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="fee"/>
														</td>
														
													</tr>
												
												
										
										</s:iterator>
											
											<pg:index export="total=itemCount">
<pg:first>
  <a href="<%=pageUrl%>&pageNo=<%=pageNumber%>"><nobr>[<bean:message key="page.first"/>]</nobr></a>
</pg:first>
<pg:skip pages="<%= -10 %>">
  <a href="<%=pageUrl%>&pageNo=<%=pageNumber%>"><nobr>[<bean:message key="page.uper"/>]</nobr></a>
</pg:skip>
<pg:prev>
  <a href="<%=pageUrl%>&pageNo=<%=pageNumber%>">[<bean:message key="page.prev"/>]</nobr></a>
</pg:prev>
<pg:pages>
<% if (pageNumber == currentPageNumber) { %> 
[<%= pageNumber %>]
<% } else { %>
   <a href="<%=pageUrl%>&pageNo=<%=pageNumber%>"><%= pageNumber %></a> 
<% } %>
</pg:pages>
<pg:next>
  <a href="<%=pageUrl%>&pageNo=<%=pageNumber%>"><nobr>[<bean:message key="page.next"/>]</nobr></a>
</pg:next>
<pg:skip pages="<%= 10 %>">
  <a href="<%=pageUrl%>&pageNo=<%=pageNumber%>"><nobr>[<bean:message key="page.skip"/>]</nobr></a>
</pg:skip>
<pg:last>
  <a href="<%=pageUrl%>&pageNo=<%=pageNumber%>"><nobr>[<bean:message key="page.last"/>]</nobr></a>
</pg:last>
<pg:page export="first,last">
    <%= first %> - <%= last %> / <%= total %>
</pg:page>
</pg:index>
									</pg:pager>
								
							</tbody>
						</table>
	</td>					
	</tr>					
  <tr> 
    <td height="40" align="left" valign="middle">
              
        <font color="#000000" size="2.5">共<s:property value="count"/>条记录</font>
        
    </td>
  </tr>	
		
		<tr>
							<td height="30" align="right" valign="middle">
								<html:submit property="add" styleClass="button_nor" onclick="this.form.type.value=1;return onprint();">
									入住通知单
								</html:submit>
								<html:submit property="add" styleClass="button_nor" onclick="this.form.type.value=2;return onprint();">
									交费通知
								</html:submit>
								<html:submit property="add" styleClass="button_nor" onclick="this.form.type.value=3;return onprint();">
									居住协议
								</html:submit>
							</td>
						</tr>
					
				</td>
			</tr>
			</s:form>
			</s:if>	
		</table>
	</body>
</center>
<script language="JavaScript">
	 function onprint(){ 
	 	if(document.all.deleteX!=null){
	 		if(document.all.deleteX.length==null){
	 			if(document.all.deleteX.checked==true){
	 				if(!confirm("是否确定要打印？")){
			 			return false;
			 		}
	 				return true;
	 			}else{	 
	 				alert("请先选择要打印的对象");			
	 				return false;
	 			}
	 		}	
			 for(i=0;i<document.all.deleteX.length;i++){
			 	if(document.all.deleteX[i].checked==true){
			 		if(!confirm("是否确定要打印？")){
			 		return false;
			 		}
			 		return true;
			 	}else{
			 		continue;
			 	}	 			
			 }	
			 	alert("请先选择要打印的对象");
		 		return false;
		 }else{
		 		alert("没有可打印的对象");
		 		return false;
		 }
	 } 
</script>

