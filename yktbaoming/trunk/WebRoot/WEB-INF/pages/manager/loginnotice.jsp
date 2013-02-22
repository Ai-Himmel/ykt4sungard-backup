<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "testPublishAction.do?method=load4edit">
<html:errors/>
<br>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">登录页面滚动文本编辑</font></strong></td>
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
         <logic:present name="noticelist" scope="request">
          <logic:iterate name="noticelist" id="nl" type="java.util.Map"  indexId="i" length="1">     
          <input name="bmTestPublish.id" type="hidden" value="<bean:write name="nl" property="id"/>">
          <input name="bmTestPublish.title" type="hidden" value="<bean:write name="nl" property="title"/>">
          <input name="bmTestPublish.ifDisplay" type="hidden" value="9">
          <input name="bmTestPublish.ifPublic" type="hidden" value="9">														
							<tr align="center" valign="middle">							    
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<textarea name="bmTestPublish.body" style="width:1px;height:1px;" onfocus="editor.HtmlEdit.focus();"><bean:write name="nl" property="body"/></textarea>
									<iframe ID="editor" src="editor.do" frameborder="0" scrolling="no" width="100%" height="405"></iframe>																	    
								</td>
							</tr>
							<input type="hidden" name="bmTestPublish.creator" value="<bean:write name="nl" property="creator"/>">
                            <input type="hidden" name="bmTestPublish.createTime" value="<bean:write name="nl" property="createTime"/>">          
          </logic:iterate>
          </logic:present>
        </tbody>
      </table></td>
  </tr>
  <tr> 
    <td height="40" align="right" valign="middle"> 
      <input name="Submit" type="button" class="button_nor" value="保 存" onClick="DoCheck()"> 
      <input name="Bdelete" type="button" class="button_nor" value="删 除" onClick="DoDelete()">           
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

<script language="JavaScript">

function loadEditor(){
  editor.HtmlEdit.document.body.innerHTML =document.forms[0].elements["bmTestPublish.body"].value;
  
  if(document.all.hmsg.value=='0')
      alert("保存成功！");
  else if(document.all.hmsg.value=='d0')
      alert("删除成功！");
}

function DoCheck(){
    
  if (editor.EditMode.checked==true)
	  document.forms[0].elements["bmTestPublish.body"].value=editor.HtmlEdit.document.body.innerText;
  else
	  document.forms[0].elements["bmTestPublish.body"].value=editor.HtmlEdit.document.body.innerHTML;  
  
  document.testPublishForm.action="testPublishAction.do?method=edit";
  document.testPublishForm.submit();     
}

function DoDelete(){
 if(confirm("您确定要删除吗？")){
     document.testPublishForm.action="testPublishAction.do?method=del";
     document.testPublishForm.submit(); 
 }
 else
  return;
}
window.onload=loadEditor;
</script>