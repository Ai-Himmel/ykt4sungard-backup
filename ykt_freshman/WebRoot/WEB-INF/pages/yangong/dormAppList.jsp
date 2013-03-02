<%@page pageEncoding="UTF-8"%>
<%@ page import="org.king.classmanage.web.help.MajorinWithStuCount"%>
<%@ page import="java.util.List"%>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="org.king.classmanage.domain.Collegemodel" %>
<%@ include file="../tiles/include.jsp"%>
<script language="JavaScript">
function DoClear(){
	document.all("graduateNoSearch1").value="";
	document.all("graduateNoSearch2").value="";
	document.all("lengthofschoolSearch").value="";
	document.all("graduateTypeSearch").value="";
	document.all("graduateNoSearch").value="";
	document.all("graduateNameSearch").value="";
	document.all("studentTypeSearch").value="";
	document.all("matriculateTypeSearch").value="";
    document.all("curCollegeSearch").value="";
	document.all("sex").value="";
    document.all("distriction").value="";
	document.all("residentneed").value="";
	document.all("memo").value="";

}
</script>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message bundle="classmanage" key="dormDistribution.graduateAppDorm" /></font></strong>
				</td>
			</tr>
			
			<tr>
				<td align="left" valign="middle">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="right" valign="middle">
					
				</td>
			</tr>
			
			<tr>
				<td align="center" height="10">
					<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
				</td>
			</tr>
			<tr>
				<td height="40" align="left" valign="top" class="medium">

						<table width=100% border=1 align="left" cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=resetFrom>
							<tbody>
							
			<tr>
				<td align="center" valign="top">
					<html:form action="dormAppAction.do?method=loadGraduateList">
						<table width=100% border=1 align="left" cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=resetFrom>
							<INPUT type="hidden" name="export" value="">
							<tbody>

								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">学号</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<html:text styleClass="input_box" property="graduateNoSearch" maxlength="20"/>
									</td>
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">学号范围</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<html:text styleClass="input_box" property="graduateNoSearch1" maxlength="20"/>----
										<html:text styleClass="input_box" property="graduateNoSearch2" maxlength="20"/>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">姓名</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:text styleClass="input_box" property="graduateNameSearch" maxlength="20"/>
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">性别</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="sex">
											<html:option value="">-----------------------</html:option>
											<html:option value="1">男</html:option>
											<html:option value="2">女</html:option>
										</html:select>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">学生类别</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="studentTypeSearch">
											<html:option value="">-----------------------</html:option>
											<html:option value="D">博士生</html:option>
											<html:option value="M">硕士生</html:option>
										</html:select>
									</td>
									<td align="left" valign="middle" class="tableHeader2">
										培养方式
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="matriculateTypeSearch">
											<html:option value="">-----------------------</html:option>
											<html:options collection="matriculateTypeList" property="id.dictValue" labelProperty="dictCaption" />
										</html:select>
									</td>
								</tr>
								
								<tr align="center" valign="middle">
									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">录取院系</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="curCollegeSearch" onchange="javascript:setClass(this.value);">
											<html:option value="">-----------------------</html:option>
											<html:options collection="curCollegeList" property="deptCode" labelProperty="deptName" />
										</html:select>
									</td>
									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">住宿年限</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:text styleClass="input_box" property="lengthofschoolSearch"  maxlength="3"/>年

									</td>
								</tr>
								
								<tr align="center" valign="middle">
									<td align="left" valign="middle" class="tableHeader2">
										研究生住宿管理类别

									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="graduateTypeSearch">
											<html:option value="">-----------------------</html:option>
											<html:option value="NULL">[空]</html:option>
											<html:options collection="graduateTypeList" property="id" labelProperty="graduateType" />
										</html:select>
									</td>
									<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">住宿区域</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
											<html:select styleClass="select01" property="distriction">
												<html:option value="">-----------------------</html:option>
												<logic:present name="districtionList" scope="request">
													<html:options collection="districtionList" labelProperty="name"
														property="id" />
												</logic:present>
											</html:select>
									</td>
								</tr>
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">是否需要住宿</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01"
											property="residentneed">
											<html:option value="">-----------------------</html:option>
											<html:option value="1">是</html:option>
											<html:option value="2">否</html:option>																						
										</html:select>
									</td>
									<td align="left" valign="middle" class="tableHeader2">
										备注
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01" property="memo">
											<html:option value="">-----------------------</html:option>
											<html:option value="0">查找无备注记录</html:option>
											<html:option value="1">查找有备注记录</html:option>
										</html:select>
									</td>
								</tr>																
							</tbody>
						</table>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<html:button property="search" styleClass="button_nor" onclick="DoSearch()">
									<bean:message key="button.query" />
								</html:button>
								<html:button property="reset" styleClass="button_nor" onclick="DoClear()">
									<bean:message key="button.reset" />
								</html:button>
							</td>
						</tr>
					</html:form>
				</td>
			</tr>
			<tr>
			    <td>
			     <table width=100% border=1 align="left" cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=resetFrom>
			            <tr><td align="left">
			            <%if(((List)request.getAttribute("graduateList")).size()>0){ %>
			                  <font class="medium" color="red">只列出筛选出来住<%=request.getAttribute("show")%>的学生</font>
			           	<%} %>
			                </td>
			                <td align="right">
			                  <font class="medium" color="red"><bean:message bundle="classmanage" key="student.need" /></font>
			                </td>
			            </tr>
			     </table>
			    </td>
			</tr>
			<tr><td align="center" valign="top">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
								<html:form action="dormAppAction.do?method=updateGraduateInfo">
								<tr class="tableHeader">
									<td align="center" valign="middle" class="medium" width="8%">
										学号
									</td>
									<td align="center" valign="middle" class="medium" width="8%">
										姓名
									</td>
									<td align="center" valign="middle" class="medium" width="4%">
										性别
									</td>
									<td align="center" valign="middle" class="medium" width="10%">
										学生类别
									</td>
									<td align="center" valign="middle" class="medium" width="10%">
										录取院系
									</td>
									<td align="center" valign="middle" class="medium" width="8%">
										录取专业
									</td>
									<td align="center" valign="middle" class="medium" width="6%">
										住宿年限(年)
									</td>
									<td align="center" valign="middle" class="medium" width="7%">
										培养方式
									</td>
									<td align="center" valign="middle" class="medium" width="10%">
										住宿类别管理类型
									</td>
									<td align="center" valign="middle" class="medium" width="6%">
										住宿区域
									</td>
									<td align="center" valign="middle" class="medium" width="9%">
										是否需要住宿

									</td>
									<td align="center" valign="middle" class="medium" width="5%">
										备注
									</td>
									<td align="center" valign="middle" class="medium" width="9%">
										更新时间
									</td>									
								</tr>
								<logic:present name="graduateList" scope="request">
									<%int graduateCount = ((Integer) request.getAttribute("graduateCount")).intValue();%>
									<!--page offset start -->
									<pg:pager url="./dormAppAction.do" items="<%=graduateCount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
										<%-- keep track of preference --%>
										<pg:param name="method" />
										<pg:param name="graduateNoSearch1" />
										<pg:param name="graduateNoSearch2" />
										<pg:param name="lengthofschoolSearch" />
										<pg:param name="graduateTypeSearch" />
										<pg:param name="graduateNoSearch" />
										<pg:param name="graduateNameSearch" />
										<pg:param name="studentTypeSearch" />
										<pg:param name="matriculateTypeSearch" />
										<pg:param name="curCollegeSearch" />
										<pg:param name="sex" />
										<pg:param name="distriction" />
										<pg:param name="residentneed" />
										<pg:param name="memo" />
										<pg:param name="page" />
										<pg:param name="orderby" />
										<pg:param name="sort" /> 
										<%-- save pager offset during form changes --%>
										<input type="hidden" name="pager.offset" value="<%= offset %>">
									<logic:iterate name="graduateList" id="graduate" indexId="i">
									<pg:item>
										<tr align="center" valign="middle">
										<c:if test="${i%2 == 0}">
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="graduateNo" />">
												<bean:write name="graduate" property="graduateNo" />
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="graduateName" />">
												<bean:write name="graduate" property="graduateName" />
											</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="sex" />">
													<c:if test="${graduate.sex=='1'}">
													男




													</c:if>
													<c:if test="${graduate.sex=='2'}">
													女




													</c:if>
												</td>											
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="studentType" />">
													<bean:write name="graduate" property="studentType" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="curCollege" />">
													<bean:write name="graduate" property="curCollege" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="speciality" />">
													<bean:write name="graduate" property="speciality" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="lengthofschool" />">
													<bean:write name="graduate" property="lengthofschool" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="matriculateType" />">
													<bean:write name="graduate" property="matriculateType" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="graduateType" />">
													<bean:write name="graduate" property="graduateType" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
													<bean:write name="graduate" property="distriction" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF">
												    <input type="hidden" name="itemlist" value="<bean:write name="graduate" property="id" />"/>
													<c:if test="${graduate.residentNeed=='1'}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />" checked>
													</c:if>
													<c:if test="${graduate.residentNeed=='2'||graduate.residentNeed==null}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />">
													</c:if>
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="memo" />">
												<c:if test="${graduate.memo!=null&&graduate.memo!=''}">
												<a href="javascript:DoView('<bean:write name="graduate" property="id" />')">查看</a>
												</c:if>
												<c:if test="${graduate.memo==null||graduate.memo==''}">
												<a href="javascript:DoView('<bean:write name="graduate" property="id" />')">添加</a>
												</c:if>							
												</td>
											    <td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="graduateType" />">
													<bean:write name="graduate" property="registerTime" formatKey="dateTimeFormat" />
													<logic:empty name="graduate" property="registerTime">
														&nbsp;													
													</logic:empty>													
												</td>													

											</c:if>
											<c:if test="${i%2 != 0}">
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="graduateNo" />">
												<bean:write name="graduate" property="graduateNo" />
											</td>
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="graduateName" />">
												<bean:write name="graduate" property="graduateName" />
											</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="sex" />">
													<c:if test="${graduate.sex=='1'}">
													男




													</c:if>
													<c:if test="${graduate.sex=='2'}">
													女




													</c:if>
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="studentType" />">
													<bean:write name="graduate" property="studentType" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="curCollege" />">
													<bean:write name="graduate" property="curCollege" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="speciality" />">
													<bean:write name="graduate" property="speciality" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="lengthofschool" />">
													<bean:write name="graduate" property="lengthofschool" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="matriculateType" />">
													<bean:write name="graduate" property="matriculateType" />
													&nbsp;
												</td>
											    <td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="graduateType" />">
													<bean:write name="graduate" property="graduateType" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<bean:write name="graduate" property="distriction" />
													&nbsp;
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5">
													<input type="hidden" name="itemlist" value="<bean:write name="graduate" property="id" />"/>
													<c:if test="${graduate.residentNeed=='1'}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />" checked>
													</c:if>
													<c:if test="${graduate.residentNeed=='2'||graduate.residentNeed==null}">
													<INPUT type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />">
													</c:if>
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="memo" />">
												<c:if test="${graduate.memo!=null&&graduate.memo!=''}">
												<a href="javascript:DoView('<bean:write name="graduate" property="id" />')">查看</a>
												</c:if>
												<c:if test="${graduate.memo==null||graduate.memo==''}">
												<a href="javascript:DoView('<bean:write name="graduate" property="id" />')">添加</a>
												</c:if>									
												</td>
											    <td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="graduateType" />">
													<bean:write name="graduate" property="registerTime"  />
													<logic:empty name="graduate" property="registerTime">
														&nbsp;													
													</logic:empty>													
												</td>																									
											</c:if>										
										</tr>
										</pg:item>
									</logic:iterate>
										<jsp:include page="./page.jsp" flush="true" />




