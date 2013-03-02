<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.List"%>
<%@ page import="org.king.classmanage.web.help.NationDistributionInfo"%>
<%@ page import="org.king.classmanage.web.help.ClassStatistic"%>
<%@ page import="org.king.classmanage.web.help.MajorinWithStuCount"%>
<%@ page import="java.util.Map"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<html:form action="studentAction.do?method=dormDistributionLastStep">
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium"><bean:message bundle="classmanage" key="dormDistribution.statistic" /></font></strong>
					</td>
				</tr>
				<tr>
					<td align="left" valign="middle">
						&nbsp;
					</td>
				</tr>
				<tr>
					<td height="40" align="center" valign="top" class="medium">

						<table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id="maintable">
							<tbody>
								<tr align="center" valign="middle">
									<td rowspan="2" valign="middle" class="tableHeader">
										书院
									</td>
									<td rowspan="2" valign="middle" class="tableHeader">
										人数
									</td>
									<td colspan="2" valign="middle" class="tableHeader">
										其中中国学生
									</td>
									<td rowspan="2" valign="middle" class="tableHeader">
										留学生
									</td>
								</tr>
								<tr>
									<td valign="middle" class="tableHeader">
										男
									</td>
									<td valign="middle" class="tableHeader">
										女
									</td>

									<logic:present name="collegeList" scope="request">
										<logic:iterate name="collegeList" id="colcls" indexId="k">
											<tr align="center" valign="middle">
												<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />">
													<bean:write name="colcls" property="collegeName" />
												</td>
												<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.1">
													&nbsp;
												</td>
												<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.2">
													&nbsp;
												</td>
												<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.3">
													&nbsp;
												</td>
												<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.4">
													&nbsp;
												</td>
											</tr>
										</logic:iterate>
									</logic:present>
								<tr align="center" valign="middle" bgcolor="#FF9999">
									<td align="center" valign="middle" class="medium" id="allCount">
										总计
									</td>
									<td align="center" valign="middle" class="medium" id="allCount.1">
										&nbsp;
									</td>
									<td align="center" valign="middle" class="medium" id="allCount.2">
										&nbsp;
									</td>
									<td align="center" valign="middle" class="medium" id="allCount.3">
										&nbsp;
									</td>
									<td align="center" valign="middle" class="medium" id="allCount.4">
										&nbsp;
									</td>
							</tbody>
						</table>
					</td>
				</tr>
<!--  -->				
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="classmanage" key="dormDistribution.statistic1" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="40" align="left" valign="top" class="medium">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable1>
						<tbody>

							<tr align="center" valign="middle">
								<td width="10%" valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.college" /></strong>
								</td>
								<logic:present name="daleiList" scope="request">
									<logic:iterate name="daleiList" id="dalei">
										<td valign="middle" class="tableHeader" id="<bean:write name="dalei" property="id.dictValue" />">
											<strong><bean:write name="dalei" property="dictCaption" /></strong>
										</td>
									</logic:iterate>
								</logic:present>
							</tr>
							<logic:present name="collegeList1" scope="request">
								<logic:iterate name="collegeList1" id="college1" indexId="k">
									<c:if test="${college1.collegeName!='daleiCount'}">
										<tr align="center" valign="middle">
											<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="college1" property="collegeId" />">
												<bean:write name="college1" property="collegeName" />
											</td>
											<c:if test="${k%2 == 0}">
												<logic:present name="daleiList" scope="request">
													<logic:iterate name="daleiList" id="dalei">
														<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="college1" property="collegeId" />.<bean:write name="dalei" property="id.dictValue" />.majorin">
															&nbsp;
														</td>
													</logic:iterate>
												</logic:present>
											</c:if>
											<c:if test="${k%2 != 0}">
												<logic:present name="daleiList" scope="request">
													<logic:iterate name="daleiList" id="dalei">
														<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="college1" property="collegeId" />.<bean:write name="dalei" property="id.dictValue" />.majorin">
															&nbsp;
														</td>
													</logic:iterate>
												</logic:present>
											</c:if>
										</tr>
									</c:if>
									<c:if test="${college1.collegeName=='daleiCount'}">
										<tr align="center" valign="middle" bgcolor="#FF9999">
											<td align="center" valign="middle" class="medium" id="daleiCount">
												总计
											</td>				
											<logic:present name="daleiList" scope="request">
												<logic:iterate name="daleiList" id="dalei">
													<td align="center" valign="middle" class="medium" id="daleiCount.<bean:write name="dalei" property="id.dictValue" />.majorin">
														&nbsp;
													</td>
												</logic:iterate>
											</logic:present>
										</tr>
									</c:if>
								</logic:iterate>
							</logic:present>
						</tbody>
					</table>
				</td>
			</tr><!--  -->				
				
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium"><bean:message bundle="classmanage" key="dormDistribution.collegeDormitorystatistic" /></font></strong>
					</td>
				</tr>
				<tr>
					<td align="left" valign="middle">
						&nbsp;
					</td>
				</tr>
				<tr>
					<td height="40" align="center" valign="top" class="medium">
						<table width=100% border=1 align="center" cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id="maintable">
							<tbody>
								<tr align="center" valign="middle">
									<td valign="middle" class="tableHeader">
										书院
									</td>
									<td valign="middle" class="tableHeader">
										宿舍总床位
									</td>
									<td valign="middle" class="tableHeader">
										男生床位
									</td>
									<td valign="middle" class="tableHeader">
										男生人数
									</td>									
									<td valign="middle" class="tableHeader">
										女生床位
									</td>
									<td valign="middle" class="tableHeader">
										女生人数
									</td>										
								</tr>
								<logic:present name="collegeList" scope="request">
									<logic:iterate name="collegeList" id="colcls">
										<tr align="center" valign="middle">
											<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />">
												<bean:write name="colcls" property="collegeName" />
											</td>
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.10">
												&nbsp;
											</td>
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.11">
												&nbsp;
											</td>
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.13">
												&nbsp;
											</td>											
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.12">
												&nbsp;
											</td>
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.14">
												&nbsp;
											</td>											
										</tr>
									</logic:iterate>
								</logic:present>
							</tbody>
						</table>
					</td>
				</tr>
				<tr>
					<td height="30" align="right" valign="middle">
						<INPUT type="button" name="goback" value="<bean:message bundle="classmanage" key="abroadDistribution.preStep" />" class="button_nor" onclick="javascript:howtoreturn();">
						<html:submit property="distribution" styleClass="button_nor">
							<bean:message bundle="classmanage" key="abroadDistribution.distribute" />
						</html:submit>
					</td>
				</tr>
			</html:form>
		</table>
	</body>
