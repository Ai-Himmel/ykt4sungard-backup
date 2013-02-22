<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<body>
<center>

<html:form action = "feeTestUpdateAction.do?method=feeTestUpdateResult">

<br>

<table width="90%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">已缴费考试更改历史记录</font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>  
  <tr> 
    <td align="center" valign="top" ><table 
        width=90% border=1 align=left 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign="middle">              
              <td width="10%" align="right" valign="middle" class="tableHeader2" >学号</td>
              <td width="40%" align="left" valign="middle" class="tableHeader3" >
              <html:text property="studentno" styleClass="input_box" maxlength="15" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
              </td>
              <td width="10%" align="right" valign="middle" class="tableHeader2" >姓名</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="stuname" styleClass="input_box" maxlength="10" onkeydown="if(event.keyCode==13) document.onkeydown();"/>
              </td>
            </tr>
           <tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									  原缴费科目
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<html:select property="oldtestId" styleClass="select01">
										<html:option value="" >请选择</html:option>
										<logic:present name="testlist" scope="request">
				  				        <html:options collection="testlist" labelProperty="testInfo" property="id" />
               						 </logic:present>									
								   </html:select>			    
								</td>
									<td width="15%" align="left" valign="middle" class="tableHeader2">
									  现缴费科目 
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									 <html:select property="newtestId" styleClass="select01">
										<html:option value="" >请选择</html:option>
										<logic:present name="testlist" scope="request">
				  				        <html:options collection="testlist" labelProperty="testInfo" property="id" />
               						 </logic:present>									
								   </html:select>					    
								</td>
							</tr>           
          </tbody>
        </table></td>
  </tr>  
  <tr> 
      <td height="40" align="right" valign="middle" class="tdborder02">
      &nbsp;&nbsp;<input name="Submit" type="submit" class="button_nor" value="查 询" > 
      <input name="Reset" type="button" class="button_nor" value="重 置" onClick="DoClear()">
      </td>
  </tr>  

  <tr> 
    <td align="right" valign="middle">
    &nbsp;
    </td>
  </tr>
  <tr> 
      <td align="center" valign="top">
      <table width=90% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
          <logic:present name="feeTestList" scope="request">
          <thead>
            <tr align="center" valign=center>
              
              <td valign="middle" class="tableHeader" >学号</td>              
              <td valign="middle" class="tableHeader" nowrap>姓名</td>              
              <td valign="middle" class="tableHeader" >原缴费科目</td>
              <td valign="middle" class="tableHeader" >现缴费科目</td>
              <td valign="middle" class="tableHeader" >修改时间</td>
               
            </tr>
          </thead>
            <!--page offset start -->
          <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./feeTestUpdateAction.do" items="<%=listcount%>" index="center" maxPageItems="10" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="method" />    
           <pg:param name="studentno" />
           <pg:param name="stuname" />
           <pg:param name="oldtestId" />
           <pg:param name="newtestId" />
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
			
            <logic:iterate name="feeTestList" id="nl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign="middle">             
             
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="stuName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="oldtest" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="newtest" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="nl" property="updateTime" />&nbsp;</td>         
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign="middle">             
             
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="stuName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="oldtest" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="newtest" />&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="nl" property="updateTime" />&nbsp;</td>     
            </tr>
            </c:when></c:choose>
            </pg:item>
            </logic:iterate>
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
            </logic:present>
            <logic:notPresent name="feeTestList" scope="request">                           
          <!--page offset start -->
		  <pg:pager url="./feeTestUpdateAction.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->		  
            </logic:notPresent>            
          </tbody>
        </table>
      </td>
  </tr>
  
</table>

</html:form>
</center>
</body>

