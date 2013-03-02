<%@ include file="/html/common/init.jsp" %>
<%@ include file="/html/portlet/ecard/hitinfo/permission.jsp" %>
<link href="/c/portal/css" type="text/css" rel="stylesheet" />
<%@ page import="java.text.SimpleDateFormat" %>
<%@ page import="org.apache.struts.validator.DynaValidatorForm" %>
<%@ page import="com.kingstargroup.ecard.hibernate.information.EcardInformation" %>
<%@ page import="com.kingstargroup.ecard.hibernate.hitinfo.EcardHitInfo" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.ResultPage" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.InformationUtil" %>
<%@ page import="com.kingstargroup.ecard.hibernate.util.HitInfoUtil" %>
<%@ page import="com.kingstargroup.ecard.util.EcardConstants" %>
<%@ page import="com.kingstargroup.ecard.util.PermissionUtil" %>
<%@ page import="com.kingstargroup.ecard.util.DateFormatUtil" %>
<%
request.setCharacterEncoding("UTF-8");
String search_title = ParamUtil.getString(request, "search_title");
List list = InformationUtil.search(search_title);
SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>

          <!-- content table -->
          <form name=SearchForm action="/html/portlet/ecard/hitinfo/inner_infolist.jsp" method="POST"
	onSubmit="javascript:validateSearchForm(this, '<bean:message key="ecard.error.keywordmaxlength" />'); return false;">
		
          <table border="0" cellpadding="0" cellspacing="0" width="100%">      
		<tr>
			<td>
				<input type=text name=search_title>&nbsp; 
				<input type=submit class=button_blank value='<bean:message key="ecardhit.button.filter" />'>
			</td>
		</tr>
		<tr>
			<td>&nbsp;</td>
		</tr>
		</table>
       <table width="100%" class="inside_table">
      <tr class="list_tr">
        <td width=3%>
			&nbsp;
		</td>
		<td width=82% align=center>
			<a class=text_blue_12_c><bean:message key="ecard.title" /></a>
		</td>
		<td width=15% align=center>
			<a class=text_blue_12_c><bean:message key="ecard.publishtime" /></a>
		</td>
      </tr>
      <%java.util.Iterator it = list.iterator();
      				int count = 0;
					while(it.hasNext()) {
						EcardInformation info = (EcardInformation) it.next();
						count++;
						int classId = count % 2 + 1;
					%>
	<tr class="tr_<%= classId%>" style="font-size: x-small;">
		<td width=10>
		<input type="radio" name="ids" value="<%= String.valueOf(info.getId())%>" onclick="javascript:parent.HitInputForm.mapInfoId.value=this.value;">
		
		</td>		
		<td align=center>
			
			<a class=text_blue_12>
			<%
				if("8".equals(info.getInfoType())){
			%>
			<bean:message key="ecardabout.tab.view" />
			<%
					
				}else if("9".equals(info.getInfoType())){
			%>
			<bean:message key="ecardservice.tab.view" />
			<%	
				}else{
			%>			
			<%=info.getInfoTitle() %>
			<%	
					
				}
			%>
			</a>			
		</td>
		<td align=center>
			<a class=text_blue_12>
			<%= format.format(info.getCreateDate())%>
			</a>
		</td>
	</tr>
	<%}%>

	</table>
</form>
<script>
	function validateSearchForm(form, errormsg) {
		if (form.search_title.value.length > 20) {
			alert(errormsg);
			return false;
		}
		submitForm(form);
	}
</script>
            <!-- content table -->
