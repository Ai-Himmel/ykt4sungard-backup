<%@ include file="/html/extportlet/shopquery/init.jsp"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccException"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccResultToomuchException"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccBgInfoException"%>
<%@ taglib uri="http://displaytag.sf.net" prefix="display" %>
<%@page import="com.liferay.util.servlet.SessionErrors"%>
<link href="/html/extcommon/styles/displaytag/alternative.css" rel="stylesheet" type="text/css" />


<%
	String shopad_begindate = request.getAttribute("shopad_begindate") == null ? ""
			: request.getAttribute("shopad_begindate").toString();
	String shopad_enddate = request.getAttribute("shopad_enddate") == null ? ""
			: request.getAttribute("shopad_enddate").toString();
    String devphyId = request.getAttribute("devphyId") == null ? ""
            : request.getAttribute("devphyId").toString();
%>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.TIME_PERIOD_TOO_LONG) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="shop_time_period_too_long"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.SHOPID_NOT_SELECTED) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="shopid_not_select"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.DATE_NOT_SELECTED) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="date_not_selected"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,BccBgInfoException.class.getName()) %>">
<font class="portlet-msg-info">
    <%=LanguageUtil.format(pageContext, EcardConstants.ERROR_EXIST,((BccBgInfoException)SessionErrors.get(request,BccBgInfoException.class.getName())).getMessage()) %>
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,BccException.class.getName()) %>">
<font class="portlet-msg-info">
    <%= LanguageUtil.format(pageContext, EcardConstants.ERROR_EXIST,((BccException)SessionErrors.get(request,BccException.class.getName())).getMessage()) %>
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,Exception.class.getName()) %>">
<font class="portlet-msg-error">
    <%= LanguageUtil.format(pageContext, EcardConstants.ERROR_EXIST,((Exception)SessionErrors.get(request,Exception.class.getName())).getMessage()) %>
 </font>
