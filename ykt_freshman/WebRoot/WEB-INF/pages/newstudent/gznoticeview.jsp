<%@page pageEncoding="GBK"%>
<%@ include file = "../tiles/include.jsp"%>

<center>

<html:form action = "gznoticeAction.do?method=find">
<html:errors/>
<br>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td height="30" align="left" valign="middle" class="tdborder02"><strong><font class="medium">新生入学事项公告</font></strong></td>
  </tr>
  <tr>
    <td align="center" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top" >    
    <table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
        <tbody>     
        <logic:present name="noticelist" scope="request">
            <logic:iterate name="noticelist" id="nl" type="java.util.Map"  indexId="i">     
          <tr valign=center bgcolor="#FFFFFF" >            
            <td align="center" valign="middle" colspan="4"><FONT size=5 color=#ee3d11><STRONG><bean:write name="nl" property="title"/></STRONG></FONT></td>
          </tr> 
          <tr valign=center bgcolor="#FFFFFF" ><td>&nbsp;</td></tr> 
          <tr align="center" valign=center bgcolor="#FFFFFF" >             
            <td colspan="4" align="left" valign="middle" >
            <textarea name="body" style="width:1px;height:1px;"><bean:write name="nl" property="body"/></textarea >
            <script>document.write(document.all.body.value);</script>            
            </td>
          </tr>
          </logic:iterate>
          </logic:present>
        </tbody>
      </table></td>
  </tr>
  <tr> 
    <td height="40" align="right" valign="middle"> 
      <input name="Submit" type="submit" class="button_nor" value="返 回" > 
    </td>
  </tr>
</table>

</html:form>
</center>
