<%@page pageEncoding="GBK"%>

<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "gzcheckinmanageAction.do?method=stuinfofind">

<br>

<table width="150%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="left" valign="middle" class="tdborder02">
    <TABLE width="55%" align="center">
		<tr>
			<td>
				<strong><font class="medium">班级入学信息表</font></strong>
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
        width=67% border=1 align=left 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody>
            <tr align="center" valign=center>               
              <td width="10%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="studentNo" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
              <td width="10%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
              <td align="left" valign="middle" class="tableHeader3" ><input 
            name="stuName" class="input_box"  maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();"></td>
            </tr>
            <tr align="center" valign=center> 
              <td width="10%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
               <bean:message bundle="checkinmanage" key="checkin.gender"/></td>
              <td align="left" valign="middle" class="tableHeader3" >
              <input name="gender" type="radio" value="1"><bean:message bundle="checkinmanage" key="checkin.male"/>&nbsp;&nbsp;&nbsp;
              <input name="gender" type="radio" value="2"><bean:message bundle="checkinmanage" key="checkin.female"/>&nbsp;&nbsp;&nbsp;
              <input name="gender" type="radio" value="" checked><bean:message bundle="checkinmanage" key="checkin.unknown"/>
              </td>    
              <td width=10% align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
              <td align="left" valign="middle" class="tableHeader3" >
                  <select name="s_classNo" class="select01">
                         <logic:present name="classlist" scope="request">
                          <logic:iterate name="classlist" id="col" type="java.util.Map">
                            <option value="<bean:write name="col" property="classNo"/>"><bean:write name="col" property="classNo"/></option>
                          </logic:iterate>
                         </logic:present>
                  </select>
              </td>           
            </tr>
            <tr align="center" valign=center style="display:none">
              <td width="10%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" > 
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
              <td width="10%" align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.fromProvince"/></td>
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
    <td height="30" align="center" valign="middle" class="tdborder02"><table 
        width=67% border=1 align=left 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1> 
      <tr align="right" valign=center>
      <td height="30" align="right" valign="middle" >    
      <input name="Submit" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.lookfor"/>" onClick="DoFind()">
      <input name="Reset" type="button" class="button_nor" value="<bean:message bundle="checkinmanage" key="checkin.reset"/>" onClick="DoClear()"> 
      </td>
      </tr>
    </table>
    </td>
  </tr>  
  <logic:notPresent name="checkinlist" scope="request">
  <font size="2.5" color="#990000">未查找到新生或您无权查看所列新生的入学信息！</font>
  </logic:notPresent>  
  <input type="hidden" name="updateid" value=""><input name="orderby" type="hidden" value="">
  <input name="doexl" type="hidden" value="">
  <logic:present name="checkinlist" scope="request">
  <tr>
      <td height="30" align="right" valign="middle" colspan="2">      
         <a href="javascript:DoExport()">导出Excel<IMG src="./pages/style/default/images/xls.gif" border="0"></a>      
      </td>
    </tr>  
  <tr>
  
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
          <thead>
          <tr align="center" > 
          <td width=6% align="center" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('classNo')"><bean:message bundle="checkinmanage" key="checkin.classNo"/></a></td>
          <td width=6% align="center" height="24" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')"><bean:message bundle="checkinmanage" key="checkin.studentNo"/></a></td>
          <td width=8% align="center" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('stuName')"><bean:message bundle="checkinmanage" key="checkin.stuName"/></a></td>
          <td width=4% align="center" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('gender')"><bean:message bundle="checkinmanage" key="checkin.gender"/></a></td>
          <td width=8% align="center" valign="middle" class="tableHeader" style="display:none"><a style="font-size:14px;color: black" href="javascript:DoSort('majorin')"><bean:message bundle="checkinmanage" key="checkin.majorin"/></a></td>          
          <td width=6% align="center" valign="middle" class="tableHeader" style="display:none"><a style="font-size:14px;color: black" href="javascript:DoSort('fromProvince')"><bean:message bundle="checkinmanage" key="checkin.fromProvince"/></a></td>
          
          <td width=6% align="center" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('ifCheckedin')">报到</a></td>
          <td width=6% align="center" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('ifChecked')">通知书</a></td>
          <td width=6% align="center" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('ifGotMaterial')">资料</a></td>
          <td width=8% align="center" valign="middle" class="tableHeader" nowrap><a style="font-size:14px;color: black" href="javascript:DoSort('ecardPhoto')">一卡通拍照</a></td>
          <td width=8% align="center" valign="middle" class="tableHeader" nowrap><a style="font-size:14px;color: black" href="javascript:DoSort('ifGotEcard')">正式一卡通</a></td> 
          <td width=6% align="center" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('hasArchives')">档案袋</a></td>         
          <td width=6% align="center" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('hasStuarchive')">档案</a></td>          
          <td width=6% align="center" valign="middle" class="tableHeader" ><a style="font-size:14px;color: black" href="javascript:DoSort('ifUnhealthy')">体检</a></td> 
          <td width=8% align="center" valign="middle" class="tableHeader" nowrap><a style="font-size:14px;color: black" href="javascript:DoSort('ifGotStucard')">学生证/校徽</a></td>         
          
          <td width=8% align="center" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
          <td align="center" height="24" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>               
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
		   <pg:param name="hfromProvince" />
		   <pg:param name="orderby" />
		   <pg:param name="horder" />
		   
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">  
			
            <logic:iterate name="checkinlist" id="cl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=middle bgcolor="#FFFFFF">             
              <td height="24" align="center" valign="middle" ><bean:write name="cl" property="classNo"/></td>
              <td align="center" valign="middle" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle"><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" style="display:none">
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              
              <td height="24" align="center" valign="middle" style="display:none">
              <logic:present name="arealist" scope="request">            
               <logic:iterate name="arealist" id="al" type="java.util.Map">
                <c:choose><c:when test="${al.dictValue == cl.fromProvince}">              
                <bean:write name="al" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td> 
              
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifCheckedin == '1'}">已报到
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifCheckedin == '0'}"><font color="#990000"><strong>未报到</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifChecked == '1'}">已核验
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifChecked == '0'}"><font color="#990000"><strong>未核验</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifGotMaterial == '1'}">已领取
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotMaterial == '0'}"><font color="#990000"><strong>未领取</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ecardPhoto == '1'}">已完成
              </c:when><c:otherwise>
              <font color="#990000"><strong>未完成</strong></font>
              </c:otherwise></c:choose>
              </td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifGotEcard == '1'}">已更换
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotEcard == '0'}"><font color="#990000"><strong>未更换</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.hasArchives == '1'}"><bean:message bundle="checkinmanage" key="checkin.handedin"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.hasArchives == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.nothandedin"/></strong></font>
              </c:when></c:choose>
              </td>
              
              <td align="center" valign="middle" nowrap>
              <c:choose><c:when test="${cl.hasStuarchive == '1'}">已核对&nbsp;
              </c:when></c:choose>
              <c:choose><c:when test="${cl.hasStuarchive == '0'}"><font color="#990000"><strong>未核对</strong></font>&nbsp;
              </c:when></c:choose> 
              <c:choose><c:when test="${cl.archiveSubmit == '1'}"><bean:message bundle="checkinmanage" key="archives.instate"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.archiveSubmit == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="archives.notinstate"/></strong></font>
              </c:when></c:choose>
              </td> 
              
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifUnhealthy == '0'}"><font color="#990000"><strong>未体检</strong></font>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '1'}">体检合格
              </c:when></c:choose> 
              <c:choose><c:when test="${cl.ifUnhealthy == '2'}"><font color="#990000"><strong>需复检</strong></font>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '3'}">复检合格
              </c:when></c:choose>
              </td>
              
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifGotStucard == '1'}"><bean:message bundle="checkinmanage" key="checkin.got"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotStucard == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notgot"/></strong></font>
              </c:when></c:choose>
               </td>
              
              <td align="center" valign="middle" ><bean:write name="cl" property="stuName"/></td> 
              <td height="24" align="center" valign="middle" ><bean:write name="cl" property="studentNo"/></td>         
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center bgcolor="#F6F4F5" >  
              <td height="24" align="center" valign="middle" ><bean:write name="cl" property="classNo"/></td>            
              <td align="center" valign="middle" ><bean:write name="cl" property="studentNo"/></td>
              <td align="center" valign="middle" ><bean:write name="cl" property="stuName"/></td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" style="display:none">
              <logic:present name="majorinlist" scope="request">            
               <logic:iterate name="majorinlist" id="ml" type="java.util.Map">
                <c:choose><c:when test="${ml.dictValue == cl.majorin}">              
                <bean:write name="ml" property="dictCaption"/>
                </c:when></c:choose>
               </logic:iterate>
               </logic:present>
              &nbsp;
              </td>
              
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
              
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifCheckedin == '1'}">已报到
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifCheckedin == '0'}"><font color="#990000"><strong>未报到</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifChecked == '1'}">已核验
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifChecked == '0'}"><font color="#990000"><strong>未核验</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifGotMaterial == '1'}">已领取
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotMaterial == '0'}"><font color="#990000"><strong>未领取</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ecardPhoto == '1'}">已完成
              </c:when><c:otherwise>
              <font color="#990000"><strong>未完成</strong></font>
              </c:otherwise></c:choose>
              </td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifGotEcard == '1'}">已更换
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotEcard == '0'}"><font color="#990000"><strong>未更换</strong></font>
              </c:when></c:choose>
              </td>
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.hasArchives == '1'}"><bean:message bundle="checkinmanage" key="checkin.handedin"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.hasArchives == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.nothandedin"/></strong></font>
              </c:when></c:choose>
              </td>
              
              <td align="center" valign="middle" nowrap>
              <c:choose><c:when test="${cl.hasStuarchive == '1'}">已核对&nbsp;
              </c:when></c:choose>
              <c:choose><c:when test="${cl.hasStuarchive == '0'}"><font color="#990000"><strong>未核对</strong></font>&nbsp;
              </c:when></c:choose> 
              <c:choose><c:when test="${cl.archiveSubmit == '1'}"><bean:message bundle="checkinmanage" key="archives.instate"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.archiveSubmit == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="archives.notinstate"/></strong></font>
              </c:when></c:choose>
              </td> 
              
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifUnhealthy == '0'}"><font color="#990000"><strong>未体检</strong></font>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '1'}">体检合格
              </c:when></c:choose> 
              <c:choose><c:when test="${cl.ifUnhealthy == '2'}"><font color="#990000"><strong>需复检</strong></font>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifUnhealthy == '3'}">复检合格
              </c:when></c:choose>
              </td>
              
              <td align="center" valign="middle" >
              <c:choose><c:when test="${cl.ifGotStucard == '1'}"><bean:message bundle="checkinmanage" key="checkin.got"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.ifGotStucard == '0'}"><font color="#990000"><strong><bean:message bundle="checkinmanage" key="checkin.notgot"/></strong></font>
              </c:when></c:choose>
               </td>
              
              <td align="center" valign="middle" ><bean:write name="cl" property="stuName"/></td>
              <td height="24" align="center" valign="middle" ><bean:write name="cl" property="studentNo"/></td>
            </tr>            
            </c:when></c:choose> 
             </pg:item>           
            </logic:iterate>
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
            </logic:present>
          
  <logic:notPresent name="checkinlist" scope="request">
  <tr>
      <td height="30" align="right" valign="middle" colspan="2">      
         &nbsp;      
      </td>
    </tr>  
  <tr>
  
  <tr> 
      <td align="left" valign="top">
      <table width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
          <tbody>
          <thead>
          <tr align="center" > 
          <td width=6% align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
          <td width=6% align="center" height="24" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>
          <td width=8% align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
          <td width=4% align="center" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.gender"/></td>
          <td width=8% align="center" valign="middle" class="tableHeader" style="display:none"><bean:message bundle="checkinmanage" key="checkin.majorin"/></td>          
          <td width=6% align="center" valign="middle" class="tableHeader" style="display:none"><bean:message bundle="checkinmanage" key="checkin.fromProvince"/></td>
          
          <td width=6% align="center" valign="middle" class="tableHeader" >报到</td>
          <td width=6% align="center" valign="middle" class="tableHeader" >通知书</td>
          <td width=6% align="center" valign="middle" class="tableHeader" >资料</td>
          <td width=8% align="center" valign="middle" class="tableHeader" nowrap>一卡通拍照</td>
          <td width=8% align="center" valign="middle" class="tableHeader" nowrap>一卡通/浴卡</td> 
          <td width=6% align="center" valign="middle" class="tableHeader" >档案袋</td>         
          <td width=6% align="center" valign="middle" class="tableHeader" nowrap>档案</td>          
          <td width=6% align="center" valign="middle" class="tableHeader" >体检</td> 
          <td width=6% align="center" valign="middle" class="tableHeader" nowrap>学生证/校徽</td>         
          
          <td width=8% align="center" valign="middle" class="tableHeader" nowrap><bean:message bundle="checkinmanage" key="checkin.stuName"/></td>
          <td align="center" height="24" valign="middle" class="tableHeader" ><bean:message bundle="checkinmanage" key="checkin.studentNo"/></td>               
          </tr>
          </thead>          
           <!--page offset start -->
		  <pg:pager url="./classcheckinpageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="hstuName" />
           <pg:param name="hstudentNo" />
           <pg:param name="hgender" />
           <pg:param name="hmajorin" />           
		   <pg:param name="hfromProvince" />
		   <pg:param name="orderby" />
		   <pg:param name="horder" />
		   
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
</table>
<logic:present name="order" scope="request">
  <input name="horder" type="hidden" value="<bean:write name="order" />"> 
  </logic:present>
  <logic:notPresent name="order" scope="request">
  <input name="horder" type="hidden" value="a"> 
