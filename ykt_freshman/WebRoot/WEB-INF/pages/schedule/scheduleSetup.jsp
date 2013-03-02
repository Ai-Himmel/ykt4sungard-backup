<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.schedulemanage.domain.Collegeschedulemodel"%>
<%@ page import="org.king.classmanage.domain.Collegemodel"%>
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
	}
</style>
<script>
function changeDate(dateId){
	window.location.href = "scheduleAction.do?method=load4List&dateId=" + dateId;
}
function doAdd(){
	window.location.href="scheduleAction.do?method=addCollegeSchedule&dateId=" + document.getElementById("dateId").value;
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
	<%
					String collegeCount = request.getAttribute("collegeCount")
					.toString();
					if(collegeCount.equals("0")){						
				%>
					<br><font color="red">尚未建立书院，无法进行日程安排，请先建立书院信息</font>
				<% }else{%>
	<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
		<form>
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium"><a name="top">整体日程安排设置</a></font></strong>
			</td>
		</tr>
		
		<tr>
			<table width="100%">
				<tr>
					<td height="30">
					请选择日期：
						<select id="dateId" name="dateId" onchange="changeDate(this.value)">
							<c:forEach items="${scheduledateList}" var="date">
								<option value="<c:out value="${date.id.dictValue}"/>" <c:if test = "${date.id.dictValue == dateId}">
								selected
								<c:set var="scheduledate" value="${date}"/>
							</c:if>>
									<c:out value="${date.dictCaption}" />
								</option>
							</c:forEach>
						</select>
					</td>
					<td align="right" valign="middle">
						<html:button property="search" styleClass="button_nor" onclick="javascript:doAdd();">
							<bean:message key="button.add" />
						</html:button>
					</td>
				</tr>
			</table>


		</tr>
		<tr>
			<td height="40" align="center" valign="top" class="medium">
				
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
					<tbody>
						<logic:present name="scheduledateList" scope="request">

							<tr align="center" valign="middle">
								<td width="4%" height="24" valign="middle" class="tableHeader">
									&nbsp;
								</td>
								
								<td colspan="<%=collegeCount%>" valign="middle" class="tableHeader">
									<c:out value="${scheduledate.dictCaption}" />
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
							<%String hours = "", minites = "";
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
					}%>
							<tr align="center" valign="middle" id='<%=hours+minites%>.<bean:write name="scheduledate" property="id.dictValue"/>'>
								<%String tdCss = "td-common";
					if (minite == 0 || minite == 30) {
						tdCss = "td-00-30";

						%>
								<td rowspan="6" align="center" valign="top" bgcolor="#FFFFFF">
									<%=hours + ":" + minites%>
								</td>
								<%}%>

								<logic:present name="collegeList" scope="request">
									<logic:iterate name="collegeList" id="college" indexId="i">
										<c:if test="${i%2 == 0}">
											<td id='<%=hours+minites%>.<c:out value="${scheduledate.id.dictValue}"/>.<bean:write name="college" property="collegeId"/>' class="<%=tdCss%>" valign="middle" bgcolor="#FFFFFF">
												&nbsp;
											</td>
										</c:if>
										<c:if test="${i%2 != 0}">
											<td id='<%=hours+minites%>.<c:out value="${scheduledate.id.dictValue}"/>.<bean:write name="college" property="collegeId"/>' class="<%=tdCss%>" " valign="middle" bgcolor="#F6F4F5">
												&nbsp;
											</td>
										</c:if>
									</logic:iterate>
								</logic:present>
							</tr>
							<%}%>

							<%}

			%>

						</logic:present>
					</tbody>
				</table>
			</td>
		</tr>
	</table>


