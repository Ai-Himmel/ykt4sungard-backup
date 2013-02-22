<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<body onload="init()">
<center>

<html:form action = "studentAction.do?method=search4historyList">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">历史数据清理</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>  
  <tr> 
    <td align="left" valign="top" ><table 
        width=100% border=1 align=left 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>            
            <tr align="center" valign="middle">              
              <td width="10%" align="right" valign="middle" class="tableHeader2" >考试</td>
              <td align="left" valign="middle" class="tableHeader3" >              
              <html:select property="search_testid" styleClass="select01">
				<html:option value="" >请选择</html:option>
				<logic:present name="testlist" scope="request">
				    <html:options collection="testlist" labelProperty="testInfo" property="id" />
                </logic:present>									
			  </html:select>
			  </td>              
            </tr>               
          </tbody>
        </table></td>
  </tr>  
  <tr> 
      <td height="40" align="right" valign="middle" class="tdborder02">
      &nbsp;&nbsp;<input name="Submit" type="button" class="button_nor" value="查 询" onClick="DoFind()"> 
      <input name="Reset" type="button" class="button_nor" value="重 置" onClick="DoClear()">
      </td>
  </tr>
  <tr> 
    <td align="right" valign="middle">
    &nbsp;
    </td>
  </tr>
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input type="hidden" name="updateid" value="">
          <logic:present name="stutestlist" scope="request">
          <thead>
            <tr align="center" valign="middle">
              <td valign="middle" class="tableHeader" >全选<input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
              <td valign="middle" class="tableHeader" >学号</td>              
              <td valign="middle" class="tableHeader" >姓名</td>              
              <td valign="middle" class="tableHeader" >性别</td> 
              <td valign="middle" class="tableHeader" >入学年份</td>
              <td valign="middle" class="tableHeader" >学院</td>
              <td valign="middle" class="tableHeader" >专业</td>
              <td valign="middle" class="tableHeader" >年级</td>
              <td valign="middle" class="tableHeader" >班级</td>               
              <td valign="middle" class="tableHeader" >考试</td>                
            </tr>
          </thead>
            <!--page offset start -->
          <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./studentAction.do" items="<%=listcount%>" index="center" maxPageItems="10" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="method" />
           <pg:param name="search_testid" />
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
			
            <logic:iterate name="stutestlist" id="nl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign="middle">             
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><input type="checkbox" name="cbgroup" value="<bean:write name="nl" property="id"/>" onClick="DoSelect(this)"></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="studentNo"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="stuName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="gender"/>&nbsp;</td>               
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="enrollYear"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="deptName" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="majorName" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="curGrade" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="curClass" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="testInfo" />&nbsp;</td>              
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign="middle">             
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><input type="checkbox" name="cbgroup" value="<bean:write name="nl" property="id"/>" onClick="DoSelect(this)"></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="studentNo"/></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="stuName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="gender"/>&nbsp;</td>               
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="enrollYear"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="deptName" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="majorName" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="curGrade" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="curClass" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="testInfo" />&nbsp;</td>
            </tr>
            </c:when></c:choose>
            </pg:item>
            </logic:iterate>
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
            </logic:present>
            <logic:notPresent name="stutestlist" scope="request">                           
          <!--page offset start -->
		  <pg:pager url="./studentAction.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->		  
            </logic:notPresent>            
          </tbody>
        </table>
      </td>
  </tr>
  <logic:present name="stutestlist" scope="request"> 
  <tr> 
    <td height="40" align="right" valign="middle">    
        <input name="delete" type="button" class="button_nor" value="删 除" onClick="DoDelete()">
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
</body>
<script language="JavaScript">

function init(){
    
    if(document.all.hmsg.value=='d0')
        alert("删除成功！");
}

function DoClear(){
     
     document.forms[0].elements["search_testid"].value="";
     
}

function DoFind(){

   document.forms[0].elements["pager.offset"].value="0";
   
   document.studentForm.action="studentAction.do?method=search4historyList";
   document.studentForm.submit();
   
}

function DoDelete(){
   
   var sflag=0;
   var cb=0;

   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;   
                   cb=i;                                  
              }
          } 
          if(sflag>0){
              if(confirm("此操作将删除当前所选择的记录，您确定要删除吗？")){
                  document.studentForm.action="studentAction.do?method=deleteselectedHistory";
                  document.studentForm.submit();
              }
              else
                  return;
          }          
          else{
              if(confirm("此操作将删除当前所查询到的所有记录，您确定要删除吗？")){
                  document.studentForm.action="studentAction.do?method=deletefoundHistory";
                  document.studentForm.submit();
               }
               else
                  return;
          }
   } 
   else if(document.all.cbgroup!=null){
        if(document.all.cbgroup.checked){   
            if(confirm("此操作将删除当前所选择的记录，您确定要删除吗？")){
                document.studentForm.action="studentAction.do?method=deleteselectedHistory";
                document.studentForm.submit();
            }
        }  
        else{
            if(confirm("此操作将删除当前所查询到的所有记录，您确定要删除吗？")){
                document.studentForm.action="studentAction.do?method=deletefoundHistory";
                document.studentForm.submit();
            }
            else
                return;
        }         
   }      
}

function DoSelect(cb){

   var sflag=1;;
   var usflag=1;;
  
   if(cb.checked){
   
       document.all.updateid.value=cb.value;

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
}

</script>
