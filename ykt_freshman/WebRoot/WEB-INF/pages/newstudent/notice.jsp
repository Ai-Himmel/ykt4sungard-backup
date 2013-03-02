<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<center>

	<html:form action="noticeAction.do?method=find">
		<html:errors />
		<br>
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">新生入学事项公告</font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
						<tbody>
							<tr align="center" valign=center>								
								<input name="notice.noticeNo" type="hidden" value="">								
								<td width=5% align="left" valign="middle" class="tableHeader2">
									公告标题
								</td>
								<td width=40% align="left" valign="middle" class="tableHeader3" colspan="3">
									<input name="notice.title" style="height:18px; width:400px; border:#000000 solid 1px; margin:0px; padding:0px; FONT-SIZE:12px" maxlength=50 value="">
								    &nbsp;&nbsp;<input name="notice.ifDeleted" type="radio" value="0" >公开&nbsp;<input name="notice.ifDeleted" type="radio" value="1" checked>登录可见&nbsp;<input name="notice.ifDeleted" type="radio" value="2">管理员可见
								</td>
							</tr>
							<tr align="center" valign=center>							
								<td colspan="4" align="left" valign="middle" class="tableHeader3">
									<html:textarea property="notice.body" style="width:1px;height:1px;" onfocus="editor.HtmlEdit.focus();"></html:textarea>
									<iframe ID="editor" src="editor.do" frameborder="0" scrolling=no width="100%" height="405"></iframe>
								</td>
							</tr>
						</tbody>
					</table>
				</td>
			</tr>
			<tr>
				<td height="40" align="right" valign="middle">
					<input name="Submit" type="button" class="button_nor" value="提交" onClick="DoCheck()">
					&nbsp;&nbsp;&nbsp;
                    <input name="cancel" type="submit" class="button_nor" value="取 消">
				</td>
			</tr>
		</table>

		<input type="hidden" name="notice.creatorId" value="<%=(String)session.getAttribute("personName")%>">
		<input type="hidden" name="notice.updatorId" value="<%=(String)session.getAttribute("personName")%>">
		<input type="hidden" name="notice.ifDeleted" value="0">

	</html:form>
</center>

<script language="JavaScript">

function DoCheck(){
 
  if(document.forms[0].elements["notice.title"].value==''){
      alert("请输入公告标题！");  
      document.forms[0].elements["notice.title"].focus();
      return; 
   }
  
  if (editor.EditMode.checked==true)
	  document.forms[0].elements["notice.body"].value=editor.HtmlEdit.document.body.innerText;
  else
	  document.forms[0].elements["notice.body"].value=editor.HtmlEdit.document.body.innerHTML;  
    
  //alert(document.forms[0].elements["notice.body"].value);
  document.noticeForm.action="noticeAction.do?method=add";
  document.noticeForm.submit();     
}

</script>
