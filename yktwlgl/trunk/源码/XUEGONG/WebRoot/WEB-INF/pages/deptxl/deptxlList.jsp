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
		<html:form action="/wxg/deptXl.do?method=search4List" method="post">

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
												部门物料小类设置
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
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													物料大类
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_wldl" styleClass="select01" onchange="changeXl(this)">
														<html:option value="">请选择	</html:option>
														<html:options collection="dllist" labelProperty="dlmc" property="id" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													物料小类
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_wlxl" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="xllist" labelProperty="xlmc" property="id" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													状态
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_xlstate" styleClass="select01">
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

									<input name="Submit" type="submit" class="button_nor" value="查 询">
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
									部门中已设置的物料小类列表
								</td>
							</tr>
							<jodd:form bean="request">
								<tr>
									<td height="20" align="center" valign="middle">
										<ec:table items="wlxllist" var="wlxl" autoIncludeParameters="false" rowsDisplayed="10" action="deptXl.do?method=search4List">

											<ec:exportXls fileName="wlxlList.xls" tooltip="导出 Excel" />
											<ec:parameter name="search_wldl" />
											<ec:parameter name="search_wlxl" />
											<ec:parameter name="search_xlstate" />
											<ec:row>
												<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" headerStyle="text-align:center" style="text-align: left">
													<input type="checkbox" name="cbgroup" value="${wlxl.id}" style="border:0px" />
												</ec:column>
												<ec:column property="dlbh" title="所属大类" headerStyle="text-align:center" style="text-align: left" width="80">
													<c:choose>
														<c:when test="${wlxl.state=='02'}">
															<font color="#A8A8A8">${wlxl.dlbh}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="dlmc" title="大类名称" headerStyle="text-align:center" style="text-align: left" width="100">
													<c:choose>
														<c:when test="${wlxl.state=='02'}">
															<font color="#A8A8A8">${wlxl.dlmc}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="lbbh" title="小类编号" headerStyle="text-align:center" style="text-align: left" width="80">
													<c:choose>
														<c:when test="${wlxl.state=='02'}">
															<font color="#A8A8A8">${wlxl.lbbh}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="mc" title="小类名称" headerStyle="text-align:center" style="text-align: left" width="100">
													<c:choose>
														<c:when test="${wlxl.state=='02'}">
															<font color="#A8A8A8">${wlxl.mc}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="stateName" title="状态" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${wlxl.state=='02'}">
															<font color="#A8A8A8">${wlxl.stateName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="updatorName" title="更新人" headerStyle="text-align:center" style="text-align: left" width="60">
													<c:choose>
														<c:when test="${wlxl.state=='02'}">
															<font color="#A8A8A8">${wlxl.updatorName}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
												<ec:column property="updateTime" title="更新日期" headerStyle="text-align:center" style="text-align: left" width="100">
													<c:choose>
														<c:when test="${wlxl.state=='02'}">
															<font color="#A8A8A8">${wlxl.updateTime}</font>&nbsp;
					</c:when>
													</c:choose>
												</ec:column>
											</ec:row>
										</ec:table>
									</td>
								</tr>
								<%if (((java.util.ArrayList) request.getAttribute("wlxllist")).size() > 0) {%>
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
														<input name="bnotuse" type="button" class="button_nor" value="废 弃" onClick="DoUse('02')">
														<input name="buse" type="button" class="button_nor" value="使 用" onClick="DoUse('01')">
														<input name="Submit4" type="button" class="button_nor" value="新 增" onClick="DoAdd()">
													</td>
												</tr>
											</tbody>
										</table>
									</td>
								</tr>
								<%} else {%>
								<tr>
									<td height="40" align="right" valign="middle">
										<input name="Submit4" type="button" class="button_nor" value="新 增" onClick="DoAdd()">
									</td>
								</tr>
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
   if(request.getAttribute("dxlist")!=null)
       resultset=(String[][])request.getAttribute("dxlist");//读取大小类对应数据
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//产生javascript二维数组，对应小类id、小类名称、大类id
     <%
     }
   }
   %>
   datacount=<%=count%>;

</script>

<SCRIPT language=javascript>

setTimeout('init()',10);
function init(){
  var dl=document.deptXlForm.elements["search_wldl"].value;
  var xl=document.deptXlForm.elements["search_wlxl"].value;
  
  if(dl!='')
      changeXl(document.deptXlForm.elements["search_wldl"]);
  for(var j=0;j<document.deptXlForm.elements["search_wlxl"].length;j++){
      if(document.deptXlForm.elements["search_wlxl"][j].value==xl)
	     document.deptXlForm.elements["search_wlxl"][j].selected=true;
					
  } 
     
  if(document.deptXlForm.hmsg.value=='dok')
       alert("设置成功！");
  else if(document.deptXlForm.hmsg.value=='dfail')
       alert("设置失败！");
  if(document.deptXlForm.hcannotUse.value!='')
       alert(document.deptXlForm.hcannotUse.value+" 大类为废弃，不能使用！");
  if(document.deptXlForm.hrepeatSet.value!='')
       alert(document.deptXlForm.hrepeatSet.value+" 重复设置！");
}  

function changeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.deptXlForm.elements["search_wlxl"].length=1; //清空原小类列表        
   
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.deptXlForm.elements["search_wlxl"].options[document.deptXlForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.deptXlForm.elements["search_wlxl"].options[document.deptXlForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   

}

function DoAdd(){
    
    document.forms.ec.action="deptXl.do?method=load4newAdd";
    document.forms.ec.submit();
    
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

function DoUse(str){

   var sflag=0;
   var ids="";
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1; 
                   var id=document.all.cbgroup[i].value;                   
                   ids=ids+"'"+id+"'"+",";                                                 
              }
          }           
         if(sflag==0){
              alert("请选择物料小类！");
              return;
          } 
   }
   else{
        if(document.all.cbgroup.checked){
              var id=document.all.cbgroup.value;              
              ids=ids+"'"+id+"'"+",";      
        }
        else{
            alert("请选择物料小类！");
            return;   
        }            
   }
   
   if(str=='02'){
   if(confirm("废弃小类同时会废弃该小类下的物料名称，您确定要废弃该物料小类吗？")){
       deptXlForm.action="deptXl.do?method=setXl&xlIds="+ids.substring(0,ids.length-1)+"&xlstate="+str+"&ec_p="+document.forms.ec.elements["ec_p"].value+"&ec_i="+document.forms.ec.elements["ec_i"].value+"&ec_crd="+document.forms.ec.elements["ec_crd"].value;
       deptXlForm.submit();
   }
   else
      return;
   }
   if(str=='01'){
   if(confirm("您确定要使用该物料小类吗？")){
       deptXlForm.action="deptXl.do?method=setXl&xlIds="+ids.substring(0,ids.length-1)+"&xlstate="+str+"&ec_p="+document.forms.ec.elements["ec_p"].value+"&ec_i="+document.forms.ec.elements["ec_i"].value+"&ec_crd="+document.forms.ec.elements["ec_crd"].value;
       deptXlForm.submit();
   }
   else
      return;
   }
}

function DoClear(){

    document.deptXlForm.elements["search_wldl"].value="";
    document.deptXlForm.elements["search_wlxl"].value=""; 
    document.deptXlForm.elements["search_xlstate"].value="";
}
</SCRIPT>
