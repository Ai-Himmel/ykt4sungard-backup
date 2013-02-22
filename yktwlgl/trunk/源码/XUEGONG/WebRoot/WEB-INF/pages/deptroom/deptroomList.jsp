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
		<%String jaddNum = request.getAttribute("addNum") == null ? ""
					: (String) request.getAttribute("addNum");
%>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/deptRoomAction.do?method=search4List" method="post">

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
												部门机房/库房设置
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="center" valign="top">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<input type="hidden" name="formName" value="<%=request.getAttribute("formName")==null?"":request.getAttribute("formName")%>">
										<tbody>
											<input type="hidden" name="addNum" value="<%=request.getAttribute("addNum")==null?"":request.getAttribute("addNum")%>">
											<input type="hidden" name="updateid" value="">
											<input type="hidden" name="noNew" value="<%=request.getAttribute("noNew")==null?"0":request.getAttribute("noNew")%>">
											<tr align="center" valign=center>
												<td width="20%" align="right" valign="middle" class="tableHeader2">
													校区
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:select property="search_area" styleClass="select01" onchange="changeBd(this)">
														<html:option value="">请选择	</html:option>
														<html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader2">
													楼宇
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:select property="search_building" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="buildinglist" labelProperty="lymc" property="id" />
													</html:select>
												</td>
											</tr>
											<tr align="center" valign=center>
												<td width="20%" align="left" valign="middle" class="tableHeader2">
													房间名称
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_roommc" styleClass="input_box" maxlength="100" />
												</td>
												<td width="20%" align="right" valign="middle" class="tableHeader2">
													状态
												</td>
												<td width="30%" align="left" valign="middle" class="tableHeader3">
													<html:select property="search_roomstate" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="mcztlist" labelProperty="ztName" property="ztCode" />
													</html:select>
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">

									<input name="Submit" type="button" class="button_nor" value="查 询" onclick="DoFind()">
									&nbsp;
									<input name="Submit2" type="button" class="button_nor" value="重 置" onclick="DoClear()">
								</td>

							</tr>
							<logic:present name="msg" scope="request">
								<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
							</logic:present>
							<logic:notPresent name="msg" scope="request">
								<input name="hmsg" type="hidden" value="">
							</logic:notPresent>
							<logic:present name="cannotUse" scope="request">
								<input name="hcannotUse" type="hidden" value="<bean:write name="cannotUse" />">
							</logic:present>
							<logic:notPresent name="cannotUse" scope="request">
								<input name="hcannotUse" type="hidden" value="">
							</logic:notPresent>
							<logic:present name="repeatSet" scope="request">
								<input name="hrepeatSet" type="hidden" value="<bean:write name="repeatSet" />">
							</logic:present>
							<logic:notPresent name="repeatSet" scope="request">
								<input name="hrepeatSet" type="hidden" value="">
							</logic:notPresent>
							<input type="hidden" name="ec_p" value="<%=request.getParameter("ec_p")==null?"1":request.getParameter("ec_p")%>">
							<input type="hidden" name="ec_i" value="<%=request.getParameter("ec_i")==null?"":request.getParameter("ec_i")%>">
							<input type="hidden" name="ec_crd" value="<%=request.getParameter("ec_crd")==null?"":request.getParameter("ec_crd")%>">
							</html:form>

							<tr>
								<td height="35" align="center" valign="middle" class="mediumblack">
									部门中已设置的机房/库房列表
								</td>
							</tr>
							<jodd:form bean="request">
								<tr>
									<td height="20" align="center" valign="middle">
										<ec:table items="roomlist" var="room" autoIncludeParameters="false" rowsDisplayed="10" action="deptRoomAction.do?method=search4List">

											<ec:exportXls fileName="roomList.xls" tooltip="导出 Excel" />
											<ec:parameter name="search_area" />
											<ec:parameter name="search_building" />
											<ec:parameter name="search_roommc" />
											<ec:parameter name="search_roomstate" />
											<ec:parameter name="formName" />
											<ec:parameter name="addNum" />
											<ec:row>
												<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" headerStyle="text-align:center" style="text-align: left">
													<input type="checkbox" name="cbgroup" value="${room.idmc}" style="border:0px" />
												</ec:column>
												<ec:column property="roommc" title="房间名称" headerStyle="text-align:center" style="text-align: left" width="80">
													<c:choose>
														<c:when test="${room.state=='02'}">
															<font color="#A8A8A8">${room.roommc}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${room.state=='00'}">
															<font color="#FF9999">${room.roommc}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="lymc" title="所属楼宇" headerStyle="text-align:center" style="text-align: left" width="150">
													<c:choose>
														<c:when test="${room.state=='02'}">
															<font color="#A8A8A8">${room.lymc}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${room.state=='00'}">
															<font color="#FF9999">${room.lymc}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="areaName" title="所属校区" headerStyle="text-align:center" style="text-align: left" width="150">
													<c:choose>
														<c:when test="${room.state=='02'}">
															<font color="#A8A8A8">${room.areaName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${room.state=='00'}">
															<font color="#FF9999">${room.areaName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="roomflagName" title="房间标识" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${room.state=='02'}">
															<font color="#A8A8A8">${room.roomflagName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${room.state=='00'}">
															<font color="#FF9999">${room.roomflagName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="stateName" title="状态" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${room.state=='02'}">
															<font color="#A8A8A8">${room.stateName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${room.state=='00'}">
															<font color="#FF9999">${room.stateName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="updatorName" title="更新人" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${room.state=='02'}">
															<font color="#A8A8A8">${room.updatorName}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${room.state=='00'}">
															<font color="#FF9999">${room.updatorName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="updateTime" title="更新日期" headerStyle="text-align:center" style="text-align: left" width="100">
													<c:choose>
														<c:when test="${room.state=='02'}">
															<font color="#A8A8A8">${room.updateTime}</font>&nbsp;
					</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${room.state=='00'}">
															<font color="#FF9999">${room.updateTime}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
											</ec:row>
										</ec:table>
									</td>
								</tr>
								<%if (((java.util.ArrayList) request.getAttribute("roomlist")).size() > 0) {%>
								<tr>
									<td height="40" align="left" valign="middle">
										<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
											<tbody>
												<tr align="center" valign=center>
													<td height="40" align="left" valign="middle">
														<input name="selectall" type="button" class="button_nor" value="全 选" onClick="DoSelectall()">
														<input name="notselectall" type="button" class="button_nor" value="全不选" onClick="DoNotselectall()">
														<input name="reverseselect" type="button" class="button_nor" value="反 选" onClick="DoReverseselect()">
													</td>
													<td height="40" align="right" valign="middle">
														<%if (request.getAttribute("addNum") == null
						|| request.getAttribute("addNum").equals("")) {%>
														<input name="bupdate" type="button" class="button_nor" value="修 改" onClick="DoUpdate()">
														<input name="bnotuse" type="button" class="button_nor" value="废弃/不通过" onClick="DoUse('02')">
														<input name="buse" type="button" class="button_nor" value="使用/通过" onClick="DoUse('01')">
														<%if (request.getAttribute("noNew") == null
							|| request.getAttribute("noNew").equals("")
							|| request.getAttribute("noNew").equals("0")) {%>
														<input name="Submit4" type="button" class="button_nor" value="新 增" onClick="DoAdd()">
														<%}%>
														<%} else {%>
														<input name="selectOK" type="button" class="button_nor" value="确 定" onClick="addRoom()">
														<input name="Submit4" type="button" class="button_nor" value="新 增" onClick="DoAdd()">														
														<%}%>
													</td>
												</tr>
											</tbody>
										</table>
									</td>
								</tr>
								<%} else {%>
								<%if (request.getAttribute("noNew") == null
						|| request.getAttribute("noNew").equals("")
						|| request.getAttribute("noNew").equals("0")) {%>
								<tr>
									<td height="40" align="right" valign="middle">
										<input name="Submit4" type="button" class="button_nor" value="新 增" onClick="DoAdd()">
									</td>
								</tr>
								<%}%>
								<%}%>
							</jodd:form>
						</table>
					</td>
				</tr>
			</table>
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
  var area=document.deptRoomForm.elements["search_area"].value;
  var building=document.deptRoomForm.elements["search_building"].value;
  
  if(area!='')
      changeBd(document.deptRoomForm.elements["search_area"]);
  for(var j=0;j<document.deptRoomForm.elements["search_building"].length;j++){
      if(document.deptRoomForm.elements["search_building"][j].value==building)
	     document.deptRoomForm.elements["search_building"][j].selected=true;
					
  }
 
  if(document.deptRoomForm.formName.value!=''){
      if(document.all.selectOK!=null)
          document.all.selectOK.style.display='';//显示确定按钮      
  }
  else{
      if(document.all.selectOK!=null)
          document.all.selectOK.style.display='none';//不显示确定按钮
  }
  
  document.forms.ec.search_area.value=area;
  document.forms.ec.search_building.value=building;
  
  if(document.deptRoomForm.hmsg.value=='dok')
       alert("设置成功！");
  else if(document.deptRoomForm.hmsg.value=='dfail')
       alert("设置失败！");
       
  if(document.deptRoomForm.hcannotUse.value!='')
       alert(document.deptRoomForm.hcannotUse.value+" 楼宇为废弃，不能使用！");
  if(document.deptRoomForm.hrepeatSet.value!='')
       alert(document.deptRoomForm.hrepeatSet.value+" 重复设置！");
       
}  

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.deptRoomForm.elements["search_building"].length=1; //清空原楼宇列表        
   
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.deptRoomForm.elements["search_building"].options[document.deptRoomForm.elements["search_building"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.deptRoomForm.elements["search_building"].options[document.deptRoomForm.elements["search_building"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   

}

function addRoom(){   
   
   var sflag=0;
   
   if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag==0){
              alert("请选择房间名称！");
              return;
          }
          if(sflag>1){
              alert("只能选择一个房间名称！");
              return;
          }           
   }
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择房间名称！");
              return;        
        }
   }   
   
   var rmid="";
   var rmmc="";
   if(document.all.cbgroup.length>1){
       for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   var idmc=document.all.cbgroup[i].value;
                   var pos=idmc.indexOf('_');
                   if(pos!=-1){
                        rmid=idmc.substring(0,pos);
                        rmmc=idmc.substring(pos+1,idmc.length); 
                   }                                                  
              }
       }
   
   }
   else{
        if(document.all.cbgroup.checked){
             var idmc=document.all.cbgroup.value;
                   var pos=idmc.indexOf('_');
                   if(pos!=-1){
                        rmid=idmc.substring(0,pos);
                        rmmc=idmc.substring(pos+1,idmc.length); 
                   }              
        }
   
   }     
   
   var targetForm=document.deptRoomForm.formName.value;
   
   if(parseInt(document.deptRoomForm.addNum.value)==1||eval("opener."+targetForm+".brmid==null")){   
       eval("opener."+targetForm+".rmid.value=rmid;");
       
       eval("opener."+targetForm+".s_xqid.value='';");
       opener.changeBd(eval("opener."+targetForm+".s_xqid"));
       eval("opener."+targetForm+".s_bdid.style.display='';");
       eval("opener."+targetForm+".tempbuilding.style.display='none';");
       
       var haswl=false;
       for(var j=0;j<eval("opener."+targetForm+".s_rmid.length");j++){
          if(eval("opener."+targetForm+".s_rmid[j].value")==rmid){
	         eval("opener."+targetForm+".s_rmid[j].selected=true;");
	         haswl=true;
	      }
       }       
       for (var i=0;i<datacount2;i++){
           if (dataset2[i][0] == rmid){   
               eval("opener."+targetForm+".s_bdid.value=dataset2[i][3];"); 
               for (var j=0;j < datacount; j++){
                 if (dataset[j][0] == eval("opener."+targetForm+".s_bdid.value")){
                     eval("opener."+targetForm+".s_xqid.value=dataset[j][2];");
                 }
             }               
           }      
       }   
       eval("opener."+targetForm+".temproom.value=rmmc;");
       eval("opener.changeRoom(opener."+targetForm+".s_rmid);");
       
       if(haswl){
           eval("opener."+targetForm+".temproom.style.display='none';");
           eval("opener."+targetForm+".s_rmid.style.display='';");
       }
       else{
           eval("opener."+targetForm+".s_rmid.style.display='none';");
           eval("opener."+targetForm+".temproom.style.display='';");
       }
       
   }
   else if(parseInt(document.deptRoomForm.addNum.value)>1){
       eval("opener."+targetForm+".brmid.value=rmid;");
       var haswl=false;
       for(var j=0;j<eval("opener."+targetForm+".bs_rmid.length");j++){
          if(eval("opener."+targetForm+".bs_rmid[j].value")==rmid){
	         eval("opener."+targetForm+".bs_rmid[j].selected=true;");
	         haswl=true;
	      }
       }
       for (var i=0;i<datacount2;i++){
           if (dataset2[i][0] == rmid){    
               eval("opener."+targetForm+".bs_bdid.value=dataset2[i][3];"); 
               for (var j=0;j < datacount; j++){
                 if (dataset[j][0] == eval("opener."+targetForm+".bs_bdid.value")){
                     eval("opener."+targetForm+".bs_xqid.value=dataset[j][2];");
                 }
             }               
           }      
       }   
       eval("opener."+targetForm+".btemproom.value=rmmc;");
       eval("opener."+targetForm+".ifChanged.value='1';");
       
       if(haswl){
           eval("opener."+targetForm+".btemproom.style.display='none';");
           eval("opener."+targetForm+".bs_rmid.style.display='';");
       }
       else{
           eval("opener."+targetForm+".bs_rmid.style.display='none';");
           eval("opener."+targetForm+".btemproom.style.display='';");
       }
   }
   this.window.close();

}

function DoFind(){
    
    var area=document.deptRoomForm.elements["search_area"].value;
    var building=document.deptRoomForm.elements["search_building"].value;
    var roommc=document.deptRoomForm.elements["search_roommc"].value;
    var roomstate=document.deptRoomForm.elements["search_roomstate"].value;    
    
    if(document.deptRoomForm.addNum.value!=''){
       // if(roommc.length%2!=0)
       //     roommc=roommc+"曰";          
       // window.open('deptRoomAction.do?method=search4List&area='+area+'&building='+building+'&roomstate='+roomstate+'&formName='+document.deptRoomForm.formName.value+'&addNum='+document.deptRoomForm.addNum.value+'&roommc='+roommc,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');
       deptRoomForm.action="deptRoomAction.do?method=search4List";
       deptRoomForm.submit(); 
    }
    else{
        deptRoomForm.action="deptRoomAction.do?method=search4List";
        deptRoomForm.submit();    
    }
}

function DoAdd(){
    
    if(document.deptRoomForm.addNum.value!='')
        window.open('deptRoomAction.do?method=load4Add&addNum='+document.deptRoomForm.addNum.value+'&formName='+document.deptRoomForm.formName.value,'nextwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');
    else{
        document.forms.ec.action="deptRoomAction.do?method=load4Add&search_roomstate="+document.deptRoomForm.elements["search_roomstate"].value;
        document.forms.ec.submit();
    }

}

function DoSelectall(){

  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=true;       
  }
  else{
       alert("当前无记录！");
  }
  

}

function DoNotselectall(){
  
  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=false;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=false;       
  }
  else{
       alert("当前无记录！");
  }

}

function DoReverseselect(){
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
           if(document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=false;
           else if(!document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
      if(document.all.cbgroup.checked)
          document.all.cbgroup.checked=false; 
      else if(!document.all.cbgroup.checked)
          document.all.cbgroup.checked=true;    
  }
  else{
       alert("当前无记录！");
  }
  

}

function DoUpdate(){

   var sflag=0;
   var cb=0;

   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;   
                   cb=i;                                  
              }
          } 
          if(sflag>1){
                       alert("只可选择一条记录进行修改！");
                       return;
          }         
          
          else if(sflag==0){
              alert("请选择要修改的房间记录！");
              return;
          } 
          else
              document.deptRoomForm.updateid.value=document.all.cbgroup[cb].value;
   } 
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要修改的房间记录！");
              return;        
        }
        else
            document.deptRoomForm.updateid.value=document.all.cbgroup.value;
   
   }   
   if(document.deptRoomForm.addNum.value!='')
        window.open('deptRoomAction.do?method=load4Update&roomId='+document.deptRoomForm.updateid.value+'&addNum='+document.deptRoomForm.addNum.value,'nextwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');
   else{   
        document.forms.ec.action="deptRoomAction.do?method=load4Update&roomId="+document.deptRoomForm.updateid.value+"&search_roomstate="+document.deptRoomForm.elements["search_roomstate"].value;
        document.forms.ec.submit();
   }
}

