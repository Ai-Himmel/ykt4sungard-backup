<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="java.util.HashMap"%>
<%@ include file="../tiles/include.jsp"%>


<script language="javascript">
function onSearch(){
	if(document.all.areaA.value==""){
			alert("校区不能为空");
			document.all.areaA.focus();
			return false;
		}
	if(document.all.locationA.value==""){
			alert("区域不能为空");
			document.all.locationA.focus();
			return false;
		}
		if(document.all.dormitoryA.value==""){
			alert("楼号不能为空");
			document.all.dormitoryA.focus();
			return false;
		}
		if(document.all.unitA.value==""){
			alert("单元不能为空");
			document.all.unitA.focus();
			return false;
		}
		if(document.all.roomNumberA.value==""){
			alert("宿舍号不能为空");
			document.all.roomNumberA.focus();
			return false;
		}
	if((document.all.areaA.value=="")&&(document.all.locationA.value=="")&&(document.all.dormitoryA.value=="")&&(document.all.roomNumberA.value=="")){
		document.forms[0].action='DormitoryAdjustAction.do?method=searchAdjust&getrole=3';
		return true;
	}else{
		if(document.all.areaA.value==""){
			alert("校区不能为空");
			document.all.areaA.focus();
			return false;
		}	
		if(document.all.locationA.value==""){
			alert("区域不能为空");
			document.all.locationA.focus();
			return false;
		}
		if(document.all.unitA.value==""){
			alert("单元不能为空");
			document.all.unitA.focus();
			return false;
		}
		if(document.all.dormitoryA.value==""){
			alert("楼号不能为空");
			document.all.dormitoryA.focus();
			return false;
		}
		if(document.all.roomNumberA.value==""){
			alert("宿舍号不能为空");
			document.all.roomNumberA.focus();
			return false;
		}
	}
	document.forms[0].action='DormitoryAdjustAction.do?method=searchAdjust&getrole=3';
	return true;		
}

function onSearch1(){	
		if(document.all.areaB.value==""){
			alert("校区不能为空");
			document.all.areaB.focus();
			return false;
		}
		if(document.all.locationB.value==""){
			alert("区域不能为空");
			document.all.locationB.focus();
			return false;
		}
		
		if(document.all.dormitoryB.value==""){
			alert("楼号不能为空");
			document.all.dormitoryB.focus();
			return false;
		}
		if(document.all.unitB.value==""){
			alert("单元不能为空");
			document.all.unitB.focus();
			return false;
		}
		if(document.all.roomNumberB.value==""){
			alert("宿舍号不能为空");
			document.all.roomNumberB.focus();
			return false;
		}
	if((document.all.areaB.value=="")&&(document.all.locationB.value=="")&&(document.all.dormitoryB.value=="")&&(document.all.roomNumberB.value=="")){
		document.forms[0].action='DormitoryAdjustAction.do?method=searchAdjust&getrole=3';
		return true;
	}else{
		if(document.all.areaB.value==""){
			alert("校区不能为空");
			document.all.areaB.focus();
			return false;
		}	
		if(document.all.locationB.value==""){
			alert("区域不能为空");
			document.all.locationB.focus();
			return false;
		}
		if(document.all.dormitoryB.value==""){
			alert("楼号不能为空");
			document.all.dormitoryB.focus();
			return false;
		}
		if(document.all.unitB.value==""){
			alert("单元不能为空");
			document.all.unitB.focus();
			return false;
		}
		if(document.all.roomNumberB.value==""){
			alert("宿舍号不能为空");
			document.all.roomNumberB.focus();
			return false;
		}
	}
	document.forms[0].action='DormitoryAdjustAction.do?method=searchAdjust&getrole=3';
	return true;				
}
</script>

