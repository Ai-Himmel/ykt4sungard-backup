package org.king.utils;

import org.apache.commons.lang.StringUtils;
import org.displaytag.tags.TableTagParameters;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.common.support.HqlPage;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.Para;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.springframework.orm.hibernate3.HibernateCallback;

import javax.servlet.http.HttpServletRequest;
import java.sql.Date;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-4
 */
public class PaginationUtil {

    /**
     * 方法用于获得displaytag的参数
     *
     * @param tableId
     * @param request
     * @param page
     */
    public static void pageInfoPopulate(String tableId, HttpServletRequest request, DBPaginatedList page) {
        if (request == null || page == null || tableId == null) {
            return;
        }
        //排序字段
//        String sort = request.getParameter(new ParamEncoder(tableId).encodeParameterName(TableTagParameters.PARAMETER_SORT));
        //升序还是降序
//        String order = request.getParameter(new ParamEncoder(tableId).encodeParameterName(TableTagParameters.PARAMETER_ORDER));
        //当前页数
//        String currentPage = request.getParameter(new ParamEncoder(tableId).encodeParameterName(TableTagParameters.PARAMETER_PAGE));
        String exportValue = request.getParameter(TableTagParameters.PARAMETER_EXPORTING);

        String currentPage = request.getParameter("page");
        String pageSize = request.getParameter("pageSize");
        String sort = request.getParameter("sort");
        String order = request.getParameter("dir");
        if (StringUtils.isNotBlank(exportValue)) {
            page.setExportValue(exportValue);
        }
        if (StringUtils.isNotBlank(sort)) {
            page.setSortCriterion(sort);
        }
        if (StringUtils.isNotBlank(order)) {
            page.setOrder(order);
        }
        if (StringUtils.isNotBlank(currentPage)) {
            page.setPageNo(Integer.parseInt(currentPage));
        }
        if (StringUtils.isNotBlank(pageSize)) {
            page.setPageSize(Integer.parseInt(pageSize));
        }
        request.setAttribute("currentPage", currentPage);
        request.setAttribute("pageSize", pageSize);
        request.setAttribute("sort", sort);
        request.setAttribute("dir", order);
    }

    /**
     * 查找分页数据，如果exportValue不为空，则找出所有数据,以做导出使用
     *
     * @param page
     * @param baseDAOHibernate
     * @param myQuery
     */
    public static void executeHibernatePage(DBPaginatedList page, BaseDAOHibernate baseDAOHibernate, MyQuery myQuery) {
        Query query = getQuery(baseDAOHibernate, myQuery);
        if (StringUtils.isBlank(page.getExportValue())) {
            HqlPage hqlPage = HqlPage.getHibernatePageInstance(query, page.getPageNumber(), page.getObjectsPerPage(), true);
            Object result = hqlPage.getResult();
            if (result != null && result instanceof List) {
                page.setResult((List) result);
            } else {
                page.setResult(new ArrayList());
            }

            page.setTotalCount(hqlPage.getTotalSize());
        } else {
            page.setResult(query.list());
            page.setPageNo(1);
            page.setTotalCount(page.getList().size());
            page.setPageSize(page.getFullListSize());
        }
    }

    /**
     * 将MyQuery对象转换成Query对象，主要用于分页
     *
     * @param baseDAOHibernate
     * @param myQuery
     * @return
     */
    public static Query getQuery(final BaseDAOHibernate baseDAOHibernate, final MyQuery myQuery) {
        return ((Query) baseDAOHibernate.getHibernateTemplate().execute(new HibernateCallback() {
            public Object doInHibernate(Session session) throws HibernateException {
                StringBuffer queryString = new StringBuffer(myQuery.getQueryString());

                if (myQuery.getGroupby() != null) {
                    queryString.append(myQuery.getGroupby());
                }
                if (myQuery.getOrderby() != null) {
                    queryString.append(myQuery.getOrderby());
                }

                Query query = session.createQuery(queryString.toString());
                if (myQuery.getParalist() != null) {
                    List list = myQuery.getParalist();

                    int i = 0;
                    for (int n = list.size(); i < n; ++i) {
                        Para param = (Para) list.get(i);

                        switch (param.getTypeNo()) {
                            case 12:
                                query.setString(i, param.getPName().toString());
                                break;
                            case 4:
                                query.setInteger(i, ((Integer) param.getPName()).intValue());
                                break;
                            case 91:
                                query.setDate(i, (Date) param.getPName());
                                break;
                            case 8:
                                query.setDouble(i, ((Double) param.getPName()).doubleValue());
                                break;
                            case 16:
                                query.setBoolean(i, ((Boolean) param.getPName()).booleanValue());
                                break;
                            case 1:
                                query.setCharacter(i, ((Character) param.getPName()).charValue());
                        }
                    }
                }

                query.setCacheable(true);
                query.setCacheRegion("frontpages");
                return query;
            }
        }));
    }
}
