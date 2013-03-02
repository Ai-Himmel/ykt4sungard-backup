<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.classmanage.domain.Classmodel"%>
<%@ page import="org.king.dormitorymanage.web.help.DormitoryWithAllInfo"%>
<%@ include file="../tiles/include.jsp"%>
<%@ page import="java.util.HashMap"%>

<script language="JavaScript">
function clearAll(){

	document.all("area").value="";
	document.all("location").value="";
	document.all("dorm").value="";
	document.all("roomNumber").value="";
	document.all("unit").value="";
	document.all("dormfee").value="";
	document.all("studentNo").value="";
	document.all("stuName").value="";
	document.all("gender").value="";
}

function document.onkeydown()
{
	var e=event.srcElement;
	if(event.keyCode==13)
	{
		document.all("search").click();
		return false;
	}
}
</script>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium">学生住宿信息查询</font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="top" height="10"></td>
		</tr>
		<tr>
			<td align="center" valign="top">
				<html:form method="post" action="DormitorySearchAction.do?method=searchDetail&getrole=3" onsubmit="javascript:return on_validate();">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
						<tr>
							<td>
								<%if (request.getAttribute("mydormitory") != null) {
								String mydormitory = request.getAttribute("mydormitory").toString();
				%>
								<INPUT type="hidden" name="mydormitory" value="<%=mydormitory%>">
								<%} else {

			%>
								<INPUT type="hidden" name="mydormitory" value="">

								<%}

			%>
							</td>
						</tr>
						<tr>
								<td>
									<INPUT type="hidden" name="export" value="">
								</td>
							</tr>
							<tr>
								<td>
									<INPUT type="hidden" name="orderby" value="">
									<INPUT type="hidden" name="sort" value="">
								</td>
							</tr>
						<tbody>
							<tr align="center" valign=middle>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<span class="medium">校区</span>
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:select property="area" styleClass="select01" onchange="javascript:changeArea(this.value);">
										<html:option value="">-----------------------</html:option>
										<html:options collection="areaList" property="dictValue" labelProperty="dictCaption" />
									</html:select>
								</td>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<span class="medium">区域</span>
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:select property="location" styleClass="select01" onchange="javascript:changeLocation(this.value);">
										<html:option value="">-----------------------</html:option>
										<html:options collection="locationList" property="dictValue" labelProperty="dictCaption" />									
									</html:select>
								</td>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<span class="medium"><bean:message bundle="dormitorymanage" key="dormitorySearch.dormitory" /></span>
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="dorm" >
										<html:option value="">-----------------------</html:option>
										<html:options collection="dormitoryList" property="dictValue" labelProperty="dictCaption" />																			
									</html:select>
								</td>								
							</tr>						

							<tr align="center" valign=middle>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									单元号									
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:text property="unit" styleClass="input_box" style="width:120" maxlength="4"/>
								</td>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.roomNumber" />
								</td>
								<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
									<html:text property="roomNumber" styleClass="input_box" maxlength="4"/>
								</td>							

								<td width="10%" align="right" valign="middle" class="tableHeader2">
									住宿费(元)
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<html:text property="dormfee" styleClass="input_box" maxlength="7"/>
								</td>
							</tr>
							<tr align="center" valign=middle>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.stuNo" />
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:text property="studentNo" styleClass="input_box" maxlength="20"/>
								</td>
								<td width="10%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.stuName" />
								</td>
								<td width="20%" align="left" valign="middle" class="tableHeader3">
									<html:text property="stuName" styleClass="input_box" maxlength="20"/>
								</td>

						    	<td width="10%" align="right" valign="middle" class="tableHeader2">
									<bean:message bundle="dormitorymanage" key="dormitorySearch.gender" />
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<html:select styleClass="select01" property="gender">
										<html:option value="">-----------------------</html:option>
										<html:options collection="genderList" property="id.dictValue" labelProperty="dictCaption" />
									</html:select>
								</td>								
							</tr>

						</tbody>
					</table>
					<tr>
						<td height="40" align="right" valign="middle" class="tdborder02">
							<html:submit property="search" styleClass="button_nor" onclick="javascript:NotExport();">
								<bean:message key="button.query" />
							</html:submit>
							<html:button property="reset" styleClass="button_nor" onclick="clearAll();">
									<bean:message key="button.reset" />
								</html:button>
						</td>
					</tr>
				</html:form>
			</td>
		</tr>
		<tr>
			<td align="left" valign="middle">
				<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
			</td>
		</tr>
		<tr>
			<td height="40" align="center" valign="top">
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
					<tbody>
						<tr align="center" valign=middle>
							<td height="24" valign="middle" class="tableHeader" onclick="sortTable('area');">
								校区
							</td>
							<td height="24" valign="middle" class="tableHeader" onclick="sortTable('location');">
								区域
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('dormitory');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.dormitory" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('unit');">
								单元号
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('roomNumber');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.roomNumber" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('dormfee');">
								住宿费(单位:元)
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('stuNo');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.stuNo" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('stuName');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.stuName" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('gender');">
								<bean:message bundle="dormitorymanage" key="dormitorySearch.gender" />
							</td>
							<td valign="middle" class="tableHeader" onclick="sortTable('gender');">
								出生日期
							</td>
						</tr>

						<logic:present name="dormitorys" scope="request">
							<%int dormitoryCount = ((Integer) request.getAttribute("dormitoryCount")).intValue();%>
							<!--page offset start -->
							<pg:pager url="./DormitorySearchAction.do" items="<%=dormitoryCount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
								<%-- keep track of preference --%>
								<pg:param name="method" />
								<pg:param name="area" />
								<pg:param name="location" />
								<pg:param name="dorm" />
								<pg:param name="unit" />
								<pg:param name="roomNumber" />
								<pg:param name="dormfee" />
								<pg:param name="studentNo" />
								<pg:param name="stuName" />
								<pg:param name="gender" />
								<pg:param name="page" />
								<pg:param name="orderby" />
								<pg:param name="sort" />
								<pg:param name="getrole" />

								<%-- save pager offset during form changes --%>
								<input type="hidden" name="pager.offset" value="<%= offset %>">
								<logic:iterate name="dormitorys" id="dry" indexId="i">
									<pg:item>
									<tr align="center" valign=middle>
												<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">

												<bean:write name="dry" property="area" />
													&nbsp;
												</td>									
												<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
												<input type="hidden" name="hpf" value="<bean:write name="dry" property="area" /><bean:write name="dry" property="location" />">												

													<bean:write name="dry" property="location" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
												<input type="hidden" name="hpf" value="<bean:write name="dry" property="area" /><bean:write name="dry" property="location" /><bean:write name="dry" property="dormitory" />">																																																

													<bean:write name="dry" property="dormitory" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
												<input type="hidden" name="hpf" value="<bean:write name="dry" property="area" /><bean:write name="dry" property="location" /><bean:write name="dry" property="dormitory" /><bean:write name="dry" property="unit" />">																																																																								
													<bean:write name="dry" property="unit" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">

													<bean:write name="dry" property="roomNumber" />
													&nbsp;
												</td>
										<c:if test="${i%2 == 0}">											
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dry" property="fee" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dry" property="studentNo" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dry" property="stuName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dry" property="gender" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="dry" property="birthday" />
													&nbsp;
												</td>
										</c:if>
										<c:if test="${i%2 != 0}">											
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dry" property="fee" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dry" property="studentNo" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dry" property="stuName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dry" property="gender" />
													&nbsp;
												</td>	
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="dry" property="birthday" />
													&nbsp;
												</td>									
										</c:if>
										</tr>
									</pg:item>
								</logic:iterate>
								<jsp:include page="./page.jsp" flush="true" />

					</tbody>
				</table>
			</td>
		</tr>
				<tr><td height="40" align="left" valign="middle">
					<jsp:include page="./pagenoexcel.jsp" flush="true" />				
				</td></tr>
											</pg:pager>
							<!-- page offset end -->
						</logic:present>
						<logic:present name="yxgraduates" scope="request">
  <tr> 
    <td height="40" align="left" valign="middle">
        <%
        int rowcount=0;
        if(request.getAttribute("dormitoryCount")!=null){
        	rowcount=((Integer)request.getAttribute("dormitoryCount")).intValue();
        %>       
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
        <%} %>
    </td>
  </tr>		
 	
		<tr>
			<td align="center" valign="bottom" height="10">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="bottom" height="10">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="bottom" height="10">
				&nbsp;
			</td>
		</tr>
 </logic:present>
	</table>


