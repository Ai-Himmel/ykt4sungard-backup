<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "stuadddelAction.do?method=addstu">
<html:errors/>
<br>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">�������</font></strong></td>
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
          <tr height="30" align="center" valign=center> 
            <td width="15%" align="right" valign="middle" class="tableHeader2">ѧ��</td>
            <td width="85%" align="left" valign="middle" class="tableHeader3" colspan="3">
                <input 
                name="studentNo" class="input_box"  maxlength=50 value="">&nbsp;&nbsp;&nbsp;
                <input name="search" type="button" class="button_nor" value="�鹲���" onClick="DoSearch()"> 
            </td>            
          </tr>         
          <logic:present name="stuinfo" scope="request">            
          <tr height="30" align="center" valign=center>  
            <td width="15%" align="right" valign="middle" class="tableHeader2" >ѧ��</td>
            <logic:iterate name="stuinfo" id="si" type="java.util.Map" length="1">
            <td width="35%" align="left" valign="middle" class="tableHeader3" ><bean:write name="si" property="studentNo"/></td>
            <input type="hidden" name="stuAdddelhis.studentNo" value="<bean:write name="si" property="studentNo"/>">
             </logic:iterate> 
            <td width="15%" align="right" valign="middle" class="tableHeader2" >����</td>
            <logic:iterate name="stuinfo" id="si" type="java.util.Map" length="1">
            <td width="35%" align="left" valign="middle" class="tableHeader3" ><bean:write name="si" property="stuName"/></td>            
             </logic:iterate> 
           </tr> 
           <tr height="30" align="center" valign=center>
            <td width="15%" align="right" valign="middle" class="tableHeader2" >�Ա�</td>
            <logic:iterate name="stuinfo" id="si" type="java.util.Map" length="1">
            <td width="35%" align="left" valign="middle" class="tableHeader3" >
            <c:choose><c:when test="${si.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${si.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
            </td>            
             </logic:iterate>
             <td width="15%" align="right" valign="middle" class="tableHeader2" >רҵ</td>
            <logic:iterate name="stuinfo" id="si" type="java.util.Map" length="1">
            <td width="35%" align="left" valign="middle" class="tableHeader3" >
            <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == si.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
            </td>            
             </logic:iterate>
           </tr> 
           <tr height="30" align="center" valign=center>
            <td width="15%" align="right" valign="middle" class="tableHeader2" >��Դ��</td>
            <logic:iterate name="stuinfo" id="si" type="java.util.Map" length="1">
            <td width="35%" align="left" valign="middle" class="tableHeader3" >
            <logic:present name="arealist" scope="request">            
               <logic:iterate name="arealist" id="al" type="java.util.Map">
                <c:choose><c:when test="${al.dictValue == si.fromProvince}">              
                <bean:write name="al" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
            </td>           
             </logic:iterate>
             <td width="15%" align="right" valign="middle" class="tableHeader2" >����</td>
            <logic:iterate name="stuinfo" id="si" type="java.util.Map" length="1">
            <td width="35%" align="left" valign="middle" class="tableHeader3" >
            <logic:present name="countrylist" scope="request">            
               <logic:iterate name="countrylist" id="ctyl" type="java.util.Map">
                <c:choose><c:when test="${ctyl.dictValue == si.nationality}">              
                <bean:write name="ctyl" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
            </td>            
             </logic:iterate>
          </tr>          
          </logic:present> 
        </tbody>
      </table></td>
  </tr>
  <tr> 
    <td height="40" align="right" valign="middle"> 
     <logic:present name="stuinfo" scope="request">
      <input name="Submit" type="button" class="button_nor" value="�� ��" onClick="DoCheck()"> 
     </logic:present>   
      &nbsp;&nbsp;&nbsp;
      <input name="cancel" type="button" class="button_nor" value="ȡ ��" onClick="DoBack()">
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

setTimeout('init()',50);
function init(){

  if(document.all.hmsg.value=='1')
      alert("���ݿ����Ѵ��ڸ�����!");  
  else if(document.all.hmsg.value=='9')
      alert("�����ظ���ӣ�");  
  else if(document.all.hmsg.value=='0') 
      alert("��ӳɹ�!");  
  else if(document.all.hmsg.value=='-1') 
      alert("�޴�����!"); 
}

function DoSearch(){

   if(document.all.studentNo.value==''){
       alert("������ѧ�ţ�");
       return;
   }
    
   document.stuadddelForm.action="stuadddelAction.do?method=findstuinfo";
   document.stuadddelForm.submit();
}
  
function DoCheck(){
   
   if(document.forms[0].elements["stuAdddelhis.studentNo"].value==''){
       alert("������ѧ�ţ�");
       return;
   }
  
  document.stuadddelForm.action="stuadddelAction.do?method=addstu";
  document.stuadddelForm.submit();    
}

function DoBack(){
       
  document.stuadddelForm.action="stuadddelAction.do?method=list";
  document.stuadddelForm.submit();    
}
</script>
