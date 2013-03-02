<%@page pageEncoding="UTF-8"%>
<%@ page import="org.king.classmanage.web.help.MajorinWithStuCount"%>
<%@ page import="java.util.List"%>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="org.king.classmanage.domain.Collegemodel" %>
<%@ page import="org.king.classmanage.web.help.MajorinInfo"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="classmanage" key="dormDistribution.title" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="right" valign="middle">
					<bean:message bundle="classmanage" key="dormDistribution.hint" />
				</td>
			</tr>
			
			<tr>
				<td align="center" height="10">
					<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
				</td>
			</tr>
			<%List collegeList = (List) request.getAttribute("collegeList");
			int collegeCount = collegeList.size();

			%>
			<tr>
				<td height="40" align="left" valign="top" class="medium">
					<html:form action="studentAction.do?method=dormDistributionSecondStep">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
							<tbody>
								<tr class="tableHeader">
									<td align="center" valign="middle" class="medium" rowspan="2" width="8%">
										录取大类
									</td>
									<td align="center" valign="middle" class="medium" rowspan="2" width="18%">
										录取院系
									</td>
									<td align="center" valign="middle" class="medium" rowspan="2" width="16%">
										录取专业
									</td>
									<td align="center" valign="middle" class="medium" align="center" valign="middle" class="medium" rowspan="2" width="5%">
										人数
									</td>
									<td align="center" valign="middle" class="medium" colspan="2" width="12%">
										其中中国学生
									</td>
									<td align="center" valign="middle" class="medium" rowspan="2" width="6%">
										留学生
									</td>
									<td align="center" valign="middle" class="medium" colspan="<%=collegeCount%>">
										分配书院
									</td>
								</tr>
								<tr class="tableHeader">
									<td align="center" valign="middle" class="medium">
										男
									</td>
									<td align="center" valign="middle" class="medium">
										女
									</td>
									<logic:present name="collegeList" scope="request">
										<logic:iterate name="collegeList" id="college">
											<td align="center" valign="middle" class="medium">
												<bean:write name="college" property="collegeName" />
											</td>
										</logic:iterate>
									</logic:present>
								</tr>


								<logic:present name="MajorinList" scope="request">
									<logic:iterate name="MajorinList" id="majorin" indexId="i">
										<tr align="center" valign="middle">
											<td valign="middle" id="<bean:write name="majorin" property="dalei" />">
												<strong><bean:write name="majorin" property="dalei" /></strong>
											</td>
											<td valign="middle" id="<bean:write name="majorin" property="yuanxi" />">
												<strong><bean:write name="majorin" property="yuanxi" /></strong>
											</td>

											<c:if test="${i%2 == 0}">
												<td valign="middle" id="<bean:write name="majorin" property="daima" />">
													<strong><bean:write name="majorin" property="zhuanye" /></strong>
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="majorin" property="daima" />.1">
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="majorin" property="daima" />.2">
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="majorin" property="daima" />.3">
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="majorin" property="daima" />.4">
													&nbsp;
												</td>
												<logic:present name="collegeList" scope="request">
													<logic:iterate name="collegeList" id="college">
														<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="college" property="collegeId" />.<bean:write name="majorin" property="daima" />">
															<INPUT type="checkbox" name="<bean:write name="college" property="collegeId" />" value="<bean:write name="majorin" property="daima" />" id="<bean:write name="college" property="collegeId" />">
														</td>
													</logic:iterate>
												</logic:present>
											</c:if>
											<c:if test="${i%2 != 0}">
												<td valign="middle" bgcolor="#F6F4F5" id="<bean:write name="majorin" property="daima" />">
													<strong><bean:write name="majorin" property="zhuanye" /></strong>
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="majorin" property="daima" />.1">
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="majorin" property="daima" />.2">
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="majorin" property="daima" />.3">
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="majorin" property="daima" />.4">
													&nbsp;
												</td>
												<logic:present name="collegeList" scope="request">
													<logic:iterate name="collegeList" id="college">
														<td align="center" valign="middle" bgcolor="#F6F4F5" class="medium" id="<bean:write name="college" property="collegeId" />.<bean:write name="majorin" property="daima" />">
															<INPUT type="checkbox" name="<bean:write name="college" property="collegeId" />" value="<bean:write name="majorin" property="daima" />" id="<bean:write name="college" property="collegeId" />">
														</td>
													</logic:iterate>
												</logic:present>
											</c:if>

										</tr>
									</logic:iterate>
								</logic:present>

								<tr align="center" valign="middle" bgcolor="#FF9999">
									<td align="center" valign="middle" class="medium" colspan="3">
										总计
									</td>
									<td align="center" valign="middle" class="medium" id="--.1">
										&nbsp;
									</td>
									<td align="center" valign="middle" class="medium" id="--.2">
										&nbsp;
									</td>
									<td align="center" valign="middle" class="medium" id="--.3">
										&nbsp;
									</td>
									<td align="center" valign="middle" class="medium" id="--.4">
										&nbsp;
									</td>
									<td align="center" colspan="<%=collegeCount%>" valign="middle" class="medium">
										&nbsp;
									</td>
								</tr>

							</tbody>
						</table>
						<tr>
							<td height="30" align="right" valign="middle" >
								<html:submit property="next" styleClass="button_nor" onclick="return validateFirstStep();">
									<bean:message bundle="classmanage" key="abroadDistribution.nextStep"  />
								</html:submit>
							</td>
						</tr>
					</html:form>
				</td>
			</tr>
		</table>
	</body>