</body>

<script language="JavaScript">
	 	 <!-- location list -->
 
		var locationcount;
		locationcount = 0;
		locations = new Array(); 
	<%	
		ArrayList locationlist=(ArrayList)request.getAttribute("locationList");
		int l1 = 0;
		for(l1=0;l1<locationlist.size();l1++){
			HashMap map1 = (HashMap)locationlist.get(l1);
			String locationid = (String)map1.get("dictValue");
			String locationname = (String)map1.get("dictCaption");
			String area = (String)map1.get("area");
	%>
		locations[<%=l1%>]= new Array("<%=locationid%>","<%=locationname%>","<%=area%>"); 
	<%	
		}	
	%>

	locationcount=<%=locationlist.size()%> 
 
	function changeArea(area){
		document.all["location"].length=0;
		var areaId=area;
		var j1; 
		document.all["location"].options[document.all["location"].length]= new Option("-----------------------","");
			for (j1=0;j1 < locationcount; j1++) 
			{ 
				if (locations[j1][2] == areaId) 
				{ 
					document.all["location"].options[document.all["location"].length]= new Option(locations[j1][1],locations[j1][0]);
					if(locations[j1][0]==<%=request.getAttribute("location")%>){
						document.all["location"].options[document.all["location"].length-1].selected=true;
					}
				} 
			} 
	}

		 
	 	 <!-- dormitory list -->
 
		var dormcount;
		dormcount = 0;
		dormitorys = new Array(); 
	<%	
		ArrayList dromitorylist=(ArrayList)request.getAttribute("dormitoryList");
		int arrayTag = 0;
		for(arrayTag=0;arrayTag<dromitorylist.size();arrayTag++){
			HashMap map = (HashMap)dromitorylist.get(arrayTag);
			String dormitoryid = (String)map.get("dictValue");
			String dormtioryname = (String)map.get("dictCaption");
			String location = (String)map.get("location");
	%>
		dormitorys[<%=arrayTag%>]= new Array("<%=dormitoryid%>","<%=dormtioryname%>","<%=location%>"); 
	<%	
		}	
	%>

	dormcount=<%=dromitorylist.size()%> 
  
	function changeLocation(location){
		document.all["dorm"].length=0;
		var locationId=location;
		var j; 
		document.all["dorm"].options[document.all["dorm"].length]= new Option("-----------------------","");
			for (j=0;j < dormcount; j++) 
			{ 
				if (dormitorys[j][2] == locationId) 
				{ 
					document.all["dorm"].options[document.all["dorm"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
			} 
	} 
	 function ondelete(){ 
	 	if(document.all.deleteX!=null){
	 		if(document.all.deleteX.length==null){
	 			if(document.all.deleteX.checked==true){
	 				if(!confirm("是否确定要删除？")){
			 			return false;
			 		}
	 				return true;
	 			}else{	 
	 				alert("请先选择要删除的对象");			
	 				return false;
	 			}
	 		}	
			 for(i=0;i<document.all.deleteX.length;i++){
			 	if(document.all.deleteX[i].checked==true){
			 		if(!confirm("是否确定要删除？")){
			 		return false;
			 		}
			 		return true;
			 	}else{
			 		continue;
			 	}	 			
			 }	
			 	alert("请先选择要删除的对象");
		 		return false;
		 }else{
		 		alert("没有可删除的对象");
		 		return false;
		 }
	 } 
	 
	 function my_onload(){
	 	
	 	if(document.all.location.value!=""){	 	
	 		document.all.dorm.length=0;
			var j; 
			document.all.dorm.options[document.all.dorm.length]= new Option("-----------------------","");
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all.location.value) 
				{ 
					document.all.dorm.options[document.all.dorm.length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("mydormitory").value){
					document.all.dorm.options[document.all.dorm.length-1].selected=true;
				}
			} 
	 	}
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
		NotExport();
	 }
	 window.onload=my_onload;
	 
	 function DoExport(){
	 	document.all("export").value='export';
	 	document.forms[0].submit();
	 }
	 function NotExport(){
 
	 	document.all("export").value='';
	 }
function on_validate(){	

	var dormfee = document.all("dormfee").value;
	if(dormfee!=""&&isDigital(dormfee)==false){ 
		alert("住宿费应输入实数");
		document.all("dormfee").value="";
		return false;
	}else{
		return true;
	}	

}
function isDigital(str){
	var j=0;
	var ch="";
	//str=trim(str);
	//alert(333);
	if (str.length==0) return false;
  for (var i=0;i<str.length;i++){
  	ch=str.charAt(i);
    if (ch=="."){
    	j++;
    	if (j>1){
    		return false;
    	}
    }else if ((parseInt(ch)+"")=="NaN"){
    	return false;
    }
  }
  return true;
}	 
	 
	 function sortTable(selected){
	 	var sortIndex = selected;
	 	document.all.orderby.value=selected;
	 	if(document.all.sort.value=="0"){
	 		document.all.sort.value="1";
	 	}else if(document.all.sort.value=="1"){
	 		document.all.sort.value="2";
	 	}else{
	 		document.all.sort.value="0";
	 	}
//	 	document.forms[0].submit();
	 }
	
	 

setTimeout('DoInit()',30);
function DoInit(){
    var area = <%=request.getAttribute("area")%>;
    var location = <%=request.getAttribute("location")%>;
    if(area!=null&&area!=''){
	changeArea(area);
	}
	if(location!=null&&location!=''){
	changeLocation(location);
	}
}
	 uniteTable(document.all.maintable,4);//执行测试。




	//合并书院、班级单元格
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