</logic:notPresent>
</html:form>
</center>

<script language="JavaScript">

//setTimeout('init()',50);
window.onload=init;
function init(){
  
  document.all.stuName.value=document.all.hstuName.value;
  document.all.studentNo.value=document.all.hstudentNo.value;  
    
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
  
  for(var i=0;i<document.all.s_classNo.length;i++){
     
      if(document.all.hclassNo.value==document.all.s_classNo.options[i].value)
          document.all.s_classNo.options[i].selected=true;
          
  }
}

function DoClear(){
  
   document.all.stuName.value="";
   
   document.all.studentNo.value="";
   
   document.all.gender[2].checked=true;
   document.all.majorin.options[0].selected=true;
   document.all.fromProvince.options[0].selected=true;
   document.all.s_classNo.options[0].selected=true;
   
   document.all.hstuName.value="";
   document.all.hstudentNo.value="";
   
   document.all.hmajorin.value="";
   document.all.hgender.value="";
   document.all.hfromProvince.value="";
   document.all.hclassNo.value="";
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
   
   document.all.doexl.value="";
   document.forms[0].elements["pager.offset"].value="0";   
   
   document.all.hstuName.value=document.all.stuName.value;
   document.all.hstudentNo.value=document.all.studentNo.value;
   
   for(var i=0;i<document.all.gender.length;i++){
       if(document.all.gender[i].checked)
            document.all.hgender.value=document.all.gender[i].value;
   
   }
   
   document.all.hmajorin.value=document.all.majorin.value;
   document.all.hfromProvince.value=document.all.fromProvince.value;
   document.all.hclassNo.value=document.all.s_classNo.value;
   
   document.stucheckininfoForm.action="gzcheckinmanageAction.do?method=classcheckinlist";
   document.stucheckininfoForm.submit();
   
}

