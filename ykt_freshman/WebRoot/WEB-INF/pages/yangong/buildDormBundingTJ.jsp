<%@page pageEncoding="UTF-8"%>
<%@ page import="org.king.classmanage.web.help.MajorinWithStuCount"%>
<%@ page import="java.util.List"%>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="org.king.classmanage.domain.Collegemodel" %>
<%@ include file="../tiles/include.jsp"%>
<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<SCRIPT language=javascript>
function doClose(){
	self.close();
}
</SCRIPT>

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <form>
    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02" style="padding:4px 0px;"><strong><font class="medium">楼绑定结果报表</font></strong><br>
        <br>
        <strong>校区:</strong><%=request.getAttribute("area") %>&nbsp;<strong>区域:</strong><%=request.getAttribute("location") %>&nbsp;<strong>楼号:</strong><%=request.getAttribute("dormitory")%>&nbsp;</td>
    </tr>
    <tr> 
      <td align="center" valign="top" height="10"></td>
    </tr>
    
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
            <tr align="center" valign=center>
              <td valign="middle" class="tableHeader" >房间号</td> 
              <td height="24" valign="middle" class="tableHeader" >性别</td>
              <td valign="middle" class="tableHeader" >院系</td>
              <td valign="middle" class="tableHeader" >绑定人数</td>
            </tr>
                        <logic:present name="list4TJ" scope="request">
            	<logic:iterate name="list4TJ" id="graduate" indexId="i">
            	<c:if test="${i%2 == 0}">
            <tr align="center" valign=center>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="graduate" property="roomNumber" /></td> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:if test="${graduate.gender=='1'}">
              男
              </c:if>
              <c:if test="${graduate.gender=='2'}">
              女
              </c:if>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="graduate" property="deptName" /></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="graduate" property="distributeNum" /></td>
            </tr>
            </c:if>
            <c:if test="${i%2 != 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5">
              <td align="center" valign="middle" ><bean:write name="graduate" property="roomNumber" /></td> 
              <td height="24" align="center" valign="middle" >              <c:if test="${graduate.gender=='1'}">
              男
              </c:if>
              <c:if test="${graduate.gender=='2'}">
              女
              </c:if></td>
              <td align="center" valign="middle" ><bean:write name="graduate" property="deptName" /></td>
              <td align="center" valign="middle" ><bean:write name="graduate" property="distributeNum" /></td>
            </tr>
                        	</c:if>
            	</logic:iterate>
			</logic:present>
          </tbody>
        </table></td>
    </tr>
    <tr>
      <td height="40" align="right"><input name="Submit2" type="button" class="button_nor" onClick="doClose()" value="关 闭" ></td>
    </tr>
  </form>
</table>
</body>

 