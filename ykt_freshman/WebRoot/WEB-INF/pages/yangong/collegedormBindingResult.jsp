<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.List"%>
<%@ page import="java.util.Map"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="left" cellpadding="0"
			cellspacing="0">
			<html:form action="collegeDormBindingAction.do?method=dormDistributionStatistic">
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium">院系宿舍绑定按院系统计
						</font>
						</strong>
					</td>
				</tr>
				<tr>
					<td align="left" valign="middle">
						<html:errors bundle="yangongdormmanage" />
					</td>
				</tr>
				<tr>
					<td height="40" align="center" valign="top" class="medium">
                    
						<table width=100% border=1 align="center" cellpadding=1
							cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff
							id="maintable">
							<tbody>
								<tr align="center" valign="middle">
									<td rowspan="3" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.college" />
									</td>	
									<td rowspan="3" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.account" />
									</td>
									<td rowspan="3" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.dormaccount" />
									</td>								
									<td colspan="4" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.master" />
									</td>
									<td colspan="4" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.doctor" />
									</td>
								</tr>
								<tr>
									<td colspan="2" valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.male" />
									</td>
									<td colspan="2" valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.female" />
									</td>
									<td colspan="2" valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.male" />
									</td>
									<td colspan="2" valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.female" />
									</td>
								</tr>
								<tr>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.shouldbind" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.exactbind" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.shouldbind" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.exactbind" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.shouldbind" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.exactbind" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.shouldbind" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.exactbind" />
									</td>
								</tr>

								<logic:present name="collegeList" scope="request">
								<%int l=0;%>
									<logic:iterate name="collegeList" id="colcls" indexId="k">
										<tr align="center" valign="middle" <%if(l%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
											<td align="center" valign="middle" 
												class="medium"
												id="<bean:write name="colcls" property="deptCode" />">
												<bean:write name="colcls" property="deptName" />
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="deptCode" />.stu">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="deptCode" />.dorm">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="deptCode" />.1">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="deptCode" />.2">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="deptCode" />.3">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="deptCode" />.4">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="deptCode" />.5">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="deptCode" />.6">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="deptCode" />.7">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="deptCode" />.8">
												0
											</td>
										</tr>
										<%l++;%>
									</logic:iterate>
								</logic:present>
								<tr align="center" valign="middle" bgcolor="#FF9999">
									<td align="center" valign="middle" class="medium" id="allCount">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.total" />
									</td>
									<td align="center" valign="middle" class="medium"
										id="allCount.stu">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="allCount.dorm">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="allCount.1">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="allCount.2">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="allCount.3">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="allCount.4">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="allCount.5">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="allCount.6">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="allCount.7">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="allCount.8">
										0
									</td>
								</tr>
							</tbody>
						</table>
					</td>
				</tr>
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium">院系宿舍绑定按楼统计
						</font>
						</strong>
					</td>
				</tr>
				<tr>
					<td align="left" valign="middle">
						&nbsp;
					</td>
				</tr>
				<tr>
					<td height="40" align="center" valign="top" class="medium">
						<table width=100% border=1 align="center" cellpadding=1
							cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff
							id="maintable">
							<tbody>
								<tr>
									<td rowspan="2" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="graduate.section" />
									</td>
									<td rowspan="2" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="graduate.districtrion2" />
									</td>
									<td rowspan="2" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="graduate.building" />
									</td>
									<td colspan="3" valign="middle" class="tableHeader">
										可绑定床位数
									</td>
									<td colspan="3" valign="middle" class="tableHeader">
										未绑定床位数
									</td>
									<td rowspan="2" valign="middle" class="tableHeader">
										已绑定床位总数
									</td>
									<td colspan="2" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.master" />
									</td>
									<td colspan="2" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.doctor" />
									</td>
							   </tr>
								<tr>
								    <td valign="middle" class="tableHeader" align="center">
										总
									</td>
								    <td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.male" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.female" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										总
									</td>
								    <td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.male" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.female" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.male" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.female" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.male" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.female" />
									</td>
								</tr>								

								<logic:present name="dormList" scope="request">								
								<%int k=0;%>
									<logic:iterate name="dormList" id="colcls">									
										<tr align="center" valign="middle" <%if(k%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
											<td align="center" valign="middle" 
												class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />">
												<bean:write name="colcls" property="areaName" />&nbsp;
											</td>
											<td align="center" valign="middle" class="medium">
												<bean:write name="colcls" property="locationName" />&nbsp;
											</td>
											<td align="center" valign="middle" class="medium">
												<bean:write name="colcls" property="dormitoryName" />&nbsp;
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />.totaltotal">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />.totalmale">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />.totalfemale">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />.lefttotal">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />.leftmale">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />.leftfemale">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />.total">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />.1">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />.2">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />.3">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="area" /><bean:write name="colcls" property="location" /><bean:write name="colcls" property="dormitory" />.4">
												0
											</td>											
										</tr>	
									<%
									k++;
									%>								
									</logic:iterate>
								</logic:present>
								<tr align="center" valign="middle" bgcolor="#FF9999">
									<td colspan="3" align="center" valign="middle" class="medium" id="dormallCount">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.total" />
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormallCount.totaltotal">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormallCount.totalmale">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormallCount.totalfemale">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormallCount.lefttotal">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormallCount.leftmale">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormallCount.leftfemale">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormallCount.total">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormallCount.1">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormallCount.2">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormallCount.3">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormallCount.4">
										0
									</td>
								</tr>
							</tbody>
						</table>
					</td>
				</tr>
				<%String ispop=request.getParameter("ispop");%>
				<%if(ispop!=null&&ispop.equals("1")){%>
				<tr>
					<td height="30" align="right" valign="middle">
						<html:button property="bclose" styleClass="button_nor" onclick="DoBack()">
							关闭
						</html:button>
					</td>
				</tr>
				<%}%>				
			</html:form>
		</table>
	</body>
</center>

<Script language="Javascript">
	<%
		String collegeCode = "";
		int MMalesb = 0;
		int MFemalesb = 0;
		int DMalesb = 0;
		int DFemalesb = 0;
		int stusb = 0;
		
		int MMaleexb = 0;
		int MFemaleexb = 0;
		int DMaleexb = 0;
		int DFemaleexb = 0;
		int dormexb = 0;
		
		int MMalesbtotal = 0;
		int MFemalesbtotal = 0;
		int DMalesbtotal = 0;
		int DFemalesbtotal = 0;
		int stuallSum = 0;
		
		int MMaleexbtotal = 0;
		int MFemaleexbtotal = 0;
		int DMaleexbtotal = 0;
		int DFemaleexbtotal = 0;
		int dormallSum = 0;		
			
		List CollegeStudentCount =new ArrayList();
		if(request.getAttribute("CollegeStudentCount")!=null)    
		    CollegeStudentCount=(List)request.getAttribute("CollegeStudentCount");
		if(CollegeStudentCount!=null&&CollegeStudentCount.size()>0){
			for(int j=0;j<CollegeStudentCount.size();j++){
			    
				Map collegeWithStuCount = (Map)CollegeStudentCount.get(j);
				
				if (j==CollegeStudentCount.size() - 1) {
			        stuallSum=((Integer)collegeWithStuCount.get("stuallSum")).intValue();
			        dormallSum=((Integer)collegeWithStuCount.get("dormallSum")).intValue();
			        
			        MMalesbtotal=((Integer)collegeWithStuCount.get("MMalesbtotal")).intValue();
			        MFemalesbtotal =((Integer)collegeWithStuCount.get("MFemalesbtotal")).intValue();
			        DMalesbtotal =((Integer)collegeWithStuCount.get("DMalesbtotal")).intValue();
                    DFemalesbtotal =((Integer)collegeWithStuCount.get("DFemalesbtotal")).intValue();

                    MMaleexbtotal =((Integer)collegeWithStuCount.get("MMaleexbtotal")).intValue();
                    MFemaleexbtotal =((Integer)collegeWithStuCount.get("MFemaleexbtotal")).intValue();
                    DMaleexbtotal =((Integer)collegeWithStuCount.get("DMaleexbtotal")).intValue();
                    DFemaleexbtotal =((Integer)collegeWithStuCount.get("DFemaleexbtotal")).intValue();
                    
                    %>
				
				
					document.getElementById("allCount.stu").innerHTML='<%=stuallSum%>';
				    document.getElementById("allCount.dorm").innerHTML='<%=dormallSum%>';
				    document.getElementById("allCount.1").innerHTML='<%=MMalesbtotal%>';
				    document.getElementById("allCount.2").innerHTML='<%=MMaleexbtotal%>';
				    document.getElementById("allCount.3").innerHTML='<%=MFemalesbtotal%>';
				    document.getElementById("allCount.4").innerHTML='<%=MFemaleexbtotal%>';
				    document.getElementById("allCount.5").innerHTML='<%=DMalesbtotal%>';
				    document.getElementById("allCount.6").innerHTML='<%=DMaleexbtotal%>';
				    document.getElementById("allCount.7").innerHTML='<%=DFemalesbtotal%>';
				    document.getElementById("allCount.8").innerHTML='<%=DFemaleexbtotal%>';
				    
			<%
                    
                    break;
			    }
				
				collegeCode = (String)collegeWithStuCount.get("curCollege");
				stusb= ((Integer)collegeWithStuCount.get("colStuNum")).intValue();
				dormexb= ((Integer)collegeWithStuCount.get("colDormNum")).intValue();
				
				MMalesb = ((Integer)collegeWithStuCount.get("mmaleshouldbindNum")).intValue();
				MFemalesb =((Integer)collegeWithStuCount.get("mfemaleshouldbindNum")).intValue();
				DMalesb =((Integer)collegeWithStuCount.get("dmaleshouldbindNum")).intValue();
				DFemalesb =((Integer)collegeWithStuCount.get("dfemaleshouldbindNum")).intValue();
				
				MMaleexb = ((Integer)collegeWithStuCount.get("mmaleexactbindNum")).intValue();
				MFemaleexb =((Integer)collegeWithStuCount.get("mfemaleexactbindNum")).intValue();
				DMaleexb =((Integer)collegeWithStuCount.get("dmaleexactbindNum")).intValue();
				DFemaleexb =((Integer)collegeWithStuCount.get("dfemaleexactbindNum")).intValue();
					
			%>
				
				if(document.getElementById("<%=collegeCode%>.stu")!=null){
					document.getElementById("<%=collegeCode%>.stu").innerHTML='<%=stusb%>';
				}
				if(document.getElementById("<%=collegeCode%>.dorm")!=null){
					document.getElementById("<%=collegeCode%>.dorm").innerHTML='<%=dormexb%>';
				}
				if(document.getElementById("<%=collegeCode%>.1")!=null){
					document.getElementById("<%=collegeCode%>.1").innerHTML='<%=MMalesb%>';
				}
				if(document.getElementById("<%=collegeCode%>.2")!=null){
					document.getElementById("<%=collegeCode%>.2").innerHTML='<%=MMaleexb%>';
				}
				if(document.getElementById("<%=collegeCode%>.3")!=null){
					document.getElementById("<%=collegeCode%>.3").innerHTML='<%=MFemalesb%>';
				}
				if(document.getElementById("<%=collegeCode%>.4")!=null){
					document.getElementById("<%=collegeCode%>.4").innerHTML='<%=MFemaleexb%>';
				}
				if(document.getElementById("<%=collegeCode%>.5")!=null){
					document.getElementById("<%=collegeCode%>.5").innerHTML='<%=DMalesb%>';
				}
				if(document.getElementById("<%=collegeCode%>.6")!=null){
					document.getElementById("<%=collegeCode%>.6").innerHTML='<%=DMaleexb%>';
				}
				if(document.getElementById("<%=collegeCode%>.7")!=null){
					document.getElementById("<%=collegeCode%>.7").innerHTML='<%=DFemalesb%>';
				}
				if(document.getElementById("<%=collegeCode%>.8")!=null){
					document.getElementById("<%=collegeCode%>.8").innerHTML='<%=DFemaleexb%>';
				}
			<%
			}
		}
		
		
		String dormstr="";
		
		int totaltotalNum=0;
		int totalmaleNum=0;
		int totalfemaleNum=0;
		int lefttotalNum=0;
		int leftmaleNum=0;
		int leftfemaleNum=0;
		
		int distributeNum=0;
		int mmaleNum=0;
		int mfemaleNum=0;
		int dmaleNum=0;
		int dfemaleNum=0;
		
		int totaltotaltotal=0;
		int totalmaletotal=0;
		int totalfemaletotal=0;		
		int lefttotaltotal=0;
		int leftmaletotal=0;
		int leftfemaletotal=0;
		
		int dormtotal=0;
		int mmaletotal=0;
		int mfemaletotal=0;
		int dmaletotal=0;
		int dfemaletotal=0;
		
		List CollegeDormitoryStatistic = new ArrayList();
		
		if(request.getAttribute("DormitoryStatistic")!=null)
		    CollegeDormitoryStatistic=(List)request.getAttribute("DormitoryStatistic");	
		    
		if(CollegeDormitoryStatistic!=null&&CollegeDormitoryStatistic.size()>0){
			for(int j=0;j<CollegeDormitoryStatistic.size();j++){
				Map cdstatistic = (Map)CollegeDormitoryStatistic.get(j);
				
				if (j==CollegeDormitoryStatistic.size() - 1) {
				
				    totaltotaltotal=((Integer)cdstatistic.get("totaltotaltotal")).intValue();
		            totalmaletotal=((Integer)cdstatistic.get("totalmaletotal")).intValue();
		            totalfemaletotal=((Integer)cdstatistic.get("totalfemaletotal")).intValue();
		            lefttotaltotal=((Integer)cdstatistic.get("lefttotaltotal")).intValue();
		            leftmaletotal=((Integer)cdstatistic.get("leftmaletotal")).intValue();
		            leftfemaletotal=((Integer)cdstatistic.get("leftfemaletotal")).intValue();
			        
			        dormtotal=((Integer)cdstatistic.get("dormtotal")).intValue();
			        
			        mmaletotal=((Integer)cdstatistic.get("mmaletotal")).intValue();
			        mfemaletotal =((Integer)cdstatistic.get("mfemaletotal")).intValue();
			        dmaletotal =((Integer)cdstatistic.get("dmaletotal")).intValue();
                    dfemaletotal =((Integer)cdstatistic.get("dfemaletotal")).intValue();
                    
                    %>
				
				    document.getElementById("dormallCount.totaltotal").innerHTML='<%=totaltotaltotal%>';
				    document.getElementById("dormallCount.totalmale").innerHTML='<%=totalmaletotal%>';
				    document.getElementById("dormallCount.totalfemale").innerHTML='<%=totalfemaletotal%>';				    
				    document.getElementById("dormallCount.lefttotal").innerHTML='<%=lefttotaltotal%>';
				    document.getElementById("dormallCount.leftmale").innerHTML='<%=leftmaletotal%>';
				    document.getElementById("dormallCount.leftfemale").innerHTML='<%=leftfemaletotal%>';
				    
				    document.getElementById("dormallCount.total").innerHTML='<%=dormtotal%>';
				    document.getElementById("dormallCount.1").innerHTML='<%=mmaletotal%>';
				    document.getElementById("dormallCount.2").innerHTML='<%=mfemaletotal%>';
				    document.getElementById("dormallCount.3").innerHTML='<%=dmaletotal%>';
				    document.getElementById("dormallCount.4").innerHTML='<%=dfemaletotal%>';
				    
			<%
                    
                    break;
			    }
			    
				dormstr ="";
				if(cdstatistic.get("area")!=null)
				     dormstr=dormstr+(String)cdstatistic.get("area");
				if(cdstatistic.get("location")!=null)
				     dormstr=dormstr+(String)cdstatistic.get("location");
				if(cdstatistic.get("dormitory")!=null)
				     dormstr=dormstr+(String)cdstatistic.get("dormitory");
				
				totaltotalNum=((Integer)cdstatistic.get("totaltotalNum")).intValue();
		        totalmaleNum=((Integer)cdstatistic.get("totalmaleNum")).intValue();
		        totalfemaleNum=((Integer)cdstatistic.get("totalfemaleNum")).intValue();
		        lefttotalNum=((Integer)cdstatistic.get("lefttotalNum")).intValue();
		        leftmaleNum=((Integer)cdstatistic.get("leftmaleNum")).intValue();
		        leftfemaleNum=((Integer)cdstatistic.get("leftfemaleNum")).intValue();
								
				distributeNum= ((Integer)cdstatistic.get("distributeNum")).intValue();
				
				mmaleNum = ((Integer)cdstatistic.get("mmaleNum")).intValue();
				mfemaleNum =((Integer)cdstatistic.get("mfemaleNum")).intValue();
				dmaleNum =((Integer)cdstatistic.get("dmaleNum")).intValue();
				dfemaleNum =((Integer)cdstatistic.get("dfemaleNum")).intValue();
			%>
			
			    if(document.getElementById("<%=dormstr%>.totaltotal")!=null){
					document.getElementById("<%=dormstr%>.totaltotal").innerHTML='<%=totaltotalNum%>';
				}
				if(document.getElementById("<%=dormstr%>.totalmale")!=null){
					document.getElementById("<%=dormstr%>.totalmale").innerHTML='<%=totalmaleNum%>';
				}
				if(document.getElementById("<%=dormstr%>.totalfemale")!=null){
					document.getElementById("<%=dormstr%>.totalfemale").innerHTML='<%=totalfemaleNum%>';
				}
				if(document.getElementById("<%=dormstr%>.lefttotal")!=null){
					document.getElementById("<%=dormstr%>.lefttotal").innerHTML='<%=lefttotalNum%>';
				}
				if(document.getElementById("<%=dormstr%>.leftmale")!=null){
					document.getElementById("<%=dormstr%>.leftmale").innerHTML='<%=leftmaleNum%>';
				}
				if(document.getElementById("<%=dormstr%>.leftfemale")!=null){
					document.getElementById("<%=dormstr%>.leftfemale").innerHTML='<%=leftfemaleNum%>';
				}				
			    
			    if(document.getElementById("<%=dormstr%>.total")!=null){
					document.getElementById("<%=dormstr%>.total").innerHTML='<%=distributeNum%>';
				}
				if(document.getElementById("<%=dormstr%>.1")!=null){
					document.getElementById("<%=dormstr%>.1").innerHTML='<%=mmaleNum%>';
				}
				if(document.getElementById("<%=dormstr%>.2")!=null){
					document.getElementById("<%=dormstr%>.2").innerHTML='<%=mfemaleNum%>';
				}
				if(document.getElementById("<%=dormstr%>.3")!=null){
					document.getElementById("<%=dormstr%>.3").innerHTML='<%=dmaleNum%>';
				}
				if(document.getElementById("<%=dormstr%>.4")!=null){
					document.getElementById("<%=dormstr%>.4").innerHTML='<%=dfemaleNum%>';
				}
			<%
			}
		}
		%>

function DoBack(){   
   self.close();
}		
</script>
