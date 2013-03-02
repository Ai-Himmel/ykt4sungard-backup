<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.List"%>
<%@ page import="org.king.classmanage.web.help.ClassStatistic"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="left" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="classmanage" key="classStatistic.classStatistic" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="30" align="left" valign="middle" class="tdborder02">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff>
						<tr>
							<td>
								报到前统计：
							</td>
							<td>
								<a href="classAction.do?method=classStatististic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.studentStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=majorinStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.majorinStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nativeplaceStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.fromprovincStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationalityStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationalityStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=daleiStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.daleiStatistic" /></a>
							</td>
						</tr>
						<tr>
							<td>
								报到后统计：
							</td>
							<td>
								<a href="classAction.do?method=classCheckInStatististic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.studentCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=majorinCheckInStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.majorinCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nativeplaceCheckInStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.fromprovincCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationCheckInStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationalityCheckInStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationalityCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=daleiCheckInStatistic" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.daleiStatistic" /></a>
							</td>
						</tr>
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
					<strong><font color="#990000"><a name="2"><bean:message bundle="classmanage" key="classStatistic.studentStatistic" />:</a></font></strong>
				</td>
			</tr>
			<tr>
				<td height="40" align="left" valign="top" class="medium">
					<table width=100% border=1 cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id="maintable">
						<tbody>
							<tr align="center" valign="middle">
								<td width="20%" valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.college" /></strong>
								</td>
								<td width="20%" height="24" valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.classes" /></strong>
								</td>
								<td valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.malestudents" /></strong>
								</td>
								<td valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.femalestudents" /></strong>
								</td>
								<td valign="middle" class="tableHeader">
									<strong>中国学生</strong>
								</td>
								<td valign="middle" class="tableHeader">
									<strong>留学生</strong>
								</td>
								<td valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.students" /></strong>
								</td>

							</tr>
							<logic:present name="collegeclassList" scope="request">
								<logic:iterate name="collegeclassList" id="colcls" indexId="k">
									<c:if test="${colcls.collegeName!='allCount'}">
										<tr align="center" valign="middle">
											<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />">
												<bean:write name="colcls" property="collegeName" />
											</td>
											<c:if test="${colcls.classNo=='smallCount'}">
												<td align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
													小计
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.1">
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.2">
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.3">
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.4">
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.5">
													&nbsp;
												</td>
											</c:if>
											<c:if test="${colcls.classNo!='smallCount'}">
												<td align="center" valign="middle" bgcolor="#FFFFFF" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
													<bean:write name="colcls" property="classNo" />
												</td>
												<c:if test="${k%2 == 0}">
													<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.1">
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.2">
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.3">
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.4">
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.5">
														&nbsp;
													</td>
												</c:if>
												<c:if test="${k%2 != 0}">
													<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.1">
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.2">
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.3">
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.4">
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.5">
														&nbsp;
													</td>
												</c:if>
											</c:if>
										</tr>
									</c:if>
									<c:if test="${colcls.collegeName=='allCount'}">
										<tr align="center" valign="middle" bgcolor="#FF9999">
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />">
												总计
											</td>
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
												<bean:write name="colcls" property="classNo" />
											</td>
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.1">
												&nbsp;
											</td>
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.2">
												&nbsp;
											</td>
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.3">
												&nbsp;
											</td>
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.4">
												&nbsp;
											</td>
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.5">
												&nbsp;
											</td>
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
		int stuMale= 0;
		int stuFemale= 0;
		int stuCount= 0;
		for(int j=0;j<classStatististic.size();j++){
			ClassStatistic classstatistic = (ClassStatistic)classStatististic.get(j);
			collegeId = classstatistic.getCollegeName();
			classNo =  classstatistic.getClassName();
			stuMale = classstatistic.getStuMale();
			stuFemale = classstatistic.getStuFemale();
			stuCount = classstatistic.getStuNumber();
			if(stuMale>0){
			%>
			if(document.getElementById("<%=collegeId%>.<%=classNo%>.<%=1%>")!=null){	
				document.getElementById("<%=collegeId%>.<%=classNo%>.<%=1%>").innerHTML='<%=stuMale%>';
			}	
			<%
			}
			if(stuFemale>0){
			%>
			if(document.getElementById("<%=collegeId%>.<%=classNo%>.<%=2%>")!=null){
				document.getElementById("<%=collegeId%>.<%=classNo%>.<%=2%>").innerHTML='<%=stuFemale%>';
			}	
			<%
			}	
			if(stuCount>0){
			%>
			if(document.getElementById("<%=collegeId%>.<%=classNo%>.<%=5%>")!=null){
				document.getElementById("<%=collegeId%>.<%=classNo%>.<%=5%>").innerHTML='<%=stuCount%>';
			}	
			<%
			}	
		%>	
	<%
		}
	%>
	
	<%
		List classStatististicWithAborad = (List)request.getAttribute("classStatististicWithAborad");
		collegeId = "";
		classNo="";
		stuMale= 0;
		stuFemale= 0;
		stuCount= 0;
		for(int j=0;j<classStatististicWithAborad.size();j++){
			ClassStatistic classstatistic = (ClassStatistic)classStatististicWithAborad.get(j);
			collegeId = classstatistic.getCollegeName();
			classNo =  classstatistic.getClassName();
			stuMale = classstatistic.getStuMale();
			stuFemale = classstatistic.getStuFemale();
			stuCount = classstatistic.getStuNumber();
			if(stuMale>0){
			%>
			if(document.getElementById("<%=collegeId%>.<%=classNo%>.<%=3%>")!=null){	
				document.getElementById("<%=collegeId%>.<%=classNo%>.<%=3%>").innerHTML='<%=stuMale%>';
			}	
			<%
			}
			if(stuFemale>0){
			%>
			if(document.getElementById("<%=collegeId%>.<%=classNo%>.<%=4%>")!=null){
				document.getElementById("<%=collegeId%>.<%=classNo%>.<%=4%>").innerHTML='<%=stuFemale%>';
			}	
			<%
			}	
			if(stuCount>0){
			%>
			if(document.getElementById("<%=collegeId%>.<%=classNo%>.<%=5%>")!=null){
				document.getElementById("<%=collegeId%>.<%=classNo%>.<%=5%>").innerHTML='<%=stuCount%>';
			}	
			<%
			}	
		%>	
	<%
		}
	%>
	
uniteTable(document.all.maintable,1);//执行测试。
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
