<%@page pageEncoding="UTF-8"%>
<%@ page import="org.king.classmanage.web.help.MajorinWithStuCount"%>
<%@ page import="java.util.List"%>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="org.king.classmanage.domain.Collegemodel" %>
<%@ include file="../tiles/include.jsp"%>

<script language="JavaScript">
function clearAll(){

	document.all("graduateNoSearch").value="";
	document.all("graduateNameSearch").value="";
	
		document.all("studentTypeSearch").value="";
	document.all("matriculateTypeSearch").value="";
	
		document.all("curCollegeSearch").value="";
	document.all("specialitySearch").value="";

}

function selectIns_app() {

    if (document.all.itemList != null) {
        if (document.all.itemList.length == null) {
            if (document.all.checkSwitch.checked == true) {
                document.all.itemList.checked = true;
            } else {
                document.all.itemList.checked = false;
            }
        } else {
            for (var i = 0; i < document.all.itemList.length; i++) {
                if (document.all.checkSwitch.checked == true) {
                    document.all.itemList[i].checked = true;
                } else {
                    document.all.itemList[i].checked = false;
                }
            }
        }
    }
}
</script>
<SCRIPT language=javascript>

function tianjia(){
    dormAppSearchForm.action = "<c:url value="/dormAppBillAction.do"/>?method=addGzDormAppInfo";
	dormAppSearchForm.submit();
}
function doSearch(){
document.all("export").value='';
		if(document.forms[0].elements["pager.offset"]!=null){
			document.forms[0].elements["pager.offset"].value="0";
	 	}
    dormAppSearchForm.action = "<c:url value="/dormAppAction.do"/>?method=loadGzList";
	dormAppSearchForm.submit();
}
function doModify(){
	var sflag = 0;
	if(document.all.itemList.checked==true){
		dormAppSearchForm.action = "<c:url value="/dormAppBillAction.do"/>?method=loadGzDormAppInfo";
		dormAppSearchForm.submit();
	}else{
		  for(var i=0;i<document.all.itemList.length;i++){
              if(document.all.itemList[i].checked){
                   sflag=sflag+1;                                                  
              }
          }
          if(sflag>1){
              alert("只能选择一条做修改!");
              return;
          }else if(sflag<1){
          	  alert("请选择一条要修改记录！");
          }else{    
			  dormAppSearchForm.action = "<c:url value="/dormAppBillAction.do"/>?method=loadGzDormAppInfo";
			  dormAppSearchForm.submit();
          }
	}
}
function doDelete(){
	var sflag = 0;
	if(document.all.itemList.checked==true){
		if (confirm("您确定要删除该生的住宿登记信息吗？")==false){
	   		return;
	    }
	    dormAppSearchForm.action = "<c:url value="/dormAppAction.do"/>?method=deleteGzDormAppInfo&tag=0";
		dormAppSearchForm.submit();
	}else{
		  for(var i=0;i<document.all.itemList.length;i++){
              if(document.all.itemList[i].checked){
                   sflag=sflag+1;                                                  
              }
          }
          if(sflag>1){
          		if (confirm("您确定要删除选中的住宿登记信息吗？")==false){
			   		return;
			    }
			    dormAppSearchForm.action = "<c:url value="/dormAppAction.do"/>?method=deleteGzDormAppInfo&tag=0";
				dormAppSearchForm.submit();

          }else if(sflag<1){
              alert("请选择要删除的记录!");
              return;
          }else{    
          	  if (confirm("您确定要删除该生的住宿登记信息吗？")==false){
	   		      return;
	    	  }
		      dormAppSearchForm.action = "<c:url value="/dormAppAction.do"/>?method=deleteGzDormAppInfo&tag=0";
			  dormAppSearchForm.submit();
          }
	}

}
	 function DoExport(){
	 	document.all("export").value='export';
	 	document.forms[0].action = "<c:url value="/dormAppAction.do"/>?method=loadGzList";
	 	document.forms[0].submit();
	 }
function my_onload(){	 
	    var sh = '<%=request.getAttribute("show")%>';
	    var msg = '<%=request.getAttribute("msg")%>';
	    if(sh=='null'){
	    	if(msg!='null'){
				alert(msg);
			}
	    }else{
			alert(sh+"参与宿舍自动分配,故无法删除其登记信息"); 	
		}
	 }
	 window.onload=my_onload;
