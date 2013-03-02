<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.List"%>
<%@ page import="java.lang.Integer"%>
<%@ page import="org.king.classmanage.web.help.ClassStatistic"%>
<%@ page import="org.king.classmanage.web.help.NationDistributionInfo"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">班级分配结果统计</font></strong>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>			
			<tr>
				<td height="30" align="left" valign="middle" class="medium">
					<strong><font color="#990000"><a name="2">文理统计:</a></font></strong>
				</td>
			</tr>
			<tr>
				<td height="40" align="left" valign="top" class="medium">
					<table width=100% border=1 cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id="maintable">
						<tbody>
							<tr align="center" valign="middle">
								<td width="20%" height="24" valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.classes" /></strong>
								</td>
								<logic:present name="examTypeList" scope="request">
									<logic:iterate name="examTypeList" id="examType">
										<td valign="middle" class="tableHeader" id="<bean:write name="examType" property="dictValue" />">
											<strong><bean:write name="examType" property="dictCaption" /></strong>
										</td>
									</logic:iterate>
								</logic:present>
								<td valign="middle" class="tableHeader" >
								<strong>总计</strong>
								</td>							
							</tr>
							<logic:present name="collegeclassList" scope="request">
								<logic:iterate name="collegeclassList" id="colcls" indexId="i">
									<c:if test="${colcls.collegeName!='allCount'}">
										<tr align="center" valign="middle">
											<c:if test="${colcls.classNo=='smallCount'}">
												<td  align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
													合计
												</td>
												<logic:present name="examTypeList" scope="request">
													<logic:iterate name="examTypeList" id="majorin">
														<td align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.<bean:write name="majorin" property="dictValue" />">
															0
														</td>
													</logic:iterate>
												</logic:present>
												<td align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.allCount">
													0
												</td>												
											</c:if>
											<c:if test="${colcls.classNo!='smallCount'}">
												<c:if test="${i%2 == 0}">
													<td  align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
														<bean:write name="colcls" property="classNo" />
													</td>
													<logic:present name="examTypeList" scope="request">
														<logic:iterate name="examTypeList" id="majorin">
															<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.<bean:write name="majorin" property="dictValue" />">
																0
															</td>
														</logic:iterate>
													</logic:present>
												<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.allCount">
													0
												</td>
												</c:if>
												<c:if test="${i%2 != 0}">
													<td  align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
														<bean:write name="colcls" property="classNo" />
													</td>
													<logic:present name="examTypeList" scope="request">
														<logic:iterate name="examTypeList" id="majorin">
															<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.<bean:write name="majorin" property="dictValue" />">
																0
															</td>
														</logic:iterate>
													</logic:present>
												<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.allCount">
													0
												</td>												
												</c:if>
													
											</c:if>

										</tr>
									</c:if>


								</logic:iterate>
							</logic:present>
						</tbody>
					</table>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="30" align="left" valign="middle" class="medium">
					<strong><font color="#990000"><a name="2">性别统计:</a></font></strong>
				</td>
			</tr>
			<tr>
				<td height="40" align="left" valign="top" class="medium">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
						<tbody>
							<tr align="left" valign="middle">
								<td height="24" valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.classes" /></strong>
								</td>
								<logic:present name="majorList" scope="request">
									<logic:iterate name="majorList" id="examType">
										<td valign="middle" class="tableHeader" id="<bean:write name="examType" property="dictValue" />">
											<strong><bean:write name="examType" property="dictCaption" /></strong>
										</td>
									</logic:iterate>
								</logic:present>
								<td valign="middle" class="tableHeader" >
								<strong>总计</strong>
								</td>							
							</tr>
							<logic:present name="gendercollegeclassList" scope="request">
								<logic:iterate name="gendercollegeclassList" id="colcls" indexId="i">
									<c:if test="${colcls.collegeName!='allCount'}">
										<tr align="left" valign="middle">
											<c:if test="${colcls.classNo=='smallCount'}">
												<td width="30%" align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
													合计
												</td>
												<logic:present name="majorList" scope="request">
													<logic:iterate name="majorList" id="majorin">
														<td align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.<bean:write name="majorin" property="dictValue" />gender">
															0
														</td>
													</logic:iterate>
												</logic:present>
												<td align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.allCountgender">
													0
												</td>												
											</c:if>
											<c:if test="${colcls.classNo!='smallCount'}">
												<c:if test="${i%2 == 0}">
													<td width="30%" align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
														<bean:write name="colcls" property="classNo" />
													</td>
													<logic:present name="majorList" scope="request">
														<logic:iterate name="majorList" id="majorin">
															<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.<bean:write name="majorin" property="dictValue" />gender">
																0
															</td>
														</logic:iterate>
													</logic:present>
												<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.allCountgender">
													0
												</td>
												</c:if>
												<c:if test="${i%2 != 0}">
													<td width="30%" align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
														<bean:write name="colcls" property="classNo" />
													</td>
													<logic:present name="majorList" scope="request">
														<logic:iterate name="majorList" id="majorin">
															<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.<bean:write name="majorin" property="dictValue" />gender">
																0
															</td>
														</logic:iterate>
													</logic:present>
												<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.allCountgender">
													0
												</td>												
												</c:if>
													
											</c:if>

										</tr>
									</c:if>


								</logic:iterate>
							</logic:present>
						</tbody>
					</table>
				</td>
			</tr>
		</table>
	</body>
