<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
	<head>
		<title>上海复旦大学物料库存及仓储管理系统</title>

		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/deptRoomAction.do?method=saveRoomInfo" method="post">

			<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td align="left" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td height="25" align="left" valign="top">
									<table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">
												部门机房/库房维护
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="center" valign="top">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<input type="hidden" name="listNum" value="all">
										<tbody>
											<input type="hidden" name="formName" value="<%=request.getAttribute("formName")==null?"":request.getAttribute("formName")%>">
											<input type="hidden" name="addNum" value="<%=request.getAttribute("addNum")==null?"":request.getAttribute("addNum")%>">
											<input type="hidden" name="isNew" value="<%=request.getAttribute("isNew")==null?"0":request.getAttribute("isNew")%>">
											<input type="hidden" name="noNew" value="<%=request.getAttribute("noNew")==null?"0":request.getAttribute("noNew")%>">
											<tr align="center" valign=center>
												<td width="20%" align="right" valign="middle" class="tableHeader2">
													校区
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:select property="info_area" styleClass="select01" onchange="changeBd(this)">
														<html:option value="">请选择	</html:option>
														<html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader2">
													<font color="red" style="font-weight:normal">*</font>&nbsp;楼宇
												</td>
												<td width="30%" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" nowrap="nowrap">
													<html:select property="info_building" styleClass="select01" onchange="changeBuilding(this)">
														<html:option value="">请选择	</html:option>
														<html:options collection="buildinglist" labelProperty="lymc" property="id" />
													</html:select>
												</td>
											</tr>
											<tr align="center" valign=center>
												<html:hidden property="roomInfo.id" />
												<td width="20%" align="left" valign="middle" class="tableHeader2">
													<font color="red" style="font-weight:normal">*</font>&nbsp;房间名称
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:text property="roomInfo.roommc" styleClass="input_box" maxlength="20" />
												</td>
												<td width="20%" align="right" valign="middle" class="tableHeader2">
													<font color="red" style="font-weight:normal">*</font>&nbsp;房间标识
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:select property="roomInfo.roomflag" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:option value="1">库房</html:option>
														<html:option value="2">机房</html:option>
														<html:option value="3">普通房间</html:option>
													</html:select>
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">

									<input name="Submit" type="button" class="button_nor" value="保 存" onclick="DoSave()">
									&nbsp;
									<input name="Submit2" type="button" class="button_nor" value="返 回" onclick="DoBack()">
								</td>

							</tr>
						</table>
						<logic:present name="msg" scope="request">
							<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
						</logic:present>
						<logic:notPresent name="msg" scope="request">
							<input name="hmsg" type="hidden" value="">
						</logic:notPresent>
						<input type="hidden" name="ec_p" value="<%=request.getAttribute("isNew")!=null&&request.getAttribute("isNew").equals("1")?"1":request.getParameter("ec_p") %>">
						<input type="hidden" name="ec_i" value="<%=request.getParameter("ec_i") %>">
						<input type="hidden" name="ec_crd" value="<%=request.getParameter("ec_crd") %>">

						<input type="hidden" name="search_area" value="<%=request.getParameter("search_area") %>">
						<input type="hidden" name="search_building" value="<%=request.getParameter("search_building") %>">
						<input type="hidden" name="search_roommc" value="<%=request.getParameter("search_roommc") %>">
						<input type="hidden" name="search_roomstate" value="<%=request.getParameter("search_roomstate") %>">
						</html:form>
	</body>
</html>

<script>

    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("ablist")!=null)
       resultset=(String[][])request.getAttribute("ablist");//读取校区、楼宇对应数据
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//产生javascript二维数组，对应楼宇id、楼宇名称、校区id
     <%
     }
   }
   %>
   datacount=<%=count%>;

</script>

<SCRIPT language=javascript>

setTimeout('init()',50);
function init(){

if(document.deptRoomForm.elements["info_area"]!=null&&document.deptRoomForm.elements["info_building"]!=null){
  var area=document.deptRoomForm.elements["info_area"].value;
  var building=document.deptRoomForm.elements["info_building"].value;
  
  if(area!='')
      changeBd(document.deptRoomForm.elements["info_area"]);
  for(var j=0;j<document.deptRoomForm.elements["info_building"].length;j++){
      if(document.deptRoomForm.elements["info_building"][j].value==building)
	     document.deptRoomForm.elements["info_building"][j].selected=true;
					
  }
  
}

  if(document.all.hmsg.value=='1')
       alert("添加成功！");
  else if(document.all.hmsg.value=='2')
       alert("修改成功！");
  else if(document.all.hmsg.value=='0')
       alert("保存失败！");
  else if(document.all.hmsg.value=='9')
       alert("数据库中已存在同名房间！");
  
}  

function changeBd(sel){

   var id;        
   var i; 
   
if(sel!=null&&sel.options!=null){

   id=sel.options[sel.selectedIndex].value;
        
   document.deptRoomForm.elements["info_building"].length=1; //清空原楼宇列表        
   
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.deptRoomForm.elements["info_building"].options[document.deptRoomForm.elements["info_building"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.deptRoomForm.elements["info_building"].options[document.deptRoomForm.elements["info_building"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
}  

}

function changeBuilding(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][0] == id)
          {                
             document.deptRoomForm.elements["info_area"].value=dataset[i][2];              
             
          }
      }
    
}

function DoSave(){

   if(document.deptRoomForm.elements["info_building"]!=null&&document.deptRoomForm.elements["info_building"].value==''){
       alert("请选择房间名称所属的楼宇！");
       return;
   }
   if(document.deptRoomForm.elements["roomInfo.roommc"].value==''){
       alert("请填写房间名称！");
       return;
   
   }
   if(document.deptRoomForm.elements["roomInfo.roomflag"].value==''){
       alert("请选择房间标识！");
       return;
   
   }
   
   deptRoomForm.action="deptRoomAction.do?method=saveRoomInfo";
   deptRoomForm.submit();
  
}

function DoBack(){ 
   
   if(document.all.addNum.value!='') {
       self.close();
       opener.deptRoomForm.action="deptRoomAction.do?method=search4List&formName="+document.all.formName.value+"&addNum="+document.all.addNum.value+"&isNew="+document.all.isNew.value+"&listNum="+document.all.listNum.value+"&ec_p="+document.all.ec_p.value+"&roomInfo.id="+document.deptRoomForm.elements["roomInfo.id"].value;
       opener.deptRoomForm.submit();
   }
   else{
       deptRoomForm.action="deptRoomAction.do?method=search4List";
       deptRoomForm.submit();       
   }
       
}
</SCRIPT>
