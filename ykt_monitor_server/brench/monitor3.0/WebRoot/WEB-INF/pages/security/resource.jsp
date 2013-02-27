<%@ include file = "../tiles/include.jsp"%>
<bean:define id="title">
<bean:message bundle="security" key="security.title"/>
</bean:define>
<bean:define id="accountTitle">
<bean:message bundle="security" key="security.account"/>
</bean:define>
<bean:define id="roleTitle">
<bean:message bundle="security" key="security.role"/>
</bean:define>
<bean:define id="resourceTitle">
<bean:message bundle="security" key="security.resource"/>
</bean:define>
<center>
 <gui:window title = "<%=title%>" prototype = "boWindow" color = "100%">
  <gui:tabbedPanel prototype = "boTabbedPanel" followUp = "listAccount.do" color = "#f0f0f0" selectedTab = "tab3"
      width = "58">
   <gui:tab prototype = "boTab" name = "tab1" title = "<%=accountTitle%>" followUp = "accountSecurityManager.do?method=searchAccount">
	account
   </gui:tab>

   <gui:tab prototype = "boTab" name = "tab2" title = "<%=roleTitle%>" followUp="roleManager.do?method=loadRole">
    role
   </gui:tab>

   <gui:tab prototype = "boTab" name = "tab3" title = "<%=resourceTitle%>" followUp="resourceManager.do?method=loadResource">
	<html:form action = "addResource?method=addResource" onsubmit = "return validateResourceForm(this);">
	<html:errors/>
		<table WIDTH="100%" class="sort-table" cellSpacing="1" cellPadding="1" width="100%" border="0">
		<thead>
			<tr>
				<td colspan="2"><bean:message bundle="security" key="resource.add"/></td>
			</tr>
		</thead>
		<tr>
			<td><bean:message bundle="security" key="resource.code"/></td>
			<td><html:text property = "code" size = "20"/></td>
		</tr>
		<tr>
			<td><bean:message bundle="security" key="resource.name"/></td>
			<td><html:text property = "name" size = "20"/></td>
		</tr>
		<tr>
			<td><bean:message bundle="security" key="resource.url"/></td>
			<td><html:text property = "url" size = "20"/></td>
		</tr>
		<tr>
       <td colspan="2" align = "right">
        <html:submit styleClass="button">
         <bean:message key = "button.save"/></html:submit>

        <html:reset styleClass="button">
         <bean:message key = "button.reset"/></html:reset>
       </td>
		</tr>
	</html:form>
		</table>
	
	<html:form action = "removeResource.do?method=removeResource" onsubmit = "return validateListResourceForm(this);">
	<table class="sort-table" cellSpacing="1" cellPadding="1" width="100%" border="0">
	<thead>
        <tr>
			<td><bean:message bundle="security" key="resource.code"/></td>
			<td><bean:message bundle="security" key="resource.name"/></td>
			<td><bean:message bundle="security" key="resource.url"/></td>
        </tr>
	</thead>
	        <logic:iterate name="resources" id="resource" indexId="i">
        <tr>
			<td><input type="checkbox" name="index" value="<bean:write  name="i" />">
			   <input type="hidden" name="id" value="<bean:write  name="resource" property="id" />">
			 <input type="text" name="code" size="20"value="<bean:write  name="resource" property="code" />"></td>
			<td><input type="text" name="name" size="20" value="<bean:write  name="resource" property="name" />"></td>
			<td><input type="text" name="url" size="30" value="<bean:write  name="resource" property="url" />"></td>
        </tr>		
        </logic:iterate>
      <tr>
       <td colspan="3" align = "right">
	   <html:submit styleClass="button" onclick="document.forms[1].action='updateResource.do?method=updateResource'">
         <bean:message key = "button.update"/></html:submit>
        <html:submit styleClass="button" onclick="document.forms[1].action='removeResource.do?method=removeResource';return confirmDelete('');">
         <bean:message key = "button.delete"/></html:submit>
        <html:reset styleClass="button">
         <bean:message key = "button.reset"/></html:reset>
       </td>
      </tr>
    </html:form>
	</table>

   </gui:tab>

  </gui:tabbedPanel>
 </gui:window>
</center>
<html:javascript formName="listResourceForm"
        dynamicJavascript="true"
         staticJavascript="false"/>
<html:javascript formName="resourceForm"
        dynamicJavascript="true"
         staticJavascript="false"/>
<script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>                  
