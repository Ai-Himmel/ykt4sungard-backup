<%@ page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">宿舍分配结果重置</font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<html:form action="gzclassAction.do?method=dormReset">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
							<tr>								
							<c:choose><c:when test="${dormDistributionResult!=0}">
								<td height="40" align="center" valign="middle" class="tdborder02">
									<FONT color="red" class="medium">系统中已经有 <bean:write name="dormDistributionResult" /> 新生分配到了相应的宿舍</font>
								</td>
							</c:when><c:otherwise>
								<td height="40" align="center" valign="middle" class="tdborder02">
										<FONT color="green" class="medium">系统中所有新生都还没有分配相应的宿舍</font>
								</td>
							</c:otherwise></c:choose>
							</tr>
						</table>
						<c:if test="${dormDistributionResult!=0}">
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<html:submit property="search" styleClass="button_nor" onclick="return checkButton();">
									<bean:message key="button.reset" />
								</html:submit>
							</td>
						</tr>
						</c:if>
					</html:form>
				</td>
			</tr>
			<tr>
				<td align="left" valign="middle">
					<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
				</td>
			</tr>


		</table>
	</body>
</center>
<script language="JavaScript">
function checkButton(){
	if(!confirm("重置工作将清除掉所有新生的宿舍信息，是否继续？")){
		return false;
	}
	return true;			 		
}
	function showError(){
		if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	}

	 window.onload=showError;	
</script>
