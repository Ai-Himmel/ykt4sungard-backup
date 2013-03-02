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

<html:form action = "stuadddelAction.do?method=findnotfudan">

<br>

<table width="170%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="center" valign="middle" class="tdborder02">
    <TABLE width="65%" align="center">
		<tr>
			<td>
				<strong><font class="medium">非学历新生基本信息查询</font></strong>
			</td>
		</tr>
	</table>
    </td>
  </tr>
  <tr> 
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="left" valign="top" ><table 
        width=60% border=1 align=left 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign=center>
              <td width="10%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>  
              <td width="10%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                <bean:message bundle="checkinmanage" key="checkin.stuName"/> </td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="stuName" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>            
              <td width="10%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                <bean:message bundle="checkinmanage" key="checkin.gender"/> </td>
              <td align="left" valign="middle" class="tableHeader3" >
              <select name="gender" class="select01">
                  <option value="" checked>-------------------------</option>
                  <option value="1" >男</option>
                  <option value="2" >女</option>
              </td>
            </tr>
            <tr align="center" valign=center> 
              <td width="10%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                录取院系</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <select name="department" class="select01">
                  <option value="" checked>-------------------------</option>
                  <logic:present name="departlist" scope="request">
                   <logic:iterate name="departlist" id="dl" type="java.util.Map">
                    <option value="<bean:write name="dl" property="deptCode"/>"><bean:write name="dl" property="deptName"/></option>
                   </logic:iterate>
                   </logic:present>
             </select>
              </td>
              <td width="10%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
                录取专业</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <select name="majorin" class="select01">
                  <option value="" checked>-------------------------</option>
                  <logic:present name="majorinlist" scope="request">
                   <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                    <option value="<bean:write name="ml" property="dictValue"/>"><bean:write name="ml" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
             </select>
              </td> 
              <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >政治面貌</td>
             <td align="left" valign="middle" class="tableHeader3" >
               <select name="polityBg" class="select01">
                  <option value="" checked>-------------------------</option>
                   <logic:present name="politylist" scope="request">
                   <logic:iterate name="politylist" id="pl" type="java.util.Map">
                    <option value="<bean:write name="pl" property="dictValue"/>"><bean:write name="pl" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
             </td>             
            </tr>
            <tr align="center" valign=center>
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >民族</td>
             <td align="left" valign="middle" class="tableHeader3" >
               <select name="nation" class="select01">
                  <option value="" checked>-------------------------</option>
                   <logic:present name="nationlist" scope="request">
                   <logic:iterate name="nationlist" id="nl" type="java.util.Map">
                    <option value="<bean:write name="nl" property="dictValue"/>"><bean:write name="nl" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
             </td>
             <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >生源地</td>
             <td align="left" valign="middle" class="tableHeader3" >
               <select name="fromProvince" class="select01">
                  <option value="" checked>-------------------------</option>
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
                  <option value="" checked>-------------------------</option>
                   <logic:present name="countrylist" scope="request">
                   <logic:iterate name="countrylist" id="ctyl" type="java.util.Map">
                    <option value="<bean:write name="ctyl" property="dictValue"/>"><bean:write name="ctyl" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
              </td>
            </tr>
            <tr align="center" valign=center>
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >培养层次</td>
             <td align="left" valign="middle" class="tableHeader3" >
               <select name="cultureMode" class="select01">
                  <option value="" checked>-------------------------</option>
                   <logic:present name="culturelist" scope="request">
                   <logic:iterate name="culturelist" id="cul" type="java.util.Map">
                    <option value="<bean:write name="cul" property="dictValue"/>"><bean:write name="cul" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
             </td>
             <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >学生性质</td>
             <td align="left" valign="middle" class="tableHeader3" >
               <select name="studentChar" class="select01">
                  <option value="" checked>-------------------------</option>
                   <logic:present name="stucharlist" scope="request">
                   <logic:iterate name="stucharlist" id="scl" type="java.util.Map">
                    <option value="<bean:write name="scl" property="dictValue"/>"><bean:write name="scl" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
             </td> 
              <td align="right" valign="middle" class="tableHeader2" >学生类别</td>
              <td align="left" valign="middle" class="tableHeader3" > 
                 <select name="studentType" class="select01">
                  <option value="" checked>-------------------------</option>
                   <logic:present name="stutypelist" scope="request">
                   <logic:iterate name="stutypelist" id="styl" type="java.util.Map">
                    <option value="<bean:write name="styl" property="dictValue"/>"><bean:write name="styl" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
              </td>
            </tr>
            <tr align="center" valign=center>
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >生日</td>
             <td align="left" valign="middle" class="tableHeader3" ><input 
            name="birthday" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();">
             </td>
             <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >家庭电话</td>
             <td align="left" valign="middle" class="tableHeader3" ><input 
            name="homeTelephone" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();">
             </td> 
              <td align="right" valign="middle" class="tableHeader2" >管理院系</td>
              <td align="left" valign="middle" class="tableHeader3" > 
                 <select name="adminCollege" class="select01">
                  <option value="" checked>-------------------------</option>
                   <logic:present name="admincollist" scope="request">
                   <logic:iterate name="admincollist" id="adl" type="java.util.Map">
                    <option value="<bean:write name="adl" property="deptCode"/>"><bean:write name="adl" property="deptName"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
              </td>
            </tr>
            <tr align="center" valign=center>            
            <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >证件类型</td>
             <td align="left" valign="middle" class="tableHeader3" >
               <select name="idType" class="select01">
                  <option value="" checked>-------------------------</option>
                   <logic:present name="idtypelist" scope="request">
                   <logic:iterate name="idtypelist" id="idl" type="java.util.Map">
                    <option value="<bean:write name="idl" property="dictValue"/>"><bean:write name="idl" property="dictCaption"/></option>
                   </logic:iterate>
                   </logic:present>
                </select>
             </td>
             <td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >证件号码</td>
             <td align="left" valign="middle" class="tableHeader3" colspan="3"><input 
            name="idCard" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();">
            </td>              
            </tr>
            <logic:present name="stuinfo" scope="request">             
            <input name="hstudentNo" type="hidden" value="<bean:write name="stuinfo" property="studentNo"/>"> 
            <input name="hstuName" type="hidden" value="<bean:write name="stuinfo" property="stuName"/>">
            <input name="hgender" type="hidden" value="<bean:write name="stuinfo" property="gender"/>">   
            <input name="hdepartment" type="hidden" value="<bean:write name="stuinfo" property="department"/>">           
            <input name="hmajorin" type="hidden" value="<bean:write name="stuinfo" property="majorin"/>">
            <input name="hnation" type="hidden" value="<bean:write name="stuinfo" property="nation"/>">
            <input name="hnationality" type="hidden" value="<bean:write name="stuinfo" property="nationality"/>">
            <input name="hfromProvince" type="hidden" value="<bean:write name="stuinfo" property="fromProvince"/>">
            <input name="hidType" type="hidden" value="<bean:write name="stuinfo" property="idType"/>"> 
            <input name="hidCard" type="hidden" value="<bean:write name="stuinfo" property="idCard"/>">
            <input name="hcultureMode" type="hidden" value="<bean:write name="stuinfo" property="cultureMode"/>"> 
            <input name="hstudentChar" type="hidden" value="<bean:write name="stuinfo" property="studentChar"/>"> 
            <input name="hstudentType" type="hidden" value="<bean:write name="stuinfo" property="studentType"/>"> 
            <input name="hpolityBg" type="hidden" value="<bean:write name="stuinfo" property="polityBg"/>"> 
            <input name="hbirthday" type="hidden" value="<bean:write name="stuinfo" property="birthday"/>"> 
            <input name="hhomeTelephone" type="hidden" value="<bean:write name="stuinfo" property="homeTelephone"/>">
            <input name="hadminCollege" type="hidden" value="<bean:write name="stuinfo" property="adminCollege"/>"> 
            </logic:present>   
            <logic:notPresent name="stuinfo" scope="request">              
            <input name="hstudentNo" type="hidden" value="">            
            <input name="hstuName" type="hidden" value=""> 
            <input name="hgender" type="hidden" value=""> 
            <input name="hdepartment" type="hidden" value="">
            <input name="hmajorin" type="hidden" value=""> 
            <input name="hnation" type="hidden" value=""> 
            <input name="hnationality" type="hidden" value="">              
            <input name="hfromProvince" type="hidden" value="">
            <input name="hidType" type="hidden" value=""> 
            <input name="hidCard" type="hidden" value="">
            <input name="hcultureMode" type="hidden" value=""> 
            <input name="hstudentChar" type="hidden" value=""> 
            <input name="hstudentType" type="hidden" value=""> 
            <input name="hpolityBg" type="hidden" value=""> 
            <input name="hbirthday" type="hidden" value=""> 
            <input name="hhomeTelephone" type="hidden" value=""> 
            <input name="hadminCollege" type="hidden" value=""> 
             </logic:notPresent>
          </tbody>
        </table></td>
  </tr>
  <tr>
    <td height="30" align="left" valign="middle" class="tdborder02"> 
      <input name="Submit" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.lookfor"/>" onClick="DoFind()">
      <input name="Reset" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.reset"/>" onClick="DoClear()"> 
    </td>
  </tr>
  <logic:present name="stuinfolist" scope="request">
  <tr>
      <td height="30" align="left" valign="middle" colspan="2">      
         <a href="javascript:DoExport()">导出Excel<IMG src="./pages/style/default/images/xls.gif" border="0"></a>      
      </td>
    </tr>  
  </logic:present>
  <input name="doexl" type="hidden" value=""><input name="orderby" type="hidden" value="">
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody><input type="hidden" name="updateid" value="">
           <logic:present name="stuinfolist" scope="request">
           <thead>
           <tr align="center" valign=center> 
              <td width="4%" height="24" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')"><bean:message bundle="checkinmanage" key="checkin.studentNo"/></a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('stuName')"><bean:message bundle="checkinmanage" key="checkin.stuName"/></a></td>
              <td width="4%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('gender')"><bean:message bundle="checkinmanage" key="checkin.gender"/></a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('department')">录取院系</a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('majorin')">录取专业</a></td>
              <td width="4%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('nation')">民族</a></td>
              <td width="4%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('nationality')">国籍</a></td>
              <td width="4%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('fromProvince')">生源地</a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('idType')">证件类型</a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('idCard')">证件号码</a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('cultureMode')">培养层次</a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('studentChar')">学生性质</a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('studentType')">学生类别</a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('polityBg')">政治面貌</a></td>
              <td width="4%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('birthday')">生日</a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('homeTelephone')">家庭电话</a></td>
              <td width="6%" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('adminCollege')">管理院系</a></td>              
              <td width="6%" valign="middle" class="tableHeader" nowrap><a style="font-size:14px;color: black" href="javascript:DoSort('stuName')"><bean:message bundle="checkinmanage" key="checkin.stuName"/></a></td>
              <td height="24" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')"><bean:message bundle="checkinmanage" key="checkin.studentNo"/></a></td>
           </tr>
           </thead>
           <!--page offset start -->
            <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		     <pg:pager url="./stuadddelAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
               <%-- keep track of preference --%>
                <pg:param name="method" />
                <pg:param name="hstudentNo" />
                <pg:param name="hstuName" /> 
                <pg:param name="hgender" /> 
                <pg:param name="hdepartment" />
                <pg:param name="hmajorin" /> 
                <pg:param name="hnation" /> 
                <pg:param name="hnationality" />              
                <pg:param name="hfromProvince" />
                <pg:param name="hidType" /> 
                <pg:param name="hidCard" />
                <pg:param name="hcultureMode" /> 
                <pg:param name="hstudentChar" /> 
                <pg:param name="hstudentType" /> 
                <pg:param name="hpolityBg" /> 
                <pg:param name="hbirthday" /> 
                <pg:param name="hhomeTelephone" /> 
                <pg:param name="hadminCollege" />
                <pg:param name="orderby" />
		        <pg:param name="horder" />
		   
		    <%-- save pager offset during form changes --%>
		    <input type="hidden" name="pager.offset" value="<%= offset %>"> 
            <logic:iterate name="stuinfolist" id="cl" type="java.util.Map"  indexId="i">
             <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=center bgcolor="#FFFFFF" >             
              <td height="24" align="center" valign="middle"><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle"><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle"><bean:write name="cl" property="genderName"/></td>
              <td align="center" valign="middle"><bean:write name="cl" property="departmentName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="majorinName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="nationName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="nationalityName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="fromProvinceName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="idTypeName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="idCard"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="cultureModeName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="studentCharName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="studentTypeName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="polityBgName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="birthday"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="homeTelephone"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="adminCollegeName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle"><bean:write name="cl" property="studentNo"/></td>
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5" >                
              <td height="24" align="center" valign="middle"><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle"><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle"><bean:write name="cl" property="genderName"/></td>
              <td align="center" valign="middle"><bean:write name="cl" property="departmentName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="majorinName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="nationName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="nationalityName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="fromProvinceName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="idTypeName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="idCard"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="cultureModeName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="studentCharName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="studentTypeName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="polityBgName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="birthday"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="homeTelephone"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="adminCollegeName"/>&nbsp;</td>
              <td align="center" valign="middle"><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle"><bean:write name="cl" property="studentNo"/></td>
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
		     <pg:pager url="./stuadddelAction.do" items="0" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
             <%-- keep track of preference --%>
               <pg:param name="method" />
               <pg:param name="hstudentNo" />
                <pg:param name="hstuName" /> 
                <pg:param name="hgender" /> 
                <pg:param name="hdepartment" />
                <pg:param name="hmajorin" /> 
                <pg:param name="hnation" /> 
                <pg:param name="hnationality" />              
                <pg:param name="hfromProvince" />
                <pg:param name="hidType" /> 
                <pg:param name="hidCard" />
                <pg:param name="hcultureMode" /> 
                <pg:param name="hstudentChar" /> 
                <pg:param name="hstudentType" /> 
                <pg:param name="hpolityBg" /> 
                <pg:param name="hbirthday" /> 
                <pg:param name="hhomeTelephone" /> 
                <pg:param name="hadminCollege" />  
                <pg:param name="orderby" />
		        <pg:param name="horder" />           
		   
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
</table>
  <logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
  </logic:notPresent>
  <logic:present name="order" scope="request">
  <input name="horder" type="hidden" value="<bean:write name="order" />"> 
  </logic:present>
  <logic:notPresent name="order" scope="request">
  <input name="horder" type="hidden" value="a"> 
