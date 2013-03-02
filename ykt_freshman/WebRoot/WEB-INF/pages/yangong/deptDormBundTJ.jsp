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
  deptBundSearchForm.action="<c:url value="/buildDormBundTJAction.do"/>?method=buildDormBundTJ";
  deptBundSearchForm.submit();
}

function DoView(code,name){
 var url="deptDormBundTJAction.do?method=deptDormBundingTJ&deptId="+code;
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
    <html:form action="/deptDormBundTJAction" method="post">
    <tr> 
      <td align="center" valign="top" ><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff>
          <tbody>
            <tr align="center" valign=center>
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><span class="medium">筛选类别</span></td>
              <td width="35" colspan="3" align="left" valign="middle" class="tableHeader3"><select name="menu1" onChange="typeChange()">
                  <option value="1" selected>按院系查看</option>
                  <option value="2">按楼查看</option>
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
              <td height="24" valign="middle" class="tableHeader" >院系</td>
              <td valign="middle" class="tableHeader" >性别</td>
              <td valign="middle" class="tableHeader" >应绑定人数</td>
              <td valign="middle" class="tableHeader" >已绑定人数</td>
            </tr>
            <logic:present name="list4TJ" scope="request">
            	<logic:iterate name="list4TJ" id="graduate" indexId="i">
										<tr align="center" valign="middle">
										  <c:if test="${i%2 == 0}">
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="deptName" />">
												<a href="javascript:DoView('<bean:write name="graduate" property="deptCode" />','<bean:write name="graduate" property="gender" />')"><bean:write name="graduate" property="deptName" /></a>
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="sex" />">
												<bean:write name="graduate" property="sex" />
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="bundingNum" />">
												<bean:write name="graduate" property="bundingNum" />
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="bundedNum" />">
												<bean:write name="graduate" property="bundedNum" />
											</td>
										  </c:if>
										  <c:if test="${i%2 != 0}">
										  	<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="deptName" />">
												<a href="javascript:DoView('<bean:write name="graduate" property="deptCode" />','<bean:write name="graduate" property="gender" />')"><bean:write name="graduate" property="deptName" /></a>
											</td>
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="sex" />">
												<bean:write name="graduate" property="sex" />
											</td>
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="bundingNum" />">
												<bean:write name="graduate" property="bundingNum" />
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
              <td align="center" valign="middle" ><bean:write name="grad" property="bundingNum" /></td>
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
