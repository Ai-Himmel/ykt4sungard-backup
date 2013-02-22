<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<body onload="init()">
<center>

<html:form action = "studentAction.do?method=search4List">

<br>

<table width="130%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">考生数据维护</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>  
  <tr> 
    <td align="left" valign="top" ><table 
        width=80% border=1 align=left 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign="middle">              
              <td width="10%" align="right" valign="middle" class="tableHeader2" >学号</td>
              <td width="40%" align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_studentno" styleClass="input_box" maxlength="15" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
              </td>
              <td width="10%" align="right" valign="middle" class="tableHeader2" >姓名</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_stuname" styleClass="input_box" maxlength="10" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
              </td>
            </tr>
            <tr align="center" valign="middle">              
              <td width="10%" align="right" valign="middle" class="tableHeader2" >学院</td>
              <td width="40%" align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_deptname" styleClass="input_box" maxlength="10" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
              </td>
              <td width="10%" align="right" valign="middle" class="tableHeader2" >专业</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_majorname" styleClass="input_box" maxlength="10" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
              </td>
            </tr>
            <tr align="center" valign="middle">              
              <td width="10%" align="right" valign="middle" class="tableHeader2" >年级</td>
              <td width="40%" align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_curgrade" styleClass="input_box" maxlength="10" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
              </td>
              <td width="10%" align="right" valign="middle" class="tableHeader2" >班级</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_curclass" styleClass="input_box" maxlength="10" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
              </td>
            </tr>
            <tr align="center" valign="middle">              
              <td width="10%" align="right" valign="middle" class="tableHeader2" >证件类型</td>
              <td width="40%" align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_idtype" styleClass="input_box" maxlength="10" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
              </td>
              <td width="10%" align="right" valign="middle" class="tableHeader2" >证件号码</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_idcard" styleClass="input_box" maxlength="10" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
              </td>
            </tr>
            <tr align="center" valign="middle">              
              <td width="10%" align="right" valign="middle" class="tableHeader2" >考试类别</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_testcatname" style="height:18px; width:300px; border:#000000 solid 1px; margin:0px; padding:0px; FONT-SIZE:12px" maxlength="30" onkeydown="if(event.keyCode==13) document.onkeydown();"/></td>
              <td width="10%" align="right" valign="middle" class="tableHeader2" >是否已报名</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_ifbm" styleClass="select01">
				<html:option value="" >请选择</html:option>
				<html:option value="1" >是</html:option>
				<html:option value="0" >否</html:option>
			  </html:select>
              </td>
            </tr>    
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
              <td width="10%" align="right" valign="middle" class="tableHeader2" >是否已缴费</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_ifpay" styleClass="select01">
				<html:option value="" >请选择</html:option>
				<html:option value="1" >是</html:option>
				<html:option value="0" >否</html:option>
			  </html:select>
			  </td>
            </tr>               
          </tbody>
        </table></td>
  </tr>  
  <tr> 
      <td height="40" align="left" valign="middle" class="tdborder02">
      &nbsp;&nbsp;<input name="Submit" type="button" class="button_nor" value="查 询" onClick="DoFind()"> 
      <input name="Reset" type="button" class="button_nor" value="重 置" onClick="DoClear()">
      </td>
  </tr>  
  <logic:present name="stutestlist" scope="request">
  <tr> 
    <td align="right" valign="middle"><table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF >
      <tr align="center" valign="middle"><td align="left" valign="middle">
      <a href="javascript:DoExport()">考生名单导出<IMG src="./pages/style/default/images/xls.gif" border="0"></a>
      &nbsp;&nbsp;
      <a href="javascript:DoExportPhoto()">考生照片导出<IMG src="./pages/style/default/images/camera.gif" width="22" height="16" border="0"></a>（请在拷贝照片后删除服务器上的照片，以免多次导出照片后造成文件夹过大）
      </td>
      </tr>
      </table>
    </td>
  </tr>
  </logic:present>
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
            <tr align="center" valign=center>
              <td valign="middle" class="tableHeader" >全选<input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
              <td valign="middle" class="tableHeader" >学号</td>              
              <td valign="middle" class="tableHeader" nowrap>姓名</td>              
              <td valign="middle" class="tableHeader" >性别</td>              
              <td valign="middle" class="tableHeader" nowrap>考试</td>
              <td valign="middle" class="tableHeader" nowrap>已报名</td> 
              <td valign="middle" class="tableHeader" nowrap>已缴费</td>    
              <td valign="middle" class="tableHeader" nowrap>成绩</td>  
              <td valign="middle" class="tableHeader" >入学年份</td>
              <td valign="middle" class="tableHeader" >学院</td>
              <td valign="middle" class="tableHeader" >专业</td>
              <td valign="middle" class="tableHeader" >年级</td>
              <td valign="middle" class="tableHeader" >班级</td>
              <td valign="middle" class="tableHeader" >证件类型</td>
              <td valign="middle" class="tableHeader" >证件号码</td>
              <td valign="middle" class="tableHeader" >电子邮件</td>        
            </tr>
          </thead>
            <!--page offset start -->
          <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./studentAction.do" items="<%=listcount%>" index="center" maxPageItems="10" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="method" />    
           <pg:param name="search_studentno" />
           <pg:param name="search_stuname" />
           <pg:param name="search_deptname" />
           <pg:param name="search_majorname" />
           <pg:param name="search_curgrade" />
           <pg:param name="search_curclass" />
           <pg:param name="search_idtype" />
           <pg:param name="search_idcard" />                 
           <pg:param name="search_testcatname" />	
           <pg:param name="search_testid" />
           <pg:param name="search_ifbm" />
           <pg:param name="search_ifpay" />
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
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="testInfo" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="ifBmName"/></td> 
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="ifPayName"/></td>  
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="grades" format="##0.##"/></td>  
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="enrollYear"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="deptName" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="majorName" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="curGrade" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="curClass" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="idType" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="idCard" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="email" />&nbsp;</td>               
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign="middle">             
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><input type="checkbox" name="cbgroup" value="<bean:write name="nl" property="id"/>" onClick="DoSelect(this)"></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="studentNo"/></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="stuName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="gender"/>&nbsp;</td>              
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="testInfo" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="ifBmName"/></td>   
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="ifPayName"/></td> 
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="grades" format="##0.##"/></td> 
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="enrollYear"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="deptName" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="majorName" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="curGrade" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="curClass" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="idType" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="idCard" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="email" />&nbsp;</td>
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
   
  <tr> 
    <td height="40" align="left" valign="middle">
        &nbsp;&nbsp;<input name="add" type="button" class="button_nor" value="添 加" onClick="DoAdd()" >
        <logic:present name="stutestlist" scope="request">
        &nbsp;&nbsp;&nbsp;
        <input name="delete" type="button" class="button_nor" value="删 除" onClick="DoDelete()">
        &nbsp;&nbsp;&nbsp;
        <input name="update" type="button" class="button_nor" value="修 改" onClick="DoUpdate()">
        </logic:present>  
    </td>
  </tr>
</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>
<logic:present name="notdel" scope="request">
  <input name="hnotdel" type="hidden" value="<bean:write name="notdel" />"> 
  </logic:present>
  <logic:notPresent name="notdel" scope="request">
  <input name="hnotdel" type="hidden" value=""> 
</logic:notPresent>
</html:form>
</center>
</body>
<script language="JavaScript">

function init(){
    
    if(document.all.hmsg.value=='0')
        alert("保存成功！");
    else if(document.all.hmsg.value=='9')
        alert("请勿重复保存！");
    else if(document.all.hmsg.value=='d0')
        alert("删除成功！");
    if(document.all.hnotdel.value!='')
        alert(document.all.hnotdel.value+"，不能删除！");
}

function DoClear(){
     
     document.forms[0].elements["search_studentno"].value="";
     document.forms[0].elements["search_stuname"].value="";
     document.forms[0].elements["search_deptname"].value="";
     document.forms[0].elements["search_majorname"].value="";
     document.forms[0].elements["search_curgrade"].value="";
     document.forms[0].elements["search_curclass"].value="";
     document.forms[0].elements["search_idtype"].value="";
     document.forms[0].elements["search_idcard"].value="";     
     document.forms[0].elements["search_testcatname"].value="";
     document.forms[0].elements["search_testid"].value="";
     document.forms[0].elements["search_ifbm"].value="";
     document.forms[0].elements["search_ifpay"].value="";
     
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
   
   document.studentForm.action="studentAction.do?method=search4List";
   document.studentForm.submit();
   
}

function DoExport(){

   document.studentForm.action="studentAction.do?method=exportBm";
   document.studentForm.submit();

}

function DoExportPhoto(){

   document.studentForm.action="studentAction.do?method=exportPhoto";
   document.studentForm.submit();

}

function DoAdd(){
   
   var sflag=0;
   var cb=0;

   document.all.updateid.value="";
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;   
                   cb=i;                                  
              }
          } 
          if(sflag>1){
              alert("每次只可添加一个考生的考试类别！");
              return;
          }          
          else if(sflag==1){          
              document.all.updateid.value=document.all.cbgroup[cb].value;
          }          
   } 
   else if(document.all.cbgroup!=null){
        if(document.all.cbgroup.checked){         
            document.all.updateid.value=document.all.cbgroup.value;
        }           
   }   
   
   if(document.all.updateid.value!='')
       document.studentForm.action="studentAction.do?method=load4addtest";   
   else
       document.studentForm.action="studentAction.do?method=load4add";  
   document.studentForm.submit();
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

function DoDelete(){
 
   var sflag=0;
   
   if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag==0){
              alert("请选择要删除的记录！");
              return;
          } 
   }
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要删除的记录！");
              return;        
        }
   }
   if(confirm("您确定要删除此记录吗？")){   
       document.studentForm.action="studentAction.do?method=delete";       
       document.studentForm.submit();
   }
   else
       return;
  
}
function DoUpdate(){
  
   var sflag=0;
   var cb=0;

   if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;   
                   cb=i;                                  
              }
          } 
          if(sflag>1){
                       alert("只可选择一条记录进行修改！");
                       return;
          }         
          
          else if(sflag==0){
              alert("请选择要修改的记录！");
              return;
          } 
          else
              document.all.updateid.value=document.all.cbgroup[cb].value;
   } 
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要修改的记录！");
              return;        
        }
        else
            document.all.updateid.value=document.all.cbgroup.value;
   
   } 
   document.studentForm.action="studentAction.do?method=load4update";
   document.studentForm.submit();
   

}
</script>
