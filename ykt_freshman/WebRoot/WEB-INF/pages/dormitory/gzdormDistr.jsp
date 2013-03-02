<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.List"%>
<%@ page import="org.king.classmanage.web.help.ClassStatistic"%>
<%@ page
	import="org.king.yangong.dormitorymanage.web.help.CollegeWithStuCount"%>
<%@ page import="java.util.HashMap"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="left" cellpadding="0"
			cellspacing="0">
			<html:form action="GzDormDistrAction.do?method=dormDistribution">
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium">班级住宿人数统计
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
									<td valign="middle" class="tableHeader" align="center">
										班级
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.account" />
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

								<logic:present name="collegeclassList" scope="request">
									<logic:iterate name="collegeclassList" id="colcls" indexId="k">
										<tr align="center" valign="middle">
											<td align="center" valign="middle" bgcolor="#FFFFFF"
												class="medium"
												id="<bean:write name="colcls" property="classId" />">
												<bean:write name="colcls" property="classNo" />
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="classId" />.1">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="classId" />.2">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="classId" />.3">
												0
											</td>
										</tr>
									</logic:iterate>
								</logic:present>
								<tr align="center" valign="middle" bgcolor="#FF9999">
									<td align="center" valign="middle" class="medium" id="allCount">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.total" />
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
								</tr>
							</tbody>
						</table>
					</td>
				</tr>
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium">班级床位数统计
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
									<td valign="middle" class="tableHeader" align="center">
										班级
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.totaldorm" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.maledorm" />
									</td>
									<td valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.femaledorm" />
									</td>
								</tr>
	

								<logic:present name="collegeclassList" scope="request">
									<logic:iterate name="collegeclassList" id="colcls">
										<tr align="center" valign="middle">
											<td align="center" valign="middle" bgcolor="#FFFFFF"
												class="medium"
												id="<bean:write name="colcls" property="classId" />">
												<bean:write name="colcls" property="classNo" />
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="classId" />.10">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="classId" />.11">
												0
											</td>
											<td align="center" valign="middle" class="medium"
												id="<bean:write name="colcls" property="classId" />.12">
												0
											</td>
										</tr>
									</logic:iterate>
								</logic:present>
								<tr align="center" valign="middle" bgcolor="#FF9999">
									<td align="center" valign="middle" class="medium" id="dormCount">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.total" />
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormCount.10">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormCount.11">
										0
									</td>
									<td align="center" valign="middle" class="medium"
										id="dormCount.12">
										0
									</td>
								</tr>
							</tbody>
						</table>
					</td>
				</tr>
				<tr>
					<td height="30" align="right" valign="middle">
						<html:submit property="distribution" styleClass="button_nor">
							<bean:message bundle="yangongdormmanage"
								key="dormDistribution.distribute" />
						</html:submit>
					</td>
				</tr>
			</html:form>
		</table>
	</body>
</center>

<Script language="Javascript">
	<%
		String collegeCode = "";
		int stuCount= 0;
		int MMaleCount= 0;
		int MFemaleCount = 0;	
		int DMaleCount= 0;
		int DFemaleCount = 0;			
		List CollegeStudentCount = (List)request.getAttribute("ClassStudentCount");
		if(CollegeStudentCount!=null){
			for(int j=0;j<CollegeStudentCount.size();j++){
				CollegeWithStuCount collegeWithStuCount = (CollegeWithStuCount)CollegeStudentCount.get(j);
				collegeCode = collegeWithStuCount.getCollegeCode();
				MMaleCount = collegeWithStuCount.getYjsMaleCount();
				MFemaleCount =collegeWithStuCount.getYjsFemaleCount();
				stuCount = collegeWithStuCount.getStuCount();	
			%>
				if(document.getElementById("<%=collegeCode%>.1")!=null){
					document.getElementById("<%=collegeCode%>.1").innerHTML='<%=stuCount%>';
				}
				if(document.getElementById("<%=collegeCode%>.2")!=null){
					document.getElementById("<%=collegeCode%>.2").innerHTML='<%=MMaleCount%>';
				}
				if(document.getElementById("<%=collegeCode%>.3")!=null){
					document.getElementById("<%=collegeCode%>.3").innerHTML='<%=MFemaleCount%>';
				}
			<%
			}
		}
		String collegeid="";
		String flag="";
		String dormCount="";
		List CollegeDormitoryStatistic = (List)request.getAttribute("ClassDormitoryStatistic");	
		if(CollegeDormitoryStatistic!=null){
			for(int j=0;j<CollegeDormitoryStatistic.size();j++){
				HashMap cdstatistic = (HashMap)CollegeDormitoryStatistic.get(j);
				collegeid = cdstatistic.get("collegeId").toString();
				dormCount = cdstatistic.get("accomodation").toString();
				flag = cdstatistic.get("flag").toString();	
				if("dormCount".equals(collegeid)){
				%>
			if(document.getElementById("dormCount.<%=flag%>")!=null){
					document.getElementById("dormCount.<%=flag%>").innerHTML='<%=dormCount%>';
				}
			<%
				}else{		
			%>
			if(document.getElementById("<%=collegeid%>.<%=flag%>")!=null){
					document.getElementById("<%=collegeid%>.<%=flag%>").innerHTML='<%=dormCount%>';
				}
			<%
			}
			}
		}
		%>
		
//uniteTable(document.all.maintable,1);//执行测试。

	//合并书院、班级单元格
function uniteTable(thistab,colLength){
	var rn=thistab.rows.length;//取得行数
	var rowspann=0;
	for(j=colLength-1;j>=0;j--){//从第0列开始，合并多少列

		for(i=rn-1;i>0;i--){//从倒数第一行开始往上检查

			if(thistab.rows[i].cells[j].innerText==thistab.rows[i-1].cells[j].innerText&&thistab.rows[i].cells[j].colSpan==thistab.rows[i-1].cells[j].colSpan){//与上面一行比较，如果两行相等就合计当前行的合并行数，并删除当前行。

				rowspann+=thistab.rows[i].cells[j].rowSpan;
				thistab.rows[i].deleteCell(j);
			}else{
				thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。

				rowspann=0;
			}
			}
			//检测无表头的表
			if(i==0&&rowspann>0){
			thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。

			rowspann=0;
		}
	}
}
</script>
