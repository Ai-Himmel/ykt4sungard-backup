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
                      title="<%=titles%>"
                      filterable="false"
                      imagePath="${pageContext.request.contextPath}/commons/ximages/*.gif"
                      rowsDisplayed="15"
                      action="/advquery/financestat/lunch_queryresult.do"
                      >

                <ec:export
                        view="xls"
                        fileName="output.xls"/>
                <ec:row highlightRow="true">
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
                    <ec:column property="card_no" headerStyle="text-align:center"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.cardno",getServletContext())%>'/>
                    <ec:column property="tx_date" headerStyle="text-align:center"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.txdate",getServletContext())%>'/>
                    <ec:column property="tx_time" headerStyle="text-align:center"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.txtime",getServletContext())%>'/>
                    <ec:column property="COL_TIMESTAMP" headerStyle="text-align:center"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.timestamp",getServletContext())%>'/>
                   
                     <ec:column property="lunch_type" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.type",getServletContext())%>'/>
                                   
                </ec:row>
                <ec:parameter name="tradedept" value='<%=request.getSession().getAttribute("tradedept")==null?"":URLEncoder.encode((String)request.getSession().getAttribute("tradedept"))%>'></ec:parameter>
            </ec:table>
        </td>
    </tr>
</table>


