<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "gzcheckinmanageAction.do?method=stuinfofind">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium"><bean:message bundle="checkinmanage" key="checkin.searchtitle"/></font></strong></td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top" ><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign=center> 
              <td width="15%" align="left" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
              <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width="35%" align="left" valign="middle" class="tableHeader3" ><input 
            name="stuName" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
              
            </tr>
            <tr align="center" valign=center> 
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
               <bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td align="left" valign="middle" class="tableHeader3" >
              <input name="gender" type="radio" value="1"><bean:message bundle="checkinmanage" key="checkin.male"/>&nbsp;&nbsp;&nbsp;
              <input name="gender" type="radio" value="2"><bean:message bundle="checkinmanage" key="checkin.female"/>&nbsp;&nbsp;&nbsp;
              <input name="gender" type="radio" value="" checked><bean:message bundle="checkinmanage" key="checkin.unknown"/>
              </td>
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
               <bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td align="left" valign="middle" class="tableHeader3" >
              <select name="classNo" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="classlist" scope="request">
                   <logic:iterate name="classlist" id="col" type="java.util.Map">
                    <option value="<bean:write name="col" property="classNo"/>"><bean:write name="col" property="classNo"/></option>
                   </logic:iterate>
                   </logic:present>
             </select>
              </td>
            </tr>
            <tr align="center" valign=center style="display:none">
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                <bean:message bundle="checkinmanage" key="checkin.majorin"/></td>
              <td align="left" valign="middle" class="tableHeader3" >
              <select name="majorin" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="majorinlist" scope="request">
                   <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                    <option value="<bean:write name="ml" property="dictValue"/>"><bean:write name="ml" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
              </td>
              <td align="left" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.fromProvince"/></td>
              <td align="left" valign="middle" class="tableHeader3"> 
                 <select name="fromProvince" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="arealist" scope="request">
                   <logic:iterate name="arealist" id="al" type="java.util.Map">
                    <option value="<bean:write name="al" property="dictValue"/>"><bean:write name="al" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
              </td>
            </tr>
            <logic:present name="stuinfo" scope="request">
            <input name="hstuName" type="hidden" value="<bean:write name="stuinfo" property="stuName"/>"> 
            <input name="hstudentNo" type="hidden" value="<bean:write name="stuinfo" property="studentNo"/>"> 
            <input name="hgender" type="hidden" value="<bean:write name="stuinfo" property="gender"/>"> 
            <input name="hmajorin" type="hidden" value="<bean:write name="stuinfo" property="majorin"/>">              
            <input name="hfromProvince" type="hidden" value="<bean:write name="stuinfo" property="fromProvince"/>">
            </logic:present>   
            <logic:notPresent name="stuinfo" scope="request">  
            <input name="hstuName" type="hidden" value=""> 
            <input name="hstudentNo" type="hidden" value=""> 
            <input name="hgender" type="hidden" value=""> 
            <input name="hmajorin" type="hidden" value="">              
            <input name="hfromProvince" type="hidden" value="">
             </logic:notPresent>
             <logic:present name="classNo" scope="request">
             <input name="hclassNo" type="hidden" value="<bean:write name="classNo" />"> 
             </logic:present>   
             <logic:notPresent name="classNo" scope="request">  
             <input name="hclassNo" type="hidden" value="">
             </logic:notPresent>
          </tbody>
        </table></td>
  </tr>
  <tr>
    <td height="30" align="right" valign="middle" class="tdborder02"> 
      <input name="Submit" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.lookfor"/>" onClick="DoFind()">
      <input name="Reset" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.reset"/>" onClick="DoClear()"> 
    </td>
  </tr>
  <tr> 
    <td align="right" valign="middle">&nbsp;</td>
  </tr>
  
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input type="hidden" name="updateid" value=""><input type="hidden" name="method" value="stuinfofind">
          <logic:present name="checkinlist" scope="request">
          <thead>
          <tr align="center" > 
          <td align="center" height="24" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
          <td align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
          <td align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
          <td align="center" valign="middle" class="tableHeader" style="display:none"><bean:message bundle="checkinmanage" key="checkin.majorin"/></td>
          <td align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
          <td align="center" valign="middle" class="tableHeader" style="display:none"><bean:message bundle="checkinmanage" key="checkin.fromProvince"/></td>      
          </tr>
          </thead>          
           <!--page offset start -->
           <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./gzcheckinmanageAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="method" />
           <pg:param name="hstuName" />
           <pg:param name="hstudentNo" />
           <pg:param name="hgender" />
           <pg:param name="hmajorin" />
           <pg:param name="hclassNo" />
		   <pg:param name="hfromProvince" />
		   
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">  
			
            <logic:iterate name="checkinlist" id="cl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=middle>             
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><a href="javascript:DoView('<bean:write name="cl" property="studentNo"/>')"><bean:write name="cl" property="studentNo"/></a></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" style="display:none">
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="classNo"/></td>
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" style="display:none">
              <logic:present name="arealist" scope="request">            
               <logic:iterate name="arealist" id="al" type="java.util.Map">
                <c:choose><c:when test="${al.dictValue == cl.fromProvince}">              
                <bean:write name="al" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>           
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center>              
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" ><a href="javascript:DoView('<bean:write name="cl" property="studentNo"/>')"><bean:write name="cl" property="studentNo"/></a></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" style="display:none">
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="classNo"/></td>
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" style="display:none">
              <logic:present name="arealist" scope="request">            
               <logic:iterate name="arealist" id="al" type="java.util.Map">
                <c:choose><c:when test="${al.dictValue == cl.fromProvince}">              
                <bean:write name="al" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
            </tr>            
            </c:when></c:choose> 
             </pg:item>           
            </logic:iterate>
            <jsp:include page="./page.jsp" flush="true" />
            </tbody>
        </table>
      </td>
  </tr>
  <tr> 
    <td height="24" align="left" valign="middle">
        <jsp:include page="./page.jsp" flush="true" />
    </td>
  </tr>
		  </pg:pager>
		  <!-- page offset end -->
            </logic:present>
          
           <logic:notPresent name="checkinlist" scope="request">
          <thead>
          <tr align="center" > 
          <td align="center" height="24" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
          <td align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
          <td align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
          <td align="center" valign="middle" class="tableHeader" style="display:none"><bean:message bundle="checkinmanage" key="checkin.majorin"/></td>
          <td align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
          <td align="center" valign="middle" class="tableHeader" style="display:none"><bean:message bundle="checkinmanage" key="checkin.fromProvince"/></td>      
          </tr>
          </thead>          
           <!--page offset start -->
		  <pg:pager url="./stuinfolistpageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="hstuName" />
           <pg:param name="hstudentNo" />
           <pg:param name="hgender" />
           <pg:param name="hmajorin" />
           <pg:param name="hclassNo" />
		   <pg:param name="hfromProvince" />
		   
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">  
			
			<jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
		  </tbody>
        </table>
      </td>
  </tr>
            </logic:notPresent>
			
            
   <logic:present name="checkinlist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">¹²<%=rowcount%>Ìõ¼ÇÂ¼</font>
    </td>
    </tr>  
    </logic:present>