</logic:notPresent>
</html:form>
</center>

<script language="JavaScript">

setTimeout('DoInit()',30);

function DoInit(){
  
  document.all.studentNo.value=document.all.hstudentNo.value;   
  document.all.stuName.value=document.all.hstuName.value;
  document.all.idCard.value=document.all.hidCard.value;
  document.all.birthday.value=document.all.hbirthday.value; 
  document.all.homeTelephone.value=document.all.hhomeTelephone.value; 
  
  for(var i=0;i<document.all.gender.length;i++){
       if(document.all.hgender.value==document.all.gender[i].value){
            document.all.gender.options[i].selected=true;
            break;
       }
   }  
   
   for(var i=0;i<document.all.department.length;i++){                              
                                                                             
      if(document.all.hdepartment.value==document.all.department.options[i].value){
          document.all.department.options[i].selected=true;                     
          break;                                                             
       }                                                                     
  } 
   
   for(var i=0;i<document.all.majorin.length;i++){
     
      if(document.all.hmajorin.value==document.all.majorin.options[i].value){
          document.all.majorin.options[i].selected=true;
          break;
       }
  }  
  
  for(var i=0;i<document.all.nation.length;i++){                              
                                                                             
      if(document.all.hnation.value==document.all.nation.options[i].value){
          document.all.nation.options[i].selected=true;                     
          break;                                                             
       }                                                                     
  } 
  
  for(var i=0;i<document.all.nationality.length;i++){
     
      if(document.all.hnationality.value==document.all.nationality.options[i].value){
          document.all.nationality.options[i].selected=true;
          break;
       }
  }
  
   for(var i=0;i<document.all.fromProvince.length;i++){
     
      if(document.all.hfromProvince.value==document.all.fromProvince.options[i].value){
          document.all.fromProvince.options[i].selected=true;
          break;
       }
  } 
  
  for(var i=0;i<document.all.idType.length;i++){                              
                                                                             
      if(document.all.hidType.value==document.all.idType.options[i].value){
          document.all.idType.options[i].selected=true;                     
          break;                                                             
       }                                                                     
  } 
  
  for(var i=0;i<document.all.cultureMode.length;i++){                              
                                                                             
      if(document.all.hcultureMode.value==document.all.cultureMode.options[i].value){
          document.all.cultureMode.options[i].selected=true;                     
          break;                                                             
       }                                                                     
  } 
  
  for(var i=0;i<document.all.studentChar.length;i++){                              
                                                                             
      if(document.all.hstudentChar.value==document.all.studentChar.options[i].value){
          document.all.studentChar.options[i].selected=true;                     
          break;                                                             
       }                                                                     
  } 
  
  for(var i=0;i<document.all.studentType.length;i++){                              
                                                                             
      if(document.all.hstudentType.value==document.all.studentType.options[i].value){
          document.all.studentType.options[i].selected=true;                     
          break;                                                             
       }                                                                     
  }  
  
  for(var i=0;i<document.all.polityBg.length;i++){                              
                                                                             
      if(document.all.hpolityBg.value==document.all.polityBg.options[i].value){
          document.all.polityBg.options[i].selected=true;                     
          break;                                                             
       }                                                                     
  }  
  
  for(var i=0;i<document.all.adminCollege.length;i++){                              
                                                                             
      if(document.all.hadminCollege.value==document.all.adminCollege.options[i].value){
          document.all.adminCollege.options[i].selected=true;                     
          break;                                                             
       }                                                                     
  }   
  
  if(document.all.hmsg.value=='-1')
      alert("未查找到记录!");
}

