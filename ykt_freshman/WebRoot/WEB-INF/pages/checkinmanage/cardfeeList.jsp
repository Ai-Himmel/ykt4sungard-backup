<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "cardfeeAction.do?method=find">

<br>

<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium">
    <logic:present name="checkinlist" scope="request">
   <logic:iterate name="checkinlist" id="cl" type="java.util.Map" length="1">
    <bean:write name="cl" property="classNo"/>班&nbsp;一卡通/浴卡缴费登记
      <input name="classNo" type="hidden" value="<bean:write name="cl" property="classNo"/>"> 
   </logic:iterate>
   </logic:present> 
  <logic:notPresent name="checkinlist" scope="request">
    一卡通/浴卡缴费登记
  </logic:notPresent>
    
    </font></strong></td>
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
              <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.enrollNo"/></td>
              <td width="35%" align="left" valign="middle" class="tableHeader3" ><input 
            name="enrollNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
              <td width="15%" align="left" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>              
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
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                <bean:message bundle="checkinmanage" key="checkin.stuName"/> </td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="stuName" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
              <td align="left" valign="middle" class="tableHeader2" >国籍</td>
              <td align="left" valign="middle" class="tableHeader3" > 
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
            <input name="henrollNo" type="hidden" value="<bean:write name="stuinfo" property="enterenceNo"/>"> 
            <input name="hstudentNo" type="hidden" value="<bean:write name="stuinfo" property="studentNo"/>"> 
            <input name="hgender" type="hidden" value="<bean:write name="stuinfo" property="gender"/>"> 
            <input name="hstuName" type="hidden" value="<bean:write name="stuinfo" property="stuName"/>">  
            <input name="hmajorin" type="hidden" value="<bean:write name="stuinfo" property="majorin"/>">            
            <input name="hfromProvince" type="hidden" value="<bean:write name="stuinfo" property="fromProvince"/>">
            </logic:present>   
            <logic:notPresent name="stuinfo" scope="request">  
            <input name="henrollNo" type="hidden" value=""> 
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
  <logic:notPresent name="checkinlist" scope="request">
  <font size="2.5" color="#990000">未查找到新生或您无权作所列新生的一卡通/浴卡缴费登记！</font>
  </logic:notPresent>  
  
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input type="hidden" name="updateid" value="">
           <logic:present name="checkinlist" scope="request">
           <thead>
           <tr align="center" valign=center> 
              <td width="6%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.selectall"/><input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" nowrap>国籍</td>
              <td width="12%" valign="middle" class="tableHeader" nowrap>一卡通缴费</td>
              <td width="10%" height="22" valign="middle" class="tableHeader" nowrap>浴卡缴费</td> 
              <td width="15%" rowspan="2" height="22" valign="middle" class="tableHeader" nowrap>浴卡卡号</td>             
              <td width="10%" rowspan="2" valign="middle" class="tableHeader">登记人</td>
              <td width="18%" rowspan="2" valign="middle" class="tableHeader" nowrap>登记时间</td>
              <td rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.saveondisk"/></td>
            </tr>
             <tr align="center" valign=center>             
              <td valign="middle" class="tableHeader" > <input type="checkbox" name="checkall1" onClick="DoCheckall1(this)">
                <span class="small"><bean:message bundle="checkinmanage" key="checkin.selectall"/></span></td>
              <td height="22" valign="middle" class="tableHeader" > <input type="checkbox" name="checkall2" onClick="DoCheckall2(this)"> 
                <span class="small"><bean:message bundle="checkinmanage" key="checkin.selectall"/></span></td>              
            </tr>
           </thead>
           <!--page offset start -->
            <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		     <pg:pager url="./cardfeeAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
               <%-- keep track of preference --%>
                <pg:param name="method" />
                <pg:param name="henrollNo" />
                <pg:param name="hstudentNo" />
                <pg:param name="hstuName" /> 
                <pg:param name="hgender" />                                                          
		        <pg:param name="hmajorin" />
		        <pg:param name="hfromProvince" /> 
		   
		    <%-- save pager offset during form changes --%>
		    <input type="hidden" name="pager.offset" value="<%= offset %>"> 
            <logic:iterate name="checkinlist" id="cl" type="java.util.Map"  indexId="i">
             <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center>             
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><input type="checkbox" name="cbgroup" value="<bean:write name="cl" property="id"/>" onClick="DoSelect(this)"></td>
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" >
              <logic:present name="arealist" scope="request">            
               <logic:iterate name="arealist" id="al" type="java.util.Map">
                <c:choose><c:when test="${al.dictValue == cl.nationality}">              
                <bean:write name="al" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              
              <logic:notPresent name="cardfeesubmit" scope="request">
				<!-- 未提交过-->
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                  <c:choose><c:when test="${cl.ecardPayed == '1'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" checked>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.ecardPayed == '0'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')">
                  </c:when></c:choose>                
                  <input name="ecardPayed<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ecardPayed"/>" >
              </td>              
              </logic:notPresent>
			  <logic:present name="cardfeesubmit" scope="request">
				<logic:iterate name="cardfeesubmit" id="cs" type="java.util.Map" length="1">
				<td align="center" valign="middle" bgcolor="#FFFFFF" >
				<c:choose><c:when test="${cs.ifSubmitted == '0'}"><!--未提交 -->
				  <c:choose><c:when test="${cl.ecardPayed == '1'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" checked>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.ecardPayed == '0'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" >
                  </c:when></c:choose> 
				</c:when></c:choose>
				
				<c:choose><c:when test="${cs.ifSubmitted == '1'}"><!--已提交 -->
				  <c:choose><c:when test="${cl.ecardPayed == '1'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" checked disabled>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.ecardPayed == '0'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" disabled>
                  </c:when></c:choose>
                  <script language="JavaScript">
                         document.all.checkall1.disabled=true;
                 </script> 
				</c:when></c:choose>
					
                 <input name="ecardPayed<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ecardPayed"/>" >
                </td>
                </logic:iterate>
			  </logic:present>	
			  		
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                  <c:choose><c:when test="${cl.bathcardPayed== '1'}">
                   <input type="checkbox" name="ck_bathcardPayed" onClick="DoCheck2(this,'<bean:write name="cl" property="id"/>')" checked>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.bathcardPayed== '0'}">
                   <input type="checkbox" name="ck_bathcardPayed" onClick="DoCheck2(this,'<bean:write name="cl" property="id"/>')">
                  </c:when></c:choose>
                  <input name="bathcardPayed<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="bathcardPayed"/>">
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF">
              <input name="bathcardNo<bean:write name="cl" property="id"/>" class="input_box"  maxlength=10 value="<bean:write name="cl" property="bathcardNo"/>">
              </td>              
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <bean:write name="cl" property="updatorId"/>&nbsp;
              </td>  
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <bean:write name="cl" property="updateTime" formatKey="dateTimeFormat"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                <input name="save" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.save"/>" onClick="DoSave('<bean:write name="cl" property="id"/>')" >
              </td>     
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center>                
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><input type="checkbox" name="cbgroup" value="<bean:write name="cl" property="id"/>" onClick="DoSelect(this)"></td>
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" >
              <logic:present name="arealist" scope="request">            
               <logic:iterate name="arealist" id="al" type="java.util.Map">
                <c:choose><c:when test="${al.dictValue == cl.nationality}">              
                <bean:write name="al" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              <logic:notPresent name="cardfeesubmit" scope="request">
				<!-- 未提交过-->
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                  <c:choose><c:when test="${cl.ecardPayed == '1'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" checked>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.ecardPayed == '0'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')">
                  </c:when></c:choose>                
                  <input name="ecardPayed<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ecardPayed"/>" >
              </td>              
              </logic:notPresent>
			  <logic:present name="cardfeesubmit" scope="request">
				<logic:iterate name="cardfeesubmit" id="cs" type="java.util.Map" length="1">
				<td align="center" valign="middle" bgcolor="#F6F4F5" >
				<c:choose><c:when test="${cs.ifSubmitted == '0'}"><!--未提交 -->
				  <c:choose><c:when test="${cl.ecardPayed == '1'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" checked>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.ecardPayed == '0'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" >
                  </c:when></c:choose> 
				</c:when></c:choose>
				
				<c:choose><c:when test="${cs.ifSubmitted == '1'}"><!--已提交 -->
				  <c:choose><c:when test="${cl.ecardPayed == '1'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" checked disabled>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.ecardPayed == '0'}">
                    <input type="checkbox" name="ck_ecardPayed" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" disabled>
                  </c:when></c:choose> 
                  <script language="JavaScript">
                         document.all.checkall1.disabled=true;
                 </script>
				</c:when></c:choose>
					
                 <input name="ecardPayed<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ecardPayed"/>" >
                </td>
                </logic:iterate>
			  </logic:present>	
			  
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
                  <c:choose><c:when test="${cl.bathcardPayed == '1'}">
                   <input type="checkbox" name="ck_bathcardPayed" onClick="DoCheck2(this,'<bean:write name="cl" property="id"/>')" checked>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.bathcardPayed == '0'}">
                   <input type="checkbox" name="ck_bathcardPayed" onClick="DoCheck2(this,'<bean:write name="cl" property="id"/>')">
                  </c:when></c:choose>
                  <input name="bathcardPayed<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="bathcardPayed"/>">
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5">
              <input name="bathcardNo<bean:write name="cl" property="id"/>" class="input_box"  maxlength=10 value="<bean:write name="cl" property="bathcardNo"/>">
              </td>            
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <bean:write name="cl" property="updatorId"/>&nbsp;
              </td>  
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <bean:write name="cl" property="updateTime" formatKey="dateTimeFormat"/>&nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
                <input name="save" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.save"/>" onClick="DoSave('<bean:write name="cl" property="id"/>')" >                
              </td> 
            </tr>            
            </c:when></c:choose>
            <input type="hidden" name="studentNo<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="studentNo"/>">            
            <input type="hidden" name="enrollYear<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="enrollYear"/>">
            <input type="hidden" name="ecardPhoto<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="ecardPhoto"/>">
            <input type="hidden" name="updatorId<bean:write name="cl" property="id"/>" value="<%=(String)session.getAttribute("personName")%>">            
            </pg:item> 
            </logic:iterate>  
            <jsp:include page="./page.jsp" flush="true" />
		    </pg:pager>
		    <!-- page offset end -->          
            </logic:present>
            
            <logic:notPresent name="checkinlist" scope="request">
			<!--page offset start -->
		     <pg:pager url="./cardfeelistpageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
             <%-- keep track of preference --%>
               <pg:param name="henrollNo" />
               <pg:param name="hstudentNo" />
               <pg:param name="hstuName" /> 
               <pg:param name="hgender" />                                                          
		       <pg:param name="hmajorin" />
		       <pg:param name="hfromProvince" />                
		   
		    <%-- save pager offset during form changes --%>
		      <input type="hidden" name="pager.offset" value="0">			
		     <jsp:include page="./page.jsp" flush="true" />
		    </pg:pager>
		    <!-- page offset end -->
            </logic:notPresent>
          </tbody>
        </table>
      </td>
  </tr>
  <logic:present name="checkinlist">
    <tr> 
    <td height="40" align="left" valign="middle">
        <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
    </td>
    </tr>  
    </logic:present>
  <tr> 
    <td height="40" align="right" valign="middle">       
        <input name="saveall" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.batchsave"/>" onClick="DoSaveAll()" >
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
  
  document.all.enrollNo.value=document.all.henrollNo.value;
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
  if(document.all.hmsg.value=='0')
      alert("保存成功!");
  else if(document.all.hmsg.value=='1')
      alert("保存失败!");
}

