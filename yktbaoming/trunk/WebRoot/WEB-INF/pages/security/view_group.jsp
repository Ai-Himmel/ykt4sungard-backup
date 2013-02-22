<%@ include file = "../tiles/include.jsp"%>

<bean:define id="title">
<bean:message key="security.title"/>
</bean:define>
<bean:define id="accountTitle">
<bean:message key="security.account"/>
</bean:define>
<bean:define id="groupTitle">
<bean:message key="security.group"/>
</bean:define>
<bean:define id="rightTitle">
<bean:message key="security.right"/>
</bean:define>
<center>
 <gui:window title = "<%=title%>" prototype = "boWindow" color = "100%">
  <gui:tabbedPanel prototype = "boTabbedPanel" followUp = "listAccount.do" color = "#f0f0f0" selectedTab = "tab2"
      width = "52">
   <gui:tab prototype = "boTab" name = "tab1" title = "<%=accountTitle%>" followUp = "listAccount.do?method=listAccount">
	account manager
   </gui:tab>

   <gui:tab prototype = "boTab" name = "tab2" title = "<%=groupTitle%>" followUp="listGroup.do?method=listRole">
	<html:form action = "updateGroupAction?method=updateRole" onsubmit = "return validateGroupForm(this);">
	<html:errors/>
	<table class="sort-table" cellSpacing="1" cellPadding="1" width="100%" border="0">
	<thead>
        <tr>
			<td colspan="2"><bean:message key="group.create"/></td>
        </tr>
	</thead>
	<tr>
		<td><bean:message key="group.desc"/></td>
		<td><html:text property = "group.desc" size = "20" /></td>
	</tr>
	<tr>
		<td colspan="2"><bean:message key="right.title"/></td>
	</tr>
	        <logic:iterate name="removerights" id="right" indexId="i">
        <tr>
			<td><input type="checkbox" name="removeRight" value="<bean:write  name="right" property="id" />">
				<bean:write  name="right" property="box" /></td>
			<td><bean:write  name="right" property="desc" /></td>
        </tr>		
        </logic:iterate>
	<tr>
		<td colspan="2"><bean:message key="right.title"/></td>
	</tr>
	        <logic:iterate name="rights" id="right" indexId="j">
        <tr>
			<td><input type="checkbox" name="addRight" value="<bean:write  name="right" property="id" />">
				<bean:write  name="right" property="box" /></td>
			<td><bean:write  name="right" property="desc" /></td>
        </tr>		
        </logic:iterate>
      <tr>
       <td colspan="2" align = "right">
        <html:submit styleClass="button">
         <bean:message key = "button.save"/></html:submit>
        <html:reset styleClass="button">
         <bean:message key = "button.reset"/></html:reset>
       </td>
      </tr>
	  <html:hidden property = "group.id"/>
    </html:form>
	</table>
   </gui:tab>

   <gui:tab prototype = "boTab" name = "tab3" title = "<%=rightTitle%>" followUp="listRight.do?method=listRight">
    right
   </gui:tab>

  </gui:tabbedPanel>
 </gui:window>
</center>
<html:javascript formName="groupForm"
        dynamicJavascript="true"
         staticJavascript="false"/>
         <script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>         