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
		<html:form action="/gyf/eqpdispatchAction.do?method=search4viewList" method="post">

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
												设备派发查询
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="center" valign="top">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<tbody>
											<tr align="center" valign=center>
												<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													设备编号
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_bh" styleClass="input_box" maxlength="32" />
												</td>
												<td width="20%" lign="left" valign="middle" class="tableHeader2">
													设备资产号
												</td>
												<td width="20%" align="left" valign="middle" class="tableHeader3">
													<html:text property="search_zch" styleClass="input_box" maxlength="50" />
												</td>
												<td width="15%" align="left" valign="middle" class="tableHeader2">
													设备序列号
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_xlh" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													原派发对象
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_opfdx" styleClass="select01">
														<html:option value="">请选择</html:option>
														<html:options collection="pflist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													原所处校区
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_oxq" styleClass="select01" onchange="changeOBd(this)">
														<html:option value="">请选择</html:option>
														<html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													原所在楼宇
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_olouyu" styleClass="select01">
														<html:option value="">请选择</html:option>
														<html:options collection="buildinglist" labelProperty="lymc" property="id" />
													</html:select>
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													新派发对象
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_npfdx" styleClass="select01">
														<html:option value="">请选择</html:option>
														<html:options collection="pflist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													新所处校区
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_nxq" styleClass="select01" onchange="changeNBd(this)">
														<html:option value="">请选择</html:option>
														<html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													新所在楼宇
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_nlouyu" styleClass="select01">
														<html:option value="">请选择</html:option>
														<html:options collection="buildinglist" labelProperty="lymc" property="id" />
													</html:select>
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													派发原因
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_pfyy" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="eqppfReasonlist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													原管理员
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_ogly" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													新管理员
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_ngly" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													申请人
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_sqr" styleClass="input_box" maxlength="50" />
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													登记日期从
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_djrqc" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_djrqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="开始日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<td align="right" valign="middle" class="tableHeader2">
													登记日期到
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_djrqd" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_djrqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="结束日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
											</tr>
											<script type="text/javascript">
                new calendar("search_djrqc", "select_djrqc", "%Y-%m-%d");
                new calendar("search_djrqd", "select_djrqd", "%Y-%m-%d");
           </script>
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
							</html:form>

							<tr>
								<td height="35" align="center" valign="middle" class="mediumblack">
									设备派发列表
								</td>
							</tr>
							<jodd:form bean="request">
								<tr>
									<td height="20" align="center" valign="middle">
										<ec:table items="eqplist" var="eqpJBInfo" rowsDisplayed="10" action="eqpdispatchAction.do?method=search4viewList">

											<ec:exportXls fileName="eqpdispatchList.xls" tooltip="导出 Excel" />
											<ec:row>
											<ec:column property="equipmentNo" title="查看" headerStyle="text-align:center" style="text-align: center" width="80">
													<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
													<a href="javascript:DoView('${eqpJBInfo.id}')">查看</a>
													</c:if>
													<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
													<a href="javascript:DoView('${eqpJBInfo.id}')">查看</a>
													</c:if>														
												</ec:column>
												<ec:column property="assetNo" title="设备标识" headerStyle="text-align:center" style="text-align: left" width="80">
													<c:if test="${eqpJBInfo.assetNo==null||eqpJBInfo.assetNo==''}">
													<a href="javascript:DoViewEqp('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.equipmentNo}</a>
													</c:if>
													<c:if test="${eqpJBInfo.assetNo!=null&&eqpJBInfo.assetNo!=''}">
													<a href="javascript:DoViewEqp('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.assetNo}</a>
													</c:if>														
												</ec:column>
												<ec:column property="opfCategory" title="原派发" headerStyle="text-align:center" style="text-align: left" width="50" />
												<ec:column property="ocollegeArea" title="原校区" headerStyle="text-align:center" style="text-align: left" width="60" />
												<ec:column property="olymc" title="原楼宇" headerStyle="text-align:center" style="text-align: left" width="50" />
												<ec:column property="npfCategory" title="新派发" headerStyle="text-align:center" style="text-align: left" width="50" />
												<ec:column property="ncollegeArea" title="新校区" headerStyle="text-align:center" style="text-align: left" width="60" />
												<ec:column property="nlymc" title="新楼宇" headerStyle="text-align:center" style="text-align: left" width="50" />
												<ec:column property="pfReason" title="原因" headerStyle="text-align:center" style="text-align: left" width="40" />
												<ec:column property="omanagerName" title="原管理" headerStyle="text-align:center" style="text-align: left" width="50" />
												<ec:column property="nmanagerName" title="新管理" headerStyle="text-align:center" style="text-align: left" width="50" />
												<ec:column property="managerCheckName" title="接收状态" headerStyle="text-align:center" style="text-align: left" width="50" />
												<ec:column property="usageCategory" title="用途大类" headerStyle="text-align:center" style="text-align: left" width="60" />																							
												<ec:column property="recordDate" title="日期" cell="date" format="yyyy-MM-dd" headerStyle="text-align:center" style="text-align: left" width="80" />
											</ec:row>
										</ec:table>
									</td>
								</tr>
							</jodd:form>
						</table>
					</td>
				</tr>
			</table>
	</body>
