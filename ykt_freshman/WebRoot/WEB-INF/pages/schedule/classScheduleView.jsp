<%@ page pageEncoding="GBK"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.schedulemanage.domain.Collegeschedulemodel"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.List"%>
<%@ page import="org.king.classmanage.domain.Classmodel"%>
<%@ page import="org.king.schedulemanage.domain.Classschedulemodel" %>
<%@ include file="../tiles/include.jsp"%>

<style>
	.td-00-30{
		font-size:2px;
		border-bottom-style:none;
		border-right-style:none;
	}
	.td-common{
		font-size:2px;
		border-top-style:none;
		border-bottom-style:none;
		border-right-style:none;
	}
	.content{		
		border-right-style:none;
		font-size: 12px;	
	}
	.td_print{
		display: none;
	}
	
	@media print { 
		.td_top {display:none;} 
		.tdborder02{ border-style: none;}
		.toplink{display: none;}
		.td_print{display: block;}
	}	
</style>

<script>
	function check(){
		if(document.getElementById("classSchedulemanage.collegeId").value == '' || document.getElementById("classSchedulemanage.classId").value == ''){
			alert("请选择书院及班级");
			return false;
		}
		
		return true;
	}
	
	function doAdd(){
		if(check())
			window.location.href="scheduleAction.do?method=addSingleClassSchedule&setup=true&classId=" + document.getElementById("classSchedulemanage.classId").value + "&collegeId="+document.getElementById("classSchedulemanage.collegeId").value;
	}
