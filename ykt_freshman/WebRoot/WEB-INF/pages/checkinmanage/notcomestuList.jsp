<%@page pageEncoding="GBK"%>

<%@ include file="../tiles/include.jsp"%>

<center>

	<html:form action="checkinsubminAction.do?method=tongjisubmit">
		<html:errors />
		<br>

		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02"> 
					<strong><font class="medium">明确不来与申请保留入学资格新生宿舍表</font></strong>
				</td>
			</tr>

			<tr>
				<td height="30" align="right" valign="middle" colspan="2">
					<logic:present name="checkinlist" scope="request">
						<a href="javascript:DoExport()">导出Excel<IMG src="./pages/style/default/images/xls.gif" border="0"></a>
					</logic:present>
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="40" align="center" valign="top">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
						<tbody>
							<input name="orderby" type="hidden" value="">
							<input name="doexl" type="hidden" value="">
							<tr align="center" valign=center>
								<td height="24" valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')"><bean:message bundle="checkinmanage" key="checkin.studentNo" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('stuName')"><bean:message bundle="checkinmanage" key="checkin.stuName" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('gender')"><bean:message bundle="checkinmanage" key="checkin.gender" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('fromProvince')">生源地</a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('department')">录取院系</a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('majorin')">录取专业</a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('classNo')"><bean:message bundle="checkinmanage" key="checkin.classNo" /></a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('locationName')">校区</a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('dormitoryName')">楼号</a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('room')">宿舍号</a>
								</td>
								<td valign="middle" class="tableHeader">
									<a style="font-size:14px;color: black" href="javascript:DoSort('reason')">未报到原因</a>
								</td>
							</tr>
							<logic:present name="checkinlist" scope="request">
								<logic:iterate name="checkinlist" id="cl" type="java.util.Map" indexId="i">
									<c:choose>
										<c:when test="${i%2 != 0}">
											<tr align="center" valign=center>
												<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="cl" property="studentNo" />
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="cl" property="stuName" />
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<c:choose>
														<c:when test="${cl.gender == '1'}">
															<bean:message bundle="checkinmanage" key="checkin.male" />
														</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${cl.gender == '2'}">
															<bean:message bundle="checkinmanage" key="checkin.female" />
														</c:when>
													</c:choose>
												</td>
												<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
													<logic:present name="arealist" scope="request">
														<logic:iterate name="arealist" id="al" type="java.util.Map">
															<c:choose>
																<c:when test="${al.dictValue == cl.fromProvince}">
																	<bean:write name="al" property="dictCaption" />
																</c:when>
															</c:choose>
														</logic:iterate>
													</logic:present>
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="cl" property="departmentName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<logic:present name="majorinlist" scope="request">
														<logic:iterate name="majorinlist" id="ml" type="java.util.Map">
															<c:choose>
																<c:when test="${ml.dictValue == cl.majorin}">
																	<bean:write name="ml" property="dictCaption" />
																</c:when>
															</c:choose>
														</logic:iterate>
													</logic:present>
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="cl" property="classNo" />
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="cl" property="locationName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="cl" property="dormitoryName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="cl" property="room" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<c:if test="${cl.reason=='00'}">
													明确不来
													</c:if>
													<c:if test="${cl.reason=='02'}">
													申请保留资格
													</c:if>
													&nbsp;
												</td>
											</tr>
										</c:when>
									</c:choose>
									<c:choose>
										<c:when test="${i%2 == 0}">
											<tr align="center" valign=center bgcolor="#F6F4F5">
												<td height="24" align="center" valign="middle">
													<bean:write name="cl" property="studentNo" />
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="cl" property="stuName" />
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<c:choose>
														<c:when test="${cl.gender == '1'}">
															<bean:message bundle="checkinmanage" key="checkin.male" />
														</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${cl.gender == '2'}">
															<bean:message bundle="checkinmanage" key="checkin.female" />
														</c:when>
													</c:choose>
												</td>
												<td height="24" align="center" valign="middle" bgcolor="#F6F4F5">
													<logic:present name="arealist" scope="request">
														<logic:iterate name="arealist" id="al" type="java.util.Map">
															<c:choose>
																<c:when test="${al.dictValue == cl.fromProvince}">
																	<bean:write name="al" property="dictCaption" />
																</c:when>
															</c:choose>
														</logic:iterate>
													</logic:present>
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="cl" property="departmentName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<logic:present name="majorinlist" scope="request">
														<logic:iterate name="majorinlist" id="ml" type="java.util.Map">
															<c:choose>
																<c:when test="${ml.dictValue == cl.majorin}">
																	<bean:write name="ml" property="dictCaption" />
																</c:when>
															</c:choose>
														</logic:iterate>
													</logic:present>
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="cl" property="classNo" />
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="cl" property="locationName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="cl" property="dormitoryName" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="cl" property="room" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<c:if test="${cl.reason=='00'}">
													明确不来
													</c:if>
													<c:if test="${cl.reason=='02'}">
													申请保留资格
													</c:if>
													&nbsp;
												</td>
											</tr>
										</c:when>
									</c:choose>
								</logic:iterate>
							</logic:present>
						</tbody>
					</table>
				</td>
			</tr>
  <tr> 
    <td height="40" align="left" valign="middle">
        <%
        int rowcount=0;
        if(request.getAttribute("listcount")!=null){
        	rowcount=((Integer)request.getAttribute("listcount")).intValue();
        %>       
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
        <%} %>
    </td>
  </tr>	
		</table>
		<logic:present name="order" scope="request">
			<input name="horder" type="hidden" value="<bean:write name="order" />">
		</logic:present>
		<logic:notPresent name="order" scope="request">
			<input name="horder" type="hidden" value="a">
		</logic:notPresent>
	</html:form>
</center>

<script language="JavaScript">

function DoSort(col){
  document.all.doexl.value="";
  document.all.orderby.value=col;
  if(document.all.horder.value=='a')
      document.all.horder.value='d';
  else if(document.all.horder.value=='d')
      document.all.horder.value='a';
      
   document.checkinsubminForm.action="checkinsubminAction.do?method=notcomestu";
   document.checkinsubminForm.submit();
}

function DoExport(){

   document.all.doexl.value="1";
     
   document.checkinsubminForm.action="checkinsubminAction.do?method=notcomestu";
   document.checkinsubminForm.submit();

}
</script>
