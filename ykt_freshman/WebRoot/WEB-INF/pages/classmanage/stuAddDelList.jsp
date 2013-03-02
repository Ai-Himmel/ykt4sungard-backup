<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>
<script language="JavaScript">

function document.onkeydown(){

	var e=event.srcElement;
	if(event.keyCode==13){
	
		document.all("Submit").click();
		return false;
	}
}
</script>
<center>

<html:form action = "stuadddelAction.do?method=find">

<br>

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">新生名单维护</font></strong></td>
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
              <td width="15%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>  
            <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                <bean:message bundle="checkinmanage" key="checkin.stuName"/> </td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="stuName" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>            
            </tr>
            <tr align="center" valign=center> 
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                <bean:message bundle="checkinmanage" key="checkin.gender"/> </td>
              <td align="left" valign="middle" class="tableHeader3" >
              <input name="gender" type="radio" value="1"><bean:message bundle="checkinmanage" key="checkin.male"/>&nbsp;&nbsp;&nbsp;
              <input name="gender" type="radio" value="2"><bean:message bundle="checkinmanage" key="checkin.female"/>&nbsp;&nbsp;&nbsp;
              <input name="gender" type="radio" value="" checked><bean:message bundle="checkinmanage" key="checkin.unknown"/>
              </td>
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                <bean:message bundle="checkinmanage" key="checkin.majorin"/> </td>
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
            </tr>
            <tr align="center" valign=center>
             <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >生源地</td>
             <td width="35%" align="left" valign="middle" class="tableHeader3" >
               <select name="fromProvince" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                   <logic:present name="arealist" scope="request">
                   <logic:iterate name="arealist" id="al" type="java.util.Map">
                    <option value="<bean:write name="al" property="dictValue"/>"><bean:write name="al" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
             </td> 
              <td align="right" valign="middle" class="tableHeader2" >国籍</td>
              <td align="left" valign="middle" class="tableHeader3" > 
                 <select name="nationality" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                   <logic:present name="countrylist" scope="request">
                   <logic:iterate name="countrylist" id="ctyl" type="java.util.Map">
                    <option value="<bean:write name="ctyl" property="dictValue"/>"><bean:write name="ctyl" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
              </td>
            </tr>
            <logic:present name="stuinfo" scope="request">
            <input name="hnationality" type="hidden" value="<bean:write name="stuinfo" property="nationality"/>"> 
            <input name="hstudentNo" type="hidden" value="<bean:write name="stuinfo" property="studentNo"/>"> 
            <input name="hgender" type="hidden" value="<bean:write name="stuinfo" property="gender"/>"> 
            <input name="hstuName" type="hidden" value="<bean:write name="stuinfo" property="stuName"/>">  
            <input name="hmajorin" type="hidden" value="<bean:write name="stuinfo" property="majorin"/>">            
            <input name="hfromProvince" type="hidden" value="<bean:write name="stuinfo" property="fromProvince"/>">
            </logic:present>   
            <logic:notPresent name="stuinfo" scope="request">  
            <input name="hnationality" type="hidden" value=""> 
            <input name="hstudentNo" type="hidden" value=""> 
            <input name="hgender" type="hidden" value=""> 
            <input name="hstuName" type="hidden" value=""> 
            <input name="hmajorin" type="hidden" value="">              
            <input name="hfromProvince" type="hidden" value="">
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
      <table width=98% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input type="hidden" name="updateid" value="">
           <logic:present name="stuinfolist" scope="request">
           <thead>
           <tr align="center" valign=center> 
              <td width="6%" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.selectall"/><input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
              <td width="18%" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td width="15%" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width="8%" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td width="20%" valign="middle" class="tableHeader" nowrap>专业</td>
              <td width="20%" valign="middle" class="tableHeader" nowrap>生源地</td>
              <td valign="middle" class="tableHeader" nowrap>国籍</td>              
            </tr>
           </thead>
           <!--page offset start -->
            <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		     <pg:pager url="./stuadddelAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
               <%-- keep track of preference --%>
                <pg:param name="method" />
                <pg:param name="hnationality" />
                <pg:param name="hstudentNo" />
                <pg:param name="hstuName" /> 
                <pg:param name="hgender" />                                                          
		        <pg:param name="hmajorin" />
		        <pg:param name="hfromProvince" /> 
		   
		    <%-- save pager offset during form changes --%>
		    <input type="hidden" name="pager.offset" value="<%= offset %>"> 
            <logic:iterate name="stuinfolist" id="cl" type="java.util.Map"  indexId="i">
             <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center bgcolor="#FFFFFF" >             
              <td align="center" valign="middle"><input type="checkbox" name="cbgroup" value="<bean:write name="cl" property="id"/>" onClick="DoSelect(this)"></td>
              <td height="24" align="center" valign="middle"><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle"><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td height="24" align="center" valign="middle">
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td height="24" align="center" valign="middle">
              <logic:present name="arealist" scope="request">            
               <logic:iterate name="arealist" id="al" type="java.util.Map">
                <c:choose><c:when test="${al.dictValue == cl.fromProvince}">              
                <bean:write name="al" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td height="24" align="center" valign="middle" >
              <logic:present name="countrylist" scope="request">            
               <logic:iterate name="countrylist" id="ctyl" type="java.util.Map">
                <c:choose><c:when test="${ctyl.dictValue == cl.nationality}">              
                <bean:write name="ctyl" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <c:choose><c:when test="${cl.dormId==null||cl.dormId==''}"> 
              <input type="hidden" name="dormId<bean:write name="cl" property="id"/>" value="">
              </c:when><c:otherwise>
              <input type="hidden" name="dormId<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="dormId"/>">
              </c:otherwise></c:choose>
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5" >                
              <td align="center" valign="middle"><input type="checkbox" name="cbgroup" value="<bean:write name="cl" property="id"/>" onClick="DoSelect(this)"></td>
              <td height="24" align="center" valign="middle"><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle"><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle">
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td height="24" align="center" valign="middle">
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td height="24" align="center" valign="middle">
              <logic:present name="arealist" scope="request">            
               <logic:iterate name="arealist" id="al" type="java.util.Map">
                <c:choose><c:when test="${al.dictValue == cl.fromProvince}">              
                <bean:write name="al" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <td height="24" align="center" valign="middle" >
              <logic:present name="countrylist" scope="request">            
               <logic:iterate name="countrylist" id="ctyl" type="java.util.Map">
                <c:choose><c:when test="${ctyl.dictValue == cl.nationality}">              
                <bean:write name="ctyl" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <c:choose><c:when test="${cl.dormId==null||cl.dormId==''}"> 
              <input type="hidden" name="dormId<bean:write name="cl" property="id"/>" value="">
              </c:when><c:otherwise>
              <input type="hidden" name="dormId<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="dormId"/>">
              </c:otherwise></c:choose>
            </tr>            
            </c:when></c:choose>
            
            </pg:item> 
            </logic:iterate>  
            <jsp:include page="./pagenoexcel.jsp" flush="true" />
						</tbody>
					</table>
				</td>
			</tr>			
			<tr> 
    			<td>
        		<jsp:include page="./pagenoexcel.jsp" flush="true" />
    			</td>
  			</tr>
		</pg:pager>
	</logic:present>
            
            <logic:notPresent name="stuinfolist" scope="request">
			<!--page offset start -->
		     <pg:pager url="./stuadddelAction.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
             <%-- keep track of preference --%>
               <pg:param name="method" />
               <pg:param name="hnationality" />
               <pg:param name="hstudentNo" />
               <pg:param name="hstuName" /> 
               <pg:param name="hgender" />                                                          
		       <pg:param name="hmajorin" />
		       <pg:param name="hfromProvince" />                
		   
		    <%-- save pager offset during form changes --%>
		      <input type="hidden" name="pager.offset" value="0">			
		     <jsp:include page="./pagenoexcel.jsp" flush="true" />
          </tbody>
        </table>
      </td>
  </tr>			   
		    </pg:pager>
		    <!-- page offset end -->
	    
            </logic:notPresent>

 
  <tr> 
    <td height="40" align="left" valign="middle">
        <%
        int rowcount=0;
        if(request.getAttribute("listcount")!=null){
        	rowcount=((Integer)request.getAttribute("listcount")).intValue();
        %>       
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
        <%} %>
    </td>
  </tr>	
   
   <tr> 
    <td height="40" align="right" valign="middle">
        <input name="add" type="button" class="button_nor" value="添加" onClick="DoAdd()" >
        &nbsp;&nbsp;&nbsp;
        <logic:present name="stuinfolist" scope="request">
            <input name="delete" type="button" class="button_nor" value="删除" onClick="DoDelete()">
        </logic:present>
    </td>
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

