<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>
<script type="text/javascript" src="<c:url value='/pages/datepicker/WdatePicker.js'/>"></script>

<center>

<html:form action = "studentAction.do?method=search4List">
<html:errors/>
<br>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">���������޸�</font></strong></td>
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
         <logic:present name="stubmlist" scope="request">
         <logic:iterate name="stubmlist" id="nl" type="java.util.Map"  indexId="i" length="1">     
         <input name="stubmId" type="hidden" value="<bean:write name="nl" property="id"/>">
                            <tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									ѧ��
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="studentNo"/> 								    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									����
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="stuName"/>					    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�Ա�
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="gender"/>			    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									��ѧ���
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="enrollYear"/>								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									ѧԺ����
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="deptName"/>								    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									רҵ����
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="majorName"/>							    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�꼶
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="curGrade"/>							    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�༶
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="curClass"/>							    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									֤������
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="idType"/>								    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									֤������
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<bean:write name="nl" property="idCard"/>								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									�����ʼ�
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<bean:write name="nl" property="email"/>	    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									ѡ����
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<bean:write name="nl" property="testInfo"/>								    
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
  <tr> 
    <td height="40" align="left" valign="middle"> 
      <font size="2.5" color="red">
      <logic:present name="stubmlist" scope="request">
      ע���ÿ����Ѳμӹ��˿��Եı����������ٽ����޸ġ�
      </logic:present>
      <logic:notPresent name="stubmlist" scope="request">
      ע���ÿ���������¼�ѱ�ɾ���������ٽ����޸ġ�
      </logic:notPresent>
      </font>
    </td>
  </tr>
</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>

<input type="hidden" name="pager.offset" value="<%=request.getParameter("pager.offset")%>"/>
<html:hidden property="search_studentno" />
<html:hidden property="search_stuname" />
<html:hidden property="search_deptname" />
<html:hidden property="search_majorname" />
<html:hidden property="search_curgrade" />
<html:hidden property="search_curclass" />
<html:hidden property="search_idtype" />
<html:hidden property="search_idcard" />
<html:hidden property="search_testcatname" />
<html:hidden property="search_testid" />
<html:hidden property="search_ifbm" />
<html:hidden property="search_ifpay" />
</html:form>
</center>
