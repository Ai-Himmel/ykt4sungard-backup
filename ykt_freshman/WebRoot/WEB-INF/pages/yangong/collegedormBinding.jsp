<%@ page pageEncoding="GBK"%>
<%@ page
	import="org.king.yangong.dormitorymanage.web.help.CollegeBindingInfo"%>
<%@ page
	import="org.king.yangong.dormitorymanage.web.help.YangongDormitoryBindInfo"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.HashMap"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.classmanage.domain.DictionaryId"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<html:form action="collegeDormBindingAction.do?method=save&getrole=3">
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium"><bean:message
									bundle="yangongdormmanage" key="graduate.collegedormbinding" />
						</font> </strong>
					</td>
				</tr>
				<tr>
					<td align="center" valign="top" height="10">
						<html:hidden property="binddormitorys" />
						<html:hidden property="unbinddormitorys" />
						<INPUT type="hidden" name="myerror"
							value="<html:errors bundle="yangongdormmanage" />">
					</td>
				</tr>

				<tr>
					<td height="40" width="40%" align="center" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td valign="top">
									<table width="98%" border="1" align="center" cellpadding="1"
										cellspacing="0" bordercolor="#AA817F"
										bordercolordark="#FFFFFF" id="submenu1">
										<tbody>
											<tr align="center" valign="middle">
											</tr>
											<tr align="center" valign="middle">
												<td height="24" align="center" valign="middle"
													bgcolor="#FFFFFF" style="padding:10px 0px 11px 0px;">																
													<br>
													<span class="medium"><bean:message
															bundle="yangongdormmanage" key="graduate.college1" /> </span>
													<html:select styleClass="select01" property="curCollege">
														<html:option value="">------------------------------------------</html:option>
														<logic:present name="collegeList" scope="request">
															<html:options collection="collegeList"
																labelProperty="deptName" property="deptCode" />
														</logic:present>
													</html:select>
													<br>
													<span class="medium"><bean:message
															bundle="yangongdormmanage" key="graduate.sex" /> </span>
													<html:select styleClass="select01" property="sex">
														<html:option value="">------------------------------------------</html:option>
														<logic:present name="sexList" scope="request">
															<html:options collection="sexList"
																labelProperty="dictCaption" property="id.dictValue" />
														</logic:present>
													</html:select>
													<br>
													<span class="medium"><bean:message
															bundle="yangongdormmanage" key="graduate.studenttype1" />
													</span>
													<html:select styleClass="select01" property="studentType">
														<html:option value="">------------------------------------------</html:option>
														<logic:present name="studentTypeList" scope="request">
															<html:options collection="studentTypeList"
																labelProperty="dictCaption" property="id.dictValue" />
														</logic:present>
													</html:select>
													<br>
													<span class="medium" style="height: 24">&nbsp;</span>
												</td>
											</tr>
											<tr align="center" valign=middle>
												<td height="15" colspan="2" align="right" valign="middle"
													class="medium">
													<html:button property="query1" styleClass="button_nor"
														onclick="javascript:changeCollge(document.all.sex.value,document.all.studentType.value,document.all.curCollege.value);">
														<bean:message key="button.query" />
													</html:button>
												</td>
											</tr>
											<tr>
												<td height="24" valign="middle" class="tableHeader">
													<strong>-- <bean:message
															bundle="yangongdormmanage" key="graduate.collegeSelect" />
														--</strong>
												</td>
											</tr>
											<tr align="center" valign="middle" bgcolor="#F6F4F5">
												<td height="20" align="center" valign="middle"
													class="graduate_select">
													<select name="colleges" size="16" style="width:250 px;"
														multiple="multiple"
														onchange="javascript:selectCollege(this.value,this.options[this.selectedIndex].text);">
													</select>
												</td>
											</tr>
										</tbody>
									</table>
								</td>
								<td valign="top" >
									<table width="98%" border="1" align="center" cellpadding="1"
										cellspacing="0" bordercolor="#AA817F"
										bordercolordark="#FFFFFF" id="submenu1">
										<tbody>
											<tr align="center" valign="middle">
												<td height="24" align="center" valign="middle"
													bgcolor="#FFFFFF" style="padding:10px 0px 11px 0px;">
													<span class="medium"><bean:message
															bundle="yangongdormmanage" key="graduate.section" /> </span>
													<html:select styleClass="select01" property="section"
														onchange="javascript:changeArea(this.value);">
														<html:option value="">------------------------------------------</html:option>
														<logic:present name="sectionList" scope="request">
															<html:options collection="sectionList"
																labelProperty="dictCaption" property="dictValue" />
														</logic:present>
													</html:select>

													<br>
													<span class="medium"><bean:message
															bundle="yangongdormmanage" key="graduate.districtrion2" />
													</span>
													<html:select styleClass="select01" property="distriction"
														onchange="javascript:changeDistriction(this.value);">
														<html:option value="">------------------------------------------</html:option>
														<logic:present name="districtionList" scope="request">
															<html:options collection="districtionList"
																labelProperty="dictCaption" property="dictValue" />
														</logic:present>
													</html:select>

													<br>
													<span class="medium"><bean:message
															bundle="yangongdormmanage" key="graduate.building" /> </span>
													<html:select styleClass="select01" property="building">
														<html:option value="">------------------------------------------</html:option>
														<logic:present name="buildingList" scope="request">
															<html:options collection="buildingList"
																labelProperty="dictCaption" property="dictValue" />
														</logic:present>
													</html:select>
													<br>
													<span class="medium"><bean:message
															bundle="yangongdormmanage" key="graduate.layer" /> </span>
													<html:text property="layer" styleClass="input_box" style="width:195" maxlength="4"/>
													<br>
													<span class="medium"><bean:message
															bundle="yangongdormmanage" key="graduate.unit" /> </span>
													<html:text property="cell" styleClass="input_box" style="width:195" maxlength="4"/>													
												   
												</td>
											</tr>
											<tr align="center" valign=middle>
												<td height="15" colspan="2" align="right" valign="middle"
													class="medium">
													<html:button property="query2" styleClass="button_nor"
														onclick="javascript:changeLocation(document.all.section.value,document.all.distriction.value,document.all.building.value,document.all.layer.value,document.all.cell.value);">
														<bean:message key="button.query" />
													</html:button>
												</td>
											</tr>
											<tr align="center" valign="middle">
												<td height="24" valign="middle" class="tableHeader">
													<strong>-- <bean:message
															bundle="yangongdormmanage" key="graduate.buildingSelect" />
														--</strong>
												</td>
											</tr>

											<tr align="center" valign="middle" bgcolor="#F6F4F5">
												<td height="20" align="center" valign="middle"
													class="graduate_select">
													<select name="unbinddormitory" size="16"
														multiple="multiple" style="width:250 px;" ondblclick="return classSelCheck();">
													</select>

												</td>
											</tr>
										</tbody>
									</table>
								</td>
								<td align="center">
									<button name="moveRight" id="moveRight" type="button"
										class="button_nor" onClick="return classSelCheck();">
										>>
									</button>
									<br />
									<br />
									<button name="moveLeft" id="moveLeft" type="button"
										class="button_nor"
										onClick="return classDelCheck();">
										<<
									</button>
								</td>
								<td valign="top">
									<table width="98%" border="1" align="center" cellpadding="1"
										cellspacing="0" bordercolor="#AA817F"
										bordercolordark="#FFFFFF" id="submenu1">
										<tbody>
											<tr align="center" valign="middle">
												<td height="24" align="center" valign="middle"
													bgcolor="#FFFFFF" class="medium"
													style="padding:10px 0px 11px 0px;" id="showlabel">
													&nbsp;
													<br>
													<br>
													<br>													
													<bean:message bundle="yangongdormmanage"
														key="graduate.buildingbindedList" />
													
													<p>	
																				
												</td>
											</tr>
											<tr align="center" valign=middle>
												<td height="15" colspan="2" align="right" valign="middle"
													class="medium">
													&nbsp;
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="24" valign="middle" class="tableHeader">
													<strong>-- <bean:message
															bundle="yangongdormmanage" key="graduate.buildingbinded" />
														--</strong>
												</td>

											</tr>
											<tr align="center" valign=center bgcolor="#F6F4F5">
												<td height="24" align="center" valign="middle"
													class="graduate_select">
													<font color="#FF0000"> <select name="binddormitory"
															multiple="multiple" size="16" style="width:250 px;" ondblclick="return classDelCheck();">
														</select> </font>
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
						</table>
					</td>
				</tr>

				<tr>
					<td height="30" align="right" valign="middle">
					<a href="javascript:DoViewBindResult()">院系宿舍绑定结果查看</a>
						<html:submit property="sure" styleClass="button_nor"
							onclick="javascript:return setValue();">
							<bean:message bundle="classmanage" key="studentsearch.sure" />
						</html:submit>
					</td>
				</tr>
			</html:form>
		</table>
	</body>
