<%@ include file="/html/commons/init.jsp" %>
<%@ include file="/html/commons/top_calendar.jsp"%>

<%@ page import="java.util.ArrayList" %>

<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConference" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TPifDictionary" %>

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
	List statlist = (List) request.getAttribute("statlist");
%> 
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td>&nbsp;</td>
  </tr>
  <tr> 
    <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
    	<span class="mediumwhite"><strong>
    		&nbsp;&nbsp;&nbsp;&nbsp;
    		<bean:message key="analyse.sign"/>
    	</strong></span>
    </td>
  </tr>
  <tr> 
    <td align="left" valign="top" >&nbsp;</td>
  </tr>  
  <tr> 
    <td align="left" valign="top" >  
		<form action="<%=ContextUtil.getCtxPath(request)%>/querysign.do" id="signAnalyseForm" name="signAnalyseForm" method="post">      	
    	<table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
        	<tr> 
          		<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.name"/>
          		</td>
          		<td colspan="3" align="left" valign="middle" bgcolor="#E6ECF2">
          			<select name="conId" class="select01" style="width: 150">
					<% 
						if(!conflist.isEmpty()) {
							Iterator citer = conflist.iterator();
							boolean checkconid = false;
							String conid = ParamUtil.getString(request,"conId");
							if(null != conid) {
								checkconid = true;
							}
							while(citer.hasNext()) {
								TConference conf = (TConference) citer.next();
					%>
              				<option value="<%=conf.getConId().toString()%>"
              				 <%=checkconid?(conid.equals(conf.getConId().toString())?"selected":""):""%>>
              					<%=conf.getConName()%>
              				</option>
              		<% 
							}
						}
					%>
            		</select>
            	</td>
            </tr>   
            <tr> 
        		<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.duty"/>
          		</td>
          		<td width="37%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<input name="duty" class="input_box" maxlength=50 style="width: 150">
            	</td>
            	<td width="15%" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.signstatus"/>
          		</td>
          		<td width="37%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<select name="status" class="select01" style="width: 150">
          				<OPTION></OPTION>
					<% 
						if(!statlist.isEmpty()) {
							Iterator siter = statlist.iterator();
							boolean checkstat = false;
							String stat = ParamUtil.getString(request,"status");
							if(null != stat) {
								checkstat = true;
							}
							while(siter.hasNext()) {
								TPifDictionary dict = (TPifDictionary) siter.next();
								String values = dict.getId().getDictValue();
					%>
              				<option value="<%=values%>"
              				 <%=checkstat?(stat.equals(values)?"selected":""):""%>>
              					<%=dict.getDictCaption()%>
              				</option>
              		<% 
							}
						}
					%>
            		</select>
            	</td>
            </tr>         
  			<tr>
  				<td colspan="4" height="35" align="right" valign="middle">
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
    	<table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
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
          			<bean:message key="analyse.type"/>
          		</td>
          		<td width="35%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=ifconf?con.getTypeName():""%>
          		</td>
          		<td width="15%" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
	          		<bean:message key="analyse.code"/>
          		</td>
          		<td width="35%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=ifconf?(con.getConId().toString()):""%>
          		</td>
        	</tr>
        	<% 
        		ArrayList count = new ArrayList();
        		boolean if_count = false;
        		boolean if_per = false;
        		int attend=0, sign=0, late=0, replace=0, leave=0, signcount=0;
        		float signper=0, lateper=0, replaceper=0, leaveper=0;
        		if(null != request.getAttribute("concount")) {
        			count = (ArrayList) request.getAttribute("concount");
        			if(!count.isEmpty()) {
	        			if_count = true;
	        			attend = ((Integer) count.get(0)).intValue();
    	    			sign = ((Integer) count.get(1)).intValue();
        				late = ((Integer) count.get(2)).intValue();
        				replace = ((Integer) count.get(3)).intValue();
        				leave = ((Integer) count.get(4)).intValue();
        			//	signcount = ((Integer) count.get(5)).intValue();
        			
        				if(0 < attend) {
        					signper = sign *10000 /attend /100.00f;
	        				lateper = late *10000 /attend /100.00f;
	        				replaceper = replace *10000 /attend /100.00f;
    	    				leaveper = leave *10000 /attend /100.00f;
    	    				if_per = true;
        				} else if(0==attend) {
        					if(0 != sign) {
        						signper = sign *100;
        						if_per = true;
	        				} else {
    	    					signper = 100;
        					}
        					if(0 != late) {
        						lateper = late *100;
        						if_per = true;
        					} else {
        						lateper = 0;
	        				}
    	    				if(0 != replace) {
        						replaceper = replace *100;
        						if_per = true;
        					} else {
        						replaceper = 0;
        					}
	        				if(0 != leave) {
    	    					leaveper = leave *100;
        						if_per = true;
        					} else {
        						leaveper = 0;
        					}
        				}
        			}
        		}
        	%>
        	<tr> 
          		<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.oughtattend"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
					<%=if_count?String.valueOf(attend):""%>
					<font class="portlet-msg-error" style="font-size: 11;">
						&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<%
						if(if_count) {
							if(0 == attend) {
					%>
						<bean:message key="analyse.countfalse1" />
					<%
							}
							if(attend < sign ) {
					%>
						<bean:message key="analyse.countfalse2" />
					<%		
							}
						}
					%>
					</font>
				</td>
          		<td align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
	          		<bean:message key="analyse.attendtime"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=if_count?String.valueOf(sign):""%>
          		</td>
        	</tr>
        	<tr> 
          		<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.attendper"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
					<%=(if_count && if_per)?(String.valueOf(signper) + "%"):""%>
				</td>
          		<td align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
	          		<bean:message key="analyse.lateper"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=(if_count && if_per)?(String.valueOf(lateper) + "%"):""%>
          		</td>
        	</tr>
        	<tr> 
          		<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.replaceper"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
					<%=(if_count && if_per)?(String.valueOf(replaceper) + "%"):""%>
				</td>
          		<td align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
	          		<bean:message key="analyse.leaveper"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=(if_count && if_per)?(String.valueOf(leaveper) + "%"):""%>
          		</td>
        	</tr>
      	</table>
      </td>
  </tr>
<% 
	List result = (List) request.getAttribute("result");
%>    
<form action="<%=ContextUtil.getCtxPath(request)%>/querysign.do" id="signAnalyse" name="signAnalyse" method="post">	
<table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
  <tr> 
    <td align="center" valign="top">
    	<ec:table items="result"
		    	var="pres"
    			filterable="false"
    			imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
    			rowsDisplayed="10"
				action="${pageContext.request.contextPath}/querysign.do"
				form="signAnalyse"
				>
			<ec:exportXls view="xls" fileName="output.xls"/>
			<ec:row highlightRow="true">				
				<ec:column property="cutName" headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("analyse.custname",getServletContext())%>' />
				<ec:column property="deptName" headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("analyse.custdept",getServletContext())%>'/>
				<ec:column property="dutyName" headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("analyse.custduty",getServletContext())%>' />
				<ec:column property="tel" headerStyle="text-align:center"
						style="text-align:left"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("analyse.custtel",getServletContext())%>' />
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
  <tr> 
    <td align="center" valign="top">&nbsp;</td>
  </tr>
</table>
<script>	
	function checkquery() {
		document.signAnalyseForm.query.value='1';
	}
</script>

</body>