<%@ page pageEncoding="UTF-8"%>

<%@ include file="/WEB-INF/pages/include/style.jsp"%>
<%@ include file="/WEB-INF/pages/tiles/include.jsp"%>
<script>
	function lookup(obj){
	
		var selectedValue = obj.catogary.value;
		
		obj.action="../ygstufeeinfoAction.do?method=dormfeenotpaylist";
		if (selectedValue=="benke") {
			obj.action="../stufeeinfoAction.do?method=dormfeenotpaylist";
		}
		else if (selectedValue=="gaozhi"){
		 obj.action="../gzstufeeinfoAction.do?method=dormfeenotpaylist";
		}
		obj.submit();
	}
</script>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" >
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">住宿费未缴纳名单一览</font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="middle">
					&nbsp;
				</td>
			</tr>
			<form action="" method="post">
			<tr>
				<td align="center" valign="top">
					
						<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
							
							<tbody>

								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">请选择未缴纳住宿费学生类别</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<select name="catogary">
											<option value="benke">本科生</option>
											<option value="gaozhi">高职生</option>
											<option value="yanjiusheng">研究生</option>
										</select>
									</td>
									
								</tr>
								
							</tbody>
						</table>
						<tr>
							<td height="40" align="right" valign="middle" class="tdborder02">
								
								<input type="button" class="button_nor" value="查看" onclick="lookup(this.form);">
									
								</input>
							</td>
						</tr>
					</form>
											
		</table>
	</body>
</center>


