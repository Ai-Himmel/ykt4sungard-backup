<%@ page import="java.net.URLEncoder" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec" %>
<%@ include file="/commons/init.jsp" %>
<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%request.setCharacterEncoding("GBK"); %>
<head>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css"/>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css"/>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css"/>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/extremecomponents.css" rel="stylesheet"
          type="text/css"/>
</head>
<%String titles = request.getAttribute("title").toString();%>
<%List result = (List) request.getAttribute("result");%>
 
<table border="0" cellpadding="0" cellspacing="0" width="100%">
    <tr>
        <td>
            <ec:table items="result"
                      var ="person"
                      title="<%=titles%>"
                      filterable="false"
                      imagePath="${pageContext.request.contextPath}/commons/ximages/*.gif"
                      rowsDisplayed="15"
                      locale="zh_CN"
                      saveFilterSort="true"
                      action="/advquery/financestat/lunchperson_queryresult.do"
                     
                      >
                
                <ec:export
                        view="xls"
                        fileName="output.xls"/>
                   
                <ec:row highlightRow="true">
                     
                     <ec:column property="name" title='<%= GetProperty.getProperties("select",getServletContext())%>'
                        style="width:5px" filterable="false"  width="5%" sortable="false"> 
                        <input type="checkbox" name="cutId" value="${person.cut_id}" /> 
                     </ec:column> 
                  
                     

                    <ec:column property="dept_name" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.dept",getServletContext())%>'/>
                    <ec:column property="stuemp_no" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.stuempno",getServletContext())%>'/>
                    <ec:column property="cut_name" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.cutname",getServletContext())%>'/>
                    <ec:column property="phy_ID" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.cardno",getServletContext())%>'/>
                    <ec:column property="lunch_type" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.type",getServletContext())%>'/>             
                    <ec:parameter name="tradedept" value='<%=request.getSession().getAttribute("tradedept")==null?"":URLEncoder.encode((String)request.getSession().getAttribute("tradedept"))%>'></ec:parameter>     
                </ec:row>
                   
            </ec:table>
           <form action="/advquery/financestat/lunchperson_delete.do"  name="personform" id="personform"         method="post">
            <input type="hidden" name="cutids"> 
            <table border="0" cellpadding="0" cellspacing="0" width="100%">
               <tr> <td align="right">
            	      <button onclick="check();"><bean:message key="btn.delete"/></button>
            	    </td>
               </tr> 
            </table>
            </form>
        </td>
    </tr>
</table>

<script language="javascript">
   function checkselect(){
		var len = document.getElementsByName("cutId").length; 
        var retstr = ""; 
        for (i = 0; i < len; i++) 
        { 
            if (document.getElementsByName("cutId")[i].checked == true) 
            {   
                retstr = retstr + document.getElementsByName("cutId")[i].value +","; 
            } 
        } 
        return retstr;
   }
   function check(){
   	 if(checkselect()!=""){
   	    document.personform.cutids.value=checkselect();
   	    
   	 	document.personform.submit();
   	 }
   }
</script>

