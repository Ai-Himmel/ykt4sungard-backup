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

/*
 ---------- Uni-Form form controls ----------
Uni-Form (v1.1) by Dragan Babic  - http://dnevnikeklektika.com/uni-form/

Modified to use the Liferay/JSR-168 classname convention
Regex used to convert classnames are
Find: (\.|#)([a-z]+)([A-Z]{1})([a-z]+)(\s|\{|:|,)
Replace: $1$2-\L$3$4$5

Distributed under http://creativecommons.org/licenses/by-sa/2.5/
*/

.uni-form {
	margin: 0;
	overflow: hidden;
	padding: 0;
	position: relative;
	width: 100%;
}

/* Some generals */

.uni-form .ctrl-holder {
	/* this is the main unit that contains our form elements */
	overflow: hidden;
	clear: both;
	margin: 0;
	padding: 0;
}

.uni-form .button-holder {
	clear: both;
	overflow: hidden;
}

.uni-form .reset-button {
}

.uni-form .submit-button {
}

.uni-form .inline-label,   .uni-form .inline-labels .inline-label,   .uni-form .block-labels .inline-label {
	display: inline;
	float: none;
	margin: 0 1em 0 0;
	width: auto;
}

.uni-form .inline-label input {
}

.uni-form .focused {
}

/* ########################################################################## */
/* Styles for form controls where labels are in line with the input elements */
/* Set the class of the parent (preferably to a fieldset) to .inline-labels */
.uni-form .inline-labels .ctrl-holder {
}

.uni-form .inline-labels label,   .uni-form .inline-labels .label {
	float: left;
	line-height: 100%;
	margin: .3em 2% 0 0;
	padding: 0;
	position: relative;
}

.uni-form .inline-labels .text-input,   .uni-form .inline-labels .file-upload {
	float: left;
}

.uni-form .inline-labels .file-upload {
}

.uni-form .inline-labels .select-input {
	float: left;
}

.uni-form .inline-labels textarea {
	float: left;
}

.uni-form .inline-labels .form-hint {
	clear: both;
}

/* inlineLabels esthetics */
.uni-form .inline-labels .form-hint strong {
}

/* ########################################################################## */
/* Styles for form controls where labels are above the input elements */
/* Set the class of the parent (preferably to a fieldset) to .block-labels */
.uni-form .block-labels .ctrl-holder {
}

.uni-form .block-labels label,   .uni-form .block-labels .label {
	display: block;
	float: none;
	line-height: 100%;
	margin: .3em 0;
	padding: 0;
	width: auto;
}

.uni-form .block-labels .label {
	float: left;
	margin-right: 3em;
}

.uni-form .block-labels .inline-label {
	position: relative;
	top: .15em;
}

.uni-form .block-labels .text-input,   .uni-form .block-labels .file-upload {
	float: left;
}

.uni-form .block-labels .file-upload {
}

.uni-form .block-labels .select-input {
	display: block;
}

.uni-form .block-labels textarea {
	display: block;
	float: left;
}

.uni-form .block-labels .form-hint {
	clear: none;
	float: right;
	margin: 0;
}

/* blockLabels esthetics */
.uni-form .block-labels .ctrl-holder {
}

.uni-form .block-labels .focused {
}

/* ########################################################################## */
/* Focus pseudoclasses */
.uni-form .ctrl-holder .text-input:focus {
}

.uni-form div.focused .text-input:focus {
}

.uni-form div.focused .form-hint {
}

/* Required fields asterisk styling, use if needed */
.uni-form label em,   .uni-form .label em {
	display: block;
	font-style: normal;
	font-weight: bold;
	left: 100%;
	position: absolute;
}

.uni-form .block-labels label em,   .uni-form .block-labels .label em {
	display: inline;
	position: static;
}

/* ########################################################################## */
/* Messages */
.uni-form #error-msg,   .uni-form .error {
}

