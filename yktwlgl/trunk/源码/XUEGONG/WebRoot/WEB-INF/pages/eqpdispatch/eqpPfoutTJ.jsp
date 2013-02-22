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
		<html:form action="/gyf/eqpdispatchAction.do?method=tongji4EqpPfout" method="post">

			<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td align="left" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<input type="hidden" name="thisAction" value="<c:url value="/gyf/eqpdispatchAction.do"/>?method=tongji4EqpPfout">
							<tr>
								<td height="25" align="left" valign="top">
									<table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">
												设备派出统计
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
											<tr id="tr8" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													派发对象
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_pfdx" styleClass="select01">
														<html:option value="">请选择</html:option>
														<html:options collection="pflist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													所处校区
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_xq" styleClass="select01" onchange="changeBd(this)">
														<html:option value="">请选择</html:option>
														<html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
													</html:select>
												</td>
												<td align="left" valign="middle" class="tableHeader2">
													所在楼宇
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_louyu" styleClass="select01">
														<html:option value="">请选择</html:option>
														<html:options collection="buildinglist" labelProperty="lymc" property="id" />
													</html:select>
												</td>
											</tr>
											<tr id="tr9" align="center" valign=center>
												<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
													机房/库房
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="search_jfkf" styleClass="input_box" maxlength="100" />
												</td>
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
													派出原因
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:select property="search_pfyy" styleClass="select01">
														<html:option value="">请选择	</html:option>
														<html:options collection="eqppfReasonlist" labelProperty="dictCaption" property="dictValue" />
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
												<td align="left" valign="middle" class="tableHeader3" colspan="3">
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
										设备派出统计
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
													<td valign="middle" class="tableHeader">
														派发对象
													</td>
													<td valign="middle" class="tableHeader">
														所在校区
													</td>
													<td valign="middle" class="tableHeader">
														所在楼宇
													</td>
													<td valign="middle" class="tableHeader">
														库房/机房
													</td>
													<td valign="middle" class="tableHeader">
														派出原因
													</td>
													<td valign="middle" class="tableHeader">
														设备数量
													</td>
													<%if (request.getAttribute("ifLimit").equals("0")) {%>
													<td valign="middle" class="tableHeader">
														设备金额
													</td>
													<%}%>
												</tr>
												<%int j = 0;%>
												<logic:iterate name="tongjilist" id="tl" type="java.util.Map" indexId="i">
													<tr align="center" valign="middle" <%if(j%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
														<td align="center" valign="middle">
															<bean:write name="tl" property="pfCategoryName" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<input type="hidden" name="hpf" value="<bean:write name="tl" property="pfCategoryName" />">
															<bean:write name="tl" property="collegeAreaName" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<input type="hidden" name="hxq" value="<bean:write name="tl" property="pfCategoryName" /><bean:write name="tl" property="collegeAreaName" />">
															<bean:write name="tl" property="lymc" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<input type="hidden" name="hly" value="<bean:write name="tl" property="pfCategoryName" /><bean:write name="tl" property="collegeAreaName" /><bean:write name="tl" property="lymc" />">
															<bean:write name="tl" property="roommc" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<input type="hidden" name="hrm" value="<bean:write name="tl" property="pfCategoryName" /><bean:write name="tl" property="collegeAreaName" /><bean:write name="tl" property="lymc" /><bean:write name="tl" property="roommc" />">
															<bean:write name="tl" property="pfReasonName" />
															&nbsp;
														</td>
														<td align="center" valign="middle">
															<a
																href="javascript:DoView('2','<bean:write name="tl" property="pfReason"/>','<bean:write name="tl" property="roomid" />','<bean:write name="tl" property="lyid"/>','<bean:write name="tl" property="collegeArea" />','<bean:write name="tl" property="pfCategory" />')"><bean:write
																	name="tl" property="eqpNum" /></a>&nbsp;
														</td>
														<%if (request.getAttribute("ifLimit").equals("0")) {%>
														<td align="center" valign="middle">
															<bean:write name="tl" property="eqpSum" />
															&nbsp;
														</td>
														<%}%>
													</tr>
												</logic:iterate>
												<logic:present name="tongjitotal" scope="request">
													<logic:iterate name="tongjitotal" id="tlt" type="java.util.Map">
														<tr height="26" align="center" valign="middle" bgcolor="#FF9999" style="font-weight:bold">
															<td align="center" valign="middle">
																总 计
															</td>
															<td align="center" valign="middle">
																--
															</td>
															<td align="center" valign="middle">
																--
															</td>
															<td align="center" valign="middle">
																--
															</td>
															<td align="center" valign="middle">
																--
															</td>
															<td align="center" valign="middle">
																<bean:write name="tlt" property="eqpNum" />
																&nbsp;
															</td>
															<%if (request.getAttribute("ifLimit").equals("0")) {%>
															<td align="center" valign="middle">
																<bean:write name="tlt" property="eqpSum" />
																&nbsp;
															</td>
															<%}%>
														</tr>
													</logic:iterate>
												</logic:present>
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
  var dl=document.eqpdispatchForm.elements["search_wldl"].value;
  var xl=document.eqpdispatchForm.elements["search_wlxl"].value;
  
  if(dl!='')
      changeXl(document.eqpdispatchForm.elements["search_wldl"]);
  for(var j=0;j<document.eqpdispatchForm.elements["search_wlxl"].length;j++){
      if(document.eqpdispatchForm.elements["search_wlxl"][j].value==xl)
	     document.eqpdispatchForm.elements["search_wlxl"][j].selected=true;
					
  }
  
  var area=document.eqpdispatchForm.elements["search_xq"].value;
  var building=document.eqpdispatchForm.elements["search_louyu"].value;
  
  if(area!='')
      changeBd(document.eqpdispatchForm.elements["search_xq"]);
  for(var j=0;j<document.eqpdispatchForm.elements["search_louyu"].length;j++){
      if(document.eqpdispatchForm.elements["search_louyu"][j].value==building)
	     document.eqpdispatchForm.elements["search_louyu"][j].selected=true;
					
  }
  
  if(document.all.maintable!=null)
      uniteTable(document.all.maintable,4);
      
}  

function changeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpdispatchForm.elements["search_wlxl"].length=1; //清空原小类列表        
   
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.eqpdispatchForm.elements["search_wlxl"].options[document.eqpdispatchForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.eqpdispatchForm.elements["search_wlxl"].options[document.eqpdispatchForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   

}

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpdispatchForm.elements["search_louyu"].length=1; //清空原楼宇列表        
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][2] == id)
          {   
             document.eqpdispatchForm.elements["search_louyu"].options[document.eqpdispatchForm.elements["search_louyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount2; i++)
      {
          document.eqpdispatchForm.elements["search_louyu"].options[document.eqpdispatchForm.elements["search_louyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function zchSetup(sel){

   alert(sel.value);

}

function DoFind(){
   
   eqpdispatchForm.action="eqpdispatchAction.do?method=tongji4EqpPfout&doexl=0";
   eqpdispatchForm.submit();

}

function DoView(io,pfr,rm,bd,xq,pf){

    eqpdispatchForm.action="eqpdispatchAction.do?method=load4Detail&inorout="+io+"&pfreason="+pfr+"&room="+rm+"&building="+bd+"&area="+xq+"&pfdx="+pf;
    eqpdispatchForm.submit();
}

function DoExport(){
   
   eqpdispatchForm.action="eqpdispatchAction.do?method=tongji4EqpPfout&doexl=1";
   eqpdispatchForm.submit();

}


function DoClear(){
    
    document.eqpdispatchForm.elements["search_wldl"].value="";
    document.eqpdispatchForm.elements["search_wlxl"].value="";
    document.eqpdispatchForm.elements["search_wlmc"].value="";
        
    document.eqpdispatchForm.elements["search_pfdx"].value="";
    document.eqpdispatchForm.elements["search_xq"].value="";
    document.eqpdispatchForm.elements["search_louyu"].value="";
    document.eqpdispatchForm.elements["search_jfkf"].value="";
    document.eqpdispatchForm.elements["search_sccj"].value="";
    document.eqpdispatchForm.elements["search_pfyy"].value="";
    document.eqpdispatchForm.elements["search_begindate"].value="";
    document.eqpdispatchForm.elements["search_enddate"].value="";
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

</SCRIPT>

