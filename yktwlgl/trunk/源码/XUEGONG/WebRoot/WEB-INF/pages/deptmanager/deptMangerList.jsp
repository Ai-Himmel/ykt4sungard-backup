<%@page pageEncoding="GBK"%>
<%@ page import="java.util.*"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<%@ page import="org.king.business.domain.DeptInfo"%>
<html>
	<head>
		<title>上海复旦大学物料库存及仓储管理系统</title>

		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<script src="<c:url value="/pages/scripts/util.js"/>" type="text/javascript"></script>
		<script src="<c:url value="/pages/scripts/selectbox.js"/>" type="text/javascript"></script>

	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" onload="init();">

		<%String curentDeptName = "";
			DeptInfo deptInfo = new DeptInfo();
			if (request.getSession().getAttribute("currentDept") != null) {
				deptInfo = (DeptInfo) request.getSession().getAttribute(
						"currentDept");
			}
			curentDeptName = deptInfo.getDeptName();

			%>
		<br>
		<br>

		<form name="form1" action="deptManager.do?method=load4AllManager" method=post>
			<jodd:form bean="request">
				<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
					<tr>
						<td align="left" valign="top">
							<table width="100%" border="0" cellspacing="0" cellpadding="0">
								<tr>
									<td height="25" align="left" valign="top">
										<table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
											<tr>
												<td width="10" bgcolor="#0066CA">
													&nbsp;
												</td>
												<td bgcolor="#0066CA" class="mediumwhite">
													部门管理员一览
												</td>
												<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
											</tr>
										</table>
									</td>
								</tr>
								<tr>
									<td height="40" align="center" valign="top">
										<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
											<tbody>
											<input type="hidden" name="updateid" value="">											
												<tr align="center" valign=center>
													<td width="15%" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
														人员工号
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<input type="text" name="searchCode" class="input_box" maxlength=20>
													</td>
													<td width="15%" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
														人员姓名
													</td>
													<td align="left" valign="middle" class="tableHeader3">
														<input type="text" name="searchName" class="input_box" maxlength=20>
													</td>
												</tr>
											</tbody>
										</table>
									</td>
								</tr>

								</jodd:form>
								<tr>
									<td height="40" align="right" valign="middle" class="tdborder02">
										<input name="Submit" type="submit" class="button_nor" value="查 询">
										<input name="bclear" type="button" class="button_nor" value="重 置" onclick="DoClear()">
									</td>
								</tr>
							<logic:present name="msg" scope="request">
								<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
							</logic:present>
							<logic:notPresent name="msg" scope="request">
								<input name="hmsg" type="hidden" value="">
							</logic:notPresent>
							<input type="hidden" name="ec_p" value="<%=request.getParameter("ec_p")==null?"1":request.getParameter("ec_p")%>">
							<input type="hidden" name="ec_i" value="<%=request.getParameter("ec_i")==null?"":request.getParameter("ec_i")%>">
							<input type="hidden" name="ec_crd" value="<%=request.getParameter("ec_crd")==null?"":request.getParameter("ec_crd")%>">
							
		</form>

								<tr>
									<td height="35" align="center" valign="middle" class="mediumblack">
										<%=curentDeptName%>
										部门管理员一览
									</td>
								</tr>
								<jodd:form bean="request">
								<tr>
									<td height="20" align="center" valign="middle">
										<ec:table items="deptAllManager" var="manager" rowsDisplayed="10" action="deptManager.do?method=load4AllManager">

											<ec:exportXls fileName="managerList.xls" tooltip="导出 Excel" />
											<ec:parameter name="searchCode" />
											<ec:parameter name="searchName" />
											<ec:row>
												<ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="30" headerStyle="text-align:center" style="text-align: left">
													<input type="checkbox" name="cbgroup" value="${manager.id}" style="border:0px" />
												</ec:column>
												<ec:column property="code" title="管理员工号" headerStyle="text-align:center" style="text-align: left" width="80" />
												<ec:column property="personName" title="管理员姓名" headerStyle="text-align:center" style="text-align: left" width="80" />
												<ec:column property="officePhone" title="座机" headerStyle="text-align:center" style="text-align: left" width="80" />
												<ec:column property="phone" title="手机" headerStyle="text-align:center" style="text-align: left" width="80" />
												<ec:column property="email" title="Email" headerStyle="text-align:center" style="text-align: left" width="80" />
											</ec:row>
										</ec:table>
									</td>
								</tr>
								<%if (((java.util.ArrayList) request.getAttribute("deptAllManager")).size() > 0) {%>
								<tr>
									<td height="40" align="right" valign="middle">
										<input name="Submit3" type="button" class="button_nor" value="修 改" onClick="DoUpdate()">
									</td>
								</tr>
								<%}%>
								</jodd:form>
							</table>
						</td>
					</tr>
				</table>

	</body>
</html>

<SCRIPT language=javascript>

function init(){    
  if(document.form1.hmsg.value=='0')
      alert("您只能维护自己的联系信息！");
}  
function DoUpdate(){

   var sflag=0;
   var cb=0;

   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
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
              alert("请选择要修改的人员记录！");
              return;
          } 
          else
              document.form1.updateid.value=document.all.cbgroup[cb].value;
   } 
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要修改的人员记录！");
              return;        
        }
        else
            document.form1.updateid.value=document.all.cbgroup.value;
   
   }   
   
    document.forms.ec.action="deptManager.do?method=load4Update&personId="+document.form1.updateid.value;
    document.forms.ec.submit();
    
}
function DoClear(){
    document.form1.elements["searchCode"].value="";
    document.form1.elements["searchName"].value="";
}
</SCRIPT>