function DoUse(str){

   var sflag=0;
   var ids="";
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1; 
                   var id=document.all.cbgroup[i].value;
                   var pos=id.indexOf('_');
                   if(pos!=-1)
                       id=id.substring(0,pos);
                   ids=ids+"'"+id+"'"+",";                                                 
              }
          }           
         if(sflag==0){
              alert("请选择房间记录！");
              return;
          } 
   }
   else{
        if(document.all.cbgroup.checked){
              var id=document.all.cbgroup.value;
              var pos=id.indexOf('_');
              if(pos!=-1)
                  id=id.substring(0,pos);
              ids=ids+"'"+id+"'"+",";      
        }
        else{
            alert("请选择房间记录！");
            return;   
        }            
   }
 
if(str=='02'){     
   if(confirm("废弃房间同时会废弃该房间下的机柜名称，您确定要废弃该房间记录吗？")){
       deptRoomForm.action="deptRoomAction.do?method=setRoomInfo&roomIds="+ids.substring(0,ids.length-1)+"&setroomstate="+str+"&ec_p="+document.forms.ec.elements["ec_p"].value+"&ec_i="+document.forms.ec.elements["ec_i"].value+"&ec_crd="+document.forms.ec.elements["ec_crd"].value;
       deptRoomForm.submit();
   }
   else
      return;
}
if(str=='01'){     
   if(confirm("您确定要使用该房间记录吗？")){
       deptRoomForm.action="deptRoomAction.do?method=setRoomInfo&roomIds="+ids.substring(0,ids.length-1)+"&setroomstate="+str+"&ec_p="+document.forms.ec.elements["ec_p"].value+"&ec_i="+document.forms.ec.elements["ec_i"].value+"&ec_crd="+document.forms.ec.elements["ec_crd"].value;
       deptRoomForm.submit();
   }
   else
      return;
}

}

function DoClear(){

    document.deptRoomForm.elements["search_area"].value="";
    document.deptRoomForm.elements["search_building"].value="";
    document.deptRoomForm.elements["search_roommc"].value="";    
    document.deptRoomForm.elements["search_roomstate"].value="";
}
</SCRIPT>
