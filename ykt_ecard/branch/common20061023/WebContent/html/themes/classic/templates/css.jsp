<%
/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

<%@ include file="init.jsp" %>

/******************************************************************************/
/* Liferay                                                                    */
/******************************************************************************/

.portlet-msg-error {
	color: <%= colorScheme.getPortletMsgError() %>;
	font-family: Tahoma, Arial;
	font-size: 12px;
}

.portlet-msg-alert {
	color: <%= colorScheme.getPortletMsgAlert() %>;
	font-family: Tahoma, Arial;
	font-size: medium;
	font-style: italic;
}

.portlet-msg-success {
	color: <%= colorScheme.getPortletMsgSuccess() %>;
	font-family: Tahoma, Arial;
	font-size: medium;
}
/******************************************************************************/
/* Navigation Portlet                                                         */
/******************************************************************************/

.portlet-navigation-menu {
	margin: 10px 0 10px 15px;
	padding: 0px;
	font-family: Arial;
	font-size: x-small;
	text-align: left;
}

.portlet-navigation-menu UL {
	margin: 0 0 0 5px;
	padding: 0px 0 0 15px;
}

body,td,th {
	font-size: 12px;	
}
body {
	margin-left: 0px;
	margin-top: 0px;
	margin-right: 0px;
	margin-bottom: 0px;
}
.text_blue_14 {
	font-size: 14px;
	color: #3B639E;
	font-weight: bold;
	text-decoration:none;
}
.text_blue_12 {
	font-size: 12px;
	color: #000099;
}
.text_blue_12_c{
	font-size: 12px;
	color: #3B639E;
	font-weight: bold;
}
.text_brown_12_c{
	font-size: 12px;
	color: #3B639E;
	font-weight: bold;
}
.text_or_12 {
	font-size: 12px;
	color: #FF0000;
}
.text_brown{
	font-size: 12px;
	color: #000099;
}
.text_w {
	font-size: 14px;
	color: #ffffff;
}
.text_w_12 {
	font-size: 12px;
	color: #ffffff;
}


.button_blank{
    cursor:hand;
	background:url(<%= themeDisplay.getPathThemeRoot() %>/images/ecard/button.jpg) center bottom;
	width:65px;
	height:20px;
	font-size:12px;
	color:#8b8989;
	margin: 0px;
	padding: 0px;
	border: 0px none;
}
.txt_or {
	font-size: 13px;
	color: #FF0000;
}

.text_w_12 {
	font-size: 12px;
	color: #ffffff;
}

.tdclass {
	line-height: 20px;
}

.bg_table table{background-color:#E6E6E6; border:0px;}
.inside_table{border:0px; margin:0px; padding:1px;}
.list_tr td{background-color:#BCD6FC; height:20px;border:0px;}
.tr_1 td{background-color:#F1F7FE; height:20px;border:0px;}
.tr_2 td{background-color:#FFFFFF; height:20px;border:0px;}

a.w_14_link{font-size: 14px;color: #ffffff;text-decoration:none;font-weight: bold;}
a.w_14_link:link{font-size: 14px;text-decoration:none;}
a.w_14_link:hover{font-size: 14px;color: #CCCCCC;text-decoration:none;}
a.w_14_link:visited{font-size: 14px;text-decoration:none;}

a.brown_link{font-size: 12px;color: #000099;text-decoration:none;}
a.brown_link:link{font-size: 12px;text-decoration:none;}
a.brown_link:hover{font-size: 12px;color: #000000;text-decoration:none;}
a.brown_link:visited{font-size: 12px;text-decoration:none;}

a.brown_link_line{font-size: 12px;color: #000099;text-decoration:underline;}
a.brown_link_line:link{font-size: 12px;color: #000099;text-decoration:underline;}
a.brown_link_line:hover{font-size: 12px;color: #000000;text-decoration:underline;}
a.brown_link_line:visited{font-size: 12px;}

a.blue_link_line{font-size: 12px;color: #000099;text-decoration:underline;}
a.blue_link_line:link{font-size: 12px;color: #000099;text-decoration:underline;}
a.blue_link_line:hover{font-size: 12px;color: #000000;text-decoration:underline;}
a.blue_link_line:visited{font-size: 12px;}

a.blue_link_line_14{font-size: 14px;color: #5e98e5;text-decoration:underline;}
a.blue_link_line_14:link{font-size: 14px;color: #5e98e5;text-decoration:underline;}
a.blue_link_line_14:hover{font-size: 14px;color: #5e98e5;text-decoration:underline;}
a.blue_link_line_14:visited{font-size: 14px;}




/******************************************************************************/
/* Display Tag Library                                                        */
/******************************************************************************/

TR.even { background-color: <%= colorScheme.getPortletMenuBg() %>; color: #000000; font-family: Tahoma, Arial; }

TR.odd { background-color: <%= colorScheme.getPortletBg() %>; color: #000000; font-family: Tahoma, Arial; }