</center>

<script language="JavaScript">
	var Dorm = 0;
	var Place = 0;
<!-- college list -->
	var collegescount;
	collegescount = 0;
	colleges = new Array(); 
	<%	
		ArrayList collegebindingList=(ArrayList)request.getAttribute("collegebindingList");
		int i = 0;
		if(collegebindingList!=null){
		for(i=0;i<collegebindingList.size();i++){
			CollegeBindingInfo collegeBindingInfo = (CollegeBindingInfo)collegebindingList.get(i);
			String curCollege=collegeBindingInfo.getCurCollege();
			String curCollegeStr=collegeBindingInfo.getCurCollegeStr();
			String studentType = collegeBindingInfo.getStudentType();
			String studentTypeStr = collegeBindingInfo.getStudentTypeStr();
			String sex = collegeBindingInfo.getSex();
			String sexStr = collegeBindingInfo.getSexStr();
			int count = collegeBindingInfo.getCount();
	%>
			colleges[<%=i%>]= new Array("<%=curCollege%>-<%=sex%>-<%=studentType%>","<%=studentType%>","<%=sex%>","<%=curCollegeStr%>[<%=studentTypeStr%>][<%=sexStr%>][<%=count%>]","<%=count%>"); 
	<%	
		}
		}
		if(collegebindingList!=null){
	%>
	collegescount=<%=collegebindingList.size()%>;
	<%}else{%>
	collegescount=0;
	<%}%>
		var districtioncount;
		districtioncount = 0;
		districtions = new Array(); 
	<%	
		ArrayList districtionlist=(ArrayList)request.getAttribute("districtionList");
		int r = 0;
		if(districtionlist!=null){
		for(r=0;r<districtionlist.size();r++){
			HashMap dicinfo = (HashMap)districtionlist.get(r);
			String aaa = (String)dicinfo.get("dictValue");
			String bbb = (String)dicinfo.get("dictCaption");
			String ccc = (String)dicinfo.get("dictParent");
	%>
		districtions[<%=r%>]= new Array("<%=aaa%>","<%=bbb%>","<%=ccc%>"); 
	<%	
		}
		}
		if(districtionlist!=null){
	%>

	districtioncount=<%=districtionlist.size()%>;
	<%}else{%>
	districtioncount=0;
	<%}%>
	
		var buildingcount;
		buildingcount = 0;
		buildings = new Array(); 
	<%	
		ArrayList buildinglist=(ArrayList)request.getAttribute("buildingList");
		int t = 0;
		if(buildinglist!=null){
		for(t=0;t<buildinglist.size();t++){
			HashMap dicinfo = (HashMap)buildinglist.get(t);
			String aaa = (String)dicinfo.get("dictValue");
			String bbb = (String)dicinfo.get("dictCaption");
			String ccc = (String)dicinfo.get("dictParent");
	%>
		buildings[<%=t%>]= new Array("<%=aaa%>","<%=bbb%>","<%=ccc%>"); 
	<%	
		}
	%>

	buildingcount=<%=buildinglist.size()%>;
	<%}else{%>
	buildingcount=0;
	<%}%>
	
	function changeCollge(sex,type,college){
	    
	    if(sex==''&&type==''&&college==''){
	         alert("查询条件不能全为空!");
	         return;
	    }
	 	document.all.colleges.length=0;
	 	var collegeId=college;
	 	var newcollegeid;
	 	var studentType = type;
	 	var gender = sex; 
		var j; 
		for (j=0; j<collegescount; j++) 
		{ 
		newcollegeid = colleges[j][0];
		newcollegeid = newcollegeid.substring(0,newcollegeid.indexOf('-'));
		if(collegeId!=''){
			if(studentType!=''){
				if(gender!=''){
					if ((newcollegeid == collegeId)&&(colleges[j][1]==studentType)&&(colleges[j][2]==gender)) 
					{ 
						document.all.colleges.options[document.all.colleges.length]= new Option(colleges[j][3],colleges[j][0]);
					}
				}else{
					if ((newcollegeid == collegeId)&&(colleges[j][1]==studentType)) 
					{ 
						document.all.colleges.options[document.all.colleges.length]= new Option(colleges[j][3],colleges[j][0]);
					}
				}
			}else{
				if(gender!=''){
					if ((newcollegeid == collegeId)&&(colleges[j][2]==gender)) 
					{ 
						document.all.colleges.options[document.all.colleges.length]= new Option(colleges[j][3],colleges[j][0]);
					}
				}else{
					if ((newcollegeid == collegeId)) 
					{ 
						document.all.colleges.options[document.all.colleges.length]= new Option(colleges[j][3],colleges[j][0]);
					}
				}
			}
		}else{
			if(studentType!=''){
				if(gender!=''){
					if ((colleges[j][1]==studentType)&&(colleges[j][2]==gender)) 
					{ 
						document.all.colleges.options[document.all.colleges.length]= new Option(colleges[j][3],colleges[j][0]);
					}
				}else{
					if ((colleges[j][1]==studentType)) 
					{ 
						document.all.colleges.options[document.all.colleges.length]= new Option(colleges[j][3],colleges[j][0]);
					}
				}
			}else{
				if(gender!=''){
					if ((colleges[j][2]==gender)) 
					{ 
						document.all.colleges.options[document.all.colleges.length]= new Option(colleges[j][3],colleges[j][0]);
					}
				}else{
						document.all.colleges.options[document.all.colleges.length]= new Option(colleges[j][3],colleges[j][0]);
				}
			}
			
		} 
		
	 }
	}
	
	
	function changeArea(area){
	document.all["distriction"].length=0;
	document.all["building"].length=0;
	var areaId=area;
	var j; 
	document.all["distriction"].options[document.all["distriction"].length]= new Option("------------------------------------------","");
	document.all["building"].options[document.all["building"].length]= new Option("------------------------------------------","");
		for (j=0;j < districtioncount; j++) 
		{ 
			if (districtions[j][2] == areaId) 
			{ 
				document.all["distriction"].options[document.all["distriction"].length]= new Option(districtions[j][1],districtions[j][0]);
				if(districtions[j][0]==<%=request.getAttribute("distriction")%>){
					document.all["distriction"].options[document.all["distriction"].length-1].selected=true;
					changeDistriction(document.all["distriction"].value);
				}
			} 
		} 
	}
	function changeDistriction(location){
	document.all["building"].length=0;
	var locationId=location;
	var j; 
	document.all["building"].options[document.all["building"].length]= new Option("------------------------------------------","");
		for (j=0;j < buildingcount; j++) 
		{ 
			if (buildings[j][2] == locationId) 
			{ 
				document.all["building"].options[document.all["building"].length]= new Option(buildings[j][1],buildings[j][0]);
				if(buildings[j][0]==<%=request.getAttribute("building")%>){
					document.all["building"].options[document.all["building"].length-1].selected=true;
				}
			} 
		} 
	}
	 
	 <!-- dormitory list -->
 
		var unbinddormcount;
		unbinddormcount = 0;
		unbinddormitorys = new Array(); 
	<%	
		ArrayList unbinddormitoryList=(ArrayList)request.getAttribute("unbinddormitoryList");
		int l = 0;
		if(unbinddormitoryList!=null){
		for(l=0;l<unbinddormitoryList.size();l++){
			YangongDormitoryBindInfo unbinddormitory = (YangongDormitoryBindInfo)unbinddormitoryList.get(l);
			String dormitoryId = unbinddormitory.getDormitoryId();
			String area = unbinddormitory.getArea();
			String areaStr = unbinddormitory.getAreaStr();
			String location = unbinddormitory.getLocation();
			String locationStr = unbinddormitory.getLocationStr();
			String dormitory = unbinddormitory.getDormitory();
			String dormitoryStr = unbinddormitory.getDormitoryStr();
			String level = unbinddormitory.getLevel();
			String levelStr = unbinddormitory.getLevel()+"层";
			String unit = unbinddormitory.getUnit();
			String unitStr = unbinddormitory.getUnit();
			String sex = unbinddormitory.getGender();
			String sexStr = unbinddormitory.getGenderStr();
			String directionStr = unbinddormitory.getDirectionStr();
			String roomNumber = unbinddormitory.getRoomNumber();
			int emptyNum = unbinddormitory.getEmptyNum();
			String collegeId = unbinddormitory.getCollegeId();
	%>
		unbinddormitorys[<%=l%>]= new Array("<%=dormitoryId%>","<%=area%>","<%=location%>","<%=dormitory%>","<%=sex%>","<%=emptyNum%>","<%=areaStr%><%=locationStr%><%=dormitoryStr%><%=levelStr%><%=unitStr%><%=roomNumber%>[<%=directionStr%>][<%=sexStr%>][<%=emptyNum%>]","<%=areaStr%><%=locationStr%><%=dormitoryStr%><%=levelStr%><%=unitStr%><%=roomNumber%>[<%=directionStr%>][<%=sexStr%>]","<%=collegeId%>","<%=unit%>","<%=level%>"); 
	<%	
		}	
	%>

	unbinddormcount=<%=unbinddormitoryList.size()%> 
	<%}else{%>
	unbinddormcount=0;
	<%}%>
 
