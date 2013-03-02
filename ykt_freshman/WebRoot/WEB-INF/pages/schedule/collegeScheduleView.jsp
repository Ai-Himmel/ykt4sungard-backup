<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.schedulemanage.domain.Collegeschedulemodel"%>
<%@ page import="org.king.classmanage.domain.Collegemodel"%>
<%@ include file="../tiles/include.jsp"%>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="middle">
				&nbsp;
			</td>
		</tr>


		<tr>
			<td height="40" align="left" valign="top" class="medium">
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
					<tbody>
						<logic:present name="scheduledateList" scope="request">
							<logic:iterate name="scheduledateList" id="scheduledate">
								<tr align="center" valign="middle">
									<td width="25" height="24" valign="middle" class="tableHeader">
										&nbsp;
									</td>
									<%String collegeCount = request.getAttribute("collegeCount")
					.toString();%>
									<td colspan="<%=collegeCount%>" valign="middle" class="tableHeader">
										<bean:write name="scheduledate" property="dictCaption" />
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td align="center" valign="middle" bgcolor="#FFFFFF">
										&nbsp;
									</td>
									<logic:present name="collegeList" scope="request">
										<logic:iterate name="collegeList" id="college">
											<td align="center" valign="middle" bgcolor="#F6F4F5">
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
								<tr align="center" valign="middle" height="10" id='<%=hours+minites%>.<bean:write name="scheduledate" property="id.dictValue"/>'>
									<td align="center" valign="middle" bgcolor="#FFFFFF" width="4%" height="10px">
										<%=hours + ":" + minites%>
									</td>
									<logic:present name="collegeList" scope="request">
										<logic:iterate name="collegeList" id="college" indexId="l">
											<c:if test="${l%2 == 0}">
												<td id='<%=hours+minites%>.<bean:write name="scheduledate" property="id.dictValue"/>.<bean:write name="college" property="collegeId"/>' valign="middle" bgcolor="#FFFFFF" >
													&nbsp;
												</td>
											</c:if>
											<c:if test="${l%2 != 0}">
												<td id='<%=hours+minites%>.<bean:write name="scheduledate" property="id.dictValue"/>.<bean:write name="college" property="collegeId"/>' valign="middle" bgcolor="#F6F4F5" >
													&nbsp;
												</td>
											</c:if>
										</logic:iterate>
									</logic:present>
									<%}%>
								</tr>
								<%}

			%>
							</logic:iterate>
						</logic:present>
					</tbody>
				</table>
			</td>
		</tr>
	</table>
</body>

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
		int rows=0;
		int cows = collegeList.size();
		String[] tdNext;
		for(int i=0;i<scheduleList.size();i++){
				//获得日程信息字段
				Collegeschedulemodel collegeschedule=(Collegeschedulemodel)scheduleList.get(i);
				scheduleId=collegeschedule.getScheduleId();
				collegeId=collegeschedule.getCollegeId();
				fromTime=collegeschedule.getFromtime();								
			    toTime=collegeschedule.getTotime();
			    fromDate=collegeschedule.getFromdate();
			    toDate=collegeschedule.getTodate();
			    mission=collegeschedule.getMission();
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
			    		    			    			    
					    if((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite)>5){
						    rows=((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite))/5;
						    }
						  %>					        					      
							document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").innerHTML='<a href="scheduleAction.do?method=cRevise&scheduleId=<%=scheduleId%>"><font size="2"><%=fromTime.substring(0,2)%>:<%=fromTime.substring(2)%>--<%=toTime.substring(0,2)%>:<%=toTime.substring(2)%><br><br><%=position%><br><br><%=mission%><br><br><%=objecter%><br><br><%=remark%></font></a>';
							document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").rowSpan='<%=2%>';	
							document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").colSpan='<%=cows%>';						
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
					 
					//删除行

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
						    	//删除列

						    	if(j<rows-1){
						    	
						    	%>												
								document.getElementById('<%=tdNext[j]%>.<%=fromDate%>').removeNode();								   	
								<%
								}else{
								    if(cows>1){
								    	for(int k=0;k<cows;k++){
								    		collegemodel =(Collegemodel) collegeList.get(k);
								    		collegeId=collegemodel.getCollegeId();
								    		%>												
											document.getElementById('<%=tdNext[j]%>.<%=fromDate%>.<%=collegeId%>').removeNode();								   	
											<%
								    	}								    	
								    }
							    }										
							}
					    }					      
			    }else{
			    //单个书院的安排

			    	    
					//设置相关格式			    			    			    
					    if((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite)>5){
						    rows=((toTimehour*60+toTimeminite)-(fromTimehour*60+fromTimeminite))/5;
						    }
						  %>					        					      
							document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").innerHTML='<font size="2"><%=fromTime.substring(0,2)%>:<%=fromTime.substring(2)%>--<%=toTime.substring(0,2)%>:<%=toTime.substring(2)%><br><br><%=position%><br><br><%=mission%><br><br><%=objecter%><br><br><%=remark%></font>';
							document.getElementById("<%=tdId%>.<%=fromDate%>.<%=collegeId%>").rowSpan='<%=rows%>';							
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
