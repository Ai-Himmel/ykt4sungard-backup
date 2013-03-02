<%@ page pageEncoding="GBK"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.Classmodel"%>
<%@ include file="../tiles/include.jsp"%>
<center>
<% String msg=(String)request.getAttribute("msg");
if(msg!=null)
{
%>
<script language="javascript">
	alert('<%=msg%>');
</script>
<%}%>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="classmanage" key="class.classmanage" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>

			<tr>
				<td align="center" valign="top">
					<html:form action="classAction.do?method=load4Search">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
							<tr>
								<td>
									<%if (request.getAttribute("myclass") != null) {
				String myclass = request.getAttribute("myclass").toString();

				%>
									<INPUT type="hidden" name="myclass" value="<%=myclass%>">
									<%} else {

			%>
									<INPUT type="hidden" name="myclass" value="">

									<%}

			%>
								</td>
							</tr>
							<tr>
								<td>
									<INPUT type="hidden" name="export" value="">
								</td>
							</tr>
							<tbody>
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<bean:message bundle="classmanage" key="class.college" />
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="college" onchange="changeCollge(this.value)">
											<html:option value="">-----------------------</html:option>
											<html:options collection="collegeList" labelProperty="collegeName" property="collegeId" />
										</html:select>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="class.name" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="classmodel.classId">
											<html:option value="">-----------------------</html:option>
											<html:options collection="classList" labelProperty="classNo" property="classId" />
										</html:select>
									</td>

								</tr>
								<tr align="center" valign="middle">
									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="class.assistant" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="assistant">
											<html:option value="">-----------------------</html:option>
											<html:options collection="assistantList" labelProperty="managerName" property="managerId" />
										</html:select>
									</td>
									<td align="left" valign="middle" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="class.tutor" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="tutor1">
											<html:option value="">-----------------------</html:option>
											<html:options collection="tutorList" labelProperty="managerName" property="managerId" />
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
					</html:form>
				</td>
			</tr>
			<tr>
				<td height="20" align="left" valign="middle" class="medium">
					<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
				</td>
			</tr>
			<tr>
				<td height="40" align="center" valign="top">
					<html:form action="classAction.do?method=delete">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<tbody>

								<tr align="center" valign="middle">
									<td width="24" height="24" valign="middle" class="tableHeader2">
										<input type="checkbox" name="checkSwitch" onclick="selectIns();">
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="class.name" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="class.college" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="class.assistant" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="class.tutor1" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="class.org" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="class.tutor2" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="classmanage" key="class.org" />
									</td>
								</tr>

								<logic:present name="classmodels" scope="request">
									<%int itemNo = ((Integer) request.getAttribute("classCount"))
					.intValue();%>
									<pg:pager url="./classAction.do" items="<%=itemNo%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%=true%>" export="offset,currentPageNumber=pageNumber" scope="request">
										<%-- keep track of preference --%>
										<pg:param name="method" />
										<pg:param name="college" />
										<pg:param name="classmodel.classId" />
										<pg:param name="assistant" />
										<pg:param name="tutor1" />
										<pg:param name="tutor2" />
										<pg:param name="page" />
										<pg:param name="orderby" />
										<pg:param name="sort" />

										<%-- save pager offset during form changes --%>
										<input type="hidden" name="pager.offset" value="<%= offset %>">
										<logic:iterate name="classmodels" id="classwithrole" indexId="i">
											<pg:item>
												<c:if test="${i%2 == 0}">
													<tr align="center" valign="middle">
												</c:if>
												<c:if test="${i%2 != 0}">
													<tr align="center" valign="middle" bgcolor="#F6F4F5">
												</c:if>
													
														<td height="24" align="center" valign="middle">
															<input type="checkbox" name="deleteX" value="<bean:write name="classwithrole" property="classId"/>">
														</td>
														<td align="center" valign="middle">
															<a href="classAction.do?method=load4Edit&classId=<bean:write name="classwithrole" property="classId"/>"><bean:write name="classwithrole" property="classNo" /></a>
														</td>
														<td align="center" valign="middle">
															<bean:write name="classwithrole" property="collegeName" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="classwithrole" property="assistantName" />
															&nbsp;
														</td>
														<td align="center" valign="middle" >
															<bean:write name="classwithrole" property="tutor1Name" />
															&nbsp;
														</td>
														<td align="center" valign="middle" >
															<bean:write name="classwithrole" property="tutor1org" />
															&nbsp;
														</td>
														<td align="center" valign="middle" >
															<bean:write name="classwithrole" property="tutor2Name" />
															&nbsp;
														</td>
														<td align="center" valign="middle" >
															<bean:write name="classwithrole" property="tutor2org" />
															&nbsp;
														</td>									
													</tr>												
											</pg:item>
										</logic:iterate>
										<jsp:include page="./page.jsp" flush="true" />
									</pg:pager>
								</logic:present>
							</tbody>
						</table>
  <tr> 
    <td height="40" align="left" valign="middle">
        <%
        int rowcount=0;
        if(request.getAttribute("listcount")!=null){
        	rowcount=((Integer)request.getAttribute("listcount")).intValue();
        %>       
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
        <%} %>
    </td>
  </tr>					
						<tr>
							<td height="30" align="right" valign="middle">
								<html:submit property="add" styleClass="button_nor" onclick="document.forms[1].action='classAction.do?method=load4Add'">
									<bean:message key="button.add" />
								</html:submit>
								<html:submit property="delete" styleClass="button_nor" onclick="javascript:return ondelete();">
									<bean:message key="button.delete" />
								</html:submit>
							</td>
						</tr>
					</html:form>
				</td>
			</tr>
		</table>
	</body>
