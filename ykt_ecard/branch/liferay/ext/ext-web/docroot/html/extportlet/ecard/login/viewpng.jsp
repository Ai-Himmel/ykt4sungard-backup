
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
<%@ include file="/html/extportlet/ecard/login/init.jsp"%>
		<%
			boolean secure = request.isSecure();

			if (PropsValues.COMPANY_SECURITY_AUTH_REQUIRES_HTTPS && !secure) {
				secure = true;
			}

			String login = LoginAction.getLogin(request, "login", company);
			String password = StringPool.BLANK;
			boolean rememberMe = ParamUtil.getBoolean(request, "rememberMe");
		%>



		<table height="100%" width="100%" bgcolor="#E3EFFD">
			<form
				action="<portlet:actionURL secure="<%=secure%>"><portlet:param name="struts_action" value="/ext/extloginview" /><portlet:param name="<%=Constants.CMD%>" value="<%=Constants.UPDATE%>" /></portlet:actionURL>"
				method="post" name="<portlet:namespace />fm">
				<input name="save_last_path" type="hidden" value="0" />
				<input name="<portlet:namespace />rememberMe" type="hidden"
					value="<%=rememberMe%>" />
			<tr valign="top">
				<td width="549" height="189" class="login_left">
					&nbsp;
				</td>
				<td class="login_middle">
					&nbsp;
				</td>
				<td width="404" class="login_right">
					<table>
						<tr>
							<td align="left" width="40%">
								&nbsp;
							</td>
							<td align="left">
								&nbsp;
							</td>
						</tr>
						<tr>
							<td align="left" colspan="2">
								<liferay-ui:error exception="<%=AuthException.class%>"
									message="authentication-failed" />
								<liferay-ui:error
									exception="<%=CookieNotSupportedException.class%>"
									message="authentication-failed-please-enable-browser-cookies" />
								<liferay-ui:error exception="<%=NoSuchUserException.class%>"
									message="please-enter-a-valid-login" />
								<liferay-ui:error
									exception="<%=PasswordExpiredException.class%>"
									message="your-password-has-expired" />
								<liferay-ui:error
									exception="<%=UserEmailAddressException.class%>"
									message="please-enter-a-valid-login" />
								<liferay-ui:error exception="<%=UserLockoutException.class%>"
									message="this-account-has-been-locked" />
								<liferay-ui:error exception="<%=UserPasswordException.class%>"
									message="please-enter-a-valid-password" />
								<liferay-ui:error exception="<%=UserScreenNameException.class%>"
									message="please-enter-a-valid-screen-name" />
								&nbsp;
							</td>
						</tr>
						<tr>
							<td align="left" width="40%">
								<liferay-ui:message key="ecard.userid" />
							</td>
							<td align="left">
								<input name="<portlet:namespace />login" style="width: 120px;"
									type="text" value="<%=login%>" />
							</td>
						</tr>
						<tr>
							<td align="left" width="40%">
								<liferay-ui:message key="ecard.passwd" />
							</td>
							<td align="left">
								<input id="<portlet:namespace />password"
									name="<portlet:namespace />password" style="width: 120px;"
									type="password" value="<%=password%>" />

								<span id="<portlet:namespace />passwordCapsLockSpan"
									style="display: none;"><liferay-ui:message
										key="caps-lock-is-on" /> </span>
							</td>
						</tr>
						<tr>
							<td align="left" width="40%">
								<liferay-ui:message key="ecard.authcode" />
							</td>
							<td>
								<input class="textbox" style="width: 120px" name="authCode"
									type="text">
							</td>
						</tr>
						<tr>
							<td align="left" width="40%">
							<td>
								<img id="cauthcodeimg" border="0" hspace="0"
									src="/servlet/ImageCaptchaServlet" vspace="0" width="128px"
									height="40" onclick="javascript:imgclick();"
									alt="<liferay-ui:message key="ecard.changecode" />">
							</td>
						</tr>					

						<tr>
							<td align="left" width="40%">
								&nbsp;
							</td>
							<td align="right">
								<input type="submit" class="lfr-submit"
									value="<liferay-ui:message key="sign-in" />" />
							</td>
						</tr>
					</table>
				</td>
			</tr>
			</form>
		</table>



		<script type="text/javascript">
			jQuery(
				function() {
					jQuery('#<portlet:namespace />password').keypress(
						function(event) {
							Liferay.Util.showCapsLock(event, '<portlet:namespace />passwordCapsLockSpan');
						}
					);
				}
			);

			<c:if test="<%=windowState.equals(WindowState.MAXIMIZED)%>">
				Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />login);
			</c:if>
			
			
			function imgclick(){
			 document.all.cauthcodeimg.src='/servlet/ImageCaptchaServlet?time='+Math.random();
			}
			
		</script>