function changeLocation(area,location,dormitory,ly,cl){

    if(area==''&&location==''&&dormitory==''&&ly==''&&cl==''){
        alert("查询条件不能全为空！");
        return;
    }
	document.all["unbinddormitory"].length=0;
	var areaId = area;
	var locationId=location;	
	var dormitoryId = dormitory;
	var layerId=ly;
	var cellId=cl;
	var j; 
	for (j=0;j < unbinddormcount; j++) 
		{ 
			if(areaId!=''){
				if(locationId!=''){
					if(dormitoryId!=''){
					  if(layerId!=''){
					    if(cellId!=''){
						    if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][3]==dormitoryId)&&(unbinddormitorys[j][10]==layerId)&&(unbinddormitorys[j][9]==cellId)) 
						    { 
							    if(unbinddormitorys[j][0]!=''){
								    document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
							    }
						    }						     
						}
						else{
						    if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][3]==dormitoryId)&&(unbinddormitorys[j][10]==layerId)) 
						    { 
							    if(unbinddormitorys[j][0]!=''){
								    document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
							    }
						    }						    
						}
					  }
					  else{
					    if(cellId!=''){
						    if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][3]==dormitoryId)&&(unbinddormitorys[j][9]==cellId)) 
						    { 
							    if(unbinddormitorys[j][0]!=''){
								    document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
							    }
						    }						     
						}
						else{
						    if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][3]==dormitoryId)) 
						    { 
							    if(unbinddormitorys[j][0]!=''){
								    document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
							    }
						    }						    
						}
					  
					  }
					}else{
					  if(layerId!=''){
					    if(cellId!=''){
					        if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][10]==layerId)&&(unbinddormitorys[j][9]==cellId)) 
						    { 
							if(unbinddormitorys[j][0]!=''){
								document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
							}
						    }
					    }
					    else{
						    if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][10]==layerId)) 
						    { 
							if(unbinddormitorys[j][0]!=''){
								document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
							}
						    }
						}
					  }
					  else{
					    if(cellId!=''){
					        if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][9]==cellId)) 
						    { 
							if(unbinddormitorys[j][0]!=''){
								document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
							}
						    }
					    }
					    else{
						    if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][2]==locationId)) 
						    { 
							if(unbinddormitorys[j][0]!=''){
								document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
							}
						    }
						}
					  }
					}
				}else{
					 if(dormitoryId!=''){
					   if(layId!=''){
					     if(cellId!=''){
					        if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][3]==dormitoryId)&&(unbinddormitorys[j][10]==layerId)&&(unbinddormitorys[j][9]==cellId)) 
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
					    }
					    else{
						    if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][3]==dormitoryId)&&(unbinddormitorys[j][10]==layerId)) 
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
					   }
					   }
					   else{
					    if(cellId!=''){
					        if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][3]==dormitoryId)&&(unbinddormitorys[j][9]==cellId)) 
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
					    }
					    else{
						    if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][3]==dormitoryId)) 
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
					   }
					  }
					 }else{
					   if(layId!=''){
					     if(cellId!=''){
					        if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][10]==layerId)&&(unbinddormitorys[j][9]==cellId))
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
					    }
					    else{
						    if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][10]==layerId))
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
					    }
					   }
					   else{
					    if(cellId!=''){
					        if ((unbinddormitorys[j][1] == areaId)&&(unbinddormitorys[j][9]==cellId))
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
					    }
					    else{
						    if (unbinddormitorys[j][1] == areaId)
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
					    }
					   }
					 }
				}
				
			}else{
				if(locationId!=''){			
					if(dormitoryId!=''){
					    if(layId!=''){
					      if(cellId!=''){
					            if ((unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][3]==dormitoryId)&&(unbinddormitorys[j][10]==layerId)&&(unbinddormitorys[j][9]==cellId)) 
							    { 
								    if(unbinddormitorys[j][0]!=''){
									    document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								    }
							    } 
					        }
					        else{
							    if ((unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][3]==dormitoryId)&&(unbinddormitorys[j][10]==layerId)) 
							    { 
								    if(unbinddormitorys[j][0]!=''){
									    document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								    }
							    } 
							}
					    }
					    else{
					        if(cellId!=''){
					            if ((unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][3]==dormitoryId)&&(unbinddormitorys[j][9]==cellId)) 
							    { 
								    if(unbinddormitorys[j][0]!=''){
									    document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								    }
							    } 
					        }
					        else{
							    if ((unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][3]==dormitoryId)) 
							    { 
								    if(unbinddormitorys[j][0]!=''){
									    document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								    }
							    } 
							}
						}
						}else{
						   if(layId!=''){
						     if(cellId!=''){
						        if ((unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][10]==layerId)&&(unbinddormitorys[j][9]==cellId)) 
							    { 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							    }
						    }
						    else{
							    if ((unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][10]==layerId)) 
							    { 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							    }
							}
						   }
						   else{
						    if(cellId!=''){
						        if ((unbinddormitorys[j][2]==locationId)&&(unbinddormitorys[j][9]==cellId)) 
							    { 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							    }
						    }
						    else{
							    if ((unbinddormitorys[j][2]==locationId)) 
							    { 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							    }
							}
						  }
						}
				}else{
					if(dormitoryId!=''){
					    if(layId!=''){
					       if(cellId!=''){
					        if (unbinddormitorys[j][3]==dormitoryId&&(unbinddormitorys[j][10]==layerId)&&(unbinddormitorys[j][9]==cellId))
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
					       }
					       else{
							if (unbinddormitorys[j][3]==dormitoryId&&(unbinddormitorys[j][10]==layerId))
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
						  }
					    }
					    else{
					       if(cellId!=''){
					        if (unbinddormitorys[j][3]==dormitoryId&&(unbinddormitorys[j][9]==cellId))
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
					       }
					       else{
							if (unbinddormitorys[j][3]==dormitoryId)
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
						  }
						 } 
						}else{
						  if(layId!=''){
						    if(cellId!=''){
						       if ((unbinddormitorys[j][10]==layerId)&&(unbinddormitorys[j][9]==cellId))
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
						   }
						   else{
							if(unbinddormitorys[j][10]==layerId){
								document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
							}	
							}
						  }
						  else{
						   if(cellId!=''){
						       if (unbinddormitorys[j][9]==cellId)
							{ 
								if(unbinddormitorys[j][0]!=''){
									document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
								}
							}
						   }
						   else{
							if(unbinddormitorys[j][0]!=''){
								document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][6],unbinddormitorys[j][0]);
							}	
							}
						  }						
						}
				}
				
			} 
		} 
}
<!-- bindeddormitory list -->
 
 
 		var binddormcount;
		binddormcount = 0;
		binddormitorys = new Array(); 
	<%	
		ArrayList binddormlist=(ArrayList)request.getAttribute("binddormList");
		int m = 0;
		if(binddormlist!=null){
		for(m=0;m<binddormlist.size();m++){
			YangongDormitoryBindInfo dormitoryBindInfo= (YangongDormitoryBindInfo)binddormlist.get(m);
			String dormitoryId = dormitoryBindInfo.getDormitoryId();
			String area = dormitoryBindInfo.getArea();
			String areaStr = dormitoryBindInfo.getAreaStr();
			String location = dormitoryBindInfo.getLocation();
			String locationStr = dormitoryBindInfo.getLocationStr();
			String dormitory = dormitoryBindInfo.getDormitory();
			String dormitoryStr = dormitoryBindInfo.getDormitoryStr();
			String level = dormitoryBindInfo.getLevel();
			String levelStr = dormitoryBindInfo.getLevel()+"层";
			String unit = dormitoryBindInfo.getUnit();
			String unitStr = dormitoryBindInfo.getUnit();
			String sex = dormitoryBindInfo.getGender();
			String sexStr = dormitoryBindInfo.getGenderStr();
			String directionStr = dormitoryBindInfo.getDirectionStr();
			String roomNumber = dormitoryBindInfo.getRoomNumber();
			int emptyNum = dormitoryBindInfo.getEmptyNum();
			String studentType = dormitoryBindInfo.getStuType();
			String collegeId = dormitoryBindInfo.getCollegeId();
	%>
		binddormitorys[<%=m%>]=  new Array("<%=dormitoryId%>","<%=area%>","<%=location%>","<%=dormitory%>","<%=sex%>","<%=emptyNum%>","<%=areaStr%><%=locationStr%><%=dormitoryStr%><%=levelStr%><%=unitStr%><%=roomNumber%>[<%=directionStr%>][<%=sexStr%>][<%=emptyNum%>]","<%=areaStr%><%=locationStr%><%=dormitoryStr%><%=levelStr%><%=unitStr%><%=roomNumber%>[<%=directionStr%>][<%=sexStr%>]","<%=collegeId%>-<%=sex%>-<%=studentType%>","<%=unit%>","<%=level%>");
	<%	
		}	
	%>

	binddormcount=<%=binddormlist.size()%> 
	
 	<%	
		}else{	
	%>
	binddormcount=0
	<%}%>

