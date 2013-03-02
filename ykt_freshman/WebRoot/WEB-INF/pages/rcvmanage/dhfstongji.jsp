<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>
<html:form action = "rcvmanageAction.do?method=dhfstongji">
<html:errors/>
<br>

<table width="80%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">新生抵沪方式统计</font></strong></td>
    </tr>
    <tr> 
      <td height="30" align="left" valign="middle" class="medium">&nbsp;</td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=50% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=maintable>
          <tbody>     
            <tr align="center" valign=center> 
              <th width=40% height="24" valign="middle" class="tableHeader" >抵沪方式</th>
              <th width=30% valign="middle" class="tableHeader" >人数</th>  
              <th height="24" valign="middle" class="tableHeader" >明细</th>
                                  
            </tr>
            
            
            <logic:present name="tjlist" scope="request">
            <logic:iterate name="tjlist" id="tj" type="java.util.Map" indexId="i">
            <c:choose><c:when test="${i%2 != 0}">            
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.arrivePlace == '01'}">
              火车
              </c:when></c:choose>
              <c:choose><c:when test="${tj.arrivePlace == '02'}">
              长途汽车
              </c:when></c:choose>
              <c:choose><c:when test="${tj.arrivePlace == '03'}">
              飞机
              </c:when></c:choose>
              <c:choose><c:when test="${tj.arrivePlace == '04'}">
              自驾车
              </c:when></c:choose>
              <c:choose><c:when test="${tj.arrivePlace == '05'}">
              其他  
              </c:when></c:choose>
              <c:choose><c:when test="${tj.arrivePlace == '06'}">
              本市  
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.stuNum != null}">      
                <bean:write name="tj" property="stuNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td> 
              <c:choose><c:when test="${tj.arrivePlace == '01'}">
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <table border="0" cellspacing="0" cellpadding="0">
                <tr align="left" valign="middle">
                  <td width="70">上海站:</td> 
                  <td width="20"><%=request.getAttribute("d1")==null?"0":request.getAttribute("d1")%></td>                
                </tr>
                <tr align="left" valign="middle">
                  <td width="70">上海南站:</td> 
                  <td width="20"><%=request.getAttribute("d2")==null?"0":request.getAttribute("d2")%></td>                                    
                </tr>
              </table>
              </td>              
              </c:when><c:when test="${tj.arrivePlace == '03'}">   
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <table border="0" cellspacing="0" cellpadding="0">
                <tr align="left" valign="middle">
                  <td width="70">虹桥机场:</td>   
                  <td width="20"><%=request.getAttribute("d3")==null?"0":request.getAttribute("d3")%></td>               
                </tr>
                <tr align="left" valign="middle">
                  <td width="70">浦东机场:</td> 
                  <td width="20"><%=request.getAttribute("d4")==null?"0":request.getAttribute("d4")%></td>                                    
                </tr>
              </table>
              </td>   
              </c:when><c:otherwise>   
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              &nbsp;
              </td>   
              </c:otherwise></c:choose>                     
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.arrivePlace == '01'}">
              火车
              </c:when></c:choose>
              <c:choose><c:when test="${tj.arrivePlace == '02'}">
              长途汽车
              </c:when></c:choose>
              <c:choose><c:when test="${tj.arrivePlace == '03'}">
              飞机
              </c:when></c:choose>
              <c:choose><c:when test="${tj.arrivePlace == '04'}">
              自驾车
              </c:when></c:choose>
              <c:choose><c:when test="${tj.arrivePlace == '05'}">
              其他  
              </c:when></c:choose>
              <c:choose><c:when test="${tj.arrivePlace == '06'}">
              本市  
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.stuNum != null}">      
                <bean:write name="tj" property="stuNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
               <c:choose><c:when test="${tj.arrivePlace == '01'}">
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <table border="0" cellspacing="0" cellpadding="0">
                <tr align="left" valign="middle">
                  <td width="70">上海站:</td> 
                  <td width="20"><%=request.getAttribute("d1")==null?"0":request.getAttribute("d1")%></td>                
                </tr>
                <tr align="left" valign="middle">
                  <td width="70">上海南站:</td> 
                  <td width="20"><%=request.getAttribute("d2")==null?"0":request.getAttribute("d2")%></td>                                   
                </tr>
              </table>
              </td>              
              </c:when><c:when test="${tj.arrivePlace == '03'}">   
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <table border="0" cellspacing="0" cellpadding="0">
                <tr align="left" valign="middle">
                  <td width="70">虹桥机场:</td>
                  <td width="20"><%=request.getAttribute("d3")==null?"0":request.getAttribute("d3")%></td>                  
                </tr>
                <tr align="left" valign="middle">
                  <td width="70">浦东机场:</td>
                  <td width="20"><%=request.getAttribute("d4")==null?"0":request.getAttribute("d4")%></td>                                 
                </tr>
              </table>
              </td>   
              </c:when><c:otherwise>   
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              &nbsp;
              </td>   
             </c:otherwise></c:choose>
           </tr> 
           </c:when></c:choose>                           
           </logic:iterate>            
           </logic:present>  
            
            
           <logic:present name="notdjNum" scope="request">
          <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" >未填</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" colspan="3"><bean:write name="notdjNum" /></td>
          </tr> 
          </logic:present>             
          </tbody>
        </table></td>
    </tr> 
    <!-- 
    <tr>
    <td height="30" align="right" valign="middle" class="tdborder02"> 
      <input name="exportexcel" type="button" class="button_nor" value="excel" onClick="DoExport()">
             
    </td>
    </tr> 
    <script type="text/javascript" src="<c:url value='/pages/scripts/sorttable.js'/>"></script> 
    -->
</table>

</html:form>
</center>

<script type="text/javascript" src="<c:url value='/pages/scripts/sorttable.js'/>"></script>  

<script language="JavaScript">

//setTimeout("initTable('maintable')",30);

function DoExport(){
document.stuarriveinfoForm.action="rcvmanageAction.do?method=dhfsexcel";
document.stuarriveinfoForm.submit();

}
</script>