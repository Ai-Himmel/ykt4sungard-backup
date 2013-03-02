<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "gzclassAction.do?method=stuinfoview">
<html:errors/>
<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">新生基本信息</font></strong></td>
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
              <td width="15%" height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.enrollNo"/></td>
              <td align="left" valign="middle" bgcolor="#FFFFFF" colspan="3"><bean:write name="sl" property="enrollNo"/>&nbsp;</td>              
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5">  
              <td width="15%" height="24" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width="35%" align="left" valign="middle" ><bean:write name="sl" property="stuName"/></td>            
              <td width="15%" valign="middle" class="tableHeader5" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td width="35%" align="left" valign="middle" >
              <c:choose><c:when test="${sl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${sl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>              
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF" >  
              <td height="24" valign="middle" class="tableHeader5" >生日</td>
              <td align="left" valign="middle" ><bean:write name="sl" property="birthday"/></td>            
              <td valign="middle" class="tableHeader5" >身份证号</td>
              <td align="left" valign="middle" ><bean:write name="sl" property="idCard"/></td>              
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5">  
              <td height="24" valign="middle" class="tableHeader5" >政治面貌</td>
              <td align="left" valign="middle" ><bean:write name="sl" property="polityBgName"/></td>            
              <td valign="middle" class="tableHeader5" >联系电话</td>
              <td align="left" valign="middle" ><bean:write name="sl" property="telephone"/></td>              
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF" >              
              <td valign="middle" class="tableHeader5" >所在地区</td>
              <td align="left" valign="middle" ><bean:write name="sl" property="districtName"/></td>
              <td valign="middle" class="tableHeader5" >邮编</td>
              <td align="left" valign="middle"><bean:write name="sl" property="postCode"/></td>
            </tr>
            <tr align="center" valign=center bgcolor="#F6F4F5">  
              <td height="24" valign="middle" class="tableHeader5" >家庭地址</td>
              <td align="left" valign="middle" colspan="3"><bean:write name="sl" property="familyAddress"/></td>            
            </tr>
            <tr align="center" valign=center bgcolor="#FFFFFF" >  
              <td height="24" valign="middle" class="tableHeader5" >高考科类</td>
              <td align="left" valign="middle" ><bean:write name="sl" property="examTypeName"/></td>            
              <td valign="middle" class="tableHeader5" >高考总分</td>
              <td align="left" valign="middle" ><bean:write name="sl" property="totalScore"/></td>              
            </tr>
            </tbody>
        </table>
            </logic:iterate>
            </logic:present>          
   <tr> 
    <td height="40" align="right" valign="middle"> 
      <input name="Submit" type="button" class="button_nor" value="返 回" onClick="Goback()"> 
    </td>
  </tr>
</table>
<input type="hidden" name="myAction" value="<%=request.getParameter("myAction")==null||request.getParameter("myAction").equals("null")?"":request.getParameter("myAction")+"&pager.offset="+request.getParameter("pager.offset")%>">
<input type="hidden" name="henrollNo" value="<%=request.getParameter("henrollNo")==null||request.getParameter("henrollNo").equals("null")?"":request.getParameter("henrollNo")%>">
<input type="hidden" name="hstuName" value="<%=request.getParameter("hstuName")==null||request.getParameter("hstuName").equals("null")?"":request.getParameter("hstuName")%>">
<input type="hidden" name="hgender" value="<%=request.getParameter("hgender")==null||request.getParameter("hgender").equals("null")?"":request.getParameter("hgender")%>">
<input type="hidden" name="hexamType" value="<%=request.getParameter("hexamType")==null||request.getParameter("hexamType").equals("null")?"":request.getParameter("hexamType")%>">
<input type="hidden" name="hclassId" value="<%=request.getParameter("hclassId")==null||request.getParameter("hclassId").equals("null")?"":request.getParameter("hclassId")%>">
</html:form>
</center>

<script language="JavaScript">
function Goback(){
 if(document.all.myAction.value!=''){
    document.classForm.action=document.all.myAction.value;
    document.classForm.submit();
 }
 else
    history.go(-1);
}

</script>