function selectCollege(collegeId,title){	
	Dorm = 0;
	Place = 0;
	document.all["binddormitory"].length=0;
	var collegeId = collegeId;
	var j; 
	for (j=0;j < binddormcount; j++) { 
		if (binddormitorys[j][8] == collegeId) 
		{ 
			Dorm++;
			Place += parseInt(binddormitorys[j][5],10);
			document.all["binddormitory"].options[document.all["binddormitory"].length]= new Option(binddormitorys[j][6],binddormitorys[j][0]);
		} 
	}
	document.getElementById("showlabel").innerHTML='<br><br>'+title+'<br>已绑定宿舍列表<br> 宿舍数:'+Dorm+'&nbsp;&nbsp;床位数:'+Place; 
}



function classSelCheck(){
	if(document.all("colleges").value==""){
		alert("请选择需要进行绑定操作的学院");
		return false;
	}
	transferOption(document.all.unbinddormitory, document.all.binddormitory,document.all.colleges,false);
	return true;

}

function classDelCheck(){
	if(document.all("colleges").value==""){
		alert("请选择需要进行绑定操作的学院");
		return false;
	}
	returnOption(document.all.binddormitory, document.all.unbinddormitory,document.all.colleges,false);
	return true;

}

function uiOptionReturn_putArrayItem(dormitoryId,collegeId){
	var dormitory_id = dormitoryId;
	var college_id = collegeId
	var i;
	var index = 0;
	var flag =0;
	var temp_num = 0;
	index = unbinddormitorys.length;
	for(i=0;i<binddormitorys.length;i++){	
	 	if((binddormitorys[i][0]==dormitory_id)&&(binddormitorys[i][8]==college_id)){
	 		for(var j=0;j<unbinddormitorys.length;j++){
	 			if(unbinddormitorys[j][0]==dormitory_id){
	 				flag = 1;
	 				break;	 				
	 			}
	 		}
	 		if(flag == 1){//原来的还有
	 			temp_num = parseInt(unbinddormitorys[j][5],10)+parseInt(binddormitorys[i][5],10);
	 			unbinddormitorys[j][5]=temp_num;
	 			unbinddormitorys[j][6]=unbinddormitorys[j][7]+"["+temp_num+"]";
	 			Dorm--;
				Place -= parseInt(binddormitorys[i][5],10);
	 		}else{
	 			unbinddormitorys[index] = new Array(binddormitorys[i][0],binddormitorys[i][1],binddormitorys[i][2],binddormitorys[i][3],binddormitorys[i][4],binddormitorys[i][5],binddormitorys[i][6],binddormitorys[i][7],"null",binddormitorys[i][9],binddormitorys[i][10]);
	 			unbinddormcount++;
	 			Dorm--;
				Place -= parseInt(binddormitorys[i][5],10);
	 		} 		
	 		binddormitorys[i][0]="";
	 		binddormitorys[i][1]="";
	 		binddormitorys[i][2]="";
	 		binddormitorys[i][3]="";
	 		binddormitorys[i][4]="";
	 		binddormitorys[i][5]="";
	 		binddormitorys[i][6]="";
	 		binddormitorys[i][7]="";
	 		binddormitorys[i][8]="";
	 		binddormitorys[i][9]="";
	 		binddormitorys[i][10]="";
	 		break;
	 	} 	
 }
 document.getElementById("showlabel").innerHTML='<br><br>'+document.all("colleges").options[document.all("colleges").selectedIndex].text+'<br>已绑定宿舍列表<br> 宿舍数:'+Dorm+'&nbsp;&nbsp;床位数:'+Place; 


}

