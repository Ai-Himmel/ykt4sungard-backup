<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "noticeAction.do?method=load4edit">
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
          <logic:iterate name="noticelist" id="nl" type="java.util.Map"  indexId="i">     
          <input name="updateid" type="hidden" value="<bean:write name="nl" property="id"/>">
          <tr align="center" valign=center style="display:none">             
             <input name="notice.noticeNo" type="hidden" value="0000">
            <td width=5% align="left" valign="middle" class="tableHeader2" >公告标题</td>
            <td width=40% align="left" valign="middle" class="tableHeader3" colspan="3">
                 <input 
                name="notice.title" style="height:18px; width:480px; border:#000000 solid 1px; margin:0px; padding:0px; FONT-SIZE:12px" maxlength=50 value="logintext">
                &nbsp;&nbsp;
                <c:choose><c:when test="${nl.ifDeleted == '0'}">
                  <input name="notice.ifDeleted" type="radio" value="0" checked>
                  </c:when><c:otherwise> 
                  <input name="notice.ifDeleted" type="radio" value="0">
                  </c:otherwise></c:choose> 
                     公开&nbsp;
                  <c:choose><c:when test="${nl.ifDeleted == '1'}">
                  <input type="radio" name="notice.ifDeleted" value="1" checked> 
                  </c:when><c:otherwise>
                  <input type="radio" name="notice.ifDeleted" value="1">
                  </c:otherwise></c:choose>登录可见                
            </td>
          </tr>  
          <tr align="center" valign=center>             
            <td colspan="4" align="left" valign="middle" class="tableHeader3" >
            <textarea name="notice.body" style="width:1px;height:1px;" onfocus="editor.HtmlEdit.focus();"><bean:write name="nl" property="body"/></textarea >
            <iframe ID="editor" src="editor.do" frameborder="0" scrolling=no width="100%" height="405"></iframe>
            </td>
          </tr>
          <input type="hidden" name="notice.creatorId" value="<%=(String)session.getAttribute("personName")%>">          
          <input type="hidden" name="notice.updatorId" value="<%=(String)session.getAttribute("personName")%>">          
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
  editor.HtmlEdit.document.body.innerHTML =document.forms[0].elements["notice.body"].value;
  
  if(document.all.hmsg.value=='0')
      alert("保存成功！");
  else if(document.all.hmsg.value=='d0')
      alert("删除成功！");
}
//setTimeout('loadEditor()',10);  

function DoCheck(){
    
  if (editor.EditMode.checked==true)
	  document.forms[0].elements["notice.body"].value=editor.HtmlEdit.document.body.innerText;
  else
	  document.forms[0].elements["notice.body"].value=editor.HtmlEdit.document.body.innerHTML;  
  
  document.noticeForm.action="noticeAction.do?method=edit";
  document.noticeForm.submit();     
}

function DoDelete(){
 if(confirm("您确定要删除吗？")){
     document.noticeForm.action="noticeAction.do?method=del";
     document.noticeForm.submit(); 
 }
 else
  return;
}
window.onload=loadEditor;
</script>