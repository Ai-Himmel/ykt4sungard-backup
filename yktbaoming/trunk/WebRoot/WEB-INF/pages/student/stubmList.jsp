<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<body onload="init()">
<center>

<html:form action = "stuBmAction.do?method=stuinfoview">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">考试网上报名</font></strong></td>
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
              <td width="5%" valign="middle" class="tableHeader" >全选<input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
              
              <td valign="middle" class="tableHeader" >可报名考试</td> 
              <td valign="middle" class="tableHeader" >报名起止时间</td>             
              <td valign="middle" class="tableHeader" >是否收费</td>
              <td valign="middle" class="tableHeader" >收费标准</td>             
            </tr>
          </thead>			
            <logic:iterate name="stubmlist" id="nl" type="java.util.Map"  indexId="i">            
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign="middle" onmouseover="DoShowTip('<bean:write name="nl" property="testInfo"/> <bean:write name="nl" property="testMemo"/>')" onmouseout="DoHideTip()">             
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><input type="checkbox" name="cbgroup" value="<bean:write name="nl" property="id"/>" onClick="DoSelect(this)"></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="testInfo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="bmInfo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="ifFeeName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="fee"/>&nbsp;</td>             
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign="middle" onmouseover="DoShowTip('<bean:write name="nl" property="testInfo"/> <bean:write name="nl" property="testMemo"/>')" onmouseout="DoHideTip()">             
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><input type="checkbox" name="cbgroup" value="<bean:write name="nl" property="id"/>" onClick="DoSelect(this)"></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="testInfo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="bmInfo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="ifFeeName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="fee"/>&nbsp;</td>   
            </tr>
            </c:when></c:choose>           
            </logic:iterate>           
            </logic:present>
          </tbody>
        </table>
      </td>
  </tr>  
  <tr> 
    <td height="40" align="center" valign="middle">
      <logic:present name="stubmlist" scope="request">
      <font size="2.5" color="red">提示：先选择需要报名的考试（可多选），点击<b>报名</b>即可。</font>
      </logic:present>
      <logic:notPresent name="stubmlist" scope="request">  
      <font size="2.5" color="red">当前没有您可以报名的考试。</font>
      </logic:notPresent>
    </td>
  </tr>  
  <tr> 
    <td height="40" align="center" valign="middle">
        <input name="cancel" type="submit" class="button_nor2" value="返回个人信息">
        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <input name="bviewbm" type="button" class="button_nor2" value="已报考信息查看" onclick="DoViewBm()">  
        <logic:present name="stubmlist" scope="request">      
        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <input name="bbm" type="button" class="button_nor2" value="报 名" onClick="DoBm()">
        </logic:present>
    </td>
  </tr>
  <tr> 
    <td id="tm" height="40" align="left" valign="middle" style="color: blue">      
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
<input name="giveAlert" type="hidden" value="<%=(String)session.getAttribute("giveAlert")%>">
</html:form>
</center>
</body>
<script language="JavaScript">

function init(){
    
    if(document.all.hmsg.value=='0')
        alert("报名成功！");  
     
     if(document.all.hnottobm.value!='')
        alert(document.all.hnottobm.value+" ！");      
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

function DoBm(){
 
   var sflag=0;
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                   
              }
          }           
         if(sflag==0){
              alert("请选择要报名的考试！");
              return;
          } 
   }
   else if(document.all.cbgroup!=null){
        if(!document.all.cbgroup.checked){
              alert("请选择要报名的考试！");
              return;        
        }
   }
   else{
       alert("当前没有可以报名的考试！");
       return;    
   }
   if(confirm("您确定要报名吗？")){   
       document.studentForm.action="stuBmAction.do?method=stubm";       
       document.studentForm.submit();
   }
   else
       return;
  
}

function DoViewBm(){
  
  document.studentForm.action="stuBmAction.do?method=search4stuBmListview";
  document.studentForm.submit();     
}

function DoShowTip(str){
  tm.innerHTML=str;
}

function DoHideTip(){
  tm.innerHTML='';
}

</script>
