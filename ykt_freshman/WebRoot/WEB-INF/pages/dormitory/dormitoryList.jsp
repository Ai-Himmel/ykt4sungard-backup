<%@ page pageEncoding="GBK"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.HashMap"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ include file="../tiles/include.jsp"%>
<script language="JavaScript">
function clearAll(){

	document.all("dormitory.location").value="";
	document.all("dormitory.dormitory").value="";
	document.all("dormitory.gender").value="";
	document.all("dormitory.roomNumber").value="";
}

function document.onkeydown(){

	var e=event.srcElement;
	if(event.keyCode==13){
	
		document.all("search").click();
		return false;
	}
}
</script>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="dormitorymanage" key="dormitoryResource.dormitoryResource" /></font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<html:form action="DormitoryAction.do?method=searchAll">
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

							<tbody>

								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">校区</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<html:select onchange="changeLocation(this.value)" styleClass="select01" property="dormitory.location">
											<html:option value="">-----------------------</html:option>
											<html:options collection="locationList" property="dictValue" labelProperty="dictCaption" />
										</html:select>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">楼号</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="dormitory.dormitory">
											<html:option value="">-----------------------</html:option>
										</html:select>
									</td>
								</tr>

								<tr align="center" valign="middle">

									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">入住性别</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="dormitory.gender">
											<html:option value="">-----------------------</html:option>
											<html:options collection="genderList" property="id.dictValue" labelProperty="dictCaption" />
										</html:select>
									</td>
									<td align="left" valign="middle" class="tableHeader2">
										宿舍号
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:text styleClass="input_box" property="dormitory.roomNumber" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
									</td>
								</tr>
							</tbody>
						</table>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<html:submit property="search" styleClass="button_nor">
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
					<html:form action="DormitoryAction.do?method=delete">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<tbody>
								<tr align="center" valign="middle">
									<td width="24" height="24" valign="middle" class="tableHeader2">
										<input type="checkbox" name="checkSwitch" onclick="selectIns();">
									</td>
									<td height="24" valign="middle" class="tableHeader">
										校区
									</td>
									<td valign="middle" class="tableHeader">
										楼号
									</td>
									<td valign="middle" class="tableHeader">
										宿舍号
									</td>
									<td valign="middle" class="tableHeader">
										入住性别
									</td>
									<td valign="middle" class="tableHeader">
										床位数
									</td>
									<td valign="middle" class="tableHeader">
										住宿费
									</td>
									<td valign="middle" class="tableHeader">
										宿舍电话
									</td>
								</tr>
								<logic:present name="dorms" scope="request">
									<%int dormsCount = ((Integer) request.getAttribute("dormsCount"))
					.intValue();%>
									<!--page offset start -->
									<pg:pager url="./DormitoryAction.do" items="<%=dormsCount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
										<%-- keep track of preference --%>
										<pg:param name="method" />
										<pg:param name="dormitory.roomNumber" />
										<pg:param name="dormitory.location" />
										<pg:param name="dormitory.dormitory" />
										<pg:param name="dormitory.gender" />
										<pg:param name="page" />
										<pg:param name="orderby" />
										<pg:param name="sort" />

										<%-- save pager offset during form changes --%>
										<input type="hidden" name="pager.offset" value="<%= offset %>">
										<logic:iterate name="dorms" id="dorm" indexId="i">
											<pg:item>
												<c:if test="${i%2 == 0}">
													<tr align="center" valign="middle">
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<input type="checkbox" name="deleteX" value="<bean:write name="dorm" property="dormitorymodel.dormitoryId"/>" />
														</td>
														<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="dorm" property="location" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="dorm" property="dormitory" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<html:link action="DormitoryAction.do?method=revise" paramId="dormitoryId" paramName="dorm" paramProperty="dormitorymodel.dormitoryId">
																<bean:write name="dorm" property="dormitorymodel.roomNumber" />&nbsp;
															</html:link>
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="dorm" property="gender" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="dorm" property="dormitorymodel.accomodation" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="dorm" property="dormitorymodel.fee" />
															&nbsp;
														</td>
														<td align="center" valign="middle" bgcolor="#FFFFFF">
															<bean:write name="dorm" property="dormitorymodel.telphone" />
															&nbsp;
														</td>
													</tr>
												</c:if>
												<c:if test="${i%2 != 0}">
													<tr align="center" valign="middle" bgcolor="#F6F4F5">
														<td align="center" valign="middle">
															<input type="checkbox" name="dormitoryId" value="<bean:write name="dorm" property="dormitorymodel.dormitoryId"/>" />
														</td>
														<td height="24" align="center" valign="middle">
															<bean:write name="dorm" property="location" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="dorm" property="dormitory" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<html:link action="DormitoryAction.do?method=revise" paramId="dormitoryId" paramName="dorm" paramProperty="dormitorymodel.dormitoryId">
																<bean:write name="dorm" property="dormitorymodel.roomNumber" />&nbsp;
															</html:link>
														</td>
														<td align="center" valign="middle">
															<bean:write name="dorm" property="gender" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="dorm" property="dormitorymodel.accomodation" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="dorm" property="dormitorymodel.fee" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<bean:write name="dorm" property="dormitorymodel.telphone" />
															&nbsp;
														</td>
													</tr>
												</c:if>
											</pg:item>
										</logic:iterate>
										<jsp:include page="../security/page.jsp" flush="true" />
									</pg:pager>
									<!-- page offset end -->
								</logic:present>
							</tbody>
						</table>
  <tr> 
    <td height="40" align="left" valign="middle">
        <%
        int rowcount=0;
        if(request.getAttribute("dormsCount")!=null){
        	rowcount=((Integer)request.getAttribute("dormsCount")).intValue();
        %>       
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
        <%} %>
    </td>
  </tr>							
						
						<tr>
							<td height="30" align="right" valign="middle">
								<html:submit property="add" styleClass="button_nor" onclick="document.forms[1].action='DormitoryAction.do?method=init4Add'">
									<bean:message key="button.add" />
								</html:submit>
								<html:submit property="delete" styleClass="button_nor" onclick="javascript:return ondelete();">
									<bean:message key="button.delete" />
								</html:submit>
							</td>
						</tr>
					</html:form>
				</td>
			</tr>
		</table>
	</body>
