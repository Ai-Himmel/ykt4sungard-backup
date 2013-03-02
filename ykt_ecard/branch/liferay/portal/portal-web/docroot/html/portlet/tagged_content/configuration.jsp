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

<%@ include file="/html/portlet/tagged_content/init.jsp" %>

<%
String tabs2 = ParamUtil.getString(request, "tabs2");

String redirect = ParamUtil.getString(request, "redirect");

String typeSelection = ParamUtil.getString(request, "typeSelection", StringPool.BLANK);

PortletURL configurationRenderURL = renderResponse.createRenderURL();

configurationRenderURL.setParameter("struts_action", "/portlet_configuration/edit_configuration");
configurationRenderURL.setParameter("redirect", redirect);
configurationRenderURL.setParameter("backURL", redirect);
configurationRenderURL.setParameter("portletResource", portletResource);

PortletURL configurationActionURL = renderResponse.createActionURL();

configurationActionURL.setParameter("struts_action", "/portlet_configuration/edit_configuration");
configurationActionURL.setParameter("redirect", redirect);
configurationActionURL.setParameter("backURL", redirect);
configurationActionURL.setParameter("portletResource", portletResource);
%>

<script type="text/javascript">
	function <portlet:namespace />chooseSelectionStyle() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = 'selection-style';

		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />moveSelectionDown(assetOrder) {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = 'move-selection-down';
		document.<portlet:namespace />fm.<portlet:namespace />assetOrder.value = assetOrder;

		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />moveSelectionUp(assetOrder) {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = 'move-selection-up';
		document.<portlet:namespace />fm.<portlet:namespace />assetOrder.value = assetOrder;

		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />selectAsset(assetId, assetParentId, assetTitle, assetOrder) {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = 'add-selection';
		document.<portlet:namespace />fm.<portlet:namespace />assetId.value = assetId;
		document.<portlet:namespace />fm.<portlet:namespace />assetParentId.value = assetParentId;
		document.<portlet:namespace />fm.<portlet:namespace />assetTitle.value = assetTitle;
		document.<portlet:namespace />fm.<portlet:namespace />assetOrder.value = assetOrder;

		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />selectionForType(type) {
		document.<portlet:namespace />fm.<portlet:namespace />typeSelection.value = type;
		document.<portlet:namespace />fm.<portlet:namespace />assetOrder.value = -1;

		submitForm(document.<portlet:namespace />fm, '<%= configurationRenderURL.toString() %>');
	}
</script>

<form action="<%= configurationActionURL.toString() %>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />
<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>" />
<input name="<portlet:namespace />typeSelection" type="hidden" value="" />
<input name="<portlet:namespace />assetId" type="hidden" value="" />
<input name="<portlet:namespace />assetParentId" type="hidden" value="" />
<input name="<portlet:namespace />assetTitle" type="hidden" value="" />
<input name="<portlet:namespace />assetOrder" type="hidden" value="-1" />

<c:choose>
	<c:when test="<%= typeSelection.equals(StringPool.BLANK) %>">
		<liferay-ui:message key="asset-selection" />

		<select name="<portlet:namespace />selectionStyle" onchange="<portlet:namespace />chooseSelectionStyle();">
			<option <%= selectionStyle.equals("dynamic") ? " selected=\"selected\"" : "" %> value="dynamic"><liferay-ui:message key="dynamic" /></option>
			<option <%= selectionStyle.equals("manual") ? " selected=\"selected\"" : "" %> value="manual"><liferay-ui:message key="manual" /></option>
		</select>

		<br /><br />

		<c:choose>
			<c:when test='<%= selectionStyle.equals("manual") %>'>
				<liferay-ui:tabs
					names="selection,display-settings"
					formName="fm"
					param="tabs2"
					refresh="<%= false %>"
				>
					<liferay-ui:section>

						<%
						String portletId = portletResource;
						%>

						<%@ include file="/html/portlet/tagged_content/add_asset.jspf" %>

						<select name="<portlet:namespace/>assetType" onchange="<portlet:namespace />selectionForType(this.options[this.selectedIndex].value);">
							<option value=""><liferay-ui:message key="select-existing"/>...</option>

							<%
							for (int i = 0; i < TagsUtil.ASSET_TYPE_CLASS_NAMES.length; i++) {
								if (!TagsUtil.ASSET_TYPE_CLASS_NAMES[i].equals(MBMessage.class.getName()) && !TagsUtil.ASSET_TYPE_CLASS_NAMES[i].equals(WikiPage.class.getName())) {
								%>

									<option value="<%= TagsUtil.ASSET_TYPE_CLASS_NAMES[i] %>"><liferay-ui:message key='<%= "model.resource." + TagsUtil.ASSET_TYPE_CLASS_NAMES[i] %>' /></option>

								<%
								}
							}
							%>

						</select>

						<br /><br />

						<%
						List headerNames = new ArrayList();

						headerNames.add("type");
						headerNames.add("title");
						headerNames.add(StringPool.BLANK);

						SearchContainer searchContainer = new SearchContainer(renderRequest, new DisplayTerms(renderRequest), new DisplayTerms(renderRequest), SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, configurationRenderURL, headerNames, LanguageUtil.get(pageContext, "no-assets-selected"));

						int total = manualEntries.length;

						searchContainer.setTotal(total);

						List results = ListUtil.fromArray(manualEntries);

						int end = (manualEntries.length < searchContainer.getEnd()) ? manualEntries.length : searchContainer.getEnd();

						results = results.subList(searchContainer.getStart(), end);

						searchContainer.setResults(results);

						List resultRows = searchContainer.getResultRows();

						for (int i = 0; i < results.size(); i++) {
							String assetEntry = (String)results.get(i);

							SAXReader reader = new SAXReader();

							Document doc = reader.read(new StringReader(assetEntry));

							Element root = doc.getRootElement();

							int assetOrder = searchContainer.getStart() + i;

							DocUtil.add(root, "asset-order", assetOrder);

							if (assetOrder == (total - 1)) {
								DocUtil.add(root, "last", true);
							}
							else {
								DocUtil.add(root, "last", false);
							}

							String assetType = root.element("asset-type").getText();
							long assetId = GetterUtil.getLong(root.element("asset-id").getText());

							TagsAsset asset = TagsAssetLocalServiceUtil.getAsset(assetId);

							ResultRow row = new ResultRow(doc, null, assetOrder);

							PortletURL rowURL = renderResponse.createRenderURL();

							rowURL.setParameter("struts_action", "/portlet_configuration/edit_configuration");
							rowURL.setParameter("redirect", redirect);
							rowURL.setParameter("backURL", redirect);
							rowURL.setParameter("portletResource", portletResource);
							rowURL.setParameter("typeSelection", assetType);
							rowURL.setParameter("assetId", String.valueOf(assetId));
							rowURL.setParameter("assetOrder", String.valueOf(assetOrder));

							// Type

							row.addText(LanguageUtil.get(pageContext, "model.resource." + assetType), rowURL);

							// Title

							if (assetType.equals(IGImage.class.getName())) {
								IGImage image = IGImageLocalServiceUtil.getImage(asset.getClassPK());

								StringMaker sm = new StringMaker();

								sm.append("<img border=\"1\" src=\"");
								sm.append(themeDisplay.getPathImage());
								sm.append("/image_gallery?img_id=");
								sm.append(image.getSmallImageId());
								sm.append("&t=");
								sm.append(ImageServletTokenUtil.getToken(image.getSmallImageId()));
								sm.append("\" title=\"");
								sm.append(image.getDescription());
								sm.append("\" />");

								row.addText(sm.toString(), rowURL);
							}
							else {
								row.addText(asset.getTitle(), rowURL);
							}

							// Action

							row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/tagged_content/asset_selection_action.jsp");

							// Add result row

							resultRows.add(row);
						}
						%>

						<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

						<br />

						<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />
					</liferay-ui:section>
					<liferay-ui:section>
						<%@ include file="/html/portlet/tagged_content/display_settings.jspf" %>

						<br />

						<input type="button" value="<liferay-ui:message key="save" />" onClick="submitForm(document.<portlet:namespace />fm);" />

						<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />
					</liferay-ui:section>
				</liferay-ui:tabs>
			</c:when>
			<c:when test='<%= selectionStyle.equals("dynamic") %>'>
				<liferay-ui:tabs
					names="query-logic,display-settings"
					formName="fm"
					param="tabs2"
					refresh="<%= false %>"
				>
					<liferay-ui:section>
						<liferay-ui:message key="asset-type" />

						<select name="<portlet:namespace/>classNameId">
							<option value=""><liferay-ui:message key="all"/></option>

							<%
							TagsAssetType[] assetTypes = TagsAssetServiceUtil.getAssetTypes(themeDisplay.getLocale().toString());

							for (int i = 0; i < assetTypes.length; i++) {
							%>

								<option <%= (classNameId == assetTypes[i].getClassNameId()) ? "selected" : "" %> value="<%= assetTypes[i].getClassNameId() %>"><liferay-ui:message key='<%= "model.resource." + assetTypes[i].getClassName() %>' /></option>

							<%
							}
							%>

						</select>

						<br /><br />

						<liferay-ui:message key="select-by-tags-category" />

						<select name="<portlet:namespace />category">
							<option value=""><liferay-ui:message key="none" /></option>

							<%
							List categories = TagsPropertyLocalServiceUtil.getPropertyValues(company.getCompanyId(), "category");

							for (int i = 0; i < categories.size(); i++) {
								TagsProperty property = (TagsProperty) categories.get(i);
							%>

								<option <%= category.equals(property.getValue()) ? "selected" : "" %> value="<%= property.getValue() %>"><%= property.getValue() %></option>

							<%
							}
							%>

						</select>

						<br /><br />

						<liferay-ui:message key="displayed-content-must-contain-the-following-tags" />

						<br /><br />

						<liferay-ui:tags-selector
							hiddenInput="entries"
							curTags="<%= StringUtil.merge(entries) %>"
							focus="<%= false %>"
						/>

						<br />

						<liferay-ui:message key="displayed-content-must-not-contain-the-following-tags" />

						<br /><br />

						<liferay-ui:tags-selector
							hiddenInput="notEntries"
							curTags="<%= StringUtil.merge(notEntries) %>"
							focus="<%= false %>"
						/>

						<br />

						<liferay-ui:message key="include-tags-specified-in-the-url" />

						<liferay-ui:input-checkbox param="mergeUrlTags" defaultValue="<%= mergeUrlTags %>" />

						<br /><br />

						<liferay-ui:message key="search-operator" />

						<select name="<portlet:namespace />andOperator">
							<option <%= andOperator ? "selected" : "" %> value="1"><liferay-ui:message key="and" /></option>
							<option <%= !andOperator ? "selected" : "" %> value="0"><liferay-ui:message key="or" /></option>
						</select>
					</liferay-ui:section>
					<liferay-ui:section>
						<%@ include file="/html/portlet/tagged_content/display_settings.jspf" %>
					</liferay-ui:section>
				</liferay-ui:tabs>

				<br />

				<input type="button" value="<liferay-ui:message key="save" />" onClick="document.<portlet:namespace />fm.<portlet:namespace />metadataFields.value = Liferay.Util.listSelect(document.<portlet:namespace />fm.<portlet:namespace />currentMetadataFields); submitForm(document.<portlet:namespace />fm);" />

				<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />
			</c:when>
		</c:choose>
	</c:when>
	<c:when test="<%= typeSelection.equals(BlogsEntry.class.getName()) %>">
		<input name="<portlet:namespace />assetType" type="hidden" value="<%= BlogsEntry.class.getName() %>" />

		<liferay-ui:message key="select" />: <liferay-ui:message key='<%= "model.resource." + BlogsEntry.class.getName() %>' />

		<br /><br />

		<%@ include file="/html/portlet/tagged_content/select_blogs_entry.jspf" %>
	</c:when>
	<c:when test="<%= typeSelection.equals(BookmarksEntry.class.getName()) %>">
		<input name="<portlet:namespace />assetType" type="hidden" value="<%= BookmarksEntry.class.getName() %>" />

		<liferay-ui:message key="select" />: <liferay-ui:message key='<%= "model.resource." + BookmarksEntry.class.getName() %>' />

		<br /><br />

		<%@ include file="/html/portlet/tagged_content/select_bookmarks_entry.jspf" %>
	</c:when>
	<c:when test="<%= typeSelection.equals(DLFileEntry.class.getName()) %>">
		<input name="<portlet:namespace />assetType" type="hidden" value="<%= DLFileEntry.class.getName() %>" />

		<liferay-ui:message key="select" />: <liferay-ui:message key='<%= "model.resource." + DLFileEntry.class.getName() %>' />

		<br /><br />

		<%@ include file="/html/portlet/tagged_content/select_document_library_file_entry.jspf" %>
	</c:when>
	<c:when test="<%= typeSelection.equals(IGImage.class.getName()) %>">
		<input name="<portlet:namespace />assetType" type="hidden" value="<%= IGImage.class.getName() %>" />

		<liferay-ui:message key="select" />: <liferay-ui:message key='<%= "model.resource." + IGImage.class.getName() %>' />

		<br /><br />

		<%@ include file="/html/portlet/tagged_content/select_image_gallery_image_entry.jspf" %>
	</c:when>
	<c:when test="<%= typeSelection.equals(JournalArticle.class.getName()) %>">
		<input name="<portlet:namespace />assetType" type="hidden" value="<%= JournalArticle.class.getName() %>" />

		<liferay-ui:message key="select" />: <liferay-ui:message key='<%= "model.resource." + JournalArticle.class.getName() %>' />

		<br /><br />

		<%@ include file="/html/portlet/tagged_content/select_journal_article.jspf" %>
	</c:when>
	<c:when test="<%= typeSelection.equals(MBMessage.class.getName()) %>">
		<input name="<portlet:namespace />assetType" type="hidden" value="<%= MBMessage.class.getName() %>" />

		<liferay-ui:message key="select" />: <liferay-ui:message key='<%= "model.resource." + MBMessage.class.getName() %>' />

		<br /><br />

		<%@ include file="/html/portlet/tagged_content/select_message_boards_message.jspf" %>
	</c:when>
	<c:when test="<%= typeSelection.equals(WikiPage.class.getName()) %>">
		<input name="<portlet:namespace />assetType" type="hidden" value="<%= WikiPage.class.getName() %>" />

		<liferay-ui:message key="select" />: <liferay-ui:message key='<%= "model.resource." + WikiPage.class.getName() %>' />

		<br /><br />

		<%@ include file="/html/portlet/tagged_content/select_wiki_page.jspf" %>
	</c:when>
</c:choose>

</form>