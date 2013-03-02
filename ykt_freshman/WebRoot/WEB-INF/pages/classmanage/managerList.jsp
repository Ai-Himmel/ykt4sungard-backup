<%@page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>

<script language="JavaScript">
function clearAll(){
	document.all("managermodel.managerNo").value="";
	document.all("managermodel.managerName").value="";
	document.all("managermodel.gender").value="";
	document.all("leader").checked=false;
	document.all("assistant").checked=false;
	document.all("tutor").checked=false;
	document.all("teacher").checked=false;
	document.all("available1").value="";	
	
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
</script>

<% String msg=(String)request.getAttribute("msg");
if(msg!=null)
{
%>
<script language="javascript">
	alert('<%=msg%>');
</script>
<%}%>

<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" >
	<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium"><bean:message bundle="classmanage" key="manager.managermanage" /></font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="middle">
				&nbsp;
			</td>
		</tr>

		<tr>
			<td align="center" valign="top">
				<html:form action="managerAction.do?method=load4Search">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
						<tr>
							<td>
								<INPUT type="hidden" name="export" value="">
							</td>
						</tr>
						<tbody>
							<tr align="center" valign="middle">
								<td  height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<bean:message bundle="classmanage" key="manager.no" />
								</td>
								<td  align="left" valign="middle" class="tableHeader3">
									<html:text property="managermodel.managerNo" styleClass="input_box" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();" />
								</td>
								<td  align="left" valign="middle" class="tableHeader2">
									<bean:message bundle="classmanage" key="manager.name" />
								</td>
								<td  align="left" valign="middle" class="tableHeader3">
									<html:text property="managermodel.managerName" styleClass="input_box" maxlength="20" onkeydown="if(event.keyCode==13) document.onkeydown();"  />
								</td>
							</tr>
							<tr align="center" valign="middle">
								<td  align="left" valign="middle" class="tableHeader2">
									<bean:message bundle="classmanage" key="manager.gender" />
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="managermodel.gender">
										<html:option value="">----------</html:option>
										<html:options collection="genderList" labelProperty="dictCaption" property="id.dictValue" />
									</html:select>
								</td>
								<!--<td  align="left" valign="middle" class="tableHeader2">
									<bean:message bundle="classmanage" key="manager.school" />
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="managermodel.schoolId">
										<html:option value="">-----------------------</html:option>
										<html:options collection="schoolList" labelProperty="schoolName" property="schoolId" />
									</html:select>
								</td>-->
								<td  align="left" valign="middle" class="tableHeader2">
									<bean:message bundle="classmanage" key="manager.available" />
								</td>								
								<td align="left" valign="middle" class="tableHeader3" >
									<html:select styleClass="select01" property="available1">
										<html:option value="">----------</html:option>
										<html:option value="1">是</html:option>
										<html:option value="0">否</html:option>										
									</html:select>
								</td>																
							</tr>							
							<tr align="center" valign="middle">
								<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<bean:message bundle="classmanage" key="manager.duties" />
								</td>
								<td colspan="5" align="left" valign="middle" class="tableHeader3">
									<table border="0" cellspacing="0" cellpadding="0">
										<tr align="center" valign="middle">
											<td width="25">
												<html:checkbox property="leader" value="11" />
											</td>
											<td width="80" align="left">
												<bean:message bundle="classmanage" key="manager.leader" />
											</td>
											<td width="25">
												<html:checkbox property="assistant" value="21" />
											</td>
											<td width="45" align="left">
												<bean:message bundle="classmanage" key="manager.assistant" />
											</td>
											<td width="25" align="center">
												<html:checkbox property="tutor" value="22" />
											</td>
											<td width="40" align="left">
												<bean:message bundle="classmanage" key="manager.tutor" />
											</td>
											<td width="25" align="center">
												<html:checkbox property="teacher" value="01" />
											</td>
											<td width="42" align="left">
												<bean:message bundle="classmanage" key="manager.teacher" />
											</td>
										</tr>
									</table>
								</td>
							</tr>

						</tbody>
					</table>					
					<tr>
						<td height="40" align="right" valign="middle" class="tdborder02">
							<html:submit property="search" styleClass="button_nor" onclick="javascript:NotExport();">
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
			<td height="20" align="left" valign="middle" class="medium">
				<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
			</td>
		</tr>

		<tr>
			<td height="40" align="center" valign="top">
				<html:form action="managerAction.do?method=delete">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
						<tbody><input type="hidden" name="updateid" value="">
							<tr align="center" valign="middle">
							
								<td width="24" height="24" valign="middle" class="tableHeader">
								 <logic:present name="managermodels" scope="request">
									<input type="checkbox" name="checkall" onClick="DoCheckall(this)">
								 </logic:present>
								 <logic:notPresent name="managermodels" scope="request">&nbsp;
								 </logic:notPresent>
								</td>
								
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="manager.no" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="manager.name" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="manager.gender" />
								</td>
								<!--<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="manager.school" />
								</td>-->								
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="manager.managerOrg" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="manager.managerType" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="manager.contact" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="manager.duties" />
								</td>
								<td valign="middle" class="tableHeader">
									<bean:message bundle="classmanage" key="manager.available" />
								</td>								

							</tr>
							<logic:present name="managermodels" scope="request">
								<%int itemNo = ((Integer) request.getAttribute("managerCount"))
					.intValue();%>
								<pg:pager url="./managerAction.do" items="<%=itemNo%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%=true%>" export="offset,currentPageNumber=pageNumber" scope="request">
									<%-- keep track of preference --%>
									<pg:param name="method" />
									<pg:param name="managermodel.managerNo" />
									<pg:param name="managermodel.managerName" />
									<pg:param name="managermodel.gender" />
									<!-- <pg:param name="managermodel.schoolId" />	 -->								
									<pg:param name="leader" />
									<pg:param name="assistant" />
									<pg:param name="tutor" />
									<pg:param name="teacher" />
									<pg:param name="page" />
									<pg:param name="orderby" />
									<pg:param name="sort" />
									<pg:param name="available1" />

									<%-- save pager offset during form changes --%>
									<input type="hidden" name="pager.offset" value="<%= offset %>">

									<logic:iterate name="managermodels" id="managerwithrole" indexId="i">
										<pg:item>
											<c:if test="${i%2 == 0}">
												<tr align="center" valign="middle">												
													<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
														<input type="checkbox" name="cbgroup" value="<bean:write name="managerwithrole" property="managerId"/>" onClick="DoSelect(this)">
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<a href="managerAction.do?method=load4Edit&managerId=<bean:write name="managerwithrole" property="managerId"/>"><bean:write name="managerwithrole" property="managerNo" /></a>
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="managerwithrole" property="managerName" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="managerwithrole" property="gender" />
														&nbsp;
													</td>
													<!--<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="managerwithrole" property="schoolId" />
														&nbsp;
													</td>	-->												
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="managerwithrole" property="managerOrg" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="managerwithrole" property="managerType" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="managerwithrole" property="contact" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<bean:write name="managerwithrole" property="roleName" />
														&nbsp;
													</td>
													<td align="center" valign="middle" bgcolor="#FFFFFF">
														<c:if test="${managerwithrole.available== '0'}">	
															否

														</c:if>	
														<c:if test="${managerwithrole.available== '1'}">	
															是

														</c:if>		
														&nbsp;	
													</td>														
												</tr>
											</c:if>
											<c:if test="${i%2 != 0}">
												<tr align="center" valign="middle" bgcolor="#F6F4F5">
													<td height="24" align="center" valign="middle">
														<input type="checkbox" name="cbgroup" value="<bean:write name="managerwithrole" property="managerId"/>" onClick="DoSelect(this)">
													</td>
													<td align="center" valign="middle">
														<a href="managerAction.do?method=load4Edit&managerId=<bean:write name="managerwithrole" property="managerId"/>"><bean:write name="managerwithrole" property="managerNo" /></a>
													</td>
													<td align="center" valign="middle">
														<bean:write name="managerwithrole" property="managerName" />
														&nbsp;
													</td>
													<td align="center" valign="middle">
														<bean:write name="managerwithrole" property="gender" />
														&nbsp;
													</td>
													<!--<td align="center" valign="middle">
														<bean:write name="managerwithrole" property="schoolId" />
														&nbsp;
													</td>	-->												
													<td align="center" valign="middle">
														<bean:write name="managerwithrole" property="managerOrg" />
														&nbsp;
													</td>
													<td align="center" valign="middle">
														<bean:write name="managerwithrole" property="managerType" />
														&nbsp;
													</td>
													<td align="center" valign="middle">
														<bean:write name="managerwithrole" property="contact" />
														&nbsp;
													</td>
													<td align="center" valign="middle">
														<bean:write name="managerwithrole" property="roleName" />
														&nbsp;
													</td>
													<td align="center" valign="middle">
														<c:if test="${managerwithrole.available== 0}">	
															否

														</c:if>	
														<c:if test="${managerwithrole.available== 1}">	
															是

														</c:if>		
														&nbsp;	
													</td>														
												</tr>
											</c:if>
										</pg:item>
									</logic:iterate>
									<jsp:include page="./page.jsp" flush="true" />
								</pg:pager>
							</logic:present>
						</tbody>
					</table>
  <tr> 
    <td height="40" align="left" valign="middle">
        <%
        int rowcount=0;
        if(request.getAttribute("listcount")!=null){
        	rowcount=((Integer)request.getAttribute("listcount")).intValue();
        %>       
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
        <%} %>
    </td>
  </tr>					
					<tr>
						<td height="30" align="right" valign="middle">
						<logic:present name="managermodels" scope="request">
							<html:button property="notonseat" styleClass="button_nor" onclick="DoUpdate('0')">
								不在任
							</html:button>
							<html:button property="onseat" styleClass="button_nor" onclick="DoUpdate('1')">
								在 任
							</html:button>	
						</logic:present>						
							<html:submit property="add" styleClass="button_nor" onclick="document.forms[1].action='managerAction.do?method=load4Add'">
								<bean:message key="button.add" />
							</html:submit>
						</td>
					</tr>
  <logic:present name="updatemsg" scope="request">
  <input name="hupdatemsg" type="hidden" value="<bean:write name="updatemsg" />"> 
  </logic:present>
  <logic:notPresent name="updatemsg" scope="request">
  <input name="hupdatemsg" type="hidden" value=""> 
  </logic:notPresent>
				</html:form>
			</td>
		</tr>
	</table>
</body>
<script language="JavaScript">

setTimeout('DoInit()',30);

function DoInit(){
    
  if(document.all.hupdatemsg.value=='0')
      alert("保存成功!");
  else if(document.all.hupdatemsg.value=='1')
      alert("保存失败!");
}
	 
function DoUpdate(str){

   if(document.all.updateid.value==""){
        alert("请选择要进行批量更改在任状态的管理人员记录！");
        return;
   }
   
   document.forms[1].action="managerAction.do?method=changeOnSeatState&ifonseat="+str;
   document.forms[1].submit();
  
}
	 
	 function DoSelect(cb){

   var sflag=1;;
   var usflag=1;;
  
   if(cb.checked){
   
       document.all.updateid.value=cb.value;
       //alert(document.all.updateid.value);

       if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(!document.all.cbgroup[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall.checked=true;
          }
       } 
   }
   
   if(!cb.checked){
       document.all.checkall.checked=false;
       if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall.checked=false;
              document.all.updateid.value="";
          }
       } 
   }
   
}

function DoCheckall(ckall){
   
   if(ckall.checked){
   
      if(document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=true;
       }
       document.all.updateid.value=document.all.cbgroup[document.all.cbgroup.length-1].value;
       }
       else{
          document.all.cbgroup.checked=true;
          document.all.updateid.value =document.all.cbgroup.value;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.cbgroup.length>1){
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=false;
       }
       document.all.updateid.value="";
      }
      else{
         document.all.cbgroup.checked=false;
         document.all.updateid.value="";
      }
   }
   //alert(document.all.updateid.value);

}
	 
	 
	 
	 
	 function DoExport(){
	 	document.all("export").value='export';
	 	document.forms[0].submit();
	 }
	 function NotExport(){
	 	document.all("export").value='';
	 }
	 
	 
	 function my_onload(){
	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	 }
	 
	 window.onload=my_onload;	 
</script>
