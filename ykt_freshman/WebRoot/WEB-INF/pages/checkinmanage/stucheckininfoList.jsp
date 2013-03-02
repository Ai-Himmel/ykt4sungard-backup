<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "checkinmanageAction.do?method=stucheckininfolist">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium"><bean:message bundle="checkinmanage" key="checkin.checkininfotitle"/></font></strong></td>
    </tr>  
    <tr> 
      <td align="center" valign="top" >
      <table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>                      
          <tr align="center" valign=center>
             <td width="15%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
             <td width="35%" align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
            <td width="15%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
            <td align="left" valign="middle" class="tableHeader3" >
                <input type="text" name="stuName" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();">
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
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=maintable>
          <tbody><input name="orderby" type="hidden" value="">
          <input name="doexl" type="hidden" value=""> <input type="hidden" name="method" value="stucheckininfolist">       
        <logic:present name="checkinlist" scope="request">
            <thead>
			<tr align="center" valign=center> 
              <td width="6%" height="24" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')"><bean:message bundle="checkinmanage" key="checkin.studentNo"/></a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('stuName')"><bean:message bundle="checkinmanage" key="checkin.stuName"/></a></td>
              <td width="3%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('gender')"><bean:message bundle="checkinmanage" key="checkin.gender"/></a></td>
              <td width="8%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('majorin')">录取<bean:message bundle="checkinmanage" key="checkin.majorin"/></a></td>              
              <td width="14%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('ifChecked')"><bean:message bundle="checkinmanage" key="checkin.hasChecked3"/></a></td>
              <td width="12%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('ifUnhealthy')"><bean:message bundle="checkinmanage" key="checkin.ifHealthy"/></a></td>
              <td width="8%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('tuitionpayed')"><bean:message bundle="checkinmanage" key="checkin.feePayoff"/></a></td>
              <td width="12%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('ifGotStucard')"><bean:message bundle="checkinmanage" key="checkin.stuCard"/></a></td>
            </tr>
		  </thead>

		  <!--page offset start -->
		  <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./checkinmanageAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <%-- keep track of preference --%> 
            <pg:param name="method" />           
            <pg:param name="hstudentNo" />           
            <pg:param name="hstuName" />
			<pg:param name="orderby" />
			<pg:param name="horder" />
			
            <%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">
            <logic:iterate name="checkinlist" id="cl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="studentNo"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="stuName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>&nbsp;
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
              <c:choose><c:when test="${cl.ifChecked == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notchecked"/></strong></font>
              </c:when></c:choose>              
              <c:choose><c:when test="${cl.ifChecked == '1'}"><bean:message bundle="checkinmanage" key="checkin.checked"/>
              </c:when></c:choose> 
              <c:choose><c:when test="${cl.ifChecked == '9'}">学院经办人签名：
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifChecked == '8'}">复旦学院公章：
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.ifCheckedin == '1'}">
                <c:choose><c:when test="${cl.ifUnhealthy == '0'}"><font color="#990000"><strong>未体检</strong></font>
                </c:when></c:choose>
                <c:choose><c:when test="${cl.ifUnhealthy == '1'}">体检合格
                </c:when></c:choose> 
                <c:choose><c:when test="${cl.ifUnhealthy == '2'}"><font color="#990000"><strong>需复检</strong></font>
                </c:when></c:choose>
                <c:choose><c:when test="${cl.ifUnhealthy == '3'}">复检合格
                </c:when></c:choose>
              </c:when><c:otherwise>
                <c:choose><c:when test="${cl.ifUnhealthy == '9'}">单位经办人签名：
                </c:when></c:choose>
                <c:choose><c:when test="${cl.ifUnhealthy == '8'}">校医疗保健中心公章：
                </c:when></c:choose>
                <c:choose><c:when test="${cl.ifUnhealthy !='8'&&cl.ifUnhealthy !='9'}">
                  <font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/></strong></font>
                </c:when></c:choose>
              </c:otherwise> </c:choose>             
              </td>   
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.ifCheckedin == '1'}">
                <c:choose><c:when test="${cl.tuitionpayed == '1'}">已缴纳 
                </c:when></c:choose>
                <c:choose><c:when test="${cl.tuitionpayed == '0'}"><font color="#990000"><strong>未缴纳</strong></font>
                </c:when></c:choose>
              </c:when><c:otherwise>
                <c:choose><c:when test="${cl.tuitionpayed == '9'}">单位经办人签名：
                </c:when></c:choose>
                <c:choose><c:when test="${cl.tuitionpayed == '8'}">校财务处公章：
                </c:when></c:choose>
                <c:choose><c:when test="${cl.tuitionpayed !='8'&&cl.tuitionpayed !='9'}">
                  <font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/></strong></font>
                 </c:when></c:choose>
              </c:otherwise> </c:choose>
              
              </td>  
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
             <c:choose><c:when test="${cl.ifCheckedin == '1'}">
              <c:choose><c:when test="${cl.ifGotStucard== '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notgiven"/> </strong></font>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotStucard == '1'}"><bean:message bundle="checkinmanage" key="checkin.given"/>
              </c:when></c:choose>
             </c:when><c:otherwise> 
              <c:choose><c:when test="${cl.ifGotStucard == '9'}">单位经办人签名：
               </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotStucard == '8'}">教务处公章：
              </c:when></c:choose>
               <c:choose><c:when test="${cl.ifGotStucard !='8'&&cl.ifGotStucard !='9'}">
                <font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/></strong></font>
              </c:when></c:choose> 
             </c:otherwise> </c:choose>              
              </td>         
            </tr>
            </c:when></c:choose>
            
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" ><bean:write name="cl" property="studentNo"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="stuName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>&nbsp;
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
              <td align="center" valign="middle" bgcolor="#F6F4F5">
               <c:choose><c:when test="${cl.ifChecked == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notchecked"/></strong></font>
              </c:when></c:choose>              
              <c:choose><c:when test="${cl.ifChecked == '1'}"><bean:message bundle="checkinmanage" key="checkin.checked"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifChecked == '9'}">学院经办人签名：
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifChecked == '8'}">复旦学院公章：
              </c:when></c:choose>
              </td>                 
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.ifCheckedin == '1'}">
                <c:choose><c:when test="${cl.ifUnhealthy == '0'}"><font color="#990000"><strong>未体检</strong></font>
                </c:when></c:choose>
                <c:choose><c:when test="${cl.ifUnhealthy == '1'}">体检合格
                </c:when></c:choose> 
                <c:choose><c:when test="${cl.ifUnhealthy == '2'}"><font color="#990000"><strong>需复检</strong></font>
                </c:when></c:choose>
                <c:choose><c:when test="${cl.ifUnhealthy == '3'}">复检合格
                </c:when></c:choose>
              </c:when><c:otherwise>
                <c:choose><c:when test="${cl.ifUnhealthy == '9'}">学院经办人签名：
                </c:when></c:choose>
                <c:choose><c:when test="${cl.ifUnhealthy == '8'}">校医疗保健中心公章：
                </c:when></c:choose>
                <c:choose><c:when test="${cl.ifUnhealthy  !='8'&&cl.ifUnhealthy !='9'}">
                <font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/></strong></font>
                </c:when></c:choose> 
              </c:otherwise> </c:choose>              
              </td>
              
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.ifCheckedin == '1'}">
                <c:choose><c:when test="${cl.tuitionpayed == '1'}">已缴纳
                </c:when></c:choose>
                <c:choose><c:when test="${cl.tuitionpayed == '0'}"><font color="#990000"><strong>未缴纳</strong></font>
                </c:when></c:choose>
              </c:when><c:otherwise> 
                <c:choose><c:when test="${cl.tuitionpayed == '9'}">单位经办人签名：
                </c:when></c:choose>
                <c:choose><c:when test="${cl.tuitionpayed == '8'}">校财务处公章：
                </c:when></c:choose>
                <c:choose><c:when test="${cl.tuitionpayed!='8'&&cl.tuitionpayed!='9'}">
                <font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/></strong></font>
                 </c:when></c:choose>  
              </c:otherwise> </c:choose>             
              </td> 
              
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.ifCheckedin == '1'}">
                <c:choose><c:when test="${cl.ifGotStucard== '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notgiven"/></strong></font>
                </c:when></c:choose>
                <c:choose><c:when test="${cl.ifGotStucard == '1'}"><bean:message bundle="checkinmanage" key="checkin.given"/>
                </c:when></c:choose>
              </c:when><c:otherwise>               
                <c:choose><c:when test="${cl.ifGotStucard == '9'}">单位经办人签名：
                </c:when></c:choose>
                <c:choose><c:when test="${cl.ifGotStucard == '8'}">教务处公章：
                </c:when></c:choose>
                <c:choose><c:when test="${cl.ifGotStucard!='8'&&cl.ifGotStucard!='9'}">             
                  <font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/></strong></font>
                 </c:when></c:choose> 
              </c:otherwise> </c:choose>               
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
          <logic:notPresent name="checkinlist" scope="request">
           <pg:pager url="./stucheckininfopageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
            <%-- keep track of preference --%>
            
            <pg:param name="hstudentNo" />           
            <pg:param name="hstuName" />
			<pg:param name="orderby" />
			<pg:param name="horder" />			
            <%-- save pager offset during form changes --%>
		    <input type="hidden" name="pager.offset" value="0">
		    <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
		  </tbody>
        </table></td>
    </tr> 
          </logic:notPresent>
            
    <logic:present name="checkinlist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">共<%=rowcount-2%>条记录</font>
    </td>
    </tr>  
    </logic:present>  
