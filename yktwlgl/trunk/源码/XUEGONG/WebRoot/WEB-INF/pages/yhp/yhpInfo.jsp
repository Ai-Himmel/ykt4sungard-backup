<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
	<head>
		<title>上海复旦大学物料库存及仓储管理系统</title>

		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<script src="<c:url value="/pages/scripts/util.js"/>" type="text/javascript"></script>

		<script>

var idcount=0;
idset=new Array();

<%
   int idsCount=0;
   String[] idsSet=null;
   if(request.getAttribute("ids")!=null)
       idsSet=(String[])request.getAttribute("ids");//读取id号数组
   
   if(idsSet!=null){
     for(idsCount=0;idsCount<idsSet.length;idsCount++)
     {
     %>
      idset[<%=idsCount%>] = new Array("<%=idsSet[idsCount]%>");//产生javascript数组
     <%
     }
   }
   %>
   idcount=<%=idsCount%>;
</script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>

		<html:form action="/gyf/yhpAction.do?method=update" method="post">

			<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td align="left" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td height="25" align="left" valign="top">
									<table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">
												易耗品信息修改
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="20" align="left" valign="top" background="<c:url value="/pages/style/default/images/titlebg3.jpg"/>" class="mediumblack">
									<table height="26" border="0" cellpadding="0" cellspacing="0">
										<tr align="center" valign="middle">
											<td width="98" background="<c:url value="/pages/style/default/images/titlebg1.gif"/>" class="mediumblue">
												基本信息修改
											</td>
											<td width="98" background="<c:url value="/pages/style/default/images/titlebg2.gif"/>">
												<a href="javascript:DoViewArlInfo()" class="black_link3">到货信息</a>
											</td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="20" align="center" valign="top" bgcolor="#C3E0FC" class="tdborder04">
									<table width="98%" border="0" cellspacing="3" cellpadding="0">
										<tr>
											<td align="left" valign="top">
												<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
													<tbody>
														<input type="hidden" name="ifChanged" value="0">
														<logic:present name="yhplist" scope="request">
															<logic:iterate name="yhplist" id="el" type="java.util.Map" indexId="i">
																<tr align="center" valign="middle">
																	<td width="15%" height="26" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		易耗品批号
																	</td>
																	<td width="85%" align="left" valign="middle" class="tableHeader3" colspan="3">
																		<bean:write name="el" property="yhpKucunInfo.id" />
																		<input type="hidden" name="yhpKucunInfo.id" value="<bean:write name="el" property="yhpKucunInfo.id"/>" />
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		大类
																	</td>
																	<td width="35%" align="left" valign="middle" class="tableHeader3">
																		<select name="s_dlid" class="select01" onchange="changeXl(this)">
																			<logic:present name="dllist" scope="request">
																				<logic:iterate name="dllist" id="dl" type="java.util.Map">
																					<option value="<bean:write name="dl" property="id"/>">
																						<bean:write name="dl" property="dlmc" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="dlid" value="<bean:write name="el" property="dlid"/>">
																	</td>
																	<td width="15%" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		小类
																	</td>
																	<td width="35%" align="left" valign="middle" class="tableHeader3">
																		<select name="s_xlid" class="select01" onchange="changeWl(this)">
																			<logic:present name="xllist" scope="request">
																				<logic:iterate name="xllist" id="xl" type="java.util.Map">
																					<option value="<bean:write name="xl" property="id"/>">
																						<bean:write name="xl" property="xlmc" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="xlid" value="<bean:write name="el" property="xlid"/>">
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		<font color="red" style="font-weight:normal">*</font>&nbsp;品名
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<table border="0" cellspacing="0" cellpadding="0">
																			<tr align="center" valign="middle">
																				<td width="35">
																					<select name="s_wlid" class="select01" onchange="changeDW(this);changeWlid(this)" title="品名" isMust='1'>
																						<option value="" checked>
																							请选择
																						</option>
																						<logic:present name="wllist" scope="request">
																							<logic:iterate name="wllist" id="wl" type="java.util.Map">
																								<option value="<bean:write name="wl" property="id"/>">
																									<bean:write name="wl" property="wlmc" />
																								</option>
																							</logic:iterate>
																						</logic:present>
																					</select>
																					<input type="hidden" name="wlid" value="<bean:write name="el" property="wlid"/>">
																					<input type="hidden" name="old_wlid" value="<bean:write name="el" property="wlid"/>">
																					<input type="hidden" name="new_wlid" value="">
																				</td>
																				<td width="20">
																					&nbsp;
																				</td>
																				<td width="40" align="right">
																					<input name="tempwlmc" style="input_box" maxlength="50" value="<bean:write name="el" property="wlmc"/>" readonly="readonly" />
																				</td>
																				<td width="20">
																					&nbsp;
																				</td>
																				<td width="20" align="right">
																					<input name="addWlmc" type="button" value="查找" onclick="DoaddWlmc()">
																				</td>
																			</tr>
																		</table>
																	</td>
																	<td align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		单位
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<input name="wldw" style="input_box" maxlength="10" value="<bean:write name="el" property="wldw"/>" readonly="readonly" />
																	</td>
																</tr>
																<tr align="center" valign="middle">
																	<td align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		进货数量
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<input name="yhpNum" style="input_box" maxlength="50" value="<bean:write name="el" property="yhpNum"/>" readonly="readonly" />
																	</td>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		当前数量
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<input name="curNum" style="input_box" maxlength="50" value="<bean:write name="el" property="curNum"/>" readonly="readonly" />
																	</td>
																</tr>																	
																<tr align="center" valign="middle">
																	<td align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		起始编号
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<input name="yhpKucunInfo.beginNo" style="input_box" maxlength="50" value="<bean:write name="el" property="yhpKucunInfo.beginNo"/>" onchange="changeBeginNo(this)" />
																		<input type="hidden" name="old_beginNo" value="<bean:write name="el" property="yhpKucunInfo.beginNo"/>">
																		<input type="hidden" name="new_beginNo" value="">
																	</td>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		结束编号
																	</td>
																	<td align="left" valign="middle" class="tableHeader3">
																		<input name="yhpKucunInfo.endNo" style="input_box" maxlength="50" value="<bean:write name="el" property="yhpKucunInfo.endNo"/>" onchange="changeEndNo(this)" />
																		<input type="hidden" name="old_endNo" value="<bean:write name="el" property="yhpKucunInfo.endNo"/>">
																		<input type="hidden" name="new_endNo" value="">
																	</td>
																</tr>
																<tr align="center" valign="middle">
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		<font color="red" style="font-weight:normal">*</font>&nbsp;资产所属
																	</td>
																	<td align="left" valign="middle" class="tableHeader3" colspan="3">
																		<select name="s_deptid" class="select01" onchange="changeDeptid(this)" title="资产所属" isMust='1'>
																			<option value="" checked>
																				请选择
																			</option>
																			<logic:present name="deptlist" scope="request">
																				<logic:iterate name="deptlist" id="dl" type="org.king.business.domain.DeptInfo">
																					<option value="<bean:write name="dl" property="deptCode"/>">
																						<bean:write name="dl" property="deptName" />
																					</option>
																				</logic:iterate>
																			</logic:present>
																		</select>
																		<input type="hidden" name="deptid" value="<bean:write name="el" property="deptid"/>">
																		<input type="hidden" name="old_deptid" value="<bean:write name="el" property="deptid"/>">
																		<input type="hidden" name="new_deptid" value="">
																	</td>
																</tr>
																<tr align="center" valign="middle">
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		<font color="red" style="font-weight:normal">*</font>&nbsp;用途大类
																	</td>
																	<td align="left" valign="middle" class="tableHeader3" colspan="3">
																		<table border="0" cellspacing="0" cellpadding="0">
																			<tr align="center" valign="middle">
																				<td width="35">
																					<select name="s_usageCategory" class="select01" onchange="changeUsageCategory(this)" title="用途大类" isMust='1'>
																						<option value="" checked>
																							请选择
																						</option>
																						<logic:present name="uclist" scope="request">
																							<logic:iterate name="uclist" id="uc" type="java.util.Map">
																								<option value="<bean:write name="uc" property="id"/>">
																									<bean:write name="uc" property="usageCategoryName" />
																								</option>
																							</logic:iterate>
																						</logic:present>
																					</select>
																					<input type="hidden" name="usageCategory" value="<bean:write name="el" property="usageCategory"/>">
																					<input type="hidden" name="old_usageCategory" value="<bean:write name="el" property="usageCategory"/>">
																					<input type="hidden" name="new_usageCategory" value="">
																				</td>
																				<td width="20">
																					&nbsp;
																				</td>
																				<td width="40" align="right">
																					<input name="tempUsageCategory" style="input_box" maxlength="50" value="<bean:write name="el" property="usageCategoryName"/>" readonly="readonly" />
																				</td>
																				<td width="20">
																					&nbsp;
																				</td>
																				<td width="20" align="right">
																					<input name="addUsageCategory" type="button" value="查找"
																						onclick="javascript:window.open('deptUsageCategoryAction.do?method=search4List&formName=yhpsearchForm&addNum='+idcount,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
																				</td>
																			</tr>
																		</table>
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		用途说明
																	</td>
																	<td colspan="3" align="left" valign="middle" class="tableHeader3">
																		<textarea name="yhpKucunInfo.yhpUsage" cols=70 rows=2 maxLength="100" onchange="changeYhpUsage(this)"><bean:write name="el" property="yhpKucunInfo.yhpUsage" /></textarea>
																		<input type="hidden" name="old_yhpUsage" value="<bean:write name="el" property="yhpKucunInfo.yhpUsage"/>">
																		<input type="hidden" name="new_yhpUsage" value="">
																	</td>
																</tr>
																<tr align="center" valign=center>
																	<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																		备注
																	</td>
																	<td colspan="3" align="left" valign="middle" class="tableHeader3">
																		<textarea name="yhpKucunInfo.memo" cols=70 rows=2 maxLength="300" onchange="changeMemo(this)"><bean:write name="el" property="yhpKucunInfo.memo" /></textarea>
																		<input type="hidden" name="old_memo" value="<bean:write name="el" property="yhpKucunInfo.memo"/>">
																		<input type="hidden" name="new_memo" value="">
																	</td>
																</tr>
															</logic:iterate>
														</logic:present>
														<logic:present name="yhpbatchlist" scope="request">

															<tr align="center" valign="middle">
																<td width="15%" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	易耗品批号
																</td>
																<td align="left" valign="middle" class="tableHeader3" colspan="3">
																	---
																</td>
															</tr>
															<tr align="center" valign=center>
																<td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	大类
																</td>
																<td width="35%" align="left" valign="middle" class="tableHeader3">
																	<select name="bs_dlid" class="select01" onchange="BchangeXl(this)">
																		<logic:present name="dllist" scope="request">
																			<logic:iterate name="dllist" id="dl" type="java.util.Map">
																				<option value="<bean:write name="dl" property="id"/>">
																					<bean:write name="dl" property="dlmc" />
																				</option>
																			</logic:iterate>
																		</logic:present>
																	</select>
																</td>
																<td width="15%" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	小类
																</td>
																<td width="35%" align="left" valign="middle" class="tableHeader3">
																	<select name="bs_xlid" class="select01" onchange="BchangeWl(this)">
																		<logic:present name="xllist" scope="request">
																			<logic:iterate name="xllist" id="xl" type="java.util.Map">
																				<option value="<bean:write name="xl" property="id"/>">
																					<bean:write name="xl" property="xlmc" />
																				</option>
																			</logic:iterate>
																		</logic:present>
																	</select>
																</td>
															</tr>
															<tr align="center" valign=center>
																<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	品名
																</td>
																<td align="left" valign="middle" class="tableHeader3">
																	<table border="0" cellspacing="0" cellpadding="0">
																		<tr align="center" valign="middle">
																			<td width="35">
																				<select name="bs_wlid" class="select01" onchange="BchangeDW(this);BchangeWlid(this)"">
																					<option value="" checked>
																						请选择
																					</option>
																					<logic:present name="wllist" scope="request">
																						<logic:iterate name="wllist" id="wl" type="java.util.Map">
																							<option value="<bean:write name="wl" property="id"/>">
																								<bean:write name="wl" property="wlmc" />
																							</option>
																						</logic:iterate>
																					</logic:present>
																				</select>
																				<input type="hidden" name="bwlid" value="<%=request.getParameter("bwlid")==null||request.getParameter("bwlid").equals("null")?"":request.getParameter("bwlid")%>">
																			</td>
																			<td width="20">
																				&nbsp;
																			</td>
																			<td width="40" align="right">
																				<input name="btempwlmc" style="input_box" maxlength="50" value="<%=request.getParameter("btempwlmc")==null||request.getParameter("btempwlmc").equals("null")?"":request.getParameter("btempwlmc")%>" readonly="readonly" />
																			</td>
																			<td width="20">
																				&nbsp;
																			</td>
																			<td width="20" align="right">
																				<input name="addWlmc" type="button" value="查找" onclick="BDoaddWlmc()">
																			</td>
																		</tr>
																	</table>
																</td>
																<td align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	单位
																</td>
																<td align="left" valign="middle" class="tableHeader3">
																	<input name="bwldw" style="input_box" maxlength="10" value="<%=request.getParameter("bwldw")==null||request.getParameter("bwldw").equals("null")?"":request.getParameter("bwldw")%>" readonly="readonly" />
																</td>
															</tr>
															<tr align="center" valign="middle">
																<td align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	进货数量
																</td>
																<td align="left" valign="middle" class="tableHeader3">
																	---
																</td>
																<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	当前数量
																</td>
																<td align="left" valign="middle" class="tableHeader3">
																	---
																</td>
															</tr>															
															<tr align="center" valign="middle">
																<td align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	起始编号
																</td>
																<td align="left" valign="middle" class="tableHeader3">
																	<input name="beginNo" style="input_box" maxlength="50" value="<%=request.getParameter("beginNo")==null||request.getParameter("beginNo").equals("null")?"":request.getParameter("beginNo")%>" onchange="BchangeBeginNo(this)" />
																</td>
																<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	结束编号
																</td>
																<td align="left" valign="middle" class="tableHeader3">
																	<input name="endNo" style="input_box" maxlength="50" value="<%=request.getParameter("endNo")==null||request.getParameter("endNo").equals("null")?"":request.getParameter("endNo")%>" onchange="BchangeEndNo(this)" />
																</td>
															</tr>
															<tr align="center" valign="middle">
																<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	资产所属
																</td>
																<td align="left" valign="middle" class="tableHeader3" colspan="3">
																	<select name="bs_deptid" class="select01" onchange="BchangeDeptid(this)">
																		<option value="" checked>
																			请选择
																		</option>
																		<logic:present name="deptlist" scope="request">
																			<logic:iterate name="deptlist" id="dl" type="org.king.business.domain.DeptInfo">
																				<option value="<bean:write name="dl" property="deptCode"/>">
																					<bean:write name="dl" property="deptName" />
																				</option>
																			</logic:iterate>
																		</logic:present>
																	</select>
																</td>
															</tr>
															<tr align="center" valign=center>
																<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	用途大类
																</td>
																<td align="left" valign="middle" class="tableHeader3" colspan="3">
																	<table border="0" cellspacing="0" cellpadding="0">
																		<tr align="center" valign="middle">
																			<td width="35">
																				<select name="bs_usageCategory" class="select01" onchange="BchangeUsageCategory(this)">
																					<option value="" checked>
																						请选择
																					</option>
																					<logic:present name="uclist" scope="request">
																						<logic:iterate name="uclist" id="uc" type="java.util.Map">
																							<option value="<bean:write name="uc" property="id"/>">
																								<bean:write name="uc" property="usageCategoryName" />
																							</option>
																						</logic:iterate>
																					</logic:present>
																				</select>
																				<input type="hidden" name="busageCategory" value="<%=request.getParameter("busageCategory")==null||request.getParameter("busageCategory").equals("null")?"":request.getParameter("busageCategory")%>">
																			</td>
																			<td width="20">
																				&nbsp;
																			</td>
																			<td width="40" align="right">
																				<input name="btempUsageCategory" style="input_box" maxlength="50" value="<%=request.getParameter("btempUsageCategory")==null||request.getParameter("btempUsageCategory").equals("null")?"":request.getParameter("btempUsageCategory")%>"
																					readonly="readonly" />
																			</td>
																			<td width="20">
																				&nbsp;
																			</td>
																			<td width="20" align="right">
																				<input name="addUsageCategory" type="button" value="查找"
																					onclick="javascript:window.open('deptUsageCategoryAction.do?method=search4List&formName=yhpsearchForm&addNum='+idcount,'newwindow','height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes');">
																			</td>
																		</tr>
																	</table>
																</td>
															</tr>
															<tr align="center" valign=center>
																<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	用途说明
																</td>
																<td colspan="3" align="left" valign="middle" class="tableHeader3">
																	<textarea name="yhpUsage" cols=70 rows=2 maxLength="100" onchange="BchangeYhpUsage(this)"></textarea>
																</td>
															</tr>
															<tr align="center" valign=center>
																<td height="26" align="right" valign="middle" bgcolor="#FFFFFF" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
																	备注
																</td>
																<td colspan="3" align="left" valign="middle" class="tableHeader3">
																	<textarea name="memo" cols=70 rows=2 maxLength="300" onchange="BchangeMemo(this)"></textarea>
																</td>
															</tr>

															<logic:iterate name="yhpbatchlist" id="ebl" type="java.util.Map" indexId="i">
																<input type="text" name="yhpNo_<bean:write name="ebl" property="yhpKucunInfo.id"/>" value="<bean:write name="ebl" property="yhpKucunInfo.id"/>" readonly="readonly">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>old_wlid" value="<bean:write name="ebl" property="wlid"/>">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>new_wlid" value="">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>old_beginNo" value="<bean:write name="ebl" property="yhpKucunInfo.beginNo"/>">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>new_beginNo" value="">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>old_endNo" value="<bean:write name="ebl" property="yhpKucunInfo.endNo"/>">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>new_endNo" value="">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>old_deptid" value="<bean:write name="ebl" property="deptid"/>">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>new_deptid" value="">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>old_usageCategory" value="<bean:write name="ebl" property="usageCategory"/>">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>new_usageCategory" value="">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>old_yhpUsage" value="<bean:write name="ebl" property="yhpKucunInfo.yhpUsage"/>">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>new_yhpUsage" value="">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>old_memo" value="<bean:write name="ebl" property="yhpKucunInfo.memo"/>">
																<input type="hidden" name="<bean:write name="ebl" property="yhpKucunInfo.id"/>new_memo" value="">
															</logic:iterate>

														</logic:present>
													</tbody>
												</table>
											</td>
										</tr>
										<tr>
											<td height="30" align="right" valign="middle">
												<%if (idsCount == 1) {%>
												<input name="Submit11" type="button" class="button_nor" value="保 存" onclick="doSave();">
												<%} else if (idsCount > 1) {%>
												<input name="Submit10" type="button" class="button_nor" value="批量保存" onclick="doBatchSave();">
												<%}%>
												&nbsp;
												<input name="Submit12" type="button" class="button_nor" value="返 回" onClick="DoBack()">
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</table>
						<logic:present name="msg" scope="request">
							<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
						</logic:present>
						<logic:notPresent name="msg" scope="request">
							<input name="hmsg" type="hidden" value="">
						</logic:notPresent>
						<logic:present name="nccols" scope="request">
							<input name="hnccols" type="hidden" value="<bean:write name="nccols" />">
						</logic:present>
						<logic:notPresent name="nccols" scope="request">
							<input name="hnccols" type="hidden" value="">
						</logic:notPresent>

						<jodd:form bean="request">
							<input type="hidden" name="ec_i" />
							<input type="hidden" name="ec_p" />
							<input type="hidden" name="ec_crd" />
							<input type="hidden" name="search_bh" />
							<input type="hidden" name="search_wlmc" />
							<input type="hidden" name="search_bNo" />
							<input type="hidden" name="search_eNo" />
							<input type="hidden" name="search_hth" />
							<input type="hidden" name="search_sccj" />
							<input type="hidden" name="search_ly" />
							<input type="hidden" name="search_dhh" />
							<input type="hidden" name="search_yhpNumc" />
							<input type="hidden" name="search_yhpNumd" />
							<input type="hidden" name="search_curNumc" />
							<input type="hidden" name="search_curNumd" />
							<input type="hidden" name="search_gys" />
							<input type="hidden" name="search_ytdl" />
							<input type="hidden" name="search_dhrqc" />
							<input type="hidden" name="search_dhrqd" />
							<input type="hidden" name="search_curNumc" />
							<input type="hidden" name="search_curNumd" />
							<input type="hidden" name="search_cgrqc" />
							<input type="hidden" name="search_cgrqd" />
							<input type="hidden" name="search_rzrqc" />
							<input type="hidden" name="search_rzrqd" />
							<input type="hidden" name="search_dfprqc" />
							<input type="hidden" name="search_dfprqd" />
							<input type="hidden" name="search_djc" />
							<input type="hidden" name="search_djd" />
							<input type="hidden" name="search_fphm" />
							<input type="hidden" name="search_jfly" />
							<input type="hidden" name="search_cgjbr" />
							<input type="hidden" name="search_dhjbr" />
							<input type="hidden" name="search_pfdx" />
							<input type="hidden" name="search_xq" />
							<input type="hidden" name="search_louyu" />
							<input type="hidden" name="search_jfkf" />

						</jodd:form>
						</html:form>
	</body>
