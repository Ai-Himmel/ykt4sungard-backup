<%@ include file = "../tiles/include.jsp"%>

<bean:define id="title">
<bean:message key="account.title"/>
</bean:define>
<center>
 <gui:window title = "<%=title%>" prototype = "boWindow" color = "100%">
  <gui:tabbedPanel prototype = "boTabbedPanel" followUp = "viewAccount.do?method=viewAccount" color = "#f0f0f0" selectedTab = "tab1"
      width = "70">
   <gui:tab prototype = "boTab" name = "tab1" title = "<%=title%>" followUp = "viewAccount.do?method=viewAccount">
	    <html:form action = "updateAccountAction?method=updateAccountInfo" focus = "account.name" onsubmit = "return validateRegisterForm(this);">
	<html:errors/>
     <br>

     <table class = "win" CELLPADDING = "0" CELLSPACING = "0" WIDTH = "100%">
      <tr>
       <td>
        <bean:message key = "register.loginName"/></td>

       <td>
        <html:text property = "account.name" size = "20" maxlength = "18" />

        <td>
      </tr>

      <tr>
       <td>
        <bean:message key = "register.name"/></td>

       <td>
        <html:text property = "account.person.name" size = "20" maxlength = "18" />

        <td>
      </tr>

      <tr>
       <td>
        <bean:message key = "register.password"/></td>

       <td>
        <html:password property = "account.password" size = "20" maxlength = "18" redisplay = "false"/></td>
      </tr>

      <tr>
       <td>
        <bean:message key = "register.confirm"/></td>

       <td>
        <html:password property = "repassword" size = "20" maxlength = "18" redisplay = "false"/></td>
      </tr>

      <tr>
       <td>
        <bean:message key = "register.sex"/></td>

       <td>
        <html:radio property = "account.person.sex" value="male"/><bean:message key = "register.male"/>
		<html:radio property = "account.person.sex" value="female"/><bean:message key = "register.female"/>

        <td>
      </tr>

      <tr>
       <td>
        <bean:message key = "register.email"/></td>

       <td>
        <html:text property = "account.person.email" size = "20" maxlength = "18" />

        <td>
      </tr>
      <tr>
       <td>
        <bean:message key = "register.qq"/></td>

       <td>
        <html:text property = "account.person.qq" size = "20" maxlength = "18" />

        <td>
      </tr>

      <tr>
       <td>
        <bean:message key = "register.phone"/></td>

       <td>
        <html:text property = "account.person.phone" size = "20" maxlength = "18" />

        <td>
      </tr>

      <tr>
       <td>
        <bean:message key = "register.question"/></td>

       <td>
        <html:text property = "account.person.question" size = "20" maxlength = "18" />

        <td>
      </tr>

      <tr>
       <td>
        <bean:message key = "register.answer"/></td>

       <td>
        <html:text property = "account.person.answer" size = "20" maxlength = "18" />

        <td>
      </tr>

      <tr>
       <td colspan = "2" align = "right">
        <html:submit styleClass="button">
         <bean:message key = "button.save"/></html:submit>

        <html:reset styleClass="button">
         <bean:message key = "button.reset"/></html:reset>
       </td>
      </tr>
	  <html:hidden property = "account.id" />
    </html:form>
	 </table>
   </gui:tab>

  </gui:tabbedPanel>
 </gui:window>
</center>
<html:javascript formName="registerForm"
        dynamicJavascript="true"
         staticJavascript="false"/>
         <script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>         