<%@ include file="/html/portlet/ecard/bankbind/init.jsp"%>
<%@ include file="/html/portlet/ecard/bankbind/permission.jsp"%>
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


<%
	String stuempno = request.getAttribute("stuempno")==null?"":(String) request.getAttribute("stuempno");
	String bankacc = request.getAttribute("bankacc")==null?"":(String) request.getAttribute("bankacc");
%>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.EDIT_INFO_SUCCESS) %>">
<font class="portlet-msg-info">
    <bean:message key="bank.cardno.bind.updatesuccess"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.DELETE_INFO_FAILED) %>">
<font class="portlet-msg-info">
    <bean:message key="bank.cardno.bind.deletesuccess"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,Exception.class.getName()) %>">
<font class="portlet-msg-error">
	<%="Error:"+SessionErrors.get(request,Exception.class.getName()) %>
 </font>
</c:if>

<html:form action="/ecardbankbind/edit" method="POST">
	<html:hidden property="cmd" />
	<table  width="800" align="center">
		<tr align="center">
			<td align="left" width="20%">
				<bean:message key="bank.acc.bind.stuempno" />:
			</td>
			<td align="left" width="80%">
				<input name="stuempno" style="width: 160px;" type="text"
					value="<%=stuempno%>" readonly="readonly" />
			</td>
		</tr>
		<tr align="center">
			<td align="left" width="20%">
				<bean:message key="bank.acc.bind.bankacc" />:
			</td>
			<td align="left">
				<input id="bankacc" name="bankacc" style="width: 160px;"
					value="<%=bankacc%>"  maxlength="20"/>
			</td>
		</tr>
		<tr align="center">
            <td align="left" colspan="2">
                &nbsp;
            </td>
        </tr>
		<tr align="center">
            <td align="left" colspan="2">
                <bean:message key="bank.acc.bind.notinfo" />
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
			<td align="right" width="50%">
				<input type="button" value="<bean:message key="bank.acc.bind.update" />"  onclick="javascript:whenonsubmit('update')"/>
			</td>
			<td align="left">
				<input type="button" value="<bean:message key="bank.acc.bind.delete" />" onclick="javascript:whenonsubmit('delete')" />
			</td>
		</tr>
		</tr>
	</table>
</html:form>

<script type="text/javascript">
    function whenonsubmit(flag){
        if('update'==flag){
            BankBindForm.cmd.value='update';
        }else if('delete'==flag){
             BankBindForm.cmd.value='delete';
        }
        if(submitPortletForm(BankBindForm)){
        	BankBindForm.submit();
        }
    }
</script>