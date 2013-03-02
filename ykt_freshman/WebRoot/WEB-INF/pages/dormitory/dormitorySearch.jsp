<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.classmanage.domain.Classmodel"%>
<%@ include file="../tiles/include.jsp"%>
<%@ page import="java.util.HashMap"%>

<script language="JavaScript">
function clearAll(){
	document.all("location").value="";
	document.all("dorm").value="";
	document.all("roomNumber").value="";
	document.all("collegeId").value="";
	document.all("classId").value="";
	document.all("managerId").value="";
	document.all("studentNo").value="";
	document.all("stuName").value="";
//	document.all("nation").value="";
	document.all("fromProvince").value="";
	document.all("majorin").value="";
	document.all("enterenceNo").value="";	
	document.all("gender").value="";
}

function document.onkeydown()
{
	var e=event.srcElement;
	if(event.keyCode==13)
	{
		document.all("search").click();
		return false;
	}
}
</script>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium"><bean:message bundle="dormitorymanage" key="dormitorySearch.dormitorySearch" /></font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="top" height="10"></td>
		</tr>
		<tr>
			<td align="center" valign="top">
				<html:form method="post" action="DormitorySearchAction.do?method=searchDetail">
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
							<td>
								<%if (request.getAttribute("mydormitory") != null) {
				String mydormitory = request.getAttribute("mydormitory")
						.toString();

				%>
								<INPUT type="hidden" name="mydormitory" value="<%=mydormitory%>">
								<%} else {

			%>
								<INPUT type="hidden" name="mydormitory" value="">

								<%}

			%>
							</td>
						</tr>
						<tr>
								<td>
									<INPUT type="hidden" name="export" value="">
								</td>
							</tr>
							<tr>
								<td>
									<INPUT type="hidden" name="orderby" value="">
									<INPUT type="hidden" name="sort" value="">
								</td>
							</tr>
						<tbody>
							<tr align="center" valign=middle>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<span class="medium"><bean:message bundle="dormitorymanage" key="dormitorySearch.location" /></span>
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:select property="location" styleClass="select01" onchange="javascript:changeLocation(this.value);">
										<html:option value="">-----------------------</html:option>
										<html:options collection="locationList1" property="dictValue" labelProperty="dictCaption" />
									</html:select>
								</td>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<span class="medium"><bean:message bundle="dormitorymanage" key="dormitorySearch.dormitory" /></span>
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="dorm">
										<html:option value="">-----------------------</html:option>
									</html:select>
								</td>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.roomNumber" />
								</td>
								<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
									<html:text property="roomNumber" styleClass="input_box" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
								</td>
							</tr>
							<tr align="center" valign=middle>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<span class="medium"><bean:message bundle="dormitorymanage" key="dormitorySearch.college" /></span>
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:select onchange="changeCollge(this.value)" styleClass="select01" property="collegeId">
										<html:option value="">-----------------------</html:option>
										<html:options collection="collegeList" property="collegeId" labelProperty="collegeName" />
									</html:select>
								</td>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.class" />
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="classId">
										<html:option value="">-----------------------</html:option>
									</html:select>
								</td>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.assistant" />
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="managerId">
										<html:option value="">-----------------------</html:option>
										<html:options collection="assistantList" property="managerId" labelProperty="managerName" />
									</html:select>
								</td>
							</tr>
							<tr align="center" valign=middle>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.stuNo" />
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:text property="studentNo" styleClass="input_box" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
								</td>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.stuName" />
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:text property="stuName" styleClass="input_box" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
								</td>
								<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<bean:message bundle="classmanage" key="studentsearch.gender" />
								</td>
								<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="gender">
											<html:option value="">-----------------------</html:option>
											<html:options collection="genderList" labelProperty="dictCaption" property="id.dictValue" />
										</html:select>
								</td>
							</tr>

							<tr align="center" valign=middle>
								<td width="14%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.enterenceNo" />
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3" >
									<html:text property="enterenceNo" styleClass="input_box" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
								</td>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.fromProvince" />
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="fromProvince">
										<html:option value="">-----------------------</html:option>
										<html:options collection="provinceList" property="dictValue" labelProperty="dictCaption" />
									</html:select>
								</td>

								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.majorin" />
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="majorin">
										<html:option value="">-------------------------------------</html:option>
										<html:options collection="majorinList" property="dictValue" labelProperty="dictCaption" />
									</html:select>
								</td>
							</tr>
							