function DoClear(){
  
   document.all.studentNo.value="";
   document.all.stuName.value="";   
   document.all.gender[0].selected=true; 
   document.all.department[0].selected=true; 
   document.all.majorin[0].selected=true; 
   document.all.nation[0].selected=true; 
   document.all.nationality[0].selected=true;       
   document.all.fromProvince[0].selected=true; 
   document.all.idType[0].selected=true; 
   document.all.idCard.value="";
   document.all.cultureMode[0].selected=true; 
   document.all.studentChar[0].selected=true; 
   document.all.studentType[0].selected=true; 
   document.all.polityBg[0].selected=true; 
   document.all.birthday.value=""; 
   document.all.homeTelephone.value=""; 
   document.all.adminCollege[0].selected=true; 
   
   
   document.all.hstudentNo.value="";   
   document.all.hstuName.value="";
   document.all.hgender.value="";
   document.all.hdepartment.value="";
   document.all.hmajorin.value=""; 
   document.all.hnation.value=""; 
   document.all.hnationality.value="";              
   document.all.hfromProvince.value="";
   document.all.hidType.value=""; 
   document.all.hidCard.value="";
   document.all.hcultureMode.value=""; 
   document.all.hstudentChar.value=""; 
   document.all.hstudentType.value=""; 
   document.all.hpolityBg.value=""; 
   document.all.hbirthday.value=""; 
   document.all.hhomeTelephone.value=""; 
   document.all.hadminCollege.value="";
}

