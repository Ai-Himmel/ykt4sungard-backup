<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>
<!-- <script type="text/javascript" src="<c:url value='/pages/scripts/sorttable.js'/>"></script>  -->
<center>
<html:form action = "rcvmanageAction.do?method=jiezhanfind">

<br>

<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
 
    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">������վ��Ϣ��ѯ</font></strong></td>
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
            <tr align="center" valign=center> 
              <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >ѧ��</td>
              <td width="35%" align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
              <td width="15%" align="right" valign="middle" class="tableHeader2" >�༶</td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="classNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
            </tr>
            <tr align="center" valign=center>
              <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�ֻ�����</td>
              <td align="left" valign="middle" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130"> <input 
            name="arriveDate" class="input_box"  maxlength=50 value="" onFocus="ChangeFocus1()" readonly="readonly"> 
                    </td>
                    <td><img name="selectDate" class="img_nor" width="21" height="21" border="0" onclick="setday(this,document.all.arriveDate)"></td>
                  </tr>
                </table></td>
              <td align="right" valign="middle" class="tableHeader2" >�ֻ�ʱ��</td>
              <td align="left" valign="middle" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <OBJECT id="time" class="TxtInput"  border="1" style="HEIGHT: 16; WIDTH: 120;" tabIndex="4" type="text/x-scriptlet" VIEWASTEXT>
                         <PARAM NAME="URL" VALUE="rcvtimesetup.do">
                    </OBJECT> 
                    </td>
                    <td>
                    <input name="timeselect" type="checkbox" value="15" >��Ҫʱ������<input type="hidden" name="arriveTime" value="">
                    </td>
                  </tr>
                </table></td>
            </tr>
            <tr align="center" valign=center> 
            <td align="right" valign="middle" class="tableHeader2" >�ֻ���ʽ</td>
              <td align="left" valign="middle" class="tableHeader3" > 
                <select name="arrivePlace" class="select01">
                  <option value="" selected>��ѡ��</option>                  
                  <option value="01">��</option>
                  <option value="02">��;����</option>
                  <option value="03">�ɻ�</option>
                  <option value="04">�Լݳ�</option>
                  <option value="05">����</option>
                  <option value="06">����</option>
                </select></td>
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                �𳵳���</td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="trainNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>              
            </tr> 
             <logic:present name="arriveform" scope="request"> 
            <input name="stuarriveinfo.enrollNo" type="hidden" value="<bean:write name="arriveform" property="enrollNo" />">     
            <input name="stuarriveinfo.arriveDate" type="hidden" value="<bean:write name="arriveform" property="arriveDate" />"> 
            <input name="stuarriveinfo.arriveTime" type="hidden" value="<bean:write name="arriveform" property="arriveTime" />">           
            <input name="stuarriveinfo.arrivePlace" type="hidden" value="<bean:write name="arriveform" property="arrivePlace" />">               
            <input name="stuarriveinfo.trainNo" type="hidden" value="<bean:write name="arriveform" property="trainNo" />">
            </logic:present>
            <logic:notPresent name="arriveform" scope="request">  
            <input name="stuarriveinfo.enrollNo" type="hidden" value="">   
            <input name="stuarriveinfo.arriveDate" type="hidden" value="1900-01-01"> 
            <input name="stuarriveinfo.arriveTime" type="hidden" value="00:00:01">            
            <input name="stuarriveinfo.arrivePlace" type="hidden" value="">                
            <input name="stuarriveinfo.trainNo" type="hidden" value="">  
            </logic:notPresent>
             <logic:present name="classNo" scope="request">
             <input name="hclassNo" type="hidden" value="<bean:write name="classNo" />"> 
             </logic:present>   
             <logic:notPresent name="classNo" scope="request">  
             <input name="hclassNo" type="hidden" value="">
             </logic:notPresent>
             <logic:present name="studentNo" scope="request">
             <input name="hstudentNo" type="hidden" value="<bean:write name="studentNo" />"> 
             </logic:present>   
             <logic:notPresent name="studentNo" scope="request">  
             <input name="hstudentNo" type="hidden" value="">
             </logic:notPresent>         
          </tbody>
        </table></td>
    </tr>
    <tr> 
      <td height="40" align="right" valign="middle" class="tdborder02"> 
      <input name="Submit" type="button" class="button_nor" value="�� ѯ" onClick="DoFind()"> 
      <input name="Reset" type="button" class="button_nor" value="�� ��" onClick="DoClear()"> 
      </td>
    </tr><input type="hidden" name="updateid" value=""> <input name="doexl" type="hidden" value="">    
    <input name="orderby" type="hidden" value="">
    <logic:present name="jzlist">
    <tr>
      <td height="30" align="right" valign="middle" colspan="2">      
         <a href="javascript:DoExport()">����Excel<IMG src="./pages/style/default/images/xls.gif" border="0"></a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      
      </td>
    </tr>
    </logic:present>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=maintable>
          <tbody>   
           <logic:present name="jzlist">       
           <thead>
            <tr align="center" valign=center> 
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('arriveDate')">�ֻ�����</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('arriveTime')">�ֻ�ʱ��</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('arrivePlace')">�ֻ���ʽ</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('ifDeleted')">�ֻ��ص�</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('trainNo')">�𳵳���</a></td>
              <td height="24" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')">ѧ��</a></td>
              <td valign="middle" class="tableHeader" nowrap><a style="font-size:14px;color: black" href="javascript:DoSort('enrollNo')">¼ȡ֪ͨ���</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('stuName')">����</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('classNo')">�༶</a></td>                                          
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('companyNum')">��ͬ����</a></td>              
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('ifNeedBus')">��У��</a></td>
              <td valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('tempconcact')">��ϵ��ʽ</a></td>
            </tr>
           </thead>
           <!--page offset start -->
           <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./rcvmanageAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <%-- keep track of preference --%>
            <pg:param name="method" />
			<pg:param name="hstudentNo" />
			<pg:param name="hclassNo" />			
			<pg:param name="stuarriveinfo.trainNo" />
			<pg:param name="stuarriveinfo.arriveDate" />
			<pg:param name="stuarriveinfo.arriveTime" />
			<pg:param name="stuarriveinfo.arrivePlace" />
			<pg:param name="orderby" />
	  	    <pg:param name="horder" />
           
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
            <logic:iterate name="jzlist" id="jl" type="java.util.Map" indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center>  
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="arriveDate"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="arriveTime" formatKey="timeFormat"/></td> 
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                  <c:choose><c:when test="${jl.arrivePlace == '01'}">
                    ��
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '02'}">
                    ��;����
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '03'}">
                    �ɻ�
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '04'}">
                    �Լݳ�
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '05'}">
                    ����
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '06'}">
                    ����
                  </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                  <c:choose><c:when test="${jl.ifDeleted == '1'}">
                    �Ϻ�վ
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '2'}">
                    �Ϻ���վ
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '3'}">
                    ���Ż���
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '4'}">
                    �ֶ�����
                  </c:when></c:choose>
                  &nbsp;
              </td>            
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="trainNo"/>&nbsp;</td> 
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><a href="javascript:DoView('<bean:write name="jl" property="id"/>')"><bean:write name="jl" property="studentNo"/></a></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="enrollNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="classNo"/></td>              
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${jl.arrivePlace == '01'}">
              <bean:write name="jl" property="companyNum"/>
              </c:when><c:otherwise>
              &nbsp;
              </c:otherwise></c:choose>
              </td>              
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${jl.ifNeedBus == '0'}">
                ��
              </c:when></c:choose>
              <c:choose><c:when test="${jl.ifNeedBus == '1'}">
                ��
              </c:when></c:choose>              
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="jl" property="tempconcact"/>&nbsp;</td>
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="arriveDate"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="arriveTime" formatKey="timeFormat"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
                  <c:choose><c:when test="${jl.arrivePlace == '01'}">
                    ��
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '02'}">
                    ��;����
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '03'}">
                    �ɻ�
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '04'}">
                    �Լݳ�
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '05'}">
                    ����
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.arrivePlace == '06'}">
                    ����
                  </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
                  <c:choose><c:when test="${jl.ifDeleted == '1'}">
                    �Ϻ�վ
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '2'}">
                    �Ϻ���վ
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '3'}">
                    ���Ż���
                  </c:when></c:choose>
                  <c:choose><c:when test="${jl.ifDeleted  == '4'}">
                    �ֶ�����
                  </c:when></c:choose>
                  &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="trainNo"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><a href="javascript:DoView('<bean:write name="jl" property="id"/>')"><bean:write name="jl" property="studentNo"/></a></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="enrollNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${jl.arrivePlace == '01'}">
              <bean:write name="jl" property="companyNum"/>
              </c:when><c:otherwise>
              &nbsp;
              </c:otherwise></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${jl.ifNeedBus == '0'}">
                ��
              </c:when></c:choose>
              <c:choose><c:when test="${jl.ifNeedBus == '1'}">
                ��
              </c:when></c:choose>              
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="jl" property="tempconcact"/>&nbsp;</td>
            </tr>
            </c:when></c:choose> 
            </pg:item>            
            </logic:iterate>
            <jsp:include page="./page.jsp" flush="true" />
            </tbody>
        </table></td>        
    </tr>
    <tr> 
    <td height="24" align="left" valign="middle">
        <jsp:include page="./page.jsp" flush="true" />
    </td>
  </tr>
		  </pg:pager>
		  <!-- page offset end -->		  
          </logic:present>
            
          <logic:notPresent name="jzlist" scope="request">                    
          <!--page offset start -->
		  <pg:pager url="./rcvmanagejiezhanpageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
			<pg:param name="hstudentNo" />
			<pg:param name="hclassNo" />			
			<pg:param name="stuarriveinfo.trainNo" />
			<pg:param name="stuarriveinfo.arriveDate" />
			<pg:param name="stuarriveinfo.arriveTime" />
			<pg:param name="stuarriveinfo.arrivePlace" />			
           
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">
           <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
		  </tbody>
        </table></td>        
    </tr>
            </logic:notPresent>                    
          
    <logic:present name="jzlist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">��<%=rowcount%>����¼</font>
    </td>
    </tr>  
    </logic:present>
