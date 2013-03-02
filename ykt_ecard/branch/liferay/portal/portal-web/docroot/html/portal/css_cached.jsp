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

<%@ include file="/html/portal/init.jsp" %>

<%
response.setContentType(ContentTypes.TEXT_CSS);
%>

<%@ include file="/html/portal/css_cached_uniform.jsp" %>

/* ---------- Modules ---------- */

/* ---------- Generic module styling ---------- */

.lfr-grid {
	width: 100%;
}

.lfr-component, .lfr-component ul, .lfr-component li {
	margin: 0;
	padding: 0;
	list-style: none;
}

/* ---------- Add content styles ---------- */

.portal-add-content-search {
	margin-bottom: 8px;
}

.portal-add-content .lfr-portlet-used {
	color: #ccc;
	cursor: default;
}

.portal-add-content .portlet-msg-info {
	color: #333;
	margin-bottom: 0;
}

.portal-add-content .lfr-portlet-used a {
	display: none;
}

.lfr-add-content {
	margin-bottom: 0.5em;
}

.lfr-add-content.collapsed {
}

.lfr-add-content.expanded {
}

.lfr-add-content h2 {
	cursor: pointer;
	font-size: 1.1em;
	font-weight: bold;
	margin: 0;
}

.lfr-add-content.collapsed h2, .lfr-add-content .lfr-add-content.collapsed h2 {
	background: url(<%= themeDisplay.getPathThemeImages() %>/arrows/01_plus.png) no-repeat 100% 50%;
	border: none;
}

.lfr-add-content.expanded h2, .lfr-add-content .lfr-add-content.expanded h2 {
	background: url(<%= themeDisplay.getPathThemeImages() %>/arrows/01_minus.png) no-repeat 100% 50%;
}
.lfr-add-content h2 span {
	background: url(<%= themeDisplay.getPathThemeImages() %>/add_content/portlet_category.png) no-repeat 0 50%;
	padding-left: 20px;
}
.lfr-content-category {
	padding-left: 10px;
	padding-top: 3px;
}
.lfr-content-category.hidden {
	display: none;
}
.lfr-content-category.visible {
	border-bottom: 1px solid #ddd;
	border-top: 1px solid #ddd;
	display: block;
}

.ie6 .lfr-content-category.visible {
	height: 1%;
}

.lfr-portlet-item {
	background: url(<%= themeDisplay.getPathThemeImages() %>/add_content/portlet_item.png) no-repeat 0 50%;
	border: 1px solid #fff;
	cursor: move;
	font-size: 1.1em;
	margin-bottom: 3px;
	padding: 0 5px 0 20px;
}

.lfr-portlet-item.lfr-instanceable {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/add_content/portlet_item_instanceable.png);
}

.lfr-portlet-item:hover, .lfr-portlet-item.over {
	background-color: #ffc;
	border-color: #fc0;
}

.ie .lfr-portlet-item {
	height: 1%;
}

.lfr-portlet-item p {
	font-size: 1em;
	margin: 0;
	padding-right: 30px;
	position: relative;
}

.lfr-portlet-item p a {
	cursor: pointer;
	font-size: 0.9em;
	font-weight: bold;
	position: absolute;
	right: 0;
	top: 0;
}

.ie .lfr-portlet-item p a {
	top: -2px;
}

.ie6 .lfr-portlet-item p a {
	right: 20px;
}

#layout_configuration_content {
	width: 95%;
}

/* ---------- Color picker ---------- */

.lfr-color-picker {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/color_picker/picker_container_bg.png);
	font: 11px Arial,Helvetica,sans-serif;
	height: 192px;
	position: relative;
	width: 305px;
}

.lfr-color {
	background-color: #F00;
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/color_picker/picker_bg.png);
	background-position: center;
	background-repeat: no-repeat;
	height: 184px;
	left: 8px;
	position: absolute;
	top: 5px;
	width: 184px;
}

