<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "rcvmanageAction.do?method=find">
<html:errors/>
<br>
<table width="90%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">新生抵沪信息</font></strong></td>
  </tr>
  <tr>
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top" >
    <logic:present name="arrivelist" scope="request">
    <logic:iterate name="arrivelist" id="al" type="java.util.Map" length="1">
    <table 
        width=95% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
        <tbody>
          <input type="hidden" name="updateid" value="<bean:write name="al" property="id"/>">
          <tr height="30" align="center" valign=center> 
            <td width="10%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >录取通知书号</td>
            <td align="left" valign="middle" class="tableHeader3" colspan="3"><bean:write name="al" property="enrollNo"/></td>
         </tr>
          <tr height="30" align="center" valign=center>
            <td align="right" valign="middle" class="tableHeader2" >学号</td>
            <td align="left" valign="middle" class="tableHeader3" ><bean:write name="al" property="studentNo"/></td>
            <td width="5%" align="right" valign="middle" class="tableHeader2" >姓名</td>
            <td align="left" valign="middle" class="tableHeader3" ><bean:write name="al" property="stuName"/></td>
          </tr>
          <tr height="30" align="center" valign=center> 
          <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >抵沪方式</td>
            <td align="left" valign="middle" class="tableHeader3" colspan="3">
                  <c:choose><c:when test="${al.arrivePlace == '01'}">
                    火车
                  </c:when></c:choose>
                  <c:choose><c:when test="${al.arrivePlace == '02'}">
                    长途汽车
                  </c:when></c:choose>
                  <c:choose><c:when test="${al.arrivePlace == '03'}">
                    飞机
                  </c:when></c:choose>
                  <c:choose><c:when test="${al.arrivePlace == '04'}">
                    自驾车
                  </c:when></c:choose> 
                   <c:choose><c:when test="${al.arrivePlace == '05'}">
                    其他
                  </c:when></c:choose>   
                  <c:choose><c:when test="${al.arrivePlace == '06'}">
                    本市
                  </c:when></c:choose>            
            </td>
          </tr>
          <tr height="30" align="center" valign=center> 
            <td id="tddate" width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >
            <c:choose><c:when test="${al.arrivePlace == '01'}">  
              预计抵沪日期
            </c:when><c:otherwise>
              预计到校日期
            </c:otherwise></c:choose>
            </td>
            <td width="35%" align="left" valign="middle" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr> 
                  <td width="130"><bean:write name="al" property="arriveDate"/> 
                  </td>
                </tr>
              </table></td>
            <td id="tdtime" width="15%" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >
            <c:choose><c:when test="${al.arrivePlace == '01'}">
              预计抵沪时间
            </c:when><c:otherwise>
              预计到校时间
            </c:otherwise></c:choose> 
            </td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr> 
                  <td width="130"><bean:write name="al" property="arriveTime" formatKey="timeFormat"/>
                  </td>
                </tr>
              </table></td>
          </tr>
          <c:choose><c:when test="${al.arrivePlace == '03'}">
          <tr id="trhelp" height="30" align="center" valign=center>             
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >机场</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" colspan="3"><table border="0" cellspacing="0" cellpadding="0">                
            <tr align="center" valign="middle">
             <td width="50"> <c:choose><c:when test="${al.ifDeleted == '3'}">
              虹桥机场
              </c:when></c:choose>
              <c:choose><c:when test="${al.ifDeleted == '4'}">
              浦东机场
              </c:when></c:choose>
              </td>
              </tr>
              </table></td>
          </tr>
          </c:when></c:choose>
          <c:choose><c:when test="${al.arrivePlace == '01'}">
          <tr height="30" id="trtrain" align="center" valign=center>             
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >火车车次</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" ><bean:write name="al" property="trainNo"/></td>           
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >车厢号</td>
            <td align="left" valign="middle" class="tableHeader3" ><bean:write name="al" property="trainRoomNo"/></td>
         </tr>
         <tr id="trnum" height="30" align="center" valign=center>    
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >陪同人数</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" colspan="3"><bean:write name="al" property="companyNum"/></td>
         </tr>
         <tr id="trhelp" height="30" align="center" valign=center>    
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >火车站</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3"><table border="0" cellspacing="0" cellpadding="0">
                <tr align="left" valign="middle"> 
                  <td width="50"> <c:choose><c:when test="${al.ifDeleted == '1'}">
                     上海站
                  </c:when></c:choose> 
                  <c:choose><c:when test="${al.ifDeleted == '2'}">
                     上海南站 
                  </c:when></c:choose> 
                  </td>
                </tr>
            </table></td>         
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >到上海站坐校车</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3"><table border="0" cellspacing="0" cellpadding="0">
                <tr align="left" valign="middle"> 
                  <td width="50"> <c:choose><c:when test="${al.ifNeedBus == '0'}">
                     否
                  </c:when></c:choose> 
                  <c:choose><c:when test="${al.ifNeedBus == '1'}">
                     是 
                  </c:when></c:choose> 
                  </td>
                </tr>
              </table></td>
          </tr>
          </c:when></c:choose> 
          <tr height="30" id="trtrain" align="center" valign=center>             
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >联系方式</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" colspan="3"><bean:write name="al" property="tempconcact"/>&nbsp;</td>          
         </tr>
          <tr align="center" valign=center> 
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >备注</td>
            <td colspan="3" align="left" valign="middle" class="tableHeader3" ><bean:write name="al" property="memo"/>
            </td>
          </tr>
        </tbody>
      </table>
      </logic:iterate>
      </logic:present>
      <logic:notPresent name="arrivelist" scope="request">
      <font color="#990000" size="2.5">该生尚未登记抵沪信息！</font>
      </logic:notPresent>
      </td>
  </tr> 
  <tr> 
    <td height="40" align="right" valign="middle"> 
      <input name="Submit" type="button" class="button_nor" value="返 回" onClick="Goback()"> 
    </td>
  </tr> 
</table>
<input type="hidden" name="myAction" value="<%=request.getParameter("myAction")==null||request.getParameter("myAction").equals("null")?"":request.getParameter("myAction")%>">
</html:form>
</center>

<script language="JavaScript">
function Goback(){
 if(document.all.myAction.value!=''){
    document.stuarriveinfoForm.action=document.all.myAction.value;
    document.stuarriveinfoForm.submit();
 }
 else
    history.go(-1);
}
</script>