</html>

<script>

    var datacount2=0;
    dataset2=new Array();
    
   <%
   int count2=0;
   String[][] resultset2=null;
   if(request.getAttribute("ablist")!=null)
       resultset2=(String[][])request.getAttribute("ablist");//读取校区、楼宇对应数据
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>");//产生javascript二维数组，对应楼宇id、楼宇名称、校区id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>

<SCRIPT language=javascript>

setTimeout('init()',10);
function init(){
   
  var oarea=document.eqpdispatchForm.elements["search_oxq"].value;
  var obuilding=document.eqpdispatchForm.elements["search_olouyu"].value;
  
  if(oarea!='')
      changeOBd(document.eqpdispatchForm.elements["search_oxq"]);
  for(var j=0;j<document.eqpdispatchForm.elements["search_olouyu"].length;j++){
      if(document.eqpdispatchForm.elements["search_olouyu"][j].value==obuilding)
	     document.eqpdispatchForm.elements["search_olouyu"][j].selected=true;
					
  }
  
  var narea=document.eqpdispatchForm.elements["search_nxq"].value;
  var nbuilding=document.eqpdispatchForm.elements["search_nlouyu"].value;
  
  if(narea!='')
      changeNBd(document.eqpdispatchForm.elements["search_nxq"]);
  for(var j=0;j<document.eqpdispatchForm.elements["search_nlouyu"].length;j++){
      if(document.eqpdispatchForm.elements["search_nlouyu"][j].value==nbuilding)
	     document.eqpdispatchForm.elements["search_nlouyu"][j].selected=true;
					
  }
   
}  

function changeOBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpdispatchForm.elements["search_olouyu"].length=1; //清空原楼宇列表        
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][2] == id)
          {   
             document.eqpdispatchForm.elements["search_olouyu"].options[document.eqpdispatchForm.elements["search_olouyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount2; i++)
      {
          document.eqpdispatchForm.elements["search_olouyu"].options[document.eqpdispatchForm.elements["search_olouyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function changeNBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpdispatchForm.elements["search_nlouyu"].length=1; //清空原楼宇列表        
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][2] == id)
          {   
             document.eqpdispatchForm.elements["search_nlouyu"].options[document.eqpdispatchForm.elements["search_nlouyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount2; i++)
      {
          document.eqpdispatchForm.elements["search_nlouyu"].options[document.eqpdispatchForm.elements["search_nlouyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function zchSetup(sel){

   alert(sel.value);

}
function doSel(sel){
//alert(sel.value);
}

function DoView(eno){

    window.open("eqpdispatchAction.do?method=load4view&dispatchId="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function DoViewEqp(eno){

    window.open("equipmentAction.do?method=load4view&equipmentNo="+eno,"detailInfo","height=600,width=1000,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function DoClear(){

    document.eqpdispatchForm.elements["search_bh"].value="";
    document.eqpdispatchForm.elements["search_zch"].value="";    
    document.eqpdispatchForm.elements["search_xlh"].value="";
    
    document.eqpdispatchForm.elements["search_opfdx"].value="";
    document.eqpdispatchForm.elements["search_opfdx"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_oxq"].value="";
    document.eqpdispatchForm.elements["search_oxq"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_olouyu"].value="";
    document.eqpdispatchForm.elements["search_olouyu"].options[0].selected=true;
    
    document.eqpdispatchForm.elements["search_npfdx"].value="";
    document.eqpdispatchForm.elements["search_npfdx"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_nxq"].value="";
    document.eqpdispatchForm.elements["search_nxq"].options[0].selected=true;
    document.eqpdispatchForm.elements["search_nlouyu"].value="";
    document.eqpdispatchForm.elements["search_nlouyu"].options[0].selected=true;
    
    document.eqpdispatchForm.elements["search_pfyy"].value="";
    document.eqpdispatchForm.elements["search_pfyy"].options[0].selected=true;    
    document.eqpdispatchForm.elements["search_ogly"].value="";
    document.eqpdispatchForm.elements["search_ngly"].value="";
    
    document.eqpdispatchForm.elements["search_sqr"].value="";
    document.eqpdispatchForm.elements["search_djrqc"].value="";
    document.eqpdispatchForm.elements["search_djrqd"].value="";
            
}

</SCRIPT>

