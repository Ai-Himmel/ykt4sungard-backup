<%@ page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"><bean:message
								bundle="yangongdormmanage" key="graduate.baseinfomantain" /> </font> </strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top" height="10"><INPUT type="hidden" name="myerror" value="<html:errors bundle="yangongdormmanage" />"></td>
			</tr>
			<html:form action="yxGraduateAction.do?method=load4List">
				<tr>
					<td align="center" valign="top">
						<table width="100%" border="1" align="center" cellpadding="1"
							cellspacing="0" bordercolor="#FFFFFF" id="submenu1">
							<tbody>
								<tr align="center" valign=center>
									<td width="15%" height="24" align="right" valign="middle"
										bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium"><bean:message
												bundle="yangongdormmanage" key="graduate.graduateno" /> </span>
									</td>
									<td width="32%" align="left" valign="middle"
										class="tableHeader3">
										<html:text property="YxGraduate.graduateNo"
											styleClass="input_box" maxlength="20" />
										&nbsp;&nbsp;
										<bean:message bundle="yangongdormmanage" key="graduate.from" />
										<html:text property="startfrom"
											style="height:16px;width:20px;border:#000000 solid 1px;margin:0px;padding:0px;FONT-SIZE: 12px;"
											maxlength="2" />
										<bean:message bundle="yangongdormmanage"
											key="graduate.positon" />
									</td>
									
									<td width="18%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">学号范围</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3" >
										<html:text styleClass="input_box" property="graduateNoSearch1" maxlength="20"/>--
										<html:text styleClass="input_box" property="graduateNoSearch2" maxlength="20"/>
									</td>									
									
								</tr>
								<tr align="center" valign=center>
									<td align="center" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader2">
										<bean:message bundle="yangongdormmanage" key="graduate.name" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader3">
										<html:text property="YxGraduate.graduateName"
											styleClass="input_box" maxlength="20" />
									</td>
																	
									<td align="center" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader2">
										性别
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader3">
										<html:select styleClass="select01"
											property="YxGraduate.sex">
											<html:option value="">-----------------------</html:option>
											<html:option value="1">男</html:option>
											<html:option value="2">女</html:option>
										</html:select>
									</td>

								</tr>
								<tr align="center" valign=center>
	<td align="center" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader2">
										<bean:message bundle="yangongdormmanage"
											key="graduate.studenttype" />
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader3">
										<html:select styleClass="select01"
											property="YxGraduate.studentType">
											<html:option value="">-----------------------</html:option>
											<logic:present name="studentTypeList" scope="request">
												<html:options collection="studentTypeList"
													labelProperty="dictCaption" property="id.dictValue" />
											</logic:present>
										</html:select>
									</td>
									<td height="24" align="right" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader2">
										<bean:message bundle="yangongdormmanage" key="graduate.style" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01"
											property="YxGraduate.matriculateType">
											<html:option value="">-----------------------</html:option>
											<logic:present name="styleList" scope="request">
												<html:options collection="styleList"
													labelProperty="dictCaption" property="id.dictValue" />
											</logic:present>
										</html:select>
									</td>
								</tr>
								<tr align="center" valign=center>
									<td height="24" align="right" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader2">
										<bean:message bundle="yangongdormmanage"
											key="graduate.college" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01"
											property="YxGraduate.curCollege">
											<html:option value="">-----------------------</html:option>
											<logic:present name="collegeList" scope="request">
												<html:options collection="collegeList"
													labelProperty="deptName" property="deptCode" />
											</logic:present>
										</html:select>
									</td>
									<td height="24" align="right" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader2">
										<bean:message bundle="yangongdormmanage"
											key="graduate.speciality" />
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:select styleClass="select01"
											property="YxGraduate.speciality">
											<html:option value="">-----------------------</html:option>
											<logic:present name="specialityList" scope="request">
												<html:options collection="specialityList"
													labelProperty="dictCaption" property="id.dictValue" />
											</logic:present>
										</html:select>
									</td>
								</tr>
								<tr align="center" valign=center>
									<td height="24" align="right" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader2">
										<span class="medium">住宿年限
										</span>
									</td>
									<td align="left" valign="middle" class="tableHeader3">
										<html:text property="lengthofschool"
											styleClass="input_box" maxlength="3" />
										<bean:message bundle="yangongdormmanage" key="graduate.year" />
									</td>								
									<td align="center" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader2">
										<span class="medium"><bean:message
												bundle="yangongdormmanage" key="graduate.type" /> </span>
									</td>
									<td align="left" valign="middle" bgcolor="#FFFFFF"
										class="tableHeader3">
										<html:select styleClass="select01"
											property="YxGraduate.graduateType">
											<html:option value="">-----------------------</html:option>
											<html:option value="NULL">[空]</html:option>
											<logic:present name="TypeList" scope="request">
												<html:options collection="TypeList"
													labelProperty="graduateType" property="id" />
											</logic:present>
										</html:select>
									</td>

								</tr>								
							</tbody>
						</table>
					</td>
				</tr>
				<tr>
					<td height="40" align="right" valign="middle" class="tdborder02">
						<html:button property="search" styleClass="button_nor"
							onclick="DoSearch()" >
							<bean:message key="button.query" />
						</html:button>
						<html:button property="clean" styleClass="button_nor" onclick="DoClear()">
							<bean:message key="button.reset" />
						</html:button>
					</td>
				</tr>
				<tr>
					<td height="10" align="center" valign="middle" class="medium"></td>
				</tr>
				<tr>
					<td height="40" align="center" valign="top">
						<table width=100% border=1 align=center cellpadding=1
							cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff
							id=submenu1>
							<tbody>
								<tr align="center" valign=center>
									<td width="30" valign="middle" class="tableHeader">
										<input type="checkbox" name="checkSwitch" value="checkbox" onclick="selectIns();">
									</td>
									<td height="24" valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="graduate.graduateno" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage" key="graduate.name1" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage" key="graduate.sex" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="graduate.studenttype" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage" key="graduate.style" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="graduate.college" />
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage"
											key="graduate.speciality" />
									</td>
									<td valign="middle" class="tableHeader">
										住宿年限(年)
									</td>
									<td valign="middle" class="tableHeader">
										<bean:message bundle="yangongdormmanage" key="graduate.type" />
									</td>
								</tr>
								<logic:present name="yxgraduates" scope="request">
									<%
										int itemNo = 0;
										if (request.getAttribute("graduateCount") != null) {
											itemNo = Integer.parseInt(request.getAttribute("graduateCount")
											.toString());
										}
									%>
									<pg:pager url="./yxGraduateAction.do" items="<%=itemNo%>"
										index="center" maxPageItems="100" maxIndexPages="10"
										isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber"
										scope="request">
										<%-- keep track of preference --%>
            <pg:param name="method" />
			<pg:param name="YxGraduate.graduateNo" />
			<pg:param name="startfrom" />
			<pg:param name="YxGraduate.graduateName" />
			<pg:param name="lengthofschool" />
			<pg:param name="YxGraduate.studentType" />
			<pg:param name="YxGraduate.matriculateType" />
			<pg:param name="YxGraduate.curCollege" />
			<pg:param name="YxGraduate.speciality" />
			<pg:param name="YxGraduate.sex" />
			<pg:param name="YxGraduate.graduateType" />
			<pg:param name="graduateNoSearch1" />
			<pg:param name="graduateNoSearch2" />
			<pg:param name="page" />
			<pg:param name="orderby" />
			<pg:param name="sort" />

										<%-- save pager offset during form changes --%>
										<input type="hidden" name="pager.offset" value="<%=offset%>">
										<logic:iterate name="yxgraduates" id="yxgraduate" indexId="i">
											<pg:item>
												<c:if test="${i%2 == 0}">
													<tr align="center" valign="middle">
												</c:if>
												<c:if test="${i%2 != 0}">
													<tr align="center" valign="middle" bgcolor="#F6F4F5">
												</c:if>

												<td height="24" align="center" valign="middle">
													<input type="checkbox" name="deleteX"
														value="<bean:write name="yxgraduate" property="id"/>">
												</td>
												<td align="center" valign="middle">
													<bean:write name="yxgraduate" property="graduateNo" />
												</td>
												<td align="center" valign="middle">
													<bean:write name="yxgraduate" property="graduateName" />
												</td>
												<td align="center" valign="middle">
													<bean:write name="yxgraduate" property="sex" />
													&nbsp;
												</td>
												<td align="center" valign="middle">
													<bean:write name="yxgraduate" property="studentType" />
													&nbsp;
												</td>
												<td align="center" valign="middle">
													<bean:write name="yxgraduate" property="matriculateType" />
													&nbsp;
												</td>
												<td align="center" valign="middle">
													<bean:write name="yxgraduate" property="curCollege" />
													&nbsp;
												</td>
												<td align="center" valign="middle">
													<bean:write name="yxgraduate" property="speciality" />
													&nbsp;
												</td>
												<td align="center" valign="middle">
													<bean:write name="yxgraduate" property="lengthofschool" />
													&nbsp;
												</td>
												<td align="center" valign="middle">
													<bean:write name="yxgraduate" property="graduateType" />
													&nbsp;
												</td>

											</pg:item>
										</logic:iterate>
										<jsp:include page="./pagenoexcel.jsp" flush="true" />

							</tbody>
						</table>
					</td>
				</tr>
				<tr><td height="40" align="left" valign="middle">
					<jsp:include page="./pagenoexcel.jsp" flush="true" />				
				</td></tr>
									</pg:pager>
								</logic:present>
		<logic:notPresent name="yxgraduates" scope="request">                  
           <!--page offset start -->
		  <pg:pager url="./yxGraduateAction.do" items="0" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
           <%-- keep track of preference --%>
            <pg:param name="method" />
			<pg:param name="YxGraduate.graduateNo" />
			<pg:param name="YxGraduate.graduateName" />
			<pg:param name="YxGraduate.studentType" />
			<pg:param name="YxGraduate.matriculateType" />
			<pg:param name="YxGraduate.curCollege" />
			<pg:param name="YxGraduate.speciality" />
			<pg:param name="YxGraduate.lengthofschool" />
			<pg:param name="YxGraduate.graduateType" />
			<pg:param name="page" />
		   
			<%-- save pager offset during form changes --%>
			<input type="hidden" name="pager.offset" value="0">  
			
			<jsp:include page="./pagenoexcel.jsp" flush="true" />
		  </pg:pager>
		  <!-- page offset end -->
        </logic:notPresent>
				<logic:present name="yxgraduates" scope="request">
				<tr> 
                  <td height="40" align="left" valign="middle">
                     <%int rowcount=((Integer)request.getAttribute("graduateCount")).intValue();%>        
                     <font color="#000000" size="2.5">共<%=rowcount%>条记录</font>
                  </td>
               </tr>               
				<tr>
					<td height="30" align="right" valign="middle" class="medium">
						住宿年限:
						<html:text property="newlengthofschool" styleClass="input_box"
							maxlength="3" />
						<bean:message bundle="yangongdormmanage" key="graduate.year" />
						&nbsp;&nbsp;&nbsp;&nbsp;
						<bean:message bundle="yangongdormmanage" key="graduate.type1" />
						<html:select styleClass="select01" property="newGraduateType">
							<html:option value="">-----------------------</html:option>
							<logic:present name="TypeList" scope="request">
								<html:options collection="TypeList" labelProperty="graduateType"
									property="id" />
							</logic:present>
						</html:select>						
					</td>
				</tr>
				<tr>
					<td height="30" align="right" valign="middle">
						<html:button property="add" styleClass="button_nor"
							onclick="DoSave()">
							<bean:message key="button.save" />
						</html:button>
					</td>
				</tr>
				</logic:present>
			</html:form>
		</table>
	</body>

