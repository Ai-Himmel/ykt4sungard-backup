<%@ include file = "../tiles/include.jsp"%>

<bean:define id="loginTitle">
<bean:message key="login.title"/>
</bean:define>
<bean:define id="registerTitle">
<bean:message key="register.title"/>
</bean:define>
<center>
 <gui:window title = "<%=registerTitle%>" prototype = "boWindow" color = "70%">
  <gui:tabbedPanel prototype = "boTabbedPanel" followUp = "login.do" color = "#f0f0f0" selectedTab = "tab2"
      width = "60">
   <gui:tab prototype = "boTab" name = "tab1" title = "<%=loginTitle%>" followUp="login.do">
    login!
   </gui:tab>
   <gui:tab prototype = "boTab" name = "tab2" title = "<%=registerTitle%>" followUp="register.do">
    <html:form action = "registerAction?method=register" focus = "account.name" onsubmit = "return validateRegisterForm(this);">
	<html:errors/>
     <br>

     <table class = "win" CELLPADDING = "0" CELLSPACING = "0" WIDTH = "100%">
      <tr>
       <td>
        <bean:message key = "register.loginName"/></td>

       <td>
        <html:text property = "account.name" size = "20" maxlength = "18"/>

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
        <bean:message key = "login.password"/></td>

       <td>
        <html:password property = "account.password" size = "20" maxlength = "18" redisplay = "false"/></td>
      </tr>

      <tr>
       <td>
        <bean:message key = "login.repassword"/></td>

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
        <html:text property = "account.person.answer" size = "20" maxlength = "18"/>

        <td>
      </tr>

      <tr>
       <td colspan = "2" align = "right">
        <html:submit styleClass="button">
         <bean:message key = "button.register"/></html:submit>

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
<html:javascript formName="registerForm"
        dynamicJavascript="true"
         staticJavascript="false"/>
         <script type="text/javascript" src="<html:rewrite forward='staticjavascript'/>"></script>         