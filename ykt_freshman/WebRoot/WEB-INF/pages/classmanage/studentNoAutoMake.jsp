<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<script language="javascript">

function isInteger(val){
	for (i=0;i<val.length;i++){
		p = val.charAt(i);
		if (p<'0'||p>'9')
			return	false;
	}
	return	true;
}

function on_validate(){
	var valstuNoPrefix = document.all("stuNoPrefix").value;
	var valstartNo = document.all("startNo").value;
	
	if(valstuNoPrefix==""||isInteger(valstuNoPrefix)==false){
		alert("学号前缀请输入正整数");
		document.all("stuNoPrefix").value="";
		return false;
	}
	if(valstartNo==""||isInteger(valstartNo)==false){
		alert("起始号请输入正整数");
		document.all("startNo").value="";
		return false;
	}	
    var sumlength = valstuNoPrefix.length + valstartNo.length;
    if(sumlength>20){
  		alert("学号前缀,起始号总长度应小于20");  
 		document.all("stuNoPrefix").value="";
		document.all("startNo").value=""; 		 		
    	return false;
    }
}
</script>
<html:html>
<html:errors />
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
	<html:form action="studentAction.do?method=studentNoAutoMake"  onsubmit="javascript:return on_validate();">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium">学号自动生成</font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="middle">
				&nbsp;
			</td>
		</tr>
			<tr>
				<td align="left" valign="middle">
		
					<span class="red1">分班业务负责人请注意：学号前缀和起始号总长度不能超过20位。
					<br>例如：学号前缀为0512，起始号为0001总共8位，可生成学号9999个，05120001-05129999。
					<br>      学号前缀为0512，起始号为001总共7位，可生成学号999个，0512001-0512999。
				</td>
			</tr>
		<tr>
			<td align="center" valign="middle">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td>
				<INPUT type="hidden" name="export" value="">
			</td>
		</tr>							
		<tr>
			<td align="center" valign="top">
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tbody>
						<tr>
							<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								<span class="medium">学号前缀</span>
							</td>
							<td align="left" valign="middle" class="tableHeader3">
								<input name="stuNoPrefix" value="<c:out value="${stuNoPrefix}" />" class="input_box_stu">									
							</td>
							<td width="10%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
								<span class="medium">起始号</span>
							</td>
							<td align="left" valign="middle" class="tableHeader3">
								<input name="startNo" value="<c:out value="${startNo}" />" class="input_box_stu">
							</td>									
						</tr>
						<tr>
							<td colspan=4>
								<table width="100%" align="left">
									<tr align="left">
										<td width="100%" height="40" align="right" valign="middle" class="tdborder02" onclick="javascript:NotExport();">
											<html:submit property="search" value="自动生成" styleClass="button_nor"/>
										</td>
									</tr>
								</table>
							</td>
						</tr>						
						<tr>
							<td height="20" align="left" valign="middle" class="medium" colspan="2">
								<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
							</td>
						</tr>
						
					</tbody>
				</table>
			</td>
		</tr>
<input name="orderby" type="hidden" value="">
<logic:present name="order" scope="request">
  <input name="horder" type="hidden" value="<bean:write name="order" />"> 
  </logic:present>
  <logic:notPresent name="order" scope="request">
  <input name="horder" type="hidden" value="a"> 
