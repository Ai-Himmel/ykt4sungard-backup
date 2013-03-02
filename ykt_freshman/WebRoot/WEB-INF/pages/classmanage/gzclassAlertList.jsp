<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "gzclassAction.do?method=classalertfind">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">班级手工调整</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top" ><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign=center> 
              <td width="15%" align="left" valign="middle" class="tableHeader2" >录取通知书号</td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="enrollNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
              <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width="35%" align="left" valign="middle" class="tableHeader3" ><input 
            name="stuName" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
              
            </tr>
            <tr align="center" valign=center> 
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
               <bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td align="left" valign="middle" class="tableHeader3" >
              <input name="gender" type="radio" value="1"><bean:message bundle="checkinmanage" key="checkin.male"/>&nbsp;&nbsp;&nbsp;
              <input name="gender" type="radio" value="2"><bean:message bundle="checkinmanage" key="checkin.female"/>&nbsp;&nbsp;&nbsp;
              <input name="gender" type="radio" value="" checked><bean:message bundle="checkinmanage" key="checkin.unknown"/>
              </td>
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
               高考科类</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <select name="examType" class="select01">
                  <option value="" selected>请选择</option>                  
                  <option value="1">文史</option>
                  <option value="2">理工</option>
                  <option value="3">综合</option>
                </select>
              </td>
            </tr>           
           <tr align="center" valign=center> 
              <td width="15%" align="left" valign="middle" class="tableHeader2" >班级</td>
              <td align="left" valign="middle" class="tableHeader3" colspan="3">
              <select name="classId" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="classlist" scope="request">
                   <logic:iterate name="classlist" id="col" type="java.util.Map">
                    <option value="<bean:write name="col" property="classId"/>"><bean:write name="col" property="classNo"/></option>
                   </logic:iterate>
                   </logic:present>
             </select>
             </td>              
           </tr>
             <logic:present name="enrollNo" scope="request">
             <input name="henrollNo" type="hidden" value="<bean:write name="enrollNo" />"> 
             </logic:present>   
             <logic:notPresent name="enrollNo" scope="request">  
             <input name="henrollNo" type="hidden" value="">
             </logic:notPresent> 
             <logic:present name="stuName" scope="request">
             <input name="hstuName" type="hidden" value="<bean:write name="stuName" />"> 
             </logic:present>   
             <logic:notPresent name="stuName" scope="request">  
             <input name="hstuName" type="hidden" value="">
             </logic:notPresent> 
             <logic:present name="gender" scope="request">
             <input name="hgender" type="hidden" value="<bean:write name="gender" />"> 
             </logic:present>   
             <logic:notPresent name="gender" scope="request">  
             <input name="hgender" type="hidden" value="">
             </logic:notPresent> 
             <logic:present name="examType" scope="request">
             <input name="hexamType" type="hidden" value="<bean:write name="examType" />"> 
             </logic:present>   
             <logic:notPresent name="examType" scope="request">  
             <input name="hexamType" type="hidden" value="">
             </logic:notPresent> 
             <logic:present name="classId" scope="request">
             <input name="hclassId" type="hidden" value="<bean:write name="classId" />"> 
             </logic:present>   
             <logic:notPresent name="classId" scope="request">  
             <input name="hclassId" type="hidden" value="">
             </logic:notPresent>
             <input type="hidden" name="myAction" value="gzclassAction.do?method=classalertfind">
          </tbody>
        </table></td>
  </tr>
  <tr>
    <td height="30" align="right" valign="middle" class="tdborder02"> 
      <input name="Submit" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.lookfor"/>" onClick="DoFind()">
      <input name="Reset" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.reset"/>" onClick="DoClear()"> 
    </td>
  </tr>
  <tr> 
    <td align="right" valign="middle">&nbsp;</td>
  </tr>
  
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input type="hidden" name="updateid" value=""><input type="hidden" name="method" value="stuinfofind">
          <logic:present name="checkinlist" scope="request">
          <thead>
          <tr align="center" > 
          <td align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.selectall"/><input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
          <td align="center" height="24" valign="middle" class="tableHeader" >录取通知书号</td>
          <td align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
          <td align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
          <td align="center" valign="middle" class="tableHeader" >高考科类</td>
          <td align="center" valign="middle" class="tableHeader" >高考总分</td>
          <td align="center" valign="middle" class="tableHeader" >班级</td>
          </tr>
          </thead>          
           <!--page offset start -->
           <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./gzclassAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="method" />
           <pg:param name="hstuName" />
           <pg:param name="henrollNo" />
           <pg:param name="hgender" />
           <pg:param name="hexamType" />
           <pg:param name="hclassId" />
		   
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">  
			
            <logic:iterate name="checkinlist" id="cl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=middle>             
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><input type="checkbox" name="cbgroup" value="<bean:write name="cl" property="id"/>" onClick="DoSelect(this)"></td>
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><a href="javascript:DoView('<bean:write name="cl" property="enrollNo"/>')"><bean:write name="cl" property="enrollNo"/></a></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>              
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                  <c:choose><c:when test="${cl.examType == '1'}">
                    文史
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.examType == '2'}">
                    理工
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.examType == '3'}">
                    综合
                  </c:when></c:choose>
              &nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="totalScore"/></td> 
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="classNo"/>&nbsp;</td>          
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center>              
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><input type="checkbox" name="cbgroup" value="<bean:write name="cl" property="id"/>" onClick="DoSelect(this)"></td>
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" ><a href="javascript:DoView('<bean:write name="cl" property="enrollNo"/>')"><bean:write name="cl" property="enrollNo"/></a></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>              
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.examType == '1'}">
                    文史
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.examType == '2'}">
                    理工
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.examType == '3'}">
                    综合
                  </c:when></c:choose>
              &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="totalScore"/></td>   
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="classNo"/>&nbsp;</td>           
            </tr>            
            </c:when></c:choose> 
             </pg:item>           
            </logic:iterate>
            <jsp:include page="./pagenoexcel.jsp" flush="true" />
            </tbody>
        </table>
      </td>
  </tr>
  <tr> 
    <td height="24" align="left" valign="middle">
        <jsp:include page="./pagenoexcel.jsp" flush="true" />
    </td>
  </tr>
		  </pg:pager>
		  <!-- page offset end -->
            </logic:present>
          
           <logic:notPresent name="checkinlist" scope="request">                  
           <!--page offset start -->
		  <pg:pager url="./stuinfolistpageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="hstuName" />
           <pg:param name="hstudentNo" />
           <pg:param name="hgender" />
           <pg:param name="hexamType" />
		   
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">  
			
			<jsp:include page="./pagenoexcel.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
		  </tbody>
        </table>
      </td>
  </tr>
            </logic:notPresent>
			
            
   <logic:present name="checkinlist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
    </td>
    </tr>  
    <tr> 
    <td height="40" align="left" valign="middle">调整到以下班级：
    <select name="toclassId" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="classlist" scope="request">
                   <logic:iterate name="classlist" id="col" type="java.util.Map">
                    <option value="<bean:write name="col" property="classId"/>"><bean:write name="col" property="classNo"/></option>
                   </logic:iterate>
                   </logic:present>
   </select>&nbsp;
   <input name="classalert" type="button" class="button_nor" value="调 整" onClick="DoClassAlert()" >     
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

<script language="JavaScript">

setTimeout('init()',10);

function init(){
  
  document.all.stuName.value=document.all.hstuName.value;
  document.all.enrollNo.value=document.all.henrollNo.value;        
      
  for(var i=0;i<document.all.gender.length;i++){
       if(document.all.hgender.value==document.all.gender[i].value)
            document.all.gender[i].checked=true;
   
   }
  
  for(var i=0;i<document.all.examType.length;i++){
     
      if(document.all.hexamType.value==document.all.examType.options[i].value)
          document.all.examType.options[i].selected=true;
          
  }  
  
  for(var i=0;i<document.all.classId.length;i++){
       if(document.all.hclassId.value==document.all.classId[i].value){
               document.all.classId[i].selected=true;
       }
   } 
  
  if(document.all.hmsg.value=='0')
      alert("班级手工调整成功!");
  else if(document.all.hmsg.value=='1')
      alert("班级手工调整失败!");
}

function DoClear(){
  
   document.all.stuName.value="";
   document.all.enrollNo.value="";
   
   document.all.gender[2].checked=true;
   document.all.examType.options[0].selected=true;
   document.all.classId.options[0].selected=true;
   
   document.all.henrollNo.value="";
   document.all.hstuName.value="";
   document.all.hexamType.value="";
   document.all.hgender.value="";
   document.all.hclassId.value="";
   
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

function DoSelect(cb){

   var sflag=1;;
   var usflag=1;;
  
   if(cb.checked){
   
       document.all.updateid.value=cb.value;
       //alert(document.all.updateid.value);

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
              document.all.updateid.value="";
          }
       } 
   }
   
}

function DoCheckall(ckall){
   
   if(ckall.checked){
   
      if(document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=true;
       }
       document.all.updateid.value=document.all.cbgroup[document.all.cbgroup.length-1].value;
       }
       else{
          document.all.cbgroup.checked=true;
          document.all.updateid.value =document.all.cbgroup.value;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.cbgroup.length>1){
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=false;
       }
       document.all.updateid.value="";
      }
      else{
         document.all.cbgroup.checked=false;
         document.all.updateid.value="";
      }
   }
   //alert(document.all.updateid.value);

}

function DoFind(){
   
   document.forms[0].elements["pager.offset"].value="0";
   
   document.all.hstuName.value=document.all.stuName.value;
   document.all.henrollNo.value=document.all.enrollNo.value;
   
   for(var i=0;i<document.all.gender.length;i++){
       if(document.all.gender[i].checked)
            document.all.hgender.value=document.all.gender[i].value;
   
   }   
   document.all.hexamType.value=document.all.examType.value;
   document.all.hclassId.value=document.all.classId.value;
   
   document.classForm.action="gzclassAction.do?method=classalertfind";
   document.classForm.submit();
   
}

function DoView(str){

   document.all.updateid.value=str;
   
   document.classForm.action="gzclassAction.do?method=stuinfoview&pager.offset="+document.forms[0].elements["pager.offset"].value;
   document.classForm.submit();
}

function DoClassAlert(){

   if(document.all.updateid.value==""){
        alert("请选择要进行班级手工调整的新生！");
        return;
   }
   if(document.all.toclassId.value==''){
       alert("请选择要调整到的班级！");
       return;
   
   }
   document.classForm.action="gzclassAction.do?method=classalert";
   document.classForm.submit();

}
</script>