<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<center>
	<gui:window title="�޸�����" prototype="boWindow" color="100%">
		<gui:tabbedPanel prototype="boTabbedPanel" followUp="accountSecurityManager.do?method=load4changePWD" color="#f0f0f0" selectedTab="tab1" width="70">
			<gui:tab prototype="boTab" name="tab1" title="�޸�����" followUp="changePWDManager.do?method=changeAccountPWD">
				<html:form action="changePWDManager.do?method=changeAccountPWD" onsubmit="return submitChange()">
					<html:errors />
					<br>

					<table class="win" CELLPADDING="0" CELLSPACING="0" WIDTH="100%">
						<tr>
							<td>
								������ԭ����
							</td>

							<td>
								<input name="oldPWD" type="password" size="15" maxlength="15">
							<td>
						</tr>
						<tr>
							<td>
								������������
							</td>

							<td>
								<input name="newPWD" type="password" size="15" maxlength="15">
							<td>
						</tr>

						<tr>
							<td>
								���ٴ���������
							</td>

							<td>
								<input name="newPWD2" type="password" size="15" maxlength="15">
							<td>
						</tr>


						<tr>
							<td colspan="2" align="right">
								<html:submit styleClass="button">
									<bean:message key="button.submit" />
								</html:submit>

								<html:reset styleClass="button">
									<bean:message key="button.reset" />
								</html:reset>
							</td>
						</tr>
						</html:form>
					</table>
			</gui:tab>

		</gui:tabbedPanel>
	</gui:window>
</center>
<script type="text/javascript">
function submitChange(){
	if(document.all("oldPWD").value==""){
	    alert("������ԭʼ����");
	    return false;
	    }
	 else if(document.all("newPWD").value==""){
	    alert("������������");
	    return false;
	    }
	 else if(document.all("newPWD").value!=document.all("newPWD2").value){
	   alert("�������������벻ƥ��");  
	   return false;
	 }
       return true;
	 }
</script>