setTimeout('DoInit()',300);

function DoInit(){
  
  document.all.studentNo.value=document.all.hstudentNo.value;   
  document.all.stuName.value=document.all.hstuName.value;
    
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
  
  for(var i=0;i<document.all.nationality.length;i++){
     
      if(document.all.hnationality.value==document.all.nationality.options[i].value)
          document.all.nationality.options[i].selected=true;
          
  }
  
  if(document.all.hmsg.value=='0')
      alert("删除成功!");
  else if(document.all.hmsg.value=='1')
      alert("保存失败!");
}

function DoClear(){
  
   document.all.studentNo.value="";
   document.all.stuName.value="";
   
   document.all.gender[2].checked=true; 
   document.all.majorin.options[0].selected=true;  
   document.all.fromProvince.options[0].selected=true;
   document.all.nationality.options[0].selected=true;
   
   
   document.all.hstudentNo.value="";
   document.all.hmajorin.value="";
   document.all.hstuName.value="";
   document.all.hgender.value="";
   document.all.hfromProvince.value="";
   document.all.hnationality.value="";
}

function DoFind(){   
  
   document.forms[0].elements["pager.offset"].value="0";
   
   document.all.hnationality.value=document.all.nationality.value;
   document.all.hstudentNo.value=document.all.studentNo.value;
   
   for(var i=0;i<document.all.gender.length;i++){
       if(document.all.gender[i].checked)
            document.all.hgender.value=document.all.gender[i].value;
   
   }
   
   document.all.hstuName.value=document.all.stuName.value;
   document.all.hmajorin.value=document.all.majorin.value;
   document.all.hfromProvince.value=document.all.fromProvince.value;
   
   document.stuadddelForm.action="stuadddelAction.do?method=find";
   document.stuadddelForm.submit();
   
}