</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>
<logic:present name="order" scope="request">
  <input name="horder" type="hidden" value="<bean:write name="order" />"> 
  </logic:present>
  <logic:notPresent name="order" scope="request">
  <input name="horder" type="hidden" value="a"> 
</logic:notPresent>
</html:form>
</center>

<script language="JavaScript">

setTimeout('init()',200);

function init(){
  
  document.all.studentNo.value=document.all.hstudentNo.value;
  if(document.forms[0].elements["stuarriveinfo.arriveDate"].value!='1900-01-01')  
      document.all.arriveDate.value=document.forms[0].elements["stuarriveinfo.arriveDate"].value;   
       
  document.all.classNo.value=document.all.hclassNo.value;
  document.all.trainNo.value=document.forms[0].elements["stuarriveinfo.trainNo"].value;
  
  if(document.forms[0].elements["stuarriveinfo.arriveTime"].value!='00:00:01'){
     document.all.time.setTime(document.forms[0].elements["stuarriveinfo.arriveTime"].value);
     document.all.timeselect.checked=true;
  }
  
  for(var i=0;i<document.all.arrivePlace.length;i++){
     
      if(document.forms[0].elements["stuarriveinfo.arrivePlace"].value==document.all.arrivePlace.options[i].value)
          document.all.arrivePlace.options[i].selected=true;
          
  }   
  
  if(document.all.hmsg.value=='1')
      alert("����Excel�ɹ�!");
  else if(document.all.hmsg.value=='0')
      alert("������!");
}

