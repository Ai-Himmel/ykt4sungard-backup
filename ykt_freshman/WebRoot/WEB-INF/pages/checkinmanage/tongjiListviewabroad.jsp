<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>
<html:form action = "checkinmanageAction.do?method=tongjisubmit">
<html:errors/>
<br>

<table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr> 
      <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium"><bean:message bundle="checkinmanage" key="checkin.tongjititle"/></font></strong></td>
    </tr>
    
     <tr> 
      <td align="center" valign="top" >
      <table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody> 
          
          <tr align="center" valign=center>
           <td width=10% align="right" valign="middle" class="tableHeader2" >书院</td>
           <td align="left" valign="middle" class="tableHeader3" >
           <select name="collegeId" class="select01" onChange="setClass(this)">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="collegelist" scope="request">
                   <logic:iterate name="collegelist" id="col" type="java.util.Map">
                    <option value="<bean:write name="col" property="id"/>"><bean:write name="col" property="collegeName"/></option>
                   </logic:iterate>
                   </logic:present>
           </select>                
            </td>
           <td width=10% align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
           <td align="left" valign="middle" class="tableHeader3" >
             <select name="classNo" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  
             </select>
            </td>
          </tr>          
         
         <logic:present name="collegeId" scope="request">
             <input name="hcollegeId" type="hidden" value="<bean:write name="collegeId" />"> 
             </logic:present>   
         <logic:notPresent name="collegeId" scope="request">  
             <input name="hcollegeId" type="hidden" value="">
         </logic:notPresent>
         <logic:present name="classNo" scope="request">
             <input name="hclassNo" type="hidden" value="<bean:write name="classNo" />"> 
             </logic:present>   
         <logic:notPresent name="classNo" scope="request">  
             <input name="hclassNo" type="hidden" value="">
         </logic:notPresent>  
         <input type="hidden" name="myAction" value="checkinmanageAction.do?method=tongjilistviewabroad">       
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
        width=96% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
          <tbody><input name="doexl" type="hidden" value=""> 
          <input name="viewclassNo" type="hidden" value="">        
            <tr align="center" valign=center>
              <td width=6% height="24" valign="middle" class="tableHeader" rowspan="2">书院</td>               
              <td width=6% height="24" valign="middle" class="tableHeader" rowspan="2"><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td width=12% valign="middle" class="tableHeader" colspan="3"><bean:message bundle="checkinmanage" key="checkin.shouldcheckinNum"/></td>
              <td width=12% valign="middle" class="tableHeader" colspan="3"><bean:message bundle="checkinmanage" key="checkin.exactcheckinNum"/></td>
              <td width=12% valign="middle" class="tableHeader" colspan="3"><bean:message bundle="checkinmanage" key="checkin.notcheckinNum"/></td>
              <td width=4% valign="middle" class="tableHeader" rowspan="2"><bean:message bundle="checkinmanage" key="checkin.askforlateNum"/></td>
              <td width=8% valign="middle" class="tableHeader" rowspan="2"><bean:message bundle="checkinmanage" key="checkin.askReserveNum"/></td>
              <td width=8% valign="middle" class="tableHeader" rowspan="2"><bean:message bundle="checkinmanage" key="checkin.noreasonNum"/></td>
              <td width=6% valign="middle" class="tableHeader" rowspan="2">明确不来人数</td>              
            <logic:notPresent name="tjlist" scope="request">
            </tr>
            <tr align="center" valign=center>
              <td width=4% valign="middle" class="tableHeader" >总</td>
              <td width=4% valign="middle" class="tableHeader" >中</td>
              <td width=4% valign="middle" class="tableHeader" >外</td>
              <td width=4% valign="middle" class="tableHeader" >总</td>
              <td width=4% valign="middle" class="tableHeader" >中</td>
              <td width=4% valign="middle" class="tableHeader" >外</td>
              <td width=4% valign="middle" class="tableHeader" >总</td>
              <td width=4% valign="middle" class="tableHeader" >中</td>
              <td width=4% valign="middle" class="tableHeader" >外</td>
            </tr>
            </logic:notPresent>
              
            <logic:present name="tjlist" scope="request">
            <td width=6% valign="middle" class="tableHeader" rowspan="2"><bean:message bundle="checkinmanage" key="checkin.submitstate"/></td>            
            </tr>
            <tr align="center" valign=center>
              <td width=4% valign="middle" class="tableHeader" >总</td>
              <td width=4% valign="middle" class="tableHeader" >中</td>
              <td width=4% valign="middle" class="tableHeader" >外</td>
              <td width=4% valign="middle" class="tableHeader" >总</td>
              <td width=4% valign="middle" class="tableHeader" >中</td>
              <td width=4% valign="middle" class="tableHeader" >外</td>
              <td width=4% valign="middle" class="tableHeader" >总</td>
              <td width=4% valign="middle" class="tableHeader" >中</td>
              <td width=4% valign="middle" class="tableHeader" >外</td>
            </tr>
            <logic:iterate name="tjlist" id="tj" type="java.util.Map" indexId="i">
            <c:choose><c:when test="${i%2 != 0}">
            
            <tr align="center" valign=center> 
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" style="font-weight:bold"><bean:write name="tj" property="collegeName"/></td>
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="tj" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.shouldcheckinNum != 0}">      
                <bean:write name="tj" property="shouldcheckinNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.shouldcheckinmaleNum != 0}">      
                <bean:write name="tj" property="shouldcheckinmaleNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.shouldcheckinfemaleNum != 0}">      
                <bean:write name="tj" property="shouldcheckinfemaleNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.exactcheckinNum != 0}">      
                <bean:write name="tj" property="exactcheckinNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.exactcheckinmaleNum != 0}">      
                <bean:write name="tj" property="exactcheckinmaleNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.exactcheckinfemaleNum != 0}">      
                <bean:write name="tj" property="exactcheckinfemaleNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.notcheckinNum != 0}">      
                <a href="javascript:DoNotcheckinView('<bean:write name="tj" property="classNo"/>','')"><bean:write name="tj" property="notcheckinNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.notcheckinmaleNum != 0}">      
                <a href="javascript:DoNotcheckinView('<bean:write name="tj" property="classNo"/>','1')"><bean:write name="tj" property="notcheckinmaleNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.notcheckinfemaleNum != 0}">      
                <a href="javascript:DoNotcheckinView('<bean:write name="tj" property="classNo"/>','2')"><bean:write name="tj" property="notcheckinfemaleNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.askforlateNum != 0}">      
                <a href="javascript:DoAskforlateView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="askforlateNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.askreserveNum != 0}">      
                <a href="javascript:DoAskreserveView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="askreserveNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>             
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${tj.noreasonNum != 0}">      
                <a href="javascript:DoNoreasonView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="noreasonNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
               <c:choose><c:when test="${tj.notcomeNum != 0}">      
                <a href="javascript:DoNotcomeView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="notcomeNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>    
              </td>              
              <c:choose><c:when test="${tj.ifSubmitted =='1'}"><!-- 已提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.submitted"/></td>              
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted =='0'}"><!-- 已退回过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.notsubmitted"/></td>              
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted ==null}"><!-- 从未提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.notsubmitted"/></td>              
              </c:when></c:choose>              
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5"> 
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" style="font-weight:bold"><bean:write name="tj" property="collegeName"/></td>
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="tj" property="classNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.shouldcheckinNum != 0}">      
                <bean:write name="tj" property="shouldcheckinNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.shouldcheckinmaleNum != 0}">      
                <bean:write name="tj" property="shouldcheckinmaleNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.shouldcheckinfemaleNum != 0}">      
                <bean:write name="tj" property="shouldcheckinfemaleNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.exactcheckinNum != 0}">      
                <bean:write name="tj" property="exactcheckinNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.exactcheckinmaleNum != 0}">      
                <bean:write name="tj" property="exactcheckinmaleNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.exactcheckinfemaleNum != 0}">      
                <bean:write name="tj" property="exactcheckinfemaleNum"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.notcheckinNum != 0}">      
                <a href="javascript:DoNotcheckinView('<bean:write name="tj" property="classNo"/>','')"><bean:write name="tj" property="notcheckinNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.notcheckinmaleNum != 0}">      
                <a href="javascript:DoNotcheckinView('<bean:write name="tj" property="classNo"/>','1')"><bean:write name="tj" property="notcheckinmaleNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.notcheckinfemaleNum != 0}">      
                <a href="javascript:DoNotcheckinView('<bean:write name="tj" property="classNo"/>','2')"><bean:write name="tj" property="notcheckinfemaleNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.askforlateNum!= 0}">      
                <a href="javascript:DoAskforlateView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="askforlateNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.askreserveNum != 0}">      
                <a href="javascript:DoAskreserveView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="askreserveNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>             
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${tj.noreasonNum !=0}">      
                <a href="javascript:DoNoreasonView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="noreasonNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
               <c:choose><c:when test="${tj.notcomeNum != 0}">      
                <a href="javascript:DoNotcomeView('<bean:write name="tj" property="classNo"/>')"><bean:write name="tj" property="notcomeNum"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>    
              </td>              
              <c:choose><c:when test="${tj.ifSubmitted =='1'}"><!-- 已提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.submitted"/></td>                                      
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted =='0'}"><!-- 已退回过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.notsubmitted"/></td>                           
              </c:when></c:choose>
              <c:choose><c:when test="${tj.ifSubmitted ==null}"><!-- 从未提交过 -->
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:message bundle="checkinmanage" key="checkin.notsubmitted"/></td>              
              </c:when></c:choose>
            </tr>   
            </c:when></c:choose>                      
           </logic:iterate>
           <logic:present name="tjlisttotal" scope="request">
           <logic:iterate name="tjlisttotal" id="tjt" type="java.util.Map">
           <tr align="center" valign=center bgcolor="#FF9999" style="font-weight:bold"> 
              <td height="24" align="center" valign="middle" colspan="2">总计</td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.shouldcheckinNumtotal != 0}"> 
              <bean:write name="tjt" property="shouldcheckinNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.shouldcheckinmaleNumtotal != 0}"> 
              <bean:write name="tjt" property="shouldcheckinmaleNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.shouldcheckinfemaleNumtotal != 0}"> 
              <bean:write name="tjt" property="shouldcheckinfemaleNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.exactcheckinNumtotal != 0}">
              <bean:write name="tjt" property="exactcheckinNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.exactcheckinmaleNumtotal != 0}">
              <bean:write name="tjt" property="exactcheckinmaleNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.exactcheckinfemaleNumtotal != 0}">
              <bean:write name="tjt" property="exactcheckinfemaleNumtotal"/>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.notcheckinNumtotal != 0}">
              <a href="javascript:DoNotcheckinView('','')"><bean:write name="tjt" property="notcheckinNumtotal"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td> 
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.notcheckinmaleNumtotal != 0}">
              <a href="javascript:DoNotcheckinView('','1')"><bean:write name="tjt" property="notcheckinmaleNumtotal"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.notcheckinfemaleNumtotal != 0}">
              <a href="javascript:DoNotcheckinView('','2')"><bean:write name="tjt" property="notcheckinfemaleNumtotal"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose> 
              </td>             
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.askforlateNumtotal != 0}">
              <a href="javascript:DoAskforlateView('')"><bean:write name="tjt" property="askforlateNumtotal"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.askreserveNumtotal != 0}">
              <a href="javascript:DoAskreserveView('')"><bean:write name="tjt" property="askreserveNumtotal"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.noreasonNumtotal != 0}">
              <a href="javascript:DoNoreasonView('')"><bean:write name="tjt" property="noreasonNumtotal"/></a>
              </c:when><c:otherwise>
              0
              </c:otherwise> </c:choose>
              </td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${tjt.notcomeNumtotal != 0}">
              <a href="javascript:DoNotcomeView('')"><bean:write name="tjt" property="notcomeNumtotal"/></a>
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
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>
</html:form>
</center>