.lfr-color-indic {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/color_picker/select.png);
	height: 11px;
	position: absolute;
	width: 11px;
}

.lfr-hue {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/color_picker/hue.png);
	height: 186px;
	left: 200px;
	position: absolute;
	top: 3px;
	width: 18px;
}

.lfr-hue-indic {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/color_picker/color_indic.png);
	height: 7px;
	position: absolute;
	width: 18px;
}

.lfr-current-color {
	border: 2px solid #999;
	height: 60px;
	position: absolute;
	right: 10px;
	top: 38px;
	width: 60px;
}

.lfr-color-values {
	left: 240px;
	position: absolute;
	top: 80px;
}

.lfr-color-values input {
	font-size: 11px;
	padding: 1px;
}

.lfr-old-color {
	background-color: #fff;
	height: 50%;
	position: absolute;
	top: 50%;
	width: 100%;
}

.lfr-rgbR, .lfr-rgbG, .lfr-rgbB {
	width: 20px;
}

.lfr-hex {
	width: 40px;
}

.lfr-color-picker-close {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/color_picker/close.png);
	cursor: pointer;
	height: 30px;
	position: absolute;
	right: 5px;
	text-indent: -9999em;
	top: 0;
	width: 30px;
}

/* ---------- Interactive Dock ---------- */

.js .lfr-dock.interactive-mode {
	float: right;
	min-width: 150px;
	position: relative;
	right: 10px;
	top: 10px;
}

.js .lfr-dock.interactive-mode h2 {
	background: url(<%= themeDisplay.getPathThemeImages() %>/dock/menu_bar.png) no-repeat 100% -30px;
	font-size: 1.2em;
	margin-bottom: 0;
	padding: 0 29px 0 0;
	position: relative;
	z-index: 82;
}

.js .lfr-dock.interactive-mode h2 span {
	background: url(<%= themeDisplay.getPathThemeImages() %>/dock/menu_bar.png) no-repeat 0 0;
	display: block;
	font-size: 1.2em;
	margin-bottom: 0;
	min-height: 16px;
	min-width: 90px;
	padding: 0.5em 0.5em 0.5em 2em;
}

.js.ie6 .lfr-dock.interactive-mode h2 span {
	height: 16px;
}

.js .lfr-dock.expanded .lfr-dock-list-container {
	border-top: none;
	top: -2px;
}

.js .lfr-dock.interactive-mode ul {
	background: url(<%= themeDisplay.getPathThemeImages() %>/dock/menu_bg.png) no-repeat 0 0;
	display: none;
	float: none;
}

.js .lfr-dock.interactive-mode li {
	display: block;
	float: none;
	margin-bottom: 0pt;
	margin-left: 0.2em;
}

.js .lfr-dock.interactive-mode li a {
	background-position: 0.5em 50%;
	background-repeat: no-repeat;
	border-top: 1px solid #ccc;
	display: block;
	margin-left: 0.3em;
	padding: 0.5em 0pt 0.5em 2.5em;
	text-decoration: none;
}

.js .lfr-dock.interactive-mode ul.lfr-dock-list > li:first-child a, .js .lfr-dock.interactive-mode ul.lfr-dock-list > li:first-child ul.show-my-places li:first-child a {
	border-top: none;
}

.js .lfr-dock.interactive-mode li a:hover {
	background-position: 1.5em 50%;
	padding-left: 3.5em;
}

.js .lfr-dock.interactive-mode ul.lfr-dock-list > li:first-child a, .js .lfr-dock.interactive-mode ul.lfr-dock-list > li:first-child a:hover, .js .lfr-dock.interactive-mode ul.lfr-dock-list li.my-places ul.show-my-places li ul li:first-child a, .js .lfr-dock.interactive-mode ul.lfr-dock-list li.my-places ul.show-my-places li ul li:first-child a:hover {
	border-top: none;
}

.js .my-places {
	display: none;
}