</html>

<script>

    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("dxlist")!=null)
       resultset=(String[][])request.getAttribute("dxlist");//读取大小类对应数据
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//产生javascript二维数组，对应小类id、小类名称、大类id
     <%
     }
   }
   %>
   datacount=<%=count%>;

</script>
<script>

    var datacount2=0;
    dataset2=new Array();
    
   <%
   int count2=0;
   String[][] resultset2=null;
   if(request.getAttribute("xmlist")!=null)
       resultset2=(String[][])request.getAttribute("xmlist");//读取小类、名称对应数据
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>","<%=resultset2[count2][3]%>");//产生javascript二维数组，对应名称id、物料名称、物料单位、小类id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>


<script type="text/javascript">

if(idcount==1)
   setTimeout('DoInit()',10);
else if(idcount>1)
   setTimeout('DoBatchInit()',10);

function DoInit(){ 
  var wl,dept,uc;
  var haswl=false;
  var hasuc=false;
     //alert(document.yhpsearchForm.elements["wlid"].value);     
     wl=document.yhpsearchForm.elements["wlid"].value;
     dept=document.yhpsearchForm.elements["deptid"].value;     
     uc=document.yhpsearchForm.elements["usageCategory"].value;    
    
   for(var j=0;j<document.yhpsearchForm.elements["s_wlid"].length;j++){
      if(document.yhpsearchForm.elements["s_wlid"][j].value==wl){
	     document.yhpsearchForm.elements["s_wlid"][j].selected=true;
	     haswl=true;
	  }
   }
   if(wl!='')
       changeDW(document.yhpsearchForm.elements["s_wlid"]);
       
   if(haswl){
       document.yhpsearchForm.elements["s_wlid"].style.display='';
       document.yhpsearchForm.elements["tempwlmc"].style.display='none';
   }
   else{
       document.yhpsearchForm.elements["s_wlid"].style.display='none';
       document.yhpsearchForm.elements["tempwlmc"].style.display='';   
   }
   
   for(var i=0;i<document.yhpsearchForm.elements["s_deptid"].length;i++){//部门
       if(document.yhpsearchForm.elements["s_deptid"][i].value==dept)
            document.yhpsearchForm.elements["s_deptid"][i].selected=true;
   
   }
     
   for(var i=0;i<document.yhpsearchForm.elements["s_usageCategory"].length;i++){//用途大类
       if(document.yhpsearchForm.elements["s_usageCategory"][i].value==uc){
            document.yhpsearchForm.elements["s_usageCategory"][i].selected=true;
            hasuc=true;
       }
   }
   
   if(hasuc){
       document.yhpsearchForm.elements["s_usageCategory"].style.display='';
       document.yhpsearchForm.elements["tempUsageCategory"].style.display='none';
   }
   else{
       document.yhpsearchForm.elements["s_usageCategory"].style.display='none';
       document.yhpsearchForm.elements["tempUsageCategory"].style.display='';   
   }
   
   if(document.all.hmsg.value=='1')
       alert("保存成功！");
   else if(document.all.hmsg.value=='0')
       alert("保存失败！");
   if(document.all.hnccols.value!='')
       alert(document.all.hnccols.value+" 已在审核中，不能修改！");
}

