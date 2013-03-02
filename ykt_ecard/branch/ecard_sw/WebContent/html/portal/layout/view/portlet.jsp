<%
/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
%>

<%@ include file="/html/portal/init.jsp" %>
<%@ page import="java.text.SimpleDateFormat" %>
<%@ page import="org.apache.struts.validator.DynaValidatorForm" %>
<%@ page import="com.kingstargroup.ecard.hibernate.information.EcardInformation" %>
<%@ page import="com.kingstargroup.ecard.hibernate.hitinfo.EcardHitInfo" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.ResultPage" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.InformationUtil" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.HitInfoUtil" %>
<%@ page import="com.kingstargroup.ecard.util.EcardConstants" %>
<%@ page import="com.kingstargroup.ecard.util.PermissionUtil" %>
<%@ page import="com.kingstargroup.ecard.util.DateFormatUtil" %>
<%@ page import="com.kingstargroup.ecard.util.TypeMappingUtil" %>
<%
boolean layoutMaximized = layoutTypePortlet.hasStateMax();

int portletWidth = themeDisplay.getResWide();
String[] columnOrder = StringUtil.split(layoutTypePortlet.getColumnOrder());

Portlet[] portlets = null;
Portlet[] narrow1Portlets = layoutTypePortlet.getNarrow1Portlets();
Portlet[] narrow2Portlets = layoutTypePortlet.getNarrow2Portlets();
Portlet[] wide1Portlets = layoutTypePortlet.getWide1Portlets();

%>

<%@ include file="/html/portal/layout/view/portlet_static.jsp" %>

<%@ include file="/html/portal/layout/view/portlet_js.jsp" %>

<!--
<div id="layout-content-outer-decoration">
	<div id="layout-content-inner-decoration">
		<div id="layout-content-container">
-->
		<!-- +++++++++++++++ -->
		<table width="1000" border="0" cellpadding="0" cellspacing="0">
		  <tr>
		    <td width="1000" height="375" valign="top" bgcolor="#f5f9ff">
		    <table width="1000" border="0" cellspacing="0" cellpadding="0">
		      <tr>
		        <td height="8"></td>
		      </tr>
		    </table>
		    <%
		    
			/*
			 * add hit info module
			 */
			 if (layoutId.equals("1") || layoutId.equals("1.1")) {
				if (!layoutMaximized) {
					String companyId = (String) getServletContext().getAttribute(WebKeys.COMPANY_ID);
					Portlet hitPortlet = PortletServiceUtil.getPortletById(companyId, "ecardhit");
					PortalUtil.renderPortlet(application, request, response, pageContext, hitPortlet, new Integer(0), "w1", new Integer(0), new Integer(0));
			%>
			<%}
				}%>
		    
		 <!-- --------------- -->
			
			<%
			if (!layoutMaximized) {%>
			<!-- ++++++++++++++ -->
			<table  width="96%" height="400"  border="0" align="center" cellpadding="0" cellspacing="0">
	        <tr>
	        <!-- --------------- -->  
			<%
				for (int i = 0; i < columnOrder.length; i++) {
					String curColumnOrder = columnOrder[i];

					if (curColumnOrder.equals("n1")) {
						portlets = narrow1Portlets;
						portletWidth = themeDisplay.getResNarrow();
						%>
						<!-- ++++++++++++ -->
						<td width="35%" align=center valign="top">
						<!-- ------------ -->
						<%
					}
					else if (curColumnOrder.equals("n2")) {
						portlets = narrow2Portlets;
						portletWidth = themeDisplay.getResNarrow();
					}
					else if (curColumnOrder.equals("w1")) {%>
					
					<%
						portlets = wide1Portlets;
						portletWidth = themeDisplay.getResWide();
						%>
						<!-- ++++++++++++ -->
						<td width="65%" align=center valign="top">
						<!-- ------------ -->
						<%
					}
			%>
				<!--
					<div id="layout-column_<%= curColumnOrder %>">
				-->

						<%
						if (portlets != null) {
							for (int j = 0; j < portlets.length; j++) {
								Portlet portlet = portlets[j];

								PortalUtil.renderPortlet(application, request, response, pageContext, portlet, new Integer(portletWidth), curColumnOrder, new Integer(j), new Integer(portlets.length));

								if (j == (portlets.length - 1)) {
						%>

									<!--<div class="layout-blank_<%= curColumnOrder %>_portlet"></div>-->

						<%
								}
								%>
								<!-- ++++++++++++++ -->
								<table width="100%" height="10"  border="0" cellpadding="0" cellspacing="0">
					              <tr>
					                <td></td>
					              </tr>
					            </table>
								<!-- -------------- -->
								<%
							}
						}
						%>

						<c:if test="<%= portlets.length == 0 %>">
							<!--
							<div class="layout-blank_<%= curColumnOrder %>_portlet"></div>
							-->
						</c:if>
				<!--
					</div>
				-->
					<c:if test="<%= i < (columnOrder.length - 1) %>">
						<!--
						<div class="layout-margin-div"></div>
						-->
					</c:if>
					<!-- ++++++++++ -->
					
					</td>
					
					<!-- ---------- -->
			<%
				}%>
				<!-- ++++++++++ -->
				</tr>
				</table>
				<!-- ---------- -->
			<%
			}
			else {
			%>

				<!-- 
				<div valign="top">
				-->

					<%
					Portlet portlet = PortletServiceUtil.getPortletById(company.getCompanyId(), StringUtil.split(layoutTypePortlet.getStateMax())[0]);

					PortalUtil.renderPortlet(application, request, response, pageContext, portlet, new Integer(themeDisplay.getResTotal()), "w1", new Integer(0), new Integer(1));
					%>

				<!--
				</div>
				-->

			<%
			}
			%>
			<!--
			<div id="layout-bottom-separator">
			</div>
			-->
			<!-- ++++++++++++ -->
					</td>
				</tr>
			</table>
			<!-- ------------ -->
		<!--
		</div>
	</div>
</div>
		-->
<!--
<div id="layout-bottom-container">
-->
	<c:if test="<%= GetterUtil.getBoolean(PropsUtil.get(PropsUtil.LAYOUT_ADD_PORTLETS)) && themeDisplay.isSignedIn() && !layoutMaximized && (!layout.isGroup() || (layout.isGroup() && RoleLocalServiceUtil.isAdministrator(user.getUserId()))) && (layout.isContentModifiable(user.getUserId())) %>">

		<%
		List allPortlets = PortletServiceUtil.getPortlets(user.getCompanyId());

		Collections.sort(allPortlets, new PortletTitleComparator(application, locale));

		for (int i = 0; i < columnOrder.length; i++) {
			String curColumnOrder = columnOrder[i];
		%>

			<div id="layout-add_<%=curColumnOrder%>">
				<form name="layout_<%= curColumnOrder %>_fm">

				<div><%= LanguageUtil.get(pageContext, curColumnOrder.equals("w1") ? "add-portlet-to-wide-column" : "add-portlet-to-narrow-column") %></div>

				<span>
					<select name="add_<%= curColumnOrder %>_sel" class="layout-add-select-style">
						<option value=""></option>

						<%
						List curColumnPortlets = new ArrayList();

						for (int j = 0; j < allPortlets.size(); j++) {
							Portlet selPortlet = (Portlet)allPortlets.get(j);

							String portletTitle = PortletConfigFactory.create(selPortlet, application).getResourceBundle(locale).getString(WebKeys.JAVAX_PORTLET_TITLE);
							if (selPortlet.isNarrow()) {
								portletTitle = StringUtil.shorten(portletTitle, 15);
							}

							boolean curColumnOrderBoolean = false;
							if (curColumnOrder.equals("w1")) {
								if (!selPortlet.isNarrow()) {
									curColumnOrderBoolean = true;
								}
							}
							else {
								if (selPortlet.isNarrow()) {
									curColumnOrderBoolean = true;
								}
							}

							if (columnOrder.length == 1) {
								curColumnOrderBoolean = true;
							}

							boolean curColumnPortlet = (curColumnOrderBoolean && selPortlet.isActive() && RoleLocalServiceUtil.hasRoles(user.getUserId(), selPortlet.getRolesArray()));

							if (curColumnPortlet) {
								curColumnPortlets.add(new KeyValuePair(selPortlet.getPortletId(), portletTitle));
							}

							if (curColumnPortlet && (selPortlet.isInstanceable() || !layoutTypePortlet.hasPortletId(selPortlet.getPortletId()))) {
						%>

								<option value="<%= selPortlet.getPortletId() %>"><%= portletTitle %></option>

						<%
							}
						}
						%>

					</select>
				</span>

				<script language="JavaScript">
					var portletTitles_<%= curColumnOrder %> = new Object();

					<%
					for (int j = 0; j < curColumnPortlets.size(); j++) {
						KeyValuePair kvp = (KeyValuePair)curColumnPortlets.get(j);
					%>

						portletTitles_<%= curColumnOrder %>["<%= kvp.getKey() %>"] = "<%= kvp.getValue() %>";

					<%
					}
					%>

				</script>

				<span>
					<input class="portlet-form-button" type="button" value="<%= LanguageUtil.get(pageContext, "add") %>" onClick="var selPortletId = document.layout_<%= curColumnOrder %>_fm.add_<%= curColumnOrder %>_sel[document.layout_<%= curColumnOrder %>_fm.add_<%= curColumnOrder %>_sel.selectedIndex].value; if (selPortletId != '') { addPortlet('<%= layoutId %>', selPortletId, '<%= curColumnOrder %>'); };">
				</span>

				</form>
			</div>

			<c:if test="<%= i < (columnOrder.length - 1) %>">
				<div class="layout-margin-div"></div>
			</c:if>

		<%
		}
		%>

	</c:if>
<!--</div>-->