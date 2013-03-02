<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "gzcheckinsubminAction.do?method=tongjisubmit">
<html:errors/>
<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">
      <logic:present name="htitle" scope="request">
      <c:choose><c:when test="${htitle == '1'}">未报到名单
      </c:when></c:choose>
      <c:choose><c:when test="${htitle == '2'}">请假名单
      </c:when></c:choose>
      <c:choose><c:when test="${htitle == '3'}">申请保留入学资格名单
      </c:when></c:choose>
      <c:choose><c:when test="${htitle == '4'}">不明原因未报到名单
      </c:when></c:choose>
      <c:choose><c:when test="${htitle == '5'}">明确不来名单
      </c:when></c:choose>
      <c:choose><c:when test="${htitle == '6'}">放弃入学资格名单
      </c:when></c:choose>
      </logic:present>
      <logic:notPresent name="htitle" scope="request">
      名单
      </logic:notPresent>
      </font></strong></td>
    </tr>     
    
    <tr>
      <td height="30" align="right" valign="middle" colspan="2">
      <logic:present name="checkinlist" scope="request">      
         <a href="javascript:DoExport()">导出Excel<IMG src="./pages/style/default/images/xls.gif" border="0"></a>      
     </logic:present>&nbsp;
      </td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input name="viewclassNo" type="hidden" value="<%=request.getAttribute("viewclassNo")%>">
          <input name="viewmajor" type="hidden" value="<%=request.getAttribute("viewmajor")%>">
          <input name="md" type="hidden" value="<%=request.getAttribute("md")%>">
          <input name="doexl" type="hidden" value=""> 
          <thead>
            <tr align="center" valign=center> 
              <td height="24" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td valign="middle" class="tableHeader" style="display:none">国籍</td>
              <td valign="middle" class="tableHeader" style="display:none">录取院系</td>
              <td valign="middle" class="tableHeader" style="display:none">录取专业</td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.state"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.reason"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.particular"/></td>
            </tr>
            <logic:present name="checkinlist" scope="request">
            </thead>          
           <!--page offset start -->
           <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		   <pg:pager url="./gzcheckinsubminAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <pg:param name="method" />
           <pg:param name="viewclassNo" />
           <pg:param name="viewmajor" />
           <pg:param name="gender" />
           <pg:param name="nationality" />
           <pg:param name="hcollegeId" />
           <pg:param name="hclassNo" /> 
           <pg:param name="hmajorin" />
           <pg:param name="myAction" />          
           <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">  
            <logic:iterate name="checkinlist" id="cl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" style="display:none">
              <logic:present name="arealist" scope="request">            
               <logic:iterate name="arealist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.nationality}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" style="display:none"><bean:write name="cl" property="departmentName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" style="display:none">
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.ifCheckedin == '0'}"><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/>
              </c:when></c:choose>              
              <c:choose><c:when test="${cl.ifCheckedin == '1'}"><bean:message bundle="checkinmanage" key="checkin.checkedin"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.reason == '00'}">不来
              </c:when></c:choose>
              <c:choose><c:when test="${cl.reason == '01'}"><bean:message bundle="checkinmanage" key="checkin.askforlate"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.reason == '02'}"><bean:message bundle="checkinmanage" key="checkin.askReserve"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.reason == '03'}"><bean:message bundle="checkinmanage" key="checkin.noReason"/>
              </c:when></c:choose>&nbsp;
              </td>   
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.ifReserve == '1'}"><bean:message bundle="checkinmanage" key="checkin.reserve"/> 
              </c:when></c:choose>              
              <c:choose><c:when test="${cl.ifLeaveSchool== '1'}"><bean:message bundle="checkinmanage" key="checkin.leaveschool"/>
              </c:when></c:choose>&nbsp;
              </td>           
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" style="display:none">
              <logic:present name="arealist" scope="request">            
               <logic:iterate name="arealist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.nationality}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" style="display:none"><bean:write name="cl" property="departmentName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" style="display:none">
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <c:choose><c:when test="${cl.ifCheckedin == '0'}"><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifCheckedin == '1'}"><bean:message bundle="checkinmanage" key="checkin.checkedin"/>
              </c:when></c:choose>
              </td>  
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.reason == '00'}">不来
              </c:when></c:choose>
              <c:choose><c:when test="${cl.reason == '01'}"><bean:message bundle="checkinmanage" key="checkin.askforlate"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.reason == '02'}"><bean:message bundle="checkinmanage" key="checkin.askReserve"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.reason == '03'}"><bean:message bundle="checkinmanage" key="checkin.noReason"/>
              </c:when></c:choose>&nbsp;
              </td>   
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.ifReserve == '1'}"><bean:message bundle="checkinmanage" key="checkin.reserve"/> 
              </c:when></c:choose>              
              <c:choose><c:when test="${cl.ifLeaveSchool== '1'}"><bean:message bundle="checkinmanage" key="checkin.leaveschool"/>
              </c:when></c:choose>&nbsp;
              </td>                
            </tr>
            </c:when></c:choose>
          </pg:item>              
          </logic:iterate>
          <jsp:include page="./page.jsp" flush="true" />
          </tbody>
        </table></td>
    </tr>
    <tr> 
    <td height="24" align="left" valign="middle">
        <jsp:include page="./page.jsp" flush="true" />
    </td>
    </tr>
		  </pg:pager>
		  <!-- page offset end -->
          </logic:present>          
          
    <logic:present name="checkinlist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
    </td>
    </tr>  
    </logic:present>
    <tr>
    <td height="40" align="right" valign="middle"> 
      <input name="Submit" type="button" class="button_nor" value="返 回" onClick="Goback()"> 
    </td>
    </tr>
</table>
<jodd:form bean="request">
	<input type="hidden" name="hcollegeId" value="<%=request.getParameter("hcollegeId")%>">
	<input type="hidden" name="hclassNo" value="<%=request.getParameter("hclassNo")%>">
	<input type="hidden" name="hmajorin" value="<%=request.getParameter("hmajorin")%>">
	<input type="hidden" name="gender" value="<%=request.getParameter("gender")%>">
	<input type="hidden" name="nationality" value="<%=request.getParameter("nationality")%>">
	<input type="hidden" name="myAction" value="<%=request.getParameter("myAction")%>">
</jodd:form>
</html:form>
</center>

<script language="JavaScript">

function DoExport(){

   document.all.doexl.value="1";
     
   document.checkinsubminForm.action="gzcheckinsubminAction.do?method="+document.all.md.value+"&viewmajor="+document.all.viewmajor.value+"&hcollegeId="+document.all.hcollegeId.value+"&hmajorin="+document.all.hmajorin.value+"&gender="+document.all.gender.value+"&nationality="+document.all.nationality.value;
   document.checkinsubminForm.submit();

}
function Goback(){
  document.all.doexl.value="";
  
  document.checkinsubminForm.action=document.all.myAction.value; 
  
  document.checkinsubminForm.submit();
}
</script>