<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium">宿舍间调整</font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" height="10">
				<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
			</td>
		</tr>

		<tr>
			<td align="center" valign="top">
				<html:form action="DormitoryAdjustAction.do?method=saveAlert&getrole=3">
					<tr>
						<td>
							<%if (request.getAttribute("mydormitoryA") != null) {
				String mydormitoryA = request.getAttribute("mydormitoryA")
						.toString();

				%>
							<INPUT type="hidden" name="mydormitoryA" value="<%=mydormitoryA%>">
							<%} else {

			%>
							<INPUT type="hidden" name="mydormitoryA" value="">

							<%}

			%>
						</td>
						<td>
							<%if (request.getAttribute("mydormitoryB") != null) {
				String mydormitoryB = request.getAttribute("mydormitoryB")
						.toString();

				%>
							<INPUT type="hidden" name="mydormitoryB" value="<%=mydormitoryB%>">
							<%} else {

			%>
							<INPUT type="hidden" name="mydormitoryB" value="">

							<%}

			%>
						</td>
						<td>
							<%if (request.getAttribute("mydormitoryIdA") != null) {
				String mydormitoryIdA = request.getAttribute("mydormitoryIdA")
						.toString();

				%>
							<INPUT type="hidden" name="mydormitoryIdA" value="<%=mydormitoryIdA%>">
							<%} else {

			%>
							<INPUT type="hidden" name="mydormitoryIdA" value="">

							<%}

			%>
						</td>
						<td>
							<%if (request.getAttribute("mydormitoryIdB") != null) {
				String mydormitoryIdB = request.getAttribute("mydormitoryIdB")
						.toString();

				%>
							<INPUT type="hidden" name="mydormitoryIdB" value="<%=mydormitoryIdB%>">
							<%} else {

			%>
							<INPUT type="hidden" name="mydormitoryIdB" value="">

							<%}

			%>
						</td>

					</tr>
					<html:hidden property="bindStudentsA" />
					<html:hidden property="bindStudentsB" />
					<table width="90%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td width="45%" align="center" valign="top" bgcolor="#ECE6E6">
								&nbsp;
							</td>
							<td align="center" valign="top" bgcolor="#FFFFFF">
								&nbsp;
							</td>
							<td width="45%" align="center" valign="top" bgcolor="#ECE6E6">
								&nbsp;
							</td>
						</tr>
						<tr>
							<td align="center" valign="middle" bgcolor="#ECE6E6">
								<table width=99% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
									<tbody>
										<tr align="center" valign=middle>
									
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												校区
											</td>
											<td align="left" valign="middle">
												<html:select property="areaA" styleClass="select01" onchange="javascript:changeAreaA(this.value);" style="width:120">
													<html:option value="">---------------------</html:option>
													<html:options collection="areaList" property="dictValue" labelProperty="dictCaption" />
												</html:select>
											</td>
										</tr>			
										<tr>								
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												区域


											</td>
											<td align="left" valign="middle">
												<html:select property="locationA" styleClass="select01" onchange="javascript:changeLocationA(this.value);" style="width:120">
													<html:option value="">---------------------</html:option>
													<html:options collection="locationList" property="dictValue" labelProperty="dictCaption" />												
												</html:select>
											</td>
										</tr>
										<tr align="center" valign=middle>
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												楼号
											</td>
											<td align="left" valign="middle">
												<html:select styleClass="select01" property="dormitoryA" style="width:120">
													<html:option value="">---------------------</html:option>
													<html:options collection="dormitoryList" property="dictValue" labelProperty="dictCaption" />																								
												</html:select>
											</td>
										</tr>
										<tr align="center" valign=middle>
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												单元
											</td>
											<td align="left" valign="middle">
												<html:text property="unitA" styleClass="input_box" style="width:120" maxlength="4"/>
											</td>
										</tr>
										<tr align="center" valign=middle>
										<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												宿舍
											</td>
											<td align="left" valign="middle">
												<html:text property="roomNumberA" styleClass="input_box" style="width:120" maxlength="4"/>
											</td>
										</tr>
										<tr align="center" valign=middle>
											<td height="24" colspan="2" align="right" valign="middle" class="medium">
												<html:submit property="search" styleClass="button_nor" onclick="return onSearch();">
													<bean:message key="button.query" />
												</html:submit>
											</td>
										</tr>
									</tbody>
								</table>
							</td>
							<td align="center" valign="top" bgcolor="#FFFFFF">
								&nbsp;
							</td>
							<td align="center" valign="top" bgcolor="#ECE6E6">
								<table width=99% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
									<tbody>
										<tr align="center" valign=middle>
									<tr align="center" valign=middle>
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												校区
											</td>
											<td align="left" valign="middle">
												<html:select property="areaB" styleClass="select01" onchange="javascript:changeAreaB(this.value);" style="width:120">
													<html:option value="">---------------------</html:option>
													<html:options collection="areaList" property="dictValue" labelProperty="dictCaption" />
												</html:select>
											</td>
										</tr>											
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												区域


											</td>
											<td align="left" valign="middle">
												<html:select property="locationB" styleClass="select01" onchange="javascript:changeLocationB(this.value);" style="width:120">
													<html:option value="">---------------------</html:option>
													<html:options collection="locationList" property="dictValue" labelProperty="dictCaption" />																								
												</html:select>
											</td>
										</tr>
										<tr align="center" valign=middle>
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												楼号
											</td>
											<td align="left" valign="middle">
												<html:select styleClass="select01" property="dormitoryB" style="width:120">
													<html:option value="">---------------------</html:option>
													<html:options collection="dormitoryList" property="dictValue" labelProperty="dictCaption" />																																				
												</html:select>
											</td>
										</tr>
										<tr align="center" valign=middle>
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												单元
											</td>
											<td align="left" valign="middle">
												<html:text property="unitB" styleClass="input_box" style="width:120" maxlength="4"/>
											</td>
										</tr>
										<tr align="center" valign=middle>
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												宿舍
											</td>
											<td align="left" valign="middle">
												<html:text property="roomNumberB" styleClass="input_box" style="width:120" maxlength="4"/>
											</td>
										</tr>
										<tr align="center" valign=middle>
											<td height="24" colspan="2" align="right" valign="middle" class="medium">
												<html:submit property="search" styleClass="button_nor" onclick="return onSearch1();">
													<bean:message key="button.query" />
												</html:submit>
											</td>
										</tr>
									</tbody>
								</table>
							</td>
						</tr>
						<tr>
							<td height="28" align="center" valign="middle" bgcolor="#ECE6E6">
								<strong class="medium">原宿舍</strong>
							</td>
							<td align="center" valign="top" bgcolor="#FFFFFF">
								&nbsp;
							</td>
							<td align="center" valign="middle" bgcolor="#ECE6E6">
								<strong class="medium">目标宿舍</strong>
							</td>
						</tr>
						<tr>
							<td align="center" valign="top" bgcolor="#ECE6E6">
								<select name="bindStudentListA" multiple="multiple" onDblClick="" size="15" style="width:250 px;">
								</select>
							</td>
							<td align="center" valign="middle" bgcolor="#FFFFFF">
								<p>
									<button name="moveRight" id="moveRight" type="button" class="button_nor" onclick="return dormitorySelCheck_trans();">
										<bean:message bundle="classmanage" key="classBinding.right" />
									</button>
									<br />
									<br />
									<button name="moveLeft" id="moveLeft" type="button" class="button_nor" onclick="return dormitorySelCheck_return();">
										<bean:message bundle="classmanage" key="classBinding.left" />
									</button>
									<br />
								</p>
							</td>
							<td align="center" valign="top" bgcolor="#ECE6E6">
								<select name="bindStudentListB" multiple="multiple" onDblClick="" size="15" style="width:250 px;">
								</select>
							</td>
						</tr>
						<tr>
							<td align="center" valign="top" bgcolor="#ECE6E6">
								&nbsp;
							</td>
							<td align="center" valign="middle" bgcolor="#FFFFFF">
								&nbsp;
							</td>
							<td align="center" valign="top" bgcolor="#ECE6E6">
								&nbsp;
							</td>
						</tr>

						<tr align="right" valign="middle">
							<td height="35">
								&nbsp;
							</td>
							<td>
								&nbsp;
							</td>
							<td>
								<html:submit property="alert" styleClass="button_nor" value="调 整" onclick="return setValue();" />
							</td>
						</tr>
					</table>
				</html:form>
			</td>
		</tr>
	</table>
