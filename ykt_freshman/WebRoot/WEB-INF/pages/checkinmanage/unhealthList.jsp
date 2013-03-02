<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "healthAction.do?method=addunhealth">

<br>

<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">体检结果校医院登记</font></strong></td>
    </tr> 
    
    <tr> 
      <td align="center" valign="top" >
      <table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>                      
          <tr align="center" valign=center>
             <td width="15%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
             <td align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
            <td align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
            <td align="left" valign="middle" class="tableHeader3" >
                <input 
                name="stuName" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();">
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
          <tr align="center" valign=center>
          
          <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                <bean:message bundle="checkinmanage" key="checkin.majorin"/> </td>
          <td align="left" valign="middle" class="tableHeader3" >
              <select name="majorin" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="majorinlist" scope="request">
                   <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                    <option value="<bean:write name="ml" property="dictValue"/>"><bean:write name="ml" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
             </select>
          </td> 
          <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                体检结果 </td>
          <td align="left" valign="middle" class="tableHeader3" >
             <select name="ifUnhealthy" class="select01">
                  <option value="" selected>请选择</option>                  
                  <option value="0">未登记/未体检</option>
                  <option value="1">体检合格</option>
                  <option value="2">需复检</option>
                  <option value="3">复检合格</option>                                                    
             </select>
         </td>        
         </tr>
         <logic:present name="stuinfo" scope="request">             
            <input name="hstudentNo" type="hidden" value="<bean:write name="stuinfo" property="studentNo"/>">            
            <input name="hstuName" type="hidden" value="<bean:write name="stuinfo" property="stuName"/>">              
            <input name="hmajorin" type="hidden" value="<bean:write name="stuinfo" property="majorin"/>">
         </logic:present>   
         <logic:notPresent name="stuinfo" scope="request">             
            <input name="hstudentNo" type="hidden" value="">             
            <input name="hstuName" type="hidden" value="">              
            <input name="hmajorin" type="hidden" value="">
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
         <logic:present name="ifUnhealthy" scope="request">
             <input name="hifUnhealthy" type="hidden" value="<bean:write name="ifUnhealthy" />"> 
             </logic:present>   
         <logic:notPresent name="ifUnhealthy" scope="request">  
             <input name="hifUnhealthy" type="hidden" value="">
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
    
    <tr> 
      <td height="30" align="left" valign="middle" class="medium">
      <span class="medium">&nbsp;</span></td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
          <tbody><input type="hidden" name="updatestate" value=""><input type="hidden" name="method" value="unhealthlist">
          <logic:present name="unhealthlist" scope="request">
           <thead>
            <tr align="center" valign=center>  
              <td width="4%" valign="middle" class="tableHeader" >&nbsp;</td> 
              <td width="8%" valign="middle" class="tableHeader" nowrap>书院</td>           
              <td width="6%" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td width="8%" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td width="8%" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width="4%" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td width="10%" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="checkin.majorin"/></td> 
              <td width="8%" valign="middle" class="tableHeader" >报到</td>             
              <td width="6%" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="health.healthresult"/></td>
              <td width="6%" valign="middle" class="tableHeader" nowrap>辅导员</td>
              <td width="15%" valign="middle" class="tableHeader" nowrap>联系方式</td>
              <td width="6%" valign="middle" class="tableHeader" nowrap>登记人</td>
              <td valign="middle" class="tableHeader" >登记时间</td>
            </tr>
            </thead>
           <!--page offset start -->
           <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./healthAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <%-- keep track of preference --%>   
            <pg:param name="method" />        
           <pg:param name="hstudentNo" />           
           <pg:param name="hstuName" />           
		   <pg:param name="hmajorin" />
		   <pg:param name="hcollegeId" />
		   <pg:param name="hclassNo" />
		   <pg:param name="hifUnhealthy" />
            
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
            <logic:iterate name="unhealthlist" id="cl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center>  
            <td align="center" valign="middle" bgcolor="#FFFFFF" ><input type="checkbox" name="cbgroup" value="<bean:write name="cl" property="id"/>"></td>             
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="collegeName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" nowrap><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <bean:write name="cl" property="genderName"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <bean:write name="cl" property="majorinName"/>&nbsp;
              </td>   
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.ifCheckedin == '1'}"><bean:message bundle="checkinmanage" key="checkin.checkedin"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifCheckedin == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/></strong></font>
              </c:when></c:choose>&nbsp;
              </td>           
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.ifUnhealthy == '0'}"><font size="2.5" color="#990000"></c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '1'}"><font size="2.5" color="#006600"></c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '2'}"><font size="2.5" color="#CC9900"></c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '3'}"><font size="2.5" color="#006600"></c:when></c:choose>
              <bean:write name="cl" property="ifUnhealthyName"/>
              </font>&nbsp;
              </td> 
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="managerName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="contact"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="updatorId"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="updateTime" formatKey="dateTimeFormat"/>&nbsp;</td>             
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5">
            <td align="center" valign="middle" bgcolor="#F6F4F5"><input type="checkbox" name="cbgroup" value="<bean:write name="cl" property="id"/>"></td>              
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="collegeName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="classNo"/></td>
              <td align="center" valign="middle" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" nowrap><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <bean:write name="cl" property="genderName"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <bean:write name="cl" property="majorinName"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.ifCheckedin == '1'}"><bean:message bundle="checkinmanage" key="checkin.checkedin"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifCheckedin == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/></strong></font>
              </c:when></c:choose>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <c:choose><c:when test="${cl.ifUnhealthy == '0'}"><font size="2.5" color="#990000"></c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '1'}"><font size="2.5" color="#006600"></c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '2'}"><font size="2.5" color="#CC9900"></c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '3'}"><font size="2.5" color="#006600"></c:when></c:choose>
              <bean:write name="cl" property="ifUnhealthyName"/>
              </font>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="managerName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="contact"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="updatorId"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="updateTime" formatKey="dateTimeFormat"/>&nbsp;</td>              
            </tr>
            </c:when></c:choose> 
            <input type="hidden" name="studentNo<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="studentNo"/>">
            <input type="hidden" name="enrollNo<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="enrollNo"/>">
            <input type="hidden" name="enrollYear<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="enrollYear"/>">
            <input type="hidden" name="ifUnhealthy<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="ifUnhealthy"/>">
            <input type="hidden" name="ifDeleted<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="ifDeleted"/>">
            <input type="hidden" name="updatorId<bean:write name="cl" property="id"/>" value="<%=(String)session.getAttribute("personName")%>">             
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
          
          <logic:notPresent name="unhealthlist" scope="request">
          <!--page offset start -->
		  <pg:pager url="./unhealthpageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="20" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="hstudentNo" />           
           <pg:param name="hstuName" />           
		   <pg:param name="hmajorin" />
		   <pg:param name="hcollegeId" />
		   <pg:param name="hclassNo" />
		   <pg:param name="hifUnhealthy" />
		   
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">
			
		    <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
		  </tbody>
        </table></td>
    </tr>
            </logic:notPresent>    
          
    <logic:present name="unhealthlist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
    </td>
    </tr>  
    
    <tr> 
    <td height="40" align="left" valign="middle">    
        <input name="selectall" type="button" class="button_nor" value="全 选" onClick="DoSelectall()" >   
        <input name="notselectall" type="button" class="button_nor" value="全不选" onClick="DoNotselectall()" >
        <input name="reverseselect" type="button" class="button_nor" value="反 选" onClick="DoReverseselect()" >
        <span style="width: 350">&nbsp;</span>
        <input name="notcome" type="button" class="button_nor" value="未体检" onClick="DoUpdate('0')" >   
        <input name="oncegood" type="button" class="button_nor" value="体检合格" onClick="DoUpdate('1')" >
        <input name="needtwice" type="button" class="button_nor" value="需复检" onClick="DoUpdate('2')" >
        <input name="twicegood" type="button" class="button_nor" value="复检合格" onClick="DoUpdate('3')" >        
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
    
  for(var i=0;i<document.all.majorin.length;i++){
       if(document.all.hmajorin.value==document.all.majorin[i].value)
            document.all.majorin[i].selected=true;
   
   } 
   
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
   
   for(var i=0;i<document.all.ifUnhealthy.length;i++){
       if(document.all.hifUnhealthy.value==document.all.ifUnhealthy[i].value)
            document.all.ifUnhealthy[i].selected=true;
   
   }   
   
   if(document.all.hmsg.value=='0')
      alert("保存成功!");
   else if(document.all.hmsg.value=='1')
      alert("保存失败!");
   
}

