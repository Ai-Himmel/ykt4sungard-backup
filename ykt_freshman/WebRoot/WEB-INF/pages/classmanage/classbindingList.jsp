<%@page pageEncoding="UTF-8"%>
<%@ page import="org.king.classmanage.domain.Classmodel"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.HashMap"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.classmanage.web.help.DormitoryBindInfo"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<html:form action="classAction.do?method=saveBinding" onsubmit="javascript:return setValue();">
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
				<html:hidden property="binddormitorys" />
				<html:hidden property="unbinddormitorys" />
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium"><bean:message bundle="classmanage" key="classBinding.classBinding" /></font></strong>
					</td>
				</tr>
				<tr>
					<td align="left" valign="top">
						<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
					</td>
				</tr>
				<tr>
					<td align="center" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td width="28%" align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td width="1%" align="center" valign="top" bgcolor="#FFFFFF">
									&nbsp;
								</td>
								<td width="33%" align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td align="center">
									&nbsp;
								</td>
								<td width="33%" align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
							</tr>
							<tr>
								<td align="center" valign="middle" bgcolor="#ECE6E6">
									<span class="medium"><bean:message bundle="classmanage" key="classBinding.college" /></span>
									<html:select property="college" onchange="javascript:changeCollge(this.options[this.selectedIndex].value);">
										<html:option value="">---------------------</html:option>
										<html:options collection="collegeList" labelProperty="collegeName" property="collegeId" />
									</html:select>
								</td>
								<td align="center" valign="top" bgcolor="#FFFFFF">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									<span class="medium"><bean:message bundle="classmanage" key="classBinding.location" /></span>
									<html:select property="dormitorymodel.location" onchange="javascript:changeLocation(this.value);">
										<html:option value="">---------------------</html:option>
										<html:options collection="locationList" labelProperty="dictCaption" property="dictValue" />
									</html:select>
									<br>
									<span class="medium"><bean:message bundle="classmanage" key="classBinding.building" /></span>
									<SELECT name="dormitorymodel.dormitory" onchange="javascript:changeDormitory(this.value);">
										<OPTION value="">
											---------------------
										</OPTION>
									</SELECT>
								</td>
								<td align="center">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6" id="showlabel">
									--已绑定宿舍列表--
								</td>
							</tr>
							<tr>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#FFFFFF">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td align="center">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
							</tr>
							<tr>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									--班级选择--
									<br>
									<select name="classes" size="20" style="width:200 px;" onchange="javascript:changeClass(this.value,this.options[this.selectedIndex].text);">
									</select>
								</td>
								<td align="center" valign="top" bgcolor="#FFFFFF">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									--宿舍选择--
									<br>
									<select name="unbinddormitory" multiple="multiple" onDblClick="" size="20" style="width:240 px;">
									</select>

								</td>
								<td align="center">
									<p>
										<button name="moveRight" id="moveRight" type="button" class="button_nor" onclick="return classSelCheck();">
											<bean:message bundle="classmanage" key="classBinding.right" />
										</button>
										<br />
										<br />
										<button name="moveLeft" id="moveLeft" type="button" class="button_nor" onclick="returnOption(this.form.binddormitory, this.form.unbinddormitory,false)">
											<bean:message bundle="classmanage" key="classBinding.left" />
										</button>
										<br />
									</p>
								</td>
								<td width="30%" align="center" valign="top" bgcolor="#ECE6E6">
									<br>
									<font color="#FF0000"><select name="binddormitory" multiple="multiple" onDblClick="" size="20" style="width:240 px;">
										</select></font>

								</td>
							</tr>
							<tr>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#FFFFFF">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td align="center">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
							</tr>

							<tr align="right" valign="middle">
								<td height="50" colspan="5">
									<html:submit property="sure" styleClass="button_nor">
										<bean:message bundle="classmanage" key="studentsearch.sure" />
									</html:submit>
								</td>
							</tr>
						</table>
					</td>
				</tr>
			</html:form>
		</table>
	</body>

</center>

