<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "stufeeinfoAction.do?method=view">
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
    <logic:present name="stuinfolist"  scope="request">
      <td height="40" align="center" valign="top"><input name="updateid" type="hidden" value="">
      <logic:iterate name="stuinfolist" id="sl" type="java.util.Map">
      <table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
            <tr align="center" valign=center> 
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><bean:write name="sl" property="studentNo"/></td>
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.enrollNo"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><bean:write name="sl" property="enrollNo"/>&nbsp;</td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" ><bean:write name="sl" property="stuName"/></td>
              <td valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${sl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${sl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
            </tr>
            <tr align="center" valign=center> 
              <td height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.majorin"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" >
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == sl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><bean:write name="sl" property="classNo"/></td>
            </tr>
            </logic:iterate>
            </logic:present>
            <tr align="center" valign=center>               
              <td colspan="4" align="left" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
            </tr>
            <logic:present name="checkinlist"  scope="request">
            <logic:iterate name="checkinlist" id="cl" type="java.util.Map">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td width="15%" height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.state"/>
                </td>
              <td width="35%" align="left" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.ifCheckedin == '1'}"><bean:message bundle="checkinmanage" key="checkin.checkedin"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifCheckedin == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notcheckedin"/></strong></font>
              </c:when></c:choose>
              </td>
              <td width="15%" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.hasChecked2"/></td>
              <td width="35%" align="left" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.ifChecked == '1'}"><bean:message bundle="checkinmanage" key="checkin.checked"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifChecked == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notchecked"/></strong></font>
              </c:when></c:choose>
              </td>
            </tr>
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.hasGotMaterial2"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.ifGotMaterial == '1'}"><bean:message bundle="checkinmanage" key="checkin.got"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotMaterial == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notgot"/></strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.fee"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" ><a href="javascript:DoView('<bean:write name="cl" property="studentNo"/>')">查看详细信息</a></td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.archives"/></td>
              <td align="left" valign="middle" >
              <c:choose><c:when test="${cl.hasArchives == '1'}"><bean:message bundle="checkinmanage" key="checkin.handedin"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.hasArchives == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.nothandedin"/></strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.stuArchive"/></td>
              <td align="left" valign="middle" >
              <c:choose><c:when test="${cl.hasStuarchive == '1'}">已核对&nbsp;
              </c:when></c:choose>
              <c:choose><c:when test="${cl.hasStuarchive == '0'}"><font color="#990000"><strong>未核对</strong></font>&nbsp;
              </c:when></c:choose> 
              <c:choose><c:when test="${cl.archiveSubmit == '1'}"><bean:message bundle="checkinmanage" key="archives.instate"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.archiveSubmit == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="archives.notinstate"/></strong></font>
              </c:when></c:choose> 
              </td>
            </tr>
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.physicalCheck"/></td>              
              <td align="left" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.ifUnhealthy == '0'}"><font color="#990000"><strong>未体检</strong></font>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '1'}">体检合格
              </c:when></c:choose> 
              <c:choose><c:when test="${cl.ifUnhealthy == '2'}"><font color="#990000"><strong>需复检</strong></font>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '3'}">复检合格
              </c:when></c:choose>
              </td>              
              <td align="center" valign="middle" bgcolor="#FFFFFF" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.hasPhoto"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" >
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
            <tr align="center" valign=center> 
              <td align="center" valign="middle" bgcolor="#F6F4F5" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.hasGotEcard3"/></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.ifGotEcard == '1'}">已更换
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotEcard == '0'}"><font color="#990000"><strong>未更换</strong></font>
              </c:when></c:choose>
              </td>
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.hasGotStucard3"/></td>
              <td align="left" valign="middle" bgcolor="#F6F4F5" > 
              <c:choose><c:when test="${cl.ifGotStucard == '1'}"><bean:message bundle="checkinmanage" key="checkin.got"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotStucard == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notgot"/></strong></font>
              </c:when></c:choose></td>
              
            </tr>           
          </tbody>
        </table>
        </logic:iterate>
       </td>
    </tr>
    </logic:present>
    <logic:notPresent name="checkinlist"  scope="request">
     <font size="2.5" color="#990000"><bean:message bundle="checkinmanage" key="checkin.nocheckininfo"/></font>
    </logic:notPresent>
   <tr> 
    <td height="40" align="right" valign="middle"> 
      <input name="Submit" type="button" class="button_nor" value="返 回" onClick="Goback()"> 
    </td>
  </tr>
</table>

<input type="hidden" name="myAction" value="<%=request.getParameter("myAction")==null||request.getParameter("myAction").equals("null")?"":request.getParameter("myAction")+"&pager.offset="+request.getParameter("pager.offset")%>">
<input type="hidden" name="henrollNo" value="<%=request.getParameter("henrollNo")==null||request.getParameter("henrollNo").equals("null")?"":request.getParameter("henrollNo")%>">
<input type="hidden" name="hstudentNo" value="<%=request.getParameter("hstudentNo")==null||request.getParameter("hstudentNo").equals("null")?"":request.getParameter("hstudentNo")%>">
<input type="hidden" name="hgender" value="<%=request.getParameter("hgender")==null||request.getParameter("hgender").equals("null")?"":request.getParameter("hgender")%>">
<input type="hidden" name="hmajorin" value="<%=request.getParameter("hmajorin")==null||request.getParameter("hmajorin").equals("null")?"":request.getParameter("hmajorin")%>">

</html:form>
</center>

<script language="JavaScript">
function DoView(str){
    
    document.all.updateid.value=str;
    
    document.stufeeinfoForm.action="stufeeinfoAction.do?method=view";
    document.stufeeinfoForm.submit();

}

function Goback(){
  if(document.all.myAction.value!='')
    window.location.href=document.all.myAction.value+"&henrollNo="+document.stufeeinfoForm.henrollNo.value+"&hstudentNo="+document.stufeeinfoForm.hstudentNo.value+"&hgender="+document.stufeeinfoForm.hgender.value+"&hmajorin="+document.stufeeinfoForm.hmajorin.value;
 else
    history.go(-1);
}

</script>