
<%@ include file="/html/extportlet/ecard/faq/init.jsp"%>
<%
ResultPage curpage = (ResultPage) request.getAttribute("result");
List list = curpage.getList();
%>
<table width="719" height="29"  border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td><table width="100%"  border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="2%">&nbsp;</td>
          <td width="72%" class="text_blue_12_c"><bean:message key="ecardfaq.tab.faqlist" /></td>
          <td width="11%" valign="bottom">&nbsp;</td>
          <td width="15%" align="right" valign="middle" nowrap class="text_brown">&nbsp;</td>
        </tr>
      </table></td>
    </tr>
  </table>
    <table width="100"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="5"></td>
      </tr>
    </table>
    <table width="719"  border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td>&nbsp;</td>
        <td valign="top" align=center>
        <!-- content table -->
        
        
        <table width="100%"  border="0" cellspacing="4" cellpadding="0">
        	<a id="#topfaq">&nbsp;</a>
        	<%java.util.Iterator it = list.iterator();				
					while(it.hasNext()) {
						EcardInformation info = (EcardInformation) it.next();
					%>
					<tr>            
            <td valign="baseline"  align="left">
            	<img src="/html/extthemes/classic/images/ecard/jiantou.jpg" width="8" height="8">
                  <a class=blue_link_line href="#<portlet:namespace /><%= info.getId()%>">
                  	<%= info.getInfoTitle()%></a>
            </td>            
          </tr>
           <%}%>
           <tr>
				<td>
					&nbsp;
	           </td>            
          </tr>
        </table>
          
          <table width="100%" height="1"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td></td>
            </tr>
          </table>
          <table width="100%" height="5"  border="0" cellpadding="0" cellspacing="0">
            <tr>
              <td></td>
            </tr>
          </table>              
          <table width="100%"  border="0" cellspacing="0" cellpadding="0">
          	<tr>
          		<td >
        	<%it = list.iterator();				
					while(it.hasNext()) {
						EcardInformation info = (EcardInformation) it.next();
					%>
			<table width="100%"  border="0" cellspacing="2" cellpadding="0">					
			<tr>							            
            <td align="left">
            		
                  <a class=blue_link_line href="#topfaq">
                  	Top</a>
             </td>
             </tr>
			<tr>							            
            <td align="left">
            		
                  <a id="#<portlet:namespace /><%= info.getId()%>">
                  	<a class=text_blue_12_c>Q</a>:<%= info.getInfoTitle()%></a>
             </td>
             </tr>
             <tr>							            
            <td align="left">
                  	<a class=text_blue_12_c>A</a>:<%= StringUtil.replace(StringUtil.replace(info.getInfoContent(), "<DIV>", ""), "</DIV>", "")%>
             </td>
             </tr>
             <tr>
             	<td>
             		&nbsp;
             	</td>
             </tr>
             <tr>
             	<td>
             		&nbsp;
             	</td>
             </tr>
             </table>
                	<%}%>
                </td>
			</tr>
        </table>
          <!-- content table --></td>
        <td>&nbsp;</td>
      </tr>
    </table>