</c:if>
<html:form action="/ext/shopposreport_result" method="POST"
	onsubmit="submitPortletForm(this); return false;">
	<table cellpadding="8" border=0 cellspacing="0" width="600">
		<tr>
			<td>
				<table border="0" align="left" cellpadding="0" cellspacing="0"
					width="100%">
					<tr>
						<td height="40">
							<table border="0" align="left" cellpadding="0" cellspacing="0"
								width="100%">
								<tr>
									<td>
										<bean:message key="shop.account.detail.query.shopname" />
									</td>

									<td>
										&nbsp;
									</td>
									<td>
										&nbsp;
									</td>

								</tr>
								<tr>
									<td nowrap="nowrap">
										<select name="shopid" style="">
											<%
												if (request.getSession().getAttribute(WebKeys.USER_ID) != null
														&& !"".equals(request.getSession().getAttribute(
																WebKeys.USER_ID))) {
													Long realUserId = (Long) request.getSession().getAttribute(
															WebKeys.USER_ID);
													List shoplist = ShopServiceUtil.getShopList(realUserId);
													long shopId = -1;
													if (null != request.getAttribute("shopid")
															&& !"".equals(request.getAttribute("shopid"))) {
														shopId = Long.parseLong(request.getAttribute("shopid")
																.toString());
													}
													Iterator iter = shoplist.iterator();
													while (iter.hasNext()) {
														TShop tshop = (TShop) iter.next();
														if (shopId == tshop.getShopid()) {
											%>
											<option value="<%=tshop.getShopid()%>" selected="selected"><%=tshop.getShopname()%></option>

											<%
												} else {
											%>
											<option value="<%=tshop.getShopid()%>"><%=tshop.getShopname()%></option>
											<%
												}
													}
												}
											%>
										</select>
									</td>
									<td nowrap="nowrap">

									</td>
								</tr>
								<tr>
									<td>
										<bean:message key="shop.query.begindate" />
										
									</td>

									<td>
										<bean:message key="shop.query.enddate" />
									</td>
									<td>
										<bean:message key="shop.query.devphyId" />
									</td>
								</tr>

								<tr>
									<td>
										<input type="text" name="shopad_begindate"
											id="shopad_begindate" value="<%=shopad_begindate%>" />
										<a href="#"><img
												src="/html/extthemes/classic/images/calendar/calendar.gif"
												border="0" id="f_trigger_shopad_begindate" /> </a>
									</td>
									<td>
										<input type="text" name="shopad_enddate" id="shopad_enddate"
											value="<%=shopad_enddate%>" />
										<a href="#"><img
												src="/html/extthemes/classic/images/calendar/calendar.gif"
												border="0" id="f_trigger_shopad_enddate" /> </a>
									</td>
									<td>
										<input type="text" name="devphyId"  value="<%=devphyId%>" />
									</td>
								</tr>

							</table>
						</td>
					</tr>
				</table>
			</td>
		</tr>
		<tr>
			<td>
				&nbsp;
			</td>
		</tr>
		<tr>
			<td>
				<table border="0" align="center" cellpadding="0" cellspacing="0"
					width="100%">
					<tr>
						<td>
							<table border="0" align="center" cellpadding="0" cellspacing="0"
								width="100%">
								<tr>
									<td width="100%" align="right" colspan="2">
										<input type="button"
											onclick="javascript:shopadvalidateAllData();"
											value="<bean:message key="shop.query.query" />">
										<input type="button"
											onclick="document.ShopPosReportForm.reset();"
											value="<bean:message key="shop.query.reset" />">
									</td>
								</tr>
							</table>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>

	<!--startprintshopaccountdetail_query.jsp-->
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>	
				<display:table name="result" pagesize="10" class="isis" id="row"
				style="width:100%" requestURI="/ext/shopposreport_result" 
				export="true">
					<display:column title="<%=LanguageUtil.get(pageContext,"pos.serialno")%>"><%=pageContext.getAttribute("row_rowNum")%></display:column>
					<display:column property="custName" title="<%=LanguageUtil.get(pageContext,"pos.custName")%>"></display:column>
					<display:column property="stuempno" title="<%=LanguageUtil.get(pageContext,"pos.custNo")%>"></display:column>
					<display:column property="classname" title="<%=LanguageUtil.get(pageContext,"pos.classname")%>"></display:column>
					<display:column property="amount" title="<%=LanguageUtil.get(pageContext,"shop.account.detail.query.amount")%>" format="{0,number,0.00}" ></display:column>
					<display:column property="transdate" title="<%=LanguageUtil.get(pageContext,"shop.account.detail.query.transdate")%>"></display:column>
					<display:column property="transtime" title="<%=LanguageUtil.get(pageContext,"shop.account.detail.query.transtime")%>"></display:column>
					<display:column property="termid" title="<%=LanguageUtil.get(pageContext,"pos.deviceId")%>"></display:column>	
					<display:column property="devphyId" title="<%=LanguageUtil.get(pageContext,"shop.query.devphyId")%>"></display:column>
					<display:column property="cardbefbal" title="<%=LanguageUtil.get(pageContext,"pos.cardbefbal")%>" format="{0,number,0.00}"></display:column>
					<display:column property="cardaftbal" title="<%=LanguageUtil.get(pageContext,"pos.cardaftbal")%>" format="{0,number,0.00}"></display:column>
				</display:table>			
			</td>
		</tr>
	</table>
	<!--endprintshopaccountdetail_query.jsp-->
</html:form>
<script language="JavaScript">                                        
    Calendar.setup({
        inputField     :    "shopad_begindate",     // id of the input field
        button         :    "f_trigger_shopad_begindate",  // trigger for the calendar (button ID)
        align          :    "Bl",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    
    Calendar.setup({
        inputField     :    "shopad_enddate",     // id of the input field
        button         :    "f_trigger_shopad_enddate",  // trigger for the calendar (button ID)
        align          :    "Bl",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
</script>
<script>
function shopadvalidateAllData() {
    if(document.ShopPosReportForm.shopad_begindate.value==""){
        alert("<%=LanguageUtil.get(pageContext,
							"shop.query.alert.nobegindate")%>");
        return false;
    }
    if(document.ShopPosReportForm.shopad_enddate.value==""){
        alert("<%=LanguageUtil.get(pageContext,
							"shop.query.alert.noenddate")%>");
        return false;
    }
    if(document.ShopPosReportForm.shopid.value==""){
        alert("<%=LanguageUtil.get(pageContext,"shop.query.alert.shopnotselected")%>");
        return false;
    }
    document.ShopPosReportForm.submit();
}

</script>

<script language="javascript">
function shopaddoprintpreview()
{
bdhtml=window.document.body.innerHTML;
sprnstr="<!--startprintshopaccountdetail_query.jsp-->";
eprnstr="<!--endprintshopaccountdetail_query.jsp-->";
prnhtml=bdhtml.substr(bdhtml.indexOf(sprnstr)+44);
prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
window.document.body.innerHTML=prnhtml;
window.print();
}
</script>