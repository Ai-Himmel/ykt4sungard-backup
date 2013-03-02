<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.DictionaryId"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.yangong.dormitorymanage.web.help.GraduateWithAllInfo"%>
<%@ page import="org.king.dormitorymanage.domain.Dormitorymodel"%>
<%@ page import="java.util.Map"%>
<%@ page import="java.util.HashMap"%>
<%@ include file="../tiles/include.jsp"%>


<script language="javascript">

function onSearch(){

	if((document.all.area.value=="")
	&&(document.all.location.value=="")
	&&(document.all.dormitory.value=="")
	&&(document.all.unit.value=="")
	&&(document.all.roomNumber.value=="")){
		document.forms[0].action='DormitoryAdjustAction.do?method=searchPeopleAdjust&getrole=3';
		return true;
	}
	document.forms[0].action='DormitoryAdjustAction.do?method=searchPeopleAdjust&getrole=3';
	return true;		
}

function onSearch1(){
		if(document.all.area.value==""){
			alert("校区不能为空");
			document.all.area.focus();
			return false;
		}	
		if(document.all.location.value==""){
			alert("区域不能为空");
			document.all.location.focus();
			return false;
		}
		if(document.all.dormitory.value==""){
			alert("楼号不能为空");
			document.all.dormitory.focus();
			return false;
		}
		if(document.all.unit.value==""){
			alert("单元不能为空");
			document.all.unit.focus();
			return false;
		}
		if(document.all.roomNumber.value==""){
			alert("宿舍号不能为空");
			document.all.roomNumber.focus();
			return false;
		}
		document.forms[0].action='DormitoryAdjustAction.do?method=searchPeopleAdjust&getrole=3';
		return true;		
}
</script>

<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium">个人宿舍调整</font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" height="10">
				<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
			</td>
		</tr>

		<tr>
			<td align="center" valign="top">
				<html:form action="DormitoryAdjustAction.do?method=savePeopleAlert&&getrole=3">
					<tr>
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
						<td>
							<%if (request.getAttribute("mydormitoryId") != null) {
				String mydormitoryId = request.getAttribute("mydormitoryId")
						.toString();

				%>
							<INPUT type="hidden" name="mydormitoryId" value="<%=mydormitoryId%>">
							<%} else {

			%>
							<INPUT type="hidden" name="mydormitoryId" value="">

							<%}

			%>
						</td>
					</tr>
					<html:hidden property="bindStudents" />
					<html:hidden property="unbindStudents" />
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
										<tr align="center" valign="middle">
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												学号
											</td>
											<td align="left" valign="middle">
												<html:text property="stuNo" styleClass="input_box" style="width:120" maxlength="20"/>
											</td>
										</tr>
										<tr align="center" valign=middle>
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												姓名
											</td>
											<td align="left" valign="middle">
												<html:text property="stuName" styleClass="input_box" style="width:120" maxlength="20"/>
											</td>
										</tr>
										<tr align="center" valign=middle>
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												性别
											</td>
											<td align="left" valign="middle">
												<html:select property="gender" styleClass="select01" style="width:120">
													<html:option value="">--------------------</html:option>
													<html:options collection="genderList" property="id.dictValue" labelProperty="dictCaption" />
												</html:select>
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
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												校区

											</td>
											<td align="left" valign="middle">
												<html:select property="area" styleClass="select01" onchange="javascript:changeArea(this.value);" style="width:120">
													<html:option value="">---------------------</html:option>
													<html:options collection="areaList" property="dictValue" labelProperty="dictCaption" />
												</html:select>
											</td>
										</tr>									
										<tr align="center" valign=middle>
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												区域

											</td>
											<td align="left" valign="middle">
												<html:select property="location" styleClass="select01" onchange="javascript:changeLocation(this.value);" style="width:120">
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
												<html:select styleClass="select01" property="dormitory" style="width:120">
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
												<html:text property="unit" styleClass="input_box" style="width:120" maxlength="4"/>
											</td>
										</tr>
										<tr align="center" valign=middle>
											<td width="30%" height="24" align="right" valign="middle" bgcolor="#DCC9CA" class="tableHeader2">
												宿舍
											</td>
											<td align="left" valign="middle">
												<html:text property="roomNumber" styleClass="input_box" style="width:120" maxlength="4"/>
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
								<strong class="medium">待调整人员</strong>
							</td>
							<td align="center" valign="top" bgcolor="#FFFFFF">
								&nbsp;
							</td>
							<td align="center" valign="middle" bgcolor="#ECE6E6" id="targetRoom">
								<strong class="medium">目标宿舍已住人员</strong>
							</td>
						</tr>
						<tr>
							<td align="center" valign="top" bgcolor="#ECE6E6">
								<select name="unbindStudentList" multiple="multiple" onDblClick="" size="15" style="width:250 px;">
								</select>
							</td>
							<td align="center" valign="middle" bgcolor="#FFFFFF">
								<p>
									<button name="moveRight" id="moveRight" type="button" class="button_nor" onclick="return dormitorySelCheck();">
										<bean:message bundle="classmanage" key="classBinding.right" />
									</button>
									<br />
									<br />
									<button name="moveLeft" id="moveLeft" type="button" class="button_nor" onclick="returnOption_dorm(document.all.bindStudentList, document.all.unbindStudentList,false);">
										<bean:message bundle="classmanage" key="classBinding.left" />
									</button>
									<br />
								</p>
							</td>
							<td align="center" valign="top" bgcolor="#ECE6E6">
								<select name="bindStudentList" multiple="multiple" onDblClick="" size="15" style="width:250 px;">
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
 
	function changeArea(area){
		document.all["location"].length=0;
		var areaId=area;
		var j1; 
		document.all["location"].options[document.all["location"].length]= new Option("---------------------","");
			for (j1=0;j1 < locationcount; j1++) 
			{ 
				if (locations[j1][2] == areaId) 
				{ 
					document.all["location"].options[document.all["location"].length]= new Option(locations[j1][1],locations[j1][0]);
					if(locations[j1][0]==<%=request.getAttribute("location")%>){
						document.all["location"].options[document.all["location"].length-1].selected=true;
					}
				} 
			} 
	}