</center>


<script language="JavaScript">
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
			String location = (String)map.get("dictParent");
			
			//Dictionary building = (Dictionary)dromitorylist.get(l);
			//String dormitoryid = building.getId().getDictValue();
			//String dormtioryname = building.getDictCaption();
			//String location = building.getDictParent();
	%>
		dormitorys[<%=l%>]= new Array("<%=dormitoryid%>","<%=dormtioryname%>","<%=location%>"); 
	<%	
		}	
	%>

	dormcount=<%=dromitorylist.size()%> 
 
	function changeLocation(location){
		document.all["dormitory.dormitory"].length=0;
		var locationId=location;
		var j; 
		document.all["dormitory.dormitory"].options[document.all["dormitory.dormitory"].length]= new Option("-----------------------","");
			for (j=0;j < dormcount; j++) 
			{ 
				if (dormitorys[j][2] == locationId) 
				{ 
					document.all["dormitory.dormitory"].options[document.all["dormitory.dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
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
	 	
	 	if(document.all("dormitory.location").value!=""){	 	
	 		document.all["dormitory.dormitory"].length=0;
			var j; 
			document.all["dormitory.dormitory"].options[document.all["dormitory.dormitory"].length]= new Option("--------------------","");
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all("dormitory.location").value) 
				{ 
					document.all["dormitory.dormitory"].options[document.all["dormitory.dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("mydormitory").value){
					document.all("dormitory.dormitory").options[document.all("dormitory.dormitory").length-1].selected=true;
				}
			} 
	 	}
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	 }
	 
	 window.onload=my_onload;	

</script>