<Script language="Javascript">
	<%
		ArrayList scheduleList=(ArrayList)request.getAttribute("scheduleList");
		ArrayList collegeList = (ArrayList)request.getAttribute("collegeList");
		String collegeId=""; //书院
		String fromTime=""; //从时间
		String toTime=""; //到时间
		String fromDate =""; //从日期
		String toDate =""; //到日期
		String objecter =""; //对象
		String position =""; //地点
		String mission =""; //任务
		String remark ="";//备注
		String scheduleId =""; //日程id	
		String tdId ="";//页面td标识
		
		int cows = collegeList.size();
		String[] tdNext;
		for(int i=0;i<scheduleList.size();i++){
				int rows=0;
				//获得日程信息字段
				Collegeschedulemodel collegeschedule=(Collegeschedulemodel)scheduleList.get(i);
				scheduleId=collegeschedule.getScheduleId();
				collegeId=collegeschedule.getCollegeId();
				fromTime=collegeschedule.getFromtime();								
			    toTime=collegeschedule.getTotime();
			    fromDate=collegeschedule.getFromdate();
			    toDate=collegeschedule.getTodate();
			    mission=collegeschedule.getMission();
			    mission=mission==null?"":mission.trim();
			    objecter =collegeschedule.getObject();
			    position = collegeschedule.getPositon();
			    tdId=fromTime;
			    int toTimehour=Integer.parseInt(toTime.substring(0,2));
			    int fromTimehour=Integer.parseInt(fromTime.substring(0,2));
			    int toTimeminite=Integer.parseInt(toTime.substring(2));
			    int fromTimeminite=Integer.parseInt(fromTime.substring(2));
			    
			    if("ALL".equals(collegeId)){
			    //全体书院的安排
			    //设置相关格式			
			   	 	Collegemodel collegemodel =(Collegemodel) collegeList.get(0);
					collegeId=collegemodel.getCollegeId();
			    		    			    			    
					    if((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite)>=5){
						    rows=((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite))/5;
						    }
						  %>					        					      
							document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").innerHTML='<c:if test="${!view}"><a href="scheduleAction.do?method=cRevise&scheduleId=<%=scheduleId%>"></c:if><font size="2"><%=fromTime.substring(0,2)%>:<%=fromTime.substring(2)%>--<%=toTime.substring(0,2)%>:<%=toTime.substring(2)%><br><%=position%><br><%=mission%><br><%=objecter%><br><%=remark%></font><c:if test="${!view}"></a></c:if>';
							document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").rowSpan='<%=rows%>';	
							document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").colSpan='<%=cows%>';
							document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").className = "content";						
					      <%
					   if(cows>1){
						  for(int k=1;k<cows;k++){
				    		collegemodel =(Collegemodel) collegeList.get(k);
				    		collegeId=collegemodel.getCollegeId();
				    		%>												
							document.getElementById('<%=tdId%>.<%=fromDate%>.<%=collegeId%>').removeNode();								   	
							<%
					   	  }	
					   }
					   
					  
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
						    	
								    
								    	for(int k=0;k<cows;k++){
								    		collegemodel =(Collegemodel) collegeList.get(k);
								    		collegeId=collegemodel.getCollegeId();
								    		%>												
											document.getElementById('<%=tdNext[j]%>.<%=fromDate%>.<%=collegeId%>').removeNode();								   	
											<%
								    	}								    	
								    
							    										
							}
					    }										      
			    }else{
			    //单个书院的安排
			    	    
					//设置相关格式			    			    			    
					    if((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite)>=5){
						    rows=((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite))/5;
						    }
						  %>					        			
						  document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").innerHTML='<c:if test="${!view}"><a href="scheduleAction.do?method=cRevise&scheduleId=<%=scheduleId%>"></c:if><font size="2"><%=fromTime.substring(0,2)%>:<%=fromTime.substring(2)%>--<%=toTime.substring(0,2)%>:<%=toTime.substring(2)%><br><%=position%><br><%=mission%><br><%=objecter%><br><%=remark%></font><c:if test="${!view}"></a></c:if>';
						  document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").rowSpan='<%=rows%>';
						  document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").className = "content";							
					      <%
					//删除单元格
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
					
								%>												
										document.getElementById('<%=tdNext[j]%>.<%=fromDate%>.<%=collegeId%>').removeNode();								   	
								<%
						    	}
					      }					      
					}	
					
			}		    
			   %>	
</script>
</body>
<%}%>