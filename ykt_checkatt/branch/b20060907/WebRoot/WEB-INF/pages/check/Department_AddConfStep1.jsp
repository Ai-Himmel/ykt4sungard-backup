<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
<head>
<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
</head>

<body>
<div class="pageTitle"><c:out value="${dptName}" />�Ű�����</div>
<form name="clerkForm"  action="department.do?method=addConf" method="post" >
<jodd:form bean="request">
       <%@ include file="/pages/common/messages.jsp" %>
        <table class="border" width=100% cellSpacing=0 cellPadding=2 align="center">
           <tr>
                <td class="left" width="20%">�Űಿ��:</td>
                <td class="right" align="left">
                    <c:out value="${dptName}" />
                </td>
            </tr>
            <tr>
                <td class="left">�����ƶ�:</td>
                <td class="right">
                    <select name="new_clerkRule" onchange=" if(this.value!='') changed();">
					<option value="">
							��ѡ��
						</option>
					<c:forEach var="workConf" items="${workConfList}">
							<option value="<c:out value="${workConf.workconfid}"/>">
								<c:out value="${workConf.confname}" />
							</option>
						</c:forEach>
                    </select>
					<p>
					<c:out value="${workconfDetail}" />
					<input type="hidden" name="new_workconfDetail" value="<c:out value='${workconfDetail}' />"/>
					</p>
                </td>
            </tr>
            <tr>
                <td class="left">���ڹ���ʱ��:</td>
                <td class="right"> 
				<select name="new_cherkTimeRule" onchange=" if(this.value!='') changed();">
                        <option value="">
							��ѡ��
						</option>
				<c:forEach var="workTime" items="${workTimeConfList}">
							<option value="<c:out value="${workTime.worktimeconfid}"/>">
								<c:out value="${workTime.confname}" />
							</option>
						</c:forEach>
                </select>
				<p>
				<c:out value="${timeDetail}" />
				<input type="hidden" name="new_timeDetail" value="<c:out value='${timeDetail}' />"/>
				</p>
			    </td>
            </tr>
			<tr>
               <td class="left" width="20%">
			   ����ʱ��:
			   </td>
               <td class="right">
				<span class="medium">
				��ʼ����
				</span> &nbsp;
				<input class="input_box"  maxlength=20 name="new_startDate" readonly="true" >
				&nbsp;
				<img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="begin date" style="cursor:pointer">
				&nbsp;	
				��������
				&nbsp;
				<input name="new_endDate" class="input_box"  maxlength=20  readonly="true" >
				<img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="end date" style="cursor:pointer">
                &nbsp;&nbsp;&nbsp;
				<input type="checkbox" value="1" checked name="new_restinwkd">&nbsp;����,����Ϣ(����ʱѡ��)
				<script type="text/javascript">
					new calendar("new_startDate", "calBegin", "%Y-%m-%d");
					new calendar("new_endDate", "calEnd", "%Y-%m-%d");
				</script>
               </td>
            </tr>
			<tr>
                <td class="left" width="20%">����:</td>
                <td class="right">
                     <input type="radio" name="new_isSeat" value="1" checked />���� <input type="radio" name="new_isSeat" value="2" />������
                </td>
            </tr>
            <!-- <tr>
                <td class="left" width="20%">����:</td>
                <td class="right">
                    <IFRAME name='DataFrame' src="departmentManager.do?method=loadDepartmentTree" width="220" height="200" SCROLLING="auto"></IFRAME>
                    
                </td>
            </tr>-->
			<input type="hidden" name ="new_department" value="<c:out value='${new_department}'/>"/>
            <tr>
                <td colspan="2" class="bottom">
                    <input type="submit" class="submitButton" name="submitButton" value="ȷ��"  style="margin-right:60px" onclick="return onSubmit();"/>
					 <input type="button" class="submitButton" name="submitButton" value="�˳�"  style="margin-right:60px" onclick="window.location.href='department.do?method=goDeptConf';"/>
					<BUTTON onclick="history.back();">��һ��</BUTTON>
                   
                </td>
            </tr>
        </table>
		</jodd:form>
</form>

<div id="titleDiv" class="pageTitle">
<strong>
<font class="medium">
<c:out value="${dptName}" />�����Ű���Ϣ
</font>
</strong>
</div>

<div id="tableDiv" style="display:<c:out value='${display}'/>">
			<ec:table items="dptConfList" var="dptConf" rowsDisplayed="5" action="department.do?method=addConfStep1">
				<ec:exportXls fileName="deptConfList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column property="department.name" title="����" width="60" />
                    <ec:column property="startdate" title="��ʼʱ��" width="60" />
					<ec:column property="enddate" title="����ʱ��" width="60" />
					<ec:column property="workconf.confname" title="�����ƶ�" width="120" />
					<ec:column property="worktimeconf.confname" title="����ʱ��" width="120" />
					
				</ec:row>
			</ec:table>

		</div>
</body>
</html>
<script>
function onSubmit(){
   /* m_sCheckKey	= DataFrame.GetAllCheckData();
    if(m_sCheckKey==""){
       alert("��ѡ���ţ�");
       return false;
    }
    var sSelKey	= "#$#$#$" ;	// ���ݷָ���(��ʾֵtext������ֵvalue)
    
    var aCheckdata	= m_sCheckKey.split(sSelKey);
    sVal	= aCheckdata[1];
    sText	= aCheckdata[0];

    document.clerkForm.new_department.value = sVal;*/

    
	if(clerkForm.new_isSeat[0].checked)
	{
		if(clerkForm.new_cherkTimeRule.value==""||clerkForm.new_clerkRule.value=="")
		{
			alert('��ѡ�����ƶ��빤��ʱ��!');
		    return false;
		}
	}
    if(clerkForm.new_startDate.value==""||clerkForm.new_endDate.value=="")
	{
		alert('�뽫������д����!');
		return false;
	}
    if(clerkForm.new_startDate.value>clerkForm.new_endDate.value)
	{
		alert('��ʼ���ڲ��ܴ��ڽ�������!');
		return false;
	}
	/*if(clerkForm.new_startDate.value<'<c:out value="${recentDate}" />')
	{
        alert(clerkForm.new_startDate.value+'��'+'<c:out value="${recentDate}" />'+'֮���Ѿ������Ű���Ϣ,����������');
		return false;
	}*/

if(clerkForm.new_isSeat[0].checked&&clerkForm.new_cherkTimeRule.value!=""&&clerkForm.new_clerkRule.value!="")
	{
		 return true;
	}
   
    
}
function changed()
{
	clerkForm.submitButton.disabled="true";
	clerkForm.action='department.do?method=getConfDetail';
	clerkForm.submit();
}
</script>