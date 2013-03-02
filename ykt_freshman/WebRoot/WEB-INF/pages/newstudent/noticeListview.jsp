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

<html:form action = "noticeAction.do?method=stufind">

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
        width=90% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign=center>               
              <td height="24" width="10%" align="left" valign="middle" class="tableHeader2" >公告标题</td>
              <td width="70%" align="left" valign="middle" class="tableHeader3" colspan="2">
              <input name="title" style="height:18px; width:480px; border:#000000 solid 1px; margin:0px; padding:0px; FONT-SIZE:12px" maxlength=50 value=""></td>
            <td width="20%" align="left" valign="middle" class="tableHeader3" >
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
    <td align="right" valign="middle">&nbsp;</td>    
  </tr>
   <tr> 
    <td align="right" valign="middle">&nbsp;</td>    
  </tr>
  <tr> 
      <td align="left" valign="top">
      <table width=90% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input type="hidden" name="updateid" value="">
          <logic:present name="noticelist" scope="request">
          <thead>
            <tr align="center" valign=center>              
              <td height="24" width=80% valign="middle" class="tableHeader" colspan="5">公告标题</td>              
              <td width=15% valign="middle" class="tableHeader" >最后更新时间</td>
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
              <td width=60% height="24" align="left" valign="middle" bgcolor="#FFFFFF" colspan="5"><a href="javascript:DoView('<bean:write name="nl" property="id"/>')"><bean:write name="nl" property="title"/></a></td>
              <td width=25% align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="updateTime" formatKey="dateTimeFormat"/></td>      
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center>
              <td width=60% height="24" align="left" valign="middle" bgcolor="#F6F4F5"  colspan="5"><a href="javascript:DoView('<bean:write name="nl" property="id"/>')"><bean:write name="nl" property="title"/></a></td>
              <td width=25% align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="updateTime" formatKey="dateTimeFormat"/></td>              
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
              <td width=60% height="24" valign="middle" class="tableHeader" colspan="5">公告标题</td>              
              <td width=25% valign="middle" class="tableHeader" >最后更新时间</td>
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

</table>
</html:form>
</center>

<script language="JavaScript">

setTimeout('init()',500);

function init(){
     
     document.all.title.value=document.forms[0].elements["notice.title"].value;
    
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
          
   document.noticeForm.action="noticeAction.do?method=stufind";
   document.noticeForm.submit();
   
}

function DoView(str){

   document.all.updateid.value=str;
   //alert(document.all.updateid.value);
   document.noticeForm.action="noticeAction.do?method=stuview";
   document.noticeForm.submit();
}

</script>
