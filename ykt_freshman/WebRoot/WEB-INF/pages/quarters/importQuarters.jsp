<%@ page pageEncoding="UTF-8"%>
<%@ include file="/WEB-INF/pages/include/style.jsp"%>
<%@ include file="/WEB-INF/pages/tiles/include.jsp"%>
<script type="text/javascript" src="<c:url value='/pages/scripts/selectbox.js'/>" ></script>
<script type="text/javascript" src="<c:url value='/pages/scripts/global.js'/>" charset="gbk"></script>
<script language="javascript">

function on_validate(){
    if(document.all("excelFile").value!=''){
        var fileext=document.forms[0].elements["excelFile"].value.substring(document.forms[0].elements["excelFile"].value.length-4,document.forms[0].elements["excelFile"].value.length)
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

<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
	<s:form action="importQuarters!importFile" method="post" namespace="/quarters" enctype="multipart/form-data" onsubmit="javascript:return on_validate();">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium"><s:property value="dept.name"/>宿舍资源导入</font></strong>
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
								<s:file name="excelFile" />
								<html:submit value="上传文件" />
								&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
								<a href='<s:url value="/quartersTemplate.xls"/>'>宿舍资源模板<IMG src='<s:url value="/pages/style/default/images/xls.gif"/>' border="0"></a>
							</td>
						</tr>
						<tr>
							<td height="20" align="left" valign="middle" class="medium" colspan="2">
								<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
							</td>
						</tr>
						<tr>
							<td height="20" align="left" valign="middle" class="medium" colspan="2">
								说明:<br/>先下载模板,填写完数据后,上传.如果数据库中存在相同的房间则更新其他字段.相同校区,区域,楼号,层号,单元号和房间号的宿舍为相同房间.
								    <br/>1.单元号,电话可以为空.其他字段不能为空.
									<br/>2.校区为中文名称不是校区代码.例如邯郸校区
									<br/>3.区域为中文名称.是校区下面的区域.例如校区为邯郸校区,区域为本部
									<br/>4.楼号为中文名称.为校区,区域下的楼号.例如校区邯郸校区,区域为本部,楼号为2号楼
									<br/>5.层号为数字.例如1
									<br/>6.朝向为东南西北.例如南
									<br/>7.入住性别为男女.例如男
									<br/>具体例子可以看模板中的样本数据.
							</td>
						</tr>
					</tbody>
				</table>
			</td>
		</tr>
	</s:form>
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