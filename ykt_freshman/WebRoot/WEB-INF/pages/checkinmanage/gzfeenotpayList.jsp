<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "gzstufeeinfoAction.do?method=tuitionnotpaylist">

<br>

<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">��ѧ����δ��ѧԺ��ѯ</font></strong></td>
    </tr>     
    
    <tr> 
      <td align="left" valign="top" >
      <table width=100% border=1 align=left cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody> 
          <tr align="center" valign=center>
             <td width="10%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
             <td align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
            <td width="10%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
            <td align="left" valign="middle" class="tableHeader3" >
                <input 
                name="stuName" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();">
            </td>           
          </tr>
          <tr align="center" valign=center>
           <td width="10%" align="right" valign="middle" class="tableHeader2" style="display:none">��Ժ</td>
           <td align="left" valign="middle" class="tableHeader3" style="display:none">
           <select name="collegeId" class="select01" onChange="setClass(this)">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="collegelist" scope="request">
                   <logic:iterate name="collegelist" id="col" type="java.util.Map">
                    <option value="<bean:write name="col" property="id"/>"><bean:write name="col" property="collegeName"/></option>
                   </logic:iterate>
                   </logic:present>
           </select>                
            </td>
           <td width="10%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
           <td align="left" valign="middle" class="tableHeader3" colspan="3">
             <select name="classNo" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="classlist" scope="request">
                   <logic:iterate name="classlist" id="col" type="java.util.Map">
                    <option value="<bean:write name="col" property="classNo"/>"><bean:write name="col" property="classNo"/></option>
                   </logic:iterate>
                   </logic:present>
             </select>
           </td>
          </tr>
          
         <logic:present name="stuinfo" scope="request">             
            <input name="hstudentNo" type="hidden" value="<bean:write name="stuinfo" property="studentNo"/>">            
            <input name="hstuName" type="hidden" value="<bean:write name="stuinfo" property="stuName"/>">            
         </logic:present>   
         <logic:notPresent name="stuinfo" scope="request">             
            <input name="hstudentNo" type="hidden" value="">             
            <input name="hstuName" type="hidden" value="">            
         </logic:notPresent>
         <logic:present name="collegeId" scope="request">
             <input name="hcollegeId" type="hidden" value="<bean:write name="collegeId" />"> 
             </logic:present>   
         <logic:notPresent name="collegeId" scope="request">  
             <input name="hcollegeId" type="hidden" value="">
         </logic:notPresent>
         <logic:present name="classNo" scope="request">
             <input name="hclassNo" type="hidden" value="<bean:write name="classNo" />"> 
             </logic:present>   
         <logic:notPresent name="classNo" scope="request">  
             <input name="hclassNo" type="hidden" value="">
         </logic:notPresent>         
        </tbody>
     </table>
     </td>
    </tr>
    
    <tr>
    <td height="30" align="right" valign="middle" class="tdborder02"> 
      <input name="Submit" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.lookfor"/>" onClick="DoFind()">
      <input name="Reset" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.reset"/>" onClick="DoClear()">        
    </td>
    </tr>
    <input name="doexl" type="hidden" value="">
    <logic:present name="feenotpaylist" scope="request">
    <tr>
      <td height="30" align="right" valign="middle" colspan="2">      
         <a href="javascript:DoExport()">����Excel<IMG src="./pages/style/default/images/xls.gif" border="0"></a>      
      </td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
          <tbody>          
           <thead>
            <tr align="center" valign=center> 
              <td height="24" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td valign="middle" class="tableHeader" style="display:none"><bean:message bundle="checkinmanage" key="checkin.majorin"/></td> 
              <td valign="middle" class="tableHeader" >ѧ��</td> 
              <td valign="middle" class="tableHeader" >��������</td>
              <td valign="middle" class="tableHeader" >ס�޷�</td> 
              <td valign="middle" class="tableHeader" >��������</td>                         
            </tr>
            </thead>
           <!--page offset start -->
           <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./gzstufeeinfoAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <pg:param name="method" />
            <pg:param name="hstudentNo" />           
            <pg:param name="hstuName" />		   
		    <pg:param name="hcollegeId" />
		    <pg:param name="hclassNo" />
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
            <logic:iterate name="feenotpaylist" id="cl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <bean:write name="cl" property="genderName"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" style="display:none">
              <bean:write name="cl" property="majorinName"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.tuitionpayed == '1'}">�ѽ���
              </c:when></c:choose>
              <c:choose><c:when test="${cl.tuitionpayed == '0'}"><font color="#990000"><strong>δ����</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <bean:write name="cl" property="tupdateTime" formatKey="dateFormat"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.dormfeepayed == '2'}">�������
              </c:when></c:choose>
              <c:choose><c:when test="${cl.dormfeepayed == '1'}">�ѽ���
              </c:when></c:choose>
              <c:choose><c:when test="${cl.dormfeepayed == '0'}"><font color="#990000"><strong>δ����</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <bean:write name="cl" property="dupdateTime" formatKey="dateFormat"/>&nbsp;
              </td>                                  
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td align="center" valign="middle" bgcolor="#FFFFFF"><bean:write name="cl" property="classNo"/></td>
              <td height="24" align="center" valign="middle" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <bean:write name="cl" property="genderName"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" style="display:none">
              <bean:write name="cl" property="majorinName"/>&nbsp;
              </td> 
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.tuitionpayed == '1'}">�ѽ���
              </c:when></c:choose>
              <c:choose><c:when test="${cl.tuitionpayed == '0'}"><font color="#990000"><strong>δ����</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <bean:write name="cl" property="tupdateTime" formatKey="dateFormat"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.dormfeepayed == '2'}">�������
              </c:when></c:choose>
              <c:choose><c:when test="${cl.dormfeepayed == '1'}">�ѽ���
              </c:when></c:choose>
              <c:choose><c:when test="${cl.dormfeepayed == '0'}"><font color="#990000"><strong>δ����</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <bean:write name="cl" property="dupdateTime" formatKey="dateFormat"/>&nbsp;
              </td>                                      
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
          
          <logic:notPresent name="feenotpaylist" scope="request">
          <!--page offset start -->           
		  <pg:pager url="./feenotpaypageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <%-- keep track of preference --%>
           <pg:param name="hstudentNo" />           
           <pg:param name="hstuName" />		   
		   <pg:param name="hcollegeId" />
		   <pg:param name="hclassNo" />
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
		  </tbody>
        </table></td>
    </tr>
          </logic:notPresent>         
          
    <logic:present name="feenotpaylist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">��<%=rowcount%>����¼</font>
    </td>
    </tr>  
    </logic:present>