.js .lfr-dock.interactive-mode li.my-places li a {
	background-image: none;
}

.js .lfr-dock.interactive-mode li.my-places li ul li.current a, .js .lfr-dock.interactive-mode li.my-places li ul li.current a:hover {
	background: transparent url(<%= themeDisplay.getPathThemeImages() %>/dock/my_place_current.png) no-repeat 1em 50%;
	margin: 0.1em 0 0 0.2em;
	padding-left: 3.5em;
}

.js .interactive-mode .my-places .show-my-places {
	display: block;
	min-width: 200px;
	padding: 0.2em;
	position: absolute;
	right: 85%;
	top: 87%;
}

.js .interactive-mode .my-places.send-right .show-my-places {
	left: 100%;
	top: -10px;
}

.js .interactive-mode .my-places.send-down .show-my-places {
	left: 0;
	top: 100%;
}

.js .interactive-mode .my-places .show-my-places li {
	background: url() no-repeat 5px 50%;
	margin: 0;
}

.js .interactive-mode .my-places .show-my-places li .my-places-toggle {
	background: url(<%= themeDisplay.getPathThemeImages() %>/dock/my_place.png) no-repeat 3px 50%;
	font-size: 1.1em;
	font-weight: bold;
	padding: 0.5em 0.2em 0.5em 2em;
}

.js .interactive-mode .my-places .show-my-places li .my-places-toggle h3 {
	background: url(<%= themeDisplay.getPathThemeImages() %>/dock/expand_community.png) no-repeat 100% 50%;
	font-size: 1em;
	margin: 0;
	padding-right: 1.8em;
}

.js .interactive-mode .my-places .show-my-places li .my-places-toggle.hide h3 {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/dock/collapse_community.png);
}

.js .interactive-mode .my-places .show-my-places li ul {
	background: none no-repeat 3px 50%;
	border: none;
	display: none;
}

.js .interactive-mode .my-places .show-my-places li ul {
	margin-left: 0.5em;
}

.js .interactive-mode .my-places .show-my-places li ul li {
	position: relative;
}

.js .interactive-mode .my-places .show-my-places ul li.public a, .js .my-places .show-my-places ul li.public a:hover {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/dock/my_places_public.png);
}

.js .interactive-mode .my-places .show-my-places li.private a, .js .my-places .show-my-places li.private a:hover {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/dock/my_places_private.png);
}

.js .interactive-mode .my-places .show-my-places ul li.public a.add-page, .js .interactive-mode .my-places .show-my-places ul li.private a.add-page {
	background: url(<%= themeDisplay.getPathThemeImages() %>/dock/page_settings.png) no-repeat;
	border: none;
	display: block;
	font-size: 0;
	height: 16px;
	padding: 0;
	position: absolute;
	right: 3px;
	text-indent: -9999em;
	top: 3px;
	width: 16px;
}

.js .interactive-mode .my-places .show-my-places ul li.public a.add-page:hover, .js .interactive-mode .my-places .show-my-places ul li.private a.add-page:hover {
	background: url(<%= themeDisplay.getPathThemeImages() %>/dock/page_settings.png) no-repeat;
	padding: 0;
}

.ie6.js .lfr-dock.interactive-mode {
	white-space: nowrap;
	width: 150px;
}

.ie.js .lfr-dock .my-places .show-my-places h3 {
	font-size: 1.1em;
}

.ie6.js .lfr-dock.expanded.interactive-mode .lfr-dock-list-container {
	height: 1%;
}

.ie6.js .interactive-mode .my-places .show-my-places {
	width: 200px;
}

.ie6.js .lfr-dock.interactive-mode li {
	height: 1%;
}

.ie6.js .lfr-dock.interactive-mode li a {
	height: 1%;
}

/* ---------- Portlet css editor ---------- */

#portlet-set-properties {
	display: none;
}

#portlet-set-properties .uni-form {
	clear: both;
}

