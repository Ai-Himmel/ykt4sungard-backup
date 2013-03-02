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

<%@ include file="portal_init.jsp" %>

	<table width="1000" border="0" cellspacing="0" cellpadding="0">
		      <tr>
		        <td height="8"></td>
		      </tr>
		    </table>
	<table width="85%" align=center bgColor=#ffffff border="0" cellspacing="0" cellpadding="0">

    <tr>
      <td width="9" height="20"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_l_1.jpg" width="9" height="20"></td>
      <td height="20" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_top.jpg">			
		<c:if test="<%= Validator.isNotNull(title) %>">
				  <table width="85" height="20" border="0" cellpadding="0" cellspacing="0" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/menu.jpg">
	                <tr>
	                  <td width="16">&nbsp;</td>
	                  <td width="69" class="text_brown_12_c"><%= title %></td>
	                </tr>
	              </table>
		</c:if>
		</td>
		
		
		<td width="9" height="20"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_r_1.jpg" width="9" height="20"></td>
    	 </tr>
			<tr>
              <td valign="top"><img height=240 id="leftImage" src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_l_2.jpg" width="9"></td>
              <td valign="top">
          
