<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
<html:form action="stufeeAction.do?method=importExcelFile" enctype="multipart/form-data">
        <tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium">�����ɷ���Ϣ����</font></strong>
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
	                        <!-- <html:file property="theFile"/>  -->
	                        <input name="theFile" type="file" value="">
	                        <input name="filepath" type="hidden" value="">
	                        <input name="updatorId" type="hidden" value="<%=(String)session.getAttribute("userName")%>">
                            <input type="button" class="button_nor" value="�ύ" onClick="DoCheck()">
                                &nbsp;&nbsp;<font color="red">���Excel�ļ�����<b>�ܼ���</b>�����Ƚ��ܼ���<b>ɾ��</b>��Ȼ���ٵ��롣</font>
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a href="./feemodel.xls">�����ɷѵ���ģ��<IMG src="./pages/style/default/images/xls.gif" border="0"></a>
							</td>
						</tr>
				   </tbody>
				</table>
			</td>
		</tr>	
</table>
</html:form>
</html:html>

<script language="JavaScript">

function DoCheck(){
     //alert("ok");
    if(document.forms[0].elements["theFile"].value!=''){
        var fileext=document.forms[0].elements["theFile"].value.substring(document.forms[0].elements["theFile"].value.length-4,document.forms[0].elements["theFile"].value.length)
		fileext=fileext.toLowerCase()
		if (fileext!='.xls')
		{
			alert("�Բ��𣬲���ȷ���ļ�����,����Ϊ.xls ��");			
			return;
		}
        else{
          document.all.filepath.value=document.forms[0].elements["theFile"].value;
          document.feeuploadForm.action="stufeeAction.do?method=importExcelFile";
          document.feeuploadForm.submit();
        }
    
    }
    else{
        alert("��ѡ��Ҫ�����Excel�ļ���");
        return;
    
    }
       

}

</script>