<%@ include file="/html/common/init.jsp" %>
<%@page import="org.apache.struts.validator.DynaValidatorForm"%>
<%@page import="com.kingstargroup.ecard.util.DateFormatUtil"%>
<%@ page import="com.kingstargroup.ecard.KSConfiguration"%>
<%@page import="com.liferay.portal.kernel.language.LanguageUtil"%>
<%@page import="com.liferay.util.servlet.SessionErrors"%>
<%@page import="com.kingstargroup.ecard.util.EcardConstants"%>
<%@page pageEncoding="GBK"%>
<portlet:defineObjects />
<%
	String gbeginDate = DateFormatUtil.getDateLaterNow();
	String gendDate = DateFormatUtil.getNowDate();
	Object obj = request.getAttribute("CheckAttDetailQueryForm");
	if (obj != null) {
		gbeginDate = (String) ((DynaValidatorForm) obj).get("gbeginDate");
		gendDate = (String) ((DynaValidatorForm) obj).get("gendDate");	
	}

%>
<form action="/ext/querycheckattdetailview_result" method="POST" >
	<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
          <tr>
            <td width="3%"></td>
            <td width="20%" valign="baseline" class="text_or_12"><bean:message key="ecard.beginDate" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12">            
				<html:text styleId="gbeginDate" property="gbeginDate" readonly="true" size="30" value="<%= gbeginDate%>" maxlength="10" onkeydown="monitorDateInput()" />	
				&nbsp;
				<img align="absmiddle" style="cursor: pointer;" border="0" hspace="0" id="f_trigger_begindate_g" src="/html/extthemes/classic/images/calendar/calendar.gif" vspace="0" onClick="zgat_jsOnClick('zgat_jsCalendarObj');">
            </td>
            <td width="20%" align=left><font  style="font-size: 11;"><html:errors
							property="beginDate" />
							</font></td>
          </tr>
          <tr>
          	<td width="3%"></td>
            <td width="20%" valign="baseline" class="text_or_12"><bean:message key="ecard.endDate" />: 
              </td>
            <td width="60%" valign="baseline" class="text_or_12">
            	<html:text styleId="gendDate" property="gendDate" size="30" readonly="true" value="<%= gendDate%>" maxlength="10" onkeydown="monitorDateInput()" />	
            	&nbsp;            	
            	<img align="absmiddle" style="cursor: pointer;" border="0" hspace="0" id="f_trigger_enddate_g" src="/html/extthemes/classic/images/calendar/calendar.gif" vspace="0" onClick="lnqb_jsOnClick('lnqb_jsCalendarObj');">
            </td>
    
            <td width="20%" align=left><font style="font-size: 11;"><html:errors
							property="gendDate" />
							</font></td>
          </tr>
	</table>
	<table width=100% border=0 align=center cellpadding=0 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
		<tr>
			<td align="center" valign="middle" bgcolor="#E7F1F5">
				<input name="Submit22" type="button" value=" ²é Ñ¯ " onclick="document.CheckAttDetailQueryForm.submit();">
			</td>
		</tr>
	</table>
</form>
      <script language="JavaScript">
                    
                Calendar.setup({
                    inputField     :    "gbeginDate",     // id of the input field
                    button         :    "f_trigger_begindate_g",  // trigger for the calendar (button ID)
                    align          :    "Bl",           // alignment (defaults to "Bl")
                    singleClick    :    true
                });
                
                Calendar.setup({
                    inputField     :    "gendDate",     // id of the input field
                    button         :    "f_trigger_enddate_g",  // trigger for the calendar (button ID)
                    align          :    "Bl",           // alignment (defaults to "Bl")
                    singleClick    :    true
                });
            </script>
    
    <script>