<script>

    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("classlist")!=null)
       resultset=(String[][])request.getAttribute("classlist");//读取数据
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>");//产生javascript二维数组，对应书院、班级
     <%
     }
   }
   %>
   datacount=<%=count%>;
  

</script>


<script language="JavaScript">

setTimeout('DoInit()',20);

function DoInit(){   
     
   for(var i=0;i<document.all.collegeId.length;i++){
       if(document.all.hcollegeId.value==document.all.collegeId[i].value){
            document.all.collegeId[i].selected=true;
            if(document.all.hcollegeId.value!=''){
                setClass(document.all.collegeId);
                for(var j=0;j<document.all.classNo.length;j++){
                    if(document.all.hclassNo.value==document.all.classNo[j].value){
                            document.all.classNo[j].selected=true;
                    }
                }
            }    
       }
   }   
   
   uniteTable(document.all.maintable,1);//执行测试。
   
   //if(document.all.hmsg.value=='1')
  //    alert("导出Excel成功!");
 //  else if(document.all.hmsg.value=='0')
  //    alert("无内容!");
}

function DoClear(){  
   
   document.all.classNo.options[0].selected=true;
   document.all.collegeId.options[0].selected=true;      
   
   document.all.hcollegeId.value="";
   document.all.hclassNo.value="";
      
}

