<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.List"%>
<%@ page import="org.king.classmanage.web.help.NationDistributionInfo"%>
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
								<a href="classAction.do?method=classStatististic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.studentStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=majorinStatistic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.majorinStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nativeplaceStatistic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.fromprovincStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationStatistic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationalityStatistic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationalityStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=daleiStatistic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.daleiStatistic" /></a>
							</td>
						</tr>
						<tr>
							<td>
								报到后统计：
							</td>
							<td>
								<a href="classAction.do?method=classCheckInStatististic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.studentCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=majorinCheckInStatistic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.majorinCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nativeplaceCheckInStatistic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.fromprovincCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationCheckInStatistic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=nationalityCheckInStatistic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.nationalityCheckInStatistic" /></a>
							</td>
							<td>
								<a href="classAction.do?method=daleiCheckInStatistic&getrole=2" class="topmenu_link"><bean:message bundle="classmanage" key="classStatistic.daleiStatistic" /></a>
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
					<strong><font color="#990000"><a name="2"><bean:message bundle="classmanage" key="classStatistic.nationStatistic" />:</a></font></strong>
				</td>
			</tr>

			<tr>
				<td height="40" align="left" valign="top" class="medium">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
						<tbody>
							<tr align="center" valign="middle">
								<td width="10%" valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.college" /></strong>
								</td>
								<td width="10%" height="24" valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.classes" /></strong>
								</td>
								<logic:present name="nationList" scope="request">
									<logic:iterate name="nationList" id="nation">
										<td valign="middle" class="tableHeader" id="<bean:write name="nation" property="dictValue" />">
											<strong><bean:write name="nation" property="dictCaption" /></strong>
										</td>
									</logic:iterate>
								</logic:present>
							</tr>
							<logic:present name="collegeclassList" scope="request">
								<logic:iterate name="collegeclassList" id="colcls" indexId="i">
									<c:if test="${colcls.collegeName!='allCount'}">
										<tr align="center" valign="middle">
											<td width="60px" align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />">
												<bean:write name="colcls" property="collegeName" />
											</td>
											<c:if test="${colcls.classNo=='smallCount'}">
												<td width="60px" align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
													小计
												</td>
												<logic:present name="nationList" scope="request">
													<logic:iterate name="nationList" id="nation">
														<td align="center" valign="middle" bgcolor="#FFFFCC" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.<bean:write name="nation" property="dictValue" />">
															&nbsp;
														</td>
													</logic:iterate>
												</logic:present>		
											</c:if>
											<c:if test="${colcls.classNo!='smallCount'}">
												<c:if test="${i%2 == 0}">
													<td width="60px" align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
														<bean:write name="colcls" property="classNo" />
													</td>
													<logic:present name="nationList" scope="request">
														<logic:iterate name="nationList" id="nation">
															<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.<bean:write name="nation" property="dictValue" />">
																&nbsp;
															</td>
														</logic:iterate>
													</logic:present>
												</c:if>
												<c:if test="${i%2 != 0}">
													<td width="60px" align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
														<bean:write name="colcls" property="classNo" />
													</td>
													<logic:present name="nationList" scope="request">
														<logic:iterate name="nationList" id="nation">
															<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.<bean:write name="nation" property="dictValue" />">
																&nbsp;
															</td>
														</logic:iterate>
													</logic:present>			
												</c:if>		
											</c:if>

										</tr>
									</c:if>
									<c:if test="${colcls.collegeName=='allCount'}">
										<tr align="center" valign="middle" bgcolor="#FF9999">
											<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />">
												总计
											</td>
											<td width="60px" align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
												<bean:write name="colcls" property="classNo" />
											</td>
											<logic:present name="nationList" scope="request">
												<logic:iterate name="nationList" id="nation">
													<td align="center" valign="middle" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.<bean:write name="nation" property="dictValue" />">
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
			</tr>
		</table>
	</body>
</center>

<Script language="Javascript">
	<%
		List majorStatistic = (List)request.getAttribute("nationStatistic");
		String collegeId = "";
		String classNo="";
		String majorin="";
		String stuCount="";
		for(int j=0;j<majorStatistic.size();j++){
			NationDistributionInfo nationdistributionInfo = (NationDistributionInfo)majorStatistic.get(j);
			collegeId = nationdistributionInfo.getCollegeName();
			classNo =  nationdistributionInfo.getClassName();
			majorin = nationdistributionInfo.getNation();
			if(nationdistributionInfo.getStudentCount()!=0){
				stuCount = String.valueOf(nationdistributionInfo.getStudentCount());
			}
			
		
	%>
	if(document.getElementById("<%=collegeId%>.<%=classNo%>.<%=majorin%>")!=null){
		document.getElementById("<%=collegeId%>.<%=classNo%>.<%=majorin%>").innerHTML='<%=stuCount%>';
	}
	
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
	//合并书院、班级单元格
function uniteTable1(thistab){
	
	var rn=thistab.rows.length;//取得行数
	var cn=thistab.rows[1].getElementsByTagName('td').length-1;//取得列数
	var rowspann=0;
	for(i=rn-1;i>0;i--){//从倒数第一行开始往上检查
		if(thistab.rows[i].cells[cn].innerText==thistab.rows[i-1].cells[cn].innerText&&thistab.rows[i].cells[cn].colSpan==thistab.rows[i-1].cells[cn].colSpan){//与上面一行比较，如果两行相等就合计当前行的合并行数，并删除当前行。
			rowspann+=thistab.rows[i].cells[cn].rowSpan;
			thistab.rows[i].deleteCell(cn);
		}else{
			thistab.rows[i].cells[cn].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
			rowspann=0;
		}
	}
	//检测无表头的表
	if(i==0&&rowspann>0){
	thistab.rows[i].cells[cn].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
	rowspann=0;
	}
 }
</script>