//add classId to unbinddormitory's record   
//and add this record to binddormitory
//and delete this record from unbinddormitory
function uiOptionTransfer_putArrayItem(dormitoryId, collegeId){
	var dormitory_id = dormitoryId;
	var college_id = collegeId;
	var i;
	var index = 0;
	index = binddormitorys.length;
	for(i=0;i<unbinddormitorys.length;i++){	
	 	if(unbinddormitorys[i][0]==dormitory_id){
		 		binddormitorys[index] = new Array(unbinddormitorys[i][0],unbinddormitorys[i][1],unbinddormitorys[i][2],unbinddormitorys[i][3],unbinddormitorys[i][4],unbinddormitorys[i][5],unbinddormitorys[i][6],unbinddormitorys[i][7],college_id,unbinddormitorys[i][9],unbinddormitorys[i][10]);
		 		unbinddormitorys[i][0]="";
		 		unbinddormitorys[i][1]="";
		 		unbinddormitorys[i][2]="";
		 		unbinddormitorys[i][3]="";
		 		unbinddormitorys[i][4]="";
		 		unbinddormitorys[i][5]="";
		 		unbinddormitorys[i][6]="";
		 		unbinddormitorys[i][7]="";
		 		unbinddormitorys[i][8]="";
		 		unbinddormitorys[i][9]="";
		 		unbinddormitorys[i][10]="";
		 		binddormcount++;
				Dorm++;
				Place += parseInt(binddormitorys[index][5],10); 		
	 	}	 	
 }
 document.getElementById("showlabel").innerHTML='<br><br>'+document.all("colleges").options[document.all("colleges").selectedIndex].text+'<br>已绑定宿舍列表<br> 宿舍数:'+Dorm+'&nbsp;&nbsp;床位数:'+Place;  
}

