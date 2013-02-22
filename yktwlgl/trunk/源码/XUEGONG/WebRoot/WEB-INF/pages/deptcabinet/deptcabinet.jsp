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
		<html:form action="/gyf/deptCabinetAction.do?method=saveCabinetInfo" method="post">

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
												部门机柜维护
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
												<td width="15%" height="26" align="right" valign="middle" style="background-color: #D1DAE9;font-family:宋体;font-size: 12px;text-align: right;">
													<b>校区</b>
												</td>
												<td width="35%" align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;">
													<%if (request.getAttribute("isNew") != null
					&& request.getAttribute("isNew").equals("1")) {%>
													<html:select property="info_area" styleClass="select01" onchange="changeBd(this)">
														<html:option value="">请选择	</html:option>
														<html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
													<%} else {%>
													<html:hidden property="info_area" />
													<%=request.getAttribute("xqName")%>
													&nbsp;
													<%}%>
												</td>
												<td width="15%" align="right" valign="middle" style="background-color: #D1DAE9;font-family:宋体;font-size: 12px;text-align: right;">
													<b>楼宇</b>
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<%if (request.getAttribute("isNew") != null
					&& request.getAttribute("isNew").equals("1")) {%>
													<html:select property="info_building" styleClass="select01" onchange="changeRm(this)">
														<html:option value="">请选择	</html:option>
														<html:options collection="buildinglist" labelProperty="lymc" property="id" />
													</html:select>
													<%} else {%>
													<html:hidden property="info_building" />
													<%=request.getAttribute("bdName")%>
													&nbsp;
													<%}%>
												</td>
											</tr>
											<tr align="center" valign=center>												
													<%if (request.getAttribute("isNew") != null
					&& request.getAttribute("isNew").equals("1")) {%>
					                            <td align="right" valign="middle" style="background-color: #D1DAE9;font-family:宋体;font-size: 12px;text-align: right;">
													<font color="red" style="font-weight:normal">*</font>&nbsp;<b>机房/库房</b>
												</td>
												<td align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" nowrap="nowrap">
													<html:select property="info_room" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="roomlist" labelProperty="roommc" property="id" />
													</html:select>
													<%} else {%>
												<td align="right" valign="middle" style="background-color: #D1DAE9;font-family:宋体;font-size: 12px;text-align: right;">
													<b>机房/库房</b>
												</td>
												<td align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" nowrap="nowrap">
													<html:hidden property="info_room" />
													<%=request.getAttribute("rmName")%>
													&nbsp;
													<%}%>
												</td>
												<html:hidden property="cabinetInfo.id" />
												<td align="right" valign="middle" style="background-color: #D1DAE9;font-family:宋体;font-size: 12px;text-align: right;">
													<font color="red" style="font-weight:normal">*</font>&nbsp;<b>机柜编号</b>
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="cabinetInfo.cabinetmc" styleClass="input_box" maxlength="20" />
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
						<input type="hidden" name="search_room" value="<%=request.getParameter("search_room") %>">
						<input type="hidden" name="search_cabinetmc" value="<%=request.getParameter("search_cabinetmc") %>">
						<input type="hidden" name="search_cbstate" value="<%=request.getParameter("search_cbstate") %>">
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
<script>

    var datacount2=0;
    dataset2=new Array();
    
   <%
   int count2=0;
   String[][] resultset2=null;
   if(request.getAttribute("bmlist")!=null)
       resultset2=(String[][])request.getAttribute("bmlist");//读取楼宇、房间对应数据
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>","<%=resultset2[count2][3]%>");//产生javascript二维数组，对应房间id、房间名称、房间标识、楼宇id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>

<SCRIPT language=javascript>

setTimeout('init()',50);
function init(){

if(document.deptCabinetForm.elements["info_area"]!=null&&document.deptCabinetForm.elements["info_building"]!=null&&document.deptCabinetForm.elements["info_room"]!=null){
  var area=document.deptCabinetForm.elements["info_area"].value;
  var building=document.deptCabinetForm.elements["info_building"].value;
  
  if(area!='')
      changeBd(document.deptCabinetForm.elements["info_area"]);
  for(var j=0;j<document.deptCabinetForm.elements["info_building"].length;j++){
      if(document.deptCabinetForm.elements["info_building"][j].value==building)
	     document.deptCabinetForm.elements["info_building"][j].selected=true;
					
  }
  var room=document.deptCabinetForm.elements["info_room"].value;
  if(building!='')
      changeRm(document.deptCabinetForm.elements["info_building"]);
  for(var j=0;j<document.deptCabinetForm.elements["info_room"].length;j++){
      if(document.deptCabinetForm.elements["info_room"][j].value==room)
	     document.deptCabinetForm.elements["info_room"][j].selected=true;
					
  }  
  
}
  
  if(document.all.hmsg.value=='1')
       alert("添加成功！");
  else if(document.all.hmsg.value=='2')
       alert("修改成功！");
  else if(document.all.hmsg.value=='0')
       alert("保存失败！");
  else if(document.all.hmsg.value=='9')
       alert("数据库中已存在同名机柜！");
  
}  

function changeBd(sel){

   var id;        
   var i;        

if(sel!=null&&sel.options!=null){
   id=sel.options[sel.selectedIndex].value;
        
   document.deptCabinetForm.elements["info_building"].length=1; //清空原楼宇列表        
   
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.deptCabinetForm.elements["info_building"].options[document.deptCabinetForm.elements["info_building"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.deptCabinetForm.elements["info_building"].options[document.deptCabinetForm.elements["info_building"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
}  

}

function changeRm(sel){

   var id;        
   var i;  
   
if(sel!=null&&sel.options!=null){

   id=sel.options[sel.selectedIndex].value;
        
   document.deptCabinetForm.elements["info_room"].length=1; //清空原房间列表  
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.deptCabinetForm.elements["info_room"].options[document.deptCabinetForm.elements["info_room"].length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
    }else{       
       for (i=0;i < datacount2; i++)
      {
          document.deptCabinetForm.elements["info_room"].options[document.deptCabinetForm.elements["info_room"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   
}
}

function DoSave(){

   if(document.deptCabinetForm.elements["info_room"]!=null&&document.deptCabinetForm.elements["info_room"].value==''){
       alert("请选择机柜所属的房间！");
       return;
   }
   if(document.deptCabinetForm.elements["cabinetInfo.cabinetmc"].value==''){
       alert("请填写机柜编号！");
       return;
   
   }   
   
   deptCabinetForm.action="deptCabinetAction.do?method=saveCabinetInfo";
   deptCabinetForm.submit();
  
}

function DoBack(){ 
   
   if(document.all.addNum.value!='') {
       self.close();
       opener.deptCabinetForm.action="deptCabinetAction.do?method=search4List&formName="+document.all.formName.value+"&addNum="+document.all.addNum.value+"&isNew="+document.all.isNew.value+"&listNum="+document.all.listNum.value+"&ec_p="+document.all.ec_p.value+"&cabinetInfo.id="+document.deptCabinetForm.elements["cabinetInfo.id"].value;
       opener.deptCabinetForm.submit();
   }
   else{
       deptCabinetForm.action="deptCabinetAction.do?method=search4List";
       deptCabinetForm.submit();       
   }
       
}
</SCRIPT>