</center>

<Script language="Javascript">	
<%
		List classStatististic = (List)request.getAttribute("classStatististic");
		String collegeId = "";
		String classNo="";
		String majorin="";
		String stuCount="";	
		for(int j=0;j<classStatististic.size();j++){
			NationDistributionInfo nationdistributionInfo = (NationDistributionInfo)classStatististic.get(j);
			collegeId = nationdistributionInfo.getCollegeName();
			if(collegeId.equals("")){
				collegeId = "0002";
			}
			classNo =  nationdistributionInfo.getClassName();
			majorin = nationdistributionInfo.getNation();
			if(nationdistributionInfo.getStudentCount()!=0){
				stuCount = String.valueOf(nationdistributionInfo.getStudentCount());
			}

		
	%>
//	var allCount =0;var stuCount ='<%=stuCount%>';
	if(document.getElementById("<%=collegeId%>.<%=classNo%>.<%=majorin%>")!=null){
		document.getElementById("<%=collegeId%>.<%=classNo%>.<%=majorin%>").innerHTML='<%=stuCount%>';
//		allCount = parseInt(allCount)+parseInt(stuCount);
		document.getElementById("<%=collegeId%>.<%=classNo%>.allCount").innerHTML
		=parseInt(document.getElementById("<%=collegeId%>.<%=classNo%>.allCount").innerHTML)
		+parseInt(document.getElementById("<%=collegeId%>.<%=classNo%>.<%=majorin%>").innerHTML);
	}	
	<%
		}
	%>


<%
		List majorStatistic = (List)request.getAttribute("majorinStatistic");
		String gendercollegeId = "";
		String genderclassNo="";
		String gendermajorin="";
		String genderstuCount="";	
		for(int j=0;j<majorStatistic.size();j++){
			NationDistributionInfo genderdistributionInfo = (NationDistributionInfo)majorStatistic.get(j);
			gendercollegeId = genderdistributionInfo.getCollegeName();
			if(gendercollegeId.equals("")){
				gendercollegeId = "0002";
			}
			genderclassNo =  genderdistributionInfo.getClassName();
			gendermajorin = genderdistributionInfo.getNation();
			if(genderdistributionInfo.getStudentCount()!=0){
				genderstuCount = String.valueOf(genderdistributionInfo.getStudentCount());
			}

		
	%>
//	var allCount ="0";var genderstuCount ='<%=genderstuCount%>';
	if(document.getElementById("<%=gendercollegeId%>.<%=genderclassNo%>.<%=gendermajorin%>gender")!=null){
		document.getElementById("<%=gendercollegeId%>.<%=genderclassNo%>.<%=gendermajorin%>gender").innerHTML='<%=genderstuCount%>';
//		allCount = parseInt(allCount)+parseInt(genderstuCount);
		document.getElementById("<%=gendercollegeId%>.<%=genderclassNo%>.allCountgender").innerHTML
		=parseInt(document.getElementById("<%=gendercollegeId%>.<%=genderclassNo%>.allCountgender").innerHTML)
		+parseInt(document.getElementById("<%=gendercollegeId%>.<%=genderclassNo%>.<%=gendermajorin%>gender").innerHTML);
	}	
	<%
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