</script>
<% String msg=(String)request.getAttribute("msg");
if(msg!=null)
{
%>
<script language="javascript">
	alert('<%=msg%>');
</script>
<%}%>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<%String hours = "", minites = "";
	if (request.getAttribute("scheduledateList") == null){%>
				<br><font color="red">尚未建立书院，无法查询日程安排，请先建立书院信息</font>
			<%}else if(request.getAttribute("collegeList") == null){%>
				<br><font color="red">您无权查询日程安排，可能是因为您没有管辖任何书院或班级</font>			
			<%}else{
			if (request.getAttribute("scheduledateList") != null) {
				java.util.List date = (java.util.List) request
						.getAttribute("scheduledateList");%>
	
		<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">班级日程安排<c:if test="${setup == 'true'}">设置</c:if><c:if test="${setup != 'true'}">查询</c:if>
					</font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr valign="middle" class="td_print">
				<td>
					书院：<c:out value="${collegeName}"/>&nbsp;&nbsp;&nbsp;&nbsp;班级：<c:out value="${className}"/>
				</td>
			</tr>
			<tr valign="middle" class="td_top">
				<td>
					<table width="100%"><tr><td>
					<html:form action="scheduleAction.do?method=load4ViewClass" onsubmit="return check();">
					书院：
					<input type="hidden" name="setup" value="<c:out value="${setup}"/>"/>
				
					<html:select styleClass="select01" onchange="changeCollge(this.value)" property="classSchedulemanage.collegeId">
						<html:option value="">---------------</html:option>
						<html:options collection="collegeList" labelProperty="collegeName" property="collegeId" />
					</html:select>
				
					班级：
				
					<html:select styleClass="select01" property="classSchedulemanage.classId">
						<html:option value="">---------------</html:option>
					</html:select><INPUT type="hidden" name="myclass" value="<c:out value="${classId}"/>">
					
					<input name="Submit" type="submit" class="button_nor" value="查询">
					</html:form>
					</td>
					<td align="right">
						<c:if test="${setup == 'true'}">
							<input type="button" name="search" value="添加" class="button_nor" onclick="javascript: doAdd();">
						</c:if>
						<c:if test="${setup != 'true'}">
							<input type="button" class="button_nor" value="打印" onclick="window.print();"/>
						</c:if>
					</td>
					</tr>
					</table>
				</td>

			</tr>
			<tr>
				<td height="40" align="left" valign="top" class="medium">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
						
							<thead style="display:table-header-group">
							<tr align="center" valign="middle">
								<td width="4%" height="24" valign="middle" class="tableHeader">
									&nbsp;
								</td>
								<%
								List classScheduleList=(List)request.getAttribute("classSchedules");
								List collegeScheduleList=(List)request.getAttribute("collegeSchedule");
								int width = 96 / date.size();
								for (int m = 0; m < date.size(); m++) {%>
								<td valign="middle" class="tableHeader" width="<%=width%>%">
									<%=((Dictionary) date.get(m)).getDictCaption()%>
								</td>
								<%}
									
								
								%>
							</tr>
							</thead>
							<tbody>
							<logic:present name="scheduledateList" scope="request">
								<%for (int hour = 6; hour < 23; hour++) {
					if (hour < 10) {
						hours = "0" + String.valueOf(hour);
					} else {
						hours = String.valueOf(hour);
					}
					for (int minite = 0; minite < 60; minite = minite + 5) {
						if (minite < 10) {
							minites = "0" + String.valueOf(minite);
						} else {
							minites = String.valueOf(minite);
						}%>
								<tr id='<%=hours+minites%>' align="center" valign="middle">
									<%String tdCss = "td-common";
						if (minite == 0 || minite == 30) {
							tdCss = "td-00-30";

							%>
									<td rowspan="6" align="center" valign="top" bgcolor="#FFFFFF" width=4%>
										<%=hours + ":" + minites%>
									</td>
									<%}%>
									<%for (int m = 0; m < date.size(); m++) {
										boolean flag =false;
										if(classScheduleList != null){
											for(int i = 0; i < classScheduleList.size();i++){
												Classschedulemodel classschedule = (Classschedulemodel)((java.util.Map)classScheduleList.get(i)).get("cSchedulemodel");;
												String fromtime = classschedule.getFromtime();
												String totime = classschedule.getTitime();
												int fromHour = Integer.parseInt(fromtime
															.substring(0, 2));
												int fromMinute = Integer.parseInt(fromtime
															.substring(2));
												int toHour = Integer.parseInt(totime
															.substring(0, 2));
												int toMinute = Integer.parseInt(totime
															.substring(2));
													
												int tm = toHour * 60 + toMinute;
												int fm = fromHour * 60 + fromMinute;	
												int cm = hour*60 + minite;
												if(classschedule.getFromdate().equals(((Dictionary)date.get(m)).getId().getDictValue())){
													String classId = classschedule.getClassId();
													String scheduleId = classschedule.getScheduleId();
													String remark = classschedule.getRemark();
													if(remark == null){
				    									Collegeschedulemodel collegeschedulemodel = classschedule.getCollegeSchedule();
													  	if(collegeschedulemodel !=null){
													   		remark = collegeschedulemodel.getRemark();
													   	}  
													   	if(remark == null)
													   		remark="";
													}
													if (cm == fm) {
														int rowspan = (tm-fm) / 5;
										%>
												
												<td rowspan="<%=rowspan%>" class="content" valign="middle">
													 <%
							    						if(request.getAttribute("setup") != null && request.getAttribute("setup").equals("true") && !classId.equalsIgnoreCase("all") && classschedule.getCollegeSchedule() == null){
							    					%>
								    					<a href="scheduleAction.do?method=editSingleClassSchedule&setup=true&scheduleId=<%=scheduleId%>">  	
														<%=fromtime.substring(0,2)+":"+fromtime.substring(2)+"--"+totime.substring(0,2)+":"+totime.substring(2)+"<br>"+classschedule.getPositon()+"<br>"+classschedule.getMission()+"<br>"+remark%>
														</a>
													<%}else{%>
														<%=fromtime.substring(0,2)+":"+fromtime.substring(2)+"--"+totime.substring(0,2)+":"+totime.substring(2)+"<br>"+classschedule.getPositon()+"<br>"+classschedule.getMission()+"<br>"+remark%>
													<%}%>
												</td>
										<%
													flag = true;
													break;
													}
													
													if (cm > fm && cm < tm ){
														flag = true;
														break;
													}
												}
											}
										}
										if(!flag){
											if(collegeScheduleList != null){
												for(int i = 0; i < collegeScheduleList.size();i++){
													Collegeschedulemodel collegeSchedule = (Collegeschedulemodel)collegeScheduleList.get(i);
													String fromtime = collegeSchedule.getFromtime();
													String totime = collegeSchedule.getTotime();
													int fromHour = Integer.parseInt(fromtime
																.substring(0, 2));
													int fromMinute = Integer.parseInt(fromtime
																.substring(2));
													int toHour = Integer.parseInt(totime
																.substring(0, 2));
													int toMinute = Integer.parseInt(totime
																.substring(2));
													
													int tm = toHour * 60 + toMinute;
													int fm = fromHour * 60 + fromMinute;	
													int cm = hour*60 + minite;
													if(collegeSchedule.getFromdate().equals(((Dictionary)date.get(m)).getId().getDictValue())){
														String remark = collegeSchedule.getRemark();
														
														if (cm == fm) {
															int rowspan = (tm-fm) / 5;
										%>
												<td rowspan="<%=rowspan%>" class="content" valign="middle">
													<%=fromtime.substring(0,2)+":"+fromtime.substring(2)+"--"+totime.substring(0,2)+":"+totime.substring(2)+"<br>"+collegeSchedule.getPositon()+"<br>"+collegeSchedule.getMission()+"<br>"+remark%>
												</td>
										<%
													flag = true;
													break;
													}
													
													if (cm > fm && cm < tm ){
														flag = true;
														break;
													}
												}
											}
										}
										
										if(!flag){
										
									%>
									<td id='<%=hours+minites%>.<%=((Dictionary)date.get(m)).getId().getDictValue()%>' valign="middle" class="<%=tdCss%>" bgcolor="#FFFFFF">
										&nbsp;
									</td>
									<%
									
										}
									}
								}%>
								</tr>
								<%}
				}%>
							</logic:present>
						</tbody>
					</table>
				</td>
			</tr>
		</table>

	<%}}%>
