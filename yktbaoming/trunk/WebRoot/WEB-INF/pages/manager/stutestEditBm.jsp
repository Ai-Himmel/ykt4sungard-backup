<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>
<script type="text/javascript" src="<c:url value='/pages/datepicker/WdatePicker.js'/>"></script>

<body onload="init()">
<center>

<html:form action = "studentAction.do?method=search4List">
<html:errors/>
<br>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">考生数据修改</font></strong></td>
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
         <logic:present name="stubmlist" scope="request">
         <logic:iterate name="stubmlist" id="nl" type="java.util.Map"  indexId="i" length="1">     
         <input name="stubmId" type="hidden" value="<bean:write name="nl" property="id"/>">
                            <tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									学号
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="studentNo"/>
									<input name="studentNo" type="hidden" value="<bean:write name="nl" property="studentNo"/>">
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									姓名
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="stuName"/>					    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									性别
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="gender"/>			    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									入学年份
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="enrollYear"/>								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									学院名称
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="deptName"/>								    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									专业名称
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="majorName"/>							    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									年级
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="curGrade"/>							    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									班级
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="curClass"/>							    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									证件类型
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="idType"/>								    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									证件号码
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="idCard"/>								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									电子邮件
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<bean:write name="nl" property="email"/>	    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									选择考试
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<select name="s_testId" class="select01">
									<option value="" >请选择</option>
									<logic:present name="testlist" scope="request">
                                        <logic:iterate name="testlist" id="ml" type="java.util.Map">
                                        <option value="<bean:write name="ml" property="id"/>"><bean:write name="ml" property="testInfo"/></option>
                                        </logic:iterate>
                                    </logic:present>									
								</select>
								<input name="testId" type="hidden"  value="<bean:write name="nl" property="testId"/>">								    
								</td>
							</tr>           
        </logic:iterate>
        </logic:present>
       </tbody>
      </table></td>
  </tr>
  <tr> 
    <td height="40" align="right" valign="middle"> 
      <input name="Submit" type="button" class="button_nor" value="保 存" onClick="DoCheck()"> 
      &nbsp;&nbsp;&nbsp;
      <input name="cancel" type="submit" class="button_nor" value="取 消">
    </td>
  </tr>
  <tr> 
    <td height="40" align="left" valign="middle"> 
      <font size="2.5" color="red">注：该考生已参加过报名，不能修改其基本信息。</font>
    </td>
  </tr>
</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>

<input type="hidden" name="pager.offset" value="<%=request.getParameter("pager.offset")%>"/>
<html:hidden property="search_studentno" />
<html:hidden property="search_stuname" />
<html:hidden property="search_deptname" />
<html:hidden property="search_majorname" />
<html:hidden property="search_curgrade" />
<html:hidden property="search_curclass" />
<html:hidden property="search_idtype" />
<html:hidden property="search_idcard" />
<html:hidden property="search_testcatname" />
<html:hidden property="search_testid" />
<html:hidden property="search_ifbm" />
<html:hidden property="search_ifpay" />
</html:form>
</center>
</body>

<script language="JavaScript">

function init(){

    var tid;
    tid=document.all.testId.value;
    for(var i=0;i<document.all.s_testId.length;i++){
            if(document.all.s_testId.options[i].value==tid){
                document.all.s_testId.options[i].selected=true;
                break;
            }        
    }
        
    if(document.all.hmsg.value=='1')
        alert("保存失败！");
    else if(document.all.hmsg.value=='22')
        alert("该考生已有此考试，保存失败！");   
}

function DoCheck(){

  document.all.testId.value=document.all.s_testId.value;
  if(document.all.testId.value==''){
      alert("请选择考试！");      
      return; 
   }
  
  document.studentForm.action="studentAction.do?method=updateBm";
  document.studentForm.submit();     
}

</script>