<%@ page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://"
			+ request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<base href="<%=basePath%>">

		<title>学生基本信息查询列自定义</title>

		<meta http-equiv="pragma" content="no-cache">
		<meta http-equiv="cache-control" content="no-cache">
		<meta http-equiv="expires" content="0">
		<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
		<meta http-equiv="description" content="This is my page">
		<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	</head>

	<body>
		<br>
		<html:form action="studentAction.do?method=saveColumnSelect&getrole=1"
			onsubmit="javascript:return setValue();">

			<table width="450" border="0" cellspacing="0" cellpadding="0"
				align="center">
                <input name="page" type="hidden"
								value="<bean:write name="page" />">
				<tr align="center" valign="top">
					<td width="45%" align="center" bgcolor="#ECE6E6">
						<span class="medium">可选择列</span>
					</td>
					<td width="8%">

						&nbsp;
					</td>
					<td width="45%" align="center" bgcolor="#ECE6E6">
						<span class="medium">已选择列</span>
					</td>
				</tr>
				<tr align="center" valign="top">
					<td width="45%" align="center" bgcolor="#ECE6E6">
						<font color="#FF0000"> <html:select multiple="true"
								style="width:180" property="tableheadleft" size="15"
								ondblclick="transferOption(this.form.tableheadleft, this.form.tableheadright,false)">
								<html:options collection="ntableheadleftList"
									labelProperty="columnName" property="id.columnId" />
							</html:select> </font>
					</td>
					<td width="8%" valign="middle">

						<p>
							<button name="moveRight" id="moveRight" type="button"
								class="button_nor"
								onclick="transferOption(this.form.tableheadleft, this.form.tableheadright,false);">
								<bean:message bundle="classmanage" key="classBinding.right" />
							</button>
							<br />
							<br />
							<button name="moveLeft" id="moveLeft" type="button"
								class="button_nor"
								onclick="transferOption(this.form.tableheadright, this.form.tableheadleft,false);">
								<bean:message bundle="classmanage" key="classBinding.left" />
							</button>
							<br />
						</p>
					</td>
					<td width="45%" align="center" bgcolor="#ECE6E6">
						<font color="#FF0000"> <html:select multiple="true"
								style="width:180" property="tableheadright" size="15"
								ondblclick="transferOption(this.form.tableheadright, this.form.tableheadleft,false)">
								<html:options collection="ntableheadrightList"
									labelProperty="columnName" property="id.columnId" />
							</html:select> </font>
					</td>
				</tr>
				<tr>
					<td align="right" valign="middle" colspan="3">
						&nbsp;
					</td>
				</tr>
				<tr>
					<td align="right" valign="middle" colspan="3">
						<html:submit property="sure" styleClass="button_nor">
							<bean:message bundle="classmanage" key="studentsearch.sure" />
						</html:submit>
					</td>
				</tr>
			</table>


		</html:form>

		<script language="javascript">
function returnOption(e1,e2,all){
  	var src = e2.options;
  	var tgt = e1.options;
  	for (var i = src.length - 1; i >= 0; --i) {
    	if (all || src[i].selected) { 
			clone = uiCommon_cloneSelectOption(src[i]);
  			tgt.add(clone);
  			src[i] = null;
  		}
  	}	
}

function transferOption(e1,e2,all){
  	var src = e1.options;
  	var tgt = e2.options;
  	for (var i = src.length - 1; i >= 0; --i) {
    	if (all || src[i].selected) { 
			clone = uiCommon_cloneSelectOption(src[i]);
  			tgt.add(clone);
  			src[i] = null;
  		}
  	}
  	
}


function uiCommon_cloneSelectOption(opt) {
  return new Option(opt.text, opt.value,
                    opt.defaultSelected, opt.selected);
}


function setValue() {
	for (var i = 0; i <=document.forms[0].tableheadleft.options.length-1; ++i){
		document.forms[0].tableheadleft.options[i].selected = true;
	}
	for (var j = 0; j <=document.forms[0].tableheadright.options.length-1; ++j){
		document.forms[0].tableheadright.options[j].selected = true;
	}
	window.close();
	window.opener.document.all.search.click();
 	return true;
}


</script>
	</body>
</html>
