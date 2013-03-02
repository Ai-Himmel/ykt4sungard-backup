<%
/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

<%@ include file="/html/taglib/ui/my_places/init.jsp" %>

<%
List myPlaces = user.getMyPlaces();
%>

<c:if test="<%= myPlaces.size() > 0 %>">
	<ul>

		<%
		PortletURL portletURL = new PortletURLImpl(request, PortletKeys.MY_PLACES, plid.longValue(), true);

		portletURL.setWindowState(WindowState.NORMAL);
		portletURL.setPortletMode(PortletMode.VIEW);

		portletURL.setParameter("struts_action", "/my_places/view");

		for (int i = 0; i < myPlaces.size(); i++) {
			Group myPlace = (Group)myPlaces.get(i);

			myPlace = myPlace.toEscapedModel();

			boolean organizationCommunity = myPlace.isOrganization();
			boolean regularCommunity = myPlace.isCommunity();
			boolean userCommunity = myPlace.isUser();
			int publicLayoutsPageCount = myPlace.getPublicLayoutsPageCount();
			int privateLayoutsPageCount = myPlace.getPrivateLayoutsPageCount();

			Organization organization = null;

			String publicAddPageHREF = null;
			String privateAddPageHREF = null;

			if (organizationCommunity) {
				organization = OrganizationLocalServiceUtil.getOrganization(myPlace.getClassPK());

				if (OrganizationPermissionUtil.contains(permissionChecker, organization.getOrganizationId(), ActionKeys.MANAGE_LAYOUTS)) {
					PortletURL addPageURL = new PortletURLImpl(request, PortletKeys.MY_PLACES, plid.longValue(), true);

					addPageURL.setWindowState(WindowState.NORMAL);
					addPageURL.setPortletMode(PortletMode.VIEW);

					addPageURL.setParameter("struts_action", "/my_places/edit_pages");
					addPageURL.setParameter("redirect", currentURL);
					addPageURL.setParameter("groupId", String.valueOf(myPlace.getGroupId()));
					addPageURL.setParameter("privateLayout", Boolean.FALSE.toString());

					publicAddPageHREF = addPageURL.toString();

					addPageURL.setParameter("privateLayout", Boolean.TRUE.toString());

					privateAddPageHREF = addPageURL.toString();
				}
			}
			else if (regularCommunity) {
				if (GroupPermissionUtil.contains(permissionChecker, myPlace.getGroupId(), ActionKeys.MANAGE_LAYOUTS)) {
					PortletURL addPageURL = new PortletURLImpl(request, PortletKeys.MY_PLACES, plid.longValue(), true);

					addPageURL.setWindowState(WindowState.NORMAL);
					addPageURL.setPortletMode(PortletMode.VIEW);

					addPageURL.setParameter("struts_action", "/my_places/edit_pages");
					addPageURL.setParameter("redirect", currentURL);
					addPageURL.setParameter("groupId", String.valueOf(myPlace.getGroupId()));
					addPageURL.setParameter("privateLayout", Boolean.FALSE.toString());

					publicAddPageHREF = addPageURL.toString();

					addPageURL.setParameter("privateLayout", Boolean.TRUE.toString());

					privateAddPageHREF = addPageURL.toString();
				}
			}
			else if (userCommunity) {
				PortletURL publicAddPageURL = new PortletURLImpl(request, PortletKeys.MY_ACCOUNT, plid.longValue(), false);

				publicAddPageURL.setWindowState(WindowState.MAXIMIZED);
				publicAddPageURL.setPortletMode(PortletMode.VIEW);

				publicAddPageURL.setParameter("struts_action", "/my_account/edit_pages");
				publicAddPageURL.setParameter("tabs2", "public");
				publicAddPageURL.setParameter("redirect", currentURL);
				publicAddPageURL.setParameter("groupId", String.valueOf(myPlace.getGroupId()));

				publicAddPageHREF = publicAddPageURL.toString();

				long privateAddPagePlid = myPlace.getDefaultPrivatePlid();

				PortletURL privateAddPageURL = new PortletURLImpl(request, PortletKeys.MY_ACCOUNT, plid.longValue(), false);

				privateAddPageURL.setWindowState(WindowState.MAXIMIZED);
				privateAddPageURL.setPortletMode(PortletMode.VIEW);

				privateAddPageURL.setParameter("struts_action", "/my_account/edit_pages");
				privateAddPageURL.setParameter("tabs2", "private");
				privateAddPageURL.setParameter("redirect", currentURL);
				privateAddPageURL.setParameter("groupId", String.valueOf(myPlace.getGroupId()));

				privateAddPageHREF = privateAddPageURL.toString();
			}

			boolean showPublicPlace = true;

			if (publicLayoutsPageCount == 0) {
				if (organizationCommunity) {
					showPublicPlace = PropsValues.MY_PLACES_SHOW_ORGANIZATION_PUBLIC_SITES_WITH_NO_LAYOUTS;
				}
				else if (regularCommunity) {
					showPublicPlace = PropsValues.MY_PLACES_SHOW_COMMUNITY_PUBLIC_SITES_WITH_NO_LAYOUTS;
				}
				else if (userCommunity) {
					showPublicPlace = PropsValues.MY_PLACES_SHOW_USER_PUBLIC_SITES_WITH_NO_LAYOUTS;
				}
			}

			boolean showPrivatePlace = true;

			if (privateLayoutsPageCount == 0) {
				if (organizationCommunity) {
					showPrivatePlace = PropsValues.MY_PLACES_SHOW_ORGANIZATION_PRIVATE_SITES_WITH_NO_LAYOUTS;
				}
				else if (regularCommunity) {
					showPrivatePlace = PropsValues.MY_PLACES_SHOW_COMMUNITY_PRIVATE_SITES_WITH_NO_LAYOUTS;
				}
				else if (userCommunity) {
					showPrivatePlace = PropsValues.MY_PLACES_SHOW_USER_PRIVATE_SITES_WITH_NO_LAYOUTS;
				}
			}
		%>

			<c:if test="<%= showPublicPlace || showPrivatePlace %>">
				<li>
					<h3>
						<c:choose>
							<c:when test="<%= organizationCommunity %>">
								<%= organization.getName() %>
							</c:when>
							<c:when test="<%= userCommunity %>">
								<liferay-ui:message key="my-community" />
							</c:when>
							<c:otherwise>
								<%= myPlace.getName() %>
							</c:otherwise>
						</c:choose>
					</h3>

					<ul>

						<%
						portletURL.setParameter("groupId", String.valueOf(myPlace.getGroupId()));
						portletURL.setParameter("privateLayout", Boolean.FALSE.toString());

						boolean selectedPlace = false;

						if (layout != null) {
							selectedPlace = !layout.isPrivateLayout() && (layout.getGroupId() == myPlace.getGroupId());
						}
						%>

						<c:if test="<%= showPublicPlace %>">
							<li class="public <%= selectedPlace ? "current" : "" %>">
								<a href="<%= publicLayoutsPageCount > 0 ? "javascript: submitForm(document.hrefFm, '" + portletURL.toString() + "');" : "javascript: ;" %>"

								<c:if test="<%= userCommunity %>">
									id="my-community-public-pages"
								</c:if>

								><liferay-ui:message key="public-pages" /> <span class="page-count">(<%= publicLayoutsPageCount %>)</span></a>

								<c:if test="<%= publicAddPageHREF != null %>">
									<a class="add-page" href="javascript: submitForm(document.hrefFm, '<%= publicAddPageHREF %>');"><liferay-ui:message key="manage-pages" /></a>
								</c:if>
							</li>
						</c:if>

						<%
						portletURL.setParameter("groupId", String.valueOf(myPlace.getGroupId()));
						portletURL.setParameter("privateLayout", Boolean.TRUE.toString());

						selectedPlace = false;

						if (layout != null) {
							selectedPlace = layout.isPrivateLayout() && (layout.getGroupId() == myPlace.getGroupId());
						}
						%>

						<c:if test="<%= showPrivatePlace %>">
							<li class="private <%= selectedPlace ? "current" : "" %>">
								<a href="<%= privateLayoutsPageCount > 0 ? "javascript: submitForm(document.hrefFm, '" + portletURL.toString() + "');" : "javascript: ;" %>"

								<c:if test="<%= userCommunity %>">
									id="my-community-private-pages"
								</c:if>

								><liferay-ui:message key="private-pages" /> <span class="page-count">(<%= privateLayoutsPageCount %>)</span></a>

								<c:if test="<%= privateAddPageHREF != null %>">
									<a class="add-page" href="javascript: submitForm(document.hrefFm, '<%= privateAddPageHREF %>');"><liferay-ui:message key="manage-pages" /></a>
								</c:if>
							</li>
						</c:if>
					</ul>
				</li>
			</c:if>

		<%
		}
		%>

	</ul>
</c:if>