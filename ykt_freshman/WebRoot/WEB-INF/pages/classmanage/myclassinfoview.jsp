<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "checkinmanageAction.do?method=myclassinfoview">
<html:errors/>
<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">本班信息查询</font></strong></td>
    </tr>
     <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
    
    <tr> 
      <td height="20" align="center" valign="middle" class="medium">&nbsp;</td>
    </tr>
    <tr> 
    <logic:present name="classlist"  scope="request">
      <td height="40" align="center" valign="top">
      <logic:iterate name="classlist" id="cl" type="java.util.Map" length="1">
      <table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>            
            <tr align="center" valign=center bgcolor="#F6F4F5">
              <td width=15% height="24" valign="middle" class="tableHeader5" >书院</td>
              <td width=35% align="left" valign="middle" >              
              <bean:write name="cl" property="collegeName"/>              
              &nbsp;
              </td>
              <td width=15% height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td width=35% align="left" valign="middle" >              
              <bean:write name="cl" property="classNo"/>
              &nbsp;
              </td>
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF">
              <td height="24" valign="middle" class="tableHeader5" >书院简介</td>
              <td align="left" valign="middle" colspan="3">              
              <bean:write name="cl" property="introduction"/>              
              &nbsp;
              </td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5">              
              <td height="24" valign="middle" class="tableHeader5" >学工组组长姓名</td>
              <td align="left" valign="middle" >
              <logic:present name="supermanagerlist" scope="request"> 
              <logic:iterate name="supermanagerlist" id="smls" type="java.util.Map" length="1">
              <bean:write name="smls" property="managerName"/>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>
              <td height="24" valign="middle" class="tableHeader5" >学工组长联系方式</td>
              <td align="left" valign="middle" >
              <logic:present name="supermanagerlist" scope="request"> 
              <logic:iterate name="supermanagerlist" id="smls" type="java.util.Map" length="1">
              <bean:write name="smls" property="contact"/>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>
            </tr>           
            <tr align="center" valign=center bgcolor="#FFFFFF">              
              <td valign="middle" class="tableHeader5">学工组组长简介</td>
              <td align="left" valign="middle" colspan="3" >
              <logic:present name="supermanagerlist" scope="request"> 
              <logic:iterate name="supermanagerlist" id="smls" type="java.util.Map" length="1">
              <bean:write name="smls" property="introduction"/>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>              
            </tr>
            
            <tr align="center" valign=center bgcolor="#FFFFFF">
            <td colspan="4">&nbsp;</td>
            </tr>            
            
            <tr align="center" valign=center bgcolor="#F6F4F5">              
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.managerName"/></td>
              <td align="left" valign="middle" >
              <logic:present name="managerlist" scope="request"> 
              <logic:iterate name="managerlist" id="mls" type="java.util.Map" length="1">
              <bean:write name="mls" property="managerName"/>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.contact"/></td>
              <td align="left" valign="middle" >
              <logic:present name="managerlist" scope="request"> 
              <logic:iterate name="managerlist" id="mls" type="java.util.Map" length="1">
              <bean:write name="mls" property="contact"/>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>
            </tr>           
            <tr align="center" valign=center bgcolor="#FFFFFF">              
              <td valign="middle" class="tableHeader5"><bean:message bundle="checkinmanage" key="checkin.introduction"/></td>
              <td align="left" valign="middle" colspan="3" >
              <logic:present name="managerlist" scope="request"> 
              <logic:iterate name="managerlist" id="mls" type="java.util.Map" length="1">
              <bean:write name="mls" property="introduction"/>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>              
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5">              
              <td height="24" valign="middle" class="tableHeader5" >导师姓名</td>
              <td align="left" valign="middle" >
              <logic:present name="tutorlist" scope="request"> 
              <logic:iterate name="tutorlist" id="tls" type="java.util.Map" indexId="i">
              <c:choose><c:when test="${i== 0}">
              <bean:write name="tls" property="managerName"/>
              </c:when></c:choose>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>
              <td height="24" valign="middle" class="tableHeader5" >导师联系方式</td>
              <td align="left" valign="middle" >
              <logic:present name="tutorlist" scope="request"> 
              <logic:iterate name="tutorlist" id="tls" type="java.util.Map" indexId="i">
              <c:choose><c:when test="${i== 0}">
              <bean:write name="tls" property="contact"/>
              </c:when></c:choose>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF">              
              <td valign="middle" class="tableHeader5">导师简介</td>
              <td align="left" valign="middle" colspan="3">
              <logic:present name="tutorlist" scope="request"> 
              <logic:iterate name="tutorlist" id="tls" type="java.util.Map" indexId="i">
              <c:choose><c:when test="${i== 0}">
              <bean:write name="tls" property="introduction"/>
              </c:when></c:choose>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>              
            </tr>  
            <tr align="center" valign=center bgcolor="#F6F4F5">              
              <td height="24" valign="middle" class="tableHeader5" >导师姓名</td>
              <td align="left" valign="middle" >
              <logic:present name="tutorlist" scope="request"> 
              <logic:iterate name="tutorlist" id="tls" type="java.util.Map" indexId="i">
              <c:choose><c:when test="${i== 1}">
              <bean:write name="tls" property="managerName"/>
              </c:when></c:choose>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>
              <td height="24" valign="middle" class="tableHeader5" >导师联系方式</td>
              <td align="left" valign="middle" >
              <logic:present name="tutorlist" scope="request"> 
              <logic:iterate name="tutorlist" id="tls" type="java.util.Map" indexId="i">
              <c:choose><c:when test="${i== 1}">
              <bean:write name="tls" property="contact"/>
              </c:when></c:choose>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF">              
              <td valign="middle" class="tableHeader5">导师简介</td>
              <td align="left" valign="middle" colspan="3">
              <logic:present name="tutorlist" scope="request"> 
              <logic:iterate name="tutorlist" id="tls" type="java.util.Map" indexId="i">
              <c:choose><c:when test="${i== 1}">
              <bean:write name="tls" property="introduction"/>
              </c:when></c:choose>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>              
            </tr>                                              
          </tbody>
        </table>
        </logic:iterate>
       </td>
    </tr>
    </logic:present>
    <logic:notPresent name="classlist"  scope="request">
    <tr align="center" valign=center>
           <td align="center" valign="middle" colspan="4"> <font size="2.5" color="#990000">暂无您班级的信息或者您不是任何班的辅导员或导师！</font></td>
    </tr>
    </logic:notPresent>

</table>

</html:form>
</center>

