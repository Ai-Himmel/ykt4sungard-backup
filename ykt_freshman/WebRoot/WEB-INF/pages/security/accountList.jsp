<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<bean:define id="title">
		<bean:message bundle="security" key="account.title" />
	</bean:define>

	<gui:window title="<%=title%>" prototype="boWindow" color="100%">
		<gui:tabbedPanel prototype="boTabbedPanel" followUp="usermanag.jsp" color="#f0f0f0" selectedTab="tab1" width="60">
			<bean:define id="tab1_title">
				<bean:message bundle="security" key="account.search" />
			</bean:define>
			<gui:tab prototype="boTab" name="tab1" title="<%=tab1_title%>" followUp="accountManager.do?method=searchAccount">

				<table class="win" CELLPADDING="2" CELLSPACING="0" width="100%">
					<html:form action="accountManager.do?method=searchAccount">
						<tr align="right">
							<td>
								
								<bean:message bundle="security" key="account.name" />
								<input type="text" name="para" value="">
								<bean:message bundle="security" key="person.name" />
								<input type="text" name="paraPersonName" value="">
								<html:submit styleClass="button">
									<bean:message key="button.search" />
								</html:submit>
							</td>
						</tr>
				</table>
				</html:form>
				<html:form action="accountManager.do">
					<input type="hidden" name="method" value="searchAccount">
					<input type="hidden" name="opType" value="add">
					<table class="sort-table" cellSpacing="1" cellPadding="1" width="100%" border="0">
						<thead>
							<tr>
								<td COLSPAN="7">
									<bean:message bundle="security" key="person.list" />
								</td>
							</tr>
						</thead>
						<logic:present name="accounts" scope="request">
							<thead>
								<tr>
									<td>
										<bean:message bundle="security" key="account.name" />
									</td>
									<td>
										<bean:message bundle="security" key="person.code" />
									</td>
									<td>
										<bean:message bundle="security" key="person.name" />
									</td>

									<td>
										<bean:message bundle="security" key="person.dept" />
									</td>

								</tr>
							</thead>

							<!--page offset start -->
							<%int itemNo = ((Integer) request.getAttribute("accountCount"))
					.intValue();%>
							<pg:pager url="./accountManager.do" items="<%=itemNo%>" index="center" maxPageItems="10" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
								<%-- keep track of preference --%>
								<pg:param name="para" />
								<pg:param name="paraPersonName" />
								<pg:param name="page" />
								<pg:param name="orderby" />
								<pg:param name="sort" />
								<pg:param name="method" />

								<%-- save pager offset during form changes --%>
								<input type="hidden" name="pager.offset" value="<%= offset %>">
								<logic:iterate name="accounts" id="account" indexId="i">
									<pg:item>
										<tr>
											<td>
												<input type="checkbox" name="id" value="<bean:write  name="account" property="id" />">
												<bean:write name="account" property="name" />
											</td>
											<td>
												<bean:write name="account" property="person.personCode" />
											</td>
											<td>
												<a href="accountManager.do?method=loadAccount4Edit&id=<bean:write  name="account" property="id" />&offset=<%= offset %>&opType=edit"> <bean:write name="account" property="person.personName" /> </a>
											</td>
											<td>
												<bean:write name="account" property="person.dept" />
											</td>
									</pg:item>
								</logic:iterate>
					</table>
					<jsp:include page="./page.jsp" flush="true" />
					</pg:pager>
					<!-- page offset end -->
					</logic:present>
					<br>
					<table cellSpacing="0" cellPadding="0" width="100%" border="0">
						<tr>
							<td COLSPAN="2" ALIGN="RIGHT">
								<html:submit styleClass="button" onclick="chgAction(document.all.method,'loadAccount4Add');chgAction(document.all.opType,'add');">
									<bean:message key="button.add" />
								</html:submit>
								<html:submit styleClass="button" onclick="chgAction(document.all.method,'loadAccount4Edit');chgAction(document.all.opType,'edit');bCancel=true;return validSelectedIdForEdit();">
									<bean:message key="button.edit" />
								</html:submit>
								<html:submit styleClass="button" onclick="chgAction(document.all.method,'removeAccount');chgAction(document.all.opType,'delete');bCancel=true;return validSelectedIdForDelete();">
									<bean:message key="button.delete" />
								</html:submit>
							</td>
						</tr>
					</table>

					<logic:notPresent name="accounts" scope="request">
						<tr>
							<td COLSPAN="3">
								<bean:message bundle="security" key="account.noRecord" />
							</td>
						</tr>
					</logic:notPresent>
				</html:form>

			</gui:tab>
		</gui:tabbedPanel>
	</gui:window>
</center>

<script language="JavaScript">

 function validSelectedIdForEdit(){
     var flag = 0;
     var count = 0;
     var a = document.all("id");
     if(a==null){
        alert("没有用户可以编辑");
        return false;
     }   
     if(a.length==null){
        if(!a.checked) {
          alert("请选择用户!");
          return false;
        }    
     }else {
        for  (var  i=0;  i<a.length;  i++){  
	         if(a[i].checked==true){
	            flag=flag+1;
	         }
        }  
	     if(flag==0){
	         alert("请选择用户!");
	         return false;
	     }    
	     if(flag>1){
	         alert("请选择一个用户!");
	         return false;
	     }
     
     }
     
     return true;
    
     
         
              
 }
 
  function validSelectedIdForDelete(){
  
   var msg = "确认删除用户?";
    ans = confirm(msg);
    if (ans) {
     var flag = 0;
     var a = document.all("id");
     if(a.length==null){
        if(!a.checked) {
          alert("请选择用户!");
          return false;
        }    
     }
     for  (var  i=0;  i<a.length;  i++){  
         if(a[i].checked==true){
            flag=flag+1;
         }
     }  
     if(flag==0){
         alert("请选择用户!");
         return false;
     }
     return true; 
    } else {
        return false;
    }
 }
 
 function chgAction(obj,str){
	obj.value=str;
 }

</script>
