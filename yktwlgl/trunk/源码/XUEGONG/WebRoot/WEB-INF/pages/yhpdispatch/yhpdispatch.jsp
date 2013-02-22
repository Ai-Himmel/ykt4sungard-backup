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
		<script src="<c:url value="/pages/scripts/util.js"/>" type="text/javascript"></script>

		<script>

var idcount=0;
idset=new Array();

<%
   int idsCount=0;
   String[] idsSet=null;
   if(request.getAttribute("ids")!=null)
       idsSet=(String[])request.getAttribute("ids");//读取设备号数组
   
   if(idsSet!=null){
     for(idsCount=0;idsCount<idsSet.length;idsCount++)
     {
     %>
      idset[<%=idsCount%>] = new Array("<%=idsSet[idsCount]%>");//产生javascript数组，对应小类id、小类名称、大类id
     <%
     }
   }
   %>
   idcount=<%=idsCount%>;
</script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>

		<html:form action="/gyf/yhpdispatchAction.do?method=dispatch" method="post">

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
												派发信息表
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
											<logic:present name="yhplist" scope="request">
												<jodd:form bean="request">
													<tr align="center" valign="middle">
														<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															<font color="red" style="font-weight:normal">*</font>&nbsp;派发原因
														</td>
														<td width="35%" align="left" valign="middle" class="tableHeader3">
															<select name="s_pfReason" class="select01" onchange="changePfReason(this)">
																<option value="" checked>
																	请选择
																</option>
																<logic:present name="yhppfReasonlist" scope="request">
																	<logic:iterate name="yhppfReasonlist" id="pr" type="java.util.Map">
																		<option value="<bean:write name="pr" property="dictValue"/>">
																			<bean:write name="pr" property="dictCaption" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
															<input type="hidden" name="pfReason" value="<%=request.getParameter("pfReason")==null||request.getParameter("pfReason").equals("null")?"":request.getParameter("pfReason")%>" title="派发原因" isMust='1'>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															用途大类
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_usageCategory" class="select01" onchange="changeUsageCategory(this)">
																			<option value="" checked>
																				请选择
																			</option>
																			<logic:present name="uclist" scope="request">
																				<logic:iterate name="uclist" id="uc" type="java.util.Map">
																					<option value="<bean:write name="uc" property="id"/>">
																						<bean:write name="uc" property="usageCategoryName" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="usageCategory" value="<%=request.getParameter("usageCategory")==null||request.getParameter("usageCategory").equals("null")?"":request.getParameter("usageCategory")%>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="tempUsageCategory" style="input_box" maxlength="50" value="<%=request.getParameter("tempUsageCategory")==null||request.getParameter("tempUsageCategory").equals("null")?"":request.getParameter("tempUsageCategory")%>"
																			readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addUsageCategory" type="button" value="查找"
																			onclick="javascript:window.open('deptUsageCategoryAction.do?method=search4List&formName=yhpdispatchForm&addNum='+idcount,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															用途说明
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<textarea name="pfUsage" cols=70 rows=2></textarea>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															<font color="red" style="font-weight:normal">*</font>&nbsp;新派发对象
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<select name="s_pfid" class="select01" onchange="changePfid(this)">
																<option value="" checked>
																	请选择
																</option>
																<logic:present name="pflist" scope="request">
																	<logic:iterate name="pflist" id="pfl" type="java.util.Map">
																		<option value="<bean:write name="pfl" property="dictValue"/>">
																			<bean:write name="pfl" property="dictCaption" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
															<input type="hidden" name="pfid" value="<%=request.getParameter("pfid")==null||request.getParameter("pfid").equals("null")?"":request.getParameter("pfid")%>" title="新派发对象" isMust='1'>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															新校区
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<select name="s_xqid" class="select01" onchange="changeBd(this);changeXqid(this)">
																<option value="" checked>
																	请选择
																</option>
																<logic:present name="arealist" scope="request">
																	<logic:iterate name="arealist" id="al" type="java.util.Map">
																		<option value="<bean:write name="al" property="dictValue"/>">
																			<bean:write name="al" property="dictCaption" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
															<input type="hidden" name="xqid" value="<%=request.getParameter("xqid")==null||request.getParameter("xqid").equals("null")?"":request.getParameter("xqid")%>">
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															新楼宇
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_bdid" class="select01" onchange="changeRm(this);changeBdid(this)">
																			<option value="" checked>
																				请选择
																			</option>
																			<logic:present name="buildinglist" scope="request">
																				<logic:iterate name="buildinglist" id="bdl" type="java.util.Map">
																					<option value="<bean:write name="bdl" property="id"/>">
																						<bean:write name="bdl" property="lymc" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="bdid" value="<%=request.getParameter("bdid")==null||request.getParameter("bdid").equals("null")?"":request.getParameter("bdid")%>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="tempbuilding" style="input_box" maxlength="50" value="<%=request.getParameter("tempbuilding")==null||request.getParameter("tempbuilding").equals("null")?"":request.getParameter("tempbuilding")%>" readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addBuilding" type="button" value="查找" onclick="DoaddLymc()">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															新房间
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_rmid" class="select01" onchange="changeRoom(this);changeRmid(this)">
																			<option value="" checked>
																				请选择
																			</option>
																			<logic:present name="roomlist" scope="request">
																				<logic:iterate name="roomlist" id="rml" type="java.util.Map">
																					<option value="<bean:write name="rml" property="id"/>">
																						<bean:write name="rml" property="roommc" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="rmid" value="<%=request.getParameter("rmid")==null||request.getParameter("rmid").equals("null")?"":request.getParameter("rmid")%>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="temproom" style="input_box" maxlength="50" value="<%=request.getParameter("temproom")==null||request.getParameter("temproom").equals("null")?"":request.getParameter("temproom")%>" readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addRoom" type="button" value="查找" onclick="DoaddRoom()">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															详细地点
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<textarea name="NPlace" cols=70 rows=2></textarea>
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															派发数量
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<input name="pfNum" style="input_box" maxlength="50" value="" title="派发数量" dataType="Int" />
														</td>
													</tr>
													<tr align="center" valign="middle">
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															派发编号
														</td>
														<td align="left" valign="middle" style="background-color: #E7F1F5;font-size: 12px;text-align: left;" nowrap="nowrap">
															<input name="beginNo" style="input_box" maxlength="50" value="" />
															&nbsp;--&nbsp;
															<input name="endNo" style="input_box" maxlength="50" value="" />
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															接收人(内部)
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<select name="s_deptacpid" class="select01" onchange="changedeptAcpid(this)">
																<option value="" checked>
																	请选择
																</option>
																<logic:present name="mglist" scope="request">
																	<logic:iterate name="mglist" id="mgl" type="java.util.Map">
																		<option value="<bean:write name="mgl" property="code"/>">
																			<bean:write name="mgl" property="personName" />
																			&nbsp;
																			<bean:write name="mgl" property="code" />
																		</option>
																	</logic:iterate>
																</logic:present>
															</select>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															接收人(外部)
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<table border="0" cellspacing="0" cellpadding="0">
																<tr align="center" valign="middle">
																	<td width="35">
																		<select name="s_acpid" class="select01" onchange="changeAcpid(this)">
																			<option value="" checked>
																				请选择
																			</option>
																			<logic:present name="acplist" scope="request">
																				<logic:iterate name="acplist" id="acpl" type="java.util.Map">
																					<option value="<bean:write name="acpl" property="id"/>">
																						<bean:write name="acpl" property="personName" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="acpid" value="<%=request.getParameter("acpid")==null||request.getParameter("acpid").equals("null")?"":request.getParameter("acpid")%>">
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="40" align="right">
																		<input name="tempAcpPerson" style="input_box" maxlength="50" value="<%=request.getParameter("tempAcpPerson")==null||request.getParameter("tempAcpPerson").equals("null")?"":request.getParameter("tempAcpPerson")%>" readonly="readonly" />
																	</td>
																	<td width="20">
																		&nbsp;
																	</td>
																	<td width="20" align="right">
																		<input name="addAcpPerson" type="button" value="查找"
																			onclick="javascript:window.open('deptOtherPersonAction.do?method=search4List&formName=yhpdispatchForm&addNum=1','newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
																	</td>
																</tr>
															</table>
														</td>
													</tr>
													<tr align="center" valign=center>
														<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
															备注
														</td>
														<td align="left" valign="middle" class="tableHeader3">
															<textarea name="memo" cols=70 rows=2 maxLength="300"></textarea>
														</td>
													</tr>
												</jodd:form>
												<logic:iterate name="yhplist" id="ebl" type="java.util.Map" indexId="i">
													<input type="text" name="yhpNo_<bean:write name="ebl" property="yhpNo"/>" value="<bean:write name="ebl" property="yhpNo"/>" readonly="readonly">
													<input type="hidden" name="<bean:write name="ebl" property="yhpNo"/>yhpNum" value="<bean:write name="ebl" property="yhpNum"/>">
													<input type="hidden" name="<bean:write name="ebl" property="yhpNo"/>ousageCategory" value="<bean:write name="ebl" property="ousageCategory"/>">
													<input type="hidden" name="<bean:write name="ebl" property="yhpNo"/>opfid" value="<bean:write name="ebl" property="opfid"/>">
													<input type="hidden" name="<bean:write name="ebl" property="yhpNo"/>oxqid" value="<bean:write name="ebl" property="oxqid"/>">
													<input type="hidden" name="<bean:write name="ebl" property="yhpNo"/>obdid" value="<bean:write name="ebl" property="obdid"/>">
													<input type="hidden" name="<bean:write name="ebl" property="yhpNo"/>ormid" value="<bean:write name="ebl" property="ormid"/>">
													<input type="hidden" name="<bean:write name="ebl" property="yhpNo"/>ocurNum" value="<bean:write name="ebl" property="curNum"/>">
												</logic:iterate>
											</logic:present>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="30" align="right" valign="middle">
									<input name="Submit10" type="button" class="button_nor" value="保 存" onclick="doSave();">
									&nbsp;
									<input name="Submit12" type="button" class="button_nor" value="返 回" onClick="DoBack()">
								</td>
							</tr>
						</table>
						<logic:present name="msg" scope="request">
							<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
						</logic:present>
						<logic:notPresent name="msg" scope="request">
							<input name="hmsg" type="hidden" value="">
						</logic:notPresent>
						<logic:present name="ncdispatch" scope="request">
							<input name="hncdispatch" type="hidden" value="<bean:write name="ncdispatch" />">
						</logic:present>
						<logic:notPresent name="ncdispatch" scope="request">
							<input name="hncdispatch" type="hidden" value="">
						</logic:notPresent>

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