function DoFind(){   
   document.all.doexl.value="";
   document.all.hcollegeId.value=document.all.collegeId.value;
   document.all.hclassNo.value=document.all.classNo.value;
      
   document.stucheckininfoForm.action="checkinmanageAction.do?method=tongjilistviewabroad";
   document.stucheckininfoForm.submit();
   
}

function DoExport(){
document.all.doexl.value="1";
document.all.hcollegeId.value=document.all.collegeId.value;
document.all.hclassNo.value=document.all.classNo.value;
document.stucheckininfoForm.action="checkinmanageAction.do?method=tongjilistviewabroad";
document.stucheckininfoForm.submit();

}

function setClass(sel){

        var id;        
        var i;        

        id=sel.options[sel.selectedIndex].value;
        document.all.classNo.length=1; //清空原班级列表        

        for (i=0;i < datacount; i++)
        {
            if (dataset[i][1] == id)
            {
                document.all.classNo.options[document.all.classNo.length]=new Option(dataset[i][0], dataset[i][0]);              
                
            }
        }

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


function DoNotcheckinView(str,flag){
  document.all.doexl.value="";
  document.all.viewclassNo.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=notcheckinstu&nationality="+flag;
  document.stucheckininfoForm.submit();
}

function DoAskforlateView(str){
  document.all.doexl.value="";
  document.all.viewclassNo.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=askforlatestu";
  document.stucheckininfoForm.submit();
}

function DoAskreserveView(str){
  document.all.doexl.value="";
  document.all.viewclassNo.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=askreservestu";
  document.stucheckininfoForm.submit();

}

function DoNoreasonView(str){
  document.all.doexl.value="";
  document.all.viewclassNo.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=noreasonstu";
  document.stucheckininfoForm.submit();

}

function DoNotcomeView(str){
  document.all.doexl.value="";
  document.all.viewclassNo.value=str;
  document.stucheckininfoForm.action="checkinsubminAction.do?method=donotcomestu";
  document.stucheckininfoForm.submit();

}


</script>