<%@ include file="/html/commons/init.jsp" %>
<%@ page import="java.util.ArrayList" %>

<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConference" %>

<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>

<head>
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css" rel="stylesheet" type="text/css" />
<html:base/>
</head>
<% 
	List conflist = (List) request.getAttribute("conflist");
%>

<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<script>	
	function checkquery() {
		document.analyseForm.query.value='1';
	}
</script>

<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td>&nbsp;</td>
  </tr>
  <tr> 
    <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
    	<span class="mediumwhite"><strong>
    		&nbsp;&nbsp;&nbsp;&nbsp;
    		<bean:message key="analyse.report"/>
    	</strong></span>
    </td>
  </tr>
  <tr> 
    <td align="left" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="left" valign="top" >
    	<form action="<%=ContextUtil.getCtxPath(request)%>/queryanalyse.do" name="analyseForm" method="post">
    	<table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
        	<tr> 
          		<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.list"/>
          		</td>
          		<td colspan="2" align="left" valign="middle" bgcolor="#E6ECF2">
          			<select name="listId" class="select01" style="width: 200">
          			<%
          				boolean checklist = false;
          				String listid = (String) request.getAttribute("listid");
          				if(null != listid) {
          					checklist = true;
          				}
          			%>
          				<option value="4" <%=checklist?("0".equals(listid)?"selected":""):"selected"%>><bean:message key="analyse.totle.list"/></option>
              			<option value="0" <%=checklist?("0".equals(listid)?"selected":""):""%>><bean:message key="analyse.attendance"/></option>
              			<option value="1" <%=checklist?("1".equals(listid)?"selected":""):""%>><bean:message key="analyse.late"/></option>
              			<option value="2" <%=checklist?("2".equals(listid)?"selected":""):""%>><bean:message key="analyse.leave"/></option>
              			<option value="3" <%=checklist?("3".equals(listid)?"selected":""):""%>><bean:message key="analyse.absence"/></option>
            		</select>
            	</td>
        	</tr>
        	<tr> 
          		<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.name"/>
          		</td>
          		<td width="37%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<select name="conId" class="select01" style="width: 200">
					<% 
						if(!conflist.isEmpty()) {							
							Iterator iter = conflist.iterator();	
							boolean checkconid = false;
							String conid = (String) request.getAttribute("conid");
							if(null != conid) {
								checkconid = true;
							}
							while(iter.hasNext()) {
								TConference conf = (TConference) iter.next();
					%>
              				<option value="<%=conf.getConId().toString()%>" <%=checkconid?(conid.equals(conf.getConId().toString())?"selected":""):""%>>
              					<%=conf.getConName()%>
              				</option>
              		<% 
							}
						}
					%>
            		</select>
            	</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
          			<input name="query" type="hidden" value="0">
    				<input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.query"/>" onClick="javascript:checkquery();" > 
    			</td>
        	</tr>
      	</table>
      	</form>
    </td>
  </tr>
  <tr> 
    <td align="left" valign="top" >
    	<table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
        	<% 
				TConference con = new TConference();
				boolean ifconf = false;
        		if(null != request.getAttribute("conference")) {
        			con = (TConference) request.getAttribute("conference");
        			ifconf = true;
        		}
        	%>
        	<tr> 
          		<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
					<bean:message key="analyse.name"/>
				</td>
          		<td colspan="3" align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=ifconf?con.getConName():""%>
          		</td>
        	</tr>
        	<tr> 
          		<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
					<bean:message key="analyse.explain"/>
				</td>
          		<td colspan="3" align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=ifconf?con.getConExplain():""%>
          		</td>
        	</tr>
        	<tr> 
          		<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.date"/>
          		</td>
          		<td width="35%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=ifconf?con.getConBegindate():""%><!-- &nbsp;<%//=con.getConBegintime()%>
          			&nbsp;--&nbsp;
          			<%//=con.getConEnddate()%>&nbsp;<%//=con.getConEndtime()%>-->
          		</td>
          		<td width="15%" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
	          		<bean:message key="analyse.time"/>
          		</td>
          		<td width="35%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<%//=con.getConBegindate()%>&nbsp;<%=ifconf?con.getConBegintime():""%>
          			<!-- &nbsp;--&nbsp;
          			<%//=con.getConEnddate()%>&nbsp;<%//=con.getConEndtime()%>-->
          		</td>
        	</tr>
        	<% 
        		ArrayList count = new ArrayList();
        		boolean if_count = false;
        		int attend=0, sign=0;
        		if(null != request.getAttribute("concount")) {
        			count = (ArrayList) request.getAttribute("concount");
        			if_count = true;
        			attend = ((Integer) count.get(0)).intValue();
        			sign = ((Integer) count.get(1)).intValue();
        		}
        	%>
        	<tr> 
          		<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.attecount"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
					<%=if_count?count.get(0):""%>
					<%
						if(if_count) {
							if(0 == attend) {
					%>
						<font class="portlet-msg-error" style="font-size: 11;">
						&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
						<bean:message key="analyse.countfalse1" />
						</font>
					<%
							}
							if(attend < sign ) {
					%>
						<font class="portlet-msg-error" style="font-size: 11;">
						&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
						<bean:message key="analyse.countfalse2" />
						</font>
					<%		
							}
						}
					%>				
				</td>
          		<td align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
	          		<bean:message key="analyse.factcount"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=if_count?count.get(1):""%>
          		</td>
        	</tr>
        	<tr> 
          		<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.latecount"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=if_count?count.get(2):""%>
          		</td>
          		<td align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.replcount"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=if_count?count.get(3):""%>
          		</td>
        	</tr>
        	<tr> 
          		<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.leavcount"/>
          		</td>
          		<td colspan="3" align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=if_count?count.get(4):""%>
          		</td>
        	</tr>
      	</table>
      </td>
  </tr>
<% 
	List result = (List) request.getAttribute("result");
%>
<form action="<%=ContextUtil.getCtxPath(request)%>/queryanalyse.do" name="analyse" method="post">
  <table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
  <tr> 
    <td align="center" valign="top">
    	<ec:table items="result"
		    	var="pres"
    			filterable="false"
    			imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
    			rowsDisplayed="10"
				action="${pageContext.request.contextPath}/queryanalyse.do"
				form="analyse">
			<ec:exportXls view="xls" fileName="output.xls"/>
				
			<ec:row highlightRow="true">				
				<ec:column property="cutName" headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("analyse.custname",getServletContext())%>' >
				</ec:column>
				<ec:column property="deptName" headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("analyse.custdept",getServletContext())%>' />
				<ec:column property="dutyName" headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("analyse.custduty",getServletContext())%>' />
				<ec:column property="attendSign" headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("analyse.signstatus",getServletContext())%>' />
				<ec:column property="attendTime" headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("analyse.signtime",getServletContext())%>' />
				<ec:column property="sendSign" headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("analyse.custsend",getServletContext())%>' />
				<ec:column property="informSign" headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("analyse.custinform",getServletContext())%>' />
			</ec:row>
		</ec:table>
    </td>
  </tr>
  </table>
  </form>
</table>
</body>