<!-- 							<tr align="center" valign=middle>
								<td width="14%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.enterenceNo" />
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3" colspan=5>
									<html:text property="enterenceNo" styleClass="input_box" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
								</td>

							</tr>	
 -->													
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
			<td align="left" valign="middle">
				<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
			</td>
		</tr>
		<tr>
			<td height="40" align="center" valign="top">
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
					<tbody>
						<tr align="center" valign=middle>
							<td height="24" valign="middle" class="tableHeader" onclick="sortTable('location');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.location" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('dormitory');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.dormitory" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('roomNumber');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.roomNumber" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('college');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.college" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('class');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.class" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('assistant');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.assistant" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('stuNo');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.stuNo" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('enterenceNo');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.enterenceNo" />
							</td>								
							<td valign="middle" class="tableHeader" onclick="sortTable('stuName');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.stuName" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('gender');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.gender" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('majorin');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.majorin" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('fromProvince');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.fromProvince" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('nation');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.nation" />
							</td>
						
						</tr>

						<logic:present name="dormitorys" scope="request">
							<%int dormitoryCount = ((Integer) request
					.getAttribute("dormitoryCount")).intValue();%>
							<!--page offset start -->
							<pg:pager url="./DormitorySearchAction.do" items="<%=dormitoryCount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
								<%-- keep track of preference --%>
								<pg:param name="method" />
								<pg:param name="location" />
								<pg:param name="dorm" />
								<pg:param name="roomNumber" />
								<pg:param name="collegeId" />
								<pg:param name="classId" />
								<pg:param name="managerId" />
								<pg:param name="studentNo" />
								<pg:param name="stuName" />
								<pg:param name="majorin" />
								<pg:param name="fromProvince" />
								<pg:param name="nation" />
								<pg:param name="enterenceNo" />
								<pg:param name="gender" />
								<pg:param name="page" />
								<pg:param name="orderby" />
								<pg:param name="sort" />


								<%-- save pager offset during form changes --%>
								<input type="hidden" name="pager.offset" value="<%= offset %>">
								<logic:iterate name="dormitorys" id="dormitorys" indexId="i">
									<pg:item>
									<tr align="center" valign=middle>
												<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="location" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dormitorys" property="dormitory" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="roomNumber" />
													&nbsp;
												</td>
										<c:if test="${i%2 == 0}">											
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="collegeName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="classNo" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="managerName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="studentNo" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="birthday" />
													&nbsp;
												</td>													
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="stuName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="gender" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="majorin" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="fromProvince" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dormitorys" property="nation" />
													&nbsp;
												</td>
																							
										</c:if>
										<c:if test="${i%2 != 0}">											
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dormitorys" property="collegeName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dormitorys" property="classNo" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dormitorys" property="managerName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dormitorys" property="studentNo" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dormitorys" property="birthday" />
													&nbsp;
												</td>												
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dormitorys" property="stuName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dormitorys" property="gender" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dormitorys" property="majorin" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dormitorys" property="fromProvince" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dormitorys" property="nation" />
													&nbsp;
												</td>
												
											
										</c:if>
										</tr>
									</pg:item>
								</logic:iterate>
								<jsp:include page="./page.jsp" flush="true" />

					</tbody>
				</table>
			</td>
		</tr>
			<tr> 
    			<td>
        		<jsp:include page="./pagenoexcel.jsp" flush="true" />
    			</td>
  			</tr>
		</pg:pager>
	</logic:present>
    <logic:notPresent name="dormitorys" scope="request">	
		  </tbody>
        </table>
      </td>
   </tr>
   </logic:notPresent>   		
  <tr> 
    <td height="40" align="left" valign="middle">
        <%
        int rowcount=0;
        if(request.getAttribute("dormitoryCount")!=null){
        	rowcount=((Integer)request.getAttribute("dormitoryCount")).intValue();
        %>       
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
        <%} %>
    </td>
  </tr>			
		<tr>
			<td align="center" valign="bottom" height="10">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="bottom" height="10">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="bottom" height="10">
				&nbsp;
			</td>
		</tr>

	</table>


</body>