</table>

<table width="100%">	
  <tr> 
    <td height="24" align="left" valign="middle">
        <jsp:include page="./pagenoexcel.jsp" flush="true" />
    </td>
  </tr>	
</table>
</td></tr>
									</pg:pager>
								</logic:present>
  <tr> 
    <td height="40" align="left" valign="middle">
        <%
        int rowcount=0;
        if(request.getAttribute("graduateCount")!=null){
        	rowcount=((Integer)request.getAttribute("graduateCount")).intValue();
        %>       
        <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
        <%} %>
    </td>
  </tr>
							</tbody>
						</table>
 						
						<tr>
							<td height="30" align="right" valign="middle">
								<html:submit property="next" styleClass="button_nor">
									<bean:message bundle="classmanage" key="studentsearch.sure" />
								</html:submit>
							</td>
						</tr>
					</html:form>
		</table>
		
	</body>
</center>
<script language="JavaScript">
	 function DoExport(){
	 	document.all("export").value='export';
	 	document.forms[0].submit();
	 }
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
      
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//产生javascript二维数组，对应学院 专业
     <%
     }
   }
   %>
   datacount=<%=count%>;


</script>
<script language="JavaScript">
function DoSearch(){
document.all("export").value='';
if(document.forms[0].elements["lengthofschoolSearch"].value!=''){

    if(isNaN(document.forms[0].elements["lengthofschoolSearch"].value)){    
        alert("住宿年限 应为数字！");
        return false;
    }
    else if(parseInt(document.forms[0].elements["lengthofschoolSearch"].value,10)<0){
        alert("住宿年限 不能为负数!");
        return false;
    }else{
        document.forms[1].elements["pager.offset"].value="0";
        document.forms[0].action="dormAppAction.do?method=loadGraduateList";
        document.forms[0].submit();
	}
}
else{
    document.forms[1].elements["pager.offset"].value="0";
    document.forms[0].action="dormAppAction.do?method=loadGraduateList";
    document.forms[0].submit();
}
}
    function DoSure(){
    	
    }
	function setClass(college){

		document.all["specialitySearch"].length=0;
		var collegeId=college;
		var j; 
		document.all["specialitySearch"].options[document.all["specialitySearch"].length]= new Option("---------------------","");
			for (j=0;j < datacount; j++) 
			{ 
				if (dataset[j][2] == collegeId) 
				{ 
					document.all["specialitySearch"].options[document.all["specialitySearch"].length]= new Option(dataset[j][1],dataset[j][0]);
				} 
			} 
	}
	function DoSearch1(id){
		var gid = id;
		var glength = document.all["itemlist"].length;
		for(var j=0;j<glength;j++){
			if(document.forms[1].elements["itemList"][j].value==gid){
				document.forms[1].elements["itemList"][j].checked=true;
				break;			
			}
		}	
	}
	function DoSearch2(id){
		var gid = id;
		var glength = document.all["itemlist"].length;
		for(var j=0;j<glength;j++){
			if(document.forms[1].elements["itemList"][j].value==gid){
				document.forms[1].elements["itemList"][j].checked=false;
				break;			
			}
		}	
	}
function DoView(id){
 var url="dormAppBillAction.do?method=memoView&gid="+id;
 var windows="height=300,width=500,toolbar=no,menubar=no,scrollbars=yes,resizable=no,location=no,status=no";
 window.open(url,"",windows);
}
	
	 function my_onload(){	 	

	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		} 	
	 }
	 window.onload=my_onload;
</script>