</center>

<script language="JavaScript">

function DoSearch(){

if(document.YxGraduateForm.elements["startfrom"].value!=''||document.YxGraduateForm.elements["lengthofschool"].value!=''){
    
    if(isNaN(document.YxGraduateForm.elements["startfrom"].value)){
        alert("从第几位起查询 应为数字！");
        return false;
    }
    else if(parseInt(document.YxGraduateForm.elements["startfrom"].value,10)<0){
       alert("从第几位起查询 不能为负数!");
       return false;
    }
    else if(isNaN(document.YxGraduateForm.elements["lengthofschool"].value)){    
        alert("住宿年限 应为数字！");
        return false;
    }
    else if(parseInt(document.YxGraduateForm.elements["lengthofschool"].value,10)<0){
        alert("住宿年限 不能为负数!");
        return false;
    }else{
        document.forms[0].elements["pager.offset"].value="0";
        document.forms[0].action="yxGraduateAction.do?method=load4List";
        document.forms[0].submit();
	}
}else{
        document.forms[0].elements["pager.offset"].value="0";
    document.forms[0].action="yxGraduateAction.do?method=load4List";
    document.forms[0].submit();
}
}

function DoClear(){
document.YxGraduateForm.elements["YxGraduate.graduateNo"].value="";
document.YxGraduateForm.elements["startfrom"].value="";
document.YxGraduateForm.elements["YxGraduate.graduateName"].value="";
document.YxGraduateForm.elements["lengthofschool"].value="";
document.YxGraduateForm.elements["YxGraduate.studentType"].value="";
document.YxGraduateForm.elements["YxGraduate.matriculateType"].value="";
document.YxGraduateForm.elements["YxGraduate.curCollege"].value="";
document.YxGraduateForm.elements["YxGraduate.speciality"].value="";
document.YxGraduateForm.elements["YxGraduate.sex"].value="";
document.YxGraduateForm.elements["YxGraduate.graduateType"].value="";
document.YxGraduateForm.elements["graduateNoSearch1"].value="";
document.YxGraduateForm.elements["graduateNoSearch2"].value="";
}

function DoSave(){
var sflag = 0;
if(document.all.deleteX!=null){
	  if(document.all.deleteX.length>1){
	      for(var i=0;i<document.all.deleteX.length;i++){
              if(document.all.deleteX[i].checked){
                   sflag=sflag+1;                                                  
              }
          }
          if(sflag<1){
              alert("请选择研究生记录!");
              return;
          }
     }
     else{
         if(!document.all.deleteX.checked){
              alert("请选择研究生记录！");
              return;        
        }
     }
	    document.forms[0].action="yxGraduateAction.do?method=update";
		document.forms[0].submit();
		
	}else{
		alert("当前无记录！");
	}

}

	 function my_onload(){	 	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		} 	
	 }
	 window.onload=my_onload;
</script>
