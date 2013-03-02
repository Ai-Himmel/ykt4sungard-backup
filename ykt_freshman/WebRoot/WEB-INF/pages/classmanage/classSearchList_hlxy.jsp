<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.Classmodel"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ include file="../tiles/include.jsp"%>
<%@ page import="java.util.HashMap"%>

<script language="JavaScript">
function clearAll(){
	document.all("classmodel.classId").value="";
	document.all("assistant").value="";	
	document.all("area").value="";	
	document.all("location").value="";	
	document.all("dormitory").value="";	
	document.all("roomnumber").value="";
	document.all("direction").value="";	
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

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="classmanage" key="classsearch.classsearch" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top" height="10"></td>
			</tr>

			<tr>
				<td align="center" valign="top">
					<html:form action="classAction.do?method=load4ClassSearch&getrole=2">

						<table width=100% border=1 align="center" cellpadding="1" cellspacing="0" bordercolor="#FFFFFF" id="submenu1">
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
							<tbody>
								<tr align="center" valign="middle">
								
									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="class.name" /></span>
									</td>
									<td width="25%" align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="classmodel.classId">
											<html:option value="">-----------------------</html:option>
											<html:options collection="classList" labelProperty="classNo" property="classId" />
										</html:select>
									</td>
									<td width="10%" align="left" valign="middle" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="classsearch.assistant" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3" >
										<html:select styleClass="select01" property="assistant">
											<html:option value="">-----------------------</html:option>
											<html:options collection="assistantList" labelProperty="managerName" property="managerId" />
										</html:select>
									</td>
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
											校区
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select property="area" styleClass="select01" onchange="javascript:changeArea(this.value);" style="width:120">
											<html:option value="">---------------------</html:option>
											<html:options collection="areaList" property="dictValue" labelProperty="dictCaption" />
										</html:select>
									</td>									
								</tr>

								<tr align="center" valign="middle">
									<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
											区域
									</td>
									<td width="25%" align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="location" onchange="changeLocation(this.value)">
											<html:option value="">-----------------------</html:option>
											<html:options collection="locationList" labelProperty="dictCaption" property="dictValue" />
										</html:select>
									</td>
									<td width="10%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="classsearch.dormitory" /></span>
									</td>
									<td width="25%" align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="dormitory">
											<html:option value="">-----------------------</html:option>
										</html:select>
									</td>
									<td width="10%" align="right" valign="middle" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="classsearch.roomnumber" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:text property="roomnumber" styleClass="input_box" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td width="10%" align="left" valign="middle" class="tableHeader2">
										<span class="medium"><bean:message bundle="classmanage" key="classsearch.direction" /></span>
									</td>
									<td align="left" valign="middle" class="tableHeader3" colspan=5>
										<html:select styleClass="select01" property="direction" >
											<html:option value="">-----------------------</html:option>
											<html:options collection="directionList" labelProperty="dictCaption" property="dictValue" />
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
				<td height="20" align="center" valign="middle" class="medium">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="40" align="center" valign="top">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
						<tbody>
							<tr align="center" valign="middle">
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="class.name" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="classsearch.assistant" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="classsearch.location" />
								</td>
								<td valign="middle" class="tableHeader">
									区域
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="classsearch.dormitory" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="classsearch.roomnumber" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="classsearch.direction" />
								</td>								
								<td valign="middle" class="tableHeader">
									入住性别
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="classsearch.accomodation" />
								</td>
								<td valign="middle" class="tableHeader">
									宿舍电话
								</td>
							</tr>
							<logic:present name="classsearchmodels" scope="request">
								<%int itemNo = ((Integer) request.getAttribute("classCount"))
					.intValue();%>
								<pg:pager url="./classAction.do" items="<%=itemNo%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%=true%>" export="offset,currentPageNumber=pageNumber" scope="request">
									<%-- keep track of preference --%>
									<pg:param name="method" />
									<pg:param name="college" />
									<pg:param name="classmodel.classId" />
									<pg:param name="assistant" />
									<pg:param name="area" />									
									<pg:param name="location" />
									<pg:param name="dormitory" />
									<pg:param name="roomnumber" />
									<pg:param name="direction" />									
									<pg:param name="page" />
									<pg:param name="orderby" />
									<pg:param name="sort" />
									<pg:param name="getrole" />

									<%-- save pager offset during form changes --%>
									<input type="hidden" name="pager.offset" value="<%= offset %>">


									<logic:iterate name="classsearchmodels" id="classsearch" indexId="i">
										<pg:item>
											<tr align="center" valign="middle">
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="classsearch" property="classNo" />
													&nbsp;
												</td>												
												<td align="center" valign="middle" bgcolor="#FFFFFF">
												<input type="hidden" name="hpf" value="<bean:write name="classsearch" property="classNo" />">												
													<bean:write name="classsearch" property="assistantName" />
													&nbsp;
												</td>
												<c:if test="${i%2 == 0}">
													<td align="center" valign="middle" bgcolor="#FFFFFF">
												<input type="hidden" name="hpf" value="<bean:write name="classsearch" property="classNo" /><bean:write name="classsearch" property="assistantName" />">												
														<bean:write name="classsearch" property="area" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="classsearch" property="location" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="classsearch" property="dormitory" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="classsearch" property="roomNumber" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="classsearch" property="direction" />
														&nbsp;
													</td>													
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="classsearch" property="gender" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="classsearch" property="accomodation" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="classsearch" property="telphone" />
														&nbsp;
													</td>
												</c:if>
												<c:if test="${i%2 != 0}">
													<td align="center" valign="middle" bgcolor="#F6F4F5">
														<bean:write name="classsearch" property="area" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#F6F4F5">
														<bean:write name="classsearch" property="location" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#F6F4F5">
														<bean:write name="classsearch" property="dormitory" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#F6F4F5">
														<bean:write name="classsearch" property="roomNumber" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#F6F4F5">
														<bean:write name="classsearch" property="direction" />
														&nbsp;
													</td>													
													<td align="center" valign="middle" bgcolor="#F6F4F5">
														<bean:write name="classsearch" property="gender" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#F6F4F5">
														<bean:write name="classsearch" property="accomodation" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#F6F4F5">
														<bean:write name="classsearch" property="telphone" />
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
    <logic:notPresent name="classsearchmodels" scope="request">	
		  </tbody>
        </table>
      </td>
   </tr>
   </logic:notPresent>			
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
				<td>
					&nbsp;
				</td>
			</tr>
		</table>
	</body>
</center>

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
			String className=classmodel.getClassName();	
			String classNo = classmodel.getClassNo();
			String collegeId = classmodel.getYxCollege().getCollegeId();
	%>
			classes[<%=i%>]= new Array("<%=classid%>","<%=classNo%>","<%=collegeId%>"); 
	<%	
		}	
	%>
	classescount=<%=classeslist.size()%>
	

	 	 <!-- location list -->
 
		var locationcount;
		locationcount = 0;
		locations = new Array(); 
	<%	
		ArrayList locationlist=(ArrayList)request.getAttribute("locationList");
		int l1 = 0;
		for(l1=0;l1<locationlist.size();l1++){
			HashMap map1 = (HashMap)locationlist.get(l1);
			String locationid = (String)map1.get("dictValue");
			String locationname = (String)map1.get("dictCaption");
			String area = (String)map1.get("area");
	%>
		locations[<%=l1%>]= new Array("<%=locationid%>","<%=locationname%>","<%=area%>"); 
	<%	
		}	
	%>

	locationcount=<%=locationlist.size()%> 
 
	function changeArea(area){
		document.all["location"].length=0;
		var areaId=area;
		var j1; 
		document.all["location"].options[document.all["location"].length]= new Option("-----------------------","");
			for (j1=0;j1 < locationcount; j1++) 
			{ 
				if (locations[j1][2] == areaId) 
				{ 
					document.all["location"].options[document.all["location"].length]= new Option(locations[j1][1],locations[j1][0]);
				} 
			} 
	}
	 
	 
	 	 <!-- dormitory list -->
 
		var dormcount;
		dormcount = 0;
		dormitorys = new Array(); 
	<%	
		ArrayList dromitorylist=(ArrayList)request.getAttribute("buildingList");
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

		document.all["dormitory"].length=0;
		var locationId=location;
		var j; 
		document.all["dormitory"].options[document.all["dormitory"].length]= new Option("-----------------------","");
			for (j=0;j < dormcount; j++) 
			{
				if (dormitorys[j][2] == locationId) 
				{ 
					document.all["dormitory"].options[document.all["dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
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

	 	if(document.all("location").value!=""){	 	
	 		document.all["dormitory"].length=0;
			var j; 
			document.all["dormitory"].options[document.all["dormitory"].length]= new Option("--------------------","");
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all("location").value) 
				{ 
					document.all["dormitory"].options[document.all["dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("mydormitory").value){
					document.all("dormitory").options[document.all("dormitory").length-1].selected=true;
				}
			} 
	 	}
	 }
	 
	 window.onload=my_onload;	
	 
uniteTable(document.all.maintable,3);//执行测试。
	//合并书院、班级单元格
function uniteTable(thistab,colLength){
var rn=thistab.rows.length;//取得行数
var rowspann=0;

for(j=colLength-1;j>=0;j--){//从第0列开始，合并多少列
for(i=rn-1;i>0;i--){//从倒数第一行开始往上检查

if(thistab.rows[i].cells[j].innerText==thistab.rows[i-1].cells[j].innerText){//与上面一行比较，如果两行相等就合计当前行的合并行数，并删除当前行。
if(thistab.rows[i].cells[j].children(0)!=null&&thistab.rows[i-1].cells[j].children(0)!=null&&thistab.rows[i].cells[j].children(0).value==thistab.rows[i-1].cells[j].children(0).value){//把前面一列的值放入隐藏域里,如果隐藏域有值就判断是否与上一行的值一样如果一样就合计当前行的合并行数，并删除当前行。
	rowspann+=thistab.rows[i].cells[j].rowSpan;	
	thistab.rows[i].deleteCell(j);	
}else if(thistab.rows[i].cells[j].children(0)==null&&thistab.rows[i-1].cells[j].children(0)==null){//如果隐藏域无值即象第一列那样就只管合并即可	    
		rowspann+=thistab.rows[i].cells[j].rowSpan;		
		thistab.rows[i].deleteCell(j);			
}
else{
thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
rowspann=0;
}

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
