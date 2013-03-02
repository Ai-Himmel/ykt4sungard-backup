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

<%@ include file="/html/portlet/journal/init.jsp" %>

<%
String portletResource = ParamUtil.getString(request, "portletResource");

String tabs2 = ParamUtil.getString(request, "tabs2");

String redirect = ParamUtil.getString(request, "redirect");

// Make sure the redirect is correct. This is a workaround for a layout that
// has both the Journal and Journal Content portlets and the user edits an
// article through the Journal Content portlet and then hits cancel.

/*if (redirect.indexOf("p_p_id=" + PortletKeys.JOURNAL_CONTENT) != -1) {
	if (layoutTypePortlet.hasPortletId(PortletKeys.JOURNAL)) {
		PortletURL portletURL = renderResponse.createRenderURL();

		portletURL.setWindowState(WindowState.NORMAL);
		portletURL.setPortletMode(PortletMode.VIEW);

		redirect = portletURL.toString();
	}
}*/

String originalRedirect = ParamUtil.getString(request, "originalRedirect", StringPool.BLANK);

if (originalRedirect.equals(StringPool.BLANK)) {
	originalRedirect = redirect;
}
else {
	redirect = originalRedirect;
}

String referringPortletResource = ParamUtil.getString(request, "referringPortletResource");

JournalArticle article = (JournalArticle)request.getAttribute(WebKeys.JOURNAL_ARTICLE);

long groupId = BeanParamUtil.getLong(article, request, "groupId", portletGroupId.longValue());

String articleId = BeanParamUtil.getString(article, request, "articleId");
String newArticleId = ParamUtil.getString(request, "newArticleId");

double version = BeanParamUtil.getDouble(article, request, "version", JournalArticleImpl.DEFAULT_VERSION);
boolean incrementVersion = ParamUtil.getBoolean(request, "incrementVersion");

Calendar displayDate = CalendarFactoryUtil.getCalendar(timeZone, locale);

if (article != null) {
	if (article.getDisplayDate() != null) {
		displayDate.setTime(article.getDisplayDate());
	}
}

boolean neverExpire = ParamUtil.getBoolean(request, "neverExpire", true);

Calendar expirationDate = CalendarFactoryUtil.getCalendar(timeZone, locale);

expirationDate.add(Calendar.YEAR, 1);

if (article != null) {
	if (article.getExpirationDate() != null) {
		neverExpire = false;

		expirationDate.setTime(article.getExpirationDate());
	}
}

boolean neverReview = ParamUtil.getBoolean(request, "neverReview", true);

Calendar reviewDate = CalendarFactoryUtil.getCalendar(timeZone, locale);

reviewDate.add(Calendar.MONTH, 9);

if (article != null) {
	if (article.getReviewDate() != null) {
		neverReview = false;

		reviewDate.setTime(article.getReviewDate());
	}
}

String type = BeanParamUtil.getString(article, request, "type", "general");

String structureId = BeanParamUtil.getString(article, request, "structureId");

JournalStructure structure = null;

String structureName = StringPool.BLANK;

if (Validator.isNotNull(structureId)) {
	try {
		structure = JournalStructureLocalServiceUtil.getStructure(groupId, structureId);

		structureName = structure.getName();
	}
	catch (NoSuchStructureException nsse) {
	}
}

List templates = new ArrayList();

if (structure != null) {
	templates = JournalTemplateLocalServiceUtil.getStructureTemplates(groupId, structureId);
}

String templateId = BeanParamUtil.getString(article, request, "templateId");

if ((structure == null) && Validator.isNotNull(templateId)) {
	JournalTemplate template = null;

	try {
		template = JournalTemplateLocalServiceUtil.getTemplate(groupId, templateId);

		structureId = template.getStructureId();

		structure = JournalStructureLocalServiceUtil.getStructure(groupId, structureId);

		structureName = structure.getName();

		templates = JournalTemplateLocalServiceUtil.getStructureTemplates(groupId, structureId);
	}
	catch (NoSuchTemplateException nste) {
	}
}

String languageId = LanguageUtil.getLanguageId(request);

String defaultLanguageId = ParamUtil.getString(request, "defaultLanguageId");

if (article == null) {
	defaultLanguageId = languageId;
}
else {
	if (Validator.isNull(defaultLanguageId)) {
		defaultLanguageId =	article.getDefaultLocale();
	}
}