function DoBatchInit(){

   var wl,dept,uc;
   var haswl=false;
     //alert("idcount="+idcount);     
     wl=document.all.bwlid.value;
     //dept=document.all.bdeptid.value;     
     uc=document.all.busageCategory.value;
 
   for(var j=0;j<document.all.bs_wlid.length;j++){
      if(document.all.bs_wlid[j].value==wl){
	     document.all.bs_wlid[j].selected=true;
	     haswl=true;
	  }
   }
   if(wl!='')
       BchangeDW(document.all.bs_wlid);
       
   if(haswl){
       document.all.bs_wlid.style.display='';
       document.all.btempwlmc.style.display='none';
   }
   else{
       document.all.bs_wlid.style.display='none';
       document.all.btempwlmc.style.display='';   
   }
   
   for(var i=0;i<document.all.bs_usageCategory.length;i++){//用途大类
       if(document.all.bs_usageCategory[i].value==uc){
           document.all.bs_usageCategory[i].selected=true;
           hasuc=true;
       }
   }
   
   if(hasuc){
       document.all.bs_usageCategory.style.display='';
       document.all.btempUsageCategory.style.display='none';
   }
   else{
       document.all.bs_usageCategory.style.display='none';
       document.all.btempUsageCategory.style.display='';   
   }
   
   if(document.all.hmsg.value=='1')
       alert("保存成功！");
   else if(document.all.hmsg.value=='0')
       alert("保存失败！");
   if(document.all.hnccols.value!='')
       alert(document.all.hnccols.value+" 已在审核中，不能修改！");
}

