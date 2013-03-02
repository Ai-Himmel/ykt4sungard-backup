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

<%@ include file="/html/portlet/translator/init.jsp" %>

<%
Translation translation = (Translation)request.getAttribute(WebKeys.TRANSLATOR_TRANSLATION);

if (translation == null) {
	translation = new Translation(PropsUtil.get(PropsUtil.TRANSLATOR_DEFAULT_LANGUAGES), StringPool.BLANK, StringPool.BLANK);
}
%>

<form accept-charset="UTF-8" action="<portlet:actionURL />" method="post" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">

<c:if test="<%= Validator.isNotNull(translation.getToText()) %>">
	<%= Html.escape(translation.getToText()) %>

	<br /><br />
</c:if>

<textarea class="lfr-textarea" name="<portlet:namespace />text" wrap="soft"><%= Html.escape(translation.getFromText()) %></textarea>

<br /><br />

<select name="<portlet:namespace />id">
	<option <%= (translation.getTranslationId().equals("en_zh")) ? "selected" : "" %> value="en_zh"><liferay-ui:message key="en_zh" /></option>
	<option <%= (translation.getTranslationId().equals("en_zt")) ? "selected" : "" %> value="en_zt"><liferay-ui:message key="en_zt" /></option>
	<option <%= (translation.getTranslationId().equals("en_nl")) ? "selected" : "" %> value="en_nl"><liferay-ui:message key="en_nl" /></option>
	<option <%= (translation.getTranslationId().equals("en_fr")) ? "selected" : "" %> value="en_fr"><liferay-ui:message key="en_fr" /></option>
	<option <%= (translation.getTranslationId().equals("en_de")) ? "selected" : "" %> value="en_de"><liferay-ui:message key="en_de" /></option>
	<option <%= (translation.getTranslationId().equals("en_it")) ? "selected" : "" %> value="en_it"><liferay-ui:message key="en_it" /></option>
	<option <%= (translation.getTranslationId().equals("en_ja")) ? "selected" : "" %> value="en_ja"><liferay-ui:message key="en_ja" /></option>
	<option <%= (translation.getTranslationId().equals("en_ko")) ? "selected" : "" %> value="en_ko"><liferay-ui:message key="en_ko" /></option>
	<option <%= (translation.getTranslationId().equals("en_pt")) ? "selected" : "" %> value="en_pt"><liferay-ui:message key="en_pt" /></option>
	<option <%= (translation.getTranslationId().equals("en_es")) ? "selected" : "" %> value="en_es"><liferay-ui:message key="en_es" /></option>
	<option <%= (translation.getTranslationId().equals("zh_en")) ? "selected" : "" %> value="zh_en"><liferay-ui:message key="zh_en" /></option>
	<option <%= (translation.getTranslationId().equals("zt_en")) ? "selected" : "" %> value="zt_en"><liferay-ui:message key="zt_en" /></option>
	<option <%= (translation.getTranslationId().equals("nl_en")) ? "selected" : "" %> value="nl_en"><liferay-ui:message key="nl_en" /></option>
	<option <%= (translation.getTranslationId().equals("fr_en")) ? "selected" : "" %> value="fr_en"><liferay-ui:message key="fr_en" /></option>
	<option <%= (translation.getTranslationId().equals("fr_de")) ? "selected" : "" %> value="fr_de"><liferay-ui:message key="fr_de" /></option>
	<option <%= (translation.getTranslationId().equals("de_en")) ? "selected" : "" %> value="de_en"><liferay-ui:message key="de_en" /></option>
	<option <%= (translation.getTranslationId().equals("de_fr")) ? "selected" : "" %> value="de_fr"><liferay-ui:message key="de_fr" /></option>
	<option <%= (translation.getTranslationId().equals("it_en")) ? "selected" : "" %> value="it_en"><liferay-ui:message key="it_en" /></option>
	<option <%= (translation.getTranslationId().equals("ja_en")) ? "selected" : "" %> value="ja_en"><liferay-ui:message key="ja_en" /></option>
	<option <%= (translation.getTranslationId().equals("ko_en")) ? "selected" : "" %> value="ko_en"><liferay-ui:message key="ko_en" /></option>
	<option <%= (translation.getTranslationId().equals("pt_en")) ? "selected" : "" %> value="pt_en"><liferay-ui:message key="pt_en" /></option>
	<option <%= (translation.getTranslationId().equals("ru_en")) ? "selected" : "" %> value="ru_en"><liferay-ui:message key="ru_en" /></option>
	<option <%= (translation.getTranslationId().equals("es_en")) ? "selected" : "" %> value="es_en"><liferay-ui:message key="es_en" /></option>
</select>

<input type="submit" value="<liferay-ui:message key="translate" />" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />text);
	</script>
</c:if>