<script language="JavaScript">
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
			String classNo=classmodel.getClassNo();	
			String collegeId = classmodel.getYxCollege().getCollegeId();
	%>
			classes[<%=i%>]= new Array("<%=classid%>","<%=classNo%>","<%=collegeId%>"); 
	<%	
		}	
	%>
	classescount=<%=classeslist.size()%>
	

	function changeCollge(college){
	 	document.all.classId.length=0;
	 	var collegeId=college; 
		var j; 
		document.all.classId.options[document.all.classId.length]=new Option("-----------------------","");
		for (j=0; j<classescount; j++) 
		{ 
			if (classes[j][2] == collegeId) 
			{ 
				document.all.classId.options[document.all.classId.length]= new Option(classes[j][1],classes[j][0]);
			} 
		}
		
	 }

	 	 <!-- dormitory list -->
 
		var dormcount;
		dormcount = 0;
		dormitorys = new Array(); 
	<%	
		ArrayList dromitorylist=(ArrayList)request.getAttribute("dormitoryList1");
		int l = 0;
		for(l=0;l<dromitorylist.size();l++){
			HashMap map = (HashMap)dromitorylist.get(l);
			String dormitoryid = (String)map.get("dictValue");
			String dormtioryname = (String)map.get("dictCaption");
			String location = (String)map.get("location");
	%>
		dormitorys[<%=l%>]= new Array("<%=dormitoryid%>","<%=dormtioryname%>","<%=location%>"); 
	<%	
		}	
	%>

	dormcount=<%=dromitorylist.size()%> 
 
	function changeLocation(location){
		document.all["dorm"].length=0;
		var locationId=location;
		var j; 
		document.all.dorm.options[document.all.dorm.length]= new Option("-----------------------","");
			for (j=0;j < dormcount; j++) 
			{ 
				if (dormitorys[j][2] == locationId) 
				{ 
					document.all.dorm.options[document.all.dorm.length]= new Option(dormitorys[j][1],dormitorys[j][0]);
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
	 
	 function my_onload(){
	 
	 	if(document.all.collegeId.value!=""){
		 	document.all.classId.length=0;
			var j; 
			document.all.classId.options[document.all.classId.length]=new Option("-----------------------","");
			for (j=0; j<classescount; j++) 
			{ 
				if (classes[j][2] == document.all.collegeId.value) 
				{ 
					document.all.classId.options[document.all.classId.length]= new Option(classes[j][1],classes[j][0]);
					if(classes[j][0]==document.all("myclass").value){
						document.all.classId.options[document.all.classId.length-1].selected=true;
					}
				} 
			} 
	 	}
	 	
	 	if(document.all.location.value!=""){	 	
	 		document.all.dorm.length=0;
			var j; 
			document.all.dorm.options[document.all.dorm.length]= new Option("-----------------------","");
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all.location.value) 
				{ 
					document.all.dorm.options[document.all.dorm.length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("mydormitory").value){
					document.all.dorm.options[document.all.dorm.length-1].selected=true;
				}
			} 
	 	}
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
		NotExport();
	 }
	 
	 
	 function DoExport(){
	 	document.all("export").value='export';
	 	document.forms[0].submit();
	 }
	 function NotExport(){
	 	document.all("export").value='';
	 }
	 
	 function sortTable(selected){
	 	var sortIndex = selected;
	 	document.all.orderby.value=selected;
	 	if(document.all.sort.value=="0"){
	 		document.all.sort.value="1";
	 	}else if(document.all.sort.value=="1"){
	 		document.all.sort.value="2";
	 	}else{
	 		document.all.sort.value="0";
	 	}
//	 	document.forms[0].submit();
	 }
	 window.onload=my_onload;	
	 
	 uniteTable(document.all.maintable,3);//执行测试。
	//合并书院、班级单元格
function uniteTable(thistab,colLength){
	var rn=thistab.rows.length;//取得行数
	var rowspann=0;
	for(j=colLength-1;j>=0;j--){//从第0列开始，合并多少列
	for(i=rn-1;i>0;i--){//从倒数第一行开始往上检查
	if(thistab.rows[i].cells[j].innerText==thistab.rows[i-1].cells[j].innerText&&thistab.rows[i].cells[j].colSpan==thistab.rows[i-1].cells[j].colSpan){//与上面一行比较，如果两行相等就合计当前行的合并行数，并删除当前行。
	rowspann+=thistab.rows[i].cells[j].rowSpan;
	thistab.rows[i].deleteCell(j);
	}else{
	thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
	rowspann=0;
	}
	}
	//检测无表头的表
	if(i==0&&rowspann>0){
	thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
	rowspann=0;
	}
	
	}
} 

</script>