function changeDW(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][0] == id)
          {   
             document.yhpsearchForm.elements["wldw"].value=dataset2[i][2];                
          }
      }
    else
       document.yhpsearchForm.elements["wldw"].value="";

}

function changeWlid(obj){

    document.all.new_wlid.value=obj.value;
    document.all.ifChanged.value="1";
    
}

function changeBeginNo(obj){

    document.all.new_beginNo.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeEndNo(obj){

    document.all.new_endNo.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeDeptid(obj){

    document.all.new_deptid.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeUsageCategory(obj){

    document.all.new_usageCategory.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeYhpUsage(obj){

    document.all.new_yhpUsage.value=obj.value;
    document.all.ifChanged.value="1";
}

function changeMemo(obj){

    document.all.new_memo.value=obj.value;
    document.all.ifChanged.value="1";
}

function DoaddWlmc(){

window.open("deptWlmcAction.do?method=search4List&formName=yhpsearchForm&addNum="+idcount+"&wldl="+document.yhpsearchForm.elements["s_dlid"].value+"&wlxl="+document.yhpsearchForm.elements["s_xlid"].value+"&dlbh=81&lbbh=81","newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");

}

function doSave(){

if(document.all.ifChanged.value=='0'){ 
    alert("您没有修改任何字段。");
    return;
}

if(document.all.ifChanged.value=='1'&&doCheckForm(yhpsearchForm)){
	yhpsearchForm.action="yhpAction.do?method=update";
	yhpsearchForm.submit();
	}
}

function BchangeDW(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][0] == id)
          {   
             document.all.bwldw.value=dataset2[i][2];                
          }
      }
    else
       document.all.bwldw.value="";

}

function BchangeWlid(obj){
    
    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_wlid.value=obj.value;");        
    document.all.ifChanged.value="1";
    
}

function BchangeBeginNo(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_beginNo.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeEndNo(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_endNo.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeDeptid(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_deptid.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeUsageCategory(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_usageCategory.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeYhpUsage(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_yhpUsage.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BchangeMemo(obj){

    for (var i=0;i<idset.length;i++)          
        eval("document.all."+idset[i]+"new_memo.value=obj.value;");        
    document.all.ifChanged.value="1";
}

function BDoaddWlmc(){

window.open("deptWlmcAction.do?method=search4List&formName=yhpsearchForm&addNum="+idcount+"&wldl="+document.all.bs_dlid.value+"&wlxl="+document.all.bs_xlid.value+"&dlbh=81&lbbh=81","newwindow","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");

}

function doBatchSave(){

if(document.all.btempwlmc.value!=''&&document.all.ifChanged.value=='1')
     BchangeWlid(document.all.bwlid);
     
if(document.all.busageCategory.value!=''&&document.all.ifChanged.value=='1')
     BchangeUsageCategory(document.all.busageCategory);

if(document.all.ifChanged.value=='1'){
	yhpsearchForm.action="yhpAction.do?method=batchupdate";
	yhpsearchForm.submit();
	}
else{
    alert("您没有修改任何字段。");
    return;
}
}

function DoViewArlInfo(){
if(document.all.ifChanged.value=='1'){

   if(confirm("有字段更改未保存，确实要离开此页面吗？")){
    if(idcount>1){
        alert("多选情况下不能查看到货记录！");    
    }
    else if(idcount==1){
        yhpsearchForm.action="yhpAction.do?method=arlInfo&yhpNo="+document.yhpsearchForm.elements["yhpKucunInfo.id"].value;
	    yhpsearchForm.submit();
    }
   }else
       return;
       
}else{
   if(idcount>1){
        alert("多选情况下不能查看到货记录！");    
    }
    else if(idcount==1){
        yhpsearchForm.action="yhpAction.do?method=arlInfo&yhpNo="+document.yhpsearchForm.elements["yhpKucunInfo.id"].value;
	    yhpsearchForm.submit();
    }
}

}

function DoBack(){   
   yhpsearchForm.action="yhpAction.do?method=search4List";
   yhpsearchForm.submit();
}
</script>