function DoSelect(cb){

   var sflag=1;;
   var usflag=1;;
  
   if(cb.checked){
   
       document.all.updateid.value=cb.value;
       //alert(document.all.updateid.value);

       if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(!document.all.cbgroup[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall.checked=true;
          }
       } 
   }
   
   if(!cb.checked){
       document.all.checkall.checked=false;
       if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall.checked=false;
              document.all.updateid.value="";
          }
       } 
   }
   
}

function DoCheckall(ckall){
   
   if(ckall.checked){
   
      if(document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=true;
       }
       document.all.updateid.value=document.all.cbgroup[document.all.cbgroup.length-1].value;
       }
       else{
          document.all.cbgroup.checked=true;
          document.all.updateid.value =document.all.cbgroup.value;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.cbgroup.length>1){
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=false;
       }
       document.all.updateid.value="";
      }
      else{
         document.all.cbgroup.checked=false;
         document.all.updateid.value="";
      }
   }
   //alert(document.all.updateid.value);

}

function DoAdd(){

   document.stuadddelForm.action="stuadddelAction.do?method=load4addstu";   
   document.stuadddelForm.submit();
}

function DoDelete(){
 
   var sflag=0;
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag==0){
              alert("请选择要删除的新生记录！");
              return;
          }
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){              
                   if(eval("document.all.dormId"+document.all.cbgroup[i].value+".value!=''")){
                         alert("所选新生尚有宿舍，请先退宿才能删除!");
                         return;
                         break;
                   }                                                   
              }
          }    
   }
   else{
        if(!document.all.cbgroup.checked){
              alert("请选择要删除的新生记录！");
              return;        
        }
        if(eval("document.all.dormId"+document.all.cbgroup.value+".value!=''")){
              alert("所选新生尚有宿舍，请先退宿才能删除!");
              return;
        }
   }
   
   if(confirm("您确定要删除该新生的记录吗？")){        
   　　　document.stuadddelForm.action="stuadddelAction.do?method=delstu";
   　　　document.stuadddelForm.submit();
   }
   else
      return;
  
}

</script>