function DoClear(){
  
   document.all.studentNo.value="";
   document.all.classNo.value="";
   document.all.arriveDate.value="";
   document.all.timeselect.checked=false;
   document.all.trainNo.value="";
   document.all.arrivePlace.options[0].selected=true;
   
   document.all.hstudentNo.value="";
   document.all.hclassNo.value="";
   document.forms[0].elements["stuarriveinfo.enrollNo"].value="";
   document.forms[0].elements["stuarriveinfo.trainNo"].value="";
   document.forms[0].elements["stuarriveinfo.arriveDate"].value="1900-01-01";
   document.forms[0].elements["stuarriveinfo.arriveTime"].value="00:00:01";
   document.forms[0].elements["stuarriveinfo.arrivePlace"].value="";
   //alert(document.all.arriveDate.value);
   //alert(document.forms[0].elements["stuarriveinfo.arriveDate"].value);
}

function document.onkeydown()
{
	var e=event.srcElement;
	if(event.keyCode==13)
	{
		DoFind();
		return false;
	}
}

function DoFind(){
   
   if(document.all.timeselect.checked){
       document.all.arriveTime.value=document.all.time.getTime();
       //alert(document.all.arriveTime.value);
   }
   else
       document.all.arriveTime.value="";
       
   document.forms[0].elements["pager.offset"].value="0";
   document.all.doexl.value="";
   
   document.all.hstudentNo.value=document.all.studentNo.value;
   document.all.hclassNo.value=document.all.classNo.value;
   document.forms[0].elements["stuarriveinfo.enrollNo"].value="";
   document.forms[0].elements["stuarriveinfo.trainNo"].value=document.all.trainNo.value;
   if(document.all.arriveDate.value!='')
       document.forms[0].elements["stuarriveinfo.arriveDate"].value=document.all.arriveDate.value;
       
   if(document.all.timeselect.checked&&document.all.arriveTime.value!='00:00:01')
       document.forms[0].elements["stuarriveinfo.arriveTime"].value=document.all.arriveTime.value;
       
   document.forms[0].elements["stuarriveinfo.arrivePlace"].value=document.all.arrivePlace.value;
   
   document.stuarriveinfoForm.action="rcvmanageAction.do?method=jiezhanfind";
   document.stuarriveinfoForm.submit();
   
}

function DoSort(col){
  document.all.doexl.value="";
  document.all.orderby.value=col;
  if(document.all.horder.value=='a')
      document.all.horder.value='d';
  else if(document.all.horder.value=='d')
      document.all.horder.value='a';
      
  document.stuarriveinfoForm.action="rcvmanageAction.do?method=jiezhanfind";
  document.stuarriveinfoForm.submit();
}

function ChangeFocus1(){
    document.all.selectDate.focus();
}

function DoView(str){

   document.all.updateid.value=str;   
   document.stuarriveinfoForm.action="rcvmanageAction.do?method=view";
   document.stuarriveinfoForm.submit();
}