.uni-form #error-msg dt,   .uni-form #error-msg h3 {
}

.uni-form #error-msg dd {
}

.uni-form #error-msg ol {
}

.uni-form #error-msg ol li {
}

.uni-form .error-field {
}

/* ########################################################################## */
/* Add the following classes to your fieldsets (preferably) if you want columns */
.uni-form .col {
	float: left;
}

.uni-form .column-left {
	float: left;
}

.uni-form .column-right {
	float: right;
}

/* ---------- IE Specific controls ---------- */

.ie6 .uni-form,   .ie6 .uni-form fieldset,   .ie6 .ctrl-holder,   .ie6 .ctrl-holder span,   .ie6 .form-hint {
	/* trigger haslayout, move to your ie specific stylesheet if possible */
	zoom: 1;
}

.ie6 .block-labels .form-hint {
	margin-top: 0;
}

/* ---------- Uni-Form custom rules ---------- */
/* Your styles below */
/* Keep in mind that wherever you see "Required property" it means that the property must exist, adjust it's value to your liking */
/* Generals */
.uni-form fieldset {
	margin: 0;
}

.uni-form fieldset legend {
	/* reset ie */
	font-weight: bold;
	color: #000;
	font-size: 120%;
}

.uni-form .ctrl-holder {
	/* this is the main unit that contains our form elements */
	padding: 3px;
}

.uni-form .button-holder {
	text-align: left;
	margin-top: 15px;
}

.uni-form .ctrl-holder .button-holder {
	clear: none;
	margin-left: 5px;
	margin-right: 5px;
	margin-top: 0;
}

.uni-form .focused {
	background: #FFFCDF;
}

.uni-form .ctrl-holder.inline-label label {
	display: inline;
}

/* .inline-labels */
.uni-form .inline-labels label,  .uni-form .inline-labels .label {
	width: 45%;
}

.uni-form .inline-labels .text-input,  .uni-form .inline-labels .file-upload {
	width: 45%;
}

.uni-form .inline-labels .select-input {
	width: 45%;
}

.uni-form .inline-labels textarea {
	height: 12em; /* required property */
	width: 45%;
}

.uni-form .inline-labels .form-hint {
	margin-left: 47%;
	margin-top: 0;
}

/* .block-labels */
.uni-form .block-labels .text-input,  .uni-form .block-labels .file-upload {
	width: 53%;
}

.uni-form .block-labels .select-input {
	display: block;
	width: 53.5%;
}

.uni-form .block-labels textarea {
	/* required property */
	height: 12em;
	width: 53%;
}

.uni-form .block-labels .form-hint {
	width: 45%;
}

/* Columns */
.uni-form .col {
	margin: 0 2% 0 0; /* required property */
	width: 47.9%;
}

.uni-form .column-left {
	width: 49%;
}

.uni-form .column-right {
	width: 49%;
}

/* Messages */
.uni-form #error-msg {
	background: #FFDFDF;
	border: 1px solid #DF7D7D;
	border-width: 1px 0;
	margin: 0 0 1em 0;
	padding: 1em;
}

.uni-form .error {
	background: #FFDFDF;
	border: 1px solid #DF7D7D;
	border-width: 1px 0;
}

.uni-form #error-msg dt,  .uni-form #error-msg h3 {
	font-size: 110%;
	font-weight: bold;
	line-height: 100%;
	margin: 0 0 .5em 0;
}

.uni-form #error-msg dd {
	margin: 0;
	padding: 0;
}

.uni-form #error-msg ol {
	margin: 0;
	padding: 0;
}

.uni-form #error-msg ol li {
	border-bottom: 1px dotted #DF7D7D;
	list-style-position: inside;
	margin: 0;
	padding: 2px;
	position: relative;
}

.uni-form .error-field {
	background: #FFBFBF;
	color: #AF4C4C;
	margin: 0 0 6px 0;
	padding: 4px;
}