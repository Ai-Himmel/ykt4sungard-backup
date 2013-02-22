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
	<body leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/eqpmaintainAction.do?method=tongji4Mtn" method="post">
			<input type="hidden" name="thisAction" value="<c:url value="/gyf/eqpmaintainAction.do"/>?method=tongji4Mtn">
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
												维修情况统计
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
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													设备大类
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_wldl" styleClass="select01" onchange="changeXl(this)">
														<html:option value="">请选择	</html:option>
														<html:options collection="dllist" labelProperty="dlmc" property="id" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													设备小类
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_wlxl" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="xllist" labelProperty="xlmc" property="id" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													设备名称
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_wlmc" styleClass="input_box" maxlength="100" />
												</td>
											</tr>
											<tr id="tr9" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													生产厂家
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_sccj" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="sccjlist" labelProperty="companyName" property="id" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													设备型号
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_xh" styleClass="input_box" maxlength="100" />
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													维修商
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_wxs" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="wxslist" labelProperty="companyName" property="id" />
													</html:select>
												</td>
											</tr>
											<tr align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													起始日期
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_begindate" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_begindate" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="开始日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													结束日期
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<table width="100%" border="0" cellspacing="0" cellpadding="0">
														<tr>
															<td width="130">
																<html:text property="search_enddate" styleClass="input_box" maxlength="50" readonly="true" />
															</td>
															<td>
																<img id="select_enddate" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="结束日期" style="cursor:pointer">
															</td>
														</tr>
													</table>
												</td>
												<script type="text/javascript">
                new calendar("search_begindate", "select_begindate", "%Y-%m-%d");
                new calendar("search_enddate", "select_enddate", "%Y-%m-%d");
              </script>
												<td align="left" valign="middle" class="tableHeader2">
													申请人
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_sqr" styleClass="input_box" maxlength="50" />
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">
									<input name="Submit" type="button" class="button_nor" value="查 询" onclick="DoFind()">
									<input name="Submit2" type="button" class="button_nor" value="重 置" onclick="DoClear()">
								</td>
							</tr>

							<logic:present name="tongjilist" scope="request">
								<tr>
									<td height="35" align="center" valign="middle" class="mediumblack">
										维修情况统计
									</td>
								</tr>
								<tr>
									<td height="30" align="right" valign="middle" colspan="2">
										<a href="javascript:DoExport()"><IMG src="<c:url value="/pages/style/default/images/xls.gif"/>" border="0"></a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
									</td>
								</tr>
								<tr>
									<td height="24" align="center" valign="middle">
										<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#3F738B bordercolordark=#ffffff id=maintable>
											<tbody>
												<tr align="center" valign=center>
													<td valign="middle" class="tableHeader" rowspan="2">
														维修设备总数
													</td>
													<td valign="middle" class="tableHeader" rowspan="2">
														维修未完成设备数
													</td>
													<td valign="middle" class="tableHeader" rowspan="2">
														维修已完成设备数
													</td>
													<td valign="middle" class="tableHeader" colspan="2">
														维修完成设备
													</td>
												</tr>
												<tr align="center" valign=center>
													<td valign="middle" class="tableHeader">
														未到发票或未入账数
													</td>
													<td valign="middle" class="tableHeader">
														已到发票且已入账数
													</td>
												</tr>
												<logic:iterate name="tongjilist" id="tl" type="java.util.Map" indexId="i">
													<tr align="center" valign="middle" bgcolor="#FFFFFF">
														<td align="center" valign="middle">
															<c:choose>
																<c:when test="${tl.totalNum != 0}">
																	<a href="javascript:DoView('','')"><bean:write name="tl" property="totalNum" /></a>&nbsp;
              </c:when>
																<c:otherwise>
              0
              </c:otherwise>
															</c:choose>
														</td>
														<td align="center" valign="middle">
															<c:choose>
																<c:when test="${tl.notdoneNum != 0}">
																	<a href="javascript:DoView('0','')"><bean:write name="tl" property="notdoneNum" /></a>&nbsp;
              </c:when>
																<c:otherwise>
              0
              </c:otherwise>
															</c:choose>
														</td>
														<td align="center" valign="middle">
															<c:choose>
																<c:when test="${tl.doneNum != 0}">
																	<a href="javascript:DoView('1','')"><bean:write name="tl" property="doneNum" /></a>&nbsp;
              </c:when>
																<c:otherwise>
              0
              </c:otherwise>
															</c:choose>
														</td>
														<td align="center" valign="middle">
															<c:choose>
																<c:when test="${tl.notaccountNum != 0}">
																	<a href="javascript:DoView('1','0')"><bean:write name="tl" property="notaccountNum" /></a>&nbsp;
              </c:when>
																<c:otherwise>
              0
              </c:otherwise>
															</c:choose>
														</td>
														<td align="center" valign="middle">
															<c:choose>
																<c:when test="${tl.accountNum != 0}">
																	<a href="javascript:DoView('1','1')"><bean:write name="tl" property="accountNum" /></a>&nbsp;
              </c:when>
																<c:otherwise>
              0
              </c:otherwise>
															</c:choose>
														</td>
													</tr>
												</logic:iterate>
											</tbody>
										</table>
									</td>
								</tr>
							</logic:present>
						</table>
					</td>
				</tr>
			</table>
		</html:form>
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
  var dl=document.eqpmaintainForm.elements["search_wldl"].value;
  var xl=document.eqpmaintainForm.elements["search_wlxl"].value;
  
  if(dl!='')
      changeXl(document.eqpmaintainForm.elements["search_wldl"]);
  for(var j=0;j<document.eqpmaintainForm.elements["search_wlxl"].length;j++){
      if(document.eqpmaintainForm.elements["search_wlxl"][j].value==xl)
	     document.eqpmaintainForm.elements["search_wlxl"][j].selected=true;
					
  }
        
}  

function changeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpmaintainForm.elements["search_wlxl"].length=1; //清空原小类列表        
   
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.eqpmaintainForm.elements["search_wlxl"].options[document.eqpmaintainForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.eqpmaintainForm.elements["search_wlxl"].options[document.eqpmaintainForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   

}

function DoView(done,act){

    eqpmaintainForm.action="eqpmaintainAction.do?method=load4MtnDetail&done="+done+"&account="+act;
    eqpmaintainForm.submit();
}

function DoFind(){
   
   eqpmaintainForm.action="eqpmaintainAction.do?method=tongji4Mtn&doexl=0";
   eqpmaintainForm.submit();

}

function DoExport(){
   
   eqpmaintainForm.action="eqpmaintainAction.do?method=tongji4Mtn&doexl=1";
   eqpmaintainForm.submit();

}

function DoClear(){
    
    document.eqpmaintainForm.elements["search_wldl"].value="";
    document.eqpmaintainForm.elements["search_wlxl"].value="";
    document.eqpmaintainForm.elements["search_wlmc"].value="";
            
    document.eqpmaintainForm.elements["search_xh"].value="";
    document.eqpmaintainForm.elements["search_sccj"].value="";
    document.eqpmaintainForm.elements["search_wxs"].value="";
    
    document.eqpmaintainForm.elements["search_begindate"].value="";
    document.eqpmaintainForm.elements["search_enddate"].value="";
    document.eqpmaintainForm.elements["search_sqr"].value="";
}

</SCRIPT>