Locale defaultLocale = LocaleUtil.fromLanguageId(defaultLanguageId);

String content = null;

if (article != null) {
	content = article.getContentByLocale(languageId);
}
else {
	content = ParamUtil.getString(request, "content");
}

boolean disableIncrementVersion = false;

if (PropsValues.JOURNAL_ARTICLE_FORCE_INCREMENT_VERSION) {
	boolean latestVersion = (article == null) || (article != null && JournalArticleLocalServiceUtil.isLatestVersion(article.getGroupId(), articleId, version));

	if (!latestVersion) {
		incrementVersion = true;
		disableIncrementVersion = true;
	}

	if ((article != null) && article.isApproved()) {
		incrementVersion = true;
		disableIncrementVersion = true;
	}
}

boolean smallImage = BeanParamUtil.getBoolean(article, request, "smallImage");
String smallImageURL = BeanParamUtil.getString(article, request, "smallImageURL");
%>

<script type="text/javascript">
	var <portlet:namespace />count = 0;
	var <portlet:namespace />documentLibraryInput = null;
	var <portlet:namespace />imageGalleryInput = null;
	var <portlet:namespace />contentChangedFlag = false;

	function <portlet:namespace />approveArticle() {
		<portlet:namespace />saveArticle("<%= Constants.APPROVE %>");
	}

	function <portlet:namespace />changeLanguageView() {
		if (<portlet:namespace />contentChangedFlag) {
			if (confirm("<%= UnicodeLanguageUtil.get(pageContext, "would-you-like-to-save-the-changes-made-to-this-language") %>")) {
				document.<portlet:namespace />fm1.<portlet:namespace /><%= Constants.CMD %>.value = "<%= Constants.UPDATE %>";
			}
			else {
				if (!confirm("<%= UnicodeLanguageUtil.get(pageContext, "are-you-sure-you-want-to-switch-the-languages-view") %>")) {
					var languageIdOptions = document.<portlet:namespace />fm1.<portlet:namespace />languageId.options;

					for (var i = 0; i < languageIdOptions.length; i++) {
						if (languageIdOptions[i].value == "<%= languageId %>") {
							languageIdOptions[i].selected = true;
						}
					}

					return;
				}
			}
		}

		document.<portlet:namespace />fm1.<portlet:namespace />redirect.value = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/journal/edit_article" /><portlet:param name="redirect" value="<%= redirect %>" /><portlet:param name="groupId" value="<%= String.valueOf(groupId) %>" /><portlet:param name="articleId" value="<%= articleId %>" /><portlet:param name="version" value="<%= String.valueOf(version) %>" /></portlet:renderURL>&<portlet:namespace />languageId=" + document.<portlet:namespace />fm1.<portlet:namespace />languageId.value;
		document.<portlet:namespace />fm1.<portlet:namespace />content.value = <portlet:namespace />getArticleContent();
		submitForm(document.<portlet:namespace />fm1);
	}

	function <portlet:namespace />contentChanged() {
		<portlet:namespace />contentChangedFlag = true;
	}

	function <portlet:namespace />deleteArticle() {
		if (confirm("<%= UnicodeLanguageUtil.get(pageContext, "are-you-sure-you-want-to-deactivate-this") %>")) {
			document.<portlet:namespace />fm1.<portlet:namespace /><%= Constants.CMD %>.value = "<%= Constants.DELETE %>";
			submitForm(document.<portlet:namespace />fm1);
		}
	}

	function <portlet:namespace />disableInputDate(date, checked) {
		eval("document.<portlet:namespace />fm1.<portlet:namespace />" + date + "Month.disabled = " + checked + ";");
		eval("document.<portlet:namespace />fm1.<portlet:namespace />" + date + "Day.disabled = " + checked + ";");
		eval("document.<portlet:namespace />fm1.<portlet:namespace />" + date + "Year.disabled = " + checked + ";");
		eval("document.<portlet:namespace />fm1.<portlet:namespace />" + date + "Hour.disabled = " + checked + ";");
		eval("document.<portlet:namespace />fm1.<portlet:namespace />" + date + "Minute.disabled = " + checked + ";");
		eval("document.<portlet:namespace />fm1.<portlet:namespace />" + date + "AmPm.disabled = " + checked + ";");
	}

	function <portlet:namespace />downloadArticleContent() {
		document.<portlet:namespace />fm2.action = "<%= themeDisplay.getPathMain() %>/journal/get_article_content";
		document.<portlet:namespace />fm2.target = "_self";
		document.<portlet:namespace />fm2.xml.value = <portlet:namespace />getArticleContent();
		document.<portlet:namespace />fm2.submit();
	}

	function <portlet:namespace />editorContentChanged(text) {
		<portlet:namespace />contentChanged();
	}

	function <portlet:namespace />expireArticle() {
		document.<portlet:namespace />fm1.<portlet:namespace /><%= Constants.CMD %>.value = "<%= Constants.EXPIRE %>";
		submitForm(document.<portlet:namespace />fm1);
	}

	function <portlet:namespace />getArticleContent() {
		<c:choose>
			<c:when test="<%= structure == null %>">
				return window.<portlet:namespace />editor.getHTML();
			</c:when>
			<c:otherwise>
				var stillLocalized = false;

				for (var i = 0; i < <portlet:namespace />count; i++) {
					var elLanguage = document.getElementById("<portlet:namespace />structure_el" + i + "_localized");

					if (elLanguage.value != "false") {
						stillLocalized = true;
					}
				}

				var xsd = "<root";

				if (stillLocalized) {
					xsd += " default-locale='<%= defaultLanguageId %>'";
				}

				var availableLocales = document.<portlet:namespace />fm1.<portlet:namespace />available_locales;

				if (stillLocalized && availableLocales.length > 1) {
					xsd += " available-locales='";

					for (var i = 1; i < availableLocales.length; i++) {
						if ((i + 1) == availableLocales.length) {
							xsd += availableLocales[i].value + "'";
						}
						else{
							xsd += availableLocales[i].value + ",";
						}
					}
				}

				xsd += ">";

				for (i = 0; i >= 0; i++) {
					var elDepth = document.getElementById("<portlet:namespace />structure_el" + i + "_depth");
					var elName = document.getElementById("<portlet:namespace />structure_el" + i + "_name");
					var elType = document.getElementById("<portlet:namespace />structure_el" + i + "_type");
					var elContent = document.getElementById("<portlet:namespace />structure_el" + i + "_content");
					var elLanguage = document.getElementById("<portlet:namespace />structure_el" + i + "_localized");

					if ((elDepth != null) && (elName != null) && (elType != null)) {
						var elDepthValue = elDepth.value;
						var elNameValue = elName.value;
						var elTypeValue = elType.value;
						var elContentValue = "";
						var elLanguageValue = elLanguage.value;

						if ((elTypeValue == "text") || (elTypeValue == "text_box") || (elTypeValue == "image_gallery") || (elTypeValue == "document_library")) {
							elContentValue = elContent.value;
							elContentValue = "<![CDATA[" + elContentValue + "]]>";
						}
						else if (elTypeValue == "text_area") {
							eval("elContentValue = window.<portlet:namespace />structure_el" + i + "_content.getHTML();");

							elContentValue = "<![CDATA[" + elContentValue + "]]>";
						}
						else if (elTypeValue == "image") {
							var elContentName = elContent.getAttribute("name");

							if (stillLocalized && (elLanguageValue != null) && (elLanguageValue != "false") && (elLanguageValue != "") && (!elContentName.match(new RegExp(elLanguageValue + "$")))) {
								elContent.setAttribute("name", elContentName + "_" + elLanguageValue);
							}

							var elDeleteState = document.getElementById("<portlet:namespace />structure_el" + i + "_delete_state");

							if ((elDeleteState != null) && (elDeleteState.value == "yes")) {
								elContentValue = "delete";
							}

							elContentValue = "<![CDATA[" + elContentValue + "]]>";
						}
						else if (elTypeValue == "boolean") {
							elContentValue = elContent.checked ? "true" : "false";
							elContentValue = "<![CDATA[" + elContentValue + "]]>";
						}
						else if (elTypeValue == "list") {
							elContentValue = "";

							if (elContent.selectedIndex > -1) {
								elContentValue = elContent.options[elContent.selectedIndex].value;
							}

							elContentValue = "<![CDATA[" + elContentValue + "]]>";
						}
						else if (elTypeValue == "multi-list") {
							for (var l = 0; l < elContent.length; l++) {
								if (elContent.options[l].selected) {
									elContentValue += "<option><![CDATA[" + elContent.options[l].value + "]]></option>";
								}
							}
						}

						xsd += "<dynamic-element name='" + elNameValue + "' type='" + elTypeValue + "'><dynamic-content";

						if (stillLocalized && (elLanguageValue != null) && (elLanguageValue != "false") && (elLanguageValue != "")) {
							xsd += " language-id='" + elLanguageValue + "'";
						}

						xsd += ">" + elContentValue + "</dynamic-content>"

						var nextElDepth = document.getElementById("<portlet:namespace />structure_el" + (i + 1) + "_depth");

						if (nextElDepth != null) {
							nextElDepthValue = nextElDepth.value;

							if (elDepthValue == nextElDepthValue) {
								xsd += "</dynamic-element>";
							}
							else if (elDepthValue > nextElDepthValue) {
								var depthDiff = elDepthValue - nextElDepthValue;

								for (var j = 0; j <= depthDiff; j++) {
									xsd += "</dynamic-element>";
								}
							}
						}
						else {
							for (var j = 0; j <= elDepthValue; j++) {
								xsd += "</dynamic-element>";
							}
						}
					}
					else {
						break;
					}
				}

				xsd += "</root>";

				return xsd;
			</c:otherwise>
		</c:choose>
	}

	function <portlet:namespace />getChoice(value) {
		for (var i = 0; i < document.<portlet:namespace />fm1.<portlet:namespace />languageId.length; i++) {
			if (document.<portlet:namespace />fm1.<portlet:namespace />languageId.options[i].value == value) {
				return document.<portlet:namespace />fm1.<portlet:namespace />languageId.options[i].index;
			}
		}

		return null;
	}

	function initEditor() {
		return "<%= UnicodeFormatter.toString(content) %>";
	}

	function <portlet:namespace />previewArticle() {
		document.<portlet:namespace />fm2.action = "<%= themeDisplay.getPathMain() %>/journal/view_article_content?<%= Constants.CMD %>=<%= Constants.PREVIEW %>&groupId=<%= String.valueOf(groupId) %>&articleId=<%= HttpUtil.encodeURL(articleId) %>&version=<%= version %>&languageId=" + document.<portlet:namespace />fm1.<portlet:namespace />languageId.value + "&templateId=" + Liferay.Util.getSelectedRadioValue(document.<portlet:namespace />fm1.<portlet:namespace />templateId);
		document.<portlet:namespace />fm2.target = "_blank";
		document.<portlet:namespace />fm2.title.value = document.<portlet:namespace />fm1.<portlet:namespace />title.value;
		document.<portlet:namespace />fm2.xml.value = <portlet:namespace />getArticleContent();
		document.<portlet:namespace />fm2.submit();
	}

	function <portlet:namespace />removeArticleLocale() {
		if (confirm("<%= UnicodeLanguageUtil.get(pageContext, "are-you-sure-you-want-to-deactivate-this-language") %>")) {
			document.<portlet:namespace />fm1.<portlet:namespace /><%= Constants.CMD %>.value = "removeArticlesLocale";
			document.<portlet:namespace />fm1.<portlet:namespace />redirect.value = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="redirect" value="<%= redirect %>" /><portlet:param name="struts_action" value="/journal/edit_article" /><portlet:param name="groupId" value="<%= String.valueOf(groupId) %>" /><portlet:param name="articleId" value="<%= articleId %>" /><portlet:param name="version" value="<%= String.valueOf(version) %>" /></portlet:renderURL>&<portlet:namespace />languageId=<%= defaultLanguageId %>";
			submitForm(document.<portlet:namespace />fm1);
		}
	}

	function <portlet:namespace />removeStructure() {
		document.<portlet:namespace />fm1.<portlet:namespace />structureId.value = "";
		document.<portlet:namespace />fm1.<portlet:namespace />templateId.value = "";
		document.<portlet:namespace />fm1.<portlet:namespace />content.value = "";
		submitForm(document.<portlet:namespace />fm1);
	}

	function <portlet:namespace />saveAndApproveArticle() {
		document.<portlet:namespace />fm1.<portlet:namespace />approve.value = "1";
		<portlet:namespace />saveArticle();
	}

	function <portlet:namespace />saveAndContinueArticle() {
		document.<portlet:namespace />fm1.<portlet:namespace />saveAndContinue.value = "1";
		<portlet:namespace />saveArticle();
	}

	function <portlet:namespace />saveArticle(cmd) {
		if (cmd == null) {
			cmd = "<%= article == null ? Constants.ADD : Constants.UPDATE %>";
		}

		document.<portlet:namespace />fm1.<portlet:namespace /><%= Constants.CMD %>.value = cmd;

		<c:if test="<%= article == null %>">
			document.<portlet:namespace />fm1.<portlet:namespace />articleId.value = document.<portlet:namespace />fm1.<portlet:namespace />newArticleId.value;
		</c:if>

		document.<portlet:namespace />fm1.<portlet:namespace />content.value = <portlet:namespace />getArticleContent();
		submitForm(document.<portlet:namespace />fm1);
	}

	function <portlet:namespace />selectDocumentLibrary(url) {
		document.getElementById(<portlet:namespace />documentLibraryInput).value = url;
	}

	function <portlet:namespace />selectImageGallery(url) {
		document.getElementById(<portlet:namespace />imageGalleryInput).value = url;
	}

	function <portlet:namespace />selectStructure(structureId) {
		if (document.<portlet:namespace />fm1.<portlet:namespace />structureId.value != structureId) {
			document.<portlet:namespace />fm1.<portlet:namespace />structureId.value = structureId;
			document.<portlet:namespace />fm1.<portlet:namespace />templateId.value = "";
			document.<portlet:namespace />fm1.<portlet:namespace />content.value = <portlet:namespace />getArticleContent();
			submitForm(document.<portlet:namespace />fm1);
		}
	}

	function <portlet:namespace />selectTemplate(structureId, templateId) {
		document.<portlet:namespace />fm1.<portlet:namespace />structureId.value = structureId;
		document.<portlet:namespace />fm1.<portlet:namespace />templateId.value = templateId;
		document.<portlet:namespace />fm1.<portlet:namespace />content.value = <portlet:namespace />getArticleContent();
		submitForm(document.<portlet:namespace />fm1);
	}

	function <portlet:namespace />setImageDeleteState(button, hidden, img, file) {
		var deleteState = document.getElementById(hidden);

		if (deleteState.value != "yes") {
			deleteState.value = "yes";
			document.images[img].style.display = "none";
			document.getElementById(file).disabled = true;
			button.value = "<liferay-ui:message key="cancel" />";
		}
		else {
			deleteState.value = "no";
			document.images[img].style.display = "block";
			document.getElementById(file).disabled = false;
			button.value = "<liferay-ui:message key="delete" />";
		}
	}
