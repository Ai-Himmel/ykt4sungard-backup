<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
<html:form action="stuuploadAction.do?method=importExcel&importmode=add" enctype="multipart/form-data">
        <tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium">考生数据导入</font></strong>
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
					            选择考试
					        </td>
					        <td align="left" valign="middle" class="tableHeader3" >
					            <select name="testId" class="select01">
									<option value="" >请选择</option>
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
					            导入文件
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
								<a href="javascript:DoExportModel()">考生数据导入模板<IMG src="./pages/style/default/images/xls.gif" border="0"></a>
					        </td>
						</tr>
						<tr align="center" valign="middle">
							<td colspan="2" height="32" align="center" valign="middle" bgcolor="#E7F1F5" >
							<input name="btnadd" type="button" class="button_nor" value="增量导入" onClick="DoCheck('add')">
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
							&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            <input name="btnupt" type="button" class="button_nor" value="更新导入" onClick="DoCheck('update')">
                            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            <input name="btndel" type="button" class="button_nor" value="删除导入" onClick="DoCheck('delete')"> 
							</td>
						</tr>						
						<tr align="center" valign="middle">
						<td>&nbsp;</td>
						</tr>
						<tr align="center" valign="middle">
							<td colspan="2" height="32" align="left" valign="middle" >
							<font size="3" color="#990000">
							<b>导入说明：</b>
							</font>
							<p>
							<font size="2.5" color="#990000">
							1. <b>Excel单元格格式须为文本型。</b><br>
                            2. <b>增量导入：</b><br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;导入前，必须先选择要导入的Excel中的考生可以报考的考试；<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;导入时，在数据库原有的考生名单基础上增加名单，<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果已存在此考生，而且他已能够报考该考试，则跳过；<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;如果已存在此考生，但他还不能报考该考试，则为此考生增加该考试。<br>
                            3. <b>更新导入：</b><br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;导入时，更新数据库已有考生的基本信息和可报考的考试；<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;若导入前选择了考试，会将该考生原有可以报名的但未报名的可报考考试删除，更新为当前选择的考试；<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;若该考生已报名，则不更新其基本信息；<br> 
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;若数据库还没有该考生，则加入数据库（这种情况相当于增量导入，导入前必须先选择考试）。<br>
                            4. <b>删除导入：</b><br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;导入前，必须先选择要导入的Excel中的考生可以报考的考试；<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;导入时，先删除数据库中原有的考生名单（仅保留已报名并且考试日期未到的考生报名记录）；<br>
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;再在数据库中增加Excel中的考生名单。
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
        alert("请先选择本次要导入的考生可以报名的考试类别！");
        return;
        } 
    }
    
    if(document.forms[0].elements["theFile"].value!=''){
        var fileext=document.forms[0].elements["theFile"].value.substring(document.forms[0].elements["theFile"].value.length-4,document.forms[0].elements["theFile"].value.length)
		fileext=fileext.toLowerCase()
		if (fileext!='.xls')
		{
			alert("对不起，不正确的文件类型,必须为.xls ！");			
			return;
		}
        else{
          document.all.filepath.value=document.forms[0].elements["theFile"].value;
          if(str=='add'){
             if(confirm("此操作将在数据库原有的考生名单基础上增加名单，确定要导入？"))
                 document.feeuploadForm.action="stuuploadAction.do?method=importExcel&importmode=add";
             else
                 return;
          }
          else if(str=='update'){
              if(document.all.testId.value==''){
                  if(confirm("此操作将更新数据库已有考生的基本信息，确定要导入？"))
                      document.feeuploadForm.action="stuuploadAction.do?method=importExcel&importmode=update";
                  else
                      return;
              }
              else{
                  if(confirm("此操作将更新数据库已有考生的基本信息，并将考生原有可以报名的但未报名的考试删除，更新为当前选择的考试，确定要导入？"))
                      document.feeuploadForm.action="stuuploadAction.do?method=importExcel&importmode=update";
                  else
                      return;
              
              }
          }
          else if(str=='delete'){
              if(confirm("此操作将删除数据库中原有的考生名单（仅保留已报名并且考试日期未到的考生报名记录），并重新增加名单，确定要导入？"))
                  document.feeuploadForm.action="stuuploadAction.do?method=importExcel&importmode=delete";
              else
                  return;
          }
              
          document.feeuploadForm.submit();
        }
    
    }
    else{
        alert("请选择要导入的Excel文件！");
        return;    
    }
}

function DoExportModel(){
   
   document.feeuploadForm.action="stuuploadAction.do?method=getModel";
   document.feeuploadForm.submit();

}

</script>