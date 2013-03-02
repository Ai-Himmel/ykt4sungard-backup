<%@ include file = "../tiles/include.jsp"%>
<bean:define id="title">
<c:if test="${departmentForm.map.methodToCall=='add'}">
  <bean:message bundle="check" key="department.add" />
</c:if>
 <c:if test="${departmentForm.map.methodToCall=='edit'}">
   <bean:message bundle="check" key="department.edit" />
</c:if> 
&nbsp;
</bean:define>


 <gui:window title = "<%=title%>" prototype = "boWindow" color = "100%">
<div class="separator"></div>

<html:form action="addDepartment" styleId="departmentForm" onsubmit="return validateDepartmentForm(this);">

<input type="hidden" name="from" value="<c:out value="${param.from}"/>" />
<input type="hidden" name="method" />
<html:errors />
					<br>
<table class="detail">

<c:set var="pageButtons">
    <tr>
    	<td></td>
    	<td class="buttonBar">
    	 <c:if test="${departmentForm.map.methodToCall=='add'}">
            <html:submit styleClass="button" property="save"
                onclick="bCancel=false;document.forms[0].action.value='addDepartment';document.forms[0].method.value='create'">
            	<bean:message key="button.save"/>
            </html:submit>
          </c:if>
          
           <c:if test="${departmentForm.map.methodToCall=='edit'}">
            <html:submit styleClass="button" property="save"
                onclick="bCancel=false;document.forms[0].action.value='editDepartment';document.forms[0].method.value='update'">
            	<bean:message key="button.save"/>
            </html:submit>
          </c:if>
            
         <c:if test="${departmentForm.map.methodToCall=='edit'}">
<!--         <html:submit styleClass="button" property="delete"
            onclick="bCancel=false;document.forms[0].method.value='delete';return confirmDelete('Menu')" tabindex="14">
          <bean:message key="button.delete"/>  
        </html:submit>-->
        </c:if>
        
       <html:button styleClass="button" property="cancle" onclick="bCancel=true;cancel();">
                <bean:message key="button.cancel"/>
            </html:button>
        </td>
    </tr>
</c:set>
   <tr>
        <td>
        <c:choose>
            <c:when test="${departmentForm.map.methodToCall=='add'}">
            		<bean:message bundle="check" key="department.id"/> 
            </c:when>
            <c:otherwise>
                  
            </c:otherwise>
        </c:choose>
        </td>
        <td>
        <c:choose>
            <c:when test="${departmentForm.map.methodToCall=='add'}">
               <html:text property="department.id" styleId="department.id" size="30" maxlength = "10"/>
            </c:when>
            <c:otherwise>
                  <html:hidden property="department.id" styleId="department.id"/>
            </c:otherwise>
        </c:choose>
        </td>
    </tr>
    <tr>
        <td>
            <bean:message bundle="check" key="department.name"/>
        </td>
        <td>
            <html:text property="department.name" styleId="department.name" size="30" maxlength = "100"/>
        </td>
    </tr>
 
     <tr>
        <td>
            <bean:message bundle="check" key="department.pid"/>
        </td>
        <td>   
          <c:choose>
            <c:when test="${empty departmentForm.map.department.parent}">
                <html:text property="department.parent.id" styleId="department.parent.id" size="30" maxlength = "32"/>
            </c:when>
            <c:otherwise>
               <c:out value="${departmentForm.map.department.parent.name}"/>
                <html:hidden property="department.parent.id" styleId="department.parent.id"/>
            </c:otherwise>
        </c:choose>        
        
        </td>
    </tr>
 
 <%-- Print out buttons - defined at top of form --%>
<c:out value="${pageButtons}" escapeXml="false" />

</table>
</html:form>
 </gui:window>
<script type="text/javascript">
<!--

// This function is a workaround for the Validator not working 
// with LookupDispatchAction.
function cancel() {
    location.href = 'departmentManager.do?method=cancel';
}

function deleteDeparment() {
    location.href = 'removeMenu.do?method=deleteMenu&id=<c:out value="$deparment.id}"/>';
}
// -->
</script>
<html:javascript formName="departmentForm" cdata="false"
        dynamicJavascript="true"
         staticJavascript="false"/>
         <script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>         

