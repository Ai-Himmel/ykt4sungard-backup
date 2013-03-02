<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "stufeeinfoAction.do?method=tuitionnotpaylist">

<br>

<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">入学费用未缴班级查询</font></strong></td>
    </tr>     
    
    <tr> 
      <td align="left" valign="top" >
      <table width=100% border=1 align=left cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody> 
          <tr align="center" valign=center>
             <td width="10%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
             <td align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
            <td width="10%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
            <td align="left" valign="middle" class="tableHeader3" >
                <input 
                name="stuName" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();">
            </td>           
          </tr>          
          
         <logic:present name="stuinfo" scope="request">             
            <input name="hstudentNo" type="hidden" value="<bean:write name="stuinfo" property="studentNo"/>">            
            <input name="hstuName" type="hidden" value="<bean:write name="stuinfo" property="stuName"/>">            
         </logic:present>   
         <logic:notPresent name="stuinfo" scope="request">             
            <input name="hstudentNo" type="hidden" value="">             
            <input name="hstuName" type="hidden" value="">            
         </logic:notPresent>
                  
        </tbody>
     </table>
     </td>
    </tr>
    
    <tr>
    <td height="30" align="right" valign="middle" class="tdborder02"> 
      <input name="Submit" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.lookfor"/>" onClick="DoFind()">
      <input name="Reset" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.reset"/>" onClick="DoClear()"> 
    </td>
    </tr>
    <input name="doexl" type="hidden" value="">
          <logic:present name="feenotpaylist" scope="request">
    <tr>
      <td height="30" align="right" valign="middle" colspan="2">      
         <a href="javascript:DoExport()">导出Excel<IMG src="./pages/style/default/images/xls.gif" border="0"></a>      
      </td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
          <tbody>
           <thead>
            <tr align="center" valign=center>              
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.majorin"/></td> 
              <td valign="middle" class="tableHeader" >学费</td> 
              <td valign="middle" class="tableHeader" >更新日期</td>
              <td valign="middle" class="tableHeader" >住宿费</td> 
              <td valign="middle" class="tableHeader" >更新日期</td>           
            </tr>
            </thead>
           <!--page offset start -->
           <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./stufeeinfoAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <pg:param name="method" />
            <pg:param name="hstudentNo" />           
            <pg:param name="hstuName" /> 		    
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
            <logic:iterate name="feenotpaylist" id="cl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center>               
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.tuitionpayed == '1'}">已缴纳
              </c:when></c:choose>
              <c:choose><c:when test="${cl.tuitionpayed == '0'}"><font color="#990000"><strong>未缴纳</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <bean:write name="cl" property="tupdateTime" formatKey="dateFormat"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.dormfeepayed == '1'}">已缴纳
              </c:when></c:choose>
              <c:choose><c:when test="${cl.dormfeepayed == '0'}"><font color="#990000"><strong>未缴纳</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <bean:write name="cl" property="dupdateTime" formatKey="dateFormat"/>&nbsp;
              </td>                      
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5">               
              <td align="center" valign="middle" bgcolor="#FFFFFF"><bean:write name="cl" property="classNo"/></td>
              <td height="24" align="center" valign="middle" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td> 
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.tuitionpayed == '1'}">已缴纳
              </c:when></c:choose>
              <c:choose><c:when test="${cl.tuitionpayed == '0'}"><font color="#990000"><strong>未缴纳</strong></font>
              </c:when></c:choose>
              </td>
               <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <bean:write name="cl" property="tupdateTime" formatKey="dateFormat"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.dormfeepayed == '1'}">已缴纳
              </c:when></c:choose>
              <c:choose><c:when test="${cl.dormfeepayed == '0'}"><font color="#990000"><strong>未缴纳</strong></font>
              </c:when></c:choose>
              </td>
               <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <bean:write name="cl" property="dupdateTime" formatKey="dateFormat"/>&nbsp;
              </td>                        
            </tr>
            </c:when></c:choose>              
           </pg:item> 
          </logic:iterate>
          <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
          </logic:present> 
          
          <logic:notPresent name="feenotpaylist" scope="request">
          <!--page offset start -->           
		  <pg:pager url="./classfeenotpaypageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <%-- keep track of preference --%>
           <pg:param name="hstudentNo" />           
           <pg:param name="hstuName" />			   
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
          </logic:notPresent>         
          </tbody>
        </table></td>
    </tr>
    <logic:present name="feenotpaylist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
    </td>
    </tr>  
    </logic:present>
</table>

</html:form>
</center>

<script language="JavaScript">

setTimeout('DoInit()',20);

function DoInit(){  
  
  document.all.studentNo.value=document.all.hstudentNo.value;  
  document.all.stuName.value=document.all.hstuName.value;      
   
}

function DoClear(){
     
   document.all.studentNo.value="";
   document.all.stuName.value="";     
         
   document.all.hstudentNo.value="";   
   document.all.hstuName.value="";
      
}

function document.onkeydown()
{
	var e=event.srcElement;
	if(event.keyCode==13)
	{
		DoFind();
		return false;
	}
}

function DoFind(){
   
   document.all.doexl.value="";
   document.forms[0].elements["pager.offset"].value="0";   
   
   document.all.hstudentNo.value=document.all.studentNo.value;   
   document.all.hstuName.value=document.all.stuName.value;   
      
   document.stufeeinfoForm.action="stufeeinfoAction.do?method=classfeenotpaylist";
   document.stufeeinfoForm.submit();
   
}

function DoExport(){

   document.all.doexl.value="1";
   
   document.all.hstudentNo.value=document.all.studentNo.value;   
   document.all.hstuName.value=document.all.stuName.value;   
      
   document.stufeeinfoForm.action="stufeeinfoAction.do?method=classfeenotpaylist";
   document.stufeeinfoForm.submit();

}
</script>