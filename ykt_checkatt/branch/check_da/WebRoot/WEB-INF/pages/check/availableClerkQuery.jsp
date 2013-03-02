<%@ page contentType="text/html;charset=UTF-8"%>
<%@ include file="/pages/common/taglibs.jsp"%>


<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<script src="<c:url value="/pages/scripts/option.js"/>" type="text/javascript"></script>
	</head>

	<body>

		<div id="titleDiv" class="pageTitle">
			考勤人员设置
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
			<jodd:form bean="request">
				<form id="queryform" method="post" action="clerkManager.do?method=QueryAvailablePerson" name="Search">
					学/工号:&nbsp;
					<input class="text" type="text" name="search_personCode" size="11" style="width: 80">
					姓&nbsp;&nbsp;名:&nbsp;
					<input class="text" type="text" name="search_personName" size="10" style="width: 80">
					部&nbsp;&nbsp;门:&nbsp;
					<select name="search_department" style="width: 200">
						<option value="all">
							所有
						</option>
						<c:forEach var="department" items="${departList}">
							<option value="<c:out value="${department.dept_code}"/>">
								<c:out value="${department.dept_name}" />
							</option>
						</c:forEach>
					</select>
					人员类别:&nbsp;
					<select name="search_cutType" style="width: 150">
						<option value="all">
							所有
						</option>
						<c:forEach var="cutType" items="${cutTypeList}">
							<option value="<c:out value="${cutType.type}"/>">
								<c:out value="${cutType.name}" />
							</option>
						</c:forEach>
					</select>
					&nbsp;&nbsp;
					<td class='tableHeader'>
						<input name="Submit22" type="button" class="submitButton" value=" 查 询 " onclick="Search.submit();">
						<!--
						&nbsp;&nbsp;
						<input name="Submit22" type="reset" class="submitButton" value=" 重 置 ">
						-->
					<p></p>
				</form>
			</jodd:form>
		</div>

		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<%@ include file="/pages/common/messages.jsp"%>
		<DIV>
		
		<jodd:form bean="request">
		<form name="setupForm"  action="setupClerk.do?method=setupClerk" method="post" >
			<%String groupedlist="";%>
			<input type=hidden name=groupedlist value='<%=groupedlist%>'>
			<tr>
				<td align="left" valign="top" class="tdborder02">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr align="center" valign="top">
							<td width="45%">
								<font color="#FF0000"> 
									<select name="search_scrlist" size="15" style="width:360" multiple ondblclick="transferOption(this.form.search_scrlist, this.form.search_destlist,false)">
										<c:forEach var="personList" items="${searchRes}">
											<option value="<c:out value="${personList.cust_id}"/>">
												<c:out value="${personList.stuemp_no}" />--
												<c:out value="${personList.cust_name}" />
											</option>
										</c:forEach>
				
									</select> 
								</font>
							</td>
							<td width="10%" valign="middle">
								<p>
									<input name="Submit22" type="button" class="button_nor" value="添 加->" onclick="transferOption(this.form.search_scrlist, this.form.search_destlist,false)">
								</p>
								<p>
									<input name="Submit23" type="button" class="button_nor" value="<-删 除" onclick="returnOption(this.form.search_destlist, this.form.search_scrlist,false)">
								</p>
							</td>
							<td width="45%">
								<font color="#FF0000"> 
									<select name="search_destlist" size="15" style="width:360" multiple ondblclick="returnOption(this.form.search_destlist, this.form.search_scrlist,false)">
									</select> 
								</font>
							</td>
						</tr>

					</table>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					&nbsp;
				</td>
			</tr>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td width="8%" height="30" align="left" class="right">
					所属部门:
				</td>
				<td width="20%" align="left" class="right">
					<select name="personDept" style="width: 150">
						<c:forEach var="personDept" items="${personDept}">
							<option value="<c:out value="${personDept.deptId}"/>">
								<c:out value="${personDept.deptName}" />
							</option>
						</c:forEach>
					</select>
				</td>
				<td class="right" width="8%" align="left">
					考勤类别:
				</td>
				<!-- 
				<td width="64%" align="left" class="right">
					<input type="radio" name="isSeat" value="1" checked />
					全职教师
					<input type="radio" name="isSeat" value="2"  />
					教职工
					<input type="radio" name="isSeat" value="3"  />
					其他
				</td>
				-->
				<td width="64%" align="left" class="right">
					<select name="isSeat" style="width: 150">
						<c:forEach var="checkatt" items="${checkattList}">
							<option value="<c:out value="${checkatt.value}"/>">
								<c:out value="${checkatt.caption}" />
							</option>
						</c:forEach>
					</select>
				</td>

			</tr>

		</table>
		<!-- 
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<TR>
				<td width="15%" height="30" align="left" class="right">
					<input type="checkbox" name="aheadOverTime" value="1" />
					提前打卡算加班
				</td>
				<td width="15%" align="left" class="right">
					<input type="checkbox" name="delayOverTime" value="1" />
					推迟打卡算加班
				</td>
				<td width="15%" align="left" class="right">
					<input type="checkbox" name="twoReset" value="1" />
					双休日打卡算加班
				</td>
				<td width="15%" align="left" class="right">
					<input type="checkbox" name="holiday" value="1" />
					节假日打卡算加班
				</td>
				<td width="30%" align="left" class="right">
					加班计算单位：
					<select name="overTimeUnit" style="width: 80">
						<OPTION value="1">1</OPTION>
						<OPTION value="10">10</OPTION>
						<OPTION value="20">20</OPTION>
						<OPTION value="30">30</OPTION>
						<OPTION value="40">40</OPTION>
						<OPTION value="50">50</OPTION>
						<OPTION value="60">60</OPTION>
					</select>
					分钟
				</td>
				
			</TR>
		</table>
		-->
		<P>
		</P>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td colspan="1" >
					<input type="button" class="submitButton" name="submitButton" value=" 设 置 " style="margin-left:380px" onClick="setCmdValue(document.forms.setupForm,'<c:url value="setupClerk.do?method=setupClerk" />');" />
				</td>
			</tr>
		</table>
		</form>
	</jodd:form>
	</DIV>
	</body>

</html>
<script>
  	function setCmdValue(form,action) {      		
		var groupedlist="";
		for (i=0;i<form.search_destlist.options.length;i++){
			groupedlist=groupedlist+form.search_destlist.options[i].value+",";
		}
		form.groupedlist.value = groupedlist;
		form.action = action;
  		form.submit();
  	}   
</script>
