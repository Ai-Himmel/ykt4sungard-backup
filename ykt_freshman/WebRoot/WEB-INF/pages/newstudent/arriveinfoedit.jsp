<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>
<script type="text/javascript" src="<c:url value='/pages/datepicker/WdatePicker.js'/>"></script>
<center>

<html:form action = "rcvmanageAction.do?method=update">
<html:errors/>
<br>
<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">�����ֻ���Ϣ�Ǽ�</font></strong></td>
  </tr>
  <tr>
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top" >
    <logic:iterate name="arrivelist" id="al" type="java.util.Map" length="1">
    <table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
        <tbody>
          <input type="hidden" name="updateid" value="<bean:write name="al" property="id"/>">
          <tr height="30" align="center" valign=center> 
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >¼ȡ֪ͨ���</td>
            <td align="left" valign="middle" class="tableHeader3" colspan="3"><bean:write name="al" property="enrollNo"/></td>
            <input type="hidden" name="stuarriveinfo.enrollNo" value="<bean:write name="al" property="enrollNo"/>">
          </tr>
          <tr height="30" align="center" valign=center>  
            <td align="right" valign="middle" class="tableHeader2" >ѧ��</td>
            <td align="left" valign="middle" class="tableHeader3" ><bean:write name="al" property="studentNo"/></td>
            <input type="hidden" name="studentNo" value="<bean:write name="al" property="studentNo"/>">
            <td align="right" valign="middle" class="tableHeader2" >����</td>
            <td align="left" valign="middle" class="tableHeader3" ><bean:write name="al" property="stuName"/></td>
            <input type="hidden" name="stuName" value="<bean:write name="al" property="stuName"/>">
          </tr>
          <tr height="30" align="center" valign=center> 
          <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">�ֻ���ʽ</td>
            <td align="left" valign="middle" class="tableHeader3"  colspan="3">            
                  <c:choose><c:when test="${al.arrivePlace == '01'}">
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="01" checked onClick="DoChange(this)">��&nbsp;
                  </c:when><c:otherwise>
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="01" onClick="DoChange(this)">��&nbsp;
                  </c:otherwise></c:choose>
                  <c:choose><c:when test="${al.arrivePlace == '02'}">
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="02" checked onClick="DoChange(this)">��;����&nbsp;
                  </c:when><c:otherwise>
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="02" onClick="DoChange(this)">��;����&nbsp;
                  </c:otherwise></c:choose>
                  <c:choose><c:when test="${al.arrivePlace == '03'}">
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="03" checked onClick="DoChange(this)">�ɻ�&nbsp;
                  </c:when><c:otherwise>
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="03" onClick="DoChange(this)">�ɻ�&nbsp;
                  </c:otherwise></c:choose>
                  <c:choose><c:when test="${al.arrivePlace == '04'}">
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="04" checked onClick="DoChange(this)">�Լݳ�&nbsp;
                  </c:when><c:otherwise>
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="04" onClick="DoChange(this)">�Լݳ�&nbsp;
                  </c:otherwise></c:choose>
                  <c:choose><c:when test="${al.arrivePlace == '05'}">
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="05" checked onClick="DoChange(this)">����&nbsp;
                  </c:when><c:otherwise>
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="05" onClick="DoChange(this)">����&nbsp;
                  </c:otherwise></c:choose> 
                  <c:choose><c:when test="${al.arrivePlace == '06'}">
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="06" checked onClick="DoChange(this)">����
                  </c:when><c:otherwise>
                  <input name="stuarriveinfo.arrivePlace" type="radio" value="06" onClick="DoChange(this)">����
                  </c:otherwise></c:choose>                 
                
            </td>
          </tr>
          <tr height="30" align="center" valign=center> 
            <td id="tddate" width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >Ԥ�Ƶֻ�����</td>
            <td width="35%" align="left" valign="middle" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr> 
                  <td width="130"><input class="Wdate" type="text" name="arriveDate" value="<bean:write name="al" property="arriveDate"/>" onfocus="new WdatePicker(this)" readonly="readonly"/> 
                    </td>                    
                </tr>
              </table></td>
            <td id="tdtime" width="15%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >Ԥ�Ƶֻ�ʱ��</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr> 
                  <td width="25">
                  <select name="shour" class="select01">
                  <option value="00" >00</option>
                  <option value="01" >01</option>
                  <option value="02" >02</option>
                  <option value="03" >03</option>
                  <option value="04" >04</option>
                  <option value="05" >05</option>
                  <option value="06" >06</option>
                  <option value="07" >07</option>
                  <option value="08" >08</option>
                  <option value="09" >09</option>
                  <option value="10" >10</option>
                  <option value="11" >11</option>
                  <option value="12" >12</option>
                  <option value="13" >13</option>
                  <option value="14" >14</option>
                  <option value="15" >15</option>
                  <option value="16" >16</option>
                  <option value="17" >17</option>
                  <option value="18" >18</option>
                  <option value="19" >19</option>
                  <option value="20" >20</option>
                  <option value="21" >21</option>
                  <option value="22" >22</option>
                  <option value="23" >23</option>
                  </select>
                  </td>
                  <td width="5" align="left">:</td>
                  <td width="25">
                  <select name="sminute" class="select01">
                  <option value="00" >00</option>
                  <option value="01" >01</option>
                  <option value="02" >02</option>
                  <option value="03" >03</option>
                  <option value="04" >04</option>
                  <option value="05" >05</option>
                  <option value="06" >06</option>
                  <option value="07" >07</option>
                  <option value="08" >08</option>
                  <option value="09" >09</option>
                  <option value="10" >10</option>
                  <option value="11" >11</option>
                  <option value="12" >12</option>
                  <option value="13" >13</option>
                  <option value="14" >14</option>
                  <option value="15" >15</option>
                  <option value="16" >16</option>
                  <option value="17" >17</option>
                  <option value="18" >18</option>
                  <option value="19" >19</option>
                  <option value="20" >20</option>
                  <option value="21" >21</option>
                  <option value="22" >22</option>
                  <option value="23" >23</option>
                  <option value="24" >24</option>
                  <option value="25" >25</option>
                  <option value="26" >26</option>
                  <option value="27" >27</option>
                  <option value="28" >28</option>
                  <option value="29" >29</option>
                  <option value="30" >30</option>
                  <option value="31" >31</option>
                  <option value="32" >32</option>
                  <option value="33" >33</option>
                  <option value="34" >34</option>
                  <option value="35" >35</option>
                  <option value="36" >36</option>
                  <option value="37" >37</option>
                  <option value="38" >38</option>
                  <option value="39" >39</option>
                  <option value="40" >40</option>
                  <option value="41" >41</option>
                  <option value="42" >42</option>
                  <option value="43" >43</option>
                  <option value="44" >44</option>
                  <option value="45" >45</option>
                  <option value="46" >46</option>
                  <option value="47" >47</option>
                  <option value="48" >48</option>
                  <option value="49" >49</option>
                  <option value="50" >50</option>
                  <option value="51" >51</option>
                  <option value="52" >52</option>
                  <option value="53" >53</option>
                  <option value="54" >54</option>
                  <option value="55" >55</option>
                  <option value="56" >56</option>
                  <option value="57" >57</option>
                  <option value="58" >58</option>
                  <option value="59" >59</option>               
                  </select>
                  </td>
                  <td width="130"> <input name="arriveTime" type="hidden" value="<bean:write name="al" property="arriveTime"/>"> 
                  </td>
                </tr>
              </table></td>
          </tr>
          <tr id="trplane" height="30" align="center" valign=center>
            <td align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >����</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" colspan="3"><table border="0" cellspacing="0" cellpadding="0">
                <tr align="center" valign="middle">
                  <td width="25"> <c:choose><c:when test="${al.ifDeleted == '3'}">
                  <input name="stuarriveinfo.ifDeleted" type="radio" value="3" checked> <!-- ��Ϊ�����ֶΣ��ֻ��ص��־-->
                  </c:when><c:otherwise> 
                  <input name="stuarriveinfo.ifDeleted" type="radio" value="3">
                  </c:otherwise></c:choose>
                  </td>
                  <td width="50" align="left">���Ż���</td>
                  <td width="25"> <c:choose><c:when test="${al.ifDeleted == '4'}">
                  <input type="radio" name="stuarriveinfo.ifDeleted" value="4" checked> 
                  </c:when><c:otherwise> 
                  <input name="stuarriveinfo.ifDeleted" type="radio" value="4">
                  </c:otherwise></c:choose>
                  </td>
                  <td width="50" align="left">�ֶ�����</td>                   
                </tr>
              </table></td> 
          </tr>
          <tr id="trtrain" height="30" align="center" valign=center>             
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�𳵳���</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" ><input 
            name="stuarriveinfo.trainNo" class="input_box"  maxlength=25 value="<bean:write name="al" property="trainNo"/>"></td>
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�����</td>
            <td align="left" valign="middle" class="tableHeader3" ><input 
            name="stuarriveinfo.trainRoomNo" class="input_box"  maxlength=25 value="<bean:write name="al" property="trainRoomNo"/>"></td>
          </tr>
          <tr id="trnum" height="30" align="center" valign=center>             
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��ͬ����</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" colspan="3"><input 
            name="companyNum" class="input_box"  maxlength=3 value="<bean:write name="al" property="companyNum"/>"></td>
          </tr>
          <tr id="trhelp" height="30" align="center" valign=center>            
                  <input name="stuarriveinfo.ifNeedHelp" type="hidden" value="0">    
            <td align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��վ</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3"><table border="0" cellspacing="0" cellpadding="0">
                <tr align="center" valign="middle">
                  <td width="25"> <c:choose><c:when test="${al.ifDeleted == '1'}">
                  <input name="stuarriveinfo.ifDeleted" type="radio" value="1" checked> 
                  </c:when><c:otherwise> 
                  <input name="stuarriveinfo.ifDeleted" type="radio" value="1">
                  </c:otherwise></c:choose>
                  </td>
                  <td width="40" align="left">�Ϻ�վ</td>
                  <td width="25"> <c:choose><c:when test="${al.ifDeleted == '2'}">
                  <input type="radio" name="stuarriveinfo.ifDeleted" value="2" checked> 
                  </c:when><c:otherwise> 
                  <input name="stuarriveinfo.ifDeleted" type="radio" value="2">
                  </c:otherwise></c:choose>
                  </td>
                  <td width="50" align="left">�Ϻ���վ</td>                   
                </tr>
            </table></td>              
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" nowrap>���Ϻ�վ��У��</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3"><table border="0" cellspacing="0" cellpadding="0">
                <tr align="center" valign="middle"> 
                  <td width="25"> <c:choose><c:when test="${al.ifNeedBus == '0'}">
                  <input name="stuarriveinfo.ifNeedBus" type="radio" value="0" checked>
                  </c:when><c:otherwise> 
                  <input name="stuarriveinfo.ifNeedBus" type="radio" value="0">
                  </c:otherwise></c:choose> 
                  </td>
                  <td width="40" align="left">��</td>
                  <td width="25"> <c:choose><c:when test="${al.ifNeedBus == '1'}">
                  <input type="radio" name="stuarriveinfo.ifNeedBus" value="1" checked> 
                  </c:when><c:otherwise>
                  <input type="radio" name="stuarriveinfo.ifNeedBus" value="1">
                  </c:otherwise></c:choose> 
                  </td>
                  <td width="50" align="left">��</td>                   
                </tr>
              </table></td>
          </tr>
          <tr height="30" align="center" valign=center>             
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��ϵ��ʽ</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" colspan="3"><input 
            name="stuarriveinfo.tempconcact" class="input_box"  maxlength=25 value="<bean:write name="al" property="tempconcact"/>">&nbsp;(����д�����ֻ���У���������ϵ�����ĵ绰���ֻ�)</td>            
          </tr>
          <tr align="center" valign=center> 
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��ע</td>
            <td colspan="3" align="left" valign="middle" class="tableHeader3" ><textarea name="stuarriveinfo.memo" cols=70 rows=4><bean:write name="al" property="memo"/>
