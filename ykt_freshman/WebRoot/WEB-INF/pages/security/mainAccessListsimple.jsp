<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "checkinsubminAction.do?method=tongjisubmit">
<html:errors/>
<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">系统登录明细表</font></strong></td>
    </tr>     
    
    <tr>
      <td height="30" align="right" valign="middle" colspan="2">
      &nbsp;
      </td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
            <tr align="center" valign=center> 
              <td height="24" valign="middle" class="tableHeader" >访问日期</td>
              <td valign="middle" class="tableHeader" >访问时间</td>
              <td valign="middle" class="tableHeader" >登录名</td>
              <td valign="middle" class="tableHeader" >姓名</td>
              <td valign="middle" class="tableHeader" >生源地</td>
              <td valign="middle" class="tableHeader" >IP地址</td>
           </tr>
            <logic:present name="accesslist" scope="request">
            <logic:iterate name="accesslist" id="cl" type="java.util.Map"  indexId="i">
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="accessDate"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="accessTime" formatKey="timeFormat"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="userName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="trueName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="fromProvinceName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="accessIp"/>&nbsp;</td>
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" ><bean:write name="cl" property="accessDate"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="accessTime" formatKey="timeFormat"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="userName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="trueName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="fromProvinceName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="accessIp"/>&nbsp;</td>
            </tr>
            </c:when></c:choose>              
          </logic:iterate>
          </logic:present>          
          </tbody>
        </table></td>
    </tr>
    <tr> 
    <td height="40" align="right" valign="middle"> 
      <input name="backbutton" type="button" class="button_nor" value="返 回" onClick="Goback()"> 
    </td>
  </tr>
</table>

</html:form>
</center>

<script language="JavaScript">
 
function Goback(){
  history.go(-1);
}

</script>