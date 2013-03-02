<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "ygcheckinmanageAction.do?method=stuinfolist">
<html:errors/>
<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">个人住宿分配结果</font></strong></td>
    </tr>
     <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
    
    <tr> 
      <td height="20" align="center" valign="middle" class="medium">&nbsp;</td>
    </tr>
    <tr>       <td height="40" align="center" valign="top">
    <logic:present name="singleInfoList"  scope="request">
      <logic:iterate name="singleInfoList" id="cl" type="java.util.Map" length="1">
      <table 
        width=80% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
            <tr align="center" valign=center> 
              <td width="15%" height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td width="65%" align="left" valign="middle" bgcolor="#FFFFFF" colspan="3"><bean:write name="cl" property="stuNo"/></td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td width="15%" height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="stuName"/></td>
              <td width="15%" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.sex == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.sex == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF"> 
              <td width=15% height="24" valign="middle" class="tableHeader5" >校区</td>
              <td width=18% align="left" valign="middle" ><bean:write name="cl" property="area"/></td>
              <td width=15% height="24" valign="middle" class="tableHeader5" >区域</td>
              <td width=18% align="left" valign="middle" ><bean:write name="cl" property="location"/>&nbsp;</td>
            </tr>          
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td width=15% height="24" valign="middle" class="tableHeader5" >楼号</td>
              <td width=18% align="left" valign="middle" ><bean:write name="cl" property="dormitory"/>&nbsp;</td>
              <td width=15% height="24" valign="middle" class="tableHeader5" >单元号</td>
              <td width=18% align="left" valign="middle" ><bean:write name="cl" property="unit"/></td>
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF"> 
              <td width=15% height="24" valign="middle" class="tableHeader5" >房间号</td>
              <td width=18% align="left" valign="middle" ><bean:write name="cl" property="roomNumber"/>&nbsp;</td>
              <td width=15% height="24" valign="middle" class="tableHeader5" >住宿费用</td>
              <td width=18% align="left" valign="middle" ><bean:write name="cl" property="fee"/>&nbsp;元RMB</td>
            </tr>
            </tbody></table>
            </logic:iterate>
    </logic:present></td></tr>
    <logic:notPresent name="singleInfoList"  scope="request">
    <tr align="center" valign=center>
           <td align="center" valign="middle" colspan="4"> <font size="2.5" color="#990000">暂无你的个人住宿信息或您没有参与宿舍分配！</font></td>
    </tr>
    </logic:notPresent>

</table>

</html:form>
</center>
