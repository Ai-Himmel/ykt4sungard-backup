<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "ygstufeeinfoAction.do?method=dormfeenotpaylist">


<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">ס�޷�δ��������</font></strong></td>
    </tr>     
    
    <tr> 
      <td align="center" valign="top" >
      <table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody> 
          <tr align="center" valign=center>
             <td width="15%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
             <td align="left" valign="middle" class="tableHeader3" ><html:text property="studentNo" styleClass="input_box" maxlength="20"/></td>
            <td align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
            <td align="left" valign="middle" class="tableHeader3" >
                <html:text property="stuName" styleClass="input_box" maxlength="20"/>
            </td>           
          </tr>
          <tr align="center" valign=center>
           <td align="right" valign="middle" class="tableHeader2" >�Ա�</td>
           <td align="left" valign="middle" class="tableHeader3" >
           <select name="gender" class="select01">
				<option value="">---------------------</option>
				<option value="1">��</option>
				<option value="2">Ů</option>
		   </select>                
            </td>
           <td align="right" valign="middle" class="tableHeader2" >ѧ�����</td>
           <td align="left" valign="middle" class="tableHeader3" >
			<select name="studentType" class="select01">
				<option value="">---------------------</option>
				<option value="D">��ʿ��</option>
				<option value="M">˶ʿ��</option>
		   </select> 	
            </td>
          </tr>
          <tr align="center" valign=center>
           <td align="right" valign="middle" class="tableHeader2" >Ժϵ</td>
           <td align="left" valign="middle" class="tableHeader3" >
           <html:select property="collegeId" styleClass="select01" onchange="javascript:setClass(this);" style="width:120">
				<html:option value="">---------------------</html:option>
				<html:options collection="collegelist" property="deptCode" labelProperty="deptName" />
		   </html:select>                
            </td>
           <td align="right" valign="middle" class="tableHeader2" >רҵ</td>
           <td align="left" valign="middle" class="tableHeader3" >
												<html:select property="classNo" styleClass="select01" style="width:120">
													<html:option value="">---------------------</html:option>
													<html:options collection="majorinlist" property="dictValue" labelProperty="dictCaption" />
												</html:select>
            </td>
          </tr>
          
         <logic:present name="stuinfo" scope="request">             
            <input name="hstudentNo" type="hidden" value="<bean:write name="stuinfo" property="graduateNo"/>">            
            <input name="hstuName" type="hidden" value="<bean:write name="stuinfo" property="graduateName"/>">
            <input name="hgender" type="hidden" value="<bean:write name="stuinfo" property="sex"/>">            
            <input name="hstudentType" type="hidden" value="<bean:write name="stuinfo" property="studentType"/>">             
         </logic:present>   
         <logic:notPresent name="stuinfo" scope="request">             
            <input name="hstudentNo" type="hidden" value="">             
            <input name="hstuName" type="hidden" value="">   
            <input name="hgender" type="hidden" value="">            
            <input name="hstudentType" type="hidden" value=""> 
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
    <tr>
			    <td>
			     <table width=100% border=1 align="left" cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=resetFrom>
			            <tr><td align="left">
			            <%if(request.getAttribute("dormdeptname")!=null){ %>
			                  <font class="medium" color="red">ֻ�г�����ס<%=request.getAttribute("dormdeptname")%>����δ�ɷѵ�ѧ����������Դ�ڲ��񴦡�</font>
			           	<%} %>
			                </td>
			                <td align="right">
			                  &nbsp;
			                </td>
			            </tr>
			     </table>
			    </td>
			</tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
          <tbody>          
           <thead>
            <tr align="center" valign=center> 

              <td width=20% height="24" valign="middle" class="tableHeader" >Ժϵ</td>
              <td width=15% valign="middle" class="tableHeader" >רҵ</td>
              <td width=15% valign="middle" class="tableHeader" >ѧ�����</td>
              <td width=10% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td width=10% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width=10% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td width=10% valign="middle" class="tableHeader" >Ӧ�ɽ��</td>
              <td width=10% valign="middle" class="tableHeader" >��������</td>
            </tr>
            </thead>
                <logic:present name="dormfeenotpaylist" scope="request">
           <!--page offset start -->
           <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./ygstufeeinfoAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <pg:param name="method" />
            <pg:param name="hstudentNo" />           
            <pg:param name="hstuName" />
            <pg:param name="hgender" />           
            <pg:param name="hstudentType" />
		    <pg:param name="hcollegeId" />
		    <pg:param name="hclassNo" />
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
            <logic:iterate name="dormfeenotpaylist" id="cl" type="java.util.Map"  indexId="i">
            <pg:item>
            
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center>
           	 <td align="center" valign="middle" bgcolor="#FFFFFF">            
				<bean:write name="cl" property="curCollege"/>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
				<bean:write name="cl" property="speciality"/>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <input type="hidden" name="hmajor" value="<bean:write name="cl" property="speciality"/>">
			  <c:choose><c:when test="${cl.studentType == 'D'}">��ʿ��
              </c:when></c:choose>
              <c:choose><c:when test="${cl.studentType == 'M'}">˶ʿ��
              </c:when></c:choose>
              </td>
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" >
              <bean:write name="cl" property="graduateNo"/>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <bean:write name="cl" property="graduateName"/>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                            <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
            
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="shouldPay"/>&nbsp;</td>       
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="updateTime" formatKey="dateFormat"/>&nbsp;</td>     
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center> 
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
<bean:write name="cl" property="curCollege"/>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
<bean:write name="cl" property="speciality"/>
              </td>
               <td align="center" valign="middle" bgcolor="#FFFFFF" >
               <input type="hidden" name="hmajor" value="<bean:write name="cl" property="speciality"/>">
              <c:choose><c:when test="${cl.studentType == 'D'}">��ʿ��
              </c:when></c:choose>
              <c:choose><c:when test="${cl.studentType == 'M'}">˶ʿ��
              </c:when></c:choose>
              </td>
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" >
              <bean:write name="cl" property="graduateNo"/>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="graduateName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>              
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="shouldPay"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="updateTime"  formatKey="dateFormat"/>&nbsp;</td>                           
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
        <jsp:include page="./pagenoexcel.jsp" flush="true" />
    </td>
  </tr> 
  		  </pg:pager>
		  <!-- page offset end -->
          </logic:present>  
                    <logic:notPresent name="dormfeenotpaylist" scope="request">
          <!--page offset start -->           
		  <pg:pager url="./dormfeenotpaypageroll.do" items="0" index="center" maxPageItems="100" maxIndexPages="50" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <%-- keep track of preference --%>
           <pg:param name="hstudentNo" />           
           <pg:param name="hstuName" />	
           <pg:param name="hgender" />           
            <pg:param name="hstudentType" />	   
		   <pg:param name="hcollegeId" />
		   <pg:param name="hclassNo" />
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
          </logic:notPresent> 
    <logic:present name="dormfeenotpaylist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">��<%=rowcount%>����¼</font>
    </td>
    </tr>  
    </logic:present>
