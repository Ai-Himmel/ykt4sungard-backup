<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<script language="javascript">

function on_validate(){
    if(document.all("theFile").value!=''){
        var fileext=document.forms[0].elements["theFile"].value.substring(document.forms[0].elements["theFile"].value.length-4,document.forms[0].elements["theFile"].value.length)
		fileext=fileext.toLowerCase()
		if (fileext!='.xls'){
			alert("�Բ��𣬲���ȷ���ļ�����,����Ϊ.xls ��");			
			return false;
		}
        return true;
    
    }
    else{
        alert("��ѡ��Ҫ�����Excel�ļ���");
        return false;
    
    }
       

}
</script>
<html:html>
<html:errors />
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
	<html:form action="DormitoryuploadAction.do?method=importDormitoryFile" enctype="multipart/form-data" onsubmit="javascript:return on_validate();">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium">������Դ����</font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="middle">
				&nbsp;
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
					<tbody>
						<tr align="center" valign="middle">
							<td width="25%" height="32" align="left" valign="middle" bgcolor="#ECE6E6">
								<html:file property="theFile" />
								<html:submit value="�ϴ��ļ�" />
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a href="./dormitorymodel.xls">������Դģ��<IMG src="./pages/style/default/images/xls.gif" border="0"></a>
							</td>
						</tr>
						<tr>
							<td height="20" align="left" valign="middle" class="medium" colspan="2">
								<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
							</td>
						</tr>
					</tbody>
				</table>
			</td>
		</tr>
	</html:form>
</table>
</html:html>
<script language="javascript">
	function showError(){
		if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	}

	 window.onload=showError;	
</script>