<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>
<script type="text/javascript" src="<c:url value='/pages/datepicker/WdatePicker.js'/>"></script>
<%@ page import="java.util.Date" %>
<%@ page import="java.text.SimpleDateFormat" %>

<%
  Date now = new Date();

  SimpleDateFormat formatter1 = new SimpleDateFormat ("yyyy-MM-dd");
  String dateStr = formatter1.format(now);
%>

<center>
<html:form action = "userAccessAction.do?method=tongjiMain">
<html:errors/>
<br>

<table width="95%" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong> 
        <font class="medium">系统登录统计</font></strong></td>
    </tr>
    <tr> 
         <td align="center" valign="top" height="10"></td>
    </tr>
    <tr> 
      <td align="center" valign="top" ><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign=center> 
              <td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >起始日期</td>
              <td align="left" valign="middle" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <input class="Wdate" type="text" name="beginDate" value="<%=dateStr%>" onfocus="new WdatePicker(this)" readonly="readonly"/>
                    </td>                    
                  </tr>
                </table></td>
              <td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >终止日期</td>
              <td align="left" valign="middle" class="tableHeader3" ><table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <input class="Wdate" type="text" name="endDate" value="<%=dateStr%>" onfocus="new WdatePicker(this)" readonly="readonly"/>
                    </td>                    
                  </tr>
                </table></td>
            </tr>            
            <tr align="center" valign=center> 
              <td width="10%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >登录名</td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="userName" class="input_box"  maxlength=50 value=""></td>
              <td width="10%" align="right" valign="middle" class="tableHeader2" >姓名</td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="trueName" class="input_box"  maxlength=50 value=""></td>
            </tr>
            <logic:present name="beginDate" scope="request">
             <input name="hbeginDate" type="hidden" value="<bean:write name="beginDate" />"> 
            </logic:present>   
            <logic:notPresent name="beginDate" scope="request">  
             <input name="hbeginDate" type="hidden" value="<%=dateStr%>">
            </logic:notPresent>
            <logic:present name="endDate" scope="request">
             <input name="hendDate" type="hidden" value="<bean:write name="endDate" />"> 
            </logic:present>   
            <logic:notPresent name="endDate" scope="request">  
             <input name="hendDate" type="hidden" value="<%=dateStr%>">
            </logic:notPresent>
            <logic:present name="userName" scope="request">
             <input name="huserName" type="hidden" value="<bean:write name="userName" />"> 
            </logic:present>   
            <logic:notPresent name="userName" scope="request">  
             <input name="huserName" type="hidden" value="">
            </logic:notPresent>
            <logic:present name="trueName" scope="request">
             <input name="htrueName" type="hidden" value="<bean:write name="trueName" />"> 
            </logic:present>   
            <logic:notPresent name="trueName" scope="request">  
             <input name="htrueName" type="hidden" value="">
            </logic:notPresent>
          </tbody>
        </table></td>
    </tr>
    <tr> 
      <td height="40" align="right" valign="middle" class="tdborder02"> <input name="Submit" type="button" class="button_nor" value="统 计" onClick="DoCheck()"> 
      </td>
    </tr>    
    
    <logic:present name="tjlist" scope="request">    
    <tr> 
      <td height="30" align="left" valign="middle" class="medium">
      <strong><font color="#990000">起始日期：</font><bean:write name="beginDate"/>&nbsp;&nbsp;&nbsp;
      <font color="#990000">终止日期：</font><bean:write name="endDate"/>&nbsp;&nbsp;&nbsp;
      <logic:present name="userName" scope="request"> 
      <bean:write name="userName"/>&nbsp;&nbsp;&nbsp;
      </logic:present>
      <logic:present name="trueName" scope="request"> 
      <bean:write name="trueName"/>
      </logic:present>
      </strong>             
      </td>           
    </tr>    
    </logic:present>  
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input name="doexl" type="hidden" value=""><input name="viewDate" type="hidden" value="">
          <logic:present name="tjlist">
            <tr align="center" valign=center> 
              <td width="40%" height="24" valign="middle" class="tableHeader" >日期</td>              
              <td valign="middle" class="tableHeader" >访问量</td>                   
            </tr>
            
            <logic:iterate name="tjlist" id="tj" type="java.util.Map" indexId="i">
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="tj" property="accessDate" formatKey="dateFormat"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><a href="javascript:DoMainAccessView('<bean:write name="tj" property="accessDate"/>')"><bean:write name="tj" property="accessNum"/></a></td>                         
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="tj" property="accessDate" formatKey="dateFormat"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><a href="javascript:DoMainAccessView('<bean:write name="tj" property="accessDate"/>')"><bean:write name="tj" property="accessNum"/></a></td>                            
            </tr>
            </c:when></c:choose>
           </logic:iterate> 
           <logic:present name="tjlisttotal" scope="request">
           <logic:iterate name="tjlisttotal" id="tjt" type="java.util.Map">
           <tr align="center" valign=center bgcolor="#FF9999"> 
              <td height="24" align="center" valign="middle" >总&nbsp;计</td>
              <td align="center" valign="middle"><bean:write name="tjt" property="totalNum"/></td>                         
            </tr>
           </logic:iterate> 
           </logic:present>          
           </logic:present>  
                        
          </tbody>
        </table></td>
    </tr>    

</table>

</html:form>
</center>

<script language="JavaScript">

function init(){
 
  document.all.beginDate.value=document.forms[0].elements["hbeginDate"].value;  
  document.all.endDate.value=document.forms[0].elements["hendDate"].value;
  document.all.userName.value=document.forms[0].elements["huserName"].value;  
  document.all.trueName.value=document.forms[0].elements["htrueName"].value;    
  
}

function DoCheck(){

   document.all.doexl.value="";
   
   if(document.all.beginDate.value==""){
       alert("请输入要统计的起始日期！");
       document.all.beginDate.focus();
       return;
   }
   if(document.all.endDate.value==""){
       alert("请输入要统计的终止日期！");
       document.all.endDate.focus();
       return;
   }
   
   document.forms[0].elements["hbeginDate"].value=document.all.beginDate.value;
   document.forms[0].elements["hendDate"].value=document.all.endDate.value;
   document.forms[0].elements["huserName"].value=document.all.userName.value;
   document.forms[0].elements["htrueName"].value=document.all.trueName.value;
   // alert("ok");  
   document.forms[0].action="userAccessAction.do?method=tongjiMain";
   document.forms[0].submit();

}

function DoMainAccessView(str){

  document.all.viewDate.value=str;
  document.forms[0].action="userAccessAction.do?method=mainAccessview";
  document.forms[0].submit();

}

window.onload=init;
</script>
