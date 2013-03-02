<%@page pageEncoding="UTF-8"%>
<%@ page import="org.king.classmanage.web.help.MajorinWithStuCount"%>
<%@ page import="java.util.List"%>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="org.king.classmanage.domain.Collegemodel" %>
<%@ include file="../tiles/include.jsp"%>
<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">
<SCRIPT language=javascript>
function typeChange(){
  buildBundSearchForm.action="<c:url value="/deptDormBundTJAction.do"/>?method=deptDormBundTJ";
  buildBundSearchForm.submit();
}

function DoView(areaCode,locationCode,dormitory){
 var url="buildDormBundTJAction.do?method=buildDormBundingTJ&areaCode="+areaCode+"&locationCode="+locationCode+"&dormitoryId="+dormitory;
 var windows="height=700,width=1000,toolbar=no,menubar=no,scrollbars=yes,resizable=no,location=no,status=no";
 window.open(url,"",windows);
}
</SCRIPT>

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium"></font></strong></td>
    </tr>
    <tr> 
      <td align="center" valign="top" height="10"></td>
    </tr>
    <html:form action="/buildDormBundTJAction" method="post">
    <tr> 
      <td align="center" valign="top" ><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff>
          <tbody>
            
            <tr align="center" valign=center> 
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><span class="medium">筛选类别</span></td>
              <td width="35" colspan="3" align="left" valign="middle" class="tableHeader3"><select name="menu1" onChange="typeChange()">
                  <option value="1">按院系查看</option>
                  <option value="2" selected>按楼查看</option>  
                </select></td>
            </tr>           
          </tbody>
        </table></td>
    </tr>

    <tr> 
      <td height="10" align="center" valign="middle" class="medium"></td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
          <tbody>
            <tr align="center" valign=center> 
              <td height="24" valign="middle" class="tableHeader" >校区</td>
              <td valign="middle" class="tableHeader" >区域</td>
              <td valign="middle" class="tableHeader" >楼号</td>
              <td valign="middle" class="tableHeader" >可绑定人数</td>
              <td valign="middle" class="tableHeader" >已绑定人数</td>
            </tr>
            <logic:present name="list4TJ" scope="request">
            	<logic:iterate name="list4TJ" id="graduate" indexId="i">
										<tr align="center" valign="middle">
										  <c:if test="${i%2 == 0}">
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="area" />">
												<bean:write name="graduate" property="area" />
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="location" />">
												<bean:write name="graduate" property="location" />
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="dormitory" />">
												<a href="javascript:DoView('<bean:write name="graduate" property="areaCode" />','<bean:write name="graduate" property="locationCode" />','<bean:write name="graduate" property="dormitoryCode" />')"><bean:write name="graduate" property="dormitory" /></a>
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="canBundNum" />">
												<bean:write name="graduate" property="canBundNum" />
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="bundedNum" />">
												<bean:write name="graduate" property="bundedNum" />
											</td>
										  </c:if>
										  <c:if test="${i%2 != 0}">
										  	<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="area" />">
												<bean:write name="graduate" property="area" />
											</td>
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="location" />">
												<bean:write name="graduate" property="location" />
											</td>
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="dormitory" />">
												<a href="javascript:DoView('<bean:write name="graduate" property="areaCode" />','<bean:write name="graduate" property="locationCode" />','<bean:write name="graduate" property="dormitoryCode" />')"><bean:write name="graduate" property="dormitory" /></a>
											</td>
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="canBundNum" />">
												<bean:write name="graduate" property="canBundNum" />
											</td>
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="bundedNum" />">
												<bean:write name="graduate" property="bundedNum" />
											</td>																				
									      </c:if>
										</tr>
				</logic:iterate>
				
			</logic:present>
			<%if(!request.getAttribute("liBundsize").equals("0")) {%>
			<logic:present name="list4TotalTJ" scope="request">
            	<logic:iterate name="list4TotalTJ" id="grad">
            <tr align="center" valign=center bgcolor="#D0B7B9">
              <td align="center" valign="middle">合计</td>
              <td height="24" align="center" valign="middle" >--</td>
              <td height="24" align="center" valign="middle" >--</td>
              <td align="center" valign="middle" ><bean:write name="grad" property="canBundNum" /></td>
              <td align="center" valign="middle" ><bean:write name="grad" property="bundedNum" /></td>
            </tr>
            	</logic:iterate>
			</logic:present>
			<% }%>
          </tbody>
        </table></td>
    </tr>
    </html:form>
</table>
</body>