</script>

<form method="post" name="<portlet:namespace />fm2">
<input name="groupId" type="hidden" value="" />
<input name="articleId" type="hidden" value="" />
<input name="version" type="hidden" value="" />
<input name="title" type="hidden" value="" />
<input name="xml" type="hidden" value="" />
</form>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/journal/edit_article" /></portlet:actionURL>" class="uni-form" enctype="multipart/form-data" method="post" name="<portlet:namespace />fm1" onSubmit="<portlet:namespace />saveArticle(); return false;">
<input name="<portlet:namespace />portletResource" type="hidden" value="<%= portletResource %>" />
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />tabs2" type="hidden" value="<%= tabs2 %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />originalRedirect" type="hidden" value="<%= originalRedirect %>" />
<input name="<portlet:namespace />referringPortletResource" type="hidden" value="<%= referringPortletResource %>" />
<input name="<portlet:namespace />groupId" type="hidden" value="<%= groupId %>" />
<input name="<portlet:namespace />articleId" type="hidden" value="<%= articleId %>" />
<input name="<portlet:namespace />version" type="hidden" value="<%= version %>" />
<input name="<portlet:namespace />content" type="hidden" value="" />
<input name="<portlet:namespace />articleURL" type="hidden" value="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/journal/edit_article" /></portlet:renderURL>" />
<input name="<portlet:namespace />approve" type="hidden" value="" />
<input name="<portlet:namespace />saveAndContinue" type="hidden" value="" />
<input name="<portlet:namespace />deleteArticleIds" type="hidden" value="<%= articleId + EditArticleAction.VERSION_SEPARATOR + version %>" />
<input name="<portlet:namespace />expireArticleIds" type="hidden" value="<%= articleId + EditArticleAction.VERSION_SEPARATOR + version %>" />

