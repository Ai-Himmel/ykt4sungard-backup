<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "rcvmanageAction.do?method=find">
<html:errors/>
<br>
<table width="90%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">�����ֻ���Ϣ</font></strong></td>
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
            <td width="10%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >¼ȡ֪ͨ���</td>
            <td align="left" valign="middle" class="tableHeader3" colspan="3"><bean:write name="al" property="enrollNo"/></td>
         </tr>
          <tr height="30" align="center" valign=center>
            <td align="right" valign="middle" class="tableHeader2" >ѧ��</td>
            <td align="left" valign="middle" class="tableHeader3" ><bean:write name="al" property="studentNo"/></td>
            <td width="5%" align="right" valign="middle" class="tableHeader2" >����</td>
            <td align="left" valign="middle" class="tableHeader3" ><bean:write name="al" property="stuName"/></td>
          </tr>
          <tr height="30" align="center" valign=center> 
          <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�ֻ���ʽ</td>
            <td align="left" valign="middle" class="tableHeader3" colspan="3">
                  <c:choose><c:when test="${al.arrivePlace == '01'}">
                    ��
                  </c:when></c:choose>
                  <c:choose><c:when test="${al.arrivePlace == '02'}">
                    ��;����
                  </c:when></c:choose>
                  <c:choose><c:when test="${al.arrivePlace == '03'}">
                    �ɻ�
                  </c:when></c:choose>
                  <c:choose><c:when test="${al.arrivePlace == '04'}">
                    �Լݳ�
                  </c:when></c:choose> 
                   <c:choose><c:when test="${al.arrivePlace == '05'}">
                    ����
                  </c:when></c:choose>   
                  <c:choose><c:when test="${al.arrivePlace == '06'}">
                    ����
                  </c:when></c:choose>            
            </td>
          </tr>
          <tr height="30" align="center" valign=center> 
            <td id="tddate" width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >
            <c:choose><c:when test="${al.arrivePlace == '01'}">  
              Ԥ�Ƶֻ�����
            </c:when><c:otherwise>
              Ԥ�Ƶ�У����
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
              Ԥ�Ƶֻ�ʱ��
            </c:when><c:otherwise>
              Ԥ�Ƶ�Уʱ��
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
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >����</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" colspan="3"><table border="0" cellspacing="0" cellpadding="0">                
            <tr align="center" valign="middle">
             <td width="50"> <c:choose><c:when test="${al.ifDeleted == '3'}">
              ���Ż���
              </c:when></c:choose>
              <c:choose><c:when test="${al.ifDeleted == '4'}">
              �ֶ�����
              </c:when></c:choose>
              </td>
              </tr>
              </table></td>
          </tr>
          </c:when></c:choose>
          <c:choose><c:when test="${al.arrivePlace == '01'}">
          <tr height="30" id="trtrain" align="center" valign=center>             
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�𳵳���</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" ><bean:write name="al" property="trainNo"/></td>           
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�����</td>
            <td align="left" valign="middle" class="tableHeader3" ><bean:write name="al" property="trainRoomNo"/></td>
         </tr>
         <tr id="trnum" height="30" align="center" valign=center>    
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��ͬ����</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" colspan="3"><bean:write name="al" property="companyNum"/></td>
         </tr>
         <tr id="trhelp" height="30" align="center" valign=center>    
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��վ</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3"><table border="0" cellspacing="0" cellpadding="0">
                <tr align="left" valign="middle"> 
                  <td width="50"> <c:choose><c:when test="${al.ifDeleted == '1'}">
                     �Ϻ�վ
                  </c:when></c:choose> 
                  <c:choose><c:when test="${al.ifDeleted == '2'}">
                     �Ϻ���վ 
                  </c:when></c:choose> 
                  </td>
                </tr>
            </table></td>         
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >���Ϻ�վ��У��</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3"><table border="0" cellspacing="0" cellpadding="0">
                <tr align="left" valign="middle"> 
                  <td width="50"> <c:choose><c:when test="${al.ifNeedBus == '0'}">
                     ��
                  </c:when></c:choose> 
                  <c:choose><c:when test="${al.ifNeedBus == '1'}">
                     �� 
                  </c:when></c:choose> 
                  </td>
                </tr>
              </table></td>
          </tr>
          </c:when></c:choose> 
          <tr height="30" id="trtrain" align="center" valign=center>             
            <td align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��ϵ��ʽ</td>
            <td align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader3" colspan="3"><bean:write name="al" property="tempconcact"/>&nbsp;</td>          
         </tr>
          <tr align="center" valign=center> 
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��ע</td>
            <td colspan="3" align="left" valign="middle" class="tableHeader3" ><bean:write name="al" property="memo"/>
            </td>
          </tr>
        </tbody>
      </table>
      </logic:iterate>
      </logic:present>
      <logic:notPresent name="arrivelist" scope="request">
      <font color="#990000" size="2.5">������δ�Ǽǵֻ���Ϣ��</font>
      </logic:notPresent>
      </td>
  </tr> 
  <tr> 
    <td height="40" align="right" valign="middle"> 
      <input name="Submit" type="button" class="button_nor" value="�� ��" onClick="Goback()"> 
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