</body>

<script language="JavaScript">
<!-- class list -->
	var classescount;
	classescount = 0;
	classes = new Array(); 
	<%	
		ArrayList classeslist=(ArrayList)request.getAttribute("classList");		
		int i =0;
		if(classeslist != null){
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
		}
	%>
	classescount=<%=classeslist != null?classeslist.size():0%>
	

	function changeCollge(college){
	 	document.all("classSchedulemanage.classId").length=0;
	 	var collegeId=college; 
		var j; 
		document.all("classSchedulemanage.classId").options[document.all("classSchedulemanage.classId").length]=new Option("---------------","");
		for (j=0; j<classescount; j++) 
		{ 
			if (classes[j][2] == collegeId) 
			{ 
				document.all("classSchedulemanage.classId").options[document.all("classSchedulemanage.classId").length]= new Option(classes[j][1],classes[j][0]);
			} 
		}		
	 }	 
	 
	 function my_onload(){

	 	if(document.all("classSchedulemanage.collegeId").value!=""){
		 	document.all("classSchedulemanage.classId").length=0;
			var j; 
			document.all("classSchedulemanage.classId").options[document.all("classSchedulemanage.classId").length]=new Option("---------------","");
			for (j=0; j<classescount; j++) 
			{ 
				if (classes[j][2] == document.all("classSchedulemanage.collegeId").value) 
				{ 
					document.all("classSchedulemanage.classId").options[document.all("classSchedulemanage.classId").length]= new Option(classes[j][1],classes[j][0]);
					if(classes[j][0]==document.all("myclass").value){
						document.all("classSchedulemanage.classId").options[document.all("classSchedulemanage.classId").length-1].selected=true;
					}
				} 
			} 
	 	}
	 }
	 
	 window.onload=my_onload;	 

</script>