#portlet-set-properties fieldset {
	margin-bottom: 1em;
}

#portlet-set-properties fieldset fieldset {
	margin-top: 1em;
}

#portlet-set-properties fieldset fieldset legend {
	font-size: 1.1em;
}

#portlet-set-properties .uni-form .text-input {
	margin-right: 5px;
	width: 80px;
}

#portlet-set-properties .uni-form fieldset.col {
	width: 29%;
}

#portlet-set-properties .common {
	width: 27%;
}

#portlet-set-properties .extra {
	width: 20%;
}

#portlet-set-properties #lfr-border-width, #portlet-set-properties #lfr-border-style, #portlet-set-properties #lfr-border-color {
	float: left;
}

#portlet-set-properties #lfr-border-width {
	width: 25%;
}

#portlet-set-properties #lfr-border-style {
	width: 15%;
}

#portlet-set-properties #lfr-border-color {
	width: 20%;
}

#portlet-set-properties #lfr-padding, #portlet-set-properties #lfr-margin {
	width: 25%;
}

#portlet-set-properties .uni-form #custom-css {
	height: 300px;
	width: 400px;
}

#portlet-set-properties .form-hint {
	float: none;
}

#portlet-set-properties .lfr-bg-image-properties {
	display: none;
}

#portlet-set-properties #border-note {
	display: none;
	margin-top: 10px;
}

#portlet-set-properties .uni-form {
	clear: both;
}

/* ---------- Tree ---------- */

ul.gamma {
}

ul.gamma .expand-image {
}

ul.gamma a {
	text-decoration: none;
}

ul.gamma li {
	margin-bottom: 2px;
	padding-left: 0;
}

ul.gamma li ul {
}

ul.gamma li ul li, ul.gamma li.tree-item {
	padding-left: 0;
}

ul.gamma img {
	vertical-align: middle;
}

ul.gamma li.tree-item {
	padding-left: 5px;
}

ul.gamma li.tree-item a img {
	cursor: move;
}

ul.gamma li.tree-item li {
	padding-left: 20px;
}

ul.gamma li.tree-item ul {
	margin-left: 0;
	margin-top: 5px;
}

ul.gamma li.tree-item a, ul.gamma li.tree-item .expand-image {
	cursor: pointer;
}

ul.gamma .tree-item-hover {
	background: #7D93C1;
	padding: 5px;
}

li.toggle-expand {
	padding-bottom: 10px;
}

li.toggle-expand a {
	padding: 2px 0 2px 20px;
}

#lfr-expand {
	background: url(<%= themeDisplay.getPathThemeImages() %>/trees/expand_all.png) no-repeat 0 50%;
}

#lfr-collapse {
	background: url(<%= themeDisplay.getPathThemeImages() %>/trees/collapse_all.png) no-repeat 0 50%;
}

/* ---------- Uploader ---------- */

.lfr-upload-container {
	margin-bottom: 1em;
	width: 450px;
}

.lfr-upload-container .upload-target a {
	float: left;
	margin-right: 15px;
}

.lfr-upload-container a.browse-button {
	background-image: url(<%=themeDisplay.getPathThemeImages()%>/dock/add_content.png);
	background-repeat: no-repeat;
}

.lfr-upload-container a.upload-button {
	background-image: url(<%=themeDisplay.getPathThemeImages()%>/common/top.png);
	background-repeat: no-repeat;
}

.lfr-upload-container a.clear-uploads {
	background-image: url(<%=themeDisplay.getPathThemeImages()%>/portlet/refresh.png);
	background-repeat: no-repeat;
}

.lfr-upload-container a.cancel-uploads {
	background-image: url(<%=themeDisplay.getPathThemeImages()%>/common/close.png);
	background-repeat: no-repeat;
	float: right;
	margin-right: 0;
}