</body>

<script language="JavaScript">	 
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
 
	function changeAreaA(area){
		document.all["locationA"].length=0;
		var areaId=area;
		var j1; 
		document.all["locationA"].options[document.all["locationA"].length]= new Option("---------------------","");
			for (j1=0;j1 < locationcount; j1++) 
			{ 
				if (locations[j1][2] == areaId) 
				{ 
					document.all["locationA"].options[document.all["locationA"].length]= new Option(locations[j1][1],locations[j1][0]);
					if(locations[j1][0]==<%=request.getAttribute("locationA")%>){
						document.all["locationA"].options[document.all["locationA"].length-1].selected=true;
					}
				} 
			} 
	}
	
	function changeAreaB(area){
		document.all["locationB"].length=0;
		var areaId=area;
		var j1; 
		document.all["locationB"].options[document.all["locationB"].length]= new Option("---------------------","");
			for (j1=0;j1 < locationcount; j1++) 
			{ 
				if (locations[j1][2] == areaId) 
				{ 
					document.all["locationB"].options[document.all["locationB"].length]= new Option(locations[j1][1],locations[j1][0]);
					if(locations[j1][0]==<%=request.getAttribute("locationB")%>){
						document.all["locationB"].options[document.all["locationB"].length-1].selected=true;
					}
				} 
			} 
	}	


	 	 <!-- dormitory list -->
 
		var dormcount;
		dormcount = 0;
		dormitorys = new Array(); 
	<%	
		ArrayList dromitorylist=(ArrayList)request.getAttribute("dormitoryList");
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
 
	function changeLocationA(location){
		document.all["dormitoryA"].length=0;
		var locationId=location;
		var j; 
		document.all["dormitoryA"].options[document.all["dormitoryA"].length]= new Option("---------------------","");
			for (j=0;j < dormcount; j++) 
			{ 
				if (dormitorys[j][2] == locationId) 
				{ 
					document.all["dormitoryA"].options[document.all["dormitoryA"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
					if(dormitorys[j][0]==<%=request.getAttribute("dormitoryA")%>){
						document.all["dormitoryA"].options[document.all["dormitoryA"].length-1].selected=true;
					}
				} 
			} 
	} 
	function changeLocationB(location){
		document.all["dormitoryB"].length=0;
		var locationId=location;
		var j; 
		document.all["dormitoryB"].options[document.all["dormitoryB"].length]= new Option("---------------------","");
			for (j=0;j < dormcount; j++) 
			{ 
				if (dormitorys[j][2] == locationId) 
				{ 
					document.all["dormitoryB"].options[document.all["dormitoryB"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
					if(dormitorys[j][0]==<%=request.getAttribute("dormitoryB")%>){
						document.all["dormitoryB"].options[document.all["dormitoryB"].length-1].selected=true;
					}
				} 
			} 
	} 


	var ustucount;

	ustucount = 0;

	unbindStudents = new Array(); 

	<%	
	if(request.getAttribute("bindStudentListA")!=null){	
		ArrayList bindStudentListA=(ArrayList)request.getAttribute("bindStudentListA");
		int k = 0;
		for(k=0;k<bindStudentListA.size();k++){
			HashMap bindStu= (HashMap)bindStudentListA.get(k);
			String stuId = bindStu.get("stuId").toString();
			String stuNo = bindStu.get("stuNo").toString();
			String stuName = bindStu.get("stuName").toString();
			String gender = bindStu.get("gender").toString();
			String dormitoryId = bindStu.get("dormitoryId").toString();
			String accomodation = bindStu.get("accomodation").toString();
			System.out.println(gender);
	%>

		unbindStudents[<%=k%>]= new Array("<%=stuId%>","<%=stuNo%> <%=stuName%>[<%=gender%>]","<%=gender%>","<%=accomodation%>","<%=dormitoryId%>");
		document.all["bindStudentListA"].options[document.all["bindStudentListA"].length]= new Option(unbindStudents[<%=k%>][1],unbindStudents[<%=k%>][0]);

	<%	
		}	
	%>

	ustucount=<%=bindStudentListA.size()%> 
	<%
	}
	%>
	var stucount;
	stucount = 0;
	bindStudents = new Array(); 
	<%	
	if(request.getAttribute("bindStudentListB")!=null){	
		ArrayList bindStudentListB=(ArrayList)request.getAttribute("bindStudentListB");
		int m = 0;
		for(m=0;m<bindStudentListB.size();m++){
			HashMap bindStu= (HashMap)bindStudentListB.get(m);
			String stuId = bindStu.get("stuId").toString();
			String stuNo = bindStu.get("stuNo").toString();
			String stuName = bindStu.get("stuName").toString();
			String gender = bindStu.get("gender").toString();
			String dormitoryId = bindStu.get("dormitoryId").toString();
			String accomodation = bindStu.get("accomodation").toString();
	%>
		bindStudents[<%=m%>]= new Array("<%=stuId%>","<%=stuNo%> <%=stuName%>[<%=gender%>]","<%=gender%>","<%=accomodation%>","<%=dormitoryId%>"); 
		document.all["bindStudentListB"].options[document.all["bindStudentListB"].length]= new Option(bindStudents[<%=m%>][1],bindStudents[<%=m%>][0]);
	<%	
		}
	
	%>
	stucount=<%=bindStudentListB.size()%> 	
	<%
	}
	%>
	 
	 function my_onload(){	 	
	 	if(document.all("locationA").value!=""){	 	
	 		document.all["dormitoryA"].length=0;
			var j; 
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all("locationA").value) 
				{ 
					document.all["dormitoryA"].options[document.all["dormitoryA"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("myDormitoryA").value){
					document.all("dormitoryA").options[document.all("dormitoryA").length-1].selected=true;
				}
			} 
	 	}	
	 	if(document.all("locationB").value!=""){	 	
	 		document.all["dormitoryB"].length=0;
			var j; 
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all("locationB").value) 
				{ 
					document.all["dormitoryB"].options[document.all["dormitoryB"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("myDormitoryB").value){
					document.all("dormitoryB").options[document.all("dormitoryB").length-1].selected=true;
				}
			} 
	 	}
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		} 	
	 }
	 
	 window.onload=my_onload;	 
	 
function setValue(){
	if(document.all.mydormitoryIdA.value!=""&&document.all.mydormitoryIdB.value!=""){
	document.all.bindStudentsA.value=unbindStudents;
	document.all.bindStudentsB.value=bindStudents;
		return true;
	}else{
		alert("没有可调整的对象");
		return false;
	}
}

function uiOptionReturn_putArrayItem_dorm(studentId){
	var student_id = studentId;
	var i;
	var index = 0;
	index = unbindStudents.length;
	for(i=0;i<bindStudents.length;i++){	
	 	if(bindStudents[i][0]==student_id){
	 		unbindStudents[index] = new Array(bindStudents[i][0],bindStudents[i][1],bindStudents[i][2],bindStudents[i][3],document.all.mydormitoryIdA.value);
	 		bindStudents[i][0]="";
	 		bindStudents[i][1]="";
	 		bindStudents[i][2]="";
	 		bindStudents[i][3]="";
	 		bindStudents[i][4]="";
	 		ustucount++;
	 	}	 	
 	}

}

//and add this record to bindStudents
//and delete this record from unbindStudents
function uiOptionTransfer_putArrayItem_dorm(studentId){
	var student_id = studentId;
	var i;
	var index = 0;
	index = bindStudents.length;
	for(i=0;i<unbindStudents.length;i++){	
	 	if(unbindStudents[i][0]==student_id){
	 		bindStudents[index] = new Array(unbindStudents[i][0],unbindStudents[i][1],unbindStudents[i][2],unbindStudents[i][3],document.all.mydormitoryIdB.value);
	 		unbindStudents[i][0]="";
	 		unbindStudents[i][1]="";
	 		unbindStudents[i][2]="";
	 		unbindStudents[i][3]="";
	 		unbindStudents[i][4]="";
	 		stucount++;	 		
	 	}
	 
}

}

function dormitorySelCheck_trans(){
	if(document.all.mydormitoryIdB.value==""){
		alert("请先选择目标宿舍");
		return false;
	}
	transferOption_dorm(document.all("bindStudentListA"), document.all("bindStudentListB"),false)
	return true;
}

function dormitorySelCheck_return(){
	if(document.all.mydormitoryIdA.value==""){
		alert("请先选择源宿舍");
		return false;
	}
	returnOption_dorm(document.all("bindStudentListB"), document.all("bindStudentListA"),false)
	return true;
}

function returnOption_dorm(e1,e2,all){
  	var src = e2.options;
  	var tgt = e1.options;
  	var items;
  	var index;
  	for (var i = tgt.length - 1; i >= 0; --i) {
    	if (all || tgt[i].selected) {      	
			clone = uiCommon_cloneSelectOption_dorm(tgt[i]);
  			src.add(clone);
  			uiOptionReturn_putArrayItem_dorm(tgt[i].value);
  			tgt[i] = null;
    	}
  	}
}

function transferOption_dorm(e1,e2,all){
	var src = e2.options;
  	var tgt = e1.options;
  	var items;
  	var index;
  	for (var i = tgt.length - 1; i >= 0; --i) {
    	if (all || tgt[i].selected) {  	
			clone = uiCommon_cloneSelectOption_dorm(tgt[i]);
  			src.add(clone);
  			uiOptionTransfer_putArrayItem_dorm(tgt[i].value);
  			tgt[i] = null;
    	}
  	}
}

function uiCommon_cloneSelectOption_dorm(opt) {
  return new Option(opt.text, opt.value,
                    opt.defaultSelected, opt.selected);
}
setTimeout('DoInit()',30);
function DoInit(){
    var areaA = <%=request.getAttribute("areaA")%>;
    var locationA = <%=request.getAttribute("locationA")%>;
    var areaB = <%=request.getAttribute("areaB")%>;
    var locationB = <%=request.getAttribute("locationB")%>;
    var dormitoryA = <%=request.getAttribute("dormitoryA")%>;
    var dormitoryB = <%=request.getAttribute("dormitoryB")%>;
    if(areaA!=null&&areaA!=''){
	changeAreaA(areaA);
	}
	if(locationA!=null&&locationA!=''){
	changeLocationA(locationA);
	}
	if(areaB!=null&&areaB!=''){
	changeAreaB(areaB);
	}
	if(locationB!=null&&locationB!=''){
	changeLocationB(locationB);
	}
}
</script>

