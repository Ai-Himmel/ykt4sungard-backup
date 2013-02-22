<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<body onload="init()">
<center>
<% String  uid = "";
  if(request.getAttribute("uid")!=null){
  	uid =  request.getAttribute("uid").toString(); 
  }

%>
	<html:form action="studentAction.do?method=search4List">
	    
		<html:errors />
		<br>
		<table width="90%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"> 考生数据添加</font></strong>
				</td>    
			</tr>
			<tr>
				<td align="center" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width="100%" border="1" align="center" cellpadding="1" cellspacing="0" bordercolor="#FFFFFF" id="submenu1">
					
						<tbody>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									学号
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.studentNo"/>
									<input name="studentNo" type="hidden" value="<bean:write name="studentForm" property="bmStudent.studentNo"/>">
								    <input type="hidden" name="uid" value="<%=uid%>" />
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									姓名
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.stuName"/>								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									性别
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.gender"/>				    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									入学年份
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.enrollYear"/>							    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									学院名称
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.deptName"/>							    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									专业名称
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.majorName"/>							    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									年级
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.curGrade"/>						    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									班级
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.curClass"/>				    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									证件类型
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.idType"/>						    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									证件号码
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.idCard"/>	    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									电子邮件
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<bean:write name="studentForm" property="bmStudent.email"/>				    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									选择考试
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<select name="testId" class="select01">
									<option value="" >请选择</option>
									<logic:present name="testlist" scope="request">
                                        <logic:iterate name="testlist" id="ml" type="java.util.Map">
                                        <option value="<bean:write name="ml" property="id"/>"><bean:write name="ml" property="testInfo"/></option>
                                        </logic:iterate>
                                    </logic:present>									
								</select>								    
								</td>
							</tr>					
						</tbody>
					</table>
				</td>
			</tr>
			<tr>
				<td height="40" align="right" valign="middle">
					<input name="Submit" type="button" class="button_nor" value="保 存" onClick="DoCheck()">
					&nbsp;&nbsp;&nbsp;
                    <input name="cancel" type="submit" class="button_nor" value="取 消">
				</td>
			</tr>
		</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>
	</html:form>
</center>
</body>

<script language="JavaScript">

function init(){
    
    if(document.all.hmsg.value=='1')
        alert("保存失败！");
    else if(document.all.hmsg.value=='2')
        alert("该考生的此考试类别已存在，保存失败！");
}

function DoCheck(){
       
   if(document.all.testId.value==''){
      alert("请选择考试！");      
      return; 
   }
         
   document.studentForm.action="studentAction.do?method=addtest";
   document.studentForm.submit();     
}

</script>
