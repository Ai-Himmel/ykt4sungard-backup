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

<%@ include file="/html/portlet/blogs/init.jsp" %>

<form action="<liferay-portlet:actionURL portletConfiguration="true" />" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />

<liferay-ui:message key="set-the-display-styles-used-to-display-blogs-when-viewed-via-as-a-regular-page-or-as-an-rss" />

<fieldset>
	<legend><liferay-ui:message key="page" /></legend>

	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="maximum-items-to-display" />
		</td>
		<td>
			<select name="<portlet:namespace />pageDelta">
				<option <%= (pageDelta == 1) ? "selected" : "" %> value="1">1</option>
				<option <%= (pageDelta == 2) ? "selected" : "" %> value="2">2</option>
				<option <%= (pageDelta == 3) ? "selected" : "" %> value="3">3</option>
				<option <%= (pageDelta == 4) ? "selected" : "" %> value="4">4</option>
				<option <%= (pageDelta == 5) ? "selected" : "" %> value="5">5</option>
				<option <%= (pageDelta == 10) ? "selected" : "" %> value="10">10</option>
				<option <%= (pageDelta == 15) ? "selected" : "" %> value="15">15</option>
				<option <%= (pageDelta == 20) ? "selected" : "" %> value="20">20</option>
				<option <%= (pageDelta == 25) ? "selected" : "" %> value="25">25</option>
				<option <%= (pageDelta == 30) ? "selected" : "" %> value="30">30</option>
				<option <%= (pageDelta == 40) ? "selected" : "" %> value="40">40</option>
				<option <%= (pageDelta == 50) ? "selected" : "" %> value="50">50</option>
				<option <%= (pageDelta == 60) ? "selected" : "" %> value="60">60</option>
				<option <%= (pageDelta == 70) ? "selected" : "" %> value="70">70</option>
				<option <%= (pageDelta == 80) ? "selected" : "" %> value="80">80</option>
				<option <%= (pageDelta == 90) ? "selected" : "" %> value="90">90</option>
				<option <%= (pageDelta == 100) ? "selected" : "" %> value="100">100</option>
			</select>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="display-style" />
		</td>
		<td>
			<select name="<portlet:namespace />pageDisplayStyle">
				<option <%= (pageDisplayStyle.equals(RSSUtil.DISPLAY_STYLE_FULL_CONTENT)) ? "selected" : "" %> value="<%= RSSUtil.DISPLAY_STYLE_FULL_CONTENT %>"><liferay-ui:message key="full-content" /></option>
				<option <%= (pageDisplayStyle.equals(RSSUtil.DISPLAY_STYLE_ABSTRACT)) ? "selected" : "" %> value="<%= RSSUtil.DISPLAY_STYLE_ABSTRACT %>"><liferay-ui:message key="abstract" /></option>
				<option <%= (pageDisplayStyle.equals(RSSUtil.DISPLAY_STYLE_TITLE)) ? "selected" : "" %> value="<%= RSSUtil.DISPLAY_STYLE_TITLE %>"><liferay-ui:message key="title" /></option>
			</select>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="enable-comments" />
		</td>
		<td>
			<liferay-ui:input-checkbox param="enableComments" defaultValue="<%= enableComments %>" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="enable-ratings" />
		</td>
		<td>
			<liferay-ui:input-checkbox param="enableRatings" defaultValue="<%= enableRatings %>" />
		</td>
	</tr>
	</table>
</fieldset>

<fieldset>
	<legend><liferay-ui:message key="rss" /></legend>

	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="maximum-items-to-display" />
		</td>
		<td>
			<select name="<portlet:namespace />rssDelta">
				<option <%= (rssDelta == 1) ? "selected" : "" %> value="1">1</option>
				<option <%= (rssDelta == 2) ? "selected" : "" %> value="2">2</option>
				<option <%= (rssDelta == 3) ? "selected" : "" %> value="3">3</option>
				<option <%= (rssDelta == 4) ? "selected" : "" %> value="4">4</option>
				<option <%= (rssDelta == 5) ? "selected" : "" %> value="5">5</option>
				<option <%= (rssDelta == 10) ? "selected" : "" %> value="10">10</option>
				<option <%= (rssDelta == 15) ? "selected" : "" %> value="15">15</option>
				<option <%= (rssDelta == 20) ? "selected" : "" %> value="20">20</option>
				<option <%= (rssDelta == 25) ? "selected" : "" %> value="25">25</option>
				<option <%= (rssDelta == 30) ? "selected" : "" %> value="30">30</option>
				<option <%= (rssDelta == 40) ? "selected" : "" %> value="40">40</option>
				<option <%= (rssDelta == 50) ? "selected" : "" %> value="50">50</option>
				<option <%= (rssDelta == 60) ? "selected" : "" %> value="60">60</option>
				<option <%= (rssDelta == 70) ? "selected" : "" %> value="70">70</option>
				<option <%= (rssDelta == 80) ? "selected" : "" %> value="80">80</option>
				<option <%= (rssDelta == 90) ? "selected" : "" %> value="90">90</option>
				<option <%= (rssDelta == 100) ? "selected" : "" %> value="100">100</option>
			</select>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="display-style" />
		</td>
		<td>
			<select name="<portlet:namespace />rssDisplayStyle">
				<option <%= (rssDisplayStyle.equals(RSSUtil.DISPLAY_STYLE_FULL_CONTENT)) ? "selected" : "" %> value="<%= RSSUtil.DISPLAY_STYLE_FULL_CONTENT %>"><liferay-ui:message key="full-content" /></option>
				<option <%= (rssDisplayStyle.equals(RSSUtil.DISPLAY_STYLE_ABSTRACT)) ? "selected" : "" %> value="<%= RSSUtil.DISPLAY_STYLE_ABSTRACT %>"><liferay-ui:message key="abstract" /></option>
				<option <%= (rssDisplayStyle.equals(RSSUtil.DISPLAY_STYLE_TITLE)) ? "selected" : "" %> value="<%= RSSUtil.DISPLAY_STYLE_TITLE %>"><liferay-ui:message key="title" /></option>
			</select>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="format" />
		</td>
		<td>
			<select name="<portlet:namespace />rssFormat">
				<option <%= (rssFormat.equals("rss10")) ? "selected" : "" %> value="rss10">RSS 1.0</option>
				<option <%= (rssFormat.equals("rss20")) ? "selected" : "" %> value="rss20">RSS 2.0</option>
				<option <%= (rssFormat.equals("atom10")) ? "selected" : "" %> value="atom10">Atom 1.0</option>
			</select>
		</td>
	</tr>
	</table>
</fieldset>

<br />

<input type="button" value="<liferay-ui:message key="save" />" onClick="submitForm(document.<portlet:namespace />fm);" />

</form>