<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
<html:form action="stuuploadAction.do?method=importExcel&importmode=add" enctype="multipart/form-data">
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
							    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a href="javascript:DoExportModel()">�������ݵ���ģ��<IMG src="./pages/style/default/images/xls.gif" border="0"></a>
					        </td>
						</tr>
						<tr align="center" valign="middle">
							<td colspan="2" height="32" align="center" valign="middle" bgcolor="#E7F1F5" >
							<input name="btnadd" type="button" class="button_nor" value="��������" onClick="DoCheck('add')">
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            <input name="btnupt" type="button" class="button_nor" value="���µ���" onClick="DoCheck('update')">
                            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            <input name="btndel" type="button" class="button_nor" value="ɾ������" onClick="DoCheck('delete')"> 
							</td>
						</tr>						
						<tr align="center" valign="middle">
						<td>&nbsp;</td>
						</tr>
						<tr align="center" valign="middle">
							<td colspan="2" height="32" align="left" valign="middle" >
							<font size="3" color="#990000">
							<b>����˵����</b>
							</font>
							<p>
							<font size="2.5" color="#990000">
							1. <b>Excel��Ԫ���ʽ��Ϊ�ı��͡�</b><br>
                            2. <b>�������룺</b><br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;����ǰ��������ѡ��Ҫ�����Excel�еĿ������Ա����Ŀ��ԣ�<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;����ʱ�������ݿ�ԭ�еĿ�����������������������<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;����Ѵ��ڴ˿��������������ܹ������ÿ��ԣ���������<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;����Ѵ��ڴ˿��������������ܱ����ÿ��ԣ���Ϊ�˿������Ӹÿ��ԡ�<br>
                            3. <b>���µ��룺</b><br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;����ʱ���������ݿ����п����Ļ�����Ϣ�Ϳɱ����Ŀ��ԣ�<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;������ǰѡ���˿��ԣ��Ὣ�ÿ���ԭ�п��Ա����ĵ�δ�����Ŀɱ�������ɾ��������Ϊ��ǰѡ��Ŀ��ԣ�<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;���ÿ����ѱ������򲻸����������Ϣ��<br> 
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;�����ݿ⻹û�иÿ�������������ݿ⣨��������൱���������룬����ǰ������ѡ���ԣ���<br>
                            4. <b>ɾ�����룺</b><br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;����ǰ��������ѡ��Ҫ�����Excel�еĿ������Ա����Ŀ��ԣ�<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;����ʱ����ɾ�����ݿ���ԭ�еĿ����������������ѱ������ҿ�������δ���Ŀ���������¼����<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;�������ݿ�������Excel�еĿ���������
							</font>
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

    if(str!='update'){
        if(document.all.testId.value==''){
        alert("����ѡ�񱾴�Ҫ����Ŀ������Ա����Ŀ������");
        return;
        } 
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
          if(str=='add'){
             if(confirm("�˲����������ݿ�ԭ�еĿ�����������������������ȷ��Ҫ���룿"))
                 document.feeuploadForm.action="stuuploadAction.do?method=importExcel&importmode=add";
             else
                 return;
          }
          else if(str=='update'){
              if(document.all.testId.value==''){
                  if(confirm("�˲������������ݿ����п����Ļ�����Ϣ��ȷ��Ҫ���룿"))
                      document.feeuploadForm.action="stuuploadAction.do?method=importExcel&importmode=update";
                  else
                      return;
              }
              else{
                  if(confirm("�˲������������ݿ����п����Ļ�����Ϣ����������ԭ�п��Ա����ĵ�δ�����Ŀ���ɾ��������Ϊ��ǰѡ��Ŀ��ԣ�ȷ��Ҫ���룿"))
                      document.feeuploadForm.action="stuuploadAction.do?method=importExcel&importmode=update";
                  else
                      return;
              
              }
          }
          else if(str=='delete'){
              if(confirm("�˲�����ɾ�����ݿ���ԭ�еĿ����������������ѱ������ҿ�������δ���Ŀ���������¼��������������������ȷ��Ҫ���룿"))
                  document.feeuploadForm.action="stuuploadAction.do?method=importExcel&importmode=delete";
              else
                  return;
          }
              
          document.feeuploadForm.submit();
        }
    
    }
    else{
        alert("��ѡ��Ҫ�����Excel�ļ���");
        return;    
    }
}

function DoExportModel(){
   
   document.feeuploadForm.action="stuuploadAction.do?method=getModel";
   document.feeuploadForm.submit();

}

</script>