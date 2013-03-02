<%@ page pageEncoding="UTF-8"%>

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
					<strong><font class="medium">研究生相关基本信息查询</font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<s:form action="queryGraduate!query" namespace="/summary">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
							
							<tbody>

									<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">学号</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<s:textfield name="model.stuNo" cssClass="input_box_stu"/>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">姓名</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
									 <s:textfield name="model.stuName" cssClass="input_box_stu"/>	
									</td>
								</tr>
								
									<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">性别</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<s:select name="model.sex" 
										headerKey="" 
										headerValue="-----------------------" list='#{"1":"男","2":"女"}'/>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">民族</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:select  name="model.minZu" headerKey="" 
										headerValue="-----------------------" 
										listKey="id" listValue="name" list='minZus== null ?{}:minZus'/>
									</td>
								</tr>
								
									<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">国籍</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<s:select  name="model.guoJi" 
										listKey="id" listValue="name" headerKey="" 
										headerValue="-----------------------" list="guoJis==null?{}:guoJis"/>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">录取院系</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:select  name="model.yuanXi" headerKey="" 
										headerValue="-----------------------"
										 listKey="id" listValue="name" list='yuanXis== null ?{}:yuanXis'/>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">录取专业</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<s:select  name="model.zhuanYe" 
										listKey="id" listValue="name" headerKey="" 
										headerValue="-----------------------" list="zhuanYes==null?{}:zhuanYes"/>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">学生类别</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<s:select name="model.leiBie" headerKey="" 
										headerValue="-----------------------"
										 listKey="id" listValue="name" list='leiBies== null ?{}:leiBies'
										/>
									</td>
								</tr>
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
									 <s:select id="dormitory" name="model.louHao" headerKey="" 
										headerValue="-----------------------" listKey="id" listValue="name" list='louHaos==null?{}:louHaos'/>
										
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
										<span class="medium">&nbsp;</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										&nbsp;
									</td>
								</tr>
							</tbody>
						</table>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<html:submit property="search" styleClass="button_nor">
									<bean:message key="button.query" />
								</html:submit>
								<input type="button" class="button_nor" value="重置" onclick="clearContent(this.form);">
									
								</input>
							</td>
						</tr>
					</s:form>
				</td>
			</tr>
			
			<tr>
				<td height="40" align="center" valign="top">
					&nbsp;
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<tbody>
								<tr align="center" valign="middle">
									
									<td height="24" valign="middle" class="tableHeader">
										学号
									</td>
									<td height="24" valign="middle" class="tableHeader">
										姓名
									</td>
									<td valign="middle" class="tableHeader">
										性别
									</td>
									<td valign="middle" class="tableHeader">
										民族
									</td>
									<td valign="middle" class="tableHeader">
										国籍
									</td>
									<td valign="middle" class="tableHeader">
										录取院系
									</td>
									<td valign="middle" class="tableHeader">
										录取专业
									</td>
									<td valign="middle" class="tableHeader">
										学生类型
									</td>
									<td valign="middle" class="tableHeader">
										生日
									</td>
									<td valign="middle" class="tableHeader">
										校区
									</td>
									
									<td valign="middle" class="tableHeader">
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
									
								</tr>
						<s:if test="count > 0">		
									<!--page offset start -->
									
									
									<%Integer count = (Integer)request.getAttribute("count");
									  if (count == null) count = new Integer(0);
									%>
									
									<pg:pager url='queryGraduate!query.action'
									 items='<%=count.intValue()%>'
									  index="center"
									   maxPageItems="100" 
									   maxIndexPages="10"
									     export="currentPageNumber=pageNumber" scope="request">
										<%-- keep track of preference --%>
										<pg:param name="model.stuNo"/>
										<pg:param name="model.stuName"/>
										<pg:param name="model.minZu"/>
										<pg:param name="model.guoJi"/>
										<pg:param name="model.yuanXi"/>
										<pg:param name="model.zhuanYe"/>
										<pg:param name="model.leiBie"/>
										
										<pg:param name="model.location"/>
										<pg:param name="model.area"/>
										<pg:param name="model.louHao"/>
										<pg:param name="model.unit"/>
										<pg:param name="model.sex"/>
										<pg:param name="model.roomNumber"/>

										
										<s:iterator value="students" status="status">
											
												<s:if test="#status.isEven()">
													<tr align="center" valign="middle" bgcolor="#FFFFFF">
												</s:if>		
												<s:else>
													<tr align="center" valign="middle" bgcolor="#F6F4F5">
												</s:else>
														<td height="24" align="center" valign="middle">
															<s:property value="STUNO"/>
															&nbsp;
														</td>
														<td align="center" valign="middle">
														&nbsp;
														
														<s:property value="STUNAME"/>
													
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="SEX"/>
														</td>
														
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="MINZU"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="GUOJI"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="YUANXI"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="ZHUANYE"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="LEIBIE"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="BIRTHDAY"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="AREA"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="LOCATION"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="LOUHAO"/>
															
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="UNIT"/>
														</td>
														<td align="center" valign="middle">
															&nbsp;
															<s:property value="ROOMNUMBER"/>
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
  <tr> 
  </pg:pager>
    <td height="40" align="left" valign="middle">
              
        <font color="#000000" size="2.5">共<s:property value="count"/>条记录</font>
        
    </td>
  </tr>	
		</s:if>	
		
			
		</table>
	</body>
</center>


