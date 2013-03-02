<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.DictionaryId"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.classmanage.web.help.StudentWithAllInfo"%>
<%@ page import="java.util.Map"%>
<%@ page import="java.util.HashMap"%>
<%@ include file="../tiles/include.jsp"%>

<SCRIPT language=javascript>

function tianjia(){
    graduateTypeSearchForm.action = "<c:url value="/graduateTypeBillAction.do"/>?method=loadGraduateTypeInfo";
	graduateTypeSearchForm.submit();
}
function doSearch(){
    graduateTypeSearchForm.action = "<c:url value="/graduateTypeAction.do"/>?method=loadDormTypeList";
	graduateTypeSearchForm.submit();
}
function clean(){
	document.graduateTypeSearchForm.elements["graduateTypeSearch"].value="";
}
function doModify(){
	var sflag = 0;
	if(document.all.itemList!=undefined){
	if(document.all.itemList.checked==true){
		graduateTypeSearchForm.action = "<c:url value="/graduateTypeBillAction.do"/>?method=loadGraduateTypeInfo";
		graduateTypeSearchForm.submit();
	}else{
		  for(var i=0;i<document.all.itemList.length;i++){
              if(document.all.itemList[i].checked){
                   sflag=sflag+1;                                                  
              }
          }
          if(sflag>1){
              alert("只能选择一条做修改!");
              return;
          }else if(sflag<1){
          	  alert("请选择一条要修改记录！");
          }else{    
			  graduateTypeSearchForm.action = "<c:url value="/graduateTypeBillAction.do"/>?method=loadGraduateTypeInfo";
			  graduateTypeSearchForm.submit();
          }
	}
	}else{
		alert('当前无记录!');
	}
}
function doDelete(){
var sflag = 0;
	if(document.all.itemList!=null){
	  if(document.all.itemList.length>1){
	      for(var i=0;i<document.all.itemList.length;i++){
              if(document.all.itemList[i].checked){
                   sflag=sflag+1;                                                  
              }
          }
          if(sflag<1){
              alert("请选择要删除的记录!");
              return;
          }
     }
     else{
         if(!document.all.itemList.checked){
              alert("请选择要删除的记录！");
              return;        
        }
     }
	    if(confirm('该研究生住宿类别也许已经被使用，删除该研究生住宿类别，可能会影响到某些的研究生信息的完整性，确定删除吗？')){
    		graduateTypeSearchForm.action = "<c:url value="/graduateTypeAction.do"/>?method=deleteDormTypeInfo";
			graduateTypeSearchForm.submit();
		}
	}else{
		alert("当前无记录！");
	}
}
	 function my_onload(){	 	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		} 	
	 }
	 window.onload=my_onload;
</SCRIPT>
<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">

  <html:form action="/graduateTypeAction" method="post">
    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">研究生住宿管理类别维护</font></strong></td>
    </tr>
    <tr> 
      <td align="center" valign="top" height="10"></td>
    </tr>
    <tr> 
      <td align="center" valign="top" >
	  <table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#ffffff id=submenu1>
          <tbody>
          
            <tr align="center" valign=center> 
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><span class="medium">研究生类型</span></td>
              <td align="left" valign="middle" class="tableHeader3" >
     
              <html:text property="graduateTypeSearch" styleClass="input_box" maxlength="30"/>
              &nbsp;
              <input name="Submit" type="button" class="button_nor" value="查询" onClick="javascript:doSearch();">
              &nbsp;&nbsp;
              <input name="Submit22" type="button" class="button_nor" value="重置" onClick="javascript:clean();">
              </td>            
            </tr>

          </tbody>
        </table></td>
    </tr>
    
    <tr> 
      <td height="10" align="center" valign="middle" class="medium"></td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
            <tr align="center" valign=center> 
              <td width="30" valign="middle" class="tableHeader" >&nbsp;</td>
              <td height="24" valign="middle" class="tableHeader" >研究生类型</td>
              <td valign="middle" class="tableHeader" >更新人</td>
              <td valign="middle" class="tableHeader" >更新时间</td>
            </tr>
            				<logic:present name="graduateTypeList" scope="request">
								<logic:iterate name="graduateTypeList" id="GraduateType">
									<tr align="center" valign="middle">
										<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
											<input type="checkbox" name="itemList" value="<bean:write name="GraduateType" property="id"/>">
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="GraduateType" property="graduateType" />&nbsp;
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="GraduateType" property="updator" />&nbsp;
											&nbsp;
										</td>
										<td align="center" valign="middle" bgcolor="#FFFFFF">
											<bean:write name="GraduateType" property="updateTime" />&nbsp;
											&nbsp;
										</td>
									</tr>
								</logic:iterate>
							</logic:present>
          </tbody>
        </table></td>
    </tr>
    
    <tr> 
      <td height="30" align="right" valign="middle"> <input name="Submit2" type="button" class="button_nor" value="添加" onClick="javascript:tianjia();"> 
        &nbsp;&nbsp; <input name="Submit22" type="button" class="button_nor" value="修改"  onClick="javascript:doModify();">&nbsp;&nbsp; <input name="Submit22" type="button" class="button_nor" value="删除"  onClick="javascript:doDelete();"></td>
    </tr>
          </html:form>
</table>
</body>
