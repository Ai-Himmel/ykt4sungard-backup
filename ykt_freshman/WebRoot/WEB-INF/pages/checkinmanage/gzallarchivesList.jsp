<%@page pageEncoding="GBK"%>
<%@ page import="java.util.Date" %>
<%@ page import="java.text.SimpleDateFormat" %>

<%
  Date now = new Date();

  SimpleDateFormat formatter1 = new SimpleDateFormat ("HH':'mm':'ss");
  String dateStr = formatter1.format(now);
  String hour = dateStr.substring(0,2);
  String minute = dateStr.substring(3,5);
  String second = dateStr.substring(6,8);
%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "gzarchivesAction.do?method=allfind">

<br>

<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02"><strong><font class="medium"><bean:message bundle="checkinmanage" key="archives.alltitle"/></font></strong></td>
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
              <td width="15%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
            </tr>
            <tr align="center" valign=center> 
              <td width="15%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="stuName" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                <bean:message bundle="checkinmanage" key="checkin.gender"/> </td>
              <td align="left" valign="middle" class="tableHeader3" >
              <input name="gender" type="radio" value="1"><bean:message bundle="checkinmanage" key="checkin.male"/>&nbsp;&nbsp;&nbsp;
              <input name="gender" type="radio" value="2"><bean:message bundle="checkinmanage" key="checkin.female"/>&nbsp;&nbsp;&nbsp;
              <input name="gender" type="radio" value="" checked><bean:message bundle="checkinmanage" key="checkin.unknown"/>
              </td>              
            </tr>
            <tr align="center" valign=center>
              <td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
               <bean:message bundle="checkinmanage" key="checkin.classNo"/> </td>
              <td align="left" valign="middle" class="tableHeader3" colspan="3">
              <select name="classNo" class="select01">
                  <option value="" checked><bean:message bundle="checkinmanage" key="checkin.select"/></option>
                  <logic:present name="classlist" scope="request">
                   <logic:iterate name="classlist" id="col" type="java.util.Map">
                    <option value="<bean:write name="col" property="classNo"/>"><bean:write name="col" property="classNo"/></option>
                   </logic:iterate>
                   </logic:present>
             </select>
              </td>              
               <td align="right" valign="middle" class="tableHeader2" style="display:none"><bean:message bundle="checkinmanage" key="checkin.fromProvince"/></td>
               <td align="left" valign="middle" class="tableHeader3" style="display:none"> 
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
            <input name="hfromProvince" type="hidden" value="<bean:write name="stuinfo" property="fromProvince"/>">
            </logic:present>   
            <logic:notPresent name="stuinfo" scope="request">  
            <input name="henrollNo" type="hidden" value=""> 
            <input name="hstudentNo" type="hidden" value=""> 
            <input name="hgender" type="hidden" value=""> 
            <input name="hstuName" type="hidden" value="">              
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
  <logic:present name="checkinlist" scope="request">
  <logic:iterate name="checkinlist" id="cl" type="java.util.Map" length="1">
  <tr> 
      <td height="30" align="left" valign="middle" class="medium">&nbsp;</td>
  </tr>
  </logic:iterate>
  </logic:present>
  
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input type="hidden" name="updateid" value=""><input type="hidden" name="method" value="allfind">
          <logic:present name="checkinlist" scope="request">
          <thead>
           <tr align="center" valign=center> 
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.selectall"/><input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td width="10%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td width="10%" rowspan="2" valign="middle" class="tableHeader" nowrap>出生日期</td>
              <td width="12%" rowspan="2" valign="middle" class="tableHeader" style="display:none"><bean:message bundle="checkinmanage" key="checkin.majorin"/></td>
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" style="display:none"><bean:message bundle="checkinmanage" key="checkin.fromProvince"/></td>
              <td width="10%" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="archives.hasSubmitted"/></td>
              <td width="8%" height="22" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="archives.archiveSubmit"/></td>
              <td rowspan="2" width="22%" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="archives.memo"/></td>
              <td rowspan="2" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="checkin.saveondisk"/></td>
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
		  <pg:pager url="./gzarchivesAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="method" />
           <pg:param name="henrollNo" />
           <pg:param name="hstudentNo" />
           <pg:param name="hgender" />
           <pg:param name="hstuName" />
           <pg:param name="hclassNo" />
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
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="birthday"/>&nbsp;</td>
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
              
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                  <c:choose><c:when test="${cl.ifSubmitted == '1'}">
                    <input type="checkbox" name="ck_ifSubmitted" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" checked>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.ifSubmitted == '0'}">
                    <input type="checkbox" name="ck_ifSubmitted" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')">
                  </c:when></c:choose>                
                  <input name="ifSubmitted<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifSubmitted"/>" >
              </td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                  <c:choose><c:when test="${cl.archiveSubmit== '1'}">
                   <input type="checkbox" name="ck_archiveSubmit" onClick="DoCheck2(this,'<bean:write name="cl" property="id"/>')" checked>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.archiveSubmit== '0'}">
                   <input type="checkbox" name="ck_archiveSubmit" onClick="DoCheck2(this,'<bean:write name="cl" property="id"/>')">
                  </c:when></c:choose>
                  <input name="archiveSubmit<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="archiveSubmit"/>">
              </td>
              
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <textarea name="memo<bean:write name="cl" property="id"/>" cols=20 rows=2><bean:write name="cl" property="memo"/></textarea>
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
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="birthday"/>&nbsp;</td>
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
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
                  <c:choose><c:when test="${cl.ifSubmitted == '1'}">
                    <input type="checkbox" name="ck_ifSubmitted" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" checked>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.ifSubmitted == '0'}">
                    <input type="checkbox" name="ck_ifSubmitted" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')">
                  </c:when></c:choose>                
                  <input name="ifSubmitted<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifSubmitted"/>">
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
                  <c:choose><c:when test="${cl.archiveSubmit == '1'}">
                   <input type="checkbox" name="ck_archiveSubmit" onClick="DoCheck2(this,'<bean:write name="cl" property="id"/>')" checked>
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.archiveSubmit == '0'}">
                   <input type="checkbox" name="ck_archiveSubmit" onClick="DoCheck2(this,'<bean:write name="cl" property="id"/>')">
                  </c:when></c:choose>
                  <input name="archiveSubmit<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="archiveSubmit"/>">
              </td>
                     
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <textarea name="memo<bean:write name="cl" property="id"/>" cols=20 rows=2><bean:write name="cl" property="memo"/></textarea>
              </td>  
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
                <input name="save" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.save"/>" onClick="DoSave('<bean:write name="cl" property="id"/>')" >                
              </td> 
            </tr>            
            </c:when></c:choose>
            <input type="hidden" name="studentNo<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="studentNo"/>">
            <input type="hidden" name="enrollNo<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="enrollNo"/>">
            <input type="hidden" name="enrollYear<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="enrollYear"/>">
            <input type="hidden" name="updatorId<bean:write name="cl" property="id"/>" value="<%=(String)session.getAttribute("userName")%>">
            <input type="hidden" name="hasArchives<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="hasArchives"/>">
            <input type="hidden" name="hasStuarchive<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="hasStuarchive"/>">
            <input type="hidden" name="hasLeagueFile<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="hasLeagueFile"/>">
            <input type="hidden" name="hasRegform<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="hasRegform"/>">
            <input type="hidden" name="otherFiles<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="otherFiles"/>">
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
           <tr align="center" valign=center> 
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.selectall"/><input type="checkbox" name="checkall" onClick="DoCheckall(this)"></td>
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td width="10%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td width="10%" rowspan="2" valign="middle" class="tableHeader" nowrap>出生日期</td>
              <td width="12%" rowspan="2" valign="middle" class="tableHeader" style="display:none"><bean:message bundle="checkinmanage" key="checkin.majorin"/></td>
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td width="8%" rowspan="2" valign="middle" class="tableHeader" style="display:none"><bean:message bundle="checkinmanage" key="checkin.fromProvince"/></td>
              <td width="10%" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="archives.hasSubmitted"/></td>
              <td width="8%" height="22" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="archives.archiveSubmit"/></td>
              <td rowspan="2" width="22%" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="archives.memo"/></td>
              <td rowspan="2" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="checkin.saveondisk"/></td>
            </tr>
             <tr align="center" valign=center>             
              <td valign="middle" class="tableHeader" > <input type="checkbox" name="checkall1" onClick="DoCheckall1(this)">
                <span class="small"><bean:message bundle="checkinmanage" key="checkin.selectall"/></span></td>
              <td height="22" valign="middle" class="tableHeader" > <input type="checkbox" name="checkall2" onClick="DoCheckall2(this)"> 
                <span class="small"><bean:message bundle="checkinmanage" key="checkin.selectall"/></span></td>
            </tr>
            </thead>
            
             <!--page offset start -->
		  <pg:pager url="./allarchiveslistpageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="henrollNo" />
           <pg:param name="hstudentNo" />
           <pg:param name="hgender" />
           <pg:param name="hstuName" />
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