<liferay-ui:tabs
	names="article"
	formName="fm1"
	backURL="<%= redirect %>"
/>

<%
SAXReader reader = new SAXReader();

Document contentDoc = null;

String[] availableLocales = null;
%>

<table class="lfr-table" width="100%">
<tr>
	<td valign="top">
		<liferay-ui:error exception="<%= ArticleContentException.class %>" message="please-enter-valid-content" />
		<liferay-ui:error exception="<%= ArticleIdException.class %>" message="please-enter-a-valid-id" />
		<liferay-ui:error exception="<%= ArticleTitleException.class %>" message="please-enter-a-valid-name" />
		<liferay-ui:error exception="<%= DuplicateArticleIdException.class %>" message="please-enter-a-unique-id" />
		<liferay-ui:tags-error />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="id" />
			</td>
			<td>
				<c:choose>
					<c:when test="<%= PropsValues.JOURNAL_ARTICLE_FORCE_AUTOGENERATE_ID %>">
						<c:choose>
							<c:when test="<%= article == null %>">
								<liferay-ui:message key="autogenerate-id" />

								<input name="<portlet:namespace />newArticleId" type="hidden" value="" />
								<input name="<portlet:namespace />autoArticleId" type="hidden" value="true" />
							</c:when>
							<c:otherwise>
								<%= articleId %>
							</c:otherwise>
						</c:choose>
					</c:when>
					<c:otherwise>
						<table class="lfr-table">
						<tr>
							<td>
								<c:choose>
									<c:when test="<%= article == null %>">
										<liferay-ui:input-field model="<%= JournalArticle.class %>" bean="<%= article %>" field="articleId" fieldParam="newArticleId" defaultValue="<%= newArticleId %>" />
									</c:when>
									<c:otherwise>
										<%= articleId %>
									</c:otherwise>
								</c:choose>
							</td>
							<td>
								<c:if test="<%= article == null %>">
									<liferay-ui:input-checkbox param="autoArticleId" />

									<liferay-ui:message key="autogenerate-id" />
								</c:if>
							</td>
						</tr>
						</table>
					</c:otherwise>
				</c:choose>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="name" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= JournalArticle.class %>" bean="<%= article %>" field="title" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="language" />
			</td>
			<td>
				<input name="<portlet:namespace />lastLanguageId" type="hidden" value="<%= languageId %>" />

				<table class="lfr-table">
				<tr>
					<td>
						<select <%= (article == null) ? "disabled" : "" %> name="<portlet:namespace />languageId" onChange="<portlet:namespace />changeLanguageView();">

							<%
							Locale[] locales = LanguageUtil.getAvailableLocales();

							for (int i = 0; i < locales.length; i++) {
							%>

								<option <%= (languageId.equals(LocaleUtil.toLanguageId(locales[i]))) ? "selected" : "" %> value="<%= LocaleUtil.toLanguageId(locales[i]) %>"><%= locales[i].getDisplayName(locales[i]) %></option>

							<%
							}
							%>

						</select>

						<c:if test="<%= (article != null) && !languageId.equals(defaultLanguageId) %>">
							<input type="button" name="<portlet:namespace />removeArticleLocaleButton" value="<liferay-ui:message key="remove" />" onClick="<portlet:namespace />removeArticleLocale();" />
						</c:if>
					</td>
					<td>
						<table class="lfr-table">

						<%
						contentDoc = null;

						try {
							contentDoc = reader.read(new StringReader(content));

							Element contentEl = contentDoc.getRootElement();

							availableLocales = StringUtil.split(contentEl.attributeValue("available-locales"));
						}
						catch (Exception e) {
							contentDoc = null;
						}
						%>

						<tr>
							<td>
								<liferay-ui:message key="default-language" />
							</td>
							<td>
								<select <%= (article == null) ? "disabled" : "" %> name="<portlet:namespace />defaultLanguageId" onChange="<portlet:namespace />changeLanguageView();">

									<%
									if ((availableLocales != null) && (availableLocales.length > 0)) {
										boolean wasLanguageId = false;

										for (int i = 0; i < availableLocales.length; i++) {
											if (availableLocales[i].equals(languageId)) {
												wasLanguageId = true;
											}

											Locale availableLocale = LocaleUtil.fromLanguageId(availableLocales[i]);
									%>

											<option <%= (availableLocales[i].equals(defaultLanguageId)) ? "selected" : "" %> value="<%= availableLocales[i] %>"><%= availableLocale.getDisplayName(availableLocale) %></option>

									<%
										}

										if (!wasLanguageId) {
											Locale languageLocale = LocaleUtil.fromLanguageId(languageId);
									%>

											<option value="<%= languageId %>"><%= languageLocale.getDisplayName(languageLocale) %></option>

									<%
										}
									}
									else {
									%>

										<option value="<%= defaultLanguageId %>"><%= defaultLocale.getDisplayName(defaultLocale) %></option>

									<%
									}
									%>

								</select>
							</td>
						</tr>
						</table>
					</td>
				</tr>
				</table>
			</td>
		</tr>
		</table>

		<br />

		<c:choose>
			<c:when test="<%= structure == null %>">
				<div>
					<liferay-ui:input-editor editorImpl="<%= EDITOR_WYSIWYG_IMPL_KEY %>" toolbarSet="liferay-article" onChangeMethod='<%= renderResponse.getNamespace() + "editorContentChanged" %>' width="100%" />
				</div>
			</c:when>
			<c:otherwise>
				<table border="0" cellpadding="0" cellspacing="0" width="100%">

				<input name="<portlet:namespace />available_locales" type="hidden" value="" />

				<%
				Document xsdDoc = reader.read(new StringReader(structure.getXsd()));

				if (contentDoc != null) {
				%>

					<input name="<portlet:namespace />available_locales" type="hidden" value="<%= defaultLanguageId %>"/>

				<%
					boolean languageFound = false;

					if ((availableLocales != null) && (availableLocales.length > 0)) {
						for (int i = 0; i < availableLocales.length ;i++) {
							if (!availableLocales[i].equals(defaultLanguageId)) {
				%>

								<input name="<portlet:namespace />available_locales" type="hidden" value="<%= availableLocales[i] %>" />

								<script type="text/javascript">
									document.<portlet:namespace />fm1.<portlet:namespace />languageId.options[<portlet:namespace />getChoice('<%= availableLocales[i] %>')].className = 'focused';
								</script>

				<%
							}
							else{
							%>

								<script type="text/javascript">
									document.<portlet:namespace />fm1.<portlet:namespace />languageId.options[<portlet:namespace />getChoice('<%= availableLocales[i] %>')].className = 'focused';
								</script>

				<%
							}

							if (availableLocales[i].equals(languageId)) {
								languageFound = true;
							}
						}
					}

					if (!languageFound && !languageId.equals(defaultLanguageId)) {
				%>

						<input name="<portlet:namespace />available_locales" type="hidden" value="<%= languageId %>"/>

						<script type="text/javascript">
							document.<portlet:namespace />fm1.<portlet:namespace />removeArticleLocaleButton.disabled = true;
						</script>

				<%
					}
				}
				else {
					DocumentFactory docFactory = DocumentFactory.getInstance();

					contentDoc = docFactory.createDocument(docFactory.createElement("root"));
				%>

					<input name="<portlet:namespace />available_locales" type="hidden" value="<%= defaultLanguageId %>" />

				<%
				}

				_format(groupId, contentDoc, xsdDoc.getRootElement(), new IntegerWrapper(0), new Integer(-1), pageContext, request);
				%>

				</table>
			</c:otherwise>
		</c:choose>

		<c:if test="<%= article == null %>">
			<table class="lfr-table">
			<tr>
				<td colspan="2">
					<br />
				</td>
			</tr>
			<tr>
				<td>
					<liferay-ui:message key="permissions" />
				</td>
				<td>
					<liferay-ui:input-permissions
						modelName="<%= JournalArticle.class.getName() %>"
					/>
				</td>
			</tr>
			</table>
		</c:if>

		<br />

		<table class="journal-edit-article-extra">
		<tr class="portlet-section-header">
			<td>
				<b><liferay-ui:message key="abstract" /></b>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:error exception="<%= ArticleSmallImageNameException.class %>">

					<%
					String[] imageExtensions = PropsUtil.getArray(PropsUtil.JOURNAL_IMAGE_EXTENSIONS);
					%>

					<liferay-ui:message key="image-names-must-end-with-one-of-the-following-extensions" /> <%= StringUtil.merge(imageExtensions, ", ") %>.
				</liferay-ui:error>

				<liferay-ui:error exception="<%= ArticleSmallImageSizeException.class %>" message="please-enter-a-small-image-with-a-valid-file-size" />

				<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="description" />
					</td>
					<td>
						<liferay-ui:input-field model="<%= JournalArticle.class %>" bean="<%= article %>" field="description" />
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<br />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="small-image-url" />
					</td>
					<td>
						<liferay-ui:input-field model="<%= JournalArticle.class %>" bean="<%= article %>" field="smallImageURL" />
					</td>
				</tr>
				<tr>
					<td>
						<span style="font-size: xx-small;">-- <%= LanguageUtil.get(pageContext, "or").toUpperCase() %> --</span> <liferay-ui:message key="small-image" />
					</td>
					<td>
						<input class="lfr-input-text" name="<portlet:namespace />smallFile" type="file" />
					</td>
				</tr>
				<tr>
					<td>
						<liferay-ui:message key="use-small-image" />
					</td>
					<td>
						<liferay-ui:input-field model="<%= JournalArticle.class %>" bean="<%= article %>" field="smallImage" />
					</td>
				</tr>
				</table>
			</td>
		</tr>
		</table>

		<div>
			<br />

			<c:if test="<%= PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.JOURNAL, ActionKeys.UPDATE) %>">
				<input type="submit" value="<liferay-ui:message key="save" />" />

				<input name="save-and-continue" type="button" value="<liferay-ui:message key="save-and-continue" />" onClick="<portlet:namespace />saveAndContinueArticle();" />

				<c:if test="<%= ((article == null) || ((article != null) && !article.isApproved())) && PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.JOURNAL, ActionKeys.APPROVE_ARTICLE) %>">
					<input type="button" value="<liferay-ui:message key="save-and-approve" />" onClick="<portlet:namespace />saveAndApproveArticle();" />
				</c:if>
			</c:if>

			<c:if test="<%= Validator.isNotNull(structureId) %>">
				<input type="button" value="<liferay-ui:message key="preview" />" onClick="<portlet:namespace />previewArticle();" />
			</c:if>

			<c:if test="<%= structure != null %>">
				<input type="button" value="<liferay-ui:message key="download" />" onClick="<portlet:namespace />downloadArticleContent();" />
			</c:if>

			<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />
		</div>
	</td>
	<td valign="top">
		<%@ include file="edit_article_extra.jspf" %>
	</td>
