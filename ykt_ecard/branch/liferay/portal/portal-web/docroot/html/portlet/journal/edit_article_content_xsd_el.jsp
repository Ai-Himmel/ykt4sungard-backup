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
String languageId = LanguageUtil.getLanguageId(request);

long groupId = GetterUtil.getLong((String)request.getAttribute(WebKeys.JOURNAL_ARTICLE_GROUP_ID));

Element el = (Element)request.getAttribute(WebKeys.JOURNAL_STRUCTURE_EL);

String elName = el.attributeValue("name", StringPool.BLANK);
String elType = el.attributeValue("type", StringPool.BLANK);
String elContent = StringPool.BLANK;
String elLanguageId = StringPool.BLANK;

StringMaker elPath = new StringMaker();

elPath.append(elName);

Element elParent = (Element)el.getParent();

for (;;) {
	if ((elParent == null) ||
		(elParent.getName().equals("root"))) {

		break;
	}

	elPath.insert(0, elParent.attributeValue("name") + StringPool.COMMA);

	elParent = (Element)elParent.getParent();
}

String[] elPathNames = StringUtil.split(elPath.toString());

Document contentDoc = (Document)request.getAttribute(WebKeys.JOURNAL_ARTICLE_CONTENT_DOC);

Element contentEl = contentDoc.getRootElement();

for (int i = 0; i < elPathNames.length; i++) {
	boolean foundEl = false;

	Iterator itr = contentEl.elements().iterator();

	while (itr.hasNext()) {
		Element tempEl = (Element)itr.next();

		if (elPathNames[i].equals(tempEl.attributeValue("name", StringPool.BLANK))) {
			contentEl = tempEl;
			foundEl = true;

			if ((i + 1) == elPathNames.length) {
				elContent = GetterUtil.getString(tempEl.elementText("dynamic-content"));

				if (!elType.equals("text_area")) {
					elContent = Html.toInputSafe(elContent);
				}

				Element dynConEl = tempEl.element("dynamic-content");

				if (dynConEl != null) {
					elLanguageId = dynConEl.attributeValue("language-id", StringPool.BLANK);
				}
				else {
					elLanguageId = languageId;
				}
			}

			break;
		}
	}

	if (!foundEl) {
		break;
	}
}

IntegerWrapper count = (IntegerWrapper)request.getAttribute(WebKeys.JOURNAL_STRUCTURE_EL_COUNT);
Integer depth = (Integer)request.getAttribute(WebKeys.JOURNAL_STRUCTURE_EL_DEPTH);
%>

<input id="<portlet:namespace />structure_el<%= count.getValue() %>_depth" type="hidden" value="<%= depth %>" />
<input id="<portlet:namespace />structure_el<%= count.getValue() %>_name" type="hidden" value="<%= elName %>" />
<input id="<portlet:namespace />structure_el<%= count.getValue() %>_type" type="hidden" value="<%= elType %>" />
<input id="<portlet:namespace />structure_el<%= count.getValue() %>_localized" type="hidden" value='<%= !elLanguageId.equals(StringPool.BLANK) ? languageId : "false" %>' />

