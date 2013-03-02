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

<%

// Modify this variable to add more fine grained filtering

String staticLayoutFilter = layout.isGroup() ? "group" : "desktop";
%>

<!-- Narrow 1 -->

<easyconf:property id="staticPortletsN1Start" component="portal" property="<%= PropsUtil.LAYOUT_STATIC_PORTLETS_N1_START %>" selector1="<%= staticLayoutFilter %>" defaultValue="" />
<easyconf:property id="staticPortletsN1End" component="portal" property="<%= PropsUtil.LAYOUT_STATIC_PORTLETS_N1_END %>" selector1="<%= staticLayoutFilter %>" defaultValue="" />

<%
narrow1Portlets = layoutTypePortlet.addStaticPortlets(narrow1Portlets, staticPortletsN1Start, staticPortletsN1End);
%>

<!-- Narrow 2 -->

<easyconf:property id="staticPortletsN2Start" component="portal" property="<%= PropsUtil.LAYOUT_STATIC_PORTLETS_N2_START %>" selector1="<%= staticLayoutFilter %>" defaultValue="" />
<easyconf:property id="staticPortletsN2End" component="portal" property="<%= PropsUtil.LAYOUT_STATIC_PORTLETS_N2_END %>" selector1="<%= staticLayoutFilter %>" defaultValue="" />

<%
narrow2Portlets = layoutTypePortlet.addStaticPortlets(narrow2Portlets, staticPortletsN2Start, staticPortletsN2End);
%>

<!-- Wide 1 -->

<easyconf:property id="staticPortletsW1Start" component="portal" property="<%= PropsUtil.LAYOUT_STATIC_PORTLETS_W1_START %>" selector1="<%= staticLayoutFilter %>" defaultValue="" />
<easyconf:property id="staticPortletsW1End" component="portal" property="<%= PropsUtil.LAYOUT_STATIC_PORTLETS_W1_END %>" selector1="<%= staticLayoutFilter %>" defaultValue="" />

<%
wide1Portlets = layoutTypePortlet.addStaticPortlets(wide1Portlets, staticPortletsW1Start, staticPortletsW1End);
%>