function DoExport(){

   document.all.doexl.value="1";
   if(document.all.timeselect.checked){
       document.all.arriveTime.value=document.all.time.getTime();
       //alert(document.all.arriveTime.value);
   }
   else
       document.all.arriveTime.value="";

   document.all.hstudentNo.value=document.all.studentNo.value;
   document.all.hclassNo.value=document.all.classNo.value;
   document.forms[0].elements["stuarriveinfo.enrollNo"].value="";
   document.forms[0].elements["stuarriveinfo.trainNo"].value=document.all.trainNo.value;
   if(document.all.arriveDate.value!='')
       document.forms[0].elements["stuarriveinfo.arriveDate"].value=document.all.arriveDate.value;
       
   if(document.all.timeselect.checked&&document.all.arriveTime.value!='00:00:01')
       document.forms[0].elements["stuarriveinfo.arriveTime"].value=document.all.arriveTime.value;
       
   document.forms[0].elements["stuarriveinfo.arrivePlace"].value=document.all.arrivePlace.value;
   
   document.stuarriveinfoForm.action="rcvmanageAction.do?method=jiezhanfind";
   document.stuarriveinfoForm.submit();

}

</script>

<script language="JavaScript">

//==================================================== �����趨���� =======================================================
var bMoveable=true;		//���������Ƿ�����϶�
var _VersionInfo="Version:2.0&#13;2.0����:walkingpoison&#13;1.0����: F.R.Huang(meizz)&#13;MAIL: meizz@hzcnc.com"	//�汾��Ϣ