.lfr-upload-container .upload-file {
	background: #f0faf0 url(<%=themeDisplay.getPathThemeImages()%>/document_library/jpg.png) no-repeat 5px 50%;
	border-bottom: 1px solid #ccc;
	display: block;
	font-weight: bold;
	margin-bottom: 1px;
	padding: 5px;
	padding-left: 25px;
	position: relative;
}

.lfr-upload-container .upload-list-info {
	margin: 5px 0;
}

.lfr-upload-container .upload-list-info h4 {
	font-size: 1.3em;
}

.lfr-upload-container .cancel-button {
	background-image: url(<%=themeDisplay.getPathThemeImages()%>/common/delete.png);
	background-repeat: no-repeat;
	position: absolute;
	right: 5px;
}

.lfr-upload-container .upload-complete {
	background-color: #E8EEF7;
	background-image: url(<%=themeDisplay.getPathThemeImages()%>/dock/my_place_current.png);
	font-weight: normal;
	opacity: 0.6;
}

.lfr-upload-container .upload-complete .cancel-button {
	display: none;
}

.lfr-upload-container .file-uploading {
	background-color: #ffc;
}

.lfr-upload-container .file-uploading .cancel-button {
	top: 0;
}

.lfr-upload-container .progress-bar {
	background: #fff;
	border: 1px solid #83a8d9;
	display: none;
	height: 15px;
}

.lfr-upload-container .progress {
	background: #8db2e3 url(<%=themeDisplay.getPathThemeImages()%>/progress_bar/complete_gradient.png) repeat-y 100% 0;
	display: block;
	height: 15px;
	width: 0;
}

.lfr-upload-container .file-uploading .progress-bar {
	display: block;
}

/* ---------- Portal ---------- */

/* ---------- Portal login ---------- */

.lfr-portal-login {
}

.lfr-portal-login:after {
	clear: both;
	content: ".";
	display: block;
	height: 0;
	visibility: hidden;
}

.ie .lfr-portal-login {
	height: 1%;
}

.lfr-portal-login form {
	float: left;
	margin-right: 10px;
	width: 300px;
}

.lfr-portal-login fieldset {
	padding-top: 0;
}

.lfr-portal-login .lfr-input-text {
	width: 150px;
}

.lfr-portal-login .uni-form legend {
	padding-top: 0;
}

/* ---------- Portal notifications styling ---------- */

.popup-alert-notice .notice-date {
	margin: 0 10px;
}

/* ---------- Tag selector styling ---------- */

.lfr-tag-select-container {
	height: 300px;
	position: relative;
	width: 400px;
}

.lfr-tag-container {
	height: 260px;
	overflow: auto;
	width: 395px;
}

.lfr-tag-container label {
	cursor: pointer;
	display: block;
	float: left;
	margin-bottom: 5px;
	margin-right: 5px;
	overflow: hidden;
	white-space: pre;
	width: 25%;
}

.lfr-tag-container label input {
	margin-right: 5px;
}

.lfr-tag-select-container .save-button {
	bottom: 0;
	left: 0;
	position: absolute;
}

/* ---------- Generic styling ---------- */

.popup-alert-notice, .popup-alert-warning {
	background: #ffc url() no-repeat 5px 50%;
	border-bottom: 1px solid;
	font-size: 1.1em;
	left: 0;
	padding: 10px;
	padding-left: 25px;
	position: fixed;
	top: 0;
	width: 100%;
	z-index: 10000;
}

.popup-alert-notice {
	background-color: #ffc;
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/messages/alert.png);
	border-bottom-color: #fc0;
}

.popup-alert-warning {
	background-color: #fcc;
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/messages/error.png);
	border-bottom-color: #f00;
	font-weight: bold;
}

.ie6 .popup-alert-notice, .ie6 .popup-alert-warning {
	bottom: auto;
	left: expression( ( LFR_IGNORE_ME2 = document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft ) + 'px' );
	position: absolute;
	right: auto;
	top: expression( ( LFR_IGNORE_ME = document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop ) + 'px' );
}