</center>

<Script language="Javascript">
<%
 List collegeLists = (List)request.getAttribute("collegeList");
 List MajorinLists = (List)request.getAttribute("MajorinList"); 
 int collegel = collegeLists.size();
 int majorl = MajorinLists.size();
 String[] coll = new String[collegel];
 String[] maj = new String[majorl];
  

%>
function validateFirstStep(){
	var collegelists = new Array();
	var majorinlists = new Array();
	var s=0;
	var k=0;
	<%
 for(int s=0;s<collegel;s++){
 	Collegemodel collegemodel = (Collegemodel)collegeLists.get(s);
	coll[s] = (String)collegemodel.getCollegeId();
	%>
	collegelists[s]='<%=coll[s]%>';
	s=s+1;
	<%
 }
 for(int k=0;k<majorl;k++){
	MajorinInfo majorinInfo = (MajorinInfo)MajorinLists.get(k);
	maj[k] = (String)majorinInfo.getDaima();
	%>
	majorinlists[k]='<%=maj[k]%>';
	k=k+1;
	<%
 } 	
	%>
	
	var collegelen='<%=collegel%>';
	var majorlen='<%=majorl%>';

	for(var m=0;m<majorlen;m++){
		var count=0;
		for(var n=0;n<collegelen;n++){	
			if(document.getElementById(collegelists[n]+"."+majorinlists[m]).firstChild.checked==false){
				count=count+1;				
			}
		}
		if(count>=collegelen){
			if (confirm("存在专业未分配书院，是否继续下一步?"))	{        	
				return true;
   			}else{
   				return false;
   			}	
		}	
	}
}
	<%
		List AbroadStudentCount = (List)request.getAttribute("AbroadStudentCount");
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
		
		List CHNStudentCount = (List)request.getAttribute("CHNStudentCount");
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
		
		List hisDistribution = (List)request.getAttribute("hisDistribution");
		String collegeId="";
		String majorin="";
		for(int j=0;j<hisDistribution.size();j++){
			Map hisdistr = (Map)hisDistribution.get(j);
			collegeId=hisdistr.get("collegeId").toString();
			majorin=hisdistr.get("majorin").toString();
		%>
		if(document.getElementById("<%=collegeId%>.<%=majorin%>")!=null){
			document.getElementById("<%=collegeId%>.<%=majorin%>").innerHTML='<INPUT type="checkbox" name="<%=collegeId%>" value="<%=majorin%>" checked="checked">';
		}
		<%
		}
		%>
uniteTable(document.all.maintable,2);//执行测试。
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
 
	 function my_onload(){
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	 }	 
	 	 window.onload=my_onload;	
</script>