<script language="JavaScript">
	var boyDorm = 0;
	var boyPlace = 0;
	var girlDorm = 0;
	var girlPlace = 0;	
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
			String classNo = classmodel.getClassNo();
			String collegeId = classmodel.getYxCollege().getCollegeId();
	%>
			classes[<%=i%>]= new Array("<%=classid%>","<%=classNo%>","<%=collegeId%>"); 
	<%	
		}	
	%>
	classescount=<%=classeslist.size()%>
	
	function changeCollge(college){
	 	document.all.classes.length=0;
	 	var collegeId=college; 
		var j; 
		for (j=0; j<classescount; j++) 
		{ 
			if (classes[j][2] == collegeId) 
			{ 
				document.all.classes.options[document.all.classes.length]= new Option(classes[j][1],classes[j][0]);
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
			//Dictionary building = (Dictionary)dromitorylist.get(l);
			//String dormitoryid = building.getId().getDictValue();
			//String dormtioryname = building.getDictCaption();
			//String location = building.getDictParent();
			String dormitoryid = (String)map.get("dictValue");
			String dormtioryname = (String)map.get("dictCaption");
			String location = (String)map.get("dictParent");						
	%>
		dormitorys[<%=l%>]= new Array("<%=dormitoryid%>","<%=dormtioryname%>","<%=location%>"); 
	<%	
		}	
	%>

	dormcount=<%=dromitorylist.size()%> 
 
function changeLocation(location){
	document.all["dormitorymodel.dormitory"].length=0;
	var locationId=location;
	var j; 
	document.all["dormitorymodel.dormitory"].options[document.all["dormitorymodel.dormitory"].length]= new Option("---------------------","");
		for (j=0;j < dormcount; j++) 
		{ 
			if (dormitorys[j][2] == locationId) 
			{ 
				document.all["dormitorymodel.dormitory"].options[document.all["dormitorymodel.dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
			} 
		} 
}

<!-- bindeddormitory list -->
 
 
 		var binddormcount;
		binddormcount = 0;
		binddormitorys = new Array(); 
	<%	
		ArrayList binddormlist=(ArrayList)request.getAttribute("bindeddormList");
		int m = 0;
		for(m=0;m<binddormlist.size();m++){
			DormitoryBindInfo dormitorybindinfo= (DormitoryBindInfo)binddormlist.get(m);
			String dormitoryId = dormitorybindinfo.getDormitoryId();
			String locationCode =  dormitorybindinfo.getLocation();
			String locationStr =  dormitorybindinfo.getLocationStr();
			String dormitoryCode =  dormitorybindinfo.getDormitory();
			String dormitoryStr =   dormitorybindinfo.getDormitoryStr();
			String roomnumber=  dormitorybindinfo.getRoomNumber();
			String genderStr =	 dormitorybindinfo.getGender();
			String directionStr =	 dormitorybindinfo.getDirection();			
			int accomodation =  dormitorybindinfo.getAccomodation();
			String classId =   dormitorybindinfo.getClassId();
	%>
		binddormitorys[<%=m%>]= new Array("<%=dormitoryId%>","<%=locationStr%><%=dormitoryStr%>-<%=roomnumber%> [<%=directionStr%>] [<%=genderStr%>] [<%=accomodation%>]","<%=dormitoryCode%>","<%=genderStr%>","<%=accomodation%>","<%=classId%>"); 
	<%	
		}	
	%>

	binddormcount=<%=binddormlist.size()%> 
 
function changeClass(classId,title){
	boyDorm = 0;
	boyPlace = 0;
	girlDorm = 0;
	girlPlace = 0;	
	document.all["binddormitory"].length=0;
	var classId=classId;
	var j; 
		for (j=0;j < binddormcount; j++) { 
			if (binddormitorys[j][5] == classId) 
			{ 
				if(binddormitorys[j][3]=='男'){
					boyDorm++;
					boyPlace += parseInt(binddormitorys[j][4],10);
				}
				if(binddormitorys[j][3]=='女'){
					girlDorm++;
					girlPlace += parseInt(binddormitorys[j][4],10);
				}
				document.all["binddormitory"].options[document.all["binddormitory"].length]= new Option(binddormitorys[j][1],binddormitorys[j][0]);
			} 
		}
		document.getElementById("showlabel").innerHTML=title+' 已绑定宿舍列表<br> 男生宿舍数:'+boyDorm+'&nbsp;&nbsp;女生宿舍数:'+girlDorm+'<br>男生床位数:'+boyPlace+'&nbsp;&nbsp;女生床位数:'+girlPlace; 
}

<!-- unbindeddormitory list -->

 		var unbinddormcount;
		unbinddormcount = 0;
		unbinddormitorys = new Array(); 
	<%	
		ArrayList unbinddormlist=(ArrayList)request.getAttribute("roomList");
		int n = 0;
		for(n=0;n<unbinddormlist.size();n++){
		DormitoryBindInfo dormitorybindinfo= (DormitoryBindInfo)unbinddormlist.get(n);
			String dormitoryId = dormitorybindinfo.getDormitoryId();
			String locationCode =  dormitorybindinfo.getLocation();
			String locationStr =  dormitorybindinfo.getLocationStr();
			String dormitoryCode =  dormitorybindinfo.getDormitory();
			String dormitoryStr =   dormitorybindinfo.getDormitoryStr();
			String roomnumber=  dormitorybindinfo.getRoomNumber();
			String directionStr =	 dormitorybindinfo.getDirection();			
			String genderStr =	 dormitorybindinfo.getGender();
			int accomodation =  dormitorybindinfo.getAccomodation();
			String classId =   dormitorybindinfo.getClassId();
	%>
		unbinddormitorys[<%=n%>]= new Array("<%=dormitoryId%>","<%=locationStr%><%=dormitoryStr%>-<%=roomnumber%> [<%=directionStr%>] [<%=genderStr%>] [<%=accomodation%>]","<%=dormitoryCode%>","<%=genderStr%>","<%=accomodation%>","<%=classId%>"); 
	<%	
		}	
	%>

	unbinddormcount=<%=unbinddormlist.size()%> 
 
function changeDormitory(dormitory){
	document.all["unbinddormitory"].length=0;
	var dormitory=dormitory;
	var j; 	
		for (j=0;j < unbinddormcount; j++) 
		{ 
			if (unbinddormitorys[j][2] == dormitory) 
			{ 
				document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][1],unbinddormitorys[j][0]);
			} 
		} 
}

function classSelCheck(){
	if(document.all("classes").value==""){
		alert("请选择需要调整的班级");
		document.all("college").focus();
		return false;
	}
	transferOption(document.all.unbinddormitory, document.all.binddormitory,document.all.classes,false)
	return true;

}

function uiOptionReturn_putArrayItem(dormitoryId){
	var dormitory_id = dormitoryId;
	var i;
	var index = 0;
	index = unbinddormitorys.length;
	for(i=0;i<binddormitorys.length;i++){	
	 	if(binddormitorys[i][0]==dormitory_id){
	 		unbinddormitorys[index] = new Array(binddormitorys[i][0],binddormitorys[i][1],binddormitorys[i][2],binddormitorys[i][3],binddormitorys[i][4],"null");
	 		binddormitorys[i][0]="";
	 		binddormitorys[i][1]="";
	 		binddormitorys[i][2]="";
	 		binddormitorys[i][3]="";
	 		binddormitorys[i][4]="";
	 		binddormitorys[i][5]="";
	 		unbinddormcount++;
	 		if(unbinddormitorys[index][3]=='男'){
					boyDorm--;
					boyPlace -= parseInt(unbinddormitorys[index][4],10);
				}
			if(unbinddormitorys[index][3]=='女'){
					girlDorm--;
					girlPlace -= parseInt(unbinddormitorys[index][4],10);
				}
	 	} 	
 }
 document.getElementById("showlabel").innerHTML=document.all("classes").options[document.all("classes").selectedIndex].text+' 已绑定宿舍列表<br> 男生宿舍数:'+boyDorm+'&nbsp;&nbsp;女生宿舍数:'+girlDorm+'<br>男生床位数:'+boyPlace+'&nbsp;&nbsp;女生床位数:'+girlPlace; 

}

//add classId to unbinddormitory's record   
//and add this record to binddormitory
//and delete this record from unbinddormitory
function uiOptionTransfer_putArrayItem(dormitoryId, classId){
	var dormitory_id = dormitoryId;
	var class_id = classId;
	var i;
	var index = 0;
	index = binddormitorys.length;
	for(i=0;i<unbinddormitorys.length;i++){	
	 	if(unbinddormitorys[i][0]==dormitory_id){
	 		binddormitorys[index] = new Array(unbinddormitorys[i][0],unbinddormitorys[i][1],unbinddormitorys[i][2],unbinddormitorys[i][3],unbinddormitorys[i][4],class_id);
	 		unbinddormitorys[i][0]="";
	 		unbinddormitorys[i][1]="";
	 		unbinddormitorys[i][2]="";
	 		unbinddormitorys[i][3]="";
	 		unbinddormitorys[i][4]="";
	 		unbinddormitorys[i][5]="";
	 		binddormcount++;
	 		if(binddormitorys[index][3]=='男'){
				boyDorm++;
				boyPlace += parseInt(binddormitorys[index][4],10);
			}
			if(binddormitorys[index][3]=='女'){
				girlDorm++;
				girlPlace += parseInt(binddormitorys[index][4],10);
			}
	 	}	 	
 }
 document.getElementById("showlabel").innerHTML=document.all("classes").options[document.all("classes").selectedIndex].text+' 已绑定宿舍列表<br> 男生宿舍数:'+boyDorm+'&nbsp;&nbsp;女生宿舍数:'+girlDorm+'<br>男生床位数:'+boyPlace+'&nbsp;&nbsp;女生床位数:'+girlPlace; 

}


function setValue(){
	document.all.binddormitorys.value=binddormitorys;
	document.all.unbinddormitorys.value=unbinddormitorys;
	return true;
}


function returnOption(e1,e2,all){
  	var src = e2.options;
  	var tgt = e1.options;
  	var items;
  	var index;
  	for (var i = tgt.length - 1; i >= 0; --i) {
    	if (all || tgt[i].selected) { 
			clone = uiCommon_cloneSelectOption(tgt[i]);
  			src.add(clone);
  			uiOptionReturn_putArrayItem(tgt[i].value);
  			tgt[i] = null;
  		}
  	}
}


function transferOption(e1,e2,e3,all){
  	var src = e2.options;
  	var tgt = e1.options;
  	var index = e3.selectedIndex;
	var classes = e3.options;
  	var items;
  	for (var i = tgt.length - 1; i >= 0; --i) {
    	if (all || tgt[i].selected) { 
			clone = uiCommon_cloneSelectOption(tgt[i]);
  			src.add(clone);
  			uiOptionTransfer_putArrayItem(tgt[i].value, classes[index].value);
  			tgt[i] = null;
  		}
  	}
}

function uiCommon_cloneSelectOption(opt) {
  return new Option(opt.text, opt.value,
                    opt.defaultSelected, opt.selected);
}
	
	
	 function my_onload(){

	 	if(document.all("college").value!=""){
		 	document.all("classes").length=0;
			var j; 
			for (j=0; j<classescount; j++) 
			{ 
				if (classes[j][2] == document.all("college").value) 
				{ 
					document.all("classes").options[document.all("classes").length]= new Option(classes[j][1],classes[j][0]);
					if(classes[j][0]==document.all("myclass").value){
						document.all("classes").options[document.all("classes").length-1].selected=true;
						 changeClass(document.all("classes").value,document.all("classes").options[document.all("classes").selectedIndex].text);
					}
				} 
			} 
	 	}	
	 	
	 	if(document.all("dormitorymodel.location").value!=""){	 	
	 		document.all["dormitorymodel.dormitory"].length=0;
			var j; 
			document.all["dormitorymodel.dormitory"].options[document.all["dormitorymodel.dormitory"].length]= new Option("---------------------","");
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all("dormitorymodel.location").value) 
				{ 
					document.all["dormitorymodel.dormitory"].options[document.all["dormitorymodel.dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("mydormitory").value){
					document.all("dormitorymodel.dormitory").options[document.all("dormitorymodel.dormitory").length-1].selected=true;
					changeDormitory(document.all("dormitorymodel.dormitory").value);
				}
			} 
	 	}
	 	 	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	 } 


	 window.onload=my_onload;	

</script>