</center>

<script language="JavaScript">
function clearAll(){
	document.all("college").value="";
	document.all("classmodel.classId").value="";
	document.all("assistant").value="";
	document.all("tutor1").value="";

}
<!-- class list -->
	var classescount;
	classescount = 0;
	classes = new Array(); 
	<%	
		ArrayList classeslist=(ArrayList)request.getAttribute("classList");		
		int i = 0;
		for(i=0;i<classeslist.size();i++){
			Classmodel classmodel = (Classmodel)classeslist.get(i);
			String classid=classmodel.getClassId();
			String className=classmodel.getClassName();	
			String classNo=classmodel.getClassNo();
			String collegeId = classmodel.getYxCollege().getCollegeId();
	%>
			classes[<%=i%>]= new Array("<%=classid%>","<%=classNo%>","<%=collegeId%>"); 
	<%	
		}	
	%>
	classescount=<%=classeslist.size()%>
	

	function changeCollge(college){
	 	document.all("classmodel.classId").length=0;
	 	var collegeId=college; 
		var j; 
		document.all("classmodel.classId").options[document.all("classmodel.classId").length]=new Option("-----------------------","");
		for (j=0; j<classescount; j++) 
		{ 
			if ((classes[j][2] == collegeId)||(collegeId=="")) 
			{ 
				document.all("classmodel.classId").options[document.all("classmodel.classId").length]= new Option(classes[j][1],classes[j][0]);
			} 
		} 
		
	 }
	 
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
	 
	 function DoExport(){
	 	document.all("export").value='export';
	 	document.forms[0].submit();
	 }
	 function NotExport(){
	 	document.all("export").value='';
	 }
	 
	 function my_onload(){

	 	if(document.all("college").value!=""){
		 	document.all("classmodel.classId").length=0;
			var j; 
			document.all("classmodel.classId").options[document.all("classmodel.classId").length]=new Option("-----------------------","");
			for (j=0; j<classescount; j++) 
			{ 
				if (classes[j][2] == document.all("college").value) 
				{ 
					document.all("classmodel.classId").options[document.all("classmodel.classId").length]= new Option(classes[j][1],classes[j][0]);
					if(classes[j][0]==document.all("myclass").value){
						document.all("classmodel.classId").options[document.all("classmodel.classId").length-1].selected=true;
					}
				} 
			} 
	 	}	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	 }
	 
	 window.onload=my_onload;	 

</script>