</textarea></td>
          </tr>
        </tbody>
      </table>
      </logic:iterate>
      </td>
  </tr>
  <tr> 
    <td height="40" align="left" valign="middle"><font size="3" color="#990000">��д��֪��</font></td>  
    <td height="40" align="right" valign="middle"> 
      <input name="Submit" type="button" class="button_nor" value="ɾ��" onClick="DoDelete()"> &nbsp;&nbsp;
      <input name="Submit" type="button" class="button_nor" value="�ύ" onClick="DoCheck()"> 
    </td>
  </tr>
  <tr>
  <td height="40" align="left" valign="middle" colspan="4"> 
    <font size="2.5" color="#990000">
    1.&nbsp;&nbsp;����ѡ��ֻ���ʽ����ͬ��Ա��ס�����������а��š�<br>
    2.&nbsp;&nbsp;���𳵵ֻ���ͬѧ����дԤ�Ƶֻ����ڡ�Ԥ�Ƶֻ�ʱ����³�վ�㣬�������ݿ�ѡ������Ҫ���Ϻ�վ����У������������Ӧѡ��<br>
    3.&nbsp;&nbsp;У�����ڱ����������Ϻ���վ���㳡��վ���Ϻ���վ�³���ͬѧ�����ȳ��������ͨ3���ߣ����Ϻ�վ���㳡���ڴ���У����<br>
    4.&nbsp;&nbsp;���ɻ��ֻ���ͬѧ����дԤ�Ƶ�У���ڡ�Ԥ�Ƶ�Уʱ��͵ֻ��������ɡ�<br>
    5.&nbsp;&nbsp;���𳵡��ɻ����������ʽ�ֻ���ͬѧֻ����дԤ�Ƶ�У���ں�Ԥ�Ƶ�Уʱ�伴�ɡ�<br>
    6.&nbsp;&nbsp;��ѧ����������Ϻ���վ��ͼ������У��ͣ��λ�ã��͸�����ѧ�ܱߵ�ͼ�����Բ鿴��
    </font>
    </td>  
  </tr>
