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

<%@ include file="/html/portlet/web_form/init.jsp" %>

<%
String title = prefs.getValue("title", StringPool.BLANK);
String description = prefs.getValue("description", StringPool.BLANK);
boolean requireCaptcha = GetterUtil.getBoolean(prefs.getValue("requireCaptcha", StringPool.BLANK));
%>

<form action="<portlet:actionURL><portlet:param name="struts_action" value="/web_form/view" /></portlet:actionURL>" class="uni-form" method="post">

<fieldset class="block-labels">
	<legend><%= Html.escape(title) %></legend>

	<p class="description"><%= Html.escape(description) %></p>

	<liferay-ui:success key="emailSent" message="the-email-was-sent-successfuly" />
	<liferay-ui:success key="saveToFileSuccees" message="the-file-was-saved-successfully" />

	<liferay-ui:error exception="<%= CaptchaTextException.class %>" message="text-verification-failed" />
	<liferay-ui:error key="allFieldsRequired" message="please-complete-all-fields" />
	<liferay-ui:error key="emailNotSent" message="the-email-could-not-be-sent" />
	<liferay-ui:error key="saveToFileFailure" message="the-file-could-not-be-saved" />

	<%
	int i = 1;

	String fieldName = "field" + i;
	String fieldLabel = prefs.getValue("fieldLabel" + i, StringPool.BLANK);
	boolean fieldOptional = PrefsParamUtil.getBoolean(prefs, request, "fieldOptional" + i, false);
	String fieldValue = ParamUtil.getString(request, fieldName);

	while ((i == 1) || (fieldLabel.trim().length() > 0)) {
		if (Validator.isNull(fieldLabel)) {
		   continue;
		}

		String fieldType = prefs.getValue("fieldType" + i, "text");
		String fieldOptions = prefs.getValue("fieldOptions" + i, "unknown");
	%>

		<c:choose>
			<c:when test='<%= fieldType.equals("paragraph") %>'>
				<p class="lfr-webform"><%= fieldOptions %></p>
			</c:when>
			<c:when test='<%= fieldType.equals("text") %>'>
				<div class="ctrl-holder">
					<label class='<%= fieldOptional ? "optional" : "" %>' for="<portlet:namespace /><%= fieldName %>"><%= Html.escape(fieldLabel) %></label>

					<input class='<%= fieldOptional ? "optional" : "" %>' id="<portlet:namespace /><%= fieldName %>" name="<portlet:namespace /><%= fieldName %>" type="text" value="<%= Html.escape(fieldValue) %>" />
				</div>
			</c:when>
			<c:when test='<%= fieldType.equals("textarea") %>'>
				<div class="ctrl-holder">
					<label class='<%= fieldOptional ? "optional" : "" %>' for="<portlet:namespace /><%= fieldName %>"><%= Html.escape(fieldLabel) %></label>

					<textarea class='<%= fieldOptional ? "optional" : "" %>' id="<portlet:namespace /><%= fieldName %>" name="<portlet:namespace /><%= fieldName %>" wrap="soft"><%= Html.escape(fieldValue) %></textarea>
				</div>
			</c:when>
			<c:when test='<%= fieldType.equals("checkbox") %>'>
				<div class="ctrl-holder <%= fieldOptional ? "optional" : "" %>">
					<label class='<%= fieldOptional ? "optional" : "" %>' for="<portlet:namespace /><%= fieldName %>"><input <%= Validator.isNotNull(fieldValue) ? "checked" : "" %> id="<portlet:namespace /><%= fieldName %>" name="<portlet:namespace /><%= fieldName %>" type="checkbox" /> <%= Html.escape(fieldLabel) %></label>
				</div>
			</c:when>
			<c:when test='<%= fieldType.equals("radio") %>'>
				<div class="ctrl-holder <%= fieldOptional ? "optional" : "" %>">
					<label class='<%= fieldOptional ? "optional" : "" %>' for="<portlet:namespace /><%= fieldName %>"><%= Html.escape(fieldLabel) %></label>

					<%
					String[] options = WebFormUtil.split(fieldOptions);

					for (int j = 0; j < options.length; j++) {
						String optionValue = options[j];
					%>

						<label><input type="radio" name="<portlet:namespace /><%= fieldName %>" <%= fieldValue.equals(optionValue) ? "checked=\"true\"" : "" %> value="<%= Html.escape(optionValue) %>" /> <%= Html.escape(optionValue) %></label>

					<%
					}
					%>

				</div>
			</c:when>
			<c:when test='<%= fieldType.equals("options") %>'>
				<div class="ctrl-holder <%= fieldOptional ? "optional" : "" %>">
					<label class='<%= fieldOptional ? "optional" : "" %>' for="<portlet:namespace /><%= fieldName %>"><%= fieldLabel %></label>

					<%
					String[] options = WebFormUtil.split(fieldOptions);
					%>

					<select name="<portlet:namespace /><%= fieldName %>">

						<%
						for (int j = 0; j < options.length; j++) {
							String optionValue = options[j];
						%>

							<option <%= fieldValue.equals(optionValue) ? "selected" : "" %> value="<%= Html.escape(optionValue) %>"><%= Html.escape(optionValue) %></option>

						<%
						}
						%>

					</select>
				</div>
			</c:when>
		</c:choose>

	<%
		i++;

		fieldName = "field" + i;
		fieldLabel = prefs.getValue("fieldLabel" + i, "");
		fieldOptional = PrefsParamUtil.getBoolean(prefs, request, "fieldOptional" + i, false);
		fieldValue = ParamUtil.getString(request, fieldName);
	}
	%>

	<c:if test="<%= requireCaptcha %>">
		<portlet:actionURL windowState="<%= LiferayWindowState.EXCLUSIVE.toString() %>" var="captchaURL">
			<portlet:param name="struts_action" value="/web_form/captcha" />
		</portlet:actionURL>

		<liferay-ui:captcha url="<%= captchaURL %>" />
	</c:if>

	<div class="button-holder">
		<input type="submit" value="<liferay-ui:message key="send" />" />
	</div>
</fieldset>

</form>