.popup-alert-notice .countdown-timer {
	font-size: 1.1em;
	font-weight: bold;
}

.popup-alert-notice input, .popup-alert-warning input {
	vertical-align: middle;
}

/* ---------- Portlets ---------- */

/* ---------- Generic styling ---------- */

.breadcrumbs {
	margin-bottom: 10px;
	margin-left: 0px;
}

.js .lfr-fallback {
	display: none;
}

.lfr-button {
	background: url() no-repeat 0 50%;
	padding: 2px 0 2px 20px;
}

.float-container:after {
	clear: both;
	content: ".";
	display: block;
	height: 0;
	visibility: hidden;
}

.ie .float-container {
	height: 1%;
}

.lfr-table {
	border-collapse: collapse;
	clear: both;
}

.lfr-table tr td, .lfr-table tr th {
	padding: 0 5px;
}

.lfr-table tr th {
	font-weight: bold;
}

.lfr-table tr td:first-child, .lfr-table tr td.first-child, .lfr-table tr th:first-child, .lfr-table tr th.first-child {
	padding-left: 0;
}

.lfr-table tr td:last-child, .lfr-table tr td.last-child, .lfr-table tr th:last-child, .lfr-table tr th.last-child {
	padding-right: 0;
}

.lfr-control-links a {
	margin-right: 1em;
}

.portlet-toolbar {
	margin-bottom: 1.5em;
}

/* ---------- Liferay forms ---------- */

.lfr-input-text {
	width: <%= ModelHintsDefaults.TEXT_DISPLAY_WIDTH %>px;
}

.lfr-textarea {
	height: <%= ModelHintsDefaults.TEXTAREA_DISPLAY_HEIGHT %>px;
	width: <%= ModelHintsDefaults.TEXTAREA_DISPLAY_WIDTH %>px;
}

/* ---------- Separator ---------- */

.separator {
	margin: 15px auto;
}

/* ---------- Taglib action bar ---------- */

.lfr-actions {
	float: right;
	text-align: left;
}

.lfr-actions.left {
	float: left;
}

.lfr-actions.right {
}

.lfr-actions.visible {
	position: relative;
}

.lfr-actions ul {
	display: none;
	bottom: 0%;
	position: absolute;
	right: 100%;
	z-index: 99999;
}

.lfr-actions.visible ul {
	display: block;
}

.lfr-actions.left ul {
	right: auto;
	left: 100%;
}

.lfr-actions .lfr-trigger, .lfr-actions .lfr-trigger strong {
	background: url(<%= themeDisplay.getPathThemeImages() %>/common/button_bg.png) no-repeat;
	font-weight: normal;
}

.lfr-actions .lfr-trigger {
	background-position: 100% -42px;
	cursor: pointer;
	padding-right: 3px;
}

.ie6 .lfr-actions {
	height: 15px;
}

.lfr-actions .lfr-trigger strong {
	display: block;
	min-width: 70px;
	padding: 2px 0 3px;
	text-align: center;
}

.ie6 .lfr-actions .lfr-trigger strong {
	display: inline-block;
}

.lfr-actions.visible .lfr-trigger {
	background-position: 100% 100%;
}

.lfr-actions.visible .lfr-trigger strong {
	background-position: 0 -21px;
}

.lfr-actions .lfr-trigger strong span {
	background: url(<%= themeDisplay.getPathThemeImages() %>/common/action.png) no-repeat 5px 0;
	padding: 2px 10px 2px 35px;
}

.lfr-actions.left .lfr-trigger strong span {
	background-position: 98% 100%;
	padding: 2px 35px 2px 10px;
}

.lfr-actions .lfr-trigger li {
	background: #fff;
	border-bottom: 1px solid #99b6db;
	padding: 5px;
}

.lfr-actions .lfr-trigger li.last {
	border-bottom: none;
}