setTimeout('DoInit()',10);
function DoInit(){

    var area = <%=request.getAttribute("area")%>;
    var location = <%=request.getAttribute("location")%>;
    var dormitory = <%=request.getAttribute("dormitory")%>;
    if(area!=null&&area!=''){
	changeArea(area);
	}
	if(location!=null&&location!=''){
	changeLocation(location);
	}
}
	 	 <!-- dormitory list -->
 
		var dormcount;
		dormcount = 0;
		dormitorys = new Array(); 
	<%	
		ArrayList dromitorylist=(ArrayList)request.getAttribute("dormitoryList");
		int arrayTag = 0;
		for(arrayTag=0;arrayTag<dromitorylist.size();arrayTag++){
			HashMap map = (HashMap)dromitorylist.get(arrayTag);
			String dormitoryid = (String)map.get("dictValue");
			String dormtioryname = (String)map.get("dictCaption");
			String location = (String)map.get("location");
	%>
		dormitorys[<%=arrayTag%>]= new Array("<%=dormitoryid%>","<%=dormtioryname%>","<%=location%>"); 
	<%	
		}	
	%>

	dormcount=<%=dromitorylist.size()%> 
  
	function changeLocation(location){
	    
		document.all["dormitory"].length=0;
		var locationId=location;
		var j; 
		document.all["dormitory"].options[document.all["dormitory"].length]= new Option("---------------------","");
			for (j=0;j < dormcount; j++) 
			{ 
				if (dormitorys[j][2] == locationId) 
				{ 
					document.all["dormitory"].options[document.all["dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
					if(dormitorys[j][0]==<%=request.getAttribute("dormitory")%>){
						document.all["dormitory"].options[document.all["dormitory"].length-1].selected=true;
					}
				} 
			} 
	} 
	var ustucount;
	ustucount = 0;
	unbindStudents = new Array(); 
	<%	
	if(request.getAttribute("unbindStudentList")!=null){	
		ArrayList unbindStudentList=(ArrayList)request.getAttribute("unbindStudentList");
		int k = 0;
		for(k=0;k<unbindStudentList.size();k++){
			HashMap unbindStu= (HashMap)unbindStudentList.get(k);
			String stuId = (String)unbindStu.get("id");
			String stuNo = (String)unbindStu.get("graduateNo");
			String stuName = (String)unbindStu.get("graduateName");
			String gender = (String)unbindStu.get("sex");
			String nation = (String)unbindStu.get("nation");
	%>
		unbindStudents[<%=k%>]= new Array("<%=stuId%>","<%=stuNo%> <%=stuName%>[<%=gender%>]","<%=gender%>","0","null"); 
		document.all["unbindStudentList"].options[document.all["unbindStudentList"].length]= new Option(unbindStudents[<%=k%>][1],unbindStudents[<%=k%>][0]);
	<%	
		}	
	%>
	ustucount=<%=unbindStudentList.size()%> 
	<%
	}
	%>
	var stucount;
	stucount = 0;
	bindStudents = new Array(); 
	<%	
	if(request.getAttribute("bindStudentList")!=null){	
		ArrayList bindStudentList=(ArrayList)request.getAttribute("bindStudentList");
		int m = 0;
		String stuId ="";
		String stuNo="";
		String stuName="";
		String gender="";
		String dormitoryId="";
		String accomodation="";
		for(m=0;m<bindStudentList.size();m++){
			HashMap bindStu= (HashMap)bindStudentList.get(m);
			stuId = bindStu.get("stuId").toString();
			stuNo = bindStu.get("stuNo").toString();
			stuName = bindStu.get("stuName").toString();
			gender = bindStu.get("gender").toString();
			dormitoryId = bindStu.get("dormitoryId").toString();
			accomodation = bindStu.get("accomodation").toString();

	%>
		bindStudents[<%=m%>]= new Array("<%=stuId%>","<%=stuNo%> <%=stuName%>[<%=gender%>]","<%=gender%>","<%=accomodation%>","<%=dormitoryId%>"); 
		document.all["bindStudentList"].options[document.all["bindStudentList"].length]= new Option(bindStudents[<%=m%>][1],bindStudents[<%=m%>][0]);
	<%	
		}	
		if(bindStudentList.size()==0&&request.getAttribute("dormmo")!=null){
						Dormitorymodel dormmo = (Dormitorymodel)request.getAttribute("dormmo");
						if("1".equals(dormmo.getGender()))
							gender = "男";
						else
						    gender = "女";
						accomodation = Integer.toString(dormmo.getAccomodation());
		}
	%>
	if(document.all["mydormitoryId"].value==""){

		if(document.getElementById("targetRoom")!=null){
			document.getElementById("targetRoom").innerHTML='<strong class="medium">目标宿舍已住人员</strong>'
		}
	}else{
		if(document.getElementById("targetRoom")!=null){
			document.getElementById("targetRoom").innerHTML='<strong class="medium">目标宿舍已住人员 <font color="#7F0055">[<%=gender%>][<%=accomodation%>]</font></strong>'
		}
	}
	stucount=<%=bindStudentList.size()%> 	
	<%
	}
	%>
	 

	 function my_onload(){	 	
	 	if(document.all("location").value!=""){	 	
	 		document.all["dormitory"].length=0;
			var j; 
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all("location").value) 
				{ 
					document.all["dormitory"].options[document.all["dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("myDormitory").value){
					document.all("dormitory").options[document.all("dormitory").length-1].selected=true;
				}
			} 
	 	}
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}	 	
	 }
	 
	 window.onload=my_onload;	 



function setValue(){
	if(document.all.mydormitoryId.value!=""){
		document.all.unbindStudents.value=unbindStudents;
		document.all.bindStudents.value=bindStudents;
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
	 		unbindStudents[index] = new Array(bindStudents[i][0],bindStudents[i][1],bindStudents[i][2],"0","null");
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
	 		bindStudents[index] = new Array(unbindStudents[i][0],unbindStudents[i][1],unbindStudents[i][2],"0",document.all.mydormitoryId.value);
	 		unbindStudents[i][0]="";
	 		unbindStudents[i][1]="";
	 		unbindStudents[i][2]="";
	 		unbindStudents[i][3]="";
	 		unbindStudents[i][4]="";
	 		stucount++;	 		
	 	}
	 
}

}

function dormitorySelCheck(){
	if(document.all.mydormitoryId.value==""){
		alert("请先选择目标宿舍");
		return false;
	}
	transferOption_dorm(document.all("unbindStudentList"), document.all("bindStudentList"),false)
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

</script>

