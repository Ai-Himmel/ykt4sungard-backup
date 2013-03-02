<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "stufeeinfoAction.do?method=bookfeenotpaylist">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">书籍费未缴纳名单</font></strong></td>
    </tr>     
    
    <tr> 
      <td align="center" valign="top" >
      <table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody> 
          <tr align="center" valign=center>
             <td width="15%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
             <td align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value=""></td>
            <td align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
            <td align="left" valign="middle" class="tableHeader3" >
                <input 
                name="stuName" class="input_box"  maxlength=50 value="" >
            </td>           
          </tr>
          <tr align="center" valign=center>
           <td align="right" valign="middle" class="tableHeader2" >书院</td>
           <td align="left" valign="middle" class="tableHeader3" >
           <select name="collegeId" class="select01" onChange="setClass(this)">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="collegelist" scope="request">
                   <logic:iterate name="collegelist" id="col" type="java.util.Map">
                    <option value="<bean:write name="col" property="id"/>"><bean:write name="col" property="collegeName"/></option>
                   </logic:iterate>
                   </logic:present>
           </select>                
            </td>
           <td align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
           <td align="left" valign="middle" class="tableHeader3" >
             <select name="classNo" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  
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
    <logic:present name="bookfeenotpaylist" scope="request">
    <tr>
      <td height="30" align="right" valign="middle" colspan="2">      
         <a href="javascript:DoExport()">导出Excel<IMG src="./pages/style/default/images/xls.gif" border="0"></a>      
      </td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
          <tbody>          
           <thead>
            <tr align="center" valign=center> 
              <td height="24" valign="middle" class="tableHeader" >书院</td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.majorin"/></td> 
              <td valign="middle" class="tableHeader" >更新日期</td>
            </tr>
            </thead>
           <!--page offset start -->
           <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./bookfeenotpaypageroll.do" items="<%=listcount%>" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <pg:param name="hstudentNo" />           
            <pg:param name="hstuName" />		   
		    <pg:param name="hcollegeId" />
		    <pg:param name="hclassNo" />
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
            <logic:iterate name="bookfeenotpaylist" id="cl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="collegeName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>              
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="updateTime"  formatKey="dateFormat"/>&nbsp;</td>           
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF"><bean:write name="cl" property="collegeName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF"><bean:write name="cl" property="classNo"/></td>
              <td align="center" valign="middle" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="updateTime"  formatKey="dateFormat"/>&nbsp;</td>
               
            </tr>
            </c:when></c:choose>              
           </pg:item> 
          </logic:iterate>
          <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
          </logic:present>  
          
          <logic:notPresent name="bookfeenotpaylist" scope="request">
          <!--page offset start -->           
		  <pg:pager url="./bookfeenotpaypageroll.do" items="0" index="center" maxPageItems="10" maxIndexPages="50" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
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
          </logic:notPresent>           
          </tbody>
        </table></td>
    </tr>

</table>

</html:form>
</center>

<script>

    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("classlist")!=null)
       resultset=(String[][])request.getAttribute("classlist");//读取数据
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>");//产生javascript二维数组，对应书院、班级
     <%
     }
   }
   %>
   datacount=<%=count%>;
  

</script>


<script language="JavaScript">

setTimeout('DoInit()',20);

function DoInit(){  
  
  document.all.studentNo.value=document.all.hstudentNo.value;  
  document.all.stuName.value=document.all.hstuName.value; 
     
   for(var i=0;i<document.all.collegeId.length;i++){
       if(document.all.hcollegeId.value==document.all.collegeId[i].value){
            document.all.collegeId[i].selected=true;
            if(document.all.hcollegeId.value!=''){
                setClass(document.all.collegeId);
                for(var i=0;i<document.all.classNo.length;i++){
                    if(document.all.hclassNo.value==document.all.classNo[i].value){
                            document.all.classNo[i].selected=true;
                    }
                }
            }
       }
   }   
   
   uniteTable(document.all.maintable,2);//执行测试。
   
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

function DoFind(){
   
   document.all.doexl.value="";
   document.forms[0].elements["pager.offset"].value="0";   
   
   document.all.hstudentNo.value=document.all.studentNo.value;   
   document.all.hstuName.value=document.all.stuName.value;   
   
   document.all.hcollegeId.value=document.all.collegeId.value;
   document.all.hclassNo.value=document.all.classNo.value;
      
   document.stufeeinfoForm.action="stufeeinfoAction.do?method=bookfeenotpaylist";
   document.stufeeinfoForm.submit();
   
}

function DoExport(){

   document.all.doexl.value="1";
   
   document.all.hstudentNo.value=document.all.studentNo.value;   
   document.all.hstuName.value=document.all.stuName.value;   
   
   document.all.hcollegeId.value=document.all.collegeId.value;
   document.all.hclassNo.value=document.all.classNo.value;
      
   document.stufeeinfoForm.action="stufeeinfoAction.do?method=bookfeenotpaylist";
   document.stufeeinfoForm.submit();

}

function setClass(sel){

        var id;        
        var i;        

        id=sel.options[sel.selectedIndex].value;
        document.all.classNo.length=1; //清空原班级列表        

        for (i=0;i < datacount; i++)
        {
            if (dataset[i][1] == id)
            {
                document.all.classNo.options[document.all.classNo.length]=new Option(dataset[i][0], dataset[i][0]);              
                
            }
        }

}

//合并书院、班级单元格
function uniteTable(thistab,colLength){
var rn=thistab.rows.length;//取得行数
var rowspann=0;
for(j=colLength-1;j>=0;j--){//从第0列开始，合并多少列
for(i=rn-1;i>0;i--){//从倒数第一行开始往上检查
if(thistab.rows[i].cells[j].innerText==thistab.rows[i-1].cells[j].innerText&&thistab.rows[i].cells[j].colSpan==thistab.rows[i-1].cells[j].colSpan){//与上面一行比较，如果两行相等就合计当前行的合并行数，并删除当前行。
rowspann+=thistab.rows[i].cells[j].rowSpan;
thistab.rows[i].deleteCell(j);
}else{
thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
rowspann=0;
}
}
//检测无表头的表
if(i==0&&rowspann>0){
thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
rowspann=0;
}

}
}
</script>