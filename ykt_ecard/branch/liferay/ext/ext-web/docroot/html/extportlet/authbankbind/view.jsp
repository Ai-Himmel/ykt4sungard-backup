
<%@page import="com.kingstargroup.ecard.exceptions.BccBgInfoException"%>
<%@page import="com.kingstargroup.ecard.exceptions.BccException"%>
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
<%@ include file="/html/extportlet/authbankbind/init.jsp"%>
<%@ include file="/html/extportlet/authbankbind/permission.jsp"%>

<%
	String stuempno = (String) request.getAttribute("stuempno");
	String bankacc = (String) request.getAttribute("bankacc");
	String authcode = (String) request.getAttribute("authcode");
%>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.EDIT_INFO_SUCCESS) %>">
<font class="portlet-msg-info">
    <liferay-ui:message key="bank.cardno.bind.updatesuccess"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.DELETE_INFO_FAILED) %>">
<font class="portlet-msg-info">
    <liferay-ui:message key="bank.cardno.bind.deletesuccess"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.RESET_INFO_FAILED) %>">
<font class="portlet-msg-info">
    <liferay-ui:message key="bank.cardno.bind.resetsuccess"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,BccBgInfoException.class.getName()) %>">
<font class="portlet-msg-error">
    <%= LanguageUtil.format(pageContext, EcardConstants.ERROR_EXIST,((BccBgInfoException)SessionErrors.get(request,BccBgInfoException.class.getName())).getMessage()) %>
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,BccException.class.getName()) %>">
<font class="portlet-msg-error">
    <%= LanguageUtil.format(pageContext, EcardConstants.ERROR_EXIST,((BccException)SessionErrors.get(request,BccException.class.getName())).getMessage()) %>
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,Exception.class.getName()) %>">
<font class="portlet-msg-error">
    <%= LanguageUtil.format(pageContext, EcardConstants.ERROR_EXIST,((Exception)SessionErrors.get(request,Exception.class.getName())).getMessage()) %>
 </font>
</c:if>
<html:form action="/ext/authbankcardnobindedit" method="POST"
	onsubmit="javascript:submitPortletForm(this); return false;">
	<html:hidden property="cmd" />
	<table class="lfr-table" width="80%" align="center">
		<tr align="center">
			<td align="left" width="20%">
				<liferay-ui:message key="bank.acc.bind.stuempno" />
				:
			</td>
			<td align="left">
				<input name="stuempno" style="width: 160px;" type="text"
					value="<%=stuempno%>" readonly="readonly" />
			</td>
		</tr>
		<tr align="center">
			<td align="left" width="20%">
				<liferay-ui:message key="bank.acc.bind.bankacc" />
				:
			</td>
			<td align="left">
				<input id="bankacc" name="bankacc" style="width: 160px;" type="text"
					value="<%=bankacc%>"  maxlength="20"/>
			</td>
		</tr>
		<tr align="center">
			<td align="left" width="20%">
				<liferay-ui:message key="bank.acc.bind.authcode" />
				:
			</td>
			<td align="left">
				<input id="authcode" name="authcode" style="width: 160px;" type="text"
					 maxlength="6"/>
			</td>
		</tr>
		<tr align="center">
            <td align="left" colspan="2">
                &nbsp;
            </td>
        </tr>
		<tr align="center">
            <td align="left" colspan="2">
                <liferay-ui:message key="bank.acc.bind.authinfo" />
            </td>
        </tr>
        <tr>
            <td align="left" colspan="2">
                &nbsp;
            </td>
        </tr>
	</table>
	<table class="lfr-table" align="center" width="95%">
		<tr>
			<td align="center">
				<input type="button"
					value="<liferay-ui:message key="bank.acc.bind.update" />"
					onclick="javascript:whenonsubmit('update')" />&nbsp;&nbsp;
				<input type="button"
					value="<liferay-ui:message key="bank.acc.bind.delete" />"
					onclick="javascript:whenonsubmit('delete')" />&nbsp;&nbsp;
				<input type="button"
					value="<liferay-ui:message key="bank.acc.bind.reset" />"
					onclick="javascript:whenonsubmit('reset')" style="background: transparent url(/html/extthemes/classic/images/login_long.png);width:75px;"/>
			</td>
		</tr>
		</tr>
	</table>
</html:form>

<script type="text/javascript">
    function whenonsubmit(flag){
        if('update'==flag){
            BankBindForm.cmd.value='update'
            BankBindForm.submit();
        }else if('delete'==flag){
             BankBindForm.cmd.value='delete'
            BankBindForm.submit();
        } else if('reset'==flag){
        	BankBindForm.cmd.value='reset'
            BankBindForm.submit();   
        }
    }
</script>