function DoClear(){
  
   document.all.enrollNo.value="";   
   document.all.studentNo.value="";
   document.all.stuName.value="";
   
   document.all.gender[2].checked=true; 
   document.all.majorin.options[0].selected=true;  
   document.all.fromProvince.options[0].selected=true;
   
   document.all.henrollNo.value="";
   document.all.hstudentNo.value="";
   document.all.hmajorin.value="";
   document.all.hstuName.value="";
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
   
   document.all.henrollNo.value=document.all.enrollNo.value;
   document.all.hstudentNo.value=document.all.studentNo.value;
   
   for(var i=0;i<document.all.gender.length;i++){
       if(document.all.gender[i].checked)
            document.all.hgender.value=document.all.gender[i].value;
   
   }
   
   document.all.hstuName.value=document.all.stuName.value;
   document.all.hmajorin.value=document.all.majorin.value;
   document.all.hfromProvince.value=document.all.fromProvince.value;
   
   document.stucardfeeinfoForm.action="cardfeeAction.do?method=find";
   document.stucardfeeinfoForm.submit();
   
}

init();

function init(){

   var sflag=1;
   if(document.all.ck_ecardPayed!=null&&document.all.ck_ecardPayed.length>1){
          for(var i=0;i<document.all.ck_ecardPayed.length;i++){
              if(!document.all.ck_ecardPayed[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall1.checked=true;
          }
    } 
    sflag=1;
    if(document.all.ck_bathcardPayed!=null&&document.all.ck_bathcardPayed.length>1){
          for(var i=0;i<document.all.ck_bathcardPayed.length;i++){
              if(!document.all.ck_bathcardPayed[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall2.checked=true;
          }
    }   
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

function DoCheckall1(ckall){

    if(ckall.checked){
   
      if(document.all.ck_ecardPayed.length>1){   
       for(var i=0;i<document.all.ck_ecardPayed.length;i++){
              if(document.all.ck_ecardPayed[i].checked==false)
                  document.all.ck_ecardPayed[i].click();
              document.all.ck_ecardPayed[i].checked=true;
       }       
       }
       else{
          if(document.all.ck_ecardPayed.checked==false)
              document.all.ck_ecardPayed.click();
          document.all.ck_ecardPayed.checked=true;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.ck_ecardPayed.length>1){
       for(var i=0;i<document.all.ck_ecardPayed.length;i++){
            if(document.all.ck_ecardPayed[i].checked==true)
                document.all.ck_ecardPayed[i].click();
            document.all.ck_ecardPayed[i].checked=false;
       }
      }
      else{
         if(document.all.ck_ecardPayed.checked==true)
             document.all.ck_ecardPayed.click();
         document.all.ck_ecardPayed.checked=false;
      }
   }

}

function DoCheckall2(ckall){
   
   if(ckall.checked){
   
      if(document.all.ck_bathcardPayed.length>1){   
       for(var i=0;i<document.all.ck_bathcardPayed.length;i++){
            if(document.all.ck_bathcardPayed[i].checked==false)
                  document.all.ck_bathcardPayed[i].click();
              document.all.ck_bathcardPayed[i].checked=true;
       }       
       }
       else{
         if(document.all.ck_bathcardPayed.checked==false)
                  document.all.ck_bathcardPayed.click();
          document.all.ck_bathcardPayed.checked=true;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.ck_bathcardPayed.length>1){
       for(var i=0;i<document.all.ck_bathcardPayed.length;i++){
           if(document.all.ck_bathcardPayed[i].checked==true)
                  document.all.ck_bathcardPayed[i].click();
              document.all.ck_bathcardPayed[i].checked=false;
       }
      }
      else{
        if(document.all.ck_bathcardPayed.checked==true)
                  document.all.ck_bathcardPayed.click();
         document.all.ck_bathcardPayed.checked=false;
      }
   }

}

function DoCheck1(ck,hid){
    
   var sflag=1;
   var usflag=1;  
   //alert(hid);
   if(ck.checked){
       
      eval("document.stucardfeeinfoForm.ecardPayed"+hid+".value='1';");
    
      if(document.all.ck_ecardPayed.length>1){
          for(var i=0;i<document.all.ck_ecardPayed.length;i++){
              if(!document.all.ck_ecardPayed[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall1.checked=true;
          }
       } 
 
   }
   else if(ck.checked==false){
   
      //alert("1 not checked");
       
      eval("document.stucardfeeinfoForm.ecardPayed"+hid+".value='0';");
      document.all.checkall1.checked=false;    
       if(document.all.ck_ecardPayed.length>1){
          for(var i=0;i<document.all.ck_ecardPayed.length;i++){
              if(document.all.ck_ecardPayed[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall1.checked=false;
          }
       } 
   }
   //alert(eval("document.stucardfeeinfoForm.ecardPayed"+hid+".value"));
    
}

function DoCheck2(ck,hid){
  
   var sflag=1;
   var usflag=1; 

   if(ck.checked){
       
      eval("document.stucardfeeinfoForm.bathcardPayed"+hid+".value='1';");
      
      if(document.all.ck_bathcardPayed.length>1){
          for(var i=0;i<document.all.ck_bathcardPayed.length;i++){
              if(!document.all.ck_bathcardPayed[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall2.checked=true;
          }
       } 
   
   }
   else if(ck.checked==false){
       
      eval("document.stucardfeeinfoForm.bathcardPayed"+hid+".value='0';");
      document.all.checkall2.checked=false;
      if(document.all.ck_bathcardPayed.length>1){
          for(var i=0;i<document.all.ck_bathcardPayed.length;i++){
              if(document.all.ck_bathcardPayed[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall2.checked=false;
          }
       } 
      
   }
   //alert(eval("document.stucardfeeinfoForm.ifChecked"+hid+".value"));
}

function DoSave(str){

   document.all.updateid.value=str; 
   
   document.stucardfeeinfoForm.action="cardfeeAction.do?method=update";
   document.stucardfeeinfoForm.submit();
}

function DoSaveAll(){

   if(document.all.updateid.value==""){
        alert("请选择要进行批量保存的记录！");
        return;
   }
   
   document.stucardfeeinfoForm.action="cardfeeAction.do?method=updateall";
   document.stucardfeeinfoForm.submit();
  
}

</script>