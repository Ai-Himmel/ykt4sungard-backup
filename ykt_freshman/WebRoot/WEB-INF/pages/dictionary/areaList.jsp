<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "dictionaryAction.do?method=findareaList">

<br>

<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">У���ֵ�ά��</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <logic:notPresent name="dictlist" scope="request">
  <font size="2.5" color="#990000">��ǰû�п�ά����У����</font>
  </logic:notPresent>  
  
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
           <logic:present name="dictlist" scope="request">
           <thead>
           <tr align="center" valign="middle"> 
              <td align="center" valign="middle" class="tableHeader" >У������</td>
              <td align="center" valign="middle" class="tableHeader" >У������</td>
              <td align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.saveondisk"/></td>
            </tr>             
           </thead>
           <%int j=0;%>
            <logic:iterate name="dictlist" id="cl" type="java.util.Map"  indexId="i">             
            <tr align="center" valign="middle" <%if(j%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>             
              <td height="24" align="center" valign="middle" ><bean:write name="cl" property="dictValue"/></td>
              <td align="center" valign="middle"><input name="dictCaption<bean:write name="cl" property="dictValue"/>" value="<bean:write name="cl" property="dictCaption"/>" maxlength="10"></td>              
              <td align="center" valign="middle">
                <input name="save" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.save"/>" onClick="DoSaveUpdate('<bean:write name="cl" property="dictValue"/>')" >
              </td>     
            </tr>
            <%j = j + 1;%>            
            </logic:iterate>                 
            </logic:present>           
          </tbody>
        </table>
      </td>
  </tr>
  <logic:present name="dictlist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">��<%=rowcount%>����¼</font>
    </td>
    </tr>  
  </logic:present>
  <tr> 
    <td height="40" align="left" valign="middle">
       <input name="dictionaryId.dictNo" type="hidden" value="17"><input name="dictionary.dictName" type="hidden" value="У��">
        У�����룺<input name="dictionaryId.dictValue" value="" maxlength="10">&nbsp;&nbsp;У�����ƣ�<input name="dictionary.dictCaption" value="" maxlength="10">&nbsp;&nbsp;
        <input name="savenew" type="button" class="button_nor" value="���" onClick="DoSaveNew()" >
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
function DoInit(){
  
  if(document.all.hmsg.value=='0')
      alert("����ɹ�!");
  else if(document.all.hmsg.value=='1')
      alert("����ʧ��!");
  else if(document.all.hmsg.value=='2')
      alert("�����ظ�������ʧ��!");    
  else if(document.all.hmsg.value=='9')
      alert("�����ظ����!");
}
window.onload=DoInit;
function DoSaveUpdate(str){
    if(eval("document.all.dictCaption"+str+".value==''")){
        alert("������У�����ƣ�");
        eval("document.all.dictCaption"+str+".focus();");
        return;
    }
    if(confirm("ȷ��Ҫ�޸���")){
        document.dictionaryForm.action="dictionaryAction.do?method=updateArea&dictvalue="+str;
        document.dictionaryForm.submit();
    }
    else
        return;
}

function DoSaveNew(){
   if(document.dictionaryForm.elements["dictionaryId.dictValue"].value==''){
       alert("������У�����룡");
       document.dictionaryForm.elements["dictionaryId.dictValue"].focus();
       return;   
   }
   if(document.dictionaryForm.elements["dictionary.dictCaption"].value==''){
       alert("������У�����ƣ�");
       document.dictionaryForm.elements["dictionary.dictCaption"].focus();
       return;   
   }
   document.dictionaryForm.action="dictionaryAction.do?method=saveArea";
   document.dictionaryForm.submit();
  
}
</script>