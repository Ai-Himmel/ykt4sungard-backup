<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec" %>
<%@ include file="/commons/init.jsp" %>
<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
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
                      rowsDisplayed="15">

                <ec:export
                        view="xls"
                        fileName="output.xls"/>
                <ec:row highlightRow="true">
                    <ec:column property="serial_no" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("handtrade.queryresult.serial_no",getServletContext())%>'/>
                    <ec:column property="STUEMP_NO" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("handtrade.queryresult.STUEMP_NO",getServletContext())%>'/>
                    <ec:column property="cut_name" headerStyle="text-align:center"
                               width="80"
                               style="text-align:center"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("handtrade.queryresult.cut_name",getServletContext())%>'/>
                    <ec:column property="card_id" headerStyle="text-align:center"
                               style="text-align:left"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("handtrade.queryresult.card_id",getServletContext())%>'/>
                    <ec:column property="operate_date" headerStyle="text-align:center"
                               style="text-align:left"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("handtrade.queryresult.operate_date",getServletContext())%>'/>
                    <ec:column property="operate_time" headerStyle="text-align:center"
                               style="text-align:left"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("handtrade.queryresult.operate_time",getServletContext())%>'/>
                    <ec:column property="collect_date" headerStyle="text-align:center"
                               style="text-align:left"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("handtrade.queryresult.collect_date",getServletContext())%>'/>
                    <ec:column property="collect_time" headerStyle="text-align:center"
                               style="text-align:left"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("handtrade.queryresult.collect_time",getServletContext())%>'/>
                    <ec:column property="enteract_date" headerStyle="text-align:center"
                               style="text-align:left"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("handtrade.queryresult.enteract_date",getServletContext())%>'/>
                    <ec:column property="enteract_time" headerStyle="text-align:center"
                               style="text-align:left"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("handtrade.queryresult.enteract_time",getServletContext())%>'/>
                    <ec:column property="devphy999_id" headerStyle="text-align:center"
                               style="text-align:left"
                               filterable="false"
                               sortable="false"
                               title='<%= GetProperty.getProperties("handtrade.queryresult.devphy999_id",getServletContext())%>'/>

                </ec:row>

            </ec:table>
        </td>
    </tr>
</table>

