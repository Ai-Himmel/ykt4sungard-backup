<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "gzcheckinmanageAction.do?method=stuinfolist">
<html:errors/>
<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium"><bean:message bundle="checkinmanage" key="checkin.personalinfoviewtitle"/></font></strong></td>
    </tr>
     <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
    
    <tr> 
      <td height="20" align="center" valign="middle" class="medium">&nbsp;</td>
    </tr>
    <tr> 
    <logic:present name="checkinlist"  scope="request">
      <td height="40" align="center" valign="top">
      <logic:iterate name="checkinlist" id="cl" type="java.util.Map" length="1">
      <table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td width=15% height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td width=35% align="left" valign="middle" ><bean:write name="cl" property="studentNo"/></td>
              <td width=15% height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.enrollNo"/></td>
              <td width=35% align="left" valign="middle" ><bean:write name="cl" property="enrollNo"/>&nbsp;</td>
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF"> 
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td align="left" valign="middle" ><bean:write name="cl" property="stuName"/></td>
              <td valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td align="left" valign="middle" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
             <td height="24" valign="middle" class="tableHeader5" >录取院系</td>
              <td align="left" valign="middle"><bean:write name="cl" property="departmentName"/>&nbsp;</td>
              <td height="24" valign="middle" class="tableHeader5" >录取专业</td>
              <td align="left" valign="middle">
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>              
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF">
            <td colspan="4">&nbsp;</td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5">              
              <td valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td align="left" valign="middle" colspan="3">
              <logic:present name="classlist" scope="request"> 
              <logic:iterate name="classlist" id="cls" type="java.util.Map" length="1">
              <bean:write name="cls" property="classNo"/>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF"> 
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.dorm"/></td>
              <td align="left" valign="middle">
              <logic:present name="dormlist" scope="request"> 
              <logic:iterate name="dormlist" id="dls" type="java.util.Map" length="1">
              <bean:write name="dls" property="locationName"/>&nbsp;
              <bean:write name="dls" property="dormitoryName"/>
              </logic:iterate>
              </logic:present>&nbsp;              
              </td>
              <td valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.room"/></td>
              <td align="left" valign="middle" >
              <logic:present name="dormlist" scope="request"> 
              <logic:iterate name="dormlist" id="dls" type="java.util.Map" length="1">
              <bean:write name="dls" property="room"/>
              </logic:iterate>
              </logic:present>&nbsp;
              </td>
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
          </tbody>
        </table>
        </logic:iterate>
       </td>
    </tr>
    </logic:present>
    <logic:notPresent name="checkinlist"  scope="request">
    <tr align="center" valign=center>
           <td align="center" valign="middle" colspan="4"> <font size="2.5" color="#990000">暂无你的个人信息或数据尚未入库！</font></td>
    </tr>
    </logic:notPresent>

</table>

</html:form>
</center>
