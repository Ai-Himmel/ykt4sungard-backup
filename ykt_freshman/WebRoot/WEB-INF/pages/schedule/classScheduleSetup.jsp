<%@ page pageEncoding="GBK"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.schedulemanage.domain.Collegeschedulemodel" %>
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
</style>
<script>
function doAdd(){
	window.location.href="scheduleAction.do?method=addClassSchedule&collegeId="+document.getElementById("scheduleCollegeId").value+"&dateId=" + document.getElementById("dateId").value;
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
				<br><font color="red">��δ������Ժ���޷������ճ̰��ţ����Ƚ�����Ժ��Ϣ</font>
			<%}
			if (request.getAttribute("scheduledateList") != null) {
				java.util.List date = (java.util.List) request
						.getAttribute("scheduledateList");
				%>
	
		<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><a name="top">��Ժ�ճ̰�������</a></font></strong>
				</td>
			</tr>
			<tr>
				<td>
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
		
					<span class="red1">��λѧ�����鳤��ע�⣺���ڸ���ѧԺ�ġ������ճ̰��š����ڡ���Ժ�ճ̰������á��У�����ָ��Ϊ������Ժ���а༶�����������Ժ�ճ��б��С��༶����һ�л��ɡ�ȫ�塱��Ϊ�����ࡱ���������������ָ�����ڡ��༶�ճ̰��Ų�ѯ���У�����Ա��ѧ�����޷������������ճ̰��š��а��ŵĻ��</span>
		
				</td>
			</tr>
			<tr>
				<td>
					&nbsp;
				</td>
			</tr>
			<tr>
				<td>
					<table width="100%">
						<html:form action="scheduleAction.do?method=load4classList">
						<tr>
							<td>
								��ѡ����Ժ��
								<html:select styleClass="select01" property="scheduleCollegeId">
									<html:options collection="colleges" property="collegeId" labelProperty="collegeName" />
								</html:select>
								��ѡ�����ڣ�
								<select id="dateId" name="dateId">
									<c:forEach items="${scheduledateList}" var="date">
										<option value="<c:out value="${date.id.dictValue}"/>"
											<c:if test = "${date.id.dictValue == dateId}">
												selected
												<c:set var="scheduledate" value="${date}"/>
											</c:if>
										>
											<c:out value="${date.dictCaption}" />
										</option>
									</c:forEach>
								</select>
								<input name="Submit" type="submit" class="button_nor" value="��ѯ">
							</td>
							<td align="right">
								
							</td>
						</tr>
							</html:form>
					</table>
				</td>
			</tr>
			<tr>
				<td height="40" align="left" valign="top" class="medium">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
						<tbody>							
							<tr align="center" valign="middle">
								<td width="25" height="24" valign="middle" class="tableHeader">
									&nbsp;
								</td>
								<td valign="middle" class="tableHeader" colspan=6>
									<c:out value="${scheduledate.dictCaption}" />
								</td>
							</tr>
							<tr align="center" valign="middle">
								<td width="25" height="24" valign="middle" class="tableHeader">
									&nbsp;
								</td>
								<td valign="middle" width="80" class="tableHeader">
									��Ժʱ��
								</td>
								<td valign="middle" width="80" class="tableHeader">
									�༶ʱ��
								</td>
								<td valign="middle" width="80" class="tableHeader">
									�༶
								</td>
								<td valign="middle" width="150" class="tableHeader">
									�ص�
								</td>
								<td valign="middle"  class="tableHeader">
									����
								</td>
								<td valign="middle" class="tableHeader">
									��ע
								</td>
							</tr>
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
									<%for (int s = 0; s <= 5; s++) {%>
									<td id='<%=hours+minites%>.<c:out value="${scheduledate.id.dictValue}" />.<%=s%>' class="<%=tdCss%>" valign="middle" bgcolor="#FFFFFF">
										&nbsp;
									</td>
									<%}%>
								</tr>
								<%}
					}%>
							</logic:present>
						</tbody>
					</table>
				</td>
			</tr>
		</table>

	<%}%>