</center>

<Script language="Javascript">
	<%
		List daleiResultStatistic = (List)request.getAttribute("daleiResultStatistic");
		String collegeId1 = "";
		String classNo="";
		String majorin="";
		String stuCount1="";
		for(int j=0;j<daleiResultStatistic.size();j++){
			NationDistributionInfo nationdistributionInfo = (NationDistributionInfo)daleiResultStatistic.get(j);
			collegeId1 = nationdistributionInfo.getCollegeName();
//			classNo =  nationdistributionInfo.getClassName();
			majorin = nationdistributionInfo.getNation();
			if(nationdistributionInfo.getStudentCount()!=0){
				stuCount1 = String.valueOf(nationdistributionInfo.getStudentCount());
			}
			
		
	%>
	if(document.getElementById("<%=collegeId1%>.<%=majorin%>.majorin")!=null){
		document.getElementById("<%=collegeId1%>.<%=majorin%>.majorin").innerHTML='<%=stuCount1%>';
	}

	<%}
		List AbroadStudentCount = (List)request.getAttribute("CollegeAbroadStudentCount");
		String majorinCode = "";
		int stuCount= 0;
		int stuMaleCount= 0;
		int stuFemaleCount = 0;
		
		for(int j=0;j<AbroadStudentCount.size();j++){
			MajorinWithStuCount majorinwithstucount = (MajorinWithStuCount)AbroadStudentCount.get(j);
			majorinCode = majorinwithstucount.getMajorinCode();
			stuCount = majorinwithstucount.getStuCount();
		%>
			if(document.getElementById("<%=majorinCode%>.1")!=null){
				document.getElementById("<%=majorinCode%>.1").innerHTML='<%=stuCount%>';
			}
			if(document.getElementById("<%=majorinCode%>.4")!=null){
				document.getElementById("<%=majorinCode%>.4").innerHTML='<%=stuCount%>';
			}
		<%
		}
		
		List CHNStudentCount = (List)request.getAttribute("CollegeCHNStudentCount");
		majorinCode = "";
		stuCount= 0;
		stuMaleCount= 0;
		stuFemaleCount = 0;
		for(int j=0;j<CHNStudentCount.size();j++){
			MajorinWithStuCount majorinwithstucount = (MajorinWithStuCount)CHNStudentCount.get(j);
			majorinCode = majorinwithstucount.getMajorinCode();
			stuCount = majorinwithstucount.getStuCount();
			stuMaleCount = majorinwithstucount.getStuMaleCount();
			stuFemaleCount = majorinwithstucount.getStuFemaleCount();		
		%>
			if(document.getElementById("<%=majorinCode%>.1")!=null){
				document.getElementById("<%=majorinCode%>.1").innerHTML='<%=stuCount%>';
			}
			if(document.getElementById("<%=majorinCode%>.2")!=null){
				document.getElementById("<%=majorinCode%>.2").innerHTML='<%=stuMaleCount%>';
			}
			if(document.getElementById("<%=majorinCode%>.3")!=null){
				document.getElementById("<%=majorinCode%>.3").innerHTML='<%=stuFemaleCount%>';
			}
		<%
		}
		String collegeid="";
		String flag="";
		String dormCount="";
		List CollegeDormitoryStatistic = (List)request.getAttribute("CollegeDormitoryStatistic");	
		for(int j=0;j<CollegeDormitoryStatistic.size();j++){
			Map cdstatistic = (Map)CollegeDormitoryStatistic.get(j);
			collegeid = cdstatistic.get("collegeId").toString();
			dormCount = cdstatistic.get("accomodation").toString();
			flag = cdstatistic.get("flag").toString();			
		%>
		if(document.getElementById("<%=collegeid%>.<%=flag%>")!=null){
			document.getElementById("<%=collegeid%>.<%=flag%>").innerHTML='<%=dormCount%>';
			if(document.getElementById("<%=collegeid%>.11").innerHTML<document.getElementById("<%=collegeid%>.13").innerHTML){
				document.getElementById("<%=collegeid%>.13").style.color ="red";			
			}
			if(document.getElementById("<%=collegeid%>.12").innerHTML<document.getElementById("<%=collegeid%>.14").innerHTML){
				document.getElementById("<%=collegeid%>.14").style.color ="red";			
			}			
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

function howtoreturn(){
	window.location.href='studentAction.do?method=dormDistributionFirstStep';

}
</script>
