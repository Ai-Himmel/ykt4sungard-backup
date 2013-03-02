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

<%@ include file="/html/portlet/unit_converter/init.jsp" %>

<%
int type = ParamUtil.getInteger(request, "type");
int fromId = ParamUtil.getInteger(request, "fromId");
int toId = ParamUtil.getInteger(request, "toId");
double fromValue = ParamUtil.getDouble(request, "fromValue");

Conversion conversion = ConverterUtil.getConversion(type, fromId, toId, fromValue);
%>

<script type="text/javascript">
	var lengthArray = new Array();

	lengthArray[0] = new Option("0", "<liferay-ui:message key="meter" />");
	lengthArray[1] = new Option("1", "<liferay-ui:message key="millimeter" />");
	lengthArray[2] = new Option("2", "<liferay-ui:message key="centimeter" />");
	lengthArray[3] = new Option("3", "<liferay-ui:message key="kilometer" />");
	lengthArray[4] = new Option("4", "<liferay-ui:message key="foot" />");
	lengthArray[5] = new Option("5", "<liferay-ui:message key="inch" />");
	lengthArray[6] = new Option("6", "<liferay-ui:message key="yard" />");
	lengthArray[7] = new Option("7", "<liferay-ui:message key="mile" />");
	lengthArray[8] = new Option("8", "<liferay-ui:message key="cubit" />");
	lengthArray[9] = new Option("9", "<liferay-ui:message key="talent" />");
	lengthArray[10] = new Option("10", "<liferay-ui:message key="handbreath" />");

	var areaArray = new Array();

	areaArray[0] = new Option("0", "<liferay-ui:message key="square-kilometer" />");
	areaArray[1] = new Option("1", "<liferay-ui:message key="square-meter" />");
	areaArray[2] = new Option("2", "<liferay-ui:message key="square-centimeter" />");
	areaArray[3] = new Option("3", "<liferay-ui:message key="square-millimeter" />");
	areaArray[4] = new Option("4", "<liferay-ui:message key="square-foot" />");
	areaArray[5] = new Option("5", "<liferay-ui:message key="square-inch" />");
	areaArray[6] = new Option("6", "<liferay-ui:message key="square-yard" />");
	areaArray[7] = new Option("7", "<liferay-ui:message key="square-mile" />");
	areaArray[8] = new Option("8", "<liferay-ui:message key="hectare" />");
	areaArray[9] = new Option("9", "<liferay-ui:message key="acre" />");

	var volumeArray = new Array();

	volumeArray[0] = new Option("0", "Liter");
	volumeArray[1] = new Option("1", "Cubic Centimeter");
	volumeArray[2] = new Option("2", "Cubic Inch (Liquid Measure)");
	volumeArray[3] = new Option("3", "Pint (Dry Measure)");
	volumeArray[4] = new Option("4", "Cor (Homer)");
	volumeArray[5] = new Option("5", "Lethek");
	volumeArray[6] = new Option("6", "Ephah");
	volumeArray[7] = new Option("7", "Seah");
	volumeArray[8] = new Option("8", "Omer");
	volumeArray[9] = new Option("9", "Cab");
	volumeArray[10] = new Option("10", "Bath");
	volumeArray[11] = new Option("11", "Hin");
	volumeArray[12] = new Option("12", "Log");

	var massArray = new Array();

	massArray[0] = new Option("0", "<liferay-ui:message key="kilogram" />");
	massArray[1] = new Option("1", "<liferay-ui:message key="pound" />");
	massArray[2] = new Option("2", "<liferay-ui:message key="ton" />");
	massArray[3] = new Option("3", "<liferay-ui:message key="talent" />");
	massArray[4] = new Option("4", "<liferay-ui:message key="mina" />");
	massArray[5] = new Option("5", "<liferay-ui:message key="shekel" />");
	massArray[6] = new Option("6", "<liferay-ui:message key="pim" />");
	massArray[7] = new Option("7", "<liferay-ui:message key="beka" />");
	massArray[8] = new Option("8", "<liferay-ui:message key="gerah" />");

	var temperatureArray = new Array();

	temperatureArray[0] = new Option("0", "Kelvin");
	temperatureArray[1] = new Option("1", "Celcius");
	temperatureArray[2] = new Option("2", "Fahrenheit");
	temperatureArray[3] = new Option("3", "Rankine");
	temperatureArray[4] = new Option("4", "Réaumure");
</script>

