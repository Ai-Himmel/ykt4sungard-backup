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
                      locale="zh_CN"
                      >

                <ec:export
                        view="xls"
                        fileName="output.xls"/>
                <ec:row highlightRow="true">
                    <ec:column property="deptname" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.dept",getServletContext())%>'/>
                    <ec:column property="stuempno" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.stuempno",getServletContext())%>'/>
                    <ec:column property="cutname" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.cutname",getServletContext())%>'/>
                               
                     <ec:column property="typename" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.typename",getServletContext())%>'/>     
                                 
                      <ec:column property="lunchtype" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.type",getServletContext())%>'/>                   
                    
                    <ec:column property="total" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("lunch.query.total",getServletContext())%>'/>
                          
                </ec:row>
				<ec:parameter name="tradedept" value='<%=request.getSession().getAttribute("tradedept")==null?"":URLEncoder.encode((String)request.getSession().getAttribute("tradedept"))%>'></ec:parameter>
            </ec:table>
        </td>
    </tr>
</table>

