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

<%@ include file="/html/portlet/maps/init.jsp" %>

<%--
<bean:define id="street" name="mapsMapsForm" property="street" type="java.lang.String" />
<bean:define id="csz" name="mapsMapsForm" property="csz" type="java.lang.String" />
--%>

<%
String street = ParamUtil.getString(request, "street");
String csz = ParamUtil.getString(request, "csz");
%>

<table border="0" cellpadding="0" cellspacing="0">
<tr>
	<td valign="top">
		<html:form action="/maps/view?windowState=maximized" method="post" onsubmit="submitForm(this); return false;">

		<liferay-ui:message key="street-address" /><br />

		<html:text name="mapsMapsForm" property="street" size="30" />

		<br />

		<liferay-ui:message key="city-state-or-zip" /><br />

		<html:text name="mapsMapsForm" property="csz" size="30" />

		<br />

		<select name="<portlet:namespace />country">
			<option value="USA">USA</option>
		</select>

		<br /><br />

		<html:submit><liferay-ui:message key="search" /></html:submit>

		</html:form>
	</td>
	<td style="padding-left: 30px;"></td>
	<td valign="top">
		<c:if test="<%= Validator.isNotNull(street) || Validator.isNotNull(csz) %>">

			<%
			MapsAddress map = null;

			try {
				map = MapsUtil.getMapsAddress(street, csz);
			}
			catch (Exception e) {
			}
			%>

			<c:choose>
				<c:when test="<%= map == null %>">
					<span class="portlet-msg-error"><liferay-ui:message key="a-map-could-not-be-found-for-the-address" /></span>

					<br /><br />

					<b><%= street %>, <%= csz %></b>.
				</c:when>
				<c:otherwise>
					<table border="1" cellpadding="0" cellspacing="0">
					<tr>
						<td>
							<input border="0" height="353" name="mqmap" src="http://mq-mapgend.websys.aol.com:80/?e=9&GetMapDirect=<%= map.getMapDirect() %>" type="image" width="463" />
						</td>
					</tr>
					</table>
				</c:otherwise>
			</c:choose>
		</c:if>
	</td>
</tr>
</table>