</table>
<input type="hidden" name="stuarriveinfo.creatorId" value="<bean:write name="al" property="creatorId"/>">
<input type="hidden" name="createTime" value="<bean:write name="al" property="createTime"/>">
<input type="hidden" name="stuarriveinfo.updatorId" value="<%=(String)session.getAttribute("userName")%>">

<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>
<input type="hidden" name="curYear" value="<%=(String)request.getAttribute("curYear")%>">
</html:form>
</center>

<script language="JavaScript">

//setTimeout('init()',50);
function init(){

  var hhour=document.all.arriveTime.value.substring(0,2);
  var hminute=document.all.arriveTime.value.substring(3,5);
  
  for(var i=0;i<document.all.shour.length;i++){
      if(document.all.shour.options[i].value==hhour){
          document.all.shour.options[i].selected=true;
          break;
      }
  }
  for(var i=0;i<document.all.sminute.length;i++){
      if(document.all.sminute.options[i].value==hminute){
          document.all.sminute.options[i].selected=true;
          break;
      }
  }
  
  for(var i=0;i<document.forms[0].elements["stuarriveinfo.arrivePlace"].length;i++){
  
   if(document.all('stuarriveinfo.arrivePlace')[0].checked){

    tddate.innerHTML="Ԥ�Ƶֻ�����";
    tdtime.innerHTML="Ԥ�Ƶֻ�ʱ��";
    
    trtrain.style.display='';
    trnum.style.display='';
    trhelp.style.display='';
    
    trplane.style.display='none';

  }

  else if(document.all('stuarriveinfo.arrivePlace')[2].checked){
    
    tddate.innerHTML="Ԥ�Ƶ�У����";
    tdtime.innerHTML="Ԥ�Ƶ�Уʱ��";
    
    trtrain.style.display='none';
    trnum.style.display='none';
    trhelp.style.display='none';
    
    trplane.style.display='';
    
    document.forms[0].elements["stuarriveinfo.trainNo"].value="";
    document.forms[0].elements["stuarriveinfo.trainRoomNo"].value="";
    document.forms[0].elements["companyNum"].value="0";    
    document.all("stuarriveinfo.ifNeedBus")[0].checked=true;

  }
  else{
    tddate.innerHTML="Ԥ�Ƶ�У����";
    tdtime.innerHTML="Ԥ�Ƶ�Уʱ��";
    
    trtrain.style.display='none';
    trnum.style.display='none';
    trhelp.style.display='none';
    
    trplane.style.display='none';
    
    document.forms[0].elements["stuarriveinfo.trainNo"].value="";
    document.forms[0].elements["stuarriveinfo.trainRoomNo"].value="";
    document.forms[0].elements["companyNum"].value="0";    
    document.all("stuarriveinfo.ifNeedBus")[0].checked=true;
  
  }
 }
 if(document.all.hmsg.value=='1'){
          alert("����ɹ�!");
          
      }
 else if(document.all.hmsg.value=='2')
          alert("�޸ĳɹ�!");
 else if(document.all.hmsg.value=='3')
          alert("ɾ���ɹ�!");
 else if(document.all.hmsg.value=='9')
          alert("�����ظ����棡");
}

