<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>
<html:form action = "checkinmanageAction.do?method=tongjisubmit">
<html:errors/>
<br>

<table width="95%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">新生报到情况按专业统计</font></strong></td>
    </tr>    
    <tr> 
      <td align="center" valign="top" >
      <table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody> 
          
          <tr align="center" valign=center>
           <td width=10% align="right" valign="middle" class="tableHeader2" >专业</td>
           <td align="left" valign="middle" class="tableHeader3" colspan="3">
           <select name="majorin" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="majorinlist" scope="request">
                   <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                    <option value="<bean:write name="ml" property="dictValue"/>"><bean:write name="ml" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
            </select>                       
           </td>            
          </tr>
         <logic:present name="majorin" scope="request">
             <input name="hmajorin" type="hidden" value="<bean:write name="majorin" />"> 
             </logic:present>   
         <logic:notPresent name="majorin" scope="request">  
             <input name="hmajorin" type="hidden" value="">
         </logic:notPresent>   
         <input type="hidden" name="myAction" value="checkinmanageAction.do?method=tongjilistmajor">      
        </tbody>
     </table>
     </td>
    </tr>    
   <tr>
    <td height="30" align="right" valign="middle" class="tdborder02"> 
      <input name="Submit" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.lookfor"/>" onClick="DoFind()">
      <input name="Reset" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.reset"/>" onClick="DoClear()"> 
    </td>
    </tr>
    <tr>
      <td height="30" align="right" valign="middle" colspan="2">      
       <logic:present name="tjlist" scope="request">      
         <a href="javascript:DoExport()">导出Excel<IMG src="./pages/style/default/images/xls.gif" border="0"></a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;      
       </logic:present>&nbsp;</td>
    </tr>
    <tr> 
      <td height="40" align="center" valign="top"><table 
        width=95% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
          <tbody><input name="updateid" type="hidden" value="">
          <input name="updateclassNo" type="hidden" value="">  
          <input name="viewmajor" type="hidden" value=""><input name="doexl" type="hidden" value="">        
            <tr align="center" valign=center>                             
              <td width=15% height="24" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.majorin"/></td>
              <td width=4% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.shouldcheckinNum"/></td>
              <td width=4% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.exactcheckinNum"/></td>
              <td width=4% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.notcheckinNum"/></td>
              <td width=4% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.askforlateNum"/></td>
              <td width=13% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.askReserveNum"/></td>
              <td width=12% valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.noreasonNum"/></td>
              <td width=8% valign="middle" class="tableHeader" >明确不来人数</td>
              
            </tr>           
              
            <logic:present name="tjlist" scope="request">            
            <logic:iterate name="tjlist" id="tj" type="java.util.Map" indexId="i">
            <c:choose><c:when test="${i%2 != 0}">
            
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" style="font-weight:bold"><bean:write name="tj" property="majorinName"/></td>              
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
                <a href="javascript:DoNotcheckinView('<bean:write name="tj" property="majorin"/>')"><bean:write name="tj" property="notcheckinNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.askforlateNum != null}">      
                <a href="javascript:DoAskforlateView('<bean:write name="tj" property="majorin"/>')"><bean:write name="tj" property="askforlateNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.askreserveNum != null}">      
                <a href="javascript:DoAskreserveView('<bean:write name="tj" property="majorin"/>')"><bean:write name="tj" property="askreserveNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>             
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.noreasonNum != null}">      
                <a href="javascript:DoNoreasonView('<bean:write name="tj" property="majorin"/>')"><bean:write name="tj" property="noreasonNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
               <c:choose><c:when test="${tj.notcomeNum != null}">      
                <a href="javascript:DoNotcomeView('<bean:write name="tj" property="majorin"/>')"><bean:write name="tj" property="notcomeNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>    
              </td>                                      
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" style="font-weight:bold"><bean:write name="tj" property="majorinName"/></td>                            
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
                <a href="javascript:DoNotcheckinView('<bean:write name="tj" property="majorin"/>')"><bean:write name="tj" property="notcheckinNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.askforlateNum!= null}">      
                <a href="javascript:DoAskforlateView('<bean:write name="tj" property="majorin"/>')"><bean:write name="tj" property="askforlateNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.askreserveNum != null}">      
                <a href="javascript:DoAskreserveView('<bean:write name="tj" property="majorin"/>')"><bean:write name="tj" property="askreserveNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>             
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.noreasonNum !=null}">      
                <a href="javascript:DoNoreasonView('<bean:write name="tj" property="majorin"/>')"><bean:write name="tj" property="noreasonNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
               <c:choose><c:when test="${tj.notcomeNum != null}">      
                <a href="javascript:DoNotcomeView('<bean:write name="tj" property="majorin"/>')"><bean:write name="tj" property="notcomeNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>    
              </td>              
            </tr>   
            </c:when></c:choose>                               
           </logic:iterate>
           <logic:present name="tjlisttotal" scope="request">
           <logic:iterate name="tjlisttotal" id="tjt" type="java.util.Map">
           <tr align="center" valign=center bgcolor="#FF9999" style="font-weight:bold"> 
              <td height="24" align="center" valign="middle">总计</td>
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
              <c:choose><c:when test="${tjt.notcheckinNumtotal != null&&tjt.notcheckinNumtotal !=0}">
              <a href="javascript:DoNotcheckinView('')"><bean:write name="tjt" property="notcheckinNumtotal"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>              
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.askforlateNumtotal != null&&tjt.askforlateNumtotal !=0}">
              <a href="javascript:DoAskforlateView('')"><bean:write name="tjt" property="askforlateNumtotal"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.askreserveNumtotal != null&&tjt.askreserveNumtotal !=0}">
              <a href="javascript:DoAskreserveView('')"><bean:write name="tjt" property="askreserveNumtotal"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.noreasonNumtotal != null&&tjt.noreasonNumtotal !=0}">
              <a href="javascript:DoNoreasonView('')"><bean:write name="tjt" property="noreasonNumtotal"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.notcomeNumtotal != null&&tjt.notcomeNumtotal !=0}">
              <a href="javascript:DoNotcomeView('')"><bean:write name="tjt" property="notcomeNumtotal"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
                                                  
           </logic:iterate> 
           </logic:present>  
           </logic:present>         
          </tbody>
        </table></td>
    </tr>   

