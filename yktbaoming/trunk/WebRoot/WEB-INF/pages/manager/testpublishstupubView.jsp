<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<center>

	<html:form action="testPublicAction.do?method=search4Listview">
		<html:errors />
		<br>
		<table width="90%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="left" valign="middle" class="tdborder02">
					<strong><font class="medium">考试信息查看</font></strong>
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
						<logic:present name="testpublishlist" scope="request">
                            <logic:iterate name="testpublishlist" id="nl" type="java.util.Map" indexId="i" length="1">					
							 <tr align="center"  valign="middle" bgcolor="#FFFFFF" >            
                                 <td align="center" valign="middle" colspan="4"><FONT size=5 color=#ee3d11><STRONG><bean:write name="nl" property="title"/></STRONG></FONT></td>
                             </tr>
                             <tr align="center" valign="middle" bgcolor="#FFFFFF" ><td>&nbsp;</td></tr>   
                             <tr align="center" valign="middle" bgcolor="#FFFFFF" >             
                                 <td colspan="4" align="left" valign="middle" >
                                     <textarea name="body" style="width:1px;height:1px;"><bean:write name="nl" property="body"/></textarea >
                                     <script>document.write(document.all.body.value);</script>            
                                 </td>
                             </tr>							
							</logic:iterate>
                        </logic:present>	
						</tbody>
					</table>
				</td>
			</tr>
			<tr>
				<td height="40" align="right" valign="middle">
                    <input name="cancel" type="submit" class="button_nor" value="返 回">
				</td>
			</tr>
		</table>

<input type="hidden" name="pager.offset" value="<%=request.getParameter("pager.offset")%>"/>
<html:hidden property="search_title" />
</html:form>
</center>