</SCRIPT>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="100%" border="0" align="left" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">新生住宿申请登记</font></strong>
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
					<html:form action="/dormAppAction" method="post">
					
						<table width=100% border=1 align="left" cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=resetFrom>
							<tbody>
							<INPUT type="hidden" name="export" value="">
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">学号</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">
										<html:text styleClass="input_box" property="graduateNoSearch" />
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">姓名</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">
										<html:text styleClass="input_box" property="graduateNameSearch" />
									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">性别</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">

												<html:select property="studentTypeSearch" styleClass="select01" style="width:120">
													<html:option value="">--------------------</html:option>
													<html:options collection="sexLi" property="id.dictValue" labelProperty="dictCaption" />
												</html:select>

									</td>
								</tr>
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">所在区县</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">

												<html:select property="matriculateTypeSearch" styleClass="select01" style="width:120">
													<html:option value="">--------------------</html:option>
													<html:options collection="qxLi" property="id.dictValue" labelProperty="dictCaption" />
												</html:select>

									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">班级</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">

												<html:select property="curCollegeSearch" styleClass="select01" style="width:120">
													<html:option value="">--------------------</html:option>
													<html:options collection="classLi" labelProperty="classNo" property="classId"  />
												</html:select>

									</td>
									<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
										<span class="medium">是否申请住宿</span>
									</td>
									<td width="18%" align="left" valign="middle" class="tableHeader3">

												<html:select property="specialitySearch" styleClass="select01" style="width:120">
													<html:option value="">--------------------</html:option>
													<html:option value="1">是</html:option>													
													<html:option value="0">否</html:option>
												</html:select>

									</td>
								</tr>
							</tbody>
						</table>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								<input name="Submit" type="button" class="button_nor" value="查询" onClick="javascript:doSearch();">
								<html:button property="reset" styleClass="button_nor" onclick="clearAll();">
									<bean:message key="button.reset" />
								</html:button>
							</td>
						</tr>

				</td>
			</tr>
			<tr><td align="center" valign="top">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>

								<tr class="tableHeader">
									<td align="center" valign="middle" class="medium" width="3%">
									<input type="checkbox" name="checkSwitch" onclick="selectIns_app();">
									</td>
									<td align="center" valign="middle" class="medium" width="10%">
										学号
									</td>
									<td align="center" valign="middle" class="medium" width="6%">
										姓名
									</td>
									<td align="center" valign="middle" class="medium" width="5%">
										性别
									</td>
									<td align="center" valign="middle" class="medium" width="12%">
										住址所在区县

									</td>
									<td align="center" valign="middle" class="medium" width="20%">
										详细住址
									</td>
									<td align="center" valign="middle" class="medium" width="9%">
										联系电话
									</td>
									<td align="center" valign="middle" class="medium" width="10%">
										是否申请住宿

									</td>
									<td align="center" valign="middle" class="medium" width="15%">
										备注
									</td>
									<td align="center" valign="middle" class="medium" width="10%">
										申请时间
									</td>									
								</tr>


								<logic:present name="graduateList" scope="request">
									<%int graduateCount = ((Integer) request.getAttribute("graduateCount")).intValue();%>
									<!--page offset start -->
									<pg:pager url="./dormAppAction.do" items="<%=graduateCount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
										<%-- keep track of preference --%>
										<pg:param name="method" />
										<pg:param name="graduateNoSearch" />
										<pg:param name="graduateNameSearch" />
										<pg:param name="page" />
										<pg:param name="orderby" />
										<pg:param name="sort" /> 

										<%-- save pager offset during form changes --%>
										<input type="hidden" name="pager.offset" value="<%= offset %>">
									<logic:iterate name="graduateList" id="graduate" indexId="i">
									<pg:item>
										<tr align="center" valign="middle">
										<c:if test="${i%2 == 0}">
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="id" />">
												<input type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />">
											
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="studentNo" />">
												<bean:write name="graduate" property="studentNo" />
													<logic:empty name="graduate" property="studentNo">
														&nbsp;													
													</logic:empty>												
											</td>
											<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="stuName" />">
												<bean:write name="graduate" property="stuName" />
													<logic:empty name="graduate" property="stuName">
														&nbsp;													
													</logic:empty>													
											</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="gender" />">
													<c:if test="${graduate.gender=='1'}">
													男

													</c:if>
													<c:if test="${graduate.gender=='2'}">
													女

													</c:if>
													<logic:empty name="graduate" property="gender">
														&nbsp;													
													</logic:empty>														
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="district" />">
													<bean:write name="graduate" property="district" />
													<logic:empty name="graduate" property="district">
														&nbsp;													
													</logic:empty>														
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="curAddress" />">
													<bean:write name="graduate" property="curAddress" />
													<logic:empty name="graduate" property="curAddress">
														&nbsp;													
													</logic:empty>													
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="curTelephone" />">
													<bean:write name="graduate" property="curTelephone" />
													<logic:empty name="graduate" property="curTelephone">
														&nbsp;													
													</logic:empty>													
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="ifNeedDorm" />">
												<c:if test="${graduate.ifNeedDorm=='0'}">
													否

												</c:if>
												<c:if test="${graduate.ifNeedDorm=='1'}">
													是

												</c:if>
													<logic:empty name="graduate" property="ifNeedDorm">
														&nbsp;													
													</logic:empty>													
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="memo" />">
													<bean:write name="graduate" property="memo" />
													<logic:empty name="graduate" property="memo">
														&nbsp;													
													</logic:empty>								
												</td>
												<td align="center" valign="middle" bgcolor="#FFFFFF" id="<bean:write name="graduate" property="updateTime" />">
													<bean:write name="graduate" property="updateTime" formatKey="dateTimeFormat" />
													<logic:empty name="graduate" property="updateTime">
														&nbsp;													
													</logic:empty>								
												</td>												
											</c:if>
											<c:if test="${i%2 != 0}">
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="id" />">
												<input type="checkbox" name="itemList" value="<bean:write name="graduate" property="id" />">
											</td>
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="studentNo" />">
												<bean:write name="graduate" property="studentNo" />
													<logic:empty name="graduate" property="studentNo">
														&nbsp;													
													</logic:empty>												
											</td>
											<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="stuName" />">
												<bean:write name="graduate" property="stuName" />
													<logic:empty name="graduate" property="stuName">
														&nbsp;													
													</logic:empty>												
											</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="gender" />">
													<c:if test="${graduate.gender=='1'}">
													男

													</c:if>
													<c:if test="${graduate.gender=='2'}">
													女

													</c:if>
													<logic:empty name="graduate" property="gender">
														&nbsp;													
													</logic:empty>														
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="district" />">
													<bean:write name="graduate" property="district" />
													<logic:empty name="graduate" property="district">
														&nbsp;													
													</logic:empty>														
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="curAddress" />">
													<bean:write name="graduate" property="curAddress" />
													<logic:empty name="graduate" property="curAddress">
														&nbsp;													
													</logic:empty>														
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="curTelephone" />">
													<bean:write name="graduate" property="curTelephone" />
													<logic:empty name="graduate" property="curTelephone">
														&nbsp;													
													</logic:empty>													
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="ifNeedDorm" />">
												<c:if test="${graduate.ifNeedDorm=='0'}">
													否

												</c:if>
												<c:if test="${graduate.ifNeedDorm=='1'}">
													是

												</c:if>
													<logic:empty name="graduate" property="ifNeedDorm">
														&nbsp;													
													</logic:empty>													
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="memo" />">
													<bean:write name="graduate" property="memo" />
													<logic:empty name="graduate" property="memo">
														&nbsp;													
													</logic:empty>														
												</td>
												<td align="center" valign="middle" bgcolor="#F6F4F5" id="<bean:write name="graduate" property="updateTime" />">
													<bean:write name="graduate" property="updateTime" formatKey="dateTimeFormat" />
													<logic:empty name="graduate" property="updateTime">
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
      <td height="30" align="right" valign="middle"> <input name="Submit2" type="button" class="button_nor" value="添加" onClick="javascript:tianjia();"> 
        &nbsp;&nbsp; <input name="Submit22" type="button" class="button_nor" value="修改"  onClick="javascript:doModify();">&nbsp;&nbsp; <input name="Submit22" type="button" class="button_nor" value="删除"  onClick="javascript:doDelete();"></td>
    </tr>
	</html:form>
		</table>
		
		
	</body>
</center>

