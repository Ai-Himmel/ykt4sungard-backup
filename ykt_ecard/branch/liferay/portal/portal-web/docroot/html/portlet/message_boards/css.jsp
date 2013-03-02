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

<%@ include file="/html/portlet/css_init.jsp" %>

.portlet-message-boards .code {
	background: #fff;
	border: 1px solid #777;
	font-family: monospace;
	white-space: pre;
}

.portlet-message-boards .code-lines {
	border-right: 1px solid #ccc;
	color: #000;
	margin-right: 5px;
	padding: 0px 5px 0px 5px;
}

.portlet-message-boards .quote {
	background: #fff url(<%= themeImagesPath %>/message_boards/quoteleft.png) left top no-repeat;
	border: 1px solid #777;
	padding: 5px 0px 0px 5px;
}

.portlet-message-boards .quote-content {
	background: transparent url(<%= themeImagesPath %>/message_boards/quoteright.png) right bottom no-repeat;
	padding: 5px 30px 10px 30px;
}

.portlet-message-boards .quote-title {
	font-weight: bold;
	padding: 5px 0px 5px 0px;
}

.portlet-message-boards .title {
	border-bottom: 1px solid #ccc;
	font-size: large;
	font-weight: normal;
	padding: 5px;
}

.portlet-message-boards .message-container {
	border: 1px solid #ccc;
	margin: 5px 0 0 0;
}

.ie .portlet-message-boards .message-container {
	width: 100%;
}

.portlet-message-boards .message-container table {
	border-collapse: collapse;
	table-layout: fixed;
}

.portlet-message-boards .message-container td {
	border: none;
}

.portlet-message-boards .thread-top {
	border-bottom: 1px solid #ccc;
	padding: 3px 5px;
}

.portlet-message-boards .thread-bottom {
	padding: 3px 5px;
	text-align: right;
}

td.user-info {
	border-right: 1px solid #ccc;
}

.portlet-message-boards .subject {
	float: left;
}

.portlet-message-boards .edit-controls {
	float: right;
}

.portlet-message-boards .edit-controls li {
	float: left;
	margin-right: 10px;
}

.portlet-message-boards .thread-body {
	padding: 15px;
}

.portlet-message-boards .user-info {
	border: 1px solid #f00;
	padding: 5px;
}

.portlet-message-boards .clear {
	clear: both;
}

.portlet-message-boards .toggle_id_message_boards_view_message_thread {
	border: 1px solid #ccc;
	margin: 5px 0px 0px 0px;
}

.portlet-message-boards .thread-controls {
	border: 1px solid #ccc;
	margin-bottom: 5px;
	padding: 3px 5px;
}

.portlet-message-boards .thread-navigation {
	float: left;
}

.portlet-message-boards .thread-actions {
	float: right;
}

.portlet-message-boards .emoticons {
	border: 1px solid #ccc;
	margin-left: 10px;
}

.portlet-message-boards .tree {
	vertical-align: middle;
}

.portlet-message-boards .message-scroll {
	margin: 5px 0px 0px 0px;
}

.portlet-message-boards .lfr-textarea.message-edit {
	height: 378px;
	min-height: 100%;
	width: 100%;
}