//==================================================== WEB ҳ����ʾ���� =====================================================
var strFrame;		//����������HTML����
document.writeln('<iframe id=meizzDateLayer Author=wayx frameborder=0 style="position: absolute; width: 144; height: 211; z-index: 9998; display: none"></iframe>');
strFrame='<style>';
strFrame+='INPUT.button{BORDER-RIGHT: #FF9999 1px solid;BORDER-TOP: #DCC9CA 1px solid;BORDER-LEFT: #DCC9CA 1px solid;';
strFrame+='BORDER-BOTTOM: #DCC9CA 1px solid;BACKGROUND-COLOR: #DCC9CA;font-family:����;}';
strFrame+='TD{FONT-SIZE: 9pt;font-family:����;}';
strFrame+='</style>';
strFrame+='<scr' + 'ipt>';
strFrame+='var datelayerx,datelayery;	/*��������ؼ������λ��*/';
strFrame+='var bDrag;	/*����Ƿ�ʼ�϶�*/';
strFrame+='function document.onmousemove()	/*������ƶ��¼��У������ʼ�϶����������ƶ�����*/';
strFrame+='{if(bDrag && window.event.button==1)';
strFrame+='	{var DateLayer=parent.document.all.meizzDateLayer.style;';
strFrame+='		DateLayer.posLeft += window.event.clientX-datelayerx;/*����ÿ���ƶ��Ժ����λ�ö��ָ�Ϊ��ʼ��λ�ã����д����div�в�ͬ*/';
strFrame+='		DateLayer.posTop += window.event.clientY-datelayery;}}';
strFrame+='function DragStart()		/*��ʼ�����϶�*/';
strFrame+='{var DateLayer=parent.document.all.meizzDateLayer.style;';
strFrame+='	datelayerx=window.event.clientX;';
strFrame+='	datelayery=window.event.clientY;';
strFrame+='	bDrag=true;}';
strFrame+='function DragEnd(){		/*���������϶�*/';
strFrame+='	bDrag=false;}';
strFrame+='</scr' + 'ipt>';
strFrame+='<div style="z-index:9999;position: absolute; left:0; top:0;" onselectstart="return false"><span id=tmpSelectYearLayer Author=wayx style="z-index: 9999;position: absolute;top: 3; left: 19;display: none"></span>';
strFrame+='<span id=tmpSelectMonthLayer Author=wayx style="z-index: 9999;position: absolute;top: 3; left: 78;display: none"></span>';
strFrame+='<table border=1 cellspacing=0 cellpadding=0 width=142 height=160 bordercolor=#DCC9CA bgcolor=#DCC9CA Author="wayx">';
strFrame+='  <tr Author="wayx"><td width=142 height=23 Author="wayx" bgcolor=#FFFFFF><table border=0 cellspacing=1 cellpadding=0 width=140 Author="wayx" height=23>';
strFrame+='      <tr align=center Author="wayx"><td width=16 align=center bgcolor=#DCC9CA style="font-size:12px;cursor: hand;color: #ffffff" ';
strFrame+='        onclick="parent.meizzPrevM()" title="��ǰ�� 1 ��" Author=meizz><b Author=meizz>&lt;</b>';
strFrame+='        </td><td width=60 align=center style="font-size:12px;cursor:default" Author=meizz ';
strFrame+='onmouseover="style.backgroundColor=\'#0099FF\'" onmouseout="style.backgroundColor=\'white\'" ';
strFrame+='onclick="parent.tmpSelectYearInnerHTML(this.innerText.substring(0,4))" title="�������ѡ�����"><span Author=meizz id=meizzYearHead></span></td>';
strFrame+='<td width=48 align=center style="font-size:12px;cursor:default" Author=meizz onmouseover="style.backgroundColor=\'#0099FF\'" ';
strFrame+=' onmouseout="style.backgroundColor=\'white\'" onclick="parent.tmpSelectMonthInnerHTML(this.innerText.length==3?this.innerText.substring(0,1):this.innerText.substring(0,2))"';
strFrame+='        title="�������ѡ���·�"><span id=meizzMonthHead Author=meizz></span></td>';
strFrame+='        <td width=16 bgcolor=#DCC9CA align=center style="font-size:12px;cursor: hand;color: #ffffff" ';
strFrame+='         onclick="parent.meizzNextM()" title="��� 1 ��" Author=meizz><b Author=meizz>&gt;</b></td></tr>';
strFrame+='    </table></td></tr>';
strFrame+='  <tr Author="wayx"><td width=142 height=18 Author="wayx">';
strFrame+='<table border=1 cellspacing=0 cellpadding=0 bgcolor=#DCC9CA ' + (bMoveable? 'onmousedown="DragStart()" onmouseup="DragEnd()"':'');
strFrame+=' BORDERCOLORLIGHT=#DCC9CA BORDERCOLORDARK=#FFFFFF width=140 height=20 Author="wayx" style="cursor:' + (bMoveable ? 'move':'default') + '">';
strFrame+='<tr Author="wayx" align=center valign=bottom><td style="font-size:12px;color:#FFFFFF" Author=meizz>��</td>';
strFrame+='<td style="font-size:12px;color:#FFFFFF" Author=meizz>һ</td><td style="font-size:12px;color:#FFFFFF" Author=meizz>��</td>';
strFrame+='<td style="font-size:12px;color:#FFFFFF" Author=meizz>��</td><td style="font-size:12px;color:#FFFFFF" Author=meizz>��</td>';
strFrame+='<td style="font-size:12px;color:#FFFFFF" Author=meizz>��</td><td style="font-size:12px;color:#FFFFFF" Author=meizz>��</td></tr>';
strFrame+='</table></td></tr><!-- Author:F.R.Huang(meizz) http://www.meizz.com/ mail: meizz@hzcnc.com 2002-10-8 -->';
strFrame+='  <tr Author="wayx"><td width=142 height=120 Author="wayx">';
strFrame+='    <table border=1 cellspacing=2 cellpadding=0 BORDERCOLORLIGHT=#DCC9CA BORDERCOLORDARK=#FFFFFF bgcolor=#DCC9CA width=140 height=120 Author="wayx">';
var n=0; for (j=0;j<5;j++){ strFrame+= ' <tr align=center Author="wayx">'; for (i=0;i<7;i++){
strFrame+='<td width=20 height=20 id=meizzDay'+n+' style="font-size:12px" Author=meizz onclick=parent.meizzDayClick(this.innerText,0)></td>';n++;}
strFrame+='</tr>';}
strFrame+='      <tr align=center Author="wayx">';
for (i=35;i<39;i++)strFrame+='<td width=20 height=20 id=meizzDay'+i+' style="font-size:12px" Author=wayx onclick="parent.meizzDayClick(this.innerText,0)"></td>';
strFrame+='        <td colspan=3 align=right Author=meizz><span onclick=parent.closeLayer() style="font-size:12px;cursor: hand"';
strFrame+='         Author=meizz title="' + _VersionInfo + '"><u>�ر�</u></span>&nbsp;</td></tr>';
strFrame+='    </table></td></tr><tr Author="wayx"><td Author="wayx">';
strFrame+='        <table border=0 cellspacing=1 cellpadding=0 width=100% Author="wayx" bgcolor=#FFFFFF>';
strFrame+='          <tr Author="wayx"><td Author=meizz align=left><input Author=meizz type=button class=button value="<<" title="��ǰ�� 1 ��" onclick="parent.meizzPrevY()" ';
strFrame+='             onfocus="this.blur()" style="font-size: 12px; height: 20px"><input Author=meizz class=button title="��ǰ�� 1 ��" type=button ';
strFrame+='             value="< " onclick="parent.meizzPrevM()" onfocus="this.blur()" style="font-size: 12px; height: 20px"></td><td ';
strFrame+='             Author=meizz align=center><input Author=meizz type=button class=button value=���� ';
strFrame+='             onfocus="this.blur()" title="��ǰ����" style="font-size: 12px; height: 20px; cursor:hand"></td><td ';
strFrame+='             Author=meizz align=right><input Author=meizz type=button class=button value=" >" onclick="parent.meizzNextM()" ';
strFrame+='             onfocus="this.blur()" title="��� 1 ��" class=button style="font-size: 12px; height: 20px"><input ';
strFrame+='             Author=meizz type=button class=button value=">>" title="��� 1 ��" onclick="parent.meizzNextY()"';
strFrame+='             onfocus="this.blur()" style="font-size: 12px; height: 20px"></td>';
strFrame+='</tr></table></td></tr></table></div>';

window.frames.meizzDateLayer.document.writeln(strFrame);
window.frames.meizzDateLayer.document.close();		//���ie������������������

//==================================================== WEB ҳ����ʾ���� ======================================================
var outObject;
var outButton;		//����İ�ť
var outDate="";		//��Ŷ��������
var odatelayer=window.frames.meizzDateLayer.document.all;		//�����������
function setday(tt,obj) //��������
{
	if (arguments.length >  2){alert("�Բ��𣡴��뱾�ؼ��Ĳ���̫�࣡");return;}
	if (arguments.length == 0){alert("�Բ�����û�д��ر��ؼ��κβ�����");return;}
	var dads  = document.all.meizzDateLayer.style;
	var th = tt;
	var ttop  = tt.offsetTop;     //TT�ؼ��Ķ�λ���
	var thei  = tt.clientHeight;  //TT�ؼ�����ĸ�
	var tleft = tt.offsetLeft;    //TT�ؼ��Ķ�λ���
	var ttyp  = tt.type;          //TT�ؼ�������
	while (tt = tt.offsetParent){ttop+=tt.offsetTop; tleft+=tt.offsetLeft;}
	dads.top  = (ttyp=="image")? ttop+thei : ttop+thei+6;
	dads.left = tleft;
	outObject = (arguments.length == 1) ? th : obj;
	outButton = (arguments.length == 1) ? null : th;	//�趨�ⲿ����İ�ť
	//���ݵ�ǰ������������ʾ����������
	var reg = /^(\d+)-(\d{1,2})-(\d{1,2})$/;
	var r = outObject.value.match(reg);
	if(r!=null){
		r[2]=r[2]-1;
		var d= new Date(r[1], r[2],r[3]);
		if(d.getFullYear()==r[1] && d.getMonth()==r[2] && d.getDate()==r[3]){
			outDate=d;		//�����ⲿ���������
		}
		else outDate="";
			meizzSetDay(r[1],r[2]+1);
	}
	else{
		outDate="";
		meizzSetDay(new Date().getFullYear(), new Date().getMonth() + 1);
	}
	dads.display = '';

	event.returnValue=false;
}

var MonHead = new Array(12);    		   //����������ÿ���µ��������
    MonHead[0] = 31; MonHead[1] = 28; MonHead[2] = 31; MonHead[3] = 30; MonHead[4]  = 31; MonHead[5]  = 30;
    MonHead[6] = 31; MonHead[7] = 31; MonHead[8] = 30; MonHead[9] = 31; MonHead[10] = 30; MonHead[11] = 31;

var meizzTheYear=new Date().getFullYear(); //������ı����ĳ�ʼֵ
var meizzTheMonth=new Date().getMonth()+1; //�����µı����ĳ�ʼֵ
var meizzWDay=new Array(39);               //����д���ڵ�����

function document.onclick() //������ʱ�رոÿؼ�	//ie6�����������������л����㴦�����
{
  with(window.event)
  { if (srcElement.getAttribute("Author")==null && srcElement != outObject && srcElement != outButton)
    closeLayer();
  }
}

function document.onkeyup()		//��Esc���رգ��л�����ر�
  {
    if (window.event.keyCode==27){
		if(outObject)outObject.blur();
		closeLayer();
	}
	else if(document.activeElement)
		if(document.activeElement.getAttribute("Author")==null && document.activeElement != outObject && document.activeElement != outButton)
		{
			closeLayer();
		}
  }

function meizzWriteHead(yy,mm)  //�� head ��д�뵱ǰ��������
  {
	odatelayer.meizzYearHead.innerText  = yy + " ��";
    odatelayer.meizzMonthHead.innerText = mm + " ��";
  }

function tmpSelectYearInnerHTML(strYear) //��ݵ�������
{
  if (strYear.match(/\D/)!=null){alert("�����������������֣�");return;}
  var m = (strYear) ? strYear : new Date().getFullYear();
  if (m < 1000 || m > 9999) {alert("���ֵ���� 1000 �� 9999 ֮�䣡");return;}
  var n = m - 80;
  if (n < 1000) n = 1000;
  if (n + 26 > 9999) n = 9974;
  var s = "<select Author=meizz name=tmpSelectYear style='font-size: 12px' "
     s += "onblur='document.all.tmpSelectYearLayer.style.display=\"none\"' "
     s += "onchange='document.all.tmpSelectYearLayer.style.display=\"none\";"
     s += "parent.meizzTheYear = this.value; parent.meizzSetDay(parent.meizzTheYear,parent.meizzTheMonth)'>\r\n";
  var selectInnerHTML = s;
  for (var i = n; i < n + 161; i++)
  {
    if (i == m)
       {selectInnerHTML += "<option Author=wayx value='" + i + "' selected>" + i + "��" + "</option>\r\n";}
    else {selectInnerHTML += "<option Author=wayx value='" + i + "'>" + i + "��" + "</option>\r\n";}
  }
  selectInnerHTML += "</select>";
  odatelayer.tmpSelectYearLayer.style.display="";
  odatelayer.tmpSelectYearLayer.innerHTML = selectInnerHTML;
  odatelayer.tmpSelectYear.focus();
}

function tmpSelectMonthInnerHTML(strMonth) //�·ݵ�������
{
  if (strMonth.match(/\D/)!=null){alert("�·���������������֣�");return;}
  var m = (strMonth) ? strMonth : new Date().getMonth() + 1;
  var s = "<select Author=meizz name=tmpSelectMonth style='font-size: 12px' "
     s += "onblur='document.all.tmpSelectMonthLayer.style.display=\"none\"' "
     s += "onchange='document.all.tmpSelectMonthLayer.style.display=\"none\";"
     s += "parent.meizzTheMonth = this.value; parent.meizzSetDay(parent.meizzTheYear,parent.meizzTheMonth)'>\r\n";
  var selectInnerHTML = s;
  for (var i = 1; i < 13; i++)
  {
    if (i == m)
       {selectInnerHTML += "<option Author=wayx value='"+i+"' selected>"+i+"��"+"</option>\r\n";}
    else {selectInnerHTML += "<option Author=wayx value='"+i+"'>"+i+"��"+"</option>\r\n";}
  }
  selectInnerHTML += "</select>";
  odatelayer.tmpSelectMonthLayer.style.display="";
  odatelayer.tmpSelectMonthLayer.innerHTML = selectInnerHTML;
  odatelayer.tmpSelectMonth.focus();
}

function closeLayer()               //�����Ĺر�
  {
    document.all.meizzDateLayer.style.display="none";
  }

function IsPinYear(year)            //�ж��Ƿ���ƽ��
  {
    if (0==year%4&&((year%100!=0)||(year%400==0))) return true;else return false;
  }

function GetMonthCount(year,month)  //�������Ϊ29��
  {
    var c=MonHead[month-1];if((month==2)&&IsPinYear(year)) c++;return c;
  }
function GetDOW(day,month,year)     //��ĳ������ڼ�
  {
    var dt=new Date(year,month-1,day).getDay()/7; return dt;
  }

function meizzPrevY()  //��ǰ�� Year
  {
    if(meizzTheYear > 999 && meizzTheYear <10000){meizzTheYear--;}
    else{alert("��ݳ�����Χ��1000-9999����");}
    meizzSetDay(meizzTheYear,meizzTheMonth);
  }
function meizzNextY()  //���� Year
  {
    if(meizzTheYear > 999 && meizzTheYear <10000){meizzTheYear++;}
    else{alert("��ݳ�����Χ��1000-9999����");}
    meizzSetDay(meizzTheYear,meizzTheMonth);
  }
function meizzToday()  //Today Button
  {
	var today;
    meizzTheYear = new Date().getFullYear();
    meizzTheMonth = new Date().getMonth()+1;
    today=new Date().getDate();
    //meizzSetDay(meizzTheYear,meizzTheMonth);
    if(outObject){
		outObject.value=meizzTheYear + "-" + meizzTheMonth + "-" + today;
    }
    closeLayer();
  }
function meizzPrevM()  //��ǰ���·�
  {
    if(meizzTheMonth>1){meizzTheMonth--}else{meizzTheYear--;meizzTheMonth=12;}
    meizzSetDay(meizzTheYear,meizzTheMonth);
  }
function meizzNextM()  //�����·�
  {
    if(meizzTheMonth==12){meizzTheYear++;meizzTheMonth=1}else{meizzTheMonth++}
    meizzSetDay(meizzTheYear,meizzTheMonth);
  }

function meizzSetDay(yy,mm)   //��Ҫ��д����**********
{
  meizzWriteHead(yy,mm);
  //���õ�ǰ���µĹ�������Ϊ����ֵ
  meizzTheYear=yy;
  meizzTheMonth=mm;

  for (var i = 0; i < 39; i++){meizzWDay[i]=""};  //����ʾ�������ȫ�����
  var day1 = 1,day2=1,firstday = new Date(yy,mm-1,1).getDay();  //ĳ�µ�һ������ڼ�
  for (i=0;i<firstday;i++)meizzWDay[i]=GetMonthCount(mm==1?yy-1:yy,mm==1?12:mm-1)-firstday+i+1	//�ϸ��µ������
  for (i = firstday; day1 < GetMonthCount(yy,mm)+1; i++){meizzWDay[i]=day1;day1++;}
  for (i=firstday+GetMonthCount(yy,mm);i<39;i++){meizzWDay[i]=day2;day2++}
  for (i = 0; i < 39; i++)
  { var da = eval("odatelayer.meizzDay"+i)     //��д�µ�һ���µ�������������
    if (meizzWDay[i]!="")
      {
		//��ʼ���߿�
		da.borderColorLight="#DCC9CA";
		da.borderColorDark="#FFFFFF";
		if(i<firstday)		//�ϸ��µĲ���
		{
			da.innerHTML="<b><font color=gray>" + meizzWDay[i] + "</font></b>";
			da.title=(mm==1?12:mm-1) +"��" + meizzWDay[i] + "��";
			da.onclick=Function("meizzDayClick(this.innerText,-1)");
			if(!outDate)
				da.style.backgroundColor = ((mm==1?yy-1:yy) == new Date().getFullYear() &&
					(mm==1?12:mm-1) == new Date().getMonth()+1 && meizzWDay[i] == new Date().getDate()) ?
					 "#0099FF":"#e0e0e0";
			else
			{
				da.style.backgroundColor =((mm==1?yy-1:yy)==outDate.getFullYear() && (mm==1?12:mm-1)== outDate.getMonth() + 1 &&
				meizzWDay[i]==outDate.getDate())? "#9DD8FF" :
				(((mm==1?yy-1:yy) == new Date().getFullYear() && (mm==1?12:mm-1) == new Date().getMonth()+1 &&
				meizzWDay[i] == new Date().getDate()) ? "#0099FF":"#e0e0e0");
				//��ѡ�е�������ʾΪ����ȥ
				if((mm==1?yy-1:yy)==outDate.getFullYear() && (mm==1?12:mm-1)== outDate.getMonth() + 1 &&
				meizzWDay[i]==outDate.getDate())
				{
					da.borderColorLight="#FFFFFF";
					da.borderColorDark="#DCC9CA";
				}
			}
		}
		else if (i>=firstday+GetMonthCount(yy,mm))		//�¸��µĲ���
		{
			da.innerHTML="<b><font color=gray>" + meizzWDay[i] + "</font></b>";
			da.title=(mm==12?1:mm+1) +"��" + meizzWDay[i] + "��";
			da.onclick=Function("meizzDayClick(this.innerText,1)");
			if(!outDate)
				da.style.backgroundColor = ((mm==12?yy+1:yy) == new Date().getFullYear() &&
					(mm==12?1:mm+1) == new Date().getMonth()+1 && meizzWDay[i] == new Date().getDate()) ?
					 "#0099FF":"#e0e0e0";
			else
			{
				da.style.backgroundColor =((mm==12?yy+1:yy)==outDate.getFullYear() && (mm==12?1:mm+1)== outDate.getMonth() + 1 &&
				meizzWDay[i]==outDate.getDate())? "#9DD8FF" :
				(((mm==12?yy+1:yy) == new Date().getFullYear() && (mm==12?1:mm+1) == new Date().getMonth()+1 &&
				meizzWDay[i] == new Date().getDate()) ? "#0099FF":"#e0e0e0");
				//��ѡ�е�������ʾΪ����ȥ
				if((mm==12?yy+1:yy)==outDate.getFullYear() && (mm==12?1:mm+1)== outDate.getMonth() + 1 &&
				meizzWDay[i]==outDate.getDate())
				{
					da.borderColorLight="#FFFFFF";
					da.borderColorDark="#DCC9CA";
				}
			}
		}
		else		//���µĲ���
		{
			da.innerHTML="<b>" + meizzWDay[i] + "</b>";
			da.title=mm +"��" + meizzWDay[i] + "��";
			da.onclick=Function("meizzDayClick(this.innerText,0)");		//��td����onclick�¼��Ĵ���
			//����ǵ�ǰѡ������ڣ�����ʾ����ɫ�ı���������ǵ�ǰ���ڣ�����ʾ����ɫ����
			if(!outDate)
				da.style.backgroundColor = (yy == new Date().getFullYear() && mm == new Date().getMonth()+1 && meizzWDay[i] == new Date().getDate())?
					"#FF6666":"#FFCCCC";
			else
			{
				da.style.backgroundColor =(yy==outDate.getFullYear() && mm== outDate.getMonth() + 1 && meizzWDay[i]==outDate.getDate())?
					"#9DD8FF":((yy == new Date().getFullYear() && mm == new Date().getMonth()+1 && meizzWDay[i] == new Date().getDate())?
					"#FF6666":"#FFCCCC");
				//��ѡ�е�������ʾΪ����ȥ
				if(yy==outDate.getFullYear() && mm== outDate.getMonth() + 1 && meizzWDay[i]==outDate.getDate())
				{
					da.borderColorLight="#FFFFFF";
					da.borderColorDark="#DCC9CA";
				}
			}
		}
        da.style.cursor="hand"
      }
    else{da.innerHTML="";da.style.backgroundColor="";da.style.cursor="default"}
  }
}

function meizzDayClick(n,ex)  //�����ʾ��ѡȡ���ڣ������뺯��*************
{
  var yy=meizzTheYear;
  var mm = parseInt(meizzTheMonth)+ex;	//ex��ʾƫ����������ѡ���ϸ��·ݺ��¸��·ݵ�����
	//�ж��·ݣ������ж�Ӧ�Ĵ���
	if(mm<1){
		yy--;
		mm=12+mm;
	}
	else if(mm>12){
		yy++;
		mm=mm-12;
	}

  if (mm < 10){mm = "0" + mm;}
  if (outObject)
  {
    if (!n) {//outObject.value="";
      return;}
    if ( n < 10){n = "0" + n;}
    outObject.value= yy + "-" + mm + "-" + n ; //ע�����������������ĳ�����Ҫ�ĸ�ʽ
    closeLayer();
  }
  else {closeLayer(); alert("����Ҫ����Ŀؼ����󲢲����ڣ�");}
}

function isQuoteExist(form1)
{
  var fe = form1.elements;
  for (i=0;i<fe.length;i++)
  {
    if ((fe[i].type=="text" || fe[i].type=="password" || fe[i].type=="textarea") && fe[i].value.indexOf("'")!=-1)
    {
       alert('����ֵ�в��ܺ��е�����!!!');
       fe[i].focus();
       return true;
    }
  }
}

</script>