function uiOptionTransfer_putArrayItemSpe(dormitoryId,collegeId,collegeCount){
	var dormitory_id = dormitoryId;
	var college_id = collegeId;
	var college_count = collegeCount;//人数
	var temp_place = Place;//床位数	
	var left_place = 0;
	var bind_place = 0;
	var i;
	var index = 0;
	index = binddormitorys.length;
	for(i=0;i<unbinddormitorys.length;i++){	
	 	if(unbinddormitorys[i][0]==dormitory_id){
		 	temp_place += parseInt(unbinddormitorys[i][5],10);
			left_place = temp_place-college_count;
			bind_place = college_count - Place;
	 		binddormitorys[index] = new Array(unbinddormitorys[i][0],unbinddormitorys[i][1],unbinddormitorys[i][2],unbinddormitorys[i][3],unbinddormitorys[i][4],bind_place,unbinddormitorys[i][7]+"["+bind_place+"]",unbinddormitorys[i][7],college_id,unbinddormitorys[i][9],unbinddormitorys[i][10]);
	 		unbinddormitorys[i][5]=left_place;
	 		unbinddormitorys[i][6] = unbinddormitorys[i][7]+"["+left_place+"]";
	 		binddormcount++;
			Dorm++;
			Place += bind_place;
			document.all("unbinddormitory").options[document.all("unbinddormitory").selectedIndex].text = unbinddormitorys[i][6];
		 	document.all["binddormitory"].options[document.all["binddormitory"].length]= new Option(binddormitorys[index][6],binddormitorys[index][0]);
	 	}	 	
 }
 document.getElementById("showlabel").innerHTML='<br><br>'+document.all("colleges").options[document.all("colleges").selectedIndex].text+'<br>已绑定宿舍列表<br> 宿舍数:'+Dorm+'&nbsp;&nbsp;床位数:'+Place;  

}


