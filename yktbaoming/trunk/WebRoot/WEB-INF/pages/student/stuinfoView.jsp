<%@page pageEncoding="GBK"%>
<%@include file = "../tiles/include.jsp"%>

<body onload="init()">
<center>

<html:form action = "stuBmAction.do?method=stuinfoview">
<html:errors/>
<br>
<table width="60%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">����������Ϣ</font></strong></td>
  </tr>
  <tr>
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top" >    
    <table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
        <tbody>
         <logic:present name="stuinfolist" scope="request">
         <logic:iterate name="stuinfolist" id="nl" type="java.util.Map"  indexId="i" length="1">         
                            <tr align="center" valign="middle">							
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									ѧ��
								</td>
								<td width="65%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="studentNo"/> 
									<input name="studentNo" type="hidden" value="<bean:write name="nl" property="studentNo"/>">								    
								</td>
								<td align="left" valign="middle" class="tableHeader3" rowspan="5">
								    <logic:present name="cutId" scope="request">
                                        <img src="/baoming/ecardimage?cutId=<%=request.getAttribute("cutId")%>" height="110">                                        
                                    </logic:present>    
								</td>
							</tr>							
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									����
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="stuName"/>					    
								</td>
							</tr>															
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									�Ա�
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="gender"/>					    
								</td>
							</tr>
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									��ѧ���
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="enrollYear"/>					    
								</td>
							</tr>
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									ѧԺ
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="deptName"/>					    
								</td>
							</tr>
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									רҵ
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="2">
									<bean:write name="nl" property="majorName"/>					    
								</td>
							</tr>
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									�꼶
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="2">
									<bean:write name="nl" property="curGrade"/>					    
								</td>
							</tr>		
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									�༶
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="2">
									<bean:write name="nl" property="curClass"/>					    
								</td>
							</tr>	
							<tr align="center" valign="middle">							
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									֤������
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="2">
									<bean:write name="nl" property="idType"/>								    
								</td>
							</tr>
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									֤������
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="2">
									<bean:write name="nl" property="idCard"/>								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									�����ʼ�
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="2">
									<bean:write name="nl" property="email"/>	    
								</td>
							</tr>												          
        </logic:iterate>
        </logic:present>
       </tbody>
      </table></td>
  </tr>
  <tr> 
    <td height="40" align="center" valign="middle">
      <font size="2.5" color="red">�뿼�����<b>ȷ��֤������</b>��ȷ���������ȷ������<b>�޸ĸ�����Ϣ</b>�����޸ġ�</font>
    </td>
  </tr>
  <tr> 
    <td height="40" align="center" valign="middle">
      <input name="bupdate" type="button" class="button_nor2" value="�޸ĸ�����Ϣ" onclick="DoUpdate()">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
      <input name="bviewbm" type="button" class="button_nor2" value="�ѱ�����Ϣ�鿴" onclick="DoViewBm()">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
      <input name="bbm" type="button" class="button_nor2" value="�������ϱ���" onclick="DoBm()">
    </td>
  </tr>  
</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>
<input name="giveAlert" type="hidden" value="<%=(String)session.getAttribute("giveAlert")%>">
</html:form>
</center>
</body>

<script language="JavaScript">

function init(){
           
    if(document.all.hmsg.value=='0')
        alert("����ɹ���");
    else if(document.all.hmsg.value=='1')
        alert("����ʧ�ܣ�");
}

function DoUpdate(){
  
  document.studentForm.action="stuBmAction.do?method=load4stuinfoupdate";
  document.studentForm.submit();     
}

function DoViewBm(){
  
  document.studentForm.action="stuBmAction.do?method=search4stuBmListview";
  document.studentForm.submit();     
}

function DoBm(){
  
  document.studentForm.action="stuBmAction.do?method=search4stuBmList";
  document.studentForm.submit();     
}

</script>