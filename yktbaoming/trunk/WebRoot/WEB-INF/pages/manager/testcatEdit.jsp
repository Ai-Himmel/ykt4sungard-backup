<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<body onload="init()">
<center>

<html:form action = "testCategoryAction.do?method=search4List">
<html:errors/>
<br>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">考试类别修改</font></strong></td>
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
         <logic:present name="testcatlist" scope="request">
         <logic:iterate name="testcatlist" id="nl" type="java.util.Map"  indexId="i" length="1">     
         <input name="bmTestCat.id" type="hidden" value="<bean:write name="nl" property="id"/>">
         <tr align="center" valign="middle">							
            <td width="15%" align="left" valign="middle" class="tableHeader2">
				考试类别名称
			</td>
			<td align="left" valign="middle" class="tableHeader3" colspan="3">
				<input name="bmTestCat.testCatName" style="height:18px; width:480px; border:#000000 solid 1px; margin:0px; padding:0px; FONT-SIZE:12px" maxlength="30" value="<bean:write name="nl" property="testCatName"/>">								    
			</td>
		 </tr>
		 <tr align="center" valign="middle">							
			<td width="15%" align="left" valign="middle" class="tableHeader2">
				是否收费
			</td>
			<td align="left" valign="middle" class="tableHeader3" colspan="3">
			<c:if test="${nl.ifFee == '1'}">
				<input name="bmTestCat.ifFee" type="radio" value="1" onclick="DoChange(this)" checked>收费&nbsp;
				<input name="bmTestCat.ifFee" type="radio" value="0" onclick="DoChange(this)">不收费																    
			</c:if>
			<c:if test="${nl.ifFee== '0'}">
				<input name="bmTestCat.ifFee" type="radio" value="1" onclick="DoChange(this)">收费&nbsp;
				<input name="bmTestCat.ifFee" type="radio" value="0" onclick="DoChange(this)" checked >不收费																    
			</c:if>
			</td>								
		</tr>
		<tr id="feetr" align="center" valign="middle">	
			<td width="15%" align="left" valign="middle" class="tableHeader2">
				收费标准
			</td>
			<td align="left" valign="middle" class="tableHeader3" colspan="3">
				<input name="bmTestCat.fee" class="input_box" value="<bean:write name="nl" property="fee"/>" maxlength="6">								    
			</td>
		</tr>
		<tr align="center" valign="middle">							
			<td width="15%" align="left" valign="middle" class="tableHeader2">
				是否使用
			</td>
			<td align="left" valign="middle" class="tableHeader3" colspan="3">
			<c:if test="${nl.state == '1'}">			
				<input name="bmTestCat.state" type="radio" value="1" checked>使用&nbsp;
				<input name="bmTestCat.state" type="radio" value="0">不使用
		    </c:if>
		    <c:if test="${nl.state == '0'}">			
				<input name="bmTestCat.state" type="radio" value="1" >使用&nbsp;
				<input name="bmTestCat.state" type="radio" value="0" checked>不使用
		    </c:if>															    
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
</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>

<input type="hidden" name="pager.offset" value="<%=request.getParameter("pager.offset")%>"/>
<html:hidden property="search_testcatname" />

</html:form>
</center>
</body>

<script language="JavaScript">

function init(){
    for(var i=0;i<document.forms[0].elements["bmTestCat.ifFee"].length;i++)   {   
        if(document.forms[0].elements["bmTestCat.ifFee"][i].checked&&document.forms[0].elements["bmTestCat.ifFee"][i].value=='0'){   
            document.forms[0].elements["bmTestCat.fee"].value='0';    
            feetr.style.display='none';
            break;   
        }   
    }   
    
    if(document.all.hmsg.value=='1')
        alert("保存失败！");
    else if(document.all.hmsg.value=='2')
        alert("已存在此考试类别名称，保存失败！");
}

function DoChange(rdo){
    if(rdo.value=='0'){
        document.forms[0].elements["bmTestCat.fee"].value='0';    
        feetr.style.display='none';
    }
    else if(rdo.value=='1'){
        feetr.style.display='';
    }   
}

function DoCheck(){

  if(document.forms[0].elements["bmTestCat.testCatName"].value==''){
      alert("请输入考试类别名称！");  
      document.forms[0].elements["bmTestCat.testCatName"].focus();
      return; 
   }
   if(document.forms[0].elements["bmTestCat.fee"].value!=''){
    if(isNaN(document.forms[0].elements["bmTestCat.fee"].value)){
      alert("收费标准应为数值！");
      document.forms[0].elements["bmTestCat.fee"].focus();
      document.forms[0].elements["bmTestCat.fee"].select();
      return;
    } 
    if(parseFloat(document.forms[0].elements["bmTestCat.fee"].value)<0){
      alert("收费标准不能为负数！");
      document.forms[0].elements["bmTestCat.fee"].focus();
      document.forms[0].elements["bmTestCat.fee"].select();
      return;
    }   
  }
  
  document.testCatForm.action="testCategoryAction.do?method=update";
  document.testCatForm.submit();     
}

</script>