function DoClear(){
     
   document.all.studentNo.value="";
   document.all.stuName.value="";   
   
   document.all.majorin.options[0].selected=true;
   document.all.classNo.options[0].selected=true;
   document.all.collegeId.options[0].selected=true;
   document.all.ifUnhealthy.options[0].selected=true;   
   
   document.all.hstudentNo.value="";   
   document.all.hstuName.value="";
   document.all.hmajorin.value="";
   
   document.all.hcollegeId.value="";
   document.all.hclassNo.value="";
   
   document.all.hifUnhealthy.value="";
   
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
   
   document.forms[0].elements["pager.offset"].value="0";   
   
   document.all.hstudentNo.value=document.all.studentNo.value;   
   document.all.hstuName.value=document.all.stuName.value;
   document.all.hmajorin.value=document.all.majorin.value;
   
   document.all.hcollegeId.value=document.all.collegeId.value;
   document.all.hclassNo.value=document.all.classNo.value;
   document.all.hifUnhealthy.value=document.all.ifUnhealthy.value;
   
   document.stuhealthinfoForm.action="healthAction.do?method=unhealthlist";
   document.stuhealthinfoForm.submit();
   
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

function DoSelectall(){

  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=true;       
  }
  else{
       alert("当前无记录！");
  }
  

}

function DoNotselectall(){
  
  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=false;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=false;       
  }
  else{
       alert("当前无记录！");
  }

}

function DoReverseselect(){
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
           if(document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=false;
           else if(!document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
      if(document.all.cbgroup.checked)
          document.all.cbgroup.checked=false; 
      else if(!document.all.cbgroup.checked)
          document.all.cbgroup.checked=true;    
  }
  else{
       alert("当前无记录！");
  }
  

}

function DoUpdate(str){
   var sflag=0;
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag==0){
              alert("请选择要登记的新生体检记录！");
              return;
          } 
   }
   else if(document.all.cbgroup!=null){
        if(!document.all.cbgroup.checked){
              alert("请选择要登记的新生体检记录！");
              return;        
        }
   }
   else{
      alert("当前无记录！");   
      return;
   }
   document.all.updatestate.value=str;
   document.stuhealthinfoForm.action="healthAction.do?method=update";
   document.stuhealthinfoForm.submit();


}

</script>