<%@page pageEncoding="GBK"%>
<%@ page import="java.util.Date" %>
<%@ page import="java.text.SimpleDateFormat" %>

<%
  Date now = new Date();

  SimpleDateFormat formatter1 = new SimpleDateFormat ("HH':'mm':'ss");
  String dateStr = formatter1.format(now);
  String hour = dateStr.substring(0,2);
  String minute = dateStr.substring(3,5);
  String second = dateStr.substring(6,8);
%>

<%@ include file = "../tiles/include.jsp"%>
<body onload="init()">
<center>

<html:form action = "testCategoryAction.do?method=search4List">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">考试类别维护</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>  
  <tr> 
    <td align="center" valign="top" ><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign="middle">               
              <td width="15%" align="left" valign="middle" class="tableHeader2" >考试类别</td>
              <td width="70%" align="left" valign="middle" class="tableHeader3" colspan="2">
              <html:text property="search_testcatname" style="height:18px; width:480px; border:#000000 solid 1px; margin:0px; padding:0px; FONT-SIZE:12px" maxlength="30" onkeydown="if(event.keyCode==13) document.onkeydown();"/></td>
              <td width="15%" align="left" valign="middle" class="tableHeader3" >
              <input name="Submit" type="button" class="button_nor" value="查 询" onClick="DoFind()">&nbsp;
              <input name="Reset" type="button" class="button_nor" value="重 置" onClick="DoClear()"> </td>
             </tr>                    
          </tbody>
        </table></td>
  </tr>   
  <tr>
    <td height="30" align="right" valign="middle" class="tdborder02"> 
      
    </td>
  </tr>
  <tr> 
    <td align="right" valign="middle">&nbsp;</td>
  </tr>
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input type="hidden" name="updateid" value="">
          <logic:present name="testcatlist" scope="request">
          <thead>
            <tr align="center" valign=center>
              <td width="5%" valign="middle" class="tableHeader" >全选<input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
              
              <td width="40%" valign="middle" class="tableHeader" >考试类别名称</td>              
              <td width="10%" valign="middle" class="tableHeader" >是否收费</td>
              <td width="10%" valign="middle" class="tableHeader" >收费标准</td>
              <td width="10%" valign="middle" class="tableHeader" >是否使用</td>
              <td width="10%" valign="middle" class="tableHeader" >最后更新人</td>
              <td width="15%" valign="middle" class="tableHeader" >最后更新时间</td>              
            </tr>
          </thead>
            <!--page offset start -->
          <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./testCategoryAction.do" items="<%=listcount%>" index="center" maxPageItems="10" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="method" />          
           <pg:param name="search_testcatname" />		   
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
			
            <logic:iterate name="testcatlist" id="nl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign="middle">             
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><input type="checkbox" name="cbgroup" value="<bean:write name="nl" property="id"/>" onClick="DoSelect(this)"></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><a href="javascript:DoView('<bean:write name="nl" property="id"/>')"><bean:write name="nl" property="testCatName"/></a></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="ifFeeName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="fee" /></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="stateName" /></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="updatorName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="updateTime" /></td>              
                    
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign="middle">             
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><input type="checkbox" name="cbgroup" value="<bean:write name="nl" property="id"/>" onClick="DoSelect(this)"></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" ><a href="javascript:DoView('<bean:write name="nl" property="id"/>')"><bean:write name="nl" property="testCatName"/></a></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="ifFeeName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="fee" /></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="stateName" /></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="updatorName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="updateTime" /></td> 
                    
            </tr>
            </c:when></c:choose>
            </pg:item>
            </logic:iterate>
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
            </logic:present>
            <logic:notPresent name="testcatlist" scope="request">                           
          <!--page offset start -->
		  <pg:pager url="./testCategoryAction.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
			<pg:param name="search_testcatname" />			
           
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
    <td height="40" align="right" valign="middle">
        <input name="add" type="button" class="button_nor" value="添 加" onClick="DoAdd()" >
        <logic:present name="testcatlist" scope="request">
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
        alert(document.all.hnotdel.value+"已被引用，不能删除！");
}

function DoClear(){
     
     document.forms[0].elements["search_testcatname"].value="";
     
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
                
   document.testCatForm.action="testCategoryAction.do?method=search4List";
   document.testCatForm.submit();
   
}

function DoAdd(){
   
   document.testCatForm.action="testCategoryAction.do?method=load4add";   
   document.testCatForm.submit();
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

function DoView(str){

   document.all.updateid.value=str;
   document.testCatForm.action="testCategoryAction.do?method=view";
   document.testCatForm.submit();
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
              alert("请选择要删除的考试类别！");
              return;
          } 
   }
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要删除的考试类别！");
              return;        
        }
   }
   if(confirm("您确定要删除此考试类别吗？")){   
       document.testCatForm.action="testCategoryAction.do?method=delete";       
       document.testCatForm.submit();
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
              alert("请选择要修改的考试类别！");
              return;
          } 
          else
              document.all.updateid.value=document.all.cbgroup[cb].value;
   } 
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要修改的考试类别！");
              return;        
        }
        else
            document.all.updateid.value=document.all.cbgroup.value;
   
   } 
   document.testCatForm.action="testCategoryAction.do?method=load4update";
   document.testCatForm.submit();
   

}
</script>
