<%@ include file="/html/extportlet/advquery/init.jsp"%>
<%@ taglib uri="http://struts.apache.org/tags-bean" prefix="bean"%>
<%@ taglib uri="http://struts.apache.org/tags-bean-el" prefix="bean-el"%>
<%@ taglib uri="http://struts.apache.org/tags-html" prefix="html"%>
<%@ taglib uri="http://struts.apache.org/tags-html-el" prefix="html-el"%>
<%@ taglib uri="http://struts.apache.org/tags-logic" prefix="logic"%>
<%@ taglib uri="http://struts.apache.org/tags-logic-el" 	prefix="logic-el"%>
<%@ taglib uri="http://struts.apache.org/tags-nested" prefix="nested"%>
<%@ taglib uri="http://struts.apache.org/tags-tiles" prefix="tiles"%>
<%@ taglib uri="http://struts.apache.org/tags-tiles-el" 	prefix="tiles-el"%>
<%@ include file="permission.jsp" %>
<%
	String querytype23 = "bydate";
	String queryType = ParamUtil.getString(request, "querytype",
			querytype23);
%>

<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.ERROR_EXIST)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.ERROR_EXIST, SessionErrors.get(
										request, EcardConstants.ERROR_EXIST))%>
	</font>
</c:if>

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
									<td width="7%" nowrap="nowrap">
										<bean:message key="spec.bDate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="speciallist_begindate"></html:text>
									</td>
									<td width="20%" nowrap="nowrap">
										<a href="#"><img
												src="/html/extthemes/classic/images/advquery/search.jpg"
												width="33" height="22" border="0"
												id="f_trigger_speciallist_begindate" /> </a>
									</td>
									<td width="8%" nowrap="nowrap">
										<bean:message key="spec.eDate" />
									</td>
									<td width="20%" nowrap="nowrap">
										<html:text property="speciallist_enddate"></html:text>
									</td>
									<td width="20%" nowrap="nowrap">
										<a href="#"><img
												src="/html/extthemes/classic/images/advquery/search.jpg"
												width="33" height="22" border="0"
												id="f_trigger_speciallist_enddate" /> </a>
									</td>
									<script language="JavaScript">
                        
				                        Calendar.setup({
				                            inputField     :    "speciallist_begindate",     // id of the input field
				                            weekNumbers     :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "f_trigger_speciallist_begindate",  // trigger for the calendar (button ID)
				                            ifFormat       :    "<%=LanguageUtil.get(pageContext, "format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                        
				                        Calendar.setup({
				                            inputField     :    "speciallist_enddate",     // id of the input field
				                            weekNumbers        :   <%=LanguageUtil.get(pageContext, "format.byweek")%>,
				                            button         :    "f_trigger_speciallist_enddate",  // trigger for the calendar (button ID)
				                            ifFormat      :    "<%=LanguageUtil.get(pageContext, "format.date")%>",
				                            align          :    "Bl",           // alignment (defaults to "Bl")
				                            singleClick    :    true
				                        });
				                    </script>
								</tr>

								<tr>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.deptNo" />
									</td>
									<td nowrap="nowrap">
										<html:select property="deptNo">
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
										<html:select property="specNo">
											<html:options collection="specList" labelProperty="s_name"
												property="s_code" />
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
										<html:select property="custType">
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
										<html:select property="feeType">
											<html:option value="0">--------</html:option>
											<html:options collection="feetypeList"
												labelProperty="fee_name" property="fee_type" />
										</html:select>
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.meal" />
									</td>
									<td nowrap="nowrap">
										<html:select property="meal">
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
										<
										<html:text property="bStuempNo"></html:text>
									</td>
									<td nowrap="nowrap">
										&nbsp;
									</td>
									<td height="25" align="right" nowrap="nowrap">
										<bean:message key="spec.eStuempNo" />
									</td>
									<td nowrap="nowrap">
										<
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
										<
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
