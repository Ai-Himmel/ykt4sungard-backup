<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "gzstufeeinfoAction.do?method=stuview">
<html:errors/>
<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium"><bean:message bundle="checkinmanage" key="checkin.searchviewtitle"/></font></strong></td>
    </tr>
     <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
    
    <tr> 
      <td height="20" align="center" valign="middle" class="medium">&nbsp;</td>
    </tr>
    <tr> 
    <logic:present name="checkinlist"  scope="request">
      <td height="40" align="center" valign="top"><input name="updateid" type="hidden" value="">
      <logic:iterate name="checkinlist" id="cl" type="java.util.Map" length="1">
      <table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
            <tr align="center" valign=center bgcolor="#FFFFFF"> 
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="studentNo"/></td>
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="stuName"/></td>
            </tr>            
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.majorin"/></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" >
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="classNo"/></td>
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF" >               
              <td colspan="4" align="left" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td width="15%" height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.state"/>
                </td>
              <td width="35%" align="left" valign="middle" bgcolor="#F6F4F5"  >
              <c:choose><c:when test="${cl.ifCheckedin == '1'}"><bean:message bundle="checkinmanage" key="checkin.checkedin"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifCheckedin == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/></strong></font>
              </c:when></c:choose>
              </td>
              <td width="15%" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.hasChecked2"/></td>
              <td width="35%" align="left" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.ifChecked == '1'}">已核验
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifChecked == '0'}"><font color="#990000"><strong>未核验</strong></font>
              </c:when></c:choose>
              </td>
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF"> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader5" >资料领取</td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.ifGotMaterial == '1'}">已领取
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotMaterial == '0'}"><font color="#990000"><strong>未领取</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader5" >缴费</td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><a href="javascript:DoView('<bean:write name="cl" property="studentNo"/>')">查看详细信息</a></td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" class="tableHeader5" >档案袋</td>
              <td align="left" valign="middle" >
              <c:choose><c:when test="${cl.hasArchives == '1'}">已上交
              </c:when></c:choose>
              <c:choose><c:when test="${cl.hasArchives == '0'}"><font color="#990000"><strong>未上交</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" class="tableHeader5" >新生档案</td>
              <td align="left" valign="middle" >
              <c:choose><c:when test="${cl.hasStuarchive == '1'}">已核对&nbsp;
              </c:when></c:choose>
              <c:choose><c:when test="${cl.hasStuarchive == '0'}"><font color="#990000"><strong>未核对</strong></font>&nbsp;
              </c:when></c:choose> 
              <c:choose><c:when test="${cl.archiveSubmit == '1'}">已入库
              </c:when></c:choose>
              <c:choose><c:when test="${cl.archiveSubmit == '0'}"><font color="#990000"><strong>未入库</strong></font>
              </c:when></c:choose> 
              </td>
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF"> 
              <td height="24" align="center" valign="middle" class="tableHeader5" >体检</td>              
              <td align="left" valign="middle" >
              <c:choose><c:when test="${cl.ifUnhealthy == '0'}"><font color="#990000"><strong>未体检</strong></font>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '1'}">体检合格
              </c:when></c:choose> 
              <c:choose><c:when test="${cl.ifUnhealthy == '2'}"><font color="#990000"><strong>需复检</strong></font>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '3'}">复检合格
              </c:when></c:choose>
              </td>              
              <td align="center" valign="middle" class="tableHeader5" >一卡通拍照</td>
              <td align="left" valign="middle" >
              <logic:present name="ecardphotolist"  scope="request">
              <logic:iterate name="ecardphotolist" id="el" type="java.util.Map">
              <c:choose><c:when test="${el.ecardPhoto == '1'}">已完成
              </c:when><c:otherwise>
              <font color="#990000"><strong>未完成</strong></font>   
              </c:otherwise></c:choose>           
              </logic:iterate>
              </logic:present>&nbsp;
              </td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td align="center" valign="middle" class="tableHeader5" >正式一卡通</td>
              <td align="left" valign="middle" >
              <c:choose><c:when test="${cl.ifGotEcard == '1'}">已更换
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotEcard == '0'}"><font color="#990000"><strong>未更换</strong></font>
              </c:when></c:choose>
              </td>
              <td height="24" align="center" valign="middle" class="tableHeader5" >学生证/校徽</td>
              <td align="left" valign="middle" > 
              <c:choose><c:when test="${cl.ifGotStucard == '1'}">已领取
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotStucard == '0'}"><font color="#990000"><strong>未领取</strong></font>
              </c:when></c:choose></td>
              
            </tr>           
          </tbody>
        </table>
        </logic:iterate>
       </td>
    </tr>
    </logic:present>
    <logic:notPresent name="checkinlist"  scope="request">
    <tr align="center" valign=center>
           <td align="center" valign="middle" colspan="4"> <font size="2.5" color="#990000">暂无你的入学信息或数据尚未入库！</font></td>
    </tr>      
    </logic:notPresent>

</table>

</html:form>
</center>

<script language="JavaScript">

function DoView(str){

    document.all.updateid.value=str;
    document.stufeeinfoForm.action="gzstufeeinfoAction.do?method=stuview&needback=1";
    document.stufeeinfoForm.submit();

}

</script>