<form action="<liferay-portlet:renderURL windowState="<%= LiferayWindowState.EXCLUSIVE.toString() %>"><portlet:param name="struts_action" value="/unit_converter/view" /></liferay-portlet:renderURL>" method="post" name="<portlet:namespace />fm" onSubmit="AjaxUtil.submit(this, {update: this.parentNode}); return false;">

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="from" />
	</td>
	<td>
		<input name="<portlet:namespace />fromValue" size="30" type="text" value="<%= conversion.getFromValue() %>" />

		<select name="<portlet:namespace />fromId">
			<c:if test="<%= type == 0 %>">
				<option <%= (fromId == 0) ? "selected" : "" %> value="0"><liferay-ui:message key="meter" /></option>
				<option <%= (fromId == 1) ? "selected" : "" %> value="1"><liferay-ui:message key="millimeter" /></option>
				<option <%= (fromId == 2) ? "selected" : "" %> value="2"><liferay-ui:message key="centimeter" /></option>
				<option <%= (fromId == 3) ? "selected" : "" %> value="3"><liferay-ui:message key="kilometer" /></option>
				<option <%= (fromId == 4) ? "selected" : "" %> value="4"><liferay-ui:message key="foot" /></option>
				<option <%= (fromId == 5) ? "selected" : "" %> value="5"><liferay-ui:message key="inch" /></option>
				<option <%= (fromId == 6) ? "selected" : "" %> value="6"><liferay-ui:message key="yard" /></option>
				<option <%= (fromId == 7) ? "selected" : "" %> value="7"><liferay-ui:message key="mile" /></option>
				<option <%= (fromId == 8) ? "selected" : "" %> value="8"><liferay-ui:message key="cubit" /></option>
				<option <%= (fromId == 9) ? "selected" : "" %> value="9"><liferay-ui:message key="talent" /></option>
				<option <%= (fromId == 10) ? "selected" : "" %> value="10"><liferay-ui:message key="handbreath" /></option>
			</c:if>
			<c:if test="<%= type == 1 %>">
				<option <%= (fromId == 0) ? "selected" : "" %> value="0"><liferay-ui:message key="square-kilometer" /></option>
				<option <%= (fromId == 1) ? "selected" : "" %> value="1"><liferay-ui:message key="square-meter" /></option>
				<option <%= (fromId == 2) ? "selected" : "" %> value="2"><liferay-ui:message key="square-centimeter" /></option>
				<option <%= (fromId == 3) ? "selected" : "" %> value="3"><liferay-ui:message key="square-millimeter" /></option>
				<option <%= (fromId == 4) ? "selected" : "" %> value="4"><liferay-ui:message key="square-foot" /></option>
				<option <%= (fromId == 5) ? "selected" : "" %> value="5"><liferay-ui:message key="square-inch" /></option>
				<option <%= (fromId == 6) ? "selected" : "" %> value="6"><liferay-ui:message key="square-yard" /></option>
				<option <%= (fromId == 7) ? "selected" : "" %> value="7"><liferay-ui:message key="square-mile" /></option>
				<option <%= (fromId == 8) ? "selected" : "" %> value="8"><liferay-ui:message key="hectare" /></option>
				<option <%= (fromId == 9) ? "selected" : "" %> value="9"><liferay-ui:message key="acre" /></option>
			</c:if>
			<c:if test="<%= type == 2 %>">
				<option <%= (fromId == 0) ? "selected" : "" %> value="0">Liter</option>
				<option <%= (fromId == 1) ? "selected" : "" %> value="1">Cubic Centimeter</option>
				<option <%= (fromId == 2) ? "selected" : "" %> value="2">Cubic Inch (Liquid Measure)</option>
				<option <%= (fromId == 3) ? "selected" : "" %> value="3">Pint (Dry Measure)</option>
				<option <%= (fromId == 4) ? "selected" : "" %> value="4">Cor (Homer)</option>
				<option <%= (fromId == 5) ? "selected" : "" %> value="5">Lethek</option>
				<option <%= (fromId == 6) ? "selected" : "" %> value="6">Ephah</option>
				<option <%= (fromId == 7) ? "selected" : "" %> value="7">Seah</option>
				<option <%= (fromId == 8) ? "selected" : "" %> value="8">Omer</option>
				<option <%= (fromId == 9) ? "selected" : "" %> value="9">Cab</option>
				<option <%= (fromId == 10) ? "selected" : "" %> value="10">Bath</option>
				<option <%= (fromId == 11) ? "selected" : "" %> value="11">Hin</option>
				<option <%= (fromId == 12) ? "selected" : "" %> value="12">Log</option>
			</c:if>
			<c:if test="<%= type == 3 %>">
				<option <%= (fromId == 0) ? "selected" : "" %> value="0"><liferay-ui:message key="kilogram" /></option>
				<option <%= (fromId == 1) ? "selected" : "" %> value="1"><liferay-ui:message key="pound" /></option>
				<option <%= (fromId == 2) ? "selected" : "" %> value="2"><liferay-ui:message key="ton" /></option>
				<option <%= (fromId == 3) ? "selected" : "" %> value="3"><liferay-ui:message key="talent" /></option>
				<option <%= (fromId == 4) ? "selected" : "" %> value="4"><liferay-ui:message key="mina" /></option>
				<option <%= (fromId == 5) ? "selected" : "" %> value="5"><liferay-ui:message key="shekel" /></option>
				<option <%= (fromId == 6) ? "selected" : "" %> value="6"><liferay-ui:message key="pim" /></option>
				<option <%= (fromId == 7) ? "selected" : "" %> value="7"><liferay-ui:message key="beka" /></option>
				<option <%= (fromId == 8) ? "selected" : "" %> value="8"><liferay-ui:message key="gerah" /></option>
			</c:if>
			<c:if test="<%= type == 4 %>">
				<option <%= (fromId == 0) ? "selected" : "" %> value="0">Kelvin</option>
				<option <%= (fromId == 1) ? "selected" : "" %> value="1">Celcius</option>
				<option <%= (fromId == 2) ? "selected" : "" %> value="2">Fahrenheit</option>
				<option <%= (fromId == 3) ? "selected" : "" %> value="3">Rankine</option>
				<option <%= (fromId == 4) ? "selected" : "" %> value="4">Réaumure</option>
			</c:if>
		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="to" />
	</td>
	<td>
		<input name="<portlet:namespace />to_value" size="30" type="text" value="<%= conversion.getToValue() %>" />

		<select name="<portlet:namespace />toId">
			<c:if test="<%= type == 0 %>">
				<option <%= (toId == 0) ? "selected" : "" %> value="0"><liferay-ui:message key="meter" /></option>
				<option <%= (toId == 1) ? "selected" : "" %> value="1"><liferay-ui:message key="millimeter" /></option>
				<option <%= (toId == 2) ? "selected" : "" %> value="2"><liferay-ui:message key="centimeter" /></option>
				<option <%= (toId == 3) ? "selected" : "" %> value="3"><liferay-ui:message key="kilometer" /></option>
				<option <%= (toId == 4) ? "selected" : "" %> value="4"><liferay-ui:message key="foot" /></option>
				<option <%= (toId == 5) ? "selected" : "" %> value="5"><liferay-ui:message key="inch" /></option>
				<option <%= (toId == 6) ? "selected" : "" %> value="6"><liferay-ui:message key="yard" /></option>
				<option <%= (toId == 7) ? "selected" : "" %> value="7"><liferay-ui:message key="mile" /></option>
				<option <%= (toId == 8) ? "selected" : "" %> value="8"><liferay-ui:message key="cubit" /></option>
				<option <%= (toId == 9) ? "selected" : "" %> value="9"><liferay-ui:message key="talent" /></option>
				<option <%= (toId == 10) ? "selected" : "" %> value="10"><liferay-ui:message key="handbreath" /></option>
			</c:if>
			<c:if test="<%= type == 1 %>">
				<option <%= (toId == 0) ? "selected" : "" %> value="0"><liferay-ui:message key="square-kilometer" /></option>
				<option <%= (toId == 1) ? "selected" : "" %> value="1"><liferay-ui:message key="square-meter" /></option>
				<option <%= (toId == 2) ? "selected" : "" %> value="2"><liferay-ui:message key="square-centimeter" /></option>
				<option <%= (toId == 3) ? "selected" : "" %> value="3"><liferay-ui:message key="square-millimeter" /></option>
				<option <%= (toId == 4) ? "selected" : "" %> value="4"><liferay-ui:message key="square-foot" /></option>
				<option <%= (toId == 5) ? "selected" : "" %> value="5"><liferay-ui:message key="square-inch" /></option>
				<option <%= (toId == 6) ? "selected" : "" %> value="6"><liferay-ui:message key="square-yard" /></option>
				<option <%= (toId == 7) ? "selected" : "" %> value="7"><liferay-ui:message key="square-mile" /></option>
				<option <%= (toId == 8) ? "selected" : "" %> value="8"><liferay-ui:message key="hectare" /></option>
				<option <%= (toId == 9) ? "selected" : "" %> value="9"><liferay-ui:message key="acre" /></option>
			</c:if>
			<c:if test="<%= type == 2 %>">
				<option <%= (toId == 0) ? "selected" : "" %> value="0">Liter</option>
				<option <%= (toId == 1) ? "selected" : "" %> value="1">Cubic Centimeter</option>
				<option <%= (toId == 2) ? "selected" : "" %> value="2">Cubic Inch (Liquid Measure)</option>
				<option <%= (toId == 3) ? "selected" : "" %> value="3">Pint (Dry Measure)</option>
				<option <%= (toId == 4) ? "selected" : "" %> value="4">Cor (Homer)</option>
				<option <%= (toId == 5) ? "selected" : "" %> value="5">Lethek</option>
				<option <%= (toId == 6) ? "selected" : "" %> value="6">Ephah</option>
				<option <%= (toId == 7) ? "selected" : "" %> value="7">Seah</option>
				<option <%= (toId == 8) ? "selected" : "" %> value="8">Omer</option>
				<option <%= (toId == 9) ? "selected" : "" %> value="9">Cab</option>
				<option <%= (toId == 10) ? "selected" : "" %> value="10">Bath</option>
				<option <%= (toId == 11) ? "selected" : "" %> value="11">Hin</option>
				<option <%= (toId == 12) ? "selected" : "" %> value="12">Log</option>
			</c:if>
			<c:if test="<%= type == 3 %>">
				<option <%= (toId == 0) ? "selected" : "" %> value="0"><liferay-ui:message key="kilogram" /></option>
				<option <%= (toId == 1) ? "selected" : "" %> value="1"><liferay-ui:message key="pound" /></option>
				<option <%= (toId == 2) ? "selected" : "" %> value="2"><liferay-ui:message key="ton" /></option>
				<option <%= (toId == 3) ? "selected" : "" %> value="3"><liferay-ui:message key="talent" /></option>
				<option <%= (toId == 4) ? "selected" : "" %> value="4"><liferay-ui:message key="mina" /></option>
				<option <%= (toId == 5) ? "selected" : "" %> value="5"><liferay-ui:message key="shekel" /></option>
				<option <%= (toId == 6) ? "selected" : "" %> value="6"><liferay-ui:message key="pim" /></option>
				<option <%= (toId == 7) ? "selected" : "" %> value="7"><liferay-ui:message key="beka" /></option>
				<option <%= (toId == 8) ? "selected" : "" %> value="8"><liferay-ui:message key="gerah" /></option>
			</c:if>
			<c:if test="<%= type == 4 %>">
				<option <%= (toId == 0) ? "selected" : "" %> value="0">Kelvin</option>
				<option <%= (toId == 1) ? "selected" : "" %> value="1">Celcius</option>
				<option <%= (toId == 2) ? "selected" : "" %> value="2">Fahrenheit</option>
				<option <%= (toId == 3) ? "selected" : "" %> value="3">Rankine</option>
				<option <%= (toId == 4) ? "selected" : "" %> value="4">Réaumure</option>
			</c:if>
		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="type" />
	</td>
	<td>
		<select name="<portlet:namespace />type"
			onChange="
				if (this[this.selectedIndex].value == 0) {
					Liferay.Util.setBox(document.<portlet:namespace />fm.<portlet:namespace />fromId, lengthArray);
					Liferay.Util.setBox(document.<portlet:namespace />fm.<portlet:namespace />toId, lengthArray);
				}
				else if (this[this.selectedIndex].value == 1) {
					Liferay.Util.setBox(document.<portlet:namespace />fm.<portlet:namespace />fromId, areaArray);
					Liferay.Util.setBox(document.<portlet:namespace />fm.<portlet:namespace />toId, areaArray);
				}
				else if (this[this.selectedIndex].value == 2) {
					Liferay.Util.setBox(document.<portlet:namespace />fm.<portlet:namespace />fromId, volumeArray);
					Liferay.Util.setBox(document.<portlet:namespace />fm.<portlet:namespace />toId, volumeArray);
				}
				else if (this[this.selectedIndex].value == 3) {
					Liferay.Util.setBox(document.<portlet:namespace />fm.<portlet:namespace />fromId, massArray);
					Liferay.Util.setBox(document.<portlet:namespace />fm.<portlet:namespace />toId, massArray);
				}
				else if (this[this.selectedIndex].value == 4) {
					Liferay.Util.setBox(document.<portlet:namespace />fm.<portlet:namespace />fromId, temperatureArray);
					Liferay.Util.setBox(document.<portlet:namespace />fm.<portlet:namespace />toId, temperatureArray);
				}"
		>
			<option <%= (type == 0) ? "selected" : "" %> value="0"><liferay-ui:message key="length" /></option>
			<option <%= (type == 1) ? "selected" : "" %> value="1"><liferay-ui:message key="area" /></option>
			<option <%= (type == 2) ? "selected" : "" %> value="2"><liferay-ui:message key="volume" /></option>
			<option <%= (type == 3) ? "selected" : "" %> value="3"><liferay-ui:message key="mass" /></option>
			<option <%= (type == 4) ? "selected" : "" %> value="4"><liferay-ui:message key="temperature" /></option>
		</select>
	</td>
</tr>
</table>

<br />

<input type="submit" value="<liferay-ui:message key="convert" />" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />fromValue);
	</script>
</c:if>