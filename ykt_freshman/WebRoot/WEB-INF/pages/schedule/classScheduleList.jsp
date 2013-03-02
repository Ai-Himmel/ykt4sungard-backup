<%@ page pageEncoding="GBK"%>
<%@ page import="java.util.Map"%>
<%@ page import="java.util.List"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.schedulemanage.domain.Collegeschedulemodel" %>
<%@ page import="org.king.schedulemanage.domain.Classschedulemodel" %>
<%@ include file="../tiles/include.jsp"%>

<SCRIPT language=javascript>

function changeCounty(collegeId){

window.location.href='scheduleAction.do?method=load4ViewCollege&collegeId='+collegeId;

}

</SCRIPT>
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
		border-top-style:solid;
		border-bottom-style:solid;
		border-right-style:none;
		font-size: 12px;
	}
	.innerdiv{
		border-top-style:solid;
		border-top-width: 1px;
		border-top-color: #AA817F;
		height:20px;
		overflow: auto;		
	}
	.innerdiv1{
		height:20px;
		overflow: auto;		
	}
	
	.td_print{
		display: none;
	}
	.toplink{float: right;}
	
	@media print { 
		.td_top {display:none;} 
		.tdborder02{ border-style: none;}
		.toplink{display: none;}
		.td_print{display: block;}
	}	
</style>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<%String hours = "", minites = "";
	if (request.getAttribute("scheduledateList") == null){%>
				<br><font color="red">尚未建立书院，无法查询日程安排，请先建立书院信息</font>
			<%}
			if (request.getAttribute("scheduledateList") != null) {
				java.util.List date = (java.util.List) request
						.getAttribute("scheduledateList");
			String action = "scheduleAction.do?method=load4classList";
			if (request.getAttribute("view") != null)
				action="scheduleAction.do?method=load4ViewCollege";
						%>
		<html:form action="<%=action%>">
		<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><a name="top">书院日程安排查询</a></font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr class="td_print">
				<td>
					书院：<c:out value="${collegeName}"/>
				</td>
			</tr>
			<tr class="td_top">
				<td>
					<table width="100%">
						<tr>
							<td>
								请选择书院：
								<html:select onchange="changeCounty(this.value)" styleClass="select01" property="scheduleCollegeId">
									<html:options collection="colleges" property="collegeId" labelProperty="collegeName" />
								</html:select>
							</td>
							<%String college = request.getAttribute("scheduleCollegeId")
						.toString();%>
							<td align="right">
								<input type="button" class="button_nor" value="打印" onclick="window.print();"/>
							</td>
						</tr>
						<tr>
							<td align="right" colspan="2">
								<%for (int m = 0; m < date.size(); m++) {%>
						[ <a href="#<%=((Dictionary) date.get(m)).getDictCaption()%>"><%=((Dictionary) date.get(m)).getDictCaption()%></a> ]
								<%}%>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td height="40" align="left" valign="top" class="medium">
					
						
							<%
							Map collegeSchedulesMap = (Map)request.getAttribute("collegeSchedule");
							Map classSchedulesMap = (Map)request.getAttribute("classSchedules");
							for (int m = 0; m < date.size(); m++) {
								List collegeScheduleList = (List)collegeSchedulesMap.get(date.get(m));								
							%>
							<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
							<THEAD style="display: table-header-group">
							<tr align="center" valign="middle">
								<td width="25" height="24" valign="middle" class="tableHeader">
									&nbsp;
								</td>
								<td valign="middle" class="tableHeader" colspan=6>
									<a href="#top" class="toplink">TOP</a>
									<a name="<%=((Dictionary) date.get(m)).getDictCaption()%>"><%=((Dictionary) date.get(m)).getDictCaption()%></a>
								</td>
							</tr>
							<tr align="center" valign="middle">
								<td height="24" valign="middle" class="tableHeader">
									&nbsp;
								</td>
								<td valign="middle" width="12%" class="tableHeader">
									书院时间
								</td>
								<td valign="middle" width="12%" class="tableHeader">
									班级时间
								</td>								
								<td valign="middle" width="10%" class="tableHeader">
									班级
								</td>
								<td valign="middle" width="15%" class="tableHeader">
									地点
								</td>
								<td valign="middle" width="30%" class="tableHeader">
									任务
								</td>
								<td valign="middle" class="tableHeader">
									备注
								</td>
							</tr>
							</THEAD>
							<TBODY>
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
									<%}
										int cm = hour*60 + minite;
										boolean flag = false;
										if(collegeScheduleList != null){
											for(int i = 0; i < collegeScheduleList.size();i++){
												Collegeschedulemodel collegeSchedule = (Collegeschedulemodel)collegeScheduleList.get(i);
												String fromTime = collegeSchedule.getFromtime();
												String toTime = collegeSchedule.getTotime();
												int fromHour = Integer.parseInt(fromTime
															.substring(0, 2));
												int fromMinute = Integer.parseInt(fromTime
																	.substring(2));
												int toHour = Integer.parseInt(toTime
																	.substring(0, 2));
												int toMinute = Integer.parseInt(toTime
																	.substring(2));
														
												int tm = toHour * 60 + toMinute;
												int fm = fromHour * 60 + fromMinute;	
												
												
												if (cm == fm) {
													flag = true;
													int rowspan = (tm-fm) / 5;%>
												<td rowspan="<%=rowspan%>" class="content" valign="middle" bgcolor="#FFFFFF">
													<%=fromTime.substring(0,2)%>:<%=fromTime.substring(2)%>--<%=toTime.substring(0,2)%>:<%=toTime.substring(2)%>
												</td>
												<%
													List classScheduleList = (List)classSchedulesMap.get(collegeSchedule);
													if(classScheduleList == null){
												%>
												<td rowspan="<%=rowspan%>" class="content" valign="middle" bgcolor="#FFFFFF">
													&nbsp;
												</td>
												<td rowspan="<%=rowspan%>" class="content" valign="middle" bgcolor="#FFFFFF">
													全体
												</td>
												<td rowspan="<%=rowspan%>" class="content" valign="middle" bgcolor="#FFFFFF">
													<%=collegeSchedule.getPositon()%>
												</td>
												<td rowspan="<%=rowspan%>" class="content" valign="middle" bgcolor="#FFFFFF">
													<%=collegeSchedule.getMission()%>
												</td>
												<td rowspan="<%=rowspan%>" class="content" valign="middle" bgcolor="#FFFFFF">
													<%=collegeSchedule.getRemark()%>&nbsp;
												</td>
												<%		
													break;
													}else{
												%>		
														<td rowspan="<%=rowspan%>" class="content" valign="middle" bgcolor="#FFFFFF">
															<%for(int j =0;j < classScheduleList.size();j++){
																Classschedulemodel classschedulemodel = (Classschedulemodel)classScheduleList.get(j);
																String className;
																if(j == 0)
																	className = "innerdiv1";
																else
																	className = "innerdiv";
															%>
															<div class="<%=className%>"><%=classschedulemodel.getFromtime().substring(0,2)%>:<%=classschedulemodel.getFromtime().substring(2)%>--<%=classschedulemodel.getTitime().substring(0,2)%>:<%=classschedulemodel.getTitime().substring(2)%></div>
															<%}%>															
														</td>
														<td rowspan="<%=rowspan%>" class="content" valign="middle" bgcolor="#FFFFFF">
															<%for(int j =0;j < classScheduleList.size();j++){
																Classschedulemodel classschedulemodel = (Classschedulemodel)classScheduleList.get(j);
																String className;
																if(j == 0)
																	className = "innerdiv1";
																else
																	className = "innerdiv";
															%>
															<div class="<%=className%>"><%=classschedulemodel.getClassId().equals("all")?"各班":classschedulemodel.getClassId()%></div>
															<%}%>
														</td>
														<td rowspan="<%=rowspan%>" class="content" valign="middle" bgcolor="#FFFFFF">
															<%for(int j =0;j < classScheduleList.size();j++){
																Classschedulemodel classschedulemodel = (Classschedulemodel)classScheduleList.get(j);
																String className;
																if(j == 0)
																	className = "innerdiv1";
																else
																	className = "innerdiv";
															%>
															<div class="<%=className%>"><%=classschedulemodel.getPositon()%></div>
															<%}%>
														</td>
														<td rowspan="<%=rowspan%>" class="content" valign="middle" bgcolor="#FFFFFF">
															<%for(int j =0;j < classScheduleList.size();j++){
																Classschedulemodel classschedulemodel = (Classschedulemodel)classScheduleList.get(j);
																String className;
																if(j == 0)
																	className = "innerdiv1";
																else
																	className = "innerdiv";
															%>
															<div class="<%=className%>"><%=classschedulemodel.getMission()%></div>
															<%}%>
														</td>
														<td rowspan="<%=rowspan%>" class="content" valign="middle" bgcolor="#FFFFFF">
															<%=collegeSchedule.getRemark()%>&nbsp;
														</td>
												<%	
													break;
													}		
												}
												if (cm > fm && cm < tm ){
													flag = true;
													break;
												}
										
											}
										}
										if(!flag){
											for (int s = 0; s <= 5; s++) {%>
												<td id='<%=hours+minites%>.<%=((Dictionary)date.get(m)).getId().getDictValue()%>.<%=s%>' class="<%=tdCss%>" valign="middle" bgcolor="#FFFFFF">
													&nbsp;
												</td>
									<%		}
										}
									%>
									
								</tr>
								<%}
					}%>
							</logic:present>
							</tbody>
					</table>
							<%}%>
						
				</td>
			</tr>
		</table>
	</html:form>
	<%}%>
</body>
