<%@ page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<SCRIPT LANGUAGE=javascript src="treeRes/SelVal.js"></SCRIPT>

<gui:window title="�˵�Ȩ��" prototype="boWindow" color="100%">
	<html:form action="grantRoleMenu" styleId="blankForm">
		<input type="hidden" name="method" value="grantRoleMenus" />
		<input type="hidden" name="roleId" value="<c:out value="${roleId}"/>" />
		<input type="hidden" id="roleMenus" name="roleMenus" value="<c:out value="${roleMenus}"/>" />
		<input type="hidden" id="submitMenus" name="submitMenus" />

		<TABLE width="100%" height="305" border="0" cellspacing="0" cellpadding="0" align='center'>
			<TR>
				<TD width="32%">
					<B>�˵��б�</B>
				</TD>
				<TD width="10%">
					&nbsp;
				</TD>
				<TD width="27%">
					<B>��ѡ�˵�</B>
				</TD>
				<TD width="21%">
					&nbsp;
				</TD>
			</TR>

			<TR>
				<TD>
					<IFRAME name='DataFrame' src="menuSecurityManager.do?method=loadAllMenu4Grant" width="220" height="300" SCROLLING="auto"></IFRAME>
				</TD>
				<TD align=left>
					<INPUT onclick='AddContent_new(DataFrame.GetAllCheckData())' type=button value="��� >>" class="button">
					<BR>
					<BR>
					<BR>
					<INPUT onclick="delContent(this.form.oSel);" type=button value="<< ɾ��" class="button">
					<BR>
					<BR>
					<BR>
					<INPUT onclick="delAllContent(this.form.oSel);" type=button value="�� &nbsp; ��" class="button">
				</TD>
				<TD>
					<SELECT name='oSel' size=20 style="width:100%;" ondblclick="delContent(this);">
						<OPTION value='----=ȫ��ȡ��=----'>
							----=ȫ��ȡ��=----
						</OPTION>
					</SELECT>
				</TD>
				<TD>
				    &nbsp;
				</TD>
	<!-- 			<TD align=right>
					<INPUT onclick='moveUp(this.form.oSel)' type=button value="�� ����" class="button">
					<br>
					<br>
					<br>
					<INPUT onclick='moveDown(this.form.oSel)' type=button value="�� ����" class="button">
				</TD>-->
			</TR>
			<TR height=30>
				<TD colSpan=4 align=center valign=bottom>
					<INPUT onclick="mySubmit(this.form, this.form.oSel);" type=button value="ȷ ��" class="button">
					<INPUT onclick="winColse()" type=button value="ȡ ��" class="button">
				</TD>
			</TR>
		</TABLE>
	</html:form>

</gui:window>
<script type="text/javascript">
<!--
var m_sSelVal, m_sSelText;
var m_sCheckKey	= ',';	// checkdata �ָ���(����ֵ��)


function window.onload()
{

	var sInitCheckdata	= document.getElementById('roleMenus').value;


	// ���ٴζ�ȡ���ݿ�,�ж�sInitCheckdata�����ݵ���ȷ��

	if ((sInitCheckdata.length) >0 )
	{
		AddContent_new(sInitCheckdata) ;
	}

}

function AddContent_new(p_sCheckdata)
{
	m_sSelVal	= "" ;
	m_sSelText	= "" ;
	m_sCheckKey	= DataFrame.m_oConfig.sCheckKey ;

	var sSelKey	= "#$#$#$" ;	// ���ݷָ���(��ʾֵtext������ֵvalue)

	var sCheckdata	= p_sCheckdata ;
	

	if (0 == sCheckdata.length) return ;

	var aCheckdata	= sCheckdata.split(m_sCheckKey);
	var nALen		= aCheckdata.length ;
	var i ;
	var aSel ;
	var sVal, sText ;

	for(i=0; i<nALen; i++)
	{
		aSel	= aCheckdata[i].split(sSelKey);
		sVal	= aSel[1];
		sText	= aSel[0];

		m_sSelVal	+=	sSelKey + sVal ;
		m_sSelText	+=	sSelKey + sText ;		
	}

	m_sSelVal	= m_sSelVal.replace(sSelKey, '');
	m_sSelText	= m_sSelText.replace(sSelKey, '');

	var aSelVal		= m_sSelVal.split(sSelKey) ;
	var aSelText	= m_sSelText.split(sSelKey) ;
    
	AddContent(aSelVal, aSelText, document.blankForm.oSel) ;

}

function mySubmit(p_oForm, p_oSel)
{
	m_sSelVal	= '' ;
	with(p_oForm)
	{
		var i ;
		var sVal ;
	
		for(i=1; i< p_oSel.length; i++)
		{
			sVal		= p_oSel.options[i].value ;
			m_sSelVal	+= m_sCheckKey + sVal ;
		}
	}

	m_sSelVal	= m_sSelVal.replace(m_sCheckKey, '') ;

	blankForm.submitMenus.value = m_sSelVal;

	blankForm.submit();
}

function winColse()
{	
    location.href  = "menuSecurityManager.do?method=loadRole4GrantMenu";
}

// -->
</script>
