<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "ygstufeeinfoAction.do?method=stuview">
<html:errors/>
<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">缴费信息</font></strong></td>
    </tr>
     <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
    
    <tr> 
      <td height="20" align="center" valign="middle" class="medium">&nbsp;</td>
    </tr>
    <tr> 
    <logic:present name="stuinfolist"  scope="request">
      <td height="40" align="center" valign="top"><input name="updateid" type="hidden" value="">
      <logic:iterate name="stuinfolist" id="sl" type="java.util.Map">
      <table 
        width=80% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
            <tr align="center" valign=center> 
              <td width="15%" height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td width="65%" align="left" valign="middle" bgcolor="#FFFFFF" colspan="4"><bean:write name="sl" property="studentNo"/></td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td width="15%" height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" colspan="2"><bean:write name="sl" property="stuName"/></td>
              <td width="15%" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td width="25%" align="left" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${sl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${sl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
            </tr>
            <tr align="center" valign=center> 
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.college"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" colspan="2">
              <logic:present name="collegelist" scope="request">            
               <logic:iterate name="collegelist" id="col" type="org.king.classmanage.domain.Department">
                <c:choose><c:when test="${col.deptCode == sl.curCollege}">              
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
                <c:choose><c:when test="${ml.dictValue == sl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>              
            </tr>
            </logic:iterate>
            </logic:present>
            
            <tr align="center" valign=center>               
              <td colspan="5" align="left" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
            </tr>
                     
          <logic:present name="dormfeelist"  scope="request">
          <logic:iterate name="dormfeelist" id="dl" type="java.util.Map">
          <tr align="center" valign=center> 
            <td width=15% height="30" rowspan="2" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >住宿费</td>
            <td width=15% height="24" align="right" valign="middle" class="tableHeader2" >应交</td>
            <td align="left" valign="middle" class="tableHeader3" colspan="3" ><bean:write name="dl" property="shouldPay"/></td>
          </tr>
          <tr align="center" valign=center> 
            <td height="24" align="right" valign="middle" bgcolor="#F6F4F5" class="tableHeader2" ><font color="#FF0000">已交</font></td>
            <td align="left" valign="middle" class="tableHeader3" colspan="3" bgcolor="#F6F4F5"><bean:write name="dl" property="exactPay"/></td>
          </tr>
          </logic:iterate>
          </logic:present>        
        
          </tbody>
        </table>        
       </td>
    </tr>

    <logic:notPresent name="dormfeelist"  scope="request">
     <c:if test="${requestAvailable == '2'}">
     	<tr align="center" valign="center"><td><font size="2.5" color="#990000">您不符合在校住宿的条件，因此没有您的住宿费信息</font></td></tr>
     </c:if>
     <c:if test="${requestAvailable == '1'&&residentNeed == '2'}">
     	<tr align="center" valign="center"><td><font size="2.5" color="#990000">您没有申请在校住宿，因此没有您的住宿费信息</font></td></tr>
     </c:if>
     <c:if test="${requestAvailable == '1'&&residentNeed == '1'}">
     	<tr align="center" valign="center"><td><font size="2.5" color="#990000">暂无您的住宿费信息</font></td></tr>
     </c:if>
    </logic:notPresent>   

</table>

</html:form>
</center>