function setValue(){
	document.all.binddormitorys.value=binddormitorys;
	document.all.unbinddormitorys.value=unbinddormitorys;
	return true;
}


function returnOption(e1,e2,e3,all){
  	var src = e2.options;
  	var tgt = e1.options;
  	var index = e3.selectedIndex;
	var classes = e3.options;
  	var items;
  	var index;
  	var flag=0;
  	for (var i = tgt.length - 1; i >= 0; --i) {
    	if (all || tgt[i].selected) { 
    	
    		for(var k=0;k<unbinddormitorys.length;k++){	
			 	if(unbinddormitorys[k][0]==tgt[i].value){
			 		flag = 1;
			 	}
			}
			if(flag==0){
				clone = uiCommon_cloneSelectOption(tgt[i]);
  				src.add(clone);
			}			
  			uiOptionReturn_putArrayItem(tgt[i].value,classes[index].value);
  			tgt[i] = null;
  		}
  	}
  	changeLocation(document.all.section.value,document.all.distriction.value,document.all.building.value,document.all.layer.value,document.all.cell.value);
}


function transferOption(e1,e2,e3,all){
  	var src = e2.options;
  	var tgt = e1.options;
  	var index = e3.selectedIndex;
	var classes = e3.options;
  	var items;
  	var index=e3.selectedIndex;;
  	var collegeCount =0;
  	var cwcount=0;
  	var collegesex=0;
  	var dormsex=0;
  	for (var i = tgt.length - 1; i >= 0; --i) {
    	if (all || tgt[i].selected) {
			for(var j=0;j<colleges.length;j++){
			 	if(colleges[j][0]==classes[index].value){
			 		collegeCount =  parseInt(colleges[j][4],10);
			 		sex = colleges[j][2];
			 		break;
			 	}
			}
			for(var k=0;k<unbinddormitorys.length;k++){	
			 	if(unbinddormitorys[k][0]==tgt[i].value){
			 		cwcount =   parseInt(unbinddormitorys[k][5],10);
			 		dormsex = unbinddormitorys[k][4];
			 		break;
			 	}
			}
			if(sex!=dormsex){
				alert("性别选择错误！");
  				return;
			}
  			if(collegeCount==Place){
  				alert("当前选择的院系床位已分配完毕！");
  				return;
  			}
  			if(Place+cwcount>collegeCount){
  				uiOptionTransfer_putArrayItemSpe(tgt[i].value,classes[index].value,collegeCount);
  				return;  				
  			}else{
	  			clone = uiCommon_cloneSelectOption(tgt[i]);
	  			src.add(clone);
  				uiOptionTransfer_putArrayItem(tgt[i].value, classes[index].value);
  				tgt[i] = null;  				
  			}	
  		}
  	}
}


function uiCommon_cloneSelectOption(opt) {
  return new Option(opt.text, opt.value,
                    opt.defaultSelected, opt.selected);
}


		 function my_onload(){

	 	if(document.all("sex").value!=""||document.all("studentType").value||document.all("curCollege").value){
		 	document.all.query1.click();
	 	}	
	 	if(document.all("section").value!=""||document.all("distriction").value||document.all("building").value){
		 	document.all.query2.click();
	 	}
	 	 	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	 } 

function DoViewBindResult(){

window.open("collegeDormBindingAction.do?method=dormDistributionStatistic&ispop=1","detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

	 window.onload=my_onload;	
	 
setTimeout('DoInit()',30);
function DoInit(){
    var section = <%=request.getAttribute("section")%>;
    var distriction = <%=request.getAttribute("distriction")%>;
    var building = <%=request.getAttribute("building")%>;
    if(section!=null&&section!=''){
	changeArea(section);
	}
	if(distriction!=null&&distriction!=''){
	changeDistriction(distriction);
	}
}
</script>