function DoChange(rdo){  

   if(rdo.value=='01'){
   
    tddate.innerHTML="Ԥ�Ƶֻ�����";
    tdtime.innerHTML="Ԥ�Ƶֻ�ʱ��";
    
    trtrain.style.display='';
    trnum.style.display='';
    trhelp.style.display='';
    trplane.style.display='none';
    document.all("stuarriveinfo.ifDeleted")[2].checked=true;
    
   }
   else if(rdo.value=='03'){
   
    tddate.innerHTML="Ԥ�Ƶ�У����";
    tdtime.innerHTML="Ԥ�Ƶ�Уʱ��";
    
    trtrain.style.display='none';
    trnum.style.display='none';
    trhelp.style.display='none';
    
    trplane.style.display='';
    document.all("stuarriveinfo.ifDeleted")[0].checked=true;
    
    document.forms[0].elements["stuarriveinfo.trainNo"].value="";
    document.forms[0].elements["stuarriveinfo.trainRoomNo"].value="";
    document.forms[0].elements["companyNum"].value="0";    
    document.all("stuarriveinfo.ifNeedBus")[0].checked=true;
   
   }
   else{
   
    tddate.innerHTML="Ԥ�Ƶ�У����";
    tdtime.innerHTML="Ԥ�Ƶ�Уʱ��";
    
    trtrain.style.display='none';
    trnum.style.display='none';
    trhelp.style.display='none';
    
    trplane.style.display='none'; 
    document.all("stuarriveinfo.ifDeleted")[0].checked=true;   
    
    document.forms[0].elements["stuarriveinfo.trainNo"].value="";
    document.forms[0].elements["stuarriveinfo.trainRoomNo"].value="";
    document.forms[0].elements["companyNum"].value="0";    
    document.all("stuarriveinfo.ifNeedBus")[0].checked=true;
   
   }
   
}

