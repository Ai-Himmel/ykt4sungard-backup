<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "testPublicAction.do?method=search4Listview">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">考试信息浏览</font></strong></td>
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
              <td width="15%" align="left" valign="middle" class="tableHeader2" >标题</td>
              <td width="70%" align="left" valign="middle" class="tableHeader3" colspan="2">
              <html:text property="search_title" style="height:18px; width:480px; border:#000000 solid 1px; margin:0px; padding:0px; FONT-SIZE:12px" maxlength="30" onkeydown="if(event.keyCode==13) document.onkeydown();"/></td>
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
          <logic:present name="testpublishlist" scope="request">
          <thead>
            <tr align="center" valign=center>
              <td valign="middle" class="tableHeader" >标题</td>
              <td valign="middle" class="tableHeader" >更新时间</td>              
            </tr>
          </thead>
            <!--page offset start -->
          <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./testPublicAction.do" items="<%=listcount%>" index="center" maxPageItems="10" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="method" />          
           <pg:param name="search_title" />		   
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
			
            <logic:iterate name="testpublishlist" id="nl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign="middle">             
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><a href="javascript:DoView('<bean:write name="nl" property="id"/>')"><bean:write name="nl" property="title"/></a></td>              
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="updateTime" /></td>                    
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign="middle">             
              <td align="left" valign="middle" bgcolor="#F6F4F5" ><a href="javascript:DoView('<bean:write name="nl" property="id"/>')"><bean:write name="nl" property="title"/></a></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="updateTime" /></td>                    
            </tr>
            </c:when></c:choose>
            </pg:item>
            </logic:iterate>
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
            </logic:present>
            <logic:notPresent name="testpublishlist" scope="request">                           
          <!--page offset start -->
		  <pg:pager url="./testPublicAction.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
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
</table>
</html:form>
</center>
<script language="JavaScript">

function DoClear(){
     
     document.forms[0].elements["search_title"].value="";
     
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
                
   document.testPublishForm.action="testPublicAction.do?method=search4Listview";
   document.testPublishForm.submit();
   
}

function DoView(str){

   document.all.updateid.value=str;
   document.testPublishForm.action="testPublicAction.do?method=stuview";
   document.testPublishForm.submit();
}

</script>
