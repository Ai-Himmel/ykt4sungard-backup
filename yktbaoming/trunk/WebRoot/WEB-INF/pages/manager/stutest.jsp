<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<body onload="init()">
<center>

	<html:form action="studentAction.do?method=search4List">
		<html:errors />
		<br>
		<table width="90%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">�����������</font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
						<tbody>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									ѧ��
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.studentNo" type="text" maxlength="15" value=""> 								    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									����
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.stuName" type="text" maxlength="20" value=""> 								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�Ա�
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<select name="bmStudent.gender" class="select01">
									    <option value="��" selected>��</option>
									    <option value="Ů">Ů</option>
									</select>						    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									��ѧ���
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.enrollYear" type="text" maxlength="4" value=""> 								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									ѧԺ����
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.deptName" type="text" maxlength="30" value=""> 								    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									רҵ����
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.majorName" type="text" maxlength="30" value=""> 								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�꼶
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.curGrade" type="text" maxlength="6" value=""> 								    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�༶
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.curClass" type="text" maxlength="20" value=""> 								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									֤������
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.idType" type="text" maxlength="6" value="���֤"> 								    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									֤������
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<input name="bmStudent.idCard" type="text" maxlength="18" value=""> 								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�����ʼ�
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<input name="bmStudent.email" type="text" maxlength="40" value=""> 								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									ѡ����
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<select name="testId" class="select01">
									<option value="" >��ѡ��</option>
									<logic:present name="testlist" scope="request">
                                        <logic:iterate name="testlist" id="ml" type="java.util.Map">
                                        <option value="<bean:write name="ml" property="id"/>"><bean:write name="ml" property="testInfo"/></option>
                                        </logic:iterate>
                                    </logic:present>									
								</select>								    
								</td>
							</tr>							
						</tbody>
					</table>
				</td>
			</tr>
			<tr>
				<td height="40" align="right" valign="middle">
					<input name="Submit" type="button" class="button_nor" value="�� ��" onClick="DoCheck()">
					&nbsp;&nbsp;&nbsp;
                    <input name="cancel" type="submit" class="button_nor" value="ȡ ��">
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
</body>

<script language="JavaScript">

function init(){
    
    if(document.all.hmsg.value=='1')
        alert("����ʧ�ܣ�");
    else if(document.all.hmsg.value=='2')
        alert("�ÿ����Ѵ��ڣ�����ʧ�ܣ�");
}

function DoCheck(){
    
   if(document.forms[0].elements["bmStudent.studentNo"].value==''){
       alert("����д����ѧ�ţ�");
       document.forms[0].elements["bmStudent.studentNo"].select();
       document.forms[0].elements["bmStudent.studentNo"].focus();
       return;
   }
   else{
       for(var i=0;i<document.forms[0].elements["bmStudent.studentNo"].value.length;i++){          
          if(isChinese(document.forms[0].elements["bmStudent.studentNo"].value.charAt(i))){
              alert("ѧ�Ų���Ϊ���֣�");
              document.forms[0].elements["bmStudent.studentNo"].select();
              document.forms[0].elements["bmStudent.studentNo"].focus();
              return;
          }
          if(document.forms[0].elements["bmStudent.studentNo"].value.charCodeAt(i)>128){
              alert("ѧ�Ų�����ȫ���ַ���");
              document.forms[0].elements["bmStudent.studentNo"].select();
              document.forms[0].elements["bmStudent.studentNo"].focus();
              return;
          }
      }  
   
   }
   
   if(document.forms[0].elements["bmStudent.stuName"].value==''){
       alert("����д����������");
       document.forms[0].elements["bmStudent.stuName"].select();
       document.forms[0].elements["bmStudent.stuName"].focus();
       return;
   }
   
   if(document.all.testId.value==''){
      alert("��ѡ���ԣ�");      
      return; 
   }
   
   if(document.forms[0].elements["bmStudent.enrollYear"].value!=''){
       var totallen=0;
       for(var i=0;i<document.forms[0].elements["bmStudent.enrollYear"].value.length;i++){          
          if(isChinese(document.forms[0].elements["bmStudent.enrollYear"].value.charAt(i))){
              totallen=totallen+3;
          }
          else if(document.forms[0].elements["bmStudent.enrollYear"].value.charCodeAt(i)>128){
              totallen=totallen+3;
          }
          else
              totallen=totallen+1;
      }      
      if(totallen>4){
          alert("��ѧ��ݳ���");
          document.forms[0].elements["bmStudent.enrollYear"].select();
          document.forms[0].elements["bmStudent.enrollYear"].focus();
          return;      
      }   
   }
          
   if(document.forms[0].elements["bmStudent.idType"].value!=''&&document.forms[0].elements["bmStudent.idType"].value=='���֤'&&document.forms[0].elements["bmStudent.idCard"].value!=''){
       var flag=checkIDCard(document.forms[0].elements["bmStudent.idCard"].value);
       if(!flag){
           alert("��������ȷ��֤�����룡");
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
           alert("��������ȷ�ĵ����ʼ���");
           document.forms[0].elements["bmStudent.email"].select();
           document.forms[0].elements["bmStudent.email"].focus();
           return;
       } 
   }
   
   document.studentForm.action="studentAction.do?method=add";
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