.lfr-actions .lfr-trigger li a {
	display: block;
	font-weight: normal;
	position: relative;
	padding-left: 20px;
	text-decoration: none;
}

.lfr-actions .lfr-trigger li a img {
	position: absolute;
	left: 0;
}

.ie6 .lfr-actions .lfr-trigger li a img {
	left: -20px;
}

/* ---------- Taglib discussion thread ---------- */

.taglib-discussion td img {
	vertical-align: middle;
}

/* ---------- Taglib diff thread ---------- */

.taglib-diff-addedline, #taglib-diff-results ins {
	background: #E6FFE6;
}

.taglib-diff-context {
	background: #EEEEEE;
}

.taglib-diff-deletedline, #taglib-diff-results del {
	background: #FFE6E6;
}

.taglib-diff-table {
	border-collapse: separate;
	border-spacing: 5pt;
	width: 100%;
}

/* ---------- Taglib search iterator ---------- */

.taglib-search-iterator {
	border-collapse: collapse;
	width: 100%;
}

.taglib-search-iterator td {
	padding: 4px;
}

.taglib-search-iterator-highlighted {
	font-weight: bold;
}

.taglib-search-iterator-page-iterator-top {
	padding-bottom: 5px;
}

.taglib-search-iterator-page-iterator-bottom {
	padding-top: 5px;
}

.taglib-page-iterator {
	clear: both;
	height: auto;
	overflow: auto;
	width: auto;
}

.taglib-page-iterator .search-results {
	float: left;
}

.taglib-page-iterator .search-pages {
	float: right;
}

.taglib-page-iterator .search-pages .page-links a, .taglib-page-iterator .search-pages .page-links span {
	background: url() no-repeat 0 0;
	border-left: 1px solid #ccc;
	padding: 2px 15px;
}

.taglib-page-iterator .search-pages .page-links span {
	background-position: 0 100%;
}

.taglib-page-iterator .search-pages .page-links a.first, .taglib-page-iterator .search-pages .page-links span.first {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/arrows/paging_first.png);
	background-repeat: no-repeat;
	border-left: none;
}

.taglib-page-iterator .search-pages .page-links a.previous, .taglib-page-iterator .search-pages .page-links span.previous {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/arrows/paging_previous.png);
	background-repeat: no-repeat;
}

.taglib-page-iterator .search-pages .page-links a.next, .taglib-page-iterator .search-pages .page-links span.next {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/arrows/paging_next.png);
	background-repeat: no-repeat;
}

.taglib-page-iterator .search-pages .page-links a.last, .taglib-page-iterator .search-pages .page-links span.last {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/arrows/paging_last.png);
	background-repeat: no-repeat;
}

.taglib-page-iterator .search-pages .page-links a.first, .taglib-page-iterator .search-pages .page-links span.first, .taglib-page-iterator .search-pages .page-links a.previous, .taglib-page-iterator .search-pages .page-links span.previous {
	padding-right: 5px;
}

.taglib-page-iterator .search-pages .page-links a.next, .taglib-page-iterator .search-pages .page-links span.next, .taglib-page-iterator .search-pages .page-links a.last, .taglib-page-iterator .search-pages .page-links span.last {
	background-position: 100% 0;
	padding-left: 5px;
}

.taglib-page-iterator .search-pages .page-links span.first, .taglib-page-iterator .search-pages .page-links span.previous {
	background-position: 0 100%;
}

.taglib-page-iterator .search-pages .page-links span.next, .taglib-page-iterator .search-pages .page-links span.last {
	background-position: 100% 100%;
}

.taglib-page-iterator .search-pages .page-selector, .taglib-page-iterator .search-pages .page-links {
	float: left;
}

.taglib-page-iterator .search-pages .page-selector {
	margin-right: 10px;
	padding-right: 10px;
}

/* ---------- Taglib social bookmark ---------- */

.taglib-social-bookmarks {
}

