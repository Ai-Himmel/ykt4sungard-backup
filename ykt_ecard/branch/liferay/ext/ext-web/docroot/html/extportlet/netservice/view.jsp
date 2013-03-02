
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
<%@ include file="/html/extportlet/netservice/init.jsp"%>
<%@ include file="/html/extportlet/netservice/permission.jsp"%>

<%
	String stuempno = (String) request.getAttribute("stuempno");
%>

	<table class="lfr-table" width="80%" align="center">
		<tr align="center">
			<td align="left" width="20%">
                
			</td>
			<td align="left">
				<liferay-ui:message key="netservice.ext_netservice" /><a target="_blank" href="http://localhost:8080/netservice/zhcxAction.do?method=login&checkcode=<%=stuempno%>"><liferay-ui:message key="netservice.clickin" /></a>
			</td>
		</tr>

		<tr align="center">
            <td align="left" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr>
            <td align="left" colspan="2">
                &nbsp;
            </td>
        </tr>
	</table>
