<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<body onload="init()">
<center>

<html:form action = "stuBmAction.do?method=stuinfoview">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">�ѱ��������б�</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>    
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
          <logic:present name="stubmlist" scope="request">
          <thead>
            <tr align="center" valign=center>
              <td width="5%" valign="middle" class="tableHeader" >ȫѡ<input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
              
              <td valign="middle" class="tableHeader" >�ѱ�������</td>
              <td valign="middle" class="tableHeader" >������ֹʱ��</td>              
              <td valign="middle" class="tableHeader" >�Ƿ��շ�</td>
              <td valign="middle" class="tableHeader" >�շѱ�׼</td> 
              <td valign="middle" class="tableHeader" >�Ƿ��ѽɷ�</td> 
              <td valign="middle" class="tableHeader" >�ɷѽ��</td> 
              <td valign="middle" class="tableHeader" >���Գɼ�</td>            
            </tr>
          </thead>            
            <logic:iterate name="stubmlist" id="nl" type="java.util.Map"  indexId="i">            
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign="middle" onmouseover="DoShowTip('<bean:write name="nl" property="testInfo"/> <bean:write name="nl" property="testMemo"/>')" onmouseout="DoHideTip()">             
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><input type="checkbox" name="cbgroup" value="<bean:write name="nl" property="id"/>" onClick="DoSelect(this)"></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF"  ><bean:write name="nl" property="testInfo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="bmInfo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="ifFeeName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="fee"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="ifPayName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="feePayed"/>&nbsp;</td>  
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="grades" format="##0.##"/>&nbsp;</td>             
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign="middle" onmouseover="DoShowTip('<bean:write name="nl" property="testInfo"/> <bean:write name="nl" property="testMemo"/>')" onmouseout="DoHideTip()">             
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><input type="checkbox" name="cbgroup" value="<bean:write name="nl" property="id"/>" onClick="DoSelect(this)"></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="testInfo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="bmInfo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="ifFeeName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="fee"/>&nbsp;</td>  
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="ifPayName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="feePayed"/>&nbsp;</td> 
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="grades" format="##0.##"/>&nbsp;</td>  
            </tr>
            </c:when></c:choose>            
            </logic:iterate>            
            </logic:present>                     
          </tbody>
        </table>
      </td>
  </tr>
  <tr> 
    <td align="center" valign="middle" >&nbsp;</td>
  </tr> 
   <tr> 
    <td height="40" align="center" valign="middle">
      <logic:present name="stubmlist" scope="request">
      <font size="2.5" color="red">��ʾ����ѡ����Ҫȡ�������Ŀ��ԣ��ɶ�ѡ�������<b>ȡ������</b>���ɡ�
        <p>�ѽɷѵĿ��Բ���ȡ���������ɷ�������ˮ�ϴ����ܻ���һ���ӳ١�</font>        
      </logic:present>
      <logic:notPresent name="stubmlist" scope="request">  
      <font size="2.5" color="red">��ǰû��������ȡ�������Ŀ��ԡ�</font>
      </logic:notPresent>
    </td>
  </tr>
  <tr> 
    <td height="40" align="center" valign="middle">
        <input name="cancel" type="submit" class="button_nor2" value="���ظ�����Ϣ">
        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <input name="bbm" type="button" class="button_nor2" value="�������ϱ���" onclick="DoBm()">
        <logic:present name="stubmlist" scope="request">
        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <input name="bnotbm" type="button" class="button_nor2" value="ȡ������" onclick="DoNotBm()"> 
        </logic:present>       
    </td>
  </tr>
  <tr> 
    <td id="tm" height="40" align="left" valign="middle" style="color: blue">      
    </td>
  </tr>
  <tr> 
    <td height="40" align="center" valign="middle">
        <logic:present name="feetotal" scope="request">        
        <table width="60%"><tr><td align="left" valign="middle">
        <font size="3" color="#990000">��ǰӦ�ɷ��ܶ�: <b><bean:write name="feetotal" /></b> Ԫ��<br>
        <logic:present name="bmendfirst" scope="request">
        <b>���� <bean:write name="bmendfirst" /> ǰ����ý���ͨ��һ��ͨ�ɷ�</b>��
        </logic:present>
         ����������ֹ���ڽ����ܽɷѡ�</font>	</td></tr>
	    <tr><td align="left" valign="middle">
	    <font size="3" color="#990000">�ڶ�ý����ɷ�ʱ������Ӧ�ɷ��ܶ�һ���Կۿ<br><b>��һ��ͨ������ <bean:write name="feetotal" /> Ԫ��������ۿ</b></font>	
	    </td></tr>	        
        </logic:present>       
    </td>
  </tr>
</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>

<logic:present name="nottobm" scope="request">
  <input name="hnottobm" type="hidden" value="<bean:write name="nottobm" />"> 
  </logic:present>
  <logic:notPresent name="nottobm" scope="request">
  <input name="hnottobm" type="hidden" value=""> 
</logic:notPresent>
<logic:present name="nottobmdue" scope="request">
  <input name="hnottobmdue" type="hidden" value="<bean:write name="nottobmdue" />"> 
  </logic:present>
  <logic:notPresent name="nottobmdue" scope="request">
  <input name="hnottobmdue" type="hidden" value=""> 
</logic:notPresent>
<input name="giveAlert" type="hidden" value="<%=(String)session.getAttribute("giveAlert")%>">
</html:form>
</center>
</body>
<script language="JavaScript">

function init(){
    
    if(document.all.hmsg.value=='0')
        alert("ȡ�������ɹ���");  
     
     if(document.all.hnottobm.value!='')
        alert(document.all.hnottobm.value+" �Ѿ��ɷѣ�����ȡ��������");  
     if(document.all.hnottobmdue.value!='')
        alert(document.all.hnottobmdue.value+" �Ѿ����ڣ�����ȡ��������");      
}

function DoSelect(cb){

   var sflag=1;;
   var usflag=1;;
  
   if(cb.checked){
   
       if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(!document.all.cbgroup[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall.checked=true;
          }
       }
       else if(document.all.cbgroup!=null){
           document.all.checkall.checked=true;
       }  
   }
   
   if(!cb.checked){
       document.all.checkall.checked=false;
       if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall.checked=false;
          }
       } 
       else if(document.all.cbgroup!=null){
           document.all.checkall.checked=false;
       } 
   }
   
}
function DoCheckall(ckall){
 

   if(ckall.checked){
   
      if(document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=true;
       }
       }
       else{
          document.all.cbgroup.checked=true;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.cbgroup.length>1){
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=false;
       }
      }
      else{
         document.all.cbgroup.checked=false;
      }
   }
}

function DoNotBm(){
 
   var sflag=0;
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                   
              }
          }           
         if(sflag==0){
              alert("��ѡ��Ҫȡ�������Ŀ��ԣ�");
              return;
          } 
   }
   else if(document.all.cbgroup!=null){
        if(!document.all.cbgroup.checked){
              alert("��ѡ��Ҫȡ�������Ŀ��ԣ�");
              return;        
        }
   }
   else{
       alert("��ǰû�п���ȡ�������Ŀ��ԣ�");
       return;    
   }
   if(confirm("��ȷ��Ҫȡ��������")){   
       document.studentForm.action="stuBmAction.do?method=stunotbm";       
       document.studentForm.submit();
   }
   else
       return;
  
}

function DoBm(){
  
  document.studentForm.action="stuBmAction.do?method=search4stuBmList";
  document.studentForm.submit();     
}

function DoShowTip(str){
  tm.innerHTML=str;
}

function DoHideTip(){
  tm.innerHTML='';
}
</script>