</logic:notPresent>			
	</html:form>
	
			<tr>
				<td height="40" align="center" valign="top">
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=submenu1>
							<tbody>
          <logic:present name="checkinlist" scope="request">
					          <tr align="center" > 
					          <td align="center" valign="middle" class="tableHeader" >
					          <a style="font-size:14px;color: black" href="javascript:DoSort('studentNo')">
					          学号
					          </a>
					          </td>
					          <td align="center" height="24" valign="middle" class="tableHeader" >
					          <a style="font-size:14px;color: black" href="javascript:DoSort('enrollNo')">					          
					          录取通知书号
					          </a>					          
					          </td>
					          <td align="center" valign="middle" class="tableHeader" >
					          <a style="font-size:14px;color: black" href="javascript:DoSort('stuName')">					          					          
					          <bean:message bundle="checkinmanage" key="checkin.stuName"/>
					          </a>					          
					          </td>
					          <td align="center" valign="middle" class="tableHeader" >
					          <a style="font-size:14px;color: black" href="javascript:DoSort('gender')">					          					          					          
					          <bean:message bundle="checkinmanage" key="checkin.gender"/>
					          </a>					          
					          </td>
					          <td align="center" valign="middle" class="tableHeader" >
					          <a style="font-size:14px;color: black" href="javascript:DoSort('examType')">					          					          					          
					          高考科类
					          </a>					          
					          </td>
					          <td align="center" valign="middle" class="tableHeader" >
					          <a style="font-size:14px;color: black" href="javascript:DoSort('totalScore')">					          					          					          
					          高考总分
					          </a>					          
					          </td>
					          <td align="center" valign="middle" class="tableHeader" >
					          <a style="font-size:14px;color: black" href="javascript:DoSort('classNo')">					          					          					          
					          班级
					          </a>					          
					          </td>
					          </tr>

           <!--page offset start -->
           <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		  <pg:pager url="./studentAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="method" />
           <pg:param name="hstuName" />
           <pg:param name="henrollNo" />
           <pg:param name="hgender" />
           <pg:param name="hexamType" />
           <pg:param name="hclassId" />
		   <pg:param name="orderby" />
		   <pg:param name="sort" />										
		   <pg:param name="horder" />        
		   
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="<%= offset %>">  
			
            <logic:iterate name="checkinlist" id="cl" type="java.util.Map"  indexId="i">
            <pg:item>
            <c:choose><c:when test="${i%2 != 0}">
            <tr align="center" valign=middle>             
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="studentNo"/>&nbsp;</td>
              <td height="24" align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="enrollNo"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="stuName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              &nbsp;
              </td>              
              <td align="center" valign="middle" bgcolor="#FFFFFF" >
                  <c:choose><c:when test="${cl.examType == '1'}">
                    文史
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.examType == '2'}">
                    理工
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.examType == '3'}">
                    综合
                  </c:when></c:choose>
              &nbsp;</td>
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="totalScore"/>&nbsp;</td> 
              <td align="center" valign="middle" bgcolor="#FFFFFF" ><bean:write name="cl" property="classNo"/>&nbsp;</td>          
            </tr>
            </c:when></c:choose>
            <c:choose><c:when test="${i%2 == 0}">
            <tr align="center" valign=center>              
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="studentNo"/>&nbsp;</td>
              <td height="24" align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="enrollNo"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="stuName"/>&nbsp;</td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.gender == '1'}"><bean:message bundle="checkinmanage" key="checkin.male"/>
              </c:when></c:choose>
              <c:choose><c:when test="${cl.gender == '2'}"><bean:message bundle="checkinmanage" key="checkin.female"/>
              </c:when></c:choose>
              &nbsp;
              </td>              
              <td align="center" valign="middle" bgcolor="#F6F4F5" >
              <c:choose><c:when test="${cl.examType == '1'}">
                    文史
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.examType == '2'}">
                    理工
                  </c:when></c:choose>
                  <c:choose><c:when test="${cl.examType == '3'}">
                    综合
                  </c:when></c:choose>
              &nbsp;
              </td>
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="totalScore"/>&nbsp;</td>   
              <td align="center" valign="middle" bgcolor="#F6F4F5" ><bean:write name="cl" property="classNo"/>&nbsp;</td>           
            </tr>            
            </c:when></c:choose> 
             </pg:item>           
            </logic:iterate>
            <jsp:include page="./page.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
            </logic:present>
          
           <logic:notPresent name="checkinlist" scope="request">                  
           <!--page offset start -->
		  <pg:pager url="./stuinfolistpageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
           <pg:param name="hstuName" />
           <pg:param name="hstudentNo" />
           <pg:param name="hgender" />
           <pg:param name="hexamType" />
		   
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">  
			
			<jsp:include page="./pagenoexcel.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
            </logic:notPresent>
							</tbody>
						</table>
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
</html:html>
<script language="javascript">
	function DoExport(){
	 	document.all("export").value='export';
	 	document.forms[0].submit();
	 }
	 function NotExport(){
	 	document.all("export").value='';
	 }
	 
	function showError(){
		if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	}

	 window.onload=showError;	
	 
function DoSort(col){
	document.all("export").value='';
	document.all("stuNoPrefix").value = "";
	document.all("startNo").value = "";	
  document.all.orderby.value=col;  
  if(document.all.horder.value=='a')
      document.all.horder.value='d';
  else if(document.all.horder.value=='d')
      document.all.horder.value='a';
      
  document.forms[0].action="studentAction.do?method=studentNoAutoMake";
  document.forms[0].submit();
}	 	 
</script>