</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>
</html:form>
</center>

<script language="JavaScript">

setTimeout('DoInit()',20);

function DoInit(){   
     
   for(var i=0;i<document.all.majorin.length;i++){
       if(document.all.hmajorin.value==document.all.majorin[i].value){
            document.all.majorin[i].selected=true;            
       }
   }
   
  // if(document.all.hmsg.value=='1')
  //    alert("导出Excel成功!");
 //  else if(document.all.hmsg.value=='0')
  //    alert("无内容!");
}

function DoClear(){  
   
   document.all.majorin.options[0].selected=true;   
   
   document.all.hmajorin.value="";
      
}

function DoFind(){   
   document.all.doexl.value="";
   document.all.hmajorin.value=document.all.majorin.value;
      
   document.stucheckininfoForm.action="checkinmanageAction.do?method=tongjilistmajor";
   document.stucheckininfoForm.submit();
   
}

function DoExport(){
document.all.hmajorin.value=document.all.majorin.value;
document.stucheckininfoForm.action="checkinmanageAction.do?method=tongjilistmajorexcel";
document.stucheckininfoForm.submit();

}

//合并书院、班级单元格
function uniteTable(thistab,colLength){
var rn=thistab.rows.length;//取得行数
var rowspann=0;
for(j=colLength-1;j>=0;j--){//从第0列开始，合并多少列
for(i=rn-1;i>0;i--){//从倒数第一行开始往上检查
if(thistab.rows[i].cells[j].innerText==thistab.rows[i-1].cells[j].innerText&&thistab.rows[i].cells[j].colSpan==thistab.rows[i-1].cells[j].colSpan){//与上面一行比较，如果两行相等就合计当前行的合并行数，并删除当前行。
rowspann+=thistab.rows[i].cells[j].rowSpan;
thistab.rows[i].deleteCell(j);
}else{
thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
rowspann=0;
}
}
//检测无表头的表
if(i==0&&rowspann>0){
thistab.rows[i].cells[j].rowSpan+=rowspann;//如果不等就完成当前相同数据的合并。
rowspann=0;
}

}
}

function DoNotcheckinView(str){
  document.all.doexl.value="";
  document.all.viewmajor.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=mjnotcheckinstu";
  document.stucheckininfoForm.submit();
}

function DoAskforlateView(str){
  document.all.doexl.value="";
  document.all.viewmajor.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=mjaskforlatestu";
  document.stucheckininfoForm.submit();
}

function DoAskreserveView(str){
  document.all.doexl.value="";
  document.all.viewmajor.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=mjaskreservestu";
  document.stucheckininfoForm.submit();

}

function DoNoreasonView(str){
  document.all.doexl.value="";
  document.all.viewmajor.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=mjnoreasonstu";
  document.stucheckininfoForm.submit();

}

function DoNotcomeView(str){
  document.all.doexl.value="";
  document.all.viewmajor.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=mjnotcomestu";
  document.stucheckininfoForm.submit();

}

function DoReserveView(str){
  document.all.doexl.value="";
  document.all.viewmajor.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=mjreservestu";
  document.stucheckininfoForm.submit();

}

function DoLeaveschoolView(str){
  document.all.doexl.value="";
  document.all.viewmajor.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=mjleaveschoolstu";
  document.stucheckininfoForm.submit();

}

</script>