function DoExport(){

   document.all.doexl.value="1";
   
   document.all.hstuName.value=document.all.stuName.value;
   document.all.hstudentNo.value=document.all.studentNo.value;
   
   for(var i=0;i<document.all.gender.length;i++){
       if(document.all.gender[i].checked)
            document.all.hgender.value=document.all.gender[i].value;
   
   }
   
   document.all.hmajorin.value=document.all.majorin.value;
   document.all.hfromProvince.value=document.all.fromProvince.value;
   document.all.hclassNo.value=document.all.s_classNo.value;
   
   document.stucheckininfoForm.action="gzcheckinmanageAction.do?method=classcheckinlist";
   document.stucheckininfoForm.submit();

}

function DoView(str){

   document.all.updateid.value=str;
   
   document.stucheckininfoForm.action="gzcheckinmanageAction.do?method=stuinfoview";
   document.stucheckininfoForm.submit();
}

function DoSort(col){
  document.all.doexl.value="";
  document.all.orderby.value=col;
  if(document.all.horder.value=='a')
      document.all.horder.value='d';
  else if(document.all.horder.value=='d')
      document.all.horder.value='a';
      
  document.stucheckininfoForm.action="gzcheckinmanageAction.do?method=classcheckinlist";
  document.stucheckininfoForm.submit();
}

</script>