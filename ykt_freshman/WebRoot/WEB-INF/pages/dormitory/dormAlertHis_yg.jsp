<%@ page pageEncoding="GBK"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.HashMap"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ include file="../tiles/include.jsp"%>

<SCRIPT language=javascript>
	function clearAll(){
		document.all("area").value="";	
		document.all("location").value="";
		document.all("dormitory").value="";
		document.all("unit").value="";
		document.all("roomNumber").value="";
		document.all("stuNo").value="";
		document.all("startDate").value="";
		document.all("endDate").value="";
	}

	function on_validate(){
	if(document.all("startDate").value == '' && document.all("endDate").value != ''){
		alert('请选择起始日期');
		return false;
		}
	else if(document.all("startDate").value != '' && document.all("endDate").value == ''){
		alert('请选择结束日期');
		return false;
		}
	 	var startDate = document.all("startDate").value;
	 	var endDate = document.all("endDate").value;
	 	if(startDate!=""&&endDate!=""&&startDate>endDate){
	 		alert("开始时间应该小于结束时间");
	 		return false;
	 	}		
	else{
		return true;
		}
	}
	function on_FD(){
		document.all("sd").click();
	}
	function on_TD(){
		document.all("ed").click();
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
</SCRIPT>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr>
		<td height="30" align="center" valign="middle" class="tdborder02">
			<strong><font class="medium"><bean:message bundle="dormitorymanage" key="dormitoryAlter.AlterHisSearch" /></font></strong>
		</td>
	</tr>
	<tr>
		<td align="right" valign="middle">
			<html:form method="post" action="DormitoryAdjustAction.do?method=alertHisSearch&getrole=3" onsubmit="javascript:return on_validate();">
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tr>
						<td>
							<%if (request.getAttribute("mydormitory") != null) {
				String mydormitory = request.getAttribute("mydormitory")
						.toString();

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
					<tbody>					
						<tr align="center" valign="middle">
							<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								校区
							</td>
							<td align="left" valign="middle" class="tableHeader3">
								<html:select styleClass="select01" property="area" onchange="changeArea(this.value)">
									<html:option value="">-----------------------</html:option>
									<html:options collection="areaList" labelProperty="dictCaption" property="dictValue" />
								</html:select>
							</td>						
							<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								区域
							</td>
							<td align="left" valign="middle" class="tableHeader3">
								<html:select styleClass="select01" property="location" onchange="changeLocation(this.value)">
									<html:option value="">-----------------------</html:option>
									<html:options collection="locationList" labelProperty="dictCaption" property="dictValue" />								
								</html:select>
							</td>
						</tr>
						<tr align="center" valign="middle">
							<td align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								楼号
							</td>
							<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
								<html:select styleClass="select01" property="dormitory" onchange="changedormitory(this.value)">
									<html:option value="">-----------------------</html:option>
									<html:options collection="dormitoryList" labelProperty="dictCaption" property="dictValue" />																	
								</html:select>
							</td>

											<td height="24" valign="middle" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
												单元
											</td>
											<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
												<html:text property="unit" styleClass="input_box" style="width:120" maxlength="4"/>
											</td>

					
						</tr>				
						<tr align="center" valign="middle">
							<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								宿舍号
							</td>
							<td align="left" valign="middle" class="tableHeader3">
								<html:text property="roomNumber" styleClass="input_box" maxlength="4"/>
							</td>
							<td align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								学号
							</td>
							<td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3">
								<html:text property="stuNo" styleClass="input_box" maxlength="20" />
							</td>
						</tr>		
						<tr align="center" valign=middle>
							<td width="15%" height="28" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								<bean:message bundle="dormitorymanage" key="dormitoryAlter.startTime" />
							</td>
							<td width="35%" align="left" valign="middle" class="tableHeader3">
								<table width="100%" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td width="130">
											<html:text property="startDate" styleClass="input_box" maxlength="16" readonly="true" onclick="on_FD();"/>
										</td>
										<td>
											<img name="sd" class="img_nor" width="21" height="21" border="0" onclick="setday(this,document.all.startDate)">
										</td>
									</tr>
								</table>
							</td>
							<td width="15%" height="28" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								<bean:message bundle="dormitorymanage" key="dormitoryAlter.endTime" />
							</td>
							<td width="35%" align="left" valign="middle" class="tableHeader3">
								<table width="100%" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td width="130">
											<html:text property="endDate" styleClass="input_box" maxlength="50" readonly="true" onclick="on_TD();"/>
										</td>
										<td>
											<img name="ed" class="img_nor" width="21" height="21" border="0" onclick="setday(this,document.all.endDate)">
										</td>
									</tr>
								</table>
							</td>
						</tr>
						
					</tbody>
				</table>
				<tr>
					<td height="40" align="right" valign="middle" class="tdborder02" onclick="javascript:NotExport();">
						<html:submit property="search" styleClass="button_nor">
							<bean:message key="button.query" />
						</html:submit>
						<html:button property="reset" styleClass="button_nor" onclick="clearAll();">
							<bean:message key="button.reset" />
						</html:button>
					</td>
				</tr>
<input name="horderby" type="hidden" value="">			
<logic:present name="order" scope="request">
  <input name="horder" type="hidden" value="<bean:write name="order" />"> 
  </logic:present>
  <logic:notPresent name="order" scope="request">
  <input name="horder" type="hidden" value="a"> 
</logic:notPresent>
			</html:form>
		</td>
	</tr>

	<tr>
		<td height="10" align="center" valign="middle" class="medium"></td>
	</tr>

	<tr>
		<td height="40" align="center" valign="top">
			<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
				<tbody>
					<tr align="center" valign="middle">
						<td height="24" valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')"><bean:message bundle="dormitorymanage" key="dormitoryAlter.stuNo" /></a>
						</td>
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('stuName')"><bean:message bundle="dormitorymanage" key="dormitoryAlter.stuName" /></a>
						</td>
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('areaO')">原校区</a>
						</td>						
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('locationO')">原区域</a>
						</td>
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('dormitoryO')"><bean:message bundle="dormitorymanage" key="dormitoryAlter.dormitoryO" /></a>
						</td>
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('unitO')">原单元号</a>
						</td>
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('roomNumberO')"><bean:message bundle="dormitorymanage" key="dormitoryAlter.roomNumberO" /></a>
						</td>						
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('areaN')">新校区</a>
						</td>
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('locationN')">新区域</a>
						</td>
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('dormitoryN')"><bean:message bundle="dormitorymanage" key="dormitoryAlter.dormitoryN" /></a>
						</td>
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('unitN')">新单元号</a>
						</td>
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('roomNumberN')"><bean:message bundle="dormitorymanage" key="dormitoryAlter.roomNumberN" /></a>
						</td>
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('operator')"><bean:message bundle="dormitorymanage" key="dormitoryAlter.operator" /></a>
						</td>
						<td valign="middle" class="tableHeader">
							<a style="font-size:14px;color: black" href="javascript:DoSort('operatetime')"><bean:message bundle="dormitorymanage" key="dormitoryAlter.operatetime" /></a>
						</td>
					</tr>
					<logic:present name="alertHis" scope="request">
						<%int itemNo = ((Integer) request.getAttribute("hisCount"))
					.intValue();%>
						<pg:pager url="DormitoryAdjustAction.do" items="<%=itemNo%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
							<%-- keep track of preference --%>
							<pg:param name="method" />
							<pg:param name="dormitory" />
							<pg:param name="area" />							
							<pg:param name="location" />
							<pg:param name="unit" />
							<pg:param name="roomNumber" />
							<pg:param name="stuNo" />
							<pg:param name="startDate" />
							<pg:param name="endDate" />
							<pg:param name="page" />
							<pg:param name="orderby" />
							<pg:param name="sort" />
							<pg:param name="horderby" />
							<pg:param name="horder" />
							<pg:param name="getrole" />

							<%-- save pager offset during form changes --%>
							<input type="hidden" name="pager.offset" value="<%= offset %>">
							<logic:iterate name="alertHis" id="alertHistory" indexId="i">
								<pg:item>
									<c:if test="${i%2 == 0}">
										<tr align="center" valign="middle">
											<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="alertHistory" property="studentNo" />
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="alertHistory" property="stuName" />
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="alertHistory" property="oarea" />
												&nbsp;
											</td>											
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="alertHistory" property="olocation" />
												&nbsp;
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="alertHistory" property="odorm" />
												&nbsp;
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="alertHistory" property="ounit" />
												&nbsp;
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="alertHistory" property="oroom" />
												&nbsp;
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<font color="#990000"><bean:write name="alertHistory" property="narea" />&nbsp;</font>
											</td>											
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<font color="#990000"><bean:write name="alertHistory" property="nlocation" />&nbsp;</font>
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<font color="#990000"><bean:write name="alertHistory" property="ndorm" />&nbsp;</font>
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<font color="#990000"><bean:write name="alertHistory" property="nunit" />&nbsp;</font>
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<font color="#990000"><bean:write name="alertHistory" property="nroom" />&nbsp;</font>
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="alertHistory" property="opId" />
												&nbsp;
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="alertHistory" property="changeTime" />
												&nbsp;
											</td>
										</tr>
									</c:if>
									<c:if test="${i%2 != 0}">
										<tr align="center" valign="middle" bgcolor="#F6F4F5">
											<td height="24" align="center" valign="middle">
												<bean:write name="alertHistory" property="studentNo" />
											</td>
											<td align="center" valign="middle">
												<bean:write name="alertHistory" property="stuName" />
											</td>
											<td align="center" valign="middle">
												<bean:write name="alertHistory" property="oarea" />
												&nbsp;
											</td>											
											<td align="center" valign="middle">
												<bean:write name="alertHistory" property="olocation" />
												&nbsp;
											</td>
											<td align="center" valign="middle">
												<bean:write name="alertHistory" property="odorm" />
												&nbsp;
											</td>
											<td align="center" valign="middle">
												<bean:write name="alertHistory" property="ounit" />
												&nbsp;
											</td>
											<td align="center" valign="middle">
												<bean:write name="alertHistory" property="oroom" />
												&nbsp;
											</td>
											<td align="center" valign="middle">
												<font color="#990000"><bean:write name="alertHistory" property="narea" />&nbsp;</font>
											</td>											
											<td align="center" valign="middle">
												<font color="#990000"><bean:write name="alertHistory" property="nlocation" />&nbsp;</font>
											</td>
											<td align="center" valign="middle">
												<font color="#990000"><bean:write name="alertHistory" property="ndorm" />&nbsp;</font>
											</td>
											<td align="center" valign="middle" >
												<font color="#990000"><bean:write name="alertHistory" property="nunit" />&nbsp;</font>
											</td>
											<td align="center" valign="middle">
												<font color="#990000"><bean:write name="alertHistory" property="nroom" />&nbsp;</font>
											</td>
											<td align="center" valign="middle">
												<bean:write name="alertHistory" property="opId" />
												&nbsp;
											</td>
											<td align="center" valign="middle">
												<bean:write name="alertHistory" property="changeTime" />&nbsp;
											</td>
										</tr>
									</c:if>
								</pg:item>
							</logic:iterate>
							<jsp:include page="./page.jsp" flush="true" />

						<!-- page offset end -->
				</tbody>
			</table>
	
<table width="100%">	
  <tr> 
    <td height="24" align="left" valign="middle">
        <jsp:include page="./pagenoexcel.jsp" flush="true" />
    </td>
  </tr>						
</table>  
						</pg:pager>
									</logic:present>
<table width="100%">						
  <tr> 
    <td height="40" align="left" valign="middle">
        <%
        int rowcount=0;
        if(request.getAttribute("hisCount")!=null){
        	rowcount=((Integer)request.getAttribute("hisCount")).intValue();
        %>       
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
        <%} %>
    </td>
  </tr>	
</table>
			<jsp:include page="./dateSelect.jsp" flush="true" />
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
		int l = 0;
		for(l=0;l<dromitorylist.size();l++){
			HashMap map = (HashMap)dromitorylist.get(l);
			String dormitoryid = (String)map.get("dictValue");
			String dormtioryname = (String)map.get("dictCaption");
			String location = (String)map.get("location");
	%>
		dormitorys[<%=l%>]= new Array("<%=dormitoryid%>","<%=dormtioryname%>","<%=location%>"); 
	<%	
		}	
	%>

	dormcount=<%=dromitorylist.size()%> 
 
 
	function changeLocation(location){
		document.all["dormitory"].length=0;
		var locationId=location;
		var j; 
		document.all["dormitory"].options[document.all["dormitory"].length]= new Option("-----------------------","");
			for (j=0;j < dormcount; j++) 
			{ 
				if (dormitorys[j][2] == locationId) 
				{ 
					document.all["dormitory"].options[document.all["dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
			} 
	}
	 
	function DoExport(){
	 	document.all("export").value='export';
	 	document.forms[0].submit();
	 }
	 function NotExport(){

	 	document.all("export").value='';
	 }
	 
	 
	 function my_onload(){
	 	
	 	if(document.all("location").value!=""){	 	
	 		document.all["dormitory"].length=0;
			var j; 
			document.all["dormitory"].options[document.all["dormitory"].length]= new Option("-----------------------","");
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all("location").value) 
				{ 
					document.all["dormitory"].options[document.all["dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("mydormitory").value){
					document.all("dormitory").options[document.all("dormitory").length-1].selected=true;
				}
			} 
	 	}
	 	NotExport();
	 }
	 
	 window.onload=my_onload;	 
	 
function DoSort(col){

  document.all.horderby.value=col;  
  if(document.all.horder.value=='a')
      document.all.horder.value='d';
  else if(document.all.horder.value=='d')
      document.all.horder.value='a';
      
  document.adjustForm.action="DormitoryAdjustAction.do?method=alertHisSearch&getrole=3";
  document.adjustForm.submit();
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
</script>