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

<%@ include file="/html/portlet/image_gallery/init.jsp" %>

<script type="text/javascript">
	var <portlet:namespace />imgArray = new Array();

	<%
	IGFolder folder = (IGFolder)request.getAttribute(WebKeys.IMAGE_GALLERY_FOLDER);

	List images = IGImageLocalServiceUtil.getImages(folder.getFolderId());

	for	(int i = 0; i < images.size(); i++) {
		IGImage image = (IGImage)images.get(i);
	%>

		<portlet:namespace />imgArray[<%= i %>] = "<%= themeDisplay.getPathImage() %>/image_gallery?img_id=<%= image.getLargeImageId() %>&t=<%= ImageServletTokenUtil.getToken(image.getLargeImageId()) %>";

	<%
	}

	int defaultSpeed = 3000;
	%>

	var <portlet:namespace />imgArrayPos = 0
	var <portlet:namespace />speed = <%= defaultSpeed %>;
	var <portlet:namespace />timeout = 0;

	function <portlet:namespace />pause() {
		clearInterval(<portlet:namespace />timeout);
		<portlet:namespace />timeout = 0;
	}

	function <portlet:namespace />play() {
		if (<portlet:namespace />timeout == 0) {
			<portlet:namespace />timeout = setInterval("<portlet:namespace />showNext()", <portlet:namespace />speed);
		}
	}

	function <portlet:namespace />showNext() {
		<portlet:namespace />imgArrayPos++;

		if (<portlet:namespace />imgArrayPos == <portlet:namespace />imgArray.length) {
			<portlet:namespace />imgArrayPos = 0;
		}

		document.images.<portlet:namespace />slideShow.src = <portlet:namespace />imgArray[<portlet:namespace />imgArrayPos];
	}

	function <portlet:namespace />showPrevious() {
		<portlet:namespace />imgArrayPos--;

		if (<portlet:namespace />imgArrayPos < 0) {
			<portlet:namespace />imgArrayPos = <portlet:namespace />imgArray.length - 1;
		}

		document.images.<portlet:namespace />slideShow.src = <portlet:namespace />imgArray[<portlet:namespace />imgArrayPos];
	}
</script>

<form>

<table class="lfr-table">
<tr>
	<td>
		<input type="button" value="<liferay-ui:message key="previous" />" onClick="<portlet:namespace />showPrevious();" /> <input type="button" value="<liferay-ui:message key="play" />" onClick="<portlet:namespace />play();" /> <input type="button" value="<liferay-ui:message key="pause" />" onClick="<portlet:namespace />pause();" /> <input type="button" value="<liferay-ui:message key="next" />" onClick="<portlet:namespace />showNext();" />
	</td>
	<td>
		<liferay-ui:message key="speed" />
	</td>
	<td>
		<select onChange="<portlet:namespace />pause(); <portlet:namespace />speed = this[this.selectedIndex].value * 1000; <portlet:namespace />play();">

			<%
			for (int i = 1; i <= 10; i++) {
			%>

				<option <%= (defaultSpeed / 1000) == i ? "selected" : "" %> value="<%= i %>"><%= i %></option>

			<%
			}
			%>

		</select>
	</td>
</tr>
</table>

</form>

<script type="text/javascript">
	<portlet:namespace />play();
</script>

<br />

<table class="lfr-table">
<tr>
	<td>

		<%
		if (images.size() > 0) {
			IGImage image = (IGImage)images.get(0);
		%>

			<img border="0" name="<portlet:namespace />slideShow" src="<%= themeDisplay.getPathImage() %>/image_gallery?img_id=<%= image.getLargeImageId() %>&t=<%= ImageServletTokenUtil.getToken(image.getLargeImageId()) %>" />

		<%
		}
		%>

	</td>
</tr>
</table>