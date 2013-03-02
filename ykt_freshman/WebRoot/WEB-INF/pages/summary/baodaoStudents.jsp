<%@ page pageEncoding="UTF-8"%>

<%@ include file="/WEB-INF/pages/include/style.jsp"%>
<%@ include file="/WEB-INF/pages/tiles/include.jsp"%>
<script>
	function lookup(obj){
	
		var selectedValue = obj.catogary.value;
		
		obj.action="../gzcheckinmanageAction.do?method=tongjilistview";
		if (selectedValue=="benke") {
		     var mvalue = obj.summaryMethod.value;
		     if (mvalue=="spec"){
		      obj.action="../checkinmanageAction.do?method=tongjilistmajor";
		     }
		     else if (mvalue=="nannv"){
		     obj.action="../checkinmanageAction.do?method=tongjilistallview";
		     }
		      else if (mvalue=="zhongwai"){
		     obj.action="../checkinmanageAction.do?method=tongjilistallviewabroad";
		     }
			
		}
		obj.submit();
	}
</script>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" >
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">报到统计一览</font></strong>
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
										<span class="medium">请选择学生类别</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<select name="catogary" onchange="javascript:if(this.value=='gaozhi'){this.form.summaryMethod.disabled=true;}else {this.form.summaryMethod.disabled=false;}">
											<option value="benke">本科生</option>
											<option value="gaozhi">高职生</option>
											
										</select>
									</td>
									
								</tr>
								<tr align="center" valign="middle">
									<td width="15%" align="left" valign="middle" class="tableHeader2">
										<span class="medium">统计方式</span>
									</td>
									<td width="35%" align="left" valign="middle" class="tableHeader3">
										<select name="summaryMethod">
											
											<option value="spec">按专业统计</option>
											<option value="nannv">按男女统计</option>
											<option value="zhongwai">按中外统计</option>
											
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