function DoFind(){   
  
   document.all.doexl.value="";
   document.forms[0].elements["pager.offset"].value="0";
   
   document.all.hstudentNo.value=document.all.studentNo.value;
   document.all.hstuName.value=document.all.stuName.value;
   document.all.hgender.value=document.all.gender.value;
   document.all.hdepartment.value=document.all.department.value;    
   document.all.hmajorin.value=document.all.majorin.value;          
   document.all.hnation.value=document.all.nation.value;            
   document.all.hnationality.value=document.all.nationality.value;  
   document.all.hfromProvince.value=document.all.fromProvince.value;
   document.all.hidType.value=document.all.idType.value;            
   document.all.hidCard.value=document.all.idCard.value;            
   document.all.hcultureMode.value=document.all.cultureMode.value;  
   document.all.hstudentChar.value=document.all.studentChar.value;  
   document.all.hstudentType.value=document.all.studentType.value;  
   document.all.hpolityBg.value=document.all.polityBg.value;        
   document.all.hbirthday.value=document.all.birthday.value;        
   document.all.hhomeTelephone.value=document.all.homeTelephone.value;
   document.all.hadminCollege.value=document.all.adminCollege.value;
   
   document.stuadddelForm.action="stuadddelAction.do?method=findnotfudan";
   document.stuadddelForm.submit();
   
}

