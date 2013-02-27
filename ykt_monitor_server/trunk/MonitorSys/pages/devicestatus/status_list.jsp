<%@ page language="java"  pageEncoding="UTF-8"%>
<%@ include file="../commons/init.jsp" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>设备状态</title>
   
  </head>
  <body>
    
   
    <html:form action="devicestatus.do?method=queryDeviceStatus">
      <table>
        <tr><td>
         设备状态 <input name="devstatus" value="1"/>
        <input name="sub" type="submit" value="查 询" >
        
        </td></tr>
     </table>
    </html:form>  
      <table  width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
           <tr align="center">
              <td> 物理id </td>
              <td> 设备名称 </td>
              <td> 故障原因 </td>
              <td> ip地址 </td>
              <td> 起始时间</td>
              <td>修复时间</td>
              <td> 异常持续时间 </td>
              <td> 负责人 </td>
              <td> 接收人 </td>
              <td> 维护状态 </td>
           </tr>
  
           <logic:present name="result" scope="request">
             <logic:iterate name="result" id="dev" type="java.util.Map">
              
                 <tr align="center" valign=center>
                   <td><bean:write name="dev"  property="devphyid"/></td>
                   <td><bean:write name="dev"  property="devicename"/>&nbsp;</td>
                   <td>
                     <bean:write name="dev"  property="statename"/>                    
                   &nbsp;
                   </td>
                   <td><bean:write name="dev"  property="ip"/>&nbsp;</td>
                   <td><bean:write name="dev"  property="errstarttime"/>&nbsp;</td>
                    <td>&nbsp;</td>
                   <td><bean:write name="dev"  property="errlasttime"/>&nbsp;</td>
                   <td><bean:write name="dev"  property="contactname"/>&nbsp;</td>
                   <td>&nbsp;</td>
                   <td>
                      <logic:equal name="dev"  property="devstatus" value="1">
                       <html:link href="/monitor/devicestatus.do?method=editDeviceStatus&status=1"  paramId="id"  paramName="dev"  paramProperty="id" > 
                            新增
                       </html:link>
                      </logic:equal>
                      <logic:equal name="dev"  property="devstatus" value="2">
                      
                           维护中
                      
                      </logic:equal>
                          
                   </td>
                   
                 </tr>  
             </logic:iterate>
           </logic:present>
       </table>   
    
  </body>
</html>