</table>

</html:form>
</center>

<script language="JavaScript">

setTimeout('init()',50);

function init(){
  
  document.all.stuName.value=document.all.hstuName.value;
  document.all.studentNo.value=document.all.hstudentNo.value;        
  
  for(var i=0;i<document.all.classNo.length;i++){
       if(document.all.hclassNo.value==document.all.classNo[i].value){
           document.all.classNo[i].selected=true;
       }
   }
    
  for(var i=0;i<document.all.gender.length;i++){
       if(document.all.hgender.value==document.all.gender[i].value)
            document.all.gender[i].checked=true;
   
   }
  
  for(var i=0;i<document.all.majorin.length;i++){
     
      if(document.all.hmajorin.value==document.all.majorin.options[i].value)
          document.all.majorin.options[i].selected=true;
          
  }   
  
   for(var i=0;i<document.all.fromProvince.length;i++){
     
      if(document.all.hfromProvince.value==document.all.fromProvince.options[i].value)
          document.all.fromProvince.options[i].selected=true;
          
  } 
}

function DoClear(){
  
   document.all.stuName.value="";   
   document.all.studentNo.value="";
   document.all.classNo.options[0].selected=true;
   
   document.all.gender[2].checked=true;
   document.all.majorin.options[0].selected=true;
   document.all.fromProvince.options[0].selected=true;
   
   //document.all.henrollNo.value="";
   document.all.hstudentNo.value="";
   document.all.hclassNo.value="";
   document.all.hmajorin.value="";
   document.all.hgender.value="";
   document.all.hfromProvince.value="";
   
}

function document.onkeydown()
{
	var e=event.srcElement;
	if(event.keyCode==13)
	{
		DoFind();
		return false;
	}
}

function DoFind(){
   
   document.forms[0].elements["pager.offset"].value="0";
   
   document.all.hclassNo.value=document.all.classNo.value;
   document.all.hstuName.value=document.all.stuName.value;
   document.all.hstudentNo.value=document.all.studentNo.value;
   
   for(var i=0;i<document.all.gender.length;i++){
       if(document.all.gender[i].checked)
            document.all.hgender.value=document.all.gender[i].value;
   
   }
   
   document.all.hmajorin.value=document.all.majorin.value;
   document.all.hfromProvince.value=document.all.fromProvince.value;
   
   document.stucheckininfoForm.action="gzcheckinmanageAction.do?method=stuinfofind";
   document.stucheckininfoForm.submit();
   
}

function DoView(str){

   document.all.updateid.value=str;
   
   document.stucheckininfoForm.action="gzcheckinmanageAction.do?method=stuinfoview";
   document.stucheckininfoForm.submit();
}

</script>