function ChangeFocus1(){
    document.all.selectDate.focus();
}

function DoCheck(){

   document.all.arriveTime.value=document.all.shour.value+":"+document.all.sminute.value+":00";
   //alert(document.all.arriveTime.value);
   
   if(document.forms[0].elements["arriveDate"].value==''){
      alert("������ֻ����ڣ�");  
      return; 
   }
   else{      
      if(document.forms[0].elements["arriveDate"].value.substring(0,4)!=document.all.curYear.value){
          alert("��ǰ���� "+document.all.curYear.value+" �꣡");
          return;
      }
   }
   
    if(document.forms[0].elements["arriveTime"].value==''){
      alert("������ֻ�ʱ��");  
      return; 
   }
   
   if(document.forms[0].elements["stuarriveinfo.arrivePlace"].value==''){
      alert("��ѡ��ֻ��ص㣡");  
      return; 
   }
   
   if(document.all.companyNum.value!=''){
     if(isNaN(document.all.companyNum.value)){
      alert("��ͬ����ӦΪ��ֵ��");
      document.all.companyNum.focus();
      document.all.companyNum.select();
      return;
    }
    var snum=document.all.companyNum.value;  
    if(parseInt(snum)<0){
      alert("��ͬ��������Ϊ������");
      document.all.companyNum.focus();
      document.all.companyNum.select();
      return;
    }
    var snum1=parseInt(snum)+"";
    if(snum1!=snum){
       alert("��ͬ����ӦΪ������");
       document.all.companyNum.focus();
       document.all.companyNum.select();
       return;
    }
  }
  
  if(document.forms[0].elements["stuarriveinfo.memo"].value.length>300){
       alert("��ע������");
       return;
  }
  
  document.stuarriveinfoForm.action="rcvmanageAction.do?method=stuupdate";
  document.stuarriveinfoForm.submit();     
}

function DoDelete(){
   
   if(confirm("��ȷ��Ҫɾ������Ϣ��")){
      document.stuarriveinfoForm.action="rcvmanageAction.do?method=studelete";
      document.stuarriveinfoForm.submit();
   }
   else
      return;
}

window.onload=init;	
</script>