</body>
<!--��ʼ���༶�ճ� -->
<Script language="Javascript">
	<%
		java.util.List scheduleList=(java.util.List)request.getAttribute("classSchedules");
		String classId,fromTime,toTime,fromDate,tdId,mission,scheduleId,position,remark,method;	
			int rows=0;
			String[] tdNext;
			
		if(scheduleList != null){	
		for(int i=0;i<scheduleList.size();i++){
				//��ð༶�ճ̰�����Ϣ�ֶ�
				
				org.king.schedulemanage.domain.Classschedulemodel cS=(org.king.schedulemanage.domain.Classschedulemodel)((java.util.Map)scheduleList.get(i)).get("cSchedulemodel");
				
				Collegeschedulemodel collegeschedule = cS.getCollegeSchedule();
				
				String classNo=((java.util.Map)scheduleList.get(i)).get("classNo").toString();
				scheduleId=cS.getScheduleId();
				classId=cS.getClassId();
				fromTime=cS.getFromtime();								
			    toTime=cS.getTitime();
			    fromDate=cS.getFromdate();
			    mission=cS.getMission();
			    mission=mission==null?"":mission.trim();
			    position=cS.getPositon();
			    remark=cS.getRemark();
			    tdId=collegeschedule.getFromtime();
			    			    
			   	method = "editSplitCollegeSchedule";	
			    remark = collegeschedule.getRemark();
			   
			    int toTimehour=Integer.parseInt(collegeschedule.getTotime().substring(0,2));
			    int fromTimehour=Integer.parseInt(collegeschedule.getFromtime().substring(0,2));
			    int toTimeminite=Integer.parseInt(collegeschedule.getTotime().substring(2));
			    int fromTimeminite=Integer.parseInt(collegeschedule.getFromtime().substring(2));
//������ظ�ʽ			    			    			    
					    if((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite)>=5){
						    rows=((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite))/5;
						    }
						  %>
						  	  			
						  	if(document.getElementById("<%=tdId%>.<%=fromDate%>.0").innerText.length != 2){
						  		document.getElementById("<%=tdId%>.<%=fromDate%>.1").innerHTML= document.getElementById("<%=tdId%>.<%=fromDate%>.1").innerHTML + '<div class="innerdiv"><%=fromTime.substring(0,2)%>:<%=fromTime.substring(2)%>--<%=toTime.substring(0,2)%>:<%=toTime.substring(2)%></div>';
						  		document.getElementById("<%=tdId%>.<%=fromDate%>.3").innerHTML= document.getElementById("<%=tdId%>.<%=fromDate%>.3").innerHTML +'<div class="innerdiv"><%=position%></div>';
								document.getElementById("<%=tdId%>.<%=fromDate%>.2").innerHTML= document.getElementById("<%=tdId%>.<%=fromDate%>.2").innerHTML + '<div class="innerdiv"><%=classNo%></div>';
								document.getElementById("<%=tdId%>.<%=fromDate%>.4").innerHTML= document.getElementById("<%=tdId%>.<%=fromDate%>.4").innerHTML + '<div class="innerdiv"><a href="scheduleAction.do?method=<%=method%>&scheduleId=<%=scheduleId%>&collegeId=<%=request.getAttribute("scheduleCollegeId").toString()%>"><%=mission%></a></div>';
						  	}else{
						  	<%
						  	String curmission="";
						  	if(collegeschedule.getMission()!=null)
						  	  curmission=collegeschedule.getMission().trim();
						  	%>
						  	document.getElementById("<%=tdId%>.<%=fromDate%>.0").innerHTML='<a title="����<%=collegeschedule.getObject()%>\n�ص㣺<%=collegeschedule.getPositon()%>\n����<%=curmission%>\n��ע��<%=collegeschedule.getRemark()%>" href="scheduleAction.do?method=splitCollegeSchedule&scheduleId=<%=collegeschedule.getScheduleId()%>&collegeId=<%=request.getAttribute("scheduleCollegeId").toString()%>&ft=<%=fromTime%>&tt=<%=toTime%>"><%=collegeschedule.getFromtime().substring(0,2)%>:<%=collegeschedule.getFromtime().substring(2)%>--<%=collegeschedule.getTotime().substring(0,2)%>:<%=collegeschedule.getTotime().substring(2)%></a>'
						  	document.getElementById("<%=tdId%>.<%=fromDate%>.1").innerHTML='<div class="innerdiv1"><%=fromTime.substring(0,2)%>:<%=fromTime.substring(2)%>--<%=toTime.substring(0,2)%>:<%=toTime.substring(2)%></div>';		      
							document.getElementById("<%=tdId%>.<%=fromDate%>.3").innerHTML='<div class="innerdiv1"><%=position%></div>';
							document.getElementById("<%=tdId%>.<%=fromDate%>.2").innerHTML='<div class="innerdiv1"><%=classNo%></div>';
							document.getElementById("<%=tdId%>.<%=fromDate%>.4").innerHTML='<div class="innerdiv1"><a href="scheduleAction.do?method=<%=method%>&scheduleId=<%=scheduleId%>&collegeId=<%=request.getAttribute("scheduleCollegeId").toString()%>"><%=mission%></a></div>';
							document.getElementById("<%=tdId%>.<%=fromDate%>.5").innerHTML='<%=remark%>&nbsp;';
							document.getElementById("<%=tdId%>.<%=fromDate%>.0").className="content";
							document.getElementById("<%=tdId%>.<%=fromDate%>.1").className="content";
							document.getElementById("<%=tdId%>.<%=fromDate%>.2").className="content";
							document.getElementById("<%=tdId%>.<%=fromDate%>.3").className="content";
							document.getElementById("<%=tdId%>.<%=fromDate%>.4").className="content";
							document.getElementById("<%=tdId%>.<%=fromDate%>.5").className="content";
						<%	for(int n=0;n<=5;n++){%>
							document.getElementById("<%=tdId%>.<%=fromDate%>.<%=n%>").rowSpan='<%=rows%>';							
					      <%}
//ɾ����Ԫ��
					    if(rows>1){
						    tdNext=new String[rows];
						    tdNext[0]=collegeschedule.getFromtime();
								    for(int j=1;j<rows;j++){
								   			String changeV=String.valueOf(Integer.parseInt(tdNext[j-1])+5);
								   				if(changeV.length()<4){
										    		changeV="0"+changeV;
										    	}
										    if(Integer.parseInt(changeV.substring(2))==60){		    	
										       int s1= Integer.parseInt(tdNext[j-1].substring(0,2))+1;
										       changeV=String.valueOf(s1)+"00";
										       if(changeV.length()<4){
										    		changeV="0"+changeV;
										    	}
										    }   
										    	
								    	tdNext[j]=changeV;
							
										for(int icr=0;icr<=5;icr++){%>
											if(document.getElementById('<%=tdNext[j]%>.<%=fromDate%>.<%=icr%>')!=null){
												document.getElementById('<%=tdNext[j]%>.<%=fromDate%>.<%=icr%>').removeNode(); 
											}
																			   	
										<%
								    	}
								    }
					      }%>
					      }
			<%					      
		}
		}%>			
