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
					<strong><font class="medium"> �����������</font></strong>
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
									ѧ��
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.studentNo"/>
									<input name="studentNo" type="hidden" value="<bean:write name="studentForm" property="bmStudent.studentNo"/>">
								    <input type="hidden" name="uid" value="<%=uid%>" />
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									����
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.stuName"/>								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�Ա�
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.gender"/>				    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									��ѧ���
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.enrollYear"/>							    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									ѧԺ����
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.deptName"/>							    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									רҵ����
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.majorName"/>							    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�꼶
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.curGrade"/>						    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�༶
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.curClass"/>				    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									֤������
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.idType"/>						    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									֤������
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="studentForm" property="bmStudent.idCard"/>	    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�����ʼ�
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<bean:write name="studentForm" property="bmStudent.email"/>				    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									ѡ����
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<select name="testId" class="select01">
									<option value="" >��ѡ��</option>
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
					<input name="Submit" type="button" class="button_nor" value="�� ��" onClick="DoCheck()">
					&nbsp;&nbsp;&nbsp;
                    <input name="cancel" type="submit" class="button_nor" value="ȡ ��">
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
        alert("����ʧ�ܣ�");
    else if(document.all.hmsg.value=='2')
        alert("�ÿ����Ĵ˿�������Ѵ��ڣ�����ʧ�ܣ�");
}

function DoCheck(){
       
   if(document.all.testId.value==''){
      alert("��ѡ���ԣ�");      
      return; 
   }
         
   document.studentForm.action="studentAction.do?method=addtest";
   document.studentForm.submit();     
}

</script>
