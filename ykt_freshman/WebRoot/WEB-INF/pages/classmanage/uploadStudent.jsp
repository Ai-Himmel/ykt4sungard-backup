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
	<html:form action="studentuploadAction.do?method=importDormitoryFile" enctype="multipart/form-data" onsubmit="javascript:return on_validate();">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium">�������ݵ���</font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="middle">
				&nbsp;
			</td>
		</tr>
			<tr>
				<td align="left" valign="middle">
		
					<span class="red1">����ѧԺ��Ҫ��������ע�⣺
					<br>��������ģ���е�¼ȡ֪ͨ��š��������롢��ϵ�绰�����֤�š���������Ϊ�ı��͡�
					<br>�������ڵĸ�ʽΪ��yyyymmdd������ʾ�������ա������磺19880728��ʾ1988��7��28�ա�
					<br>ת������:
					<br>(1)���衰���֤�š�ΪE��,�ڡ����֤�š��к����һ���հ��У�ΪF��.
					����F2��Ԫ�����빫ʽ��=TEXT(E2,"000000000000000")����
					��ʽ�н�E2��Ԫ���������ָ���ĸ�ʽ(15λ��0��)�滻�����س����󣬼��õ�����ȷ�����֤�š�
					<br>(2)���������߽���ʽ���Ƶ�������Ԫ���С�������ɺ󣬲���ֱ��ɾ��ԭ���֤�����ڵ�E�У�
					����F�����ݽ�����������ʾ����Ҫ�Ա����д�ӡ������
					�ɽ�E�����ػ�F������ѡ�������������ơ���ť�����һ����ѡ��ѡ����ճ�������
					<br>(3)�ӵ����ġ�ѡ����ճ�����Ի�����ѡ����ֵ�����ɣ�Ȼ��Ϳ��԰�ȫ��ɾ��ԭ���֤�����ڵ�E�������ˡ� 
					<br>ͬ���ڡ��������ڡ��к����һ���հ��У�����F2��Ԫ�����빫ʽ��=TEXT(E2,"yyyymmdd")��									
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
								<a href="./importstudentmodel.xls">��������ģ��<IMG src="./pages/style/default/images/xls.gif" border="0"></a>
							</td>
						</tr>
						<tr>
							<td height="20" align="left" valign="middle" class="medium" colspan="2">
								<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
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