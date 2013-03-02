<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>
<html:form action = "cardfeesubmitAction.do?method=cardfeesubmit">
<html:errors/>
<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">一卡通缴费情况一览</font></strong></td>
    </tr>
    <tr> 
      <td height="30" align="left" valign="middle" class="medium">&nbsp;</td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>              
            <tr align="center" valign=center> 
              <td width=6% height="24" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td width=6% valign="middle" class="tableHeader" >应缴人数</td>
              <td width=6% valign="middle" class="tableHeader" >实缴人数</td>
              <td width=6% valign="middle" class="tableHeader" >未缴人数</td>
              
            <logic:notPresent name="tjlist" scope="request">
            </tr>
            </logic:notPresent>
              
            <logic:present name="tjlist" scope="request">
            <td width=6% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.submitstate"/></td>            
            
            </tr>
            <logic:iterate name="tjlist" id="tj" type="java.util.Map" indexId="i">
            <c:choose><c:when test="${i%2 != 0}">
            
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="tj" property="classNo"/></a></td>
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
                <bean:write name="tj" property="notcheckinNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              
              <c:choose><c:when test="${tj.ifSubmitted =='1'}"><!-- 已提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" >已确认</td>              
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted =='0'}"><!-- 已退回过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" >已退回</td>              
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted ==null}"><!-- 从未提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" >未确认</td>              
              </c:when></c:choose>
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="tj" property="classNo"/></a></td>
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
               <bean:write name="tj" property="notcheckinNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              
              <c:choose><c:when test="${tj.ifSubmitted =='1'}"><!-- 已提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" >已确认</td>              
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted =='0'}"><!-- 已退回过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" >已退回</td>              
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted ==null}"><!-- 从未提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" >未确认</td>              
              </c:when></c:choose>
              
            </c:when></c:choose>
            </tr>                                 
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
