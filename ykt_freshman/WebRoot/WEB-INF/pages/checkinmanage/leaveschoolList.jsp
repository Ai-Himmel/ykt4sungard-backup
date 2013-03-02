<%@page pageEncoding="GBK"%>
<%@ page import="java.util.Date" %>
<%@ page import="java.text.SimpleDateFormat" %>

<%
  Date now = new Date();

  SimpleDateFormat formatter1 = new SimpleDateFormat ("HH':'mm':'ss");
  String dateStr = formatter1.format(now);
  String hour = dateStr.substring(0,2);
  String minute = dateStr.substring(3,5);
  String second = dateStr.substring(6,8);
%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "checkinmanageAction.do?method=addleaveschool">
<html:errors/>
<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium"><bean:message bundle="checkinmanage" key="checkin.leaveschooltitle"/></font></strong></td>
    </tr>
    
    <tr> 
      <td align="center" valign="top" >
      <table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
           <logic:notPresent name="stuinfo" scope="request">
          <tr align="center" valign=center> 
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.enrollNo"/></td>
            <td align="left" valign="middle" class="tableHeader3" colspan="3">            
                <input 
                name="stucheckininfo.enrollNo" class="input_box"  maxlength=50 value="" >&nbsp;
                <input name="searchstu" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.search"/>" onClick="ShowName()">
                </td>
          </tr>            
          <tr align="center" valign=center>
            <td align="left" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
            <td align="left" valign="middle" class="tableHeader3" >
                <input 
                name="stuName" class="input_box" style="background:#ECE6E6" maxlength=50 value="" readonly="true" >
            </td>
            <td align="left" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
            <td align="left" valign="middle" class="tableHeader3" >
                <input 
                name="classNo" class="input_box" style="background:#ECE6E6" maxlength=50 value="" readonly="true" >
            </td>
          </tr>
          
          </tbody>
     </table>
     </td>
    </tr>
    
    <tr> 
      <td height="30" align="right" valign="middle" class="tdborder02"> 
        &nbsp; 
      </td>
    </tr>
    </logic:notPresent>
    <logic:present name="stuinfo" scope="request">  
          <tr align="center" valign=center> 
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.enrollNo"/></td>
            <td align="left" valign="middle" class="tableHeader3" colspan="3">          
              <logic:iterate name="stuinfo" id="si" type="java.util.Map" length="1">
                <input id="eNo" name="stucheckininfo.enrollNo" class="input_box"  maxlength=50 value="<bean:write name="si" property="enrollNo"/>" >&nbsp;
                <input name="searchstu" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.search"/>" onClick="ShowName()">
                </td>
              </logic:iterate>
          </tr>
            </logic:present>
            <logic:present name="stuinfo" scope="request">
              <td align="left" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td align="left" valign="middle" class="tableHeader3" >
              <logic:iterate name="stuinfo" id="si" type="java.util.Map" length="1">
                <input 
                name="stuName" class="input_box"  maxlength=50 value="<bean:write name="si" property="stuName"/>"  style="background:#ECE6E6" disabled></td>
              </logic:iterate>                                    
              <td align="left" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td align="left" valign="middle" class="tableHeader3" >
              <logic:iterate name="stuinfo" id="si" type="java.util.Map" length="1">
                <input 
                name="classNo" class="input_box"  maxlength=50 value="<bean:write name="si" property="classNo"/>"  style="background:#ECE6E6" disabled></td>
              <input name="stucheckininfo.studentNo" type="hidden" value="<bean:write name="si" property="studentNo"/>">
              <input name="stucheckininfo.enrollYear" type="hidden" value="<bean:write name="si" property="enrollYear"/>">
              <input name="stucheckininfo.ifCheckedin" type="hidden" value="<bean:write name="si" property="ifCheckedin"/>">
              <input name="stucheckininfo.ifChecked" type="hidden" value="<bean:write name="si" property="ifChecked"/>">
              <input name="stucheckininfo.ifGotMaterial" type="hidden" value="<bean:write name="si" property="ifGotMaterial"/>">
              <input name="stucheckininfo.ifGotEcard" type="hidden" value="<bean:write name="si" property="ifGotEcard"/>">
              <input name="stucheckininfo.ifGotStucard" type="hidden" value="<bean:write name="si" property="ifGotStucard"/>">
              <input name="stucheckininfo.reason" type="hidden" value="<bean:write name="si" property="reason"/>">
              <input name="stucheckininfo.memo" type="hidden" value="<bean:write name="si" property="memo"/>">
              <input name="stucheckininfo.ifReserve" type="hidden" value="<bean:write name="si" property="ifReserve"/>">
              <input name="stucheckininfo.ifLeaveSchool" type="hidden" value="<bean:write name="si" property="ifLeaveSchool"/>">
              <input name="stucheckininfo.ifSubmitted" type="hidden" value="<bean:write name="si" property="ifSubmitted"/>">
              <input name="stucheckininfo.updatorId" type="hidden" value="<%=(String)session.getAttribute("userName")%>">
              <input name="stucheckininfo.id" type="hidden" value="<bean:write name="si" property="id"/>">
              
              </logic:iterate> 
          </tr>
          
          </tbody>
     </table>
     </td>
    </tr>
    
    <tr> 
      <td height="30" align="right" valign="middle" class="tdborder02"> 
        <input name="Submit" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.add"/>" onClick="DoAdd()"> 
      </td>
    </tr>
    </logic:present>
    <tr> 
      <td height="30" align="left" valign="middle" class="medium">
      <span class="medium">&nbsp;</span></td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input name="updateid" type="hidden" value="">
            <tr align="center" valign=center> 
              <td height="24" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.enrollNo"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.majorin"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.state"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.reason2"/></td>
              <td valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.cancel"/></td>
            </tr>
            <logic:present name="checkinlist" scope="request">
            <logic:iterate name="checkinlist" id="cl" type="java.util.Map"  indexId="i">
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="studentNo"/></td>
               <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="enrollNo"/></td>
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
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.ifCheckedin == '0'}"><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifCheckedin == '1'}"><bean:message bundle="checkinmanage" key="checkin.checkedin"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.leaveschool"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <input name="cancelReserve" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.cancel"/>" onClick="DoCancel('<bean:write name="cl" property="id"/>')">
              </td>
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="enrollNo"/></td>
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
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:write name="cl" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <c:choose><c:when test="${cl.ifCheckedin == '0'}"><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifCheckedin == '1'}"><bean:message bundle="checkinmanage" key="checkin.checkedin"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5"><bean:message bundle="checkinmanage" key="checkin.leaveschool"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <input name="cancelReserve" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.cancel"/>" onClick="DoCancel('<bean:write name="cl" property="id"/>')">
              </td>
            </tr>
            </c:when></c:choose>
              <input name="enrollNo<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="enrollNo"/>">
              <input name="studentNo<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="studentNo"/>">
              <input name="enrollYear<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="enrollYear"/>">
              <input name="ifCheckedin<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifCheckedin"/>">
              <input name="ifChecked<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifChecked"/>">
              <input name="ifGotMaterial<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifGotMaterial"/>">
              <input name="ifGotEcard<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifGotEcard"/>">
              <input name="ifGotStucard<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifGotStucard"/>">
              <input name="reason<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="reason"/>">
              <input name="memo<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="memo"/>">
              <input name="ifReserve<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifReserve"/>">
              <input name="ifLeaveSchool<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifLeaveSchool"/>">
              <input name="ifSubmitted<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifSubmitted"/>">
              <input name="updatorId<bean:write name="cl" property="id"/>" type="hidden" value="<%=(String)session.getAttribute("userName")%>"> 
          </logic:iterate>
          </logic:present>          
          </tbody>
        </table></td>
    </tr>

</table>

</html:form>
</center>


<script language="JavaScript">

function ShowName(){
    //alert("ok");
    document.stucheckininfoForm.action="checkinmanageAction.do?method=findstuinfo_leaveschool";
    document.stucheckininfoForm.submit();
}

function DoAdd(){

  if(document.forms[0].elements["stucheckininfo.ifReserve"].value=='1'){
      alert("该生已保留入学资格，请撤销原状态后再添加！");
      return;
  }
  if(document.forms[0].elements["stucheckininfo.ifLeaveSchool"].value=='1'){
      alert("该生已登记放弃入学资格！");
      return;
  }
  
  //document.all.eNo.blur();       
  document.stucheckininfoForm.action="checkinmanageAction.do?method=addleaveschool";
  document.stucheckininfoForm.submit();  
     
}

function DoCancel(str){

  if(confirm("您确定要撤销吗？")){
   document.all.updateid.value=str;
   
   document.stucheckininfoForm.action="checkinmanageAction.do?method=cancelleaveschool";
   document.stucheckininfoForm.submit();
  }
  else
    return;
}

</script>