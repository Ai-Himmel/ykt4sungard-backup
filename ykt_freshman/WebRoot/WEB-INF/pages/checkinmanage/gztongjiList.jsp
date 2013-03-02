<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>
<html:form action = "gzcheckinsubminAction.do?method=tongjisubmit">
<html:errors/>
<br>
<input type="hidden" name="myAction" value="gzcheckinmanageAction.do?method=tongjilist">
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium"><bean:message bundle="checkinmanage" key="checkin.tongjititle"/></font></strong></td>
    </tr>
    <tr> 
      <td height="30" align="left" valign="middle" class="medium">&nbsp;</td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input name="updateid" type="hidden" value="">
          <input name="updateclassNo" type="hidden" value="">  
          <input name="viewclassNo" type="hidden" value="">        
            <tr align="center" valign=center> 
              <td width=6% height="24" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td width=6% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.shouldcheckinNum"/></td>
              <td width=6% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.exactcheckinNum"/></td>
              <td width=6% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.notcheckinNum"/></td>
              <td width=6% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.askforlateNum"/></td>
              <td width=12% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.askReserveNum"/></td>
              <td width=11% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.noreasonNum"/></td>
              <td width=6% valign="middle" class="tableHeader" >明确不来人数</td>              
            <logic:notPresent name="tjlist" scope="request">
            </tr>
            </logic:notPresent>
              
            <logic:present name="tjlist" scope="request">
            <td width=6% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.submitstate"/></td>            
            <td width=6% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.backto"/></td>
            <td width=6% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.submitto"/></td>
            </tr>
            <logic:iterate name="tjlist" id="tj" type="java.util.Map" indexId="i">
            <c:choose><c:when test="${i%2 != 0}">
            
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="tj" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.shouldcheckinNum != null}">      
                <bean:write name="tj" property="shouldcheckinNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.exactcheckinNum != null}">      
                <bean:write name="tj" property="exactcheckinNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.notcheckinNum != null}">      
                <a href="javascript:DoNotcheckinView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="notcheckinNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.askforlateNum != null}">      
                <a href="javascript:DoAskforlateView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="askforlateNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.askreserveNum != null}">      
                <a href="javascript:DoAskreserveView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="askreserveNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>             
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.noreasonNum != null}">      
                <a href="javascript:DoNoreasonView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="noreasonNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
               <c:choose><c:when test="${tj.notcomeNum != null}">      
                <a href="javascript:DoNotcomeView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="notcomeNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>    
              </td>              
              <c:choose><c:when test="${tj.ifSubmitted =='1'}"><!-- 已提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.submitted"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="backto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.backto"/>" onClick="DoBack('<bean:write name="tj" property="classNo"/>','<bean:write name="tj" property="csid"/>')" >
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="submitto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.submitto"/>" onClick="DoSubmit('<bean:write name="tj" property="classNo"/>','<bean:write name="tj" property="csid"/>')" disabled>
              </td>
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted =='0'}"><!-- 已退回过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.notsubmitted"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="backto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.backto"/>" onClick="DoBack('<bean:write name="tj" property="classNo"/>','<bean:write name="tj" property="csid"/>')" disabled>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="submitto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.submitto"/>" onClick="DoSubmit('<bean:write name="tj" property="classNo"/>','<bean:write name="tj" property="csid"/>')" >
              </td>
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted ==null}"><!-- 从未提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.notsubmitted"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="backto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.backto"/>" onClick="DoBack('<bean:write name="tj" property="classNo"/>',null)" disabled>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="submitto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.submitto"/>" onClick="DoSubmit('<bean:write name="tj" property="classNo"/>',null)" >
              </td>
              </c:when></c:choose>
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="tj" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.shouldcheckinNum != null}">      
                <bean:write name="tj" property="shouldcheckinNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.exactcheckinNum != null}">      
                <bean:write name="tj" property="exactcheckinNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.notcheckinNum != null}">      
                <a href="javascript:DoNotcheckinView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="notcheckinNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.askforlateNum!= null}">      
                <a href="javascript:DoAskforlateView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="askforlateNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.askreserveNum != null}">      
                <a href="javascript:DoAskreserveView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="askreserveNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>             
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.noreasonNum !=null}">      
                <a href="javascript:DoNoreasonView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="noreasonNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
               <c:choose><c:when test="${tj.notcomeNum != null}">      
                <a href="javascript:DoNotcomeView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="notcomeNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>    
              </td>             
              <c:choose><c:when test="${tj.ifSubmitted =='1'}"><!-- 已提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.submitted"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="backto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.backto"/>" onClick="DoBack('<bean:write name="tj" property="classNo"/>','<bean:write name="tj" property="csid"/>')" >
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="submitto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.submitto"/>" onClick="DoSubmit('<bean:write name="tj" property="classNo"/>','<bean:write name="tj" property="csid"/>')" disabled>
              </td>                         
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted =='0'}"><!-- 已退回过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.notsubmitted"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="backto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.backto"/>" onClick="DoBack('<bean:write name="tj" property="classNo"/>','<bean:write name="tj" property="csid"/>')" disabled>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="submitto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.submitto"/>" onClick="DoSubmit('<bean:write name="tj" property="classNo"/>','<bean:write name="tj" property="csid"/>')" >
              </td>              
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted ==null}"><!-- 从未提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.notsubmitted"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="backto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.backto"/>" onClick="DoBack('<bean:write name="tj" property="classNo"/>',null)" disabled>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="submitto" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.submitto"/>" onClick="DoSubmit('<bean:write name="tj" property="classNo"/>',null)" >
              </td>
              </c:when></c:choose>
            </tr>   
            </c:when></c:choose>                      
           </logic:iterate>
           <logic:present name="tjlisttotal" scope="request">
           <logic:iterate name="tjlisttotal" id="tjt" type="java.util.Map">
           <tr align="center" valign=center bgcolor="#FF9999"> 
              <td height="24" align="center" valign="middle"><bean:message bundle="checkinmanage" key="checkin.totalNum"/></td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.shouldcheckinNumtotal != null}"> 
              <bean:write name="tjt" property="shouldcheckinNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.exactcheckinNumtotal != null}">
              <bean:write name="tjt" property="exactcheckinNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.notcheckinNumtotal != null}">
              <bean:write name="tjt" property="notcheckinNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>              
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.askforlateNumtotal != null}">
              <bean:write name="tjt" property="askforlateNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.askreserveNumtotal != null}">
              <bean:write name="tjt" property="askreserveNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.noreasonNumtotal != null}">
              <bean:write name="tjt" property="noreasonNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.notcomeNumtotal != null}">
              <bean:write name="tjt" property="notcomeNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>              
              <td align="center" valign="middle">--</td>
              <td align="center" valign="middle">--</td>
              <td align="center" valign="middle">--</td>              
           </logic:iterate> 
           </logic:present>  
           </logic:present>         
          </tbody>
        </table></td>
    </tr>   

