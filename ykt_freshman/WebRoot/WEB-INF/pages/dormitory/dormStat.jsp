<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.List"%>
<%@ page import="org.king.dormitorymanage.web.help.DormitoryStatistic"%>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="medium">
				<strong>����ͳ��</strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				<form method="post" name="form1">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolor=#ffffff id=submenu1>
						<tbody>
							<tr align="center" valign="middle" bgcolor="#D6B3B1">
								<td width="20%" valign="middle">
									������������
								</td>
								<td width="20%" height="24" valign="middle">
									����¥��
								</td>
								<td width="15%" valign="middle">
									��ס������
								</td>
								<td width="15%" valign="middle">
									�Ѱ�������
								</td>
								<td width="15%" valign="middle">
									���д�λ��
								</td>
								<td width="15%" valign="middle">
									δ������λ��
								</td>
							</tr>
							<logic:present name="dormStat" scope="request">
								<!--page offset start -->
								<%int dormStatCount = ((Integer) request
					.getAttribute("dormStatCount")).intValue();%>
								<pg:pager url="./DormitoryAction.do" items="<%=dormStatCount%>" index="center" maxPageItems="<%=dormStatCount+1%>" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
									<%-- keep track of preference --%>
									<pg:param name="page" />
									<pg:param name="orderby" />
									<pg:param name="sort" />
									<pg:param name="method" />
									<%-- save pager offset during form changes --%>
									<input type="hidden" name="pager.offset" value="<%= offset %>">
									<logic:iterate name="dormStat" id="dormStat">
									<c:if test="${dormStat.location=='ALLLOC'}">
										<tr align="center" valign="middle" bgcolor="#FF9999">
											<td height="24" align="center" valign="middle">
												�ܼ�
											</td>
											<td align="center" valign="middle">
												����
											</td>
											<td align="center" valign="middle">
												<bean:write name="dormStat" property="totalNumber" />
											</td>
											<td align="center" valign="middle">
												<bean:write name="dormStat" property="studentInCount" />
											</td>
											<td align="center" valign="middle">
												<bean:write name="dormStat" property="nonCount" />
											</td>
											<td align="center" valign="middle">
												<%=request.getAttribute("notcheckindormSum")==null?0:((Integer)request.getAttribute("notcheckindormSum")).intValue()%>
											</td>
										</tr>
									</c:if>
									<c:if test="${dormStat.location!='ALLLOC'}">
										<tr align="center" valign="middle" bgcolor="#FFFFFF">
											<td height="24" align="center" valign="middle" bgcolor="#FFFFFF">
												<bean:write name="dormStat" property="location" />
											</td>
											<td align="center" valign="middle">
												<a href='DormitoryAction.do?method=showRoomStat&Location=<bean:write name="dormStat" property="locationId"/>&Dorm=<bean:write name="dormStat" property="dormitoryId"/>&cw=<bean:write name="dormStat" property="totalNumber"/>&yzrs=<bean:write name="dormStat" property="studentInCount"/>&kxcw=<bean:write name="dormStat" property="nonCount"/>'><bean:write name="dormStat" property="dormitory" /></a>
											</td>
											<td id="<bean:write name="dormStat" property="locationId"/><bean:write name="dormStat" property="dormitoryId"/>.1" align="center" valign="middle">
												<bean:write name="dormStat" property="totalNumber" />
											</td>
											<td id="<bean:write name="dormStat" property="locationId"/><bean:write name="dormStat" property="dormitoryId"/>.2" align="center" valign="middle">
												<bean:write name="dormStat" property="studentInCount" />
											</td>
											<td id="<bean:write name="dormStat" property="locationId"/><bean:write name="dormStat" property="dormitoryId"/>.3" align="center" valign="middle">
												<bean:write name="dormStat" property="nonCount" />
											</td>
											<td id="<bean:write name="dormStat" property="locationId"/><bean:write name="dormStat" property="dormitoryId"/>.4" align="center" valign="middle">
												0
											</td>
										</tr>
									</c:if>
										
									</logic:iterate>
									<jsp:include page="../security/page.jsp" flush="true" />
								</pg:pager>
								<!-- page offset end -->
							</logic:present>
						</tbody>
					</table>
				</form>
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td height="40" align="right" valign="middle">

			</td>
		</tr>
	</table>
</body>

<script language="Javascript">

<%
        List emptyDormStatistic = new ArrayList();
		
		if(request.getAttribute("notcheckindormStat")!=null)
		    emptyDormStatistic=(List)request.getAttribute("notcheckindormStat");	
		
		int totalNum=0;
		int inNum=0;
		int emptyNum=0;
		int notcheckinNum=0;			
		if(emptyDormStatistic!=null&&emptyDormStatistic.size()>0){
			for(int j=0;j<emptyDormStatistic.size();j++){
			    String dormstr ="";	
				DormitoryStatistic emptyDorm = (DormitoryStatistic)emptyDormStatistic.get(j);
				if(!emptyDorm.getLocationId().equals("ALLLOC")){
				    if(emptyDorm.getLocationId()!=null)
				        dormstr=dormstr+emptyDorm.getLocationId();
				    if(emptyDorm.getDormitoryId()!=null)
				        dormstr=dormstr+emptyDorm.getDormitoryId();
				     
				    notcheckinNum=emptyDorm.getStudentInCount();
				%>
								    
				    if(document.getElementById("<%=dormstr%>.4")!=null){
				      <%if(notcheckinNum>0){%>				        
				        var istring="<a href='DormitoryAction.do?method=showNotCheckinRoomStat&Location=<%=emptyDorm.getLocationId()%>&Dorm=<%=emptyDorm.getDormitoryId()%>'><%=notcheckinNum%></a>"
					    document.getElementById("<%=dormstr%>.4").innerHTML=istring;
				      <%}else{%>
				        document.getElementById("<%=dormstr%>.4").innerHTML='<%=notcheckinNum%>';
				      <%}%>
				    
				    }
				
				<%
				}
		   }
		}
%>
</script>