setTimeout('DoInit()',500);

function DoInit(){
  
  document.all.enrollNo.value=document.all.henrollNo.value;
  document.all.studentNo.value=document.all.hstudentNo.value;  
  document.all.stuName.value=document.all.hstuName.value;
  
  for(var i=0;i<document.all.classNo.length;i++){
       if(document.all.hclassNo.value==document.all.classNo[i].value){
           document.all.classNo[i].selected=true;
       }
   }  
  for(var i=0;i<document.all.gender.length;i++){
       if(document.all.hgender.value==document.all.gender[i].value)
            document.all.gender[i].checked=true;
   
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
   
   document.all.classNo.options[0].selected=true;
   document.all.gender[2].checked=true;   
   document.all.fromProvince.options[0].selected=true;
   
   document.all.henrollNo.value="";
   document.all.hstudentNo.value="";
   document.all.hclassNo.value="";
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
   
   document.all.hclassNo.value=document.all.classNo.value;
   document.all.henrollNo.value=document.all.enrollNo.value;
   document.all.hstudentNo.value=document.all.studentNo.value;
   
   for(var i=0;i<document.all.gender.length;i++){
       if(document.all.gender[i].checked)
            document.all.hgender.value=document.all.gender[i].value;
   
   }
   
   document.all.hstuName.value=document.all.stuName.value;
   document.all.hfromProvince.value=document.all.fromProvince.value;
   
   document.stuarchivesinfoForm.action="gzarchivesAction.do?method=allfind";
   document.stuarchivesinfoForm.submit();
   
}

init();

function init(){

   var sflag=1;
   if(document.all.ck_ifSubmitted!=null&&document.all.ck_ifSubmitted.length>1){
          for(var i=0;i<document.all.ck_ifSubmitted.length;i++){
              if(!document.all.ck_ifSubmitted[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall1.checked=true;
          }
    }
    sflag=1;
   if(document.all.ck_archiveSubmit!=null&&document.all.ck_archiveSubmit.length>1){
          for(var i=0;i<document.all.ck_archiveSubmit.length;i++){
              if(!document.all.ck_archiveSubmit[i].checked){
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
   
      if(document.all.ck_ifSubmitted!=null&&document.all.ck_ifSubmitted.length>1){   
       for(var i=0;i<document.all.ck_ifSubmitted.length;i++){
              if(document.all.ck_ifSubmitted[i].checked==false)
                  document.all.ck_ifSubmitted[i].click();
              document.all.ck_ifSubmitted[i].checked=true;
       }       
       }
       else{
          if(document.all.ck_ifSubmitted.checked==false)
              document.all.ck_ifSubmitted.click();
          document.all.ck_ifSubmitted.checked=true;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.ck_ifSubmitted!=null&&document.all.ck_ifSubmitted.length>1){
       for(var i=0;i<document.all.ck_ifSubmitted.length;i++){
            if(document.all.ck_ifSubmitted[i].checked==true)
                document.all.ck_ifSubmitted[i].click();
            document.all.ck_ifSubmitted[i].checked=false;
       }
      }
      else{
         if(document.all.ck_ifSubmitted.checked==true)
             document.all.ck_ifSubmitted.click();
         document.all.ck_ifSubmitted.checked=false;
      }
   }

}

function DoCheckall2(ckall){
   
   if(ckall.checked){
   
      if(document.all.ck_archiveSubmit!=null&&document.all.ck_archiveSubmit.length>1){   
       for(var i=0;i<document.all.ck_archiveSubmit.length;i++){
            if(document.all.ck_archiveSubmit[i].checked==false)
                  document.all.ck_archiveSubmit[i].click();
              document.all.ck_archiveSubmit[i].checked=true;
       }       
       }
       else{
         if(document.all.ck_archiveSubmit.checked==false)
                  document.all.ck_archiveSubmit.click();
          document.all.ck_archiveSubmit.checked=true;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.ck_archiveSubmit!=null&&document.all.ck_archiveSubmit.length>1){
       for(var i=0;i<document.all.ck_archiveSubmit.length;i++){
           if(document.all.ck_archiveSubmit[i].checked==true)
                  document.all.ck_archiveSubmit[i].click();
              document.all.ck_archiveSubmit[i].checked=false;
       }
      }
      else{
        if(document.all.ck_archiveSubmit.checked==true)
                  document.all.ck_archiveSubmit.click();
         document.all.ck_archiveSubmit.checked=false;
      }
   }

}

function DoCheck1(ck,hid){
    
   var sflag=1;
   var usflag=1;  
   //alert(hid);
   if(ck.checked){
       
      eval("document.stuarchivesinfoForm.ifSubmitted"+hid+".value='1';");
    
      if(document.all.ck_ifSubmitted!=null&&document.all.ck_ifSubmitted.length>1){
          for(var i=0;i<document.all.ck_ifSubmitted.length;i++){
              if(!document.all.ck_ifSubmitted[i].checked){
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
       
      eval("document.stuarchivesinfoForm.ifSubmitted"+hid+".value='0';");
      document.all.checkall1.checked=false;    
       if(document.all.ck_ifSubmitted!=null&&document.all.ck_ifSubmitted.length>1){
          for(var i=0;i<document.all.ck_ifSubmitted.length;i++){
              if(document.all.ck_ifSubmitted[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall1.checked=false;
          }
       } 
   }
   //alert(eval("document.stucheckininfoForm.ifCheckedin"+hid+".value"));
    
}

function DoCheck2(ck,hid){
  
   var sflag=1;
   var usflag=1; 

   if(ck.checked){
       
      eval("document.stuarchivesinfoForm.archiveSubmit"+hid+".value='1';");
      
      if(document.all.ck_archiveSubmit!=null&&document.all.ck_archiveSubmit.length>1){
          for(var i=0;i<document.all.ck_archiveSubmit.length;i++){
              if(!document.all.ck_archiveSubmit[i].checked){
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
       
      eval("document.stuarchivesinfoForm.archiveSubmit"+hid+".value='0';");
      document.all.checkall2.checked=false;
      if(document.all.ck_archiveSubmit!=null&&document.all.ck_archiveSubmit.length>1){
          for(var i=0;i<document.all.ck_archiveSubmit.length;i++){
              if(document.all.ck_archiveSubmit[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall2.checked=false;
          }
       } 
      
   }
   //alert(eval("document.stucheckininfoForm.ifChecked"+hid+".value"));
}

function DoSave(str){

   document.all.updateid.value=str;
   
   if(eval("document.all.memo"+str+".value.length>100")){
   
       alert("备注过长!");
       return;
   
   }
   
   document.stuarchivesinfoForm.action="gzarchivesAction.do?method=allupdate";
   document.stuarchivesinfoForm.submit();
}

function DoSaveAll(){

   if(document.all.updateid.value==""){
        alert("请选择要进行批量保存的记录！");
        return;
   }
   
   var x = document.getElementsByTagName('textarea');
   for (var i=0;i<x.length;i++)
   {
      if (x[i].value.length>100){
          alert("有备注过长!");
          return;
      }
   }
   
   document.stuarchivesinfoForm.action="gzarchivesAction.do?method=allupdateall";
   document.stuarchivesinfoForm.submit();
  
}

</script>