</script>

<script language="javascript">
<%		
		java.util.List cscheduleList=(java.util.List)request.getAttribute("collegeSchedule");
			int crows=0;
			String[] ctdNext;
		if(cscheduleList != null){
		for(int i=0;i<cscheduleList.size();i++){
				//�����Ժ�ճ̰�����Ϣ�ֶ�
				org.king.schedulemanage.domain.Collegeschedulemodel ccS=(org.king.schedulemanage.domain.Collegeschedulemodel)cscheduleList.get(i);
				scheduleId=ccS.getScheduleId();
				fromTime=ccS.getFromtime();								
			    toTime=ccS.getTotime();
			    fromDate=ccS.getFromdate();
			    mission=ccS.getMission();
			    mission=mission==null?"":mission.trim();
			    position=ccS.getPositon();
			    remark=ccS.getRemark();
			    tdId=fromTime;
			    int toTimehour=Integer.parseInt(toTime.substring(0,2));
			    int fromTimehour=Integer.parseInt(fromTime.substring(0,2));
			    int toTimeminite=Integer.parseInt(toTime.substring(2));
			    int fromTimeminite=Integer.parseInt(fromTime.substring(2));
//������ظ�ʽ			    			    			    
					    if((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite)>=5){
						    rows=((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite))/5;
						    }
						  %>
						  	
						  	document.getElementById("<%=tdId%>.<%=fromDate%>.0").innerHTML='<a href="scheduleAction.do?method=splitCollegeSchedule&scheduleId=<%=scheduleId%>&collegeId=<%=request.getAttribute("scheduleCollegeId").toString()%>&ft=<%=fromTime%>&tt=<%=toTime%>"><%=fromTime.substring(0,2)%>:<%=fromTime.substring(2)%>--<%=toTime.substring(0,2)%>:<%=toTime.substring(2)%></a>'
						         					      
							document.getElementById("<%=tdId%>.<%=fromDate%>.3").innerHTML='<%=position%>';							
							document.getElementById("<%=tdId%>.<%=fromDate%>.2").innerHTML='ȫ��';
							document.getElementById("<%=tdId%>.<%=fromDate%>.4").innerHTML='<%=mission%>';
							document.getElementById("<%=tdId%>.<%=fromDate%>.5").innerHTML='<%=remark%>&nbsp;';
							document.getElementById("<%=tdId%>.<%=fromDate%>.0").className="content";
							document.getElementById("<%=tdId%>.<%=fromDate%>.1").className="content";
							document.getElementById("<%=tdId%>.<%=fromDate%>.3").className="content";
							document.getElementById("<%=tdId%>.<%=fromDate%>.2").className="content";
							document.getElementById("<%=tdId%>.<%=fromDate%>.4").className="content";
							document.getElementById("<%=tdId%>.<%=fromDate%>.5").className="content";
						<%	for(int n=0;n<=5;n++){%>
							document.getElementById("<%=tdId%>.<%=fromDate%>.<%=n%>").rowSpan='<%=rows%>';							
					      <%}
//ɾ����Ԫ��
					    if(rows>1){
						    tdNext=new String[rows];
						    tdNext[0]=fromTime;
								    for(int j=1;j<rows;j++){
								   			String changeV=String.valueOf(Integer.parseInt(tdNext[j-1])+5);
								   				if(changeV.length()<4){
										    		changeV="0"+changeV;
										    	}
										    if(Integer.parseInt(changeV.substring(2))==60){		    	
										       int s1= Integer.parseInt(tdNext[j-1].substring(0,2))+1;
										       changeV=String.valueOf(s1)+"00";
										       if(changeV.length()<4){
										    		changeV="0"+changeV;
										    	}
										    }   
										    	
								    	tdNext[j]=changeV;
							
										for(int icr=0;icr<=5;icr++){%>
											if(document.getElementById('<%=tdNext[j]%>.<%=fromDate%>.<%=icr%>')!=null){
												document.getElementById('<%=tdNext[j]%>.<%=fromDate%>.<%=icr%>').removeNode(); 
											}
																			   	
										<%
								    	}}%>
								    	
								    	<%
					      }					      
		}
		}%>
</script>

