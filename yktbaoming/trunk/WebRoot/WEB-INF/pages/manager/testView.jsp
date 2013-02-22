<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "testAction.do?method=search4List">
<html:errors/>
<br>
<table width="80%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">考试查看</font></strong></td>
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
         <logic:present name="testlist" scope="request">
         <logic:iterate name="testlist" id="nl" type="java.util.Map"  indexId="i" length="1">     
         <input name="bmTest.id" type="hidden" value="<bean:write name="nl" property="id"/>">
                            <tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									考试类别名称
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<bean:write name="nl" property="testCatName"/> 						    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									报名开始时间
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
                                    <bean:write name="nl" property="bmBegin"/> 
                                </td>                                             							
							</tr>
							<tr align="center" valign="middle">	
							    <td width="15%" align="left" valign="middle" class="tableHeader2">
									报名结束时间
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
                                    <bean:write name="nl" property="bmEnd"/>
                                </td> 
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									考试日期
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
								    <bean:write name="nl" property="testDate"/>
                                </td> 
                            </tr>
                            <tr align="center" valign="middle">	
							    <td width="15%" align="left" valign="middle" class="tableHeader2">
									考试开始时间
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
							        <bean:write name="nl" property="testBeginTime"/>
                               </td>
                            </tr>
                            <tr align="center" valign="middle">	
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									考试结束时间
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
                                    <bean:write name="nl" property="testEndTime"/>
                                </td> 
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									考试说明
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
								    <bean:write name="nl" property="testMemo"/>
								</td>
							</tr>                        
        </logic:iterate>
        </logic:present>
       </tbody>
      </table></td>
  </tr>
  <tr> 
    <td height="40" align="right" valign="middle">      
      <input name="cancel" type="submit" class="button_nor" value="返 回">
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
<html:hidden property="search_testcatname" />

</html:form>
</center>
