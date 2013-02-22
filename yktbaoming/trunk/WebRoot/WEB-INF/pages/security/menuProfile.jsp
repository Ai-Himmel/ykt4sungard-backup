<%@ include file = "../tiles/include.jsp"%>
<bean:define id="title">
<bean:message bundle="security" key="menuProfile.title"/>
</bean:define>


 <gui:window title = "<%=title%>" prototype = "boWindow" color = "100%">
<div class="separator"></div>

<html:form action="addMenu" styleId="menuForm" onsubmit="return validateMenuForm(this);">

<input type="hidden" name="from" value="<c:out value="${param.from}"/>" />
<input type="hidden" name="method" />
<html:errors />
					<br>
<table class="detail">

<c:set var="pageButtons">
    <tr>
    	<td></td>
    	<td class="buttonBar">
    	 <c:if test="${menuForm.map.methodToCall=='add'}">
            <html:submit styleClass="button" property="save"
                onclick="bCancel=false;document.forms[0].action.value='addMenu';document.forms[0].method.value='addMenu'">
            	<bean:message key="button.save"/>
            </html:submit>
          </c:if>
          
           <c:if test="${menuForm.map.methodToCall=='edit'}">
            <html:submit styleClass="button" property="save"
                onclick="bCancel=false;document.forms[0].action.value='editMenu';document.forms[0].method.value='updateMenu'">
            	<bean:message key="button.save"/>
            </html:submit>
          </c:if>
            
         <c:if test="${menuForm.map.methodToCall=='edit'}">
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
            <bean:message bundle="security" key="menu.id"/>
        </td>
        <td>
        <c:choose>
            <c:when test="${menuForm.map.methodToCall=='add'}">
                <html:text property="menu.id" styleId="menu.id" size="50" maxlength = "32"/>
            </c:when>
            <c:otherwise>
                <c:out value="${menuForm.map.menu.id}"/>
                <html:hidden property="menu.id" styleId="menu.id"/>
            </c:otherwise>
        </c:choose>
        </td>
    </tr>
    <tr>
        <td>
            <bean:message bundle="security" key="menu.name"/>
        </td>
        <td>
            <html:text property="menu.name" styleId="menu.name" size="50" maxlength = "32"/>
        </td>
    </tr>
 
     <tr>
        <td>
            <bean:message bundle="security" key="menu.pid"/>
        </td>
        <td>   
               <c:choose>
            <c:when test="${empty menuForm.map.menu.pid}">
                <html:text property="menu.pid" styleId="menu.pid" size="50" maxlength = "32"/>
            </c:when>
            <c:otherwise>
            <c:out value="${menuForm.map.menu.pid}"/>
                <html:hidden property="menu.pid" styleId="menu.pid"/>
            </c:otherwise>
        </c:choose>        
        
        </td>
    </tr>
    <tr>
        <td>
            <bean:message bundle="security" key="menu.url"/>
        </td>
        <td>
            <html:text property="menu.url" styleId="menu.url" size="50" maxlength = "255"/>
        </td>
    </tr>
 
 <tr>
        <td>
            <bean:message bundle="security" key="menu.title"/>
        </td>
        <td>
            <html:text property="menu.title" styleId="menu.title" size="50" maxlength = "255"/>
        </td>
    </tr>
    <tr>
        <td>
            <bean:message bundle="security" key="menu.target"/>
        </td>
        <td>
            <html:text property="menu.target" styleId="menu.target" size="50" maxlength = "255"/>
        </td>
    </tr>
   
        <tr>
        <td>
            <bean:message bundle="security"  key="menu.sortFlag"/>
        </td>
        <td>
        <c:if test="${menuForm.map.methodToCall=='add'}">
            <html:text property="menu.sortFlag" styleId="menu.sortFlag" size="50" maxlength = "10" value="0"/>
        </c:if>
        <c:if test="${menuForm.map.methodToCall=='edit'}">
            <html:text property="menu.sortFlag" styleId="menu.sortFlag" size="50" maxlength = "10"/>
        </c:if>    
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
    location.href = 'menuManager.do?method=cancelMenu';
}

function deleteMenu() {
    location.href = 'removeMenu.do?method=deleteMenu&id=<c:out value="${menu.id}"/>';
}
// -->
</script>
<html:javascript formName="menuForm" cdata="false"
        dynamicJavascript="true"
         staticJavascript="false"/>
         <script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>         

