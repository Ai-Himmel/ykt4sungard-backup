<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "testCategoryAction.do?method=search4List">
<html:errors/>
<br>
<table width="80%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">�������鿴</font></strong></td>
  </tr>
  <tr>
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top" >    
    <table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
        <tbody>
         <logic:present name="testcatlist" scope="request">
         <logic:iterate name="testcatlist" id="nl" type="java.util.Map"  indexId="i" length="1">     
         <input name="bmTestCat.id" type="hidden" value="<bean:write name="nl" property="id"/>">
         <tr align="center" valign="middle">							
            <td width="15%" align="left" valign="middle" class="tableHeader2">
				�����������
			</td>
			<td align="left" valign="middle" class="tableHeader3" colspan="3">
				<bean:write name="nl" property="testCatName"/>								    
			</td>
		 </tr>
		 <tr align="center" valign="middle">							
			<td width="15%" align="left" valign="middle" class="tableHeader2">
				�Ƿ��շ�
			</td>
			<td align="left" valign="middle" class="tableHeader3" colspan="3">
			<c:if test="${nl.ifFee == '1'}">��</c:if>
			<c:if test="${nl.ifFee == '0'}">��</c:if>
			</td>								
		</tr>
		<tr align="center" valign="middle">	
			<td width="15%" align="left" valign="middle" class="tableHeader2">
				�շѱ�׼
			</td>
			<td align="left" valign="middle" class="tableHeader3" colspan="3">
				<bean:write name="nl" property="fee"/>								    
			</td>
		</tr>
		<tr align="center" valign="middle">							
			<td width="15%" align="left" valign="middle" class="tableHeader2">
				�Ƿ�ʹ��
			</td>
			<td align="left" valign="middle" class="tableHeader3" colspan="3">
			<c:if test="${nl.state == '1'}">ʹ��</c:if>
		    <c:if test="${nl.state == '0'}">��ʹ��</c:if>															    
			</td>								
		</tr>                
        </logic:iterate>
        </logic:present>
       </tbody>
      </table></td>
  </tr>
  <tr> 
    <td height="40" align="right" valign="middle">      
      <input name="cancel" type="submit" class="button_nor" value="�� ��">
    </td>
  </tr>
</table>

<input type="hidden" name="pager.offset" value="<%=request.getParameter("pager.offset")%>"/>
<html:hidden property="search_testcatname" />

</html:form>
</center>