function DoExport(){

   document.all.doexl.value="1";
   
   document.all.hstudentNo.value=document.all.studentNo.value;
   document.all.hstuName.value=document.all.stuName.value;
   document.all.hgender.value=document.all.gender.value;
   document.all.hdepartment.value=document.all.department.value;    
   document.all.hmajorin.value=document.all.majorin.value;          
   document.all.hnation.value=document.all.nation.value;            
   document.all.hnationality.value=document.all.nationality.value;  
   document.all.hfromProvince.value=document.all.fromProvince.value;
   document.all.hidType.value=document.all.idType.value;            
   document.all.hidCard.value=document.all.idCard.value;            
   document.all.hcultureMode.value=document.all.cultureMode.value;  
   document.all.hstudentChar.value=document.all.studentChar.value;  
   document.all.hstudentType.value=document.all.studentType.value;  
   document.all.hpolityBg.value=document.all.polityBg.value;        
   document.all.hbirthday.value=document.all.birthday.value;        
   document.all.hhomeTelephone.value=document.all.homeTelephone.value;
   document.all.hadminCollege.value=document.all.adminCollege.value;
   
   document.stuadddelForm.action="stuadddelAction.do?method=findnotfudan";
   document.stuadddelForm.submit();

}

function DoSort(col){
  document.all.doexl.value="";
  document.all.orderby.value=col;
  if(document.all.horder.value=='a')
      document.all.horder.value='d';
  else if(document.all.horder.value=='d')
      document.all.horder.value='a';
      
  document.stuadddelForm.action="stuadddelAction.do?method=findnotfudan";
  document.stuadddelForm.submit();
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

</script>