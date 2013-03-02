<%@page pageEncoding="UTF-8"%>
<%@ page import="org.king.classmanage.web.help.MajorinWithStuCount"%>
<%@ page import="java.util.List"%>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="org.king.classmanage.domain.Collegemodel" %>
<%@ include file="../tiles/include.jsp"%>

<script language="JavaScript">
function clearAll(){

	document.all("graduateNoSearch").value="";
	document.all("graduateNameSearch").value="";
	
		document.all("studentTypeSearch").value="";
	document.all("matriculateTypeSearch").value="";
	
		document.all("curCollegeSearch").value="";
	document.all("specialitySearch").value="";
}
function queding(){
    dormAppSearchForm.action = "<c:url value="/dormAppAction.do"/>?method=updateGzDormAppModify";
	dormAppSearchForm.submit();
}
function doSearch(){
    dormAppSearchForm.action = "<c:url value="/dormAppAction.do"/>?method=loadGzList4Need";
	dormAppSearchForm.submit();
}

function NotExport(){
	document.all("export").value='';
}
function DoExport(){
	document.all("export").value='export';
	document.forms[0].submit();
}
	 function my_onload(){	 	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		} 	
	 }
	 window.onload=my_onload;
</script>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">新生住宿名单筛选</font></strong>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="right" valign="middle">
					<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
				</td>
			</tr>
			
			<tr>
				<td align="center" height="10">

				</td>
			</tr>
			<tr>
				<td height="40" align="left" valign="top" class="medium">

						<table width=100% border=1 align="left" cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=resetFrom>
							<tbody>
							
			<tr>
				<td align="center" valign="top">
					<html:form action="dormAppAction.do?method=loadGzList4Need">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>

							<tbody>

