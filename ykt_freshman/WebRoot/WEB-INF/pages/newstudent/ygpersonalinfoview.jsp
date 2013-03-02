<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "ygcheckinmanageAction.do?method=stuinfolist">
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
        width=80% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
            <tr align="center" valign=center> 
              <td width="15%" height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td width="65%" align="left" valign="middle" bgcolor="#FFFFFF" colspan="3"><bean:write name="cl" property="studentNo"/></td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td width="15%" height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="stuName"/></td>
              <td width="15%" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
            </tr>
            
            <tr align="center" valign=center> 
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.college"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" >
              <logic:present name="collegeList" scope="request">            
               <logic:iterate name="collegeList" id="col" type="org.king.classmanage.domain.Department">
                <c:choose><c:when test="${col.deptCode == cl.curCollege}">              
                <bean:write name="col" property="deptName"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>  
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.majorin"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF">
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
            
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.dorm"/></td>
              <td align="left" valign="middle">
              <logic:present name="dormlist" scope="request"> 
              <logic:iterate name="dormlist" id="dls" type="java.util.Map" length="1">
              <bean:write name="dls" property="area"/>&nbsp;&nbsp;
              <bean:write name="dls" property="location"/>&nbsp;&nbsp;
              <bean:write name="dls" property="dorm"/>&nbsp;&nbsp;
              <bean:write name="dls" property="unit"/>单元
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
            </logic:iterate>
    </logic:present>


</table>
    <logic:notPresent name="checkinlist"  scope="request">
    <tr align="center" valign=center>
           <td align="center" valign="middle" colspan="4"> <font size="2.5" color="#990000">暂无你的个人信息或数据尚未入库！</font></td>
    </tr>
    </logic:notPresent>
    <logic:present name="checkinlist"  scope="request">
	<logic:notPresent name="dormlist"  scope="request">
    <tr align="center" valign=center>
           <td align="center" valign="middle" colspan="4"> <font size="2.5" color="#990000">暂无你的个人宿舍信息或您未参与住宿分配！</font></td>
    </tr>
	</logic:notPresent>
	</logic:present>
</html:form>
</center>
