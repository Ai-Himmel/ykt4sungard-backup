<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<script language="javascript">

function on_validate(){
    if(document.all("theFile").value!=''){
        var fileext=document.forms[0].elements["theFile"].value.substring(document.forms[0].elements["theFile"].value.length-4,document.forms[0].elements["theFile"].value.length)
		fileext=fileext.toLowerCase()
		if (fileext!='.xls'){
			alert("对不起，不正确的文件类型,必须为.xls ！");			
			return false;
		}
        return true;
    
    }
    else{
        alert("请选择要导入的Excel文件！");
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
				<strong><font class="medium">新生数据导入</font></strong>
			</td>
		</tr>
		<tr>
			<td align="center" valign="middle">
				&nbsp;
			</td>
		</tr>
			<tr>
				<td align="left" valign="middle">
		
					<span class="red1">护理学院主要负责人请注意：
					<br>新生数据模板中的录取通知书号、邮政编码、联系电话、身份证号、出生日期为文本型。
					<br>出生日期的格式为“yyyymmdd”，表示“年月日”。例如：19880728表示1988年7月28日。
					<br>转换方法:
					<br>(1)假设“身份证号”为E列,在“身份证号”列后插入一个空白列，为F列.
					单击F2单元格，输入公式“=TEXT(E2,"000000000000000")”，
					公式中将E2单元格的内容用指定的格式(15位“0”)替换，按回车键后，即得到了正确的身份证号。
					<br>(2)用填充柄工具将公式复制到其他单元格中。操作完成后，不能直接删除原身份证号所在的E列，
					否则F列数据将不能正常显示，若要对表格进行打印操作，
					可将E列隐藏或将F列数据选定，单击“复制”按钮，再右击鼠标选择“选择性粘贴”命令，
					<br>(3)从弹出的“选择性粘贴”对话框中选择“数值”即可，然后就可以安全地删除原身份证号所在的E列数据了。 
					<br>同理在“出生日期”列后插入一个空白列，单击F2单元格，输入公式“=TEXT(E2,"yyyymmdd")”									
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
								<html:submit value="上传文件" />
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a href="./importstudentmodel.xls">新生数据模板<IMG src="./pages/style/default/images/xls.gif" border="0"></a>
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