<%@page pageEncoding="GBK"%>
<%@include file = "../tiles/include.jsp"%>

<body onload="init()">
<center>

<html:form action = "stuBmAction.do?method=stuinfoview">
<html:errors/>
<br>
<table width="60%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">考生个人信息</font></strong></td>
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
									学号
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
									姓名
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="stuName"/>					    
								</td>
							</tr>															
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									性别
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="gender"/>					    
								</td>
							</tr>
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									入学年份
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="enrollYear"/>					    
								</td>
							</tr>
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									学院
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="deptName"/>					    
								</td>
							</tr>
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									专业
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="2">
									<bean:write name="nl" property="majorName"/>					    
								</td>
							</tr>
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									年级
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="2">
									<bean:write name="nl" property="curGrade"/>					    
								</td>
							</tr>		
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									班级
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="2">
									<bean:write name="nl" property="curClass"/>					    
								</td>
							</tr>	
							<tr align="center" valign="middle">							
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									证件类型
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="2">
									<bean:write name="nl" property="idType"/>								    
								</td>
							</tr>
							<tr align="center" valign="middle">	
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									证件号码
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="2">
									<bean:write name="nl" property="idCard"/>								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
									电子邮件
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
      <font size="2.5" color="red">请考生务必<b>确认证件号码</b>正确与否。若不正确，请点击<b>修改个人信息</b>进行修改。</font>
    </td>
  </tr>
  <tr> 
    <td height="40" align="center" valign="middle">
      <input name="bupdate" type="button" class="button_nor2" value="修改个人信息" onclick="DoUpdate()">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
      <input name="bviewbm" type="button" class="button_nor2" value="已报考信息查看" onclick="DoViewBm()">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
      <input name="bbm" type="button" class="button_nor2" value="考试网上报名" onclick="DoBm()">
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
        alert("保存成功！");
    else if(document.all.hmsg.value=='1')
        alert("保存失败！");
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