</table>

</html:form>
</center>

<script language="JavaScript">


    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("classlist")!=null)
       resultset=(String[][])request.getAttribute("classlist");//��ȡ����
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//����javascript��ά���飬��ӦѧԺ רҵ
     <%
     
     }
   }
   %>
   datacount=<%=count%>;
  

</script>
<script>
	function setClassbak(college){
		document.all["classNo"].length=0;
		var collegeId=college;
		var j; 
		document.all["classNo"].options[document.all["classNo"].length]= new Option("---------------------","");
			for (j=0;j < datacount; j++) 
			{ 
				if (dataset[j][2] == collegeId) 
				{ 
					document.all["classNo"].options[document.all["classNo"].length]= new Option(dataset[j][1],dataset[j][0]);
				} 
			} 
	} 
	
	function setClass(sel){

        var id;        
        var i;        

        id=sel.options[sel.selectedIndex].value;
        document.all.classNo.length=1; //���ԭ�б�        

        for (i=0;i < datacount; i++)
        {
            if (dataset[i][2] == id)
            {
                document.all.classNo.options[document.all.classNo.length]=new Option(dataset[i][1], dataset[i][0]);              
                
            }
        }

}
setTimeout('DoInit()',5);

function DoInit(){  
  
  document.all.studentNo.value=document.all.hstudentNo.value;  
  document.all.stuName.value=document.all.hstuName.value; 
  
  for(var i=0;i<document.all.collegeId.length;i++){
       if(document.all.hcollegeId.value==document.all.collegeId[i].value){
            document.all.collegeId[i].selected=true;
            if(document.all.hcollegeId.value!=''){
                setClass(document.all.collegeId);
                for(var j=0;j<document.all.classNo.length;j++){
                    if(document.all.hclassNo.value==document.all.classNo[j].value){
                            document.all.classNo[j].selected=true;
                    }
                }
            }
       }
   }
   
   for(var i=0;i<document.all.gender.length;i++){
       if(document.all.hgender.value==document.all.gender[i].value){
            document.all.gender.options[i].selected=true;
            break;
       }
   }
   
   for(var i=0;i<document.all.studentType.length;i++){                              
                                                                             
      if(document.all.hstudentType.value==document.all.studentType.options[i].value){
          document.all.studentType.options[i].selected=true;                     
          break;                                                             
       }                                                                     
  } 
   
   uniteTable(document.all.maintable,3);//ִ�в��ԡ�
   
}