<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">学号</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">
										<html:text styleClass="input_box" property="graduateNoSearch" />
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">姓名</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">
										<html:text styleClass="input_box" property="graduateNameSearch" />
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">性别</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">

												<html:select property="studentTypeSearch" styleClass="select01" style="width:120">
													<html:option value="">--------------------</html:option>
													<html:options collection="sexLi" property="id.dictValue" labelProperty="dictCaption" />
												</html:select>

									</td>
								</tr>
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">所在区县</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">

												<html:select property="matriculateTypeSearch" styleClass="select01" style="width:120">
													<html:option value="">--------------------</html:option>
													<html:options collection="qxLi" property="id.dictValue" labelProperty="dictCaption" />
												</html:select>

									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">班级</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">

												<html:select property="curCollegeSearch" styleClass="select01" style="width:120">
													<html:option value="">--------------------</html:option>
													<html:options collection="classLi" labelProperty="classNo" property="classId"  />
												</html:select>

									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">是否参与自动分配</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">

												<html:select property="specialitySearch" styleClass="select01" style="width:120">
													<html:option value="">--------------------</html:option>
													<html:option value="1">是</html:option>													
													<html:option value="0">否</html:option>
												</html:select>
									</td>
								</tr>
							</tbody>
						</table>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<html:submit property="search" styleClass="button_nor" onclick="javascript:NotExport();">
									<bean:message key="button.query" />
								</html:submit>
								<html:button property="reset" styleClass="button_nor" onclick="clearAll();">
									<bean:message key="button.reset" />
								</html:button>
							</td>
						</tr>
							<tr>
								<td>
									<INPUT type="hidden" name="export" value="">
								</td>
							</tr>						
					</html:form>
				</td>
			</tr>
			<tr><td align="center" valign="top">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
								<html:form action="dormAppAction.do?method=updateGzDormAppModify">
								<tr class="tableHeader">
									<td align="center" valign="middle" class="medium" width="12%">
										学号
									</td>
									<td align="center" valign="middle" class="medium" width="12%">
										姓名
									</td>
									<td align="center" valign="middle" class="medium" width="10%">
										性别
									</td>
									<td align="center" valign="middle" class="medium" width="32%">
										目前详细住址
									</td>
									<td align="center" valign="middle" class="medium" width="16%">
										是否申请住宿




									</td>
									<td align="center" valign="middle" class="medium" width="18%">
										是否参与住宿自动分配
									</td>
								</tr>


								<logic:present name="graduateList" scope="request">
									<%int graduateCount = ((Integer) request.getAttribute("graduateCount")).intValue();%>
									<!--page offset start -->
									<pg:pager url="./dormAppAction.do" items="<%=graduateCount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
										<%-- keep track of preference --%>
										<pg:param name="method" />
										<pg:param name="graduateNoSearch" />
										<pg:param name="graduateNameSearch" />
										<pg:param name="page" />
										<pg:param name="orderby" />
										<pg:param name="sort" /> 

										<%-- save pager offset during form changes --%>
										<input type="hidden" name="pager.offset" value="<%= offset %>">
									<logic:iterate name="graduateList" id="graduate" indexId="i">
									<pg:item>
										<tr align="center" valign="middle">
										<c:if test="${i%2 == 0}">
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="graduateNo" />">
												<bean:write name="graduate" property="stuNo" />
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="graduateName" />">
												<bean:write name="graduate" property="stuName" />
											</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="studentType" />">
													<c:if test="${graduate.gender=='1'}">
													男

													</c:if>
													<c:if test="${graduate.gender=='2'}">
													女

													</c:if>
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="matriculateType" />">
													<bean:write name="graduate" property="curAddress" />
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
												    <input type="hidden" name="itemlist" value="<bean:write name="graduate" property="id" />"/>
													<c:if test="${graduate.ifNeedDorm=='1'}">
													是




													</c:if>
													<c:if test="${graduate.ifNeedDorm=='0'}">
													否




													</c:if>
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
												    <input type="hidden" name="itemlist" value="<bean:write name="graduate" property="id" />"/>    
												    <c:if test="${graduate.ifGiveDorm==null}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />" >
													</c:if>
													<c:if test="${graduate.ifGiveDorm=='0'}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />" >
													</c:if>
													<c:if test="${graduate.ifGiveDorm=='1'}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />" checked>
													</c:if>
												</td>
											</c:if>
											
											<c:if test="${i%2 != 0}">
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="graduateNo" />">
												<bean:write name="graduate" property="stuNo" />
											</td>
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="graduateName" />">
												<bean:write name="graduate" property="stuName" />
											</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="studentType" />">
													<c:if test="${graduate.gender=='1'}">
													男

													</c:if>
													<c:if test="${graduate.gender=='2'}">
													女

													</c:if>
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="matriculateType" />">
													<bean:write name="graduate" property="curAddress" />
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
												    <input type="hidden" name="itemlist" value="<bean:write name="graduate" property="id" />"/>
													<c:if test="${graduate.ifNeedDorm=='1'}">
													是




													</c:if>
													<c:if test="${graduate.ifNeedDorm=='0'}">
													否



													</c:if>
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
												    <input type="hidden" name="itemlist" value="<bean:write name="graduate" property="id" />"/>
												    <c:if test="${graduate.ifGiveDorm==null}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />" >
													</c:if>
													<c:if test="${graduate.ifGiveDorm=='0'}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />" >
													</c:if>
													<c:if test="${graduate.ifGiveDorm=='1'}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />" checked>
													</c:if>
												</td>
											</c:if>
										</tr>
										</pg:item>
									</logic:iterate>
									<jsp:include page="./page.jsp" flush="true" />

</table>
<table width="100%">	
  <tr> 
    <td height="24" align="left" valign="middle">
        <jsp:include page="./pagenoexcel.jsp" flush="true" />
    </td>
  </tr>					
</table> 
</td></tr>
									</pg:pager>
								</logic:present>
  <tr> 
    <td height="40" align="left" valign="middle">
        <%
        int rowcount=0;
        if(request.getAttribute("graduateCount")!=null){
        	rowcount=((Integer)request.getAttribute("graduateCount")).intValue();
        %>       
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
        <%} %>
    </td>
  </tr>	
							</tbody>
						</table>
						<tr>
							<td height="30" align="right" valign="middle">
								<html:submit property="next" styleClass="button_nor">
									<bean:message bundle="classmanage" key="studentsearch.sure" />
								</html:submit>
							</td>
						</tr>
					</html:form>
		</table>
	</body>
</center>