.taglib-social-bookmark-blinklist {
	background: url(<%= themeDisplay.getPathThemeImages() %>/social_bookmarks/blinklist.gif) no-repeat 0 50%;
	padding: 3px 2px 3px 20px;
}

.taglib-social-bookmark-delicious {
	background: url(<%= themeDisplay.getPathThemeImages() %>/social_bookmarks/delicious.gif) no-repeat 0 50%;
	padding: 3px 2px 3px 20px;
}

.taglib-social-bookmark-digg {
	background: url(<%= themeDisplay.getPathThemeImages() %>/social_bookmarks/digg.gif) no-repeat 0 50%;
	padding: 3px 2px 3px 20px;
}

.taglib-social-bookmark-furl {
	background: url(<%= themeDisplay.getPathThemeImages() %>/social_bookmarks/furl.gif) no-repeat 0 50%;
	padding: 3px 2px 3px 20px;
}

.taglib-social-bookmark-newsvine {
	background: url(<%= themeDisplay.getPathThemeImages() %>/social_bookmarks/newsvine.gif) no-repeat 0 50%;
	padding: 3px 2px 3px 20px;
}

.taglib-social-bookmark-reddit {
	background: url(<%= themeDisplay.getPathThemeImages() %>/social_bookmarks/reddit.gif) no-repeat 0 50%;
	padding: 3px 2px 3px 20px;
}

.taglib-social-bookmark-technorati {
	background: url(<%= themeDisplay.getPathThemeImages() %>/social_bookmarks/technorati.gif) no-repeat 0 50%;
	padding: 3px 2px 3px 20px;
}

/* ---------- Specific portlet styles ---------- */

/* ---------- Document Library ---------- */

.portlet-document-library .upload-file {
	background-image: url(<%= themeDisplay.getPathThemeImages() %>/document_library/page.png);
}

/* ---------- Quick note ---------- */

.portlet-quick-note {
	margin: 2px;
	padding: 5px;
}

.portlet-quick-note textarea {
	min-height: 100px;
	padding: 3px;
	width: 95%;
}

.ie6 .portlet-quick-note textarea {
	height: expression(this.height < 100 ? '100px' : this.height);
}

.portlet-quick-note .note-color {
	border: 1px solid;
	cursor: pointer;
	float: left;
	font-size: 0;
	height: 10px;
	margin: 3px 5px;
	width: 10px;
}

.portlet-quick-note .note-color.yellow {
	background-color: #ffc;
	border-color: #fc0;
	margin-left: 0;
}

.portlet-quick-note .note-color.green {
	background-color: #cfc;
	border-color: #0c0;
}

.portlet-quick-note .note-color.blue {
	background-color: #ccf;
	border-color: #309;
}

.portlet-quick-note .note-color.red {
	background-color: #fcc;
	border-color: #f00;
}

.portlet-quick-note a.close-note {
	float: right;
}

/* ---------- RSS ---------- */

.portlet-rss .header {
	cursor: default;
	font-weight: bold;
	margin-top: 2px;
	padding: 2px 5px;
}

/* ---------- jQuery plugins ---------- */

/* ---------- Tabs ---------- */

.tabs-hide {
	display: none;
}

.ie6 .tabs-nav {
	display: inline-block;
}

.ie6 .tabs-nav .tabs-disabled a {
	filter: alpha(opacity=40);
}

/* ----------- OpenID ---------- */

input[type="text"].openid_login {
	background: url(<%= themeDisplay.getPathThemeImages() %>/common/openid.gif) no-repeat;
	background-color: #fff;
	background-position: 0 50%;
	color: #000;
	padding-left: 18px;
}

.ie6 input.text.openid_login {
	background: url(<%= themeDisplay.getPathThemeImages() %>/common/openid.gif) no-repeat;
	background-color: #fff;
	background-position: 0 50%;
	color: #000;
	padding-left: 18px;
}