function DoClear(){
     
   document.all.studentNo.value="";
   document.all.stuName.value="";      
   
   document.all.classNo.options[0].selected=true;
   document.all.collegeId.options[0].selected=true;
   
   document.all.gender.options[0].selected=true;
   document.all.studentType.options[0].selected=true;
      
   document.all.hstudentNo.value="";   
   document.all.hstuName.value="";  
   
   document.all.hgender.value="";   
   document.all.hstudentType.value="";  
   
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
   
   document.all.hgender.value=document.all.gender.value;
   document.all.hstudentType.value=document.all.studentType.value;
   
   document.all.hcollegeId.value=document.all.collegeId.value;
   document.all.hclassNo.value=document.all.classNo.value;
      
   document.stufeeinfoForm.action="ygstufeeinfoAction.do?method=dormfeenotpaylist";
   document.stufeeinfoForm.submit();
   
}

function DoExport(){

   document.all.doexl.value="1";
   
   document.all.hstudentNo.value=document.all.studentNo.value;   
   document.all.hstuName.value=document.all.stuName.value;   
   
   document.all.hgender.value=document.all.gender.value;
   document.all.hstudentType.value=document.all.studentType.value;
   
   document.all.hcollegeId.value=document.all.collegeId.value;
   document.all.hclassNo.value=document.all.classNo.value;
      
   document.stufeeinfoForm.action="ygstufeeinfoAction.do?method=dormfeenotpaylist";
   document.stufeeinfoForm.submit();

}

function uniteTable(thistab,colLength){
var rn=thistab.rows.length;//ȡ������
var rowspann=0;

for(j=colLength-1;j>=0;j--){//�ӵ�0�п�ʼ���ϲ�������
for(i=rn-1;i>0;i--){//�ӵ�����һ�п�ʼ���ϼ��

if(thistab.rows[i].cells[j].innerText==thistab.rows[i-1].cells[j].innerText){//������һ�бȽϣ����������ȾͺϼƵ�ǰ�еĺϲ���������ɾ����ǰ�С�
if(thistab.rows[i].cells[j].children(0)!=null&&thistab.rows[i-1].cells[j].children(0)!=null&&thistab.rows[i].cells[j].children(0).value==thistab.rows[i-1].cells[j].children(0).value){//��ǰ��һ�е�ֵ������������,�����������ֵ���ж��Ƿ�����һ�е�ֵһ�����һ���ͺϼƵ�ǰ�еĺϲ���������ɾ����ǰ�С�
	rowspann+=thistab.rows[i].cells[j].rowSpan;	
	thistab.rows[i].deleteCell(j);	
}else if(thistab.rows[i].cells[j].children(0)==null&&thistab.rows[i-1].cells[j].children(0)==null){//�����������ֵ�����һ��������ֻ�ܺϲ�����	    
		rowspann+=thistab.rows[i].cells[j].rowSpan;		
		thistab.rows[i].deleteCell(j);			
}
else{
thistab.rows[i].cells[j].rowSpan+=rowspann;//������Ⱦ���ɵ�ǰ��ͬ���ݵĺϲ���
rowspann=0;
}

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
</script>