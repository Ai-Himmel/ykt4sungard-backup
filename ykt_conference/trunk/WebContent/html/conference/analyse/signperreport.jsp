<%@ include file="/html/commons/init.jsp" %>
<%@ include file="/html/commons/top_calendar.jsp"%>

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
	List conftype = (List) request.getAttribute("conftype");
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
    		<bean:message key="analyse.signpercent"/>
    	</strong></span>
    	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<c:if test='<%=SessionErrors.contains(request, "analyse.failed.date")%>'>	
			<font class="portlet-msg-error" style="font-size: 11;">					
				<bean:message key="analyse.failed.date" />
			</font>
		</c:if>
    </td>
  </tr>
  <tr> 
    <td align="left" valign="top" >&nbsp;</td>
  </tr>  
  <tr> 
    <td align="left" valign="top" >    
  		<form action="<%=ContextUtil.getCtxPath(request)%>/querysignper.do" name="signPerAnalyseForm" method="post"> 		      	
    	<table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
        	<tr>         	
          		<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.name"/>
          		</td>
          		<td width="37%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<select name="conId" class="select01" style="width: 150">
          					<OPTION></OPTION>
					<% 
						if(!conflist.isEmpty()) {
							Iterator citer = conflist.iterator();	
							boolean checkconid = false;
							String id = "";
							String conid = ParamUtil.getString(request,"conId");
							if(null != conid) {
								checkconid = true;
							}
							while(citer.hasNext()) {
								TConference conf = (TConference) citer.next();
								id = conf.getConId().toString();
					%>
              				<option value="<%=id%>" <%=checkconid?(conid.equals(id)?"selected":""):""%>>
              					<%=conf.getConName()%>
              				</option>
              		<% 
							}
						}
					%>
            		</select>
            	</td>
            	<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.type"/>
          		</td>
          		<td width="37%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<select name="conType" class="select01" style="width: 150">
          					<OPTION></OPTION>
					<% 
						String contype = ParamUtil.getString(request,"conType");
						if(!conftype.isEmpty()) {
							Iterator titer = conftype.iterator();
							boolean checktype = false;	
							String type = "";					
							if(null != contype) {
								checktype = true;
							}
							while(titer.hasNext()) {
								type = (String) titer.next();
					%>
              				<option value="<%=type%>" <%=checktype?((contype.equals(type))?"selected":"" ):""%>>
              					<%=type%>
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
          			<bean:message key="analyse.begindate"/>
          		</td>
          		<td width="37%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<table width="100%" border="0" cellspacing="0" cellpadding="0">
                		<tr> 
                  			<td width="130"> 
                  				<input name=begindate class="input_box" maxlength=50 readonly="true" style="width: 150"> 
                  			</td>
                  			<td>
                  				<a href="#">
                  					<img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/date.gif" width="21" height="21" border="0" id="f_trigger_begindate">
                  				</a>
                  			</td>
                		</tr>
              		</table>
            	</td>
            	<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.enddate"/>
          		</td>
          		<td width="37%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<table width="100%" border="0" cellspacing="0" cellpadding="0">
                		<tr> 
                  			<td width="130"> 
                  				<input name=enddate class="input_box" maxlength=50 readonly="true" style="width: 150"> 
                  			</td>
                  			<td>
                  				<a href="#">
                  					<img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/date.gif" width="21" height="21" border="0" id="f_trigger_enddate">	
                  				</a>
                  			</td>
                		</tr>
              		</table>
            	</td>
            </tr>  
            <tr>
  				<td colspan="4" height="35" align="right" valign="middle">
    				<input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.query"/>" > 
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
				boolean iftype = false;
        		if(null != request.getAttribute("conference")) {
        			List conlist = (List) request.getAttribute("conference");
        			if(!conlist.isEmpty()) {
        				Iterator coniter = conlist.iterator();
        				if(coniter.hasNext()) {
	        				con = (TConference) coniter.next();
	        			}
	        			if(coniter.hasNext()) {
	        				ifconf = false;
	        			} else {
	        				ifconf = true;
	        			}
	        		}
        		} else if (null != contype) {
        			iftype = true;
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
          			<bean:message key="analyse.type"/>
          		</td>
          		<td width="35%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=iftype?contype:(ifconf?con.getTypeName():"")%>
          		</td>
          		<td width="15%" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
	          		<bean:message key="analyse.code"/>
          		</td>
          		<td width="35%" align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=ifconf?con.getConId().toString():""%>
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
        		boolean if_per = false;
        		int attend=0, sign=0;
        		float percent=0;
        		if(null != request.getAttribute("concount")) {
        			count = (ArrayList) request.getAttribute("concount");
        			if_count = true;
        			attend = ((Integer) count.get(0)).intValue();
        			sign = ((Integer) count.get(1)).intValue();
        			if(0<attend) {
        				percent = sign *10000 /attend /100.00f;
        			} else if(0==attend) {
        				if_per = true;
        				percent = 100;
        				if(0 != sign) {
        					percent = sign *100;
        					if_per = false;
        				}	
        			}
        		}
        	%>
        	<tr> 
          		<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.attendcount"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
					<%=if_count?String.valueOf(attend):""%>
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
	          		<bean:message key="analyse.signcount"/>
          		</td>
          		<td align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=if_count?String.valueOf(sign):""%>
          		</td>
        	</tr>
        	<tr> 
          		<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
          			<bean:message key="analyse.signper"/>
          		</td>
          		<td colspan="3" align="left" valign="middle" bgcolor="#E6ECF2">
          			<%=(if_count && !if_per)?(percent + "%"):""%>
          		</td>
        	</tr>
      	</table>  
     </td>
  </tr>
  <tr> 
    <td align="left" valign="top" >&nbsp;</td>
  </tr>
</table>
<script>
	function cancelPage() {
      	self.location = '<%= ContextUtil.getCtxPath(request)%>/anal/querysignper.do';
	}
</script>
<script language="JavaScript">
	
	Calendar.setup({
        inputField     :    "begindate",     // id of the input field
        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    
	Calendar.setup({
        inputField     :    "enddate",     // id of the input field
        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
</script>
</body>