<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "studentAction.do?method=tongji4BM">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">考生报名情况统计</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr> 
  <tr> 
    <td align="right" valign="middle">&nbsp;</td>
  </tr>
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>          
          <thead>
            <tr align="center" valign="middle">
              <td height="24" valign="middle" class="tableHeader" rowspan="2">考试</td>              
              <td valign="middle" class="tableHeader" rowspan="2">可报名人数</td>
              <td valign="middle" class="tableHeader" colspan="3">已报名人数</td>              
              <td valign="middle" class="tableHeader" rowspan="2">未报名人数</td>            
            </tr>
            <tr align="center" valign="middle">
              <td valign="middle" class="tableHeader" >已报名</td>
              <td valign="middle" class="tableHeader" >已缴费</td>
              <td valign="middle" class="tableHeader" >未缴费</td>
            </tr>
          </thead>  
          <logic:present name="tongjilist" scope="request">          
            <logic:iterate name="tongjilist" id="tj" type="java.util.Map"  indexId="i">            
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign="middle">             
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="tj" property="testInfo" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="tj" property="stuNum" /></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="tj" property="bmNum"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="tj" property="payNum" /></td> 
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="tj" property="notpayNum" /></td> 
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="tj" property="notbmNum" /></td>                                 
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign="middle">             
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="tj" property="testInfo" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="tj" property="stuNum" /></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="tj" property="bmNum"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="tj" property="payNum" /></td> 
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="tj" property="notpayNum" /></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="tj" property="notbmNum" /></td>                     
            </tr>
            </c:when></c:choose>            
            </logic:iterate>                       
            </logic:present>
           <logic:present name="tongjitotal" scope="request">
           <logic:iterate name="tongjitotal" id="tjt" type="java.util.Map">
           <tr align="center" valign="middle" bgcolor="#FF9999"> 
              <td height="24" align="center" valign="middle"><b>总 计</b></td>
              <td align="center" valign="middle" ><b><bean:write name="tjt" property="stuNum" /></b></td>
              <td align="center" valign="middle" ><b><bean:write name="tjt" property="bmNum"/></b></td>
              <td align="center" valign="middle" ><b><bean:write name="tjt" property="payNum"/></b></td>
              <td align="center" valign="middle" ><b><bean:write name="tjt" property="notpayNum"/></b></td>
              <td align="center" valign="middle" ><b><bean:write name="tjt" property="notbmNum" /></b></td> 
           </logic:iterate> 
           </logic:present>                   
          </tbody>
        </table>
      </td>
  </tr>
</table>
</html:form>
</center>