<tr>
	<td>
		<c:if test="<%= count.getValue() > 0 %>">
			<br />
		</c:if>

		<table class="lfr-table">
		<tr>
			<c:if test="<%= depth.intValue() > 0 %>">
				<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="<%= depth.intValue() * 50 %>" /></td>
			</c:if>

			<td width="100%">
				<table border="0" cellpadding="0" cellspacing="0" width="100%">
				<tr>
					<td>
						<c:if test='<%= elType.equals("text") %>'>
							<input id="<portlet:namespace />structure_el<%= count.getValue() %>_content" size="75" type="text" value="<%= elContent %>" onChange="<portlet:namespace />contentChanged();" />
						</c:if>

						<c:if test='<%= elType.equals("text_box") %>'>
							<textarea cols="80" id="<portlet:namespace />structure_el<%= count.getValue() %>_content" rows="10" onChange="<portlet:namespace />contentChanged();"><%= elContent %></textarea>
						</c:if>

						<c:if test='<%= elType.equals("text_area") %>'>
							<script type="text/javascript">
								function initEditor<%= count.getValue() %>() {
									return "<%= UnicodeFormatter.toString(elContent) %>";
								}
							</script>

							<liferay-ui:input-editor
								name='<%= renderResponse.getNamespace() + "structure_el" + count.getValue() + "_content" %>'
								editorImpl="<%= EDITOR_WYSIWYG_IMPL_KEY %>"
								toolbarSet="liferay-article"
								initMethod='<%= "initEditor" + count.getValue() %>'
								onChangeMethod='<%= renderResponse.getNamespace() + "editorContentChanged" %>'
								height="250"
								width="600"
							/>
						</c:if>

						<c:if test='<%= elType.equals("image") %>'>
							<input id="<portlet:namespace />structure_el<%= count.getValue() %>_content" name="structure_image_<%= elName + (!elLanguageId.equals(StringPool.BLANK) ? "_" + languageId : "") %>" size="75" type="file" onChange="<portlet:namespace />contentChanged();" />

							<c:if test="<%= Validator.isNotNull(elContent) %>">
								<span style="font-size: xx-small; margin-left: 15px;">
								[<a href="javascript: void(0);" onClick="Liferay.Util.toggleByIdSpan(this, '<portlet:namespace />image_<%= elName %>'); self.focus();"><span><liferay-ui:message key="show" /></span><span style="display: none;"><liferay-ui:message key="hide" /></span></a>]
								</span>
							</c:if>
						</c:if>

						<c:if test='<%= elType.equals("image_gallery") %>'>
							<input id="<portlet:namespace />structure_el<%= count.getValue() %>_content" size="75" type="text" value="<%= elContent %>" onChange="<portlet:namespace />contentChanged();" /> <input type="button" value="<liferay-ui:message key="select" />" onClick="<portlet:namespace />imageGalleryInput = '<portlet:namespace />structure_el<%= count.getValue() %>_content'; var imageGalleryWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/journal/select_image_gallery" /><portlet:param name="groupId" value="<%= String.valueOf(groupId) %>" /></portlet:renderURL>', 'imageGallery', 'directories=no,height=640,location=no,menubar=no,resizable=yes,scrollbars=yes,status=no,toolbar=no,width=680'); void(''); imageGalleryWindow.focus();" />
						</c:if>

						<c:if test='<%= elType.equals("document_library") %>'>
							<input id="<portlet:namespace />structure_el<%= count.getValue() %>_content" size="75" type="text" value="<%= elContent %>" onChange="<portlet:namespace />contentChanged();" /> <input type="button" value="<liferay-ui:message key="select" />" onClick="<portlet:namespace />documentLibraryInput = '<portlet:namespace />structure_el<%= count.getValue() %>_content';  var documentLibraryWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/journal/select_document_library" /><portlet:param name="groupId" value="<%= String.valueOf(groupId) %>" /></portlet:renderURL>', 'documentLibrary', 'directories=no,height=640,location=no,menubar=no,resizable=yes,scrollbars=yes,status=no,toolbar=no,width=680'); void(''); documentLibraryWindow.focus();" />
						</c:if>

						<c:if test='<%= elType.equals("boolean") %>'>
							<input id="<portlet:namespace />structure_el<%= count.getValue() %>_content" type="checkbox" <%= elContent.equals("true") ? "checked" : "" %> onChange="<portlet:namespace />contentChanged();" />
						</c:if>

						<c:if test='<%= elType.equals("list") %>'>
							<select id="<portlet:namespace />structure_el<%= count.getValue() %>_content" onChange="<portlet:namespace />contentChanged();">

								<%
								Iterator itr = el.elements().iterator();

								while (itr.hasNext()) {
									Element child = (Element)itr.next();

									String listElName = child.attributeValue("name", StringPool.BLANK);
									String listElValue = child.attributeValue("type", StringPool.BLANK);
								%>

									<option <%= elContent.equals(listElName) ? "selected" : "" %> value="<%= listElName %>"><%= listElValue %></option>

								<%
								}
								%>

							</select>
						</c:if>

						<c:if test='<%= elType.equals("multi-list") %>'>
							<select id="<portlet:namespace />structure_el<%= count.getValue() %>_content" multiple="true" onChange="<portlet:namespace />contentChanged();">

								<%
								Iterator itr1 = el.elements().iterator();

								while (itr1.hasNext()) {
									Element child = (Element)itr1.next();

									String listElName = child.attributeValue("name", StringPool.BLANK);
									String listElValue = child.attributeValue("type", StringPool.BLANK);

									boolean contains = false;

									Element dynConEl = contentEl.element("dynamic-content");

									if (dynConEl != null) {
										Iterator itr2 = dynConEl.elements("option").iterator();

										while (itr2.hasNext()) {
											Element option = (Element)itr2.next();

											if (listElName.equals(option.getText())) {
												contains = true;
											}
										}
									}
								%>

									<option <%= contains ? "selected" : "" %> value="<%= listElName %>"><%= listElValue %></option>

								<%
								}
								%>

							</select>
						</c:if>
					</td>
				</tr>

				<c:if test='<%= elType.equals("image") && Validator.isNotNull(elContent) %>'>
					<tr>
						<td>
							<div id="<portlet:namespace />image_<%= elName %>" style="border: 1px dotted; display: none; overflow: scroll; overflow-x: scroll; overflow-y: scroll; padding: 4px; width: 500px;">
								<table>
								<tr>
									<td>
										<img name="<portlet:namespace />image_<%= elName %>_img" hspace="0" src="<%= elContent %>" vspace="0" />
									</td>
								</tr>
								<tr>
									<td>
										<input type="button" value="<liferay-ui:message key="delete" />" onClick="<portlet:namespace />setImageDeleteState(this, '<portlet:namespace />structure_el<%= count.getValue() %>_delete_state', '<portlet:namespace />image_<%= elName %>_img', '<portlet:namespace />structure_el<%= count.getValue() %>_content');" />
									</td>
								</tr>
								</table>

								<input id="<portlet:namespace />structure_el<%= count.getValue() %>_delete_state" type="hidden" value="" />
							</div>
						</td>
					</tr>
				</c:if>

				</table>
			</td>
		</tr>
		<tr class="gamma">
			<c:if test="<%= depth.intValue() > 0 %>">
				<td></td>
			</c:if>

			<td>
				<table border="0" cellpadding="0" cellspacing="0">
				<tr>
					<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="2" /></td>
					<td width="125">
						<span style="font-size: xx-small;"><b><%= TextFormatter.format(elName, TextFormatter.J) %></b></span>
					</td>
					<td>
						<input type="checkbox" <%= elLanguageId.equals(StringPool.BLANK) ? "" : "checked" %> onClick="if (this.checked) { document.<portlet:namespace />fm1.<portlet:namespace />structure_el<%= count.getValue() %>_localized.value = '<%= languageId %>'; } else { if (confirm('<%= UnicodeLanguageUtil.get(pageContext, "unchecking-this-field-will-remove-localized-data-for-languages-not-shown-in-this-view") %>')) { document.<portlet:namespace />fm1.<portlet:namespace />structure_el<%= count.getValue() %>_localized.value = 'false'; } else { this.checked = true; }};" /> <span style="font-size: xx-small;"><liferay-ui:message key="localized" /></span>
					</td>
				</tr>
				</table>
			</td>
		</tr>
		</table>

		<script type="text/javascript">
			<portlet:namespace />count++;
		</script>
	</td>
</tr>

<%!
public static final String EDITOR_WYSIWYG_IMPL_KEY = "editor.wysiwyg.portal-web.docroot.html.portlet.journal.edit_article_content_xsd_el.jsp";
%>