</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>
<logic:present name="order" scope="request">
  <input name="horder" type="hidden" value="<bean:write name="order" />"> 
  </logic:present>
  <logic:notPresent name="order" scope="request">
  <input name="horder" type="hidden" value="a"> 
</logic:notPresent>
</html:form>
</center>

<script language="JavaScript">

setTimeout('init()',30);

function init(){

document.all.studentNo.value=document.all.hstudentNo.value;  
document.all.stuName.value=document.all.hstuName.value; 
  
if(document.all.hmsg.value=='1')
      alert("导出Excel成功!");
else if(document.all.hmsg.value=='0')
      alert("无内容!");
      
 
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
   
   document.stucheckininfoForm.action="checkinmanageAction.do?method=stucheckininfolist";
   document.stucheckininfoForm.submit();
   
}

function DoExport(){

document.all.doexl.value="1";
document.all.hstudentNo.value=document.all.studentNo.value;   
document.all.hstuName.value=document.all.stuName.value;
document.stucheckininfoForm.action="checkinmanageAction.do?method=stucheckininfoexcel";
document.stucheckininfoForm.submit();

}

function DoSort(col){
  document.all.doexl.value="";
  document.all.orderby.value=col;
  if(document.all.horder.value=='a')
      document.all.horder.value='d';
  else if(document.all.horder.value=='d')
      document.all.horder.value='a';
      
  document.stucheckininfoForm.action="checkinmanageAction.do?method=stucheckininfolist";
  document.stucheckininfoForm.submit();
}
</script>
