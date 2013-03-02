<%@page pageEncoding="UTF-8"%>
<%@ page import="org.king.classmanage.web.help.MajorinWithStuCount"%>
<%@ page import="java.util.List"%>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="org.king.classmanage.domain.Collegemodel" %>
<%@ include file="../tiles/include.jsp"%>
<link href="<c:url value="/pages/styles/style.css"/>" rel="stylesheet" type="text/css">

<SCRIPT language=javascript>

function doModify(){
		dormAppSearchForm.action = "<c:url value="/dormAppBillAction.do"/>?method=loadGzDormAppInfo4s";
		dormAppSearchForm.submit();
}
function doDelete(){
    dormAppSearchForm.action = "<c:url value="/dormAppAction.do"/>?method=deleteGzDormAppInfo&tag=1";
	dormAppSearchForm.submit();
}
function my_onload(){	 
	    var sh = '<%=request.getAttribute("show")%>';
	    var msg = '<%=request.getAttribute("msg")%>';
	    if(sh=='null'){
	    	if(msg!='null'){
				alert(msg);
			}
	    }else{
			alert(sh+"参与宿舍自动分配,故无法删除其登记信息"); 	
		}
	 }
	 window.onload=my_onload;
</SCRIPT>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">新生住宿申请登记</font></strong>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="right" valign="middle">
					
				</td>
			</tr>
			
			<tr>
				<td align="center" height="10">
					<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
				</td>
			</tr>
			<tr>
				<td height="40" align="left" valign="top" class="medium">

						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
							<tbody>
							
			<tr>
				<td align="center" valign="top">
					<html:form action="/dormAppAction" method="post">

				</td>
			</tr>
			<tr><td align="center" valign="top"><table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>

								<tr class="tableHeader">
									<td align="center" valign="middle" class="medium" width="6%">
										学号
									</td>
									<td align="center" valign="middle" class="medium" width="6%">
										姓名
									</td>
									<td align="center" valign="middle" class="medium" width="5%">
										性别
									</td>
									<td align="center" valign="middle" class="medium" width="6%">
										班级
									</td>
									<td align="center" valign="middle" class="medium" width="8%">
										录取通知书号
									</td>
									<td align="center" valign="middle" class="medium" width="10%">
										住址所在区县
									</td>
									<td align="center" valign="middle" class="medium" width="19%">
										详细住址
									</td>
									<td align="center" valign="middle" class="medium" width="6%">
										联系电话
									</td>
									<td align="center" valign="middle" class="medium" width="8%">
										是否申请住宿
									</td>
									<td align="center" valign="middle" class="medium" width="24%">
										备注
									</td>
								</tr>


								<logic:present name="graduateList" scope="request">

									<logic:iterate name="graduateList" id="graduate" indexId="i">

										<tr align="center" valign="middle">
											<input type="hidden" name="itemList" value="<bean:write name="graduate" property="id" />">
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="enrollNo" />">
												<bean:write name="graduate" property="stuNo" />
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="stuName" />">
												<bean:write name="graduate" property="stuName" />
											</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="gender" />">
													<c:if test="${graduate.gender=='1'}">
													男
													</c:if>
													<c:if test="${graduate.gender=='2'}">
													女
													</c:if>
												</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="enrollNo" />">
												<bean:write name="graduate" property="classNo" />
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="enrollNo" />">
												<bean:write name="graduate" property="enrollNo" />
											</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="district" />">
													<bean:write name="graduate" property="district" />
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="curAddress" />">
													<bean:write name="graduate" property="curAddress" />
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="curTelephone" />">
													<bean:write name="graduate" property="curTelephone" />
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="ifNeedDorm" />">
												<c:if test="${graduate.ifNeedDorm=='0'}">
													否
												</c:if>
												<c:if test="${graduate.ifNeedDorm=='1'}">
													是
												</c:if>
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="memo" />">
													<bean:write name="graduate" property="memo" />
												</td>
										</tr>
									</logic:iterate>
								</logic:present>
</table>
							</tbody>
						</table>
						<tr>
    <tr> 
      <td height="30" align="right" valign="middle">
        &nbsp;&nbsp; <input name="Submit22" type="button" class="button_nor" value="修改"  onClick="javascript:doModify();">&nbsp;&nbsp; <input name="Submit22" type="button" class="button_nor" value="删除"  onClick="javascript:doDelete();"></td>
    </tr>
	</html:form>
		</table>
	</body>
</center>

