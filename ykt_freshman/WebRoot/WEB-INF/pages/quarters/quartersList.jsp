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
function clearContent(obj){
	var els = obj.elements;
	
	for(var i=0;i<els.length;i++) {
	     if (els[i].type !='submit' && els[i].type !='button' && els[i].type !='reset')  
		 els[i].value = "";
	}
	
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
					<strong><font class="medium"><s:property value="dept.name"/><bean:message bundle="dormitorymanage" key="dormitoryResource.dormitoryResource" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<s:form action="listQuarters!search" namespace="/quarters">
					    <input type="hidden" name="type"/>
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
							
							<tbody>

								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">校区</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<s:select id="area" name="model.area" 
										listKey="id" listValue="name" headerKey="" 
										headerValue="-----------------------" list="areas==null?null:areas"
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
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">层号</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
									<s:select id="dormitory" name="model.level" headerKey="" 
										headerValue="-----------------------" listKey="id" listValue="name" list='levels==null?{}:levels'/>
										
									</td>
									
								</tr>
								
								<tr align="center" valign="middle">
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">单元号</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.unit"/>
									</td>
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">朝向</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										
										<s:select id="dormitory" name="model.direction" headerKey="" 
										headerValue="-----------------------" listKey="id" listValue="name" list='directions==null?{}:directions'/>
									</td>
								</tr>
								

								<tr align="center" valign="middle">

									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">入住性别</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										
										<s:select  name="model.gender" 
										listKey="id" listValue="name" headerKey="" 
										headerValue="-----------------------" list="sexs"/>
									</td>
									<td align="left" valign="middle" class="tableHeader2">
										宿舍号
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.roomNumber"/>
									</td>
								</tr>
							</tbody>
						</table>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<html:submit property="search" styleClass="button_nor" onclick="this.form.type.value='dofind';">
									<bean:message key="button.query" />
								</html:submit>
								<input type="button" class="button_nor" value="重置" onclick="clearContent(this.form);">
								<html:submit property="search" styleClass="button_nor" onclick="this.form.type.value='doexl';">
									导出
								</html:submit>	
								</input>	
								
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
							<tbody>
								<tr align="center" valign="middle">
									
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
										层号
									</td>
									<td valign="middle" class="tableHeader">
										单元号
									</td>
									<td valign="middle" class="tableHeader">
										宿舍号
									</td>
									<td valign="middle" class="tableHeader">
										入住性别
									</td>
									<td valign="middle" class="tableHeader">
										床位数
									</td>
									
									<td valign="middle" class="tableHeader">
										可分配床数
									</td>
									
									<td valign="middle" class="tableHeader">
										住宿费(元)
									</td>
									<td valign="middle" class="tableHeader">
										宿舍电话
									</td>
									<td valign="middle" class="tableHeader">
										朝向
									</td>
								</tr>
								
									<!--page offset start -->
									
									
									<%Integer count = (Integer)ActionContext.getContext().getValueStack().findValue("count");%>
									
									<pg:pager url='listQuarters!search.action'
									 items='<%=count.intValue()%>'
									  index="center"
									   maxPageItems="100" 
									   maxIndexPages="10"
									     export="currentPageNumber=pageNumber" scope="request">
										<%-- keep track of preference --%>
										<pg:param name="model.location"/>
										<pg:param name="model.area"/>
										<pg:param name="model.dormitory"/>
										<pg:param name="model.unit"/>
										<pg:param name="model.level"/>
										<pg:param name="model.telphone"/>
										<pg:param name="model.direction"/>
										<pg:param name="model.fee"/>
										<pg:param name="model.gender"/>
										<pg:param name="model.roomNumber"/>

										
										<s:iterator value="quarters" status="status">
											
												<s:if test="#status.isEven()">
													<tr align="center" valign="middle" bgcolor="#FFFFFF">
												</s:if>		
												<s:else>
													<tr align="center" valign="middle" bgcolor="#F6F4F5">
												</s:else>
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
															<s:property value="level"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="unit"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:url id="updateLink" action="addOrUpdateQuarters!input" namespace="/quarters">
																<s:param name="model.dormitoryId"><s:property value="dormitoryId"/></s:param>
															</s:url>
															<s:a href='%{updateLink}'>
															<s:property value="roomNumber"/></s:a>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="gender"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="accomodation"/>
														</td>
														
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="distributeNum"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="fee"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="telphone"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="direction"/>
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
									
								
							</tbody>
						</table>
	</td>					
	</tr>	
	<tr> 
    <td>
              
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
    </td>
  </tr>		
  </pg:pager>			
  <tr> 
    <td height="40" align="left" valign="middle">
              
        <font color="#000000" size="2.5">共<s:property value="count"/>条记录</font>
        
    </td>
  </tr>	
		</s:if>	
		<tr>
							<td height="30" align="right" valign="middle">
								<html:submit property="add" styleClass="button_nor" onclick="javascript:window.open('addOrUpdateQuarters!input.action','_self');">
									<bean:message key="button.add" />
								</html:submit>
								
							</td>
						</tr>
					
				</td>
			</tr>
		</table>
	</body>
</center>