</table>

</html:form>
</center>

<script language="JavaScript">

function DoBack(str,strid){

  document.all.updateclassNo.value=str;
  document.all.updateid.value=strid;
  
  document.checkinsubminForm.action="gzcheckinsubminAction.do?method=tongjibackto";
  document.checkinsubminForm.submit();
}

function DoSubmit(str,strid){
  
  document.all.updateclassNo.value=str;
  document.all.updateid.value=strid;
  
  document.checkinsubminForm.action="gzcheckinsubminAction.do?method=tongjisubmit";
  document.checkinsubminForm.submit();

}

function DoNotcheckinView(str){
  document.all.viewclassNo.value=str;
  document.checkinsubminForm.action="gzcheckinsubminAction.do?method=notcheckinstu";
  document.checkinsubminForm.submit();
}

function DoAskforlateView(str){
  document.all.viewclassNo.value=str;
  document.checkinsubminForm.action="gzcheckinsubminAction.do?method=askforlatestu";
  document.checkinsubminForm.submit();
}

function DoAskreserveView(str){
  document.all.viewclassNo.value=str;
  document.checkinsubminForm.action="gzcheckinsubminAction.do?method=askreservestu";
  document.checkinsubminForm.submit();

}

function DoNoreasonView(str){

  document.all.viewclassNo.value=str;
  document.checkinsubminForm.action="gzcheckinsubminAction.do?method=noreasonstu";
  document.checkinsubminForm.submit();

}

function DoNotcomeView(str){

  document.all.viewclassNo.value=str;
  document.checkinsubminForm.action="gzcheckinsubminAction.do?method=donotcomestu";
  document.checkinsubminForm.submit();

}

</script>