<script type="text/javascript">

setTimeout('DoInit()',10);

function DoInit(){

   var xq,bd,rm;
   var hasbd=false;
   var hasrm=false;
       
     xq=document.all.s_xqid.value;
     bd=document.all.s_bdid.value;
     rm=document.all.s_rmid.value;
          
     if(xq!='')
      BchangeBd(document.all.s_xqid);
      for(var j=0;j<document.all.s_bdid.length;j++){
      if(document.all.s_bdid[j].value==bd){
	     document.all.s_bdid[j].selected=true;
	     hasbd=true;
	  }
	  }	
	  
	  if(hasbd){
	      document.all.s_bdid.style.display='';
	      document.all.tempbuilding.style.display='none';	  
	  }
	  else{
	      document.all.s_bdid.style.display='none';
	      document.all.tempbuilding.style.display='';	  
	  }		
   
   if(bd!='')
        BchangeRm(document.all.s_bdid);
   for(var j=0;j<document.all.s_rmid.length;j++){
      if(document.all.s_rmid[j].value==rm){
	     document.all.s_rmid[j].selected=true;
	     hasrm=true;
	  }
   }  
   
   if(hasrm){
	      document.all.s_rmid.style.display='';
	      document.all.temproom.style.display='none';	  
	  }
	  else{
	      document.all.s_rmid.style.display='none';
	      document.all.temproom.style.display='';	  
	} 
	
	var uc;
   var hasuc=false;
   
   uc=document.all.usageCategory.value;
   for(var i=0;i<document.all.s_usageCategory.length;i++){//用途大类
       if(document.all.s_usageCategory[i].value==uc){
           hasuc=true;
       }
   }
   
   if(hasuc){
       document.all.s_usageCategory.style.display='';
       document.all.tempUsageCategory.style.display='none';
   }
   else{
       document.all.s_usageCategory.style.display='none';
       document.all.tempUsageCategory.style.display='';   
   }
   
   var acp;
   var hasacp=false;
   
   acp=document.all.acpid.value;
   for(var i=0;i<document.all.s_acpid.length;i++){//外部人员
       if(document.all.s_acpid[i].value==acp){
           hasacp=true;
       }
   }
   
   if(hasacp){
       document.all.s_acpid.style.display='';
       document.all.tempAcpPerson.style.display='none';
   }
   else{
       document.all.s_acpid.style.display='none';
       document.all.tempAcpPerson.style.display='';   
   }     
   
   if(document.all.hmsg.value=='1')
       alert("保存成功！");
   else if(document.all.hmsg.value=='0')
       alert("保存失败！");
   if(document.all.hncdispatch.value!='')
       alert(document.all.hncdispatch.value+" 暂时不能重新派发！");
}

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.s_bdid.length=1; //清空原楼宇列表
   document.all.s_rmid.length=1; //清空原房间列表        
      
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.all.s_bdid.options[document.all.s_bdid.length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.all.s_bdid.options[document.all.s_bdid.length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
       for (i=0;i < datacount2; i++)
      {
          document.all.s_rmid.options[document.all.s_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
    }
   

}

function changeRm(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.all.s_rmid.length=1; //清空原房间列表        
   
   if(id!=""){      
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][3] == id)
          {   
             document.all.s_rmid.options[document.all.s_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]); 
                  
          }
      }
      for (i=0;i < datacount; i++){
          if (dataset[i][0] == id){
             document.all.s_xqid.value=dataset[i][2];
          }
      }
    }else{
       //alert("wl is null");
       for (i=0;i < datacount2; i++)
      {
          document.all.s_rmid.options[document.all.s_rmid.length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function changeRoom(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   
   if(id!="")
      for (var i=0;i < datacount2; i++)
      {
         if (dataset2[i][0] == id)
          {                
             document.all.s_bdid.value=dataset2[i][3];              
             for (var j=0;j< datacount;j++){
                 if (dataset[j][0] == document.all.s_bdid.value){
                     document.all.s_xqid.value=dataset[j][2];
                 }
             }
          }
      }
    
}

function changePfReason(sel){
    document.all.pfReason.value=sel.value;
}

function changeUsageCategory(sel){
    document.all.usageCategory.value=sel.value;
}

function changePfid(sel){
    document.all.pfid.value=sel.value;
}

function changeXqid(sel){
    document.all.xqid.value=sel.value;
}

function changeBdid(sel){
    document.all.bdid.value=sel.value;
}

function changeRmid(sel){
    document.all.rmid.value=sel.value;
}

function changeManagerid(sel){
    document.all.mgid.value=sel.value;
}

function changeAcpid(sel){
    document.all.acpid.value=sel.value;
    document.all.s_deptacpid.value="";
}

function changedeptAcpid(sel){
    document.all.acpid.value=sel.value;
    document.all.s_acpid.value="";
    document.all.tempAcpPerson.value="";
}

function DoaddLymc(){

window.open("deptBuildingAction.do?method=search4List&formName=yhpdispatchForm&addNum="+idcount+"&area="+document.all.s_xqid.value,"newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
//document.all.s_xqid.value="";
//changeBd(document.all.s_xqid);

}

function DoaddRoom(){

window.open("deptRoomAction.do?method=search4List&formName=yhpdispatchForm&addNum="+idcount+"&area="+document.all.s_xqid.value+"&building="+document.all.s_bdid.value,"newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
//document.all.s_xqid.value="";
//changeBd(document.all.s_xqid);

}

function doSave(){

if(document.all.pfid.value!=''&&document.all.pfid.value!='2_geren'){
    if(document.all.rmid.value==''){
        alert("非派发给个人必须选择派发到的具体房间！");
        return;
    }    
}

if(document.all.pfid.value!=''&&document.all.pfid.value!='2_xianzhichu'){
   if(document.all.pfNum.value==''){
       alert("非派发到闲置处必须填写派发数量！");
       return;
   }
}

if(doCheckForm(yhpdispatchForm)){
    
    for(var i=0;i<idcount;i++){
        var yNo=idset[i];
        var ynum=eval("document.all."+idset[i]+"yhpNum.value");
        var ocnum=eval("document.all."+idset[i]+"ocurNum.value");
        var pfnum=document.all.pfNum.value;
        
        if(document.all.pfid.value!='2_xianzhichu'){
            if(parseInt(ocnum)<parseInt(pfnum)){
                alert(yNo+" 派发数量超过易耗品的库存数量！");
                return;
            }                
        }
    }
    
	yhpdispatchForm.action="yhpdispatchAction.do?method=dispatch&idset="+idset+"&idcount="+idcount;
	yhpdispatchForm.submit();
}

}

function DoBack(){   
   yhpdispatchForm.action="yhpdispatchAction.do?method=search4List&listNum='all'";
   yhpdispatchForm.submit();
}
</script>