</table>

<!-- 
<table id=theObjTable>
  <tr>
   <td>��htmlҳ����</td>
   <td>����ҳ�еı�</td>
   <td>�����ݵ��뵽</td>
   <td>word��</td>
   <td>Ҳ���Ե��뵽excel</td>
</tr>
</table>
<input type="button" value="����EXCEL���" onclick="tableToExcel()">
-->
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>
</html:form>
</center>

<script language="JavaScript">

setTimeout('DoInit()',20);

function DoInit(){  
  
  document.all.studentNo.value=document.all.hstudentNo.value;  
  document.all.stuName.value=document.all.hstuName.value; 
     
   for(var i=0;i<document.all.classNo.length;i++){
       if(document.all.hclassNo.value==document.all.classNo[i].value){
           document.all.classNo[i].selected=true;
       }
   }
   
   if(document.all.maintable!=null)
       uniteTable(document.all.maintable,1);//ִ�в��ԡ�
   
   if(document.all.hmsg.value=='1')
      alert("����Excel�ɹ�!");
   else if(document.all.hmsg.value=='0')
      alert("������!");
   
}

function DoClear(){
     
   document.all.studentNo.value="";
   document.all.stuName.value="";      
   
   document.all.classNo.options[0].selected=true;
   document.all.collegeId.options[0].selected=true;
      
   document.all.hstudentNo.value="";   
   document.all.hstuName.value="";   
   
   document.all.hcollegeId.value="";
   document.all.hclassNo.value="";
      
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
   
   document.all.doexl.value="";
   document.forms[0].elements["pager.offset"].value="0";   
   
   document.all.hstudentNo.value=document.all.studentNo.value;   
   document.all.hstuName.value=document.all.stuName.value;   
   
   document.all.hcollegeId.value=document.all.collegeId.value;
   document.all.hclassNo.value=document.all.classNo.value;
      
   document.stufeeinfoForm.action="gzstufeeinfoAction.do?method=feenotpaylist";
   document.stufeeinfoForm.submit();
   
}

