<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.List"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.Map"%>
<%@ page import="org.king.schedulemanage.domain.Collegeschedulemodel"%>
<%@ page import="org.king.classmanage.domain.Collegemodel"%>
<%@ page import="java.util.Iterator"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
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
		border-top-style:solid;
		border-bottom-style:solid;
		border-right-style:none;
		font-size: 12px;	
	}
	.toplink{
		float: right;
	}
	
	@media print { 
		.td_top {display:none;} 
		.tdborder02{ border-style: none;}
		.toplink{display: none;}
	}	
</style>

<c:if test="${empty collegeList}">
	<br>
	<font color="red">尚未建立书院，无法查询日程安排，请先建立书院信息</font>
</c:if>
<c:if test="${not empty collegeList}">
	<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
		<form>
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium"><a name="top">整体日程安排查询</a></font></strong>
			</td>
		</tr>
		<tr>
			<td align="right" height="30" class="td_top">
				<logic:present name="scheduledateList" scope="request">
					<logic:iterate name="scheduledateList" id="scheduledate">
						[ <a href='#<bean:write name="scheduledate" property="dictCaption" />'><bean:write name="scheduledate" property="dictCaption" /></a> ]
					</logic:iterate>
				</logic:present>
				<input type="button" class="button_nor" value="打印" onclick="window.print();" />
			</td>
		</tr>
		<tr>
			<td height="40" align="left" valign="top" class="medium">


				<%
						List collegeList = (List) request.getAttribute("collegeList");
						Map schedulesMap = (Map) request.getAttribute("schedulesMap");
						Iterator it = ((List) request.getAttribute("scheduledateList")).iterator();
						
						while (it.hasNext()) {
							Dictionary date = (Dictionary) it.next();
							List schdulesList = (List) schedulesMap.get(date);
						%>
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
					<COLGROUP>
						<col />
						<logic:iterate name="collegeList" id="college" indexId="index">
							<c:if test="${index%2 == 0}">
								<col />
							</c:if>
							<c:if test="${index%2 != 0}">
								<col bgcolor="#F6F4F5" />
							</c:if>
						</logic:iterate>
					</COLGROUP>
					<thead style="display:table-header-group">
						<tr align="center" valign="middle">
							<td width="4%" height="24" valign="middle" class="tableHeader">
								&nbsp;
							</td>
							<td colspan="<c:out value="${collegeCount}"/>" valign="middle" class="tableHeader">
								<a href="#top" class="toplink">TOP</a> <a name="<%=date.getDictCaption()%>"><%=date.getDictCaption()%></a>
							</td>
						</tr>
						<tr align="center" valign="middle">
							<td align="center" valign="middle" bgcolor="#FFFFFF">
								&nbsp;
							</td>
							<fmt:formatNumber value="${96 / collegeCount}" maxFractionDigits="0" var="tdWidth" />
							<logic:present name="collegeList" scope="request">
								<logic:iterate name="collegeList" id="college">
									<td align="center" valign="middle" bgcolor="#F6F4F5" width="<c:out value="${tdWidth}"/>%">
										<bean:write name="college" property="collegeName" />
									</td>
								</logic:iterate>
							</logic:present>
						</tr>
					</thead>
					<tbody>
						<%
							String hours = "", minites = "";
							for (int hour = 6; hour < 23; hour++) {
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
									}
							%>
						<tr align="center" valign="middle">
							<%
									String tdCss = "td-common";
									if (minite == 0 || minite == 30) {
										tdCss = "td-00-30";
									%>
							<td rowspan="6" align="center" valign="top" bgcolor="#FFFFFF">
								<%=hours + ":" + minites%>
							</td>
							<%
									}
									
									for (int i = 0; i < collegeList.size(); i++) {
										boolean flag =false;
										Collegemodel college = (Collegemodel) collegeList.get(i);
										for (int j = 0; j < schdulesList.size(); j++) {
											Collegeschedulemodel collegeschedule = (Collegeschedulemodel) schdulesList.get(j);
											if (collegeschedule.getCollegeId().equals(college.getCollegeId()) || collegeschedule.getCollegeId().equalsIgnoreCase("ALL")) {
												String fromtime = collegeschedule
														.getFromtime();
												String totime = collegeschedule.getTotime();
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
												if (cm == fm) {
													int rowspan = (tm-fm) / 5;
													if(collegeschedule.getCollegeId().equalsIgnoreCase("ALL")){
														if(i == 0){
															int colspan = collegeList.size();
%>
							<td rowspan="<%=rowspan%>" colspan="<%=colspan%>" class="content" valign="middle">
								<%=fromtime.substring(0,2)+":"+fromtime.substring(2)+"--"+totime.substring(0,2)+":"+totime.substring(2)+"<br>"+collegeschedule.getPositon()+"<br>"+collegeschedule.getObject()+"<br>"+collegeschedule.getMission()+"<br>"+collegeschedule.getRemark()%>
							</td>
							<%																																
														}
														flag = true;
														break;													
													}else{
													
									%>
							<td rowspan="<%=rowspan%>" class="content" valign="middle">
								<%=fromtime.substring(0,2)+":"+fromtime.substring(2)+"--"+totime.substring(0,2)+":"+totime.substring(2)+"<br>"+collegeschedule.getPositon()+"<br>"+collegeschedule.getObject()+"<br>"+collegeschedule.getMission()+"<br>"+collegeschedule.getRemark()%>
							</td>


							<%				flag = true;
													break;
													}
												} else if (cm > fm && cm < tm ){
													flag = true;
													break;
												}%>


							<%		}
	
										}
										if(!flag){
									%>

							<td class="<%=tdCss%>" valign="middle">
								&nbsp;
							</td>

							<%											
										}	
									}
						

					%>
						</tr>
						<%}}%>

					</tbody>
				</table>
				<%%>

				<%

			}%>


			</td>
		</tr>
	</table>
</c:if>
