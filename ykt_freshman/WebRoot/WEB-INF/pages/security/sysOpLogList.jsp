<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<center>
	<gui:window title="系统操作日志查询" prototype="boWindow" color="100%">
				<table class="win" CELLPADDING="2" CELLSPACING="0" width="100%">
					<html:form action="sysLogManager.do?method=searchSysOpLog">
						<tr align="right">
							<td>
								开始日期 <input type="text" name="beginDate" value="<c:out value="${beginDate}"/>" style="width:90">
								结束日期 <input type="text" name="endDate" value="<c:out value="${endDate}"/>" style="width:90">
								学工号   <input type="text" name="personCode" value="<c:out value="${personCode}"/>" style="width:90">
								姓名     <input type="text" name="personName" value="<c:out value="${personName}"/>" style="width:90">
								<html:submit styleClass="button">
									<bean:message key="button.search" />
								</html:submit>
							</td>
						</tr>
				</table>
				</html:form>
				<html:form action="sysLogManager.do">
					<input type="hidden" name="method" value="searchSysOpLog">
					<table class="sort-table" cellSpacing="1" cellPadding="1" width="100%" border="0">
						<thead>
							<tr>
								<td COLSPAN="7">
									系统日志
								</td>
							</tr>
						</thead>
						<logic:present name="sysOpLogs" scope="request">
							<thead>
								<tr>
									<td>
										学工号
									</td>
									<td>
										姓名
									</td>

									<td>
										操作时间
									</td>

                                    <td>
										操作功能
									</td>
								</tr>
							</thead>

							<!--page offset start -->
							<%int itemNo = ((Integer) request.getAttribute("logCount")).intValue();%>
							<pg:pager url="./sysLogManager.do" items="<%=itemNo%>" index="center" maxPageItems="10" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
								<%-- keep track of preference --%>
								<pg:param name="beginDate" />
								<pg:param name="endDate" />
								<pg:param name="personCode" />
								<pg:param name="personName" />
								<pg:param name="page" />
								<pg:param name="orderby" />
								<pg:param name="sort" />
								<pg:param name="method" />

							    <pg:param name="style"/>
							    <pg:param name="position"/>
							    <pg:param name="index"/>
							    <pg:param name="maxPageItems"/>
							    <pg:param name="maxIndexPages"/>
							    
								<%-- save pager offset during form changes --%>
								<input type="hidden" name="pager.offset" value="<%= offset %>">
								<logic:iterate name="sysOpLogs" id="log" indexId="i">
									<pg:item>
										<tr>
											<td>
											<c:if test="${log.person_code==null}">
											    <bean:write name="log" property="loginid" />
											</c:if>
											<c:if test="${log.person_code!=null}">
												<bean:write name="log" property="person_code" />
									      	</c:if>		
											</td>
											<td>
											<c:if test="${log.loginid=='anonymous'}">
											    匿名用户
											</c:if>
											<c:if test="${log.loginid!='anonymous'}">
											   <bean:write name="log" property="person_name" />
											</c:if>
											</td>
											<td>
												<bean:write name="log" property="logdate" />
											</td>
											
											<td>
											<c:if test="${log.resource_name==null}">
											   <bean:write name="log" property="msg" />
											</c:if>
											<c:if test="${log.resource_name!=null}">
												<bean:write name="log" property="resource_name" />
												</c:if>
											</td>
											
									</pg:item>
								</logic:iterate>
					</table>
					<jsp:include page="./page.jsp" flush="true" />
					</pg:pager>
					<!-- page offset end -->
					</logic:present>
					<br>
				</html:form>
	</gui:window>
</center>

