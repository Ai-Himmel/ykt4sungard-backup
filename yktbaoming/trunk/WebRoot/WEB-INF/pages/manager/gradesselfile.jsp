<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
<html:form action="stuuploadAction.do?method=importGrades" enctype="multipart/form-data">
        <tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium">�����ɼ�����</font></strong>
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
					        <td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
					            ѡ����
					        </td>
					        <td align="left" valign="middle" class="tableHeader3" >
					            <select name="testId" class="select01">
									<option value="" >��ѡ��</option>
									<logic:present name="testlist" scope="request">
                                        <logic:iterate name="testlist" id="ml" type="java.util.Map">
                                        <option value="<bean:write name="ml" property="id"/>"><bean:write name="ml" property="testInfo"/></option>
                                        </logic:iterate>
                                    </logic:present>									
								</select>
					        </td>
					    </tr>
						<tr align="center" valign="middle">
						    <td width="15%" height="24" align="left" valign="middle" class="tableHeader2">
					            �����ļ�
					        </td>
							<td align="left" valign="middle" class="tableHeader3" >
	                        <!-- <html:file property="theFile"/>  -->
	                        <input name="theFile" type="file" value="">
	                        <input name="filepath" type="hidden" value="">
	                        <input name="updatorId" type="hidden" value="<%=(String)session.getAttribute("userName")%>">                                                       
							    <input name="btnupt" type="button" class="button_nor" value="�ɼ�����" onClick="DoCheck()">
							    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a href="javascript:DoExportModel()">�����ɼ�����ģ��<IMG src="./pages/style/default/images/xls.gif" border="0"></a>
					        </td>
						</tr>
						<tr align="left" valign="middle">
							<td colspan="2" height="32" align="left" valign="middle" bgcolor="#E7F1F5" >							
							<font size="2.5" color="red">ע��Excel�ĵ�ѧ����Ϊ�ı��͡�ѧ�ű��</font>
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

function DoCheck(str){  

    if(document.all.testId.value==''){
        alert("����ѡ�񱾴�Ҫ����ɼ��Ŀ��ԣ�");
        return;
    } 
    
    
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
          
          document.feeuploadForm.action="stuuploadAction.do?method=importGrades";
          document.feeuploadForm.submit();
        }
    
    }
    else{
        alert("��ѡ��Ҫ�����Excel�ļ���");
        return;    
    }
}

function DoExportModel(){
   
   document.feeuploadForm.action="stuuploadAction.do?method=getGradesModel";
   document.feeuploadForm.submit();

}

</script>