function DoExport(){

   document.all.doexl.value="1";
   
   document.all.hstudentNo.value=document.all.studentNo.value;   
   document.all.hstuName.value=document.all.stuName.value;   
   
   document.all.hcollegeId.value=document.all.collegeId.value;
   document.all.hclassNo.value=document.all.classNo.value;
      
   document.stufeeinfoForm.action="gzstufeeinfoAction.do?method=feenotpaylist";
   document.stufeeinfoForm.submit();

}

//�ϲ���Ժ���༶��Ԫ��
function uniteTable(thistab,colLength){
var rn=thistab.rows.length;//ȡ������
var rowspann=0;
for(j=colLength-1;j>=0;j--){//�ӵ�0�п�ʼ���ϲ�������
for(i=rn-1;i>0;i--){//�ӵ�����һ�п�ʼ���ϼ��
if(thistab.rows[i].cells[j].innerText==thistab.rows[i-1].cells[j].innerText&&thistab.rows[i].cells[j].colSpan==thistab.rows[i-1].cells[j].colSpan){//������һ�бȽϣ����������ȾͺϼƵ�ǰ�еĺϲ���������ɾ����ǰ�С�
rowspann+=thistab.rows[i].cells[j].rowSpan;
thistab.rows[i].deleteCell(j);
}else{
thistab.rows[i].cells[j].rowSpan+=rowspann;//������Ⱦ���ɵ�ǰ��ͬ���ݵĺϲ���
rowspann=0;
}
}
//����ޱ�ͷ�ı�
if(i==0&&rowspann>0){
thistab.rows[i].cells[j].rowSpan+=rowspann;//������Ⱦ���ɵ�ǰ��ͬ���ݵĺϲ���
rowspann=0;
}

}
}

//����
//����Excel�ļ�
function exportExcel(tableid) 
{  
if (typeof(EXPORT_OBJECT)!="object") 
{  
document.body.insertAdjacentHTML("afterBegin","<OBJECT style='display:none' classid=clsid:0002E510-0000-0000-C000-000000000046 id=EXPORT_OBJECT></Object>");  
}  
with (EXPORT_OBJECT) 
{  
DataType = "HTMLData";  
HTMLData =tableid.outerHTML;  
try 
{  
ActiveSheet.Export("d:\\���.xls", 0);  
alert('�ɹ�����EXCEL���');  
}  
catch (e) 
{  
alert('����EXCEL���ʧ�ܣ���ȷ���Ѱ�װExcel2000(����߰汾),����û��ͬ��xls�ļ�');  
}  
}  
}  

function tableToExcel() { 
window.clipboardData.setData("Text",document.all('theObjTable').outerHTML);
//window.clipboardData.setData("Text",maintable.outerHTML);
alert("1");
try
{
alert("try");
var ExApp = new ActiveXObject("Excel.Application");
alert("2");
var ExWBk = ExApp.workbooks.add();
alert("3");
var ExWSh = ExWBk.worksheets(1);
alert("4");
ExApp.DisplayAlerts = false;
alert("5");
ExApp.visible = true;
alert("6");
}  
catch(e)
{

alert("���ĵ���û�а�װMicrosoft Excel�����");
return false;
} 
 ExWBk.worksheets(1).Paste;
 }


</script>