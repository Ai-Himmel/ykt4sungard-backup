<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<body onload="init()">
<center>

<html:form action = "stuBmAction.do?method=stuinfoview">
<html:errors/>
<br>
<table width="50%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">������Ϣ�޸�</font></strong></td>
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
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									ѧ��
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="studentNo"/> 
									<input name="bmStudent.studentNo" type="hidden" value="<bean:write name="nl" property="studentNo"/>">
									<input name="bmStudent.stuName" type="hidden" value="<bean:write name="nl" property="stuName"/>">
									<input name="bmStudent.gender" type="hidden" value="<bean:write name="nl" property="gender"/>">
									<input name="bmStudent.enrollYear" type="hidden" value="<bean:write name="nl" property="enrollYear"/>">
									<input name="bmStudent.deptName" type="hidden" value="<bean:write name="nl" property="deptName"/>">
									<input name="bmStudent.majorName" type="hidden" value="<bean:write name="nl" property="majorName"/>">
									<input name="bmStudent.curGrade" type="hidden" value="<bean:write name="nl" property="curGrade"/>">
									<input name="bmStudent.curClass" type="hidden" value="<bean:write name="nl" property="curClass"/>">																    
								</td>
							</tr>							
							<tr align="center" valign="middle">	
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									����
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="stuName"/>					    
								</td>
							</tr>							
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									֤������
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.idType" type="text" maxlength="6" value="<bean:write name="nl" property="idType"/>"> 						    
								</td>
							</tr>							
							<tr align="center" valign="middle">	
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									֤������
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.idCard" type="text" maxlength="18" value="<bean:write name="nl" property="idCard"/>"> 						    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�����ʼ�
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.email" type="text" maxlength="40" value="<bean:write name="nl" property="email"/>">
								</td>
							</tr>													          
        </logic:iterate>
        </logic:present>
       </tbody>
      </table></td>
  </tr>
  <tr> 
    <td height="40" align="center" valign="middle">
      <input name="Submit" type="button" class="button_nor" value="�� ��" onClick="DoCheck()"> 
      &nbsp;&nbsp;&nbsp;
      <input name="cancel" type="submit" class="button_nor" value="�� ��">
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
        alert("����ɹ���");
    else if(document.all.hmsg.value=='1')
        alert("����ʧ�ܣ�");
}

function DoCheck(){
            
   if(document.forms[0].elements["bmStudent.idType"].value!=''&&document.forms[0].elements["bmStudent.idType"].value=='���֤'&&document.forms[0].elements["bmStudent.idCard"].value!=''){
       var flag=checkIDCard(document.forms[0].elements["bmStudent.idCard"].value);
       if(!flag){
           alert("��������ȷ��֤������");
           document.forms[0].elements["bmStudent.idCard"].select();
           document.forms[0].elements["bmStudent.idCard"].focus();
           return;
       }       
   }
   else if(document.forms[0].elements["bmStudent.idCard"].value!=''){
       var totallen=0;
       for(var i=0;i<document.forms[0].elements["bmStudent.idCard"].value.length;i++){          
          if(isChinese(document.forms[0].elements["bmStudent.idCard"].value.charAt(i))){
              totallen=totallen+3;
          }
          else if(document.forms[0].elements["bmStudent.idCard"].value.charCodeAt(i)>128){
              totallen=totallen+3;
          }
          else
              totallen=totallen+1;
      }
      if(totallen>18){
          alert("֤�����볬��");
          document.forms[0].elements["bmStudent.idCard"].select();
          document.forms[0].elements["bmStudent.idCard"].focus();
          return;      
      }   
   }
   
   if(document.forms[0].elements["bmStudent.email"].value!=''){
      var flag=checkEmail(document.forms[0].elements["bmStudent.email"].value);
       if(!flag){
           alert("��������ȷ�ĵ����ʼ�");
           document.forms[0].elements["bmStudent.email"].select();
           document.forms[0].elements["bmStudent.email"].focus();
           return;
       } 
   }
   
  document.studentForm.action="stuBmAction.do?method=stuinfoupdate";
  document.studentForm.submit();     
}

function isChinese(str)
{
     var reg=/[^\u4E00-\u9FA5]/g;
     if (reg.test(str))
         return false;     
     else    
         return true;
    
}

function checkIDCard(idcard) //���ڻ�����Ϣ��ȫ��δ���������Ա����֤
{ 
var IDCheck=true;
var sVerifyCode="1,0,x,9,8,7,6,5,4,3,2";
var arrVerifyCode=sVerifyCode.split(","); 
var sWi="7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2";
var Wi = sWi.split(",");

if(idcard.length!=15&&idcard.length!=18){
    IDCheck=false;
    return IDCheck;
}
 
var Ai;
if(idcard.length==18){
    Ai=idcard.substring(0,17);
}
else if(idcard.length==15){    
    Ai = idcard.substring(0,6)+"19"+idcard.substring(6,15);
}
if(isNaN(Ai)){  
    IDCheck = false;  
    return IDCheck;
}

var strYear, strMonth, strDay  
strYear = Ai.substring(6,10);
strMonth =Ai.substring(10,12);
strDay =Ai.substring(12,14);
if(strMonth>12||strDay>31){
        IDCheck = false;
        return IDCheck;
}
var BirthDay =strYear+ "-" + strMonth+"-"+strDay;
var now=new Date();
var nowYear=now.getFullYear();
var nowMonth=(now.getMonth()+1)+"";
var nowDate=now.getDate()+"";
if(nowMonth.length==1)
    nowMonth="0"+nowMonth;
if(nowDate.length==1)
    nowDate="0"+nowDate;
 
var nowDay=nowYear+"-"+nowMonth+"-"+nowDate;
if(isDate(BirthDay)){
    if(parseInt(nowYear,10)-parseInt(strYear,10)>140||BirthDay>nowDay){
        IDCheck = false;
        return IDCheck;
    }    
}
else{
    IDCheck = false;
    return IDCheck;
} 
//ĩλ��֤��
var TotalmulAiWi=0; 
if(idcard.length==18){
    for(var i = 0;i<17;i++){
        TotalmulAiWi = TotalmulAiWi + parseInt(Ai.substring(i,i+1),10)* Wi[i];
    } 
    var modValue;
    modValue = TotalmulAiWi%11;
    var strVerifyCode;
    strVerifyCode = arrVerifyCode[modValue];
    var AiX="";
    if(strVerifyCode=='x')
        AiX=Ai+"X";
    Ai = Ai+strVerifyCode;
    if(idcard!=Ai&&idcard!=AiX){
        IDCheck = false;
        return IDCheck;
    }
}
 
return IDCheck;    
}  

function isDate(v)
{
  var r = v.match(/^(\d{1,4})(-|\/)(\d{1,2})\2(\d{1,2})$/); 
  if(r==null)
      return false; 
  var d = new Date(r[1],r[3]-1,r[4]); 
  return (d.getFullYear()==r[1]&&(d.getMonth()+1)==r[3]&&d.getDate()==r[4]);
}

function checkEmail(str){
    
    var returnValue = true;
	var re =/^\w+((-\w+)|(\.\w+))*\@[A-Za-z0-9]+((\.|-)[A-Za-z0-9]+)*\.[A-Za-z0-9]+$/;
	if(str.match(re) == null)
	    returnValue=false;
		
	return returnValue;    
}

</script>