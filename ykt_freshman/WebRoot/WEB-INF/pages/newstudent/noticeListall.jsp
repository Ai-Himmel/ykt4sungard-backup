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

<center>

<html:form action = "noticeAction.do?method=find">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">新生入学事项公告</font></strong></td>
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
              <td width="10%" align="left" valign="middle" class="tableHeader2" >公告标题</td>
              <td width="75%" align="left" valign="middle" class="tableHeader3" colspan="2">
              <input name="title" style="height:18px; width:480px; border:#000000 solid 1px; margin:0px; padding:0px; FONT-SIZE:12px" maxlength=50 value=""></td>
            <td width="15%" align="left" valign="middle" class="tableHeader3" >
            <input name="Submit" type="button" class="button_nor" value="查 询" onClick="DoFind()">&nbsp;
      <input name="Reset" type="button" class="button_nor" value="重 置" onClick="DoClear()"> </td>
             </tr>  
            <logic:present name="noticeform" scope="request"> 
            <input name="notice.noticeNo" type="hidden" value="<bean:write name="noticeform" property="noticeNo" />">     
            <input name="notice.title" type="hidden" value="<bean:write name="noticeform" property="title" />"> 
            
            </logic:present>
            <logic:notPresent name="noticeform" scope="request">  
            <input name="notice.noticeNo" type="hidden" value="">                              
            <input name="notice.title" type="hidden" value="">  
            </logic:notPresent>          
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
          <logic:present name="noticelist" scope="request">
          <thead>
            <tr align="center" valign=center>
              <td width="5%" valign="middle" class="tableHeader" >全选<input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
              
              <td width="40%" valign="middle" class="tableHeader" >公告标题</td>     
              <td width="8%" valign="middle" class="tableHeader" >公告状态</td>         
              <td width="8%" valign="middle" class="tableHeader" >创建人</td>
              <td width="12%" valign="middle" class="tableHeader" >创建时间</td>
              <td width="10%" valign="middle" class="tableHeader" >最后更新人</td>
              <td width="15%" valign="middle" class="tableHeader" >最后更新时间</td>              
            </tr>
          </thead>
            <!--page offset start -->
          <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./noticeAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="notice.noticeNo" />
		   <pg:param name="notice.title" />
		   <pg:param name="method" />
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
			
            <logic:iterate name="noticelist" id="nl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center>             
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><input type="checkbox" name="cbgroup" value="<bean:write name="nl" property="id"/>" onClick="DoSelect(this)"></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><a href="javascript:DoView('<bean:write name="nl" property="id"/>')"><bean:write name="nl" property="title"/></a></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${nl.ifDeleted == '0'}">
                    公开
              </c:when></c:choose>
              <c:choose><c:when test="${nl.ifDeleted == '1'}">
                    登录可见
              </c:when></c:choose>
              <c:choose><c:when test="${nl.ifDeleted == '2'}">
                    管理员可见
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="creatorId"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="createTime" formatKey="dateTimeFormat"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="updatorId"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="updateTime" formatKey="dateTimeFormat"/></td>              
                    
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center>             
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><input type="checkbox" name="cbgroup" value="<bean:write name="nl" property="id"/>" onClick="DoSelect(this)"></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" ><a href="javascript:DoView('<bean:write name="nl" property="id"/>')"><bean:write name="nl" property="title"/></a></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${nl.ifDeleted == '0'}">
                    公开
              </c:when></c:choose>
              <c:choose><c:when test="${nl.ifDeleted == '1'}">
                    登录可见
              </c:when></c:choose>
              <c:choose><c:when test="${nl.ifDeleted == '2'}">
                    管理员可见
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="creatorId"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="createTime" formatKey="dateTimeFormat"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="updatorId"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="updateTime" formatKey="dateTimeFormat"/></td> 
                    
            </tr>
            </c:when></c:choose>
            </pg:item>
            </logic:iterate>
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
            </logic:present>
            <logic:notPresent name="noticelist" scope="request">
          <thead>
            <tr align="center" valign=center>
              <td width="30" valign="middle" class="tableHeader" >全选<input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
              
              <td valign="middle" class="tableHeader" >公告标题</td>
              <td valign="middle" class="tableHeader" >公告状态</td>              
              <td valign="middle" class="tableHeader" >创建人</td>
              <td valign="middle" class="tableHeader" >创建时间</td>
              <td valign="middle" class="tableHeader" >最后更新人</td>
              <td valign="middle" class="tableHeader" >最后更新时间</td>              
            </tr>
          </thead>
            <!--page offset start -->
		  <pg:pager url="./noticeAction.do" items="0" index="center" maxPageItems="10" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="notice.noticeNo" />
		   <pg:param name="notice.title" />
		   <pg:param name="method" />
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
        &nbsp;&nbsp;&nbsp;
        <input name="delete" type="button" class="button_nor" value="删 除" onClick="DoDelete()">
        &nbsp;&nbsp;&nbsp;
        <input name="update" type="button" class="button_nor" value="修 改" onClick="DoUpdate()"></td>
  </tr>
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
     
     document.all.title.value=document.forms[0].elements["notice.title"].value;
     
     if(document.all.hmsg.value=='9')
          alert("请勿重复保存！");
     else if(document.all.hmsg.value=='0')
          alert("保存成功！");
     else if(document.all.hmsg.value=='1')
          alert("保存失败！");
     else if(document.all.hmsg.value=='d0')
          alert("删除成功！");
     else if(document.all.hmsg.value=='d1')
          alert("删除失败！");
}

function DoClear(){
     
     document.all.title.value="";
     
     document.forms[0].elements["notice.noticeNo"].value="";
     document.forms[0].elements["notice.title"].value="";
}

function DoFind(){

   document.forms[0].elements["pager.offset"].value="0";
   
   document.forms[0].elements["notice.noticeNo"].value="";
   document.forms[0].elements["notice.title"].value=document.all.title.value;
          
   document.noticeForm.action="noticeAction.do?method=find";
   document.noticeForm.submit();
   
}

function DoAdd(){
   
   document.noticeForm.action="noticeAction.do?method=load4add";   
   document.noticeForm.submit();
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

function DoView(str){

   document.all.updateid.value=str;
   //alert(document.all.updateid.value);
   document.noticeForm.action="noticeAction.do?method=view";
   document.noticeForm.submit();
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
              alert("请选择要删除的公告记录！");
              return;
          } 
   }
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要删除的公告记录！");
              return;        
        }
   }
   if(confirm("您确定要删除此入学事项公告吗？")){   
       document.noticeForm.action="noticeAction.do?method=delete";       
       document.noticeForm.submit();
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
              alert("请选择要修改的公告记录！");
              return;
          } 
          else
              document.all.updateid.value=document.all.cbgroup[cb].value;
   } 
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要修改的公告记录！");
              return;        
        }
        else
            document.all.updateid.value=document.all.cbgroup.value;
   
   } 
   //alert("每次只能选择一条记录进行修改，选择多条记录将仅修改最后一次所选择的记录！");
   document.noticeForm.action="noticeAction.do?method=load4update";
   document.noticeForm.submit();
   

}
</script>
