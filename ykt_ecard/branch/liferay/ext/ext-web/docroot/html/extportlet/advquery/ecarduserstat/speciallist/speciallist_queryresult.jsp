<%@ include file="/html/extportlet/advquery/init.jsp"%>
<%
	String querytype23 = "bydate";
	String queryType = ParamUtil.getString(request, "querytype",
			querytype23);
%>

<html:form action="/ext/speciallist_queryresult" method="POST"
	onsubmit="submitPortletForm(this); return false;">
	<table width="100%" border="0" align="center" cellpadding="0"
		cellspacing="0">
		<tr>
			<td>
				<table width="98%" border="0" align="center" cellpadding="0"
					cellspacing="0">
					<tr>
						<td height="40">
							<table width="96%" border="0" align="center" cellpadding="0"
								cellspacing="0">
								<tr>
									<td width="7%" nowrap="nowrap" align="right">
										<bean:message key="spec.bDate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="speciallist_begindate" styleId="speciallist_begindate"></html:text>
										<a href="javascript:void(0);"><img
												src="/html/extthemes/classic/images/advquery/search.jpg"
												width="33" height="22" border="0"
													onclick="WdatePicker({el:'speciallist_begindate'})"/></a>
									</td>
									<td width="20%" nowrap="nowrap" align="left">

									</td>
									<td width="8%" nowrap="nowrap" align="right">
										<bean:message key="spec.eDate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="speciallist_enddate" styleId="speciallist_enddate"></html:text>
										<a href="javascript:void(0);"><img
												src="/html/extthemes/classic/images/advquery/search.jpg"
												width="33" height="22" border="0"
												onclick="WdatePicker({el:'speciallist_enddate'})" /></a>
									</td>
									<td width="20%" nowrap="nowrap" align="left">
									</td>
								</tr>

								<tr>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.deptNo" />
									</td>
									<td nowrap="nowrap">
										<html:select property="deptNo" style="width:150px">
											<html:option value="">---------------------</html:option>
											<html:options collection="deptList" labelProperty="deptname"
												property="deptcode" />
										</html:select>
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.specNo" />
									</td>
									<td nowrap="nowrap">
										<html:select property="specNo" style="width:150px">
											<html:option value="">---------------------</html:option>
											<html:options collection="specList"
												labelProperty="specialtyname" property="specialtycode" />
										</html:select>
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.class" />
									</td>
									<td nowrap="nowrap">
										<html:text property="classNo"></html:text>
									<td nowrap="nowrap">
										&nbsp;
									</td>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.custType" />
									</td>
									<td nowrap="nowrap">
										<html:select property="custType" style="width:150px">
										<html:option value="">---------------------</html:option>
											<html:options collection="custtypeList"
												labelProperty="custtypename" property="custtype" />
										</html:select>
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.feeType" />
									</td>
									<td nowrap="nowrap">
										<html:select property="feeType" style="width:150px">
											<html:option value="0">---------------------</html:option>
											<html:options collection="feetypeList"
												labelProperty="feename" property="feetype" />
										</html:select>
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.meal" />
									</td>
									<td nowrap="nowrap">
										<html:select property="meal" style="width:150px">
											<html:option value="">
												<bean:message key="spec.all" />
											</html:option>
											<html:option value="bk">
												<bean:message key="spec.bk" />
											</html:option>
											<html:option value="lun">
												<bean:message key="spec.lun" />
											</html:option>
											<html:option value="sup">
												<bean:message key="spec.sup" />
											</html:option>
										</html:select>
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.bStuempNo" />
									</td>
									<td nowrap="nowrap">
										<html:text property="bStuempNo"></html:text>
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.eStuempNo" />
									</td>
									<td nowrap="nowrap">
										<html:text property="eStuempNo"></html:text>
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.per" />
									</td>
									<td nowrap="nowrap">
										<html:text property="per"
											onkeypress="return checkNumber(event);"></html:text>
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>

									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.avgRange" />
									</td>
									<td nowrap="nowrap">
										<html:text property="bavgRange"></html:text>
										-->
										<html:text property="eavgRange"></html:text>
									</td>
								</tr>

								<tr>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.perRange" />
									</td>
									<td nowrap="nowrap">
										<html:select property="selPer">
											<html:option value="">
												<bean:message key="spec.nullAvg" />
											</html:option>
											<html:option value="up">
												<bean:message key="spec.upAvg" />
											</html:option>
											<html:option value="down">
												<bean:message key="spec.downAvg" />
											</html:option>
										</html:select>
										<html:text property="perRange"
											onkeypress="return checkNumber(event);"></html:text>
										%
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
								</tr>

							</table>
						</td>
					</tr>
				</table>
				<table width="98%" border="0" align="center" cellpadding="0"
					cellspacing="0" bgcolor="#f8f8f8">
					<tr>
						<td height="30">
							<table width="96%" border="0" align="center" cellpadding="0"
								cellspacing="0">
								<tr>
									<td width="66%" class="red_text">
										<bean:message key="system.note" />
									</td>
									<td width="34%" align="center">
										<button onclick="document.speciallistform.submit();">
											<bean:message key="btn.query" />
										</button>
										<button onclick="document.speciallistform.reset();">
											<bean:message key="btn.clear" />
										</button>
									</td>
								</tr>
							</table>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
	<c:if test='<%=request.getAttribute("resultList") != null%>'>

		<%
			List resultList = (List) request.getAttribute("resultList");
		%>
		<%
			String dateRange = request.getAttribute("daterange")
							.toString();
		%>
		<%
			String specStatTip = request.getAttribute("specStatTip")
							.toString();
		%>
		<%
			String yLabel = request.getAttribute("ylabel").toString();
		%>
		<%
			String mealStr = request.getAttribute("mealStr").toString();
		%>
		<%
			List resultAvg = (List) request.getAttribute("resultAvg");
		%>

		<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td>
					<display:table name="resultAvg" pagesize="10" class="isis"
						style="width:100%" requestURI="/ext/speciallist_queryresult" export="false">
						<display:column property="acctime"
							title="<%=LanguageUtil
											.get(pageContext, "spec.time")%>"></display:column>
						<display:column property="femaleavg"
							title="<%=LanguageUtil.get(pageContext,
											"spec.femaleavg")%>"
							format="{0,number,#,##0.00}"></display:column>
						<display:column property="maleavg"
							title="<%=LanguageUtil.get(pageContext,
											"spec.maleavg")%>"
							format="{0,number,#,##0.00}"></display:column>
						<display:column property="totavg"
							title="<%=LanguageUtil.get(pageContext,
													"spec.avg")%>"
							format="{0,number,#,##0.00}"></display:column>
					</display:table>
				</td>
			</tr>
		</table>
		<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td>
					<display:table name="resultList" pagesize="10" class="isis"
						style="width:100%" requestURI="/ext/speciallist_queryresult">
						<display:column property="stuemp_no"
							title="<%=LanguageUtil.get(pageContext,
											"spec.stuempNo")%>"></display:column>
						<display:column property="cut_name"
							title="<%=LanguageUtil
											.get(pageContext, "spec.name")%>"></display:column>
						<display:column property="dept_name"
							title="<%=LanguageUtil
											.get(pageContext, "spec.dept")%>"></display:column>
						<display:column property="s_name"
							title="<%=LanguageUtil.get(pageContext,
											"spec.scode")%>"></display:column>
						<display:column property="class_no"
							title="<%=LanguageUtil.get(pageContext,
											"spec.class")%>"></display:column>
						<display:column property="type_name"
							title="<%=LanguageUtil.get(pageContext,
											"spec.custType")%>"></display:column>
						<display:column property="meal"
							title="<%=LanguageUtil
											.get(pageContext, "spec.meal")%>"></display:column>
						<display:column property="amcount"
							title="<%=LanguageUtil.get(pageContext,
											"spec.amcount")%>"></display:column>
						<display:column property="amsum"
							title="<%=LanguageUtil.get(pageContext,
											"spec.amsum")%>"
							format="{0,number,#,##0.00}"></display:column>
						<display:column property="avg"
							title="<%=LanguageUtil.get(pageContext,
													"spec.avg")%>"
							format="{0,number,#,##0.00}"></display:column>
					</display:table>
				</td>
			</tr>
		</table>

		<table>
			<%
				String basePath = request.getScheme() + "://"
								+ request.getServerName() + ":"
								+ request.getServerPort() + "/delegate/cewolf";
			%>
			<cewolf:chart id="verticalBar"
				title='<%=mealStr
								+ "-"
								+ LanguageUtil.get(pageContext,
										"spec.consTitle")%>'
				type="verticalBar" yaxislabel="<%=yLabel%>">
				<cewolf:colorpaint
					color='<%=LanguageUtil
										.get(pageContext, "chart.bgcolor")%>' />
				<cewolf:data>
					<cewolf:producer id="consAvgData" />
				</cewolf:data>
				<cewolf:chartpostprocessor id="dataColor">
					<cewolf:param name="0"
						value='<%=LanguageUtil.get(pageContext,
											"chart.customer1")%>' />
					<cewolf:param name="1"
						value='<%=LanguageUtil.get(pageContext,
											"chart.customer2")%>' />
					<cewolf:param name="2"
						value='<%=LanguageUtil.get(pageContext,
											"chart.customer3")%>' />
					<cewolf:param name="3"
						value='<%=LanguageUtil.get(pageContext,
											"chart.customer4")%>' />
					<cewolf:param name="4"
						value='<%=LanguageUtil.get(pageContext,
											"chart.customer5")%>' />
					<cewolf:param name="5"
						value='<%=LanguageUtil.get(pageContext,
											"chart.customer6")%>' />
				</cewolf:chartpostprocessor>

			</cewolf:chart>

			<cewolf:img chartid="verticalBar" renderer="<%=basePath%>"
				width='<%=Integer.parseInt(LanguageUtil.get(pageContext,
									"chart.barwidth"))%>'
				height='<%=Integer.parseInt(LanguageUtil.get(pageContext,
									"chart.barheight"))%>' />
		</table>
	</c:if>
</html:form>
<script type="text/javascript">  
function checkNumber(e) {     
	var key = window.event ? e.keyCode : e.which;     
	var keychar = String.fromCharCode(key);     
	var el = document.getElementById('per');     
	//var msg = document.getElementById('msg');     
	reg = /\d/;     
	var result = reg.test(keychar);     
 	if(!result){         
 		return false;
	}else{
		return true;
	}
}
</script>
