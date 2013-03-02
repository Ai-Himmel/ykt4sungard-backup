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
						<strong><font class="medium">筛选统计</font>
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
							id="maintabl">
							<tbody>
								<tr align="center" valign="middle">
									<td width=20% rowspan="2" valign="middle" class="tableHeader">
										状态
									</td>	
									<td width=40% rowspan="2" valign="middle" class="tableHeader">
										类别
									</td>							
									<td width=20% colspan="2" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.master" />
									</td>
									<td width=20% colspan="2" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.doctor" />
									</td>
								</tr>
								<tr>
									<td width=10% valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.male" />
									</td>
									<td width=10% valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.female" />
									</td>
									<td width=10% valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.male" />
									</td>
									<td width=10% valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.female" />
									</td>
								</tr>

								<logic:present name="sxlist" scope="request">
								<%int l=0;%>
									<logic:iterate name="sxlist" id="colcls" indexId="k">
										<tr align="center" valign="middle">
											<td align="center" valign="middle" class="medium" bgcolor="#FFFFFF">
												<bean:write name="colcls" property="state" />
											</td>
											<td align="center" valign="middle" class="medium" <%if(l%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
												<bean:write name="colcls" property="type" />&nbsp;
											</td>
											<td align="center" valign="middle" class="medium" <%if(l%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
												<bean:write name="colcls" property="mmale" />
											</td>
											<td align="center" valign="middle" class="medium" <%if(l%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
												<bean:write name="colcls" property="mfemale" />
											</td>
											<td align="center" valign="middle" class="medium" <%if(l%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
												<bean:write name="colcls" property="dmale" />
											</td>
											<td align="center" valign="middle" class="medium" <%if(l%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
												<bean:write name="colcls" property="dfemale" />
											</td>
										</tr>
										<%l++;%>
									</logic:iterate>
								</logic:present>
							</tbody>
						</table>
					</td>
				</tr>
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium">可申请人数按院系统计</font>
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
									<td width=20% rowspan="2" valign="middle" class="tableHeader">校区</td>
									<td width=40% rowspan="2" valign="middle" class="tableHeader">院系</td>
									<td width=20% colspan="2" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.master" />
									</td>
									<td width=20% colspan="2" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.doctor" />
									</td>
							   </tr>
								<tr>
									<td width=10% valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.male" />
									</td>
									<td width=10% valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.female" />
									</td>
									<td width=10% valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.male" />
									</td>
									<td width=10% valign="middle" class="tableHeader" align="center">
										<bean:message bundle="yangongdormmanage"
											key="dormDistribution.female" />
									</td>
								</tr>								

								<logic:present name="canreqlist" scope="request">								
								<%int k=0;%>
									<logic:iterate name="canreqlist" id="colcl">									
										<tr align="center" valign="middle" >
											<td align="center" valign="middle" class="medium" bgcolor="#FFFFFF">
												<bean:write name="colcl" property="district" />&nbsp;
											</td>
											<td align="center" valign="middle" class="medium" <%if(k%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
												<bean:write name="colcl" property="curCollege" />&nbsp;
											</td>
											<td align="center" valign="middle" class="medium"
												<%if(k%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
												<bean:write name="colcl" property="mmale" />
											</td>
											<td align="center" valign="middle" class="medium"
												<%if(k%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
												<bean:write name="colcl" property="mfemale" />
											</td>
											<td align="center" valign="middle" class="medium"
												<%if(k%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
												<bean:write name="colcl" property="dmale" />
											</td>
											<td align="center" valign="middle" class="medium"
												<%if(k%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
												<bean:write name="colcl" property="dfemale" />
											</td>
										</tr>	
									<%
									k++;
									%>								
									</logic:iterate>
								</logic:present>
							</tbody>
						</table>
					</td>
				</tr>			
			</html:form>
		</table>
	</body>
</center>

<Script language="Javascript">
function DoBack(){   
   self.close();
}		
uniteTable(document.all.maintable,1);
uniteTable1(document.all.maintabl,1);
function uniteTable1(thistab,colLength){
var rn=thistab.rows.length;//取得行数
var rowspann=0;

for(j=colLength-1;j>=0;j--){//从第0列开始，合并多少列

for(i=rn-1;i>0;i--){//从倒数第一行开始往上检查


if(thistab.rows[i].cells[j].innerText==thistab.rows[i-1].cells[j].innerText){//与上面一行比较，如果两行相等就合计当前行的合并行数，并删除当前行。

if(thistab.rows[i].cells[j].children(0)!=null&&thistab.rows[i-1].cells[j].children(0)!=null&&thistab.rows[i].cells[j].children(0).value==thistab.rows[i-1].cells[j].children(0).value){//把前面一列的值放入隐藏域里,如果隐藏域有值就判断是否与上一行的值一样如果一样就合计当前行的合并行数，并删除当前行。

	rowspann+=thistab.rows[i].cells[j].rowSpan;	
	thistab.rows[i].deleteCell(j);	
}else if(thistab.rows[i].cells[j].children(0)==null&&thistab.rows[i-1].cells[j].children(0)==null){//如果隐藏域无值即象第一列那样就只管合并即可	    
		rowspann+=thistab.rows[i].cells[j].rowSpan;		
		thistab.rows[i].deleteCell(j);			
}
else{
thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。

rowspann=0;
}

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
function uniteTable(thistab,colLength){
var rn=thistab.rows.length;//取得行数
var rowspann=0;

for(j=colLength-1;j>=0;j--){//从第0列开始，合并多少列

for(i=rn-1;i>0;i--){//从倒数第一行开始往上检查


if(thistab.rows[i].cells[j].innerText==thistab.rows[i-1].cells[j].innerText){//与上面一行比较，如果两行相等就合计当前行的合并行数，并删除当前行。

if(thistab.rows[i].cells[j].children(0)!=null&&thistab.rows[i-1].cells[j].children(0)!=null&&thistab.rows[i].cells[j].children(0).value==thistab.rows[i-1].cells[j].children(0).value){//把前面一列的值放入隐藏域里,如果隐藏域有值就判断是否与上一行的值一样如果一样就合计当前行的合并行数，并删除当前行。

	rowspann+=thistab.rows[i].cells[j].rowSpan;	
	thistab.rows[i].deleteCell(j);	
}else if(thistab.rows[i].cells[j].children(0)==null&&thistab.rows[i-1].cells[j].children(0)==null){//如果隐藏域无值即象第一列那样就只管合并即可	    
		rowspann+=thistab.rows[i].cells[j].rowSpan;		
		thistab.rows[i].deleteCell(j);			
}
else{
thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。

rowspann=0;
}

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
