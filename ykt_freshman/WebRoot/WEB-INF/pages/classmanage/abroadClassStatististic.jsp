<%@page pageEncoding="UTF-8"%>
<%@ page import="java.util.List" %>
<%@ page import="org.king.classmanage.web.help.NationDistributionInfo" %>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="left" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="classmanage" key="abroadDistribution.abroadDistributionStatistic" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="40" align="left" valign="top" class="medium">
					<table width=100% border=1 cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
						<tbody>
							<tr align="center" valign="middle">
								<td width="30%" valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.college" /></strong>
								</td>
								<td width="35%" height="24" valign="middle" class="tableHeader">
									<strong><bean:message bundle="classmanage" key="classStatistic.classes" /></strong>
								</td>
								<logic:present name="majorList" scope="request">
									<logic:iterate name="majorList" id="majorin">
										<td valign="middle" class="tableHeader" width="16px" id="<bean:write name="majorin" property="dictValue" />">
											<strong><bean:write name="majorin" property="dictCaption" /></strong>
										</td>
									</logic:iterate>
								</logic:present>
							</tr>
							<logic:present name="collegeclassList" scope="request">
								<logic:iterate name="collegeclassList" id="colcls">
									<tr align="center" valign="middle">
										<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />">
											<bean:write name="colcls" property="collegeName" />
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />">
											<bean:write name="colcls" property="classNo" />
										</td>
										<logic:present name="majorList" scope="request">
											<logic:iterate name="majorList" id="majorin">
													<td align="center" valign="middle" bgcolor="#FFFFFF" class="medium" id="<bean:write name="colcls" property="collegeId" />.<bean:write name="colcls" property="classNo" />.<bean:write name="majorin" property="dictValue" />">
														&nbsp;
													</td>
												</logic:iterate>
										</logic:present>
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
		List majorStatistic = (List)request.getAttribute("majorinStatistic");
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
	document.getElementById("<%=collegeId%>.<%=classNo%>.<%=majorin%>").innerHTML='<%=stuCount%>';
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
