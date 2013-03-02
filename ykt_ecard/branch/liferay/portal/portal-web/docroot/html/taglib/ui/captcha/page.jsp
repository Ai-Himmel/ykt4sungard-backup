
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

<%@ include file="/html/taglib/init.jsp"%>

<%@ page import="com.liferay.portal.captcha.CaptchaUtil"%>

<%
	String url = (String) request
			.getAttribute("liferay-ui:captcha:url");

	boolean captchaEnabled = false;

	if (renderRequest != null) {
		captchaEnabled = CaptchaUtil.isEnabled(renderRequest);
	} else {
		captchaEnabled = CaptchaUtil.isEnabled(request);
	}
%>


<c:if test="<%=captchaEnabled%>">
	<table class="lfr-table">
		<tr>
			<td align="left" width="40%">
				<liferay-ui:message key="text-verification" />
				:
			</td>
			<td align="left">
				<input name="<%=namespace%>captchaText" style="width: 120px;"
					type="text" value="" />
			</td>
		</tr>
		<tr>
			<td width="40%">
				&nbsp;
			</td>
			<td align="left">
				<img id="imgcheckcode" width="130" height="55" src="<%=url%>"
					onclick="javascript:checkcodeimgclick();"
					alt="<liferay-ui:message key="ecard.changecode" />">
			</td>
		</tr>
	</table>
	<br />
	
	<script type="text/javascript"> 
            function checkcodeimgclick(){    
            var myurl = "<%=url%>" ;
             document.all.imgcheckcode.src=myurl+'?time='+Math.random();
            }
            
        </script>
</c:if>