</tr>
</table>

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		<c:choose>
			<c:when test="<%= PropsValues.JOURNAL_ARTICLE_FORCE_AUTOGENERATE_ID %>">
				Liferay.Util.focusFormField(document.<portlet:namespace />fm1.<portlet:namespace />title);
			</c:when>
			<c:otherwise>
				Liferay.Util.focusFormField(document.<portlet:namespace />fm1.<portlet:namespace /><%= (article == null) ? "newArticleId" : "title" %>);
			</c:otherwise>
		</c:choose>
	</script>
</c:if>

<%!
private void _format(long groupId, Document contentDoc, Element root, IntegerWrapper count, Integer depth, PageContext pageContext, HttpServletRequest req) throws Exception {
	depth = new Integer(depth.intValue() + 1);

	Iterator itr = root.elements().iterator();

	while (itr.hasNext()) {
		Element el = (Element)itr.next();

		req.setAttribute(WebKeys.JOURNAL_ARTICLE_GROUP_ID, String.valueOf(groupId));

		req.setAttribute(WebKeys.JOURNAL_STRUCTURE_EL, el);
		req.setAttribute(WebKeys.JOURNAL_STRUCTURE_EL_COUNT, count);
		req.setAttribute(WebKeys.JOURNAL_STRUCTURE_EL_DEPTH, depth);

		req.setAttribute(WebKeys.JOURNAL_ARTICLE_CONTENT_DOC, contentDoc);

		pageContext.include("/html/portlet/journal/edit_article_content_xsd_el.jsp");

		count.increment();

		String elType = el.attributeValue("type", StringPool.BLANK);

		if (!elType.equals("list") && !elType.equals("multi-list")) {
			_format(groupId, contentDoc, el, count, depth, pageContext, req);
		}
	}
}

public static final String EDITOR_WYSIWYG_IMPL_KEY = "editor.wysiwyg.portal-web.docroot.html.portlet.journal.edit_article_content.jsp";
%>