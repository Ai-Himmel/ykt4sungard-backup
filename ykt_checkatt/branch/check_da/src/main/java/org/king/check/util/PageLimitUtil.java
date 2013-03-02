package org.king.check.util;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.lang.StringUtils;
import org.extremecomponents.table.context.Context;
import org.extremecomponents.table.context.HttpServletRequestContext;
import org.extremecomponents.table.core.TableConstants;
import org.extremecomponents.table.filter.ExportFilterUtils;
import org.extremecomponents.table.limit.Limit;
import org.extremecomponents.table.limit.LimitFactory;
import org.extremecomponents.table.limit.TableLimit;
import org.extremecomponents.table.limit.TableLimitFactory;
import org.hibernate.Criteria;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.king.check.common.ec.DBPageLimit;
import org.king.framework.common.support.HqlPage;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.Para;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.springframework.orm.hibernate3.HibernateCallback;
import org.springframework.web.util.WebUtils;

/**
 * ec分页的帮助类.
 * 
 * User: Yiming.You
 * Date: 2010-09-17
 */
public class PageLimitUtil {
	/**
	 * 从request中获得分页参数，构造分页对象
	 * 
	 * @param tableId
	 * @param request
	 * @param page
	 */
	public static void pageInfoPopulate(String tableId,HttpServletRequest request, DBPageLimit page) {
		if (tableId == null) {
			tableId = "ec";
		}
		Context context = new HttpServletRequestContext(request);
		LimitFactory limitFactory = new TableLimitFactory(context, tableId);
		Limit limit = new TableLimit(limitFactory);
		page.setLimit(limit);
		String rcdStr = context.getParameter(tableId + "_" + TableConstants.CURRENT_ROWS_DISPLAYED);
		if (StringUtils.isNotBlank(rcdStr)) {
			page.setPageSize(Integer.parseInt(rcdStr));
		}
		if (ExportFilterUtils.isExported(context)) {
			page.setExported(true);
		}
		page.setOrderMap(WebUtils.getParametersStartingWith(request, tableId + "_" + TableConstants.SORT));
//		request.setAttribute("totalRows", new Integer(totalRows));
	}
	
	/**
     * 查找分页数据，如果exportValue不为空，则找出所有数据,以做导出使用
     *
     * @param page
     * @param baseDAOHibernate
     * @param myQuery
     */
    public static void executeHibernatePage(DBPageLimit page, BaseDAOHibernate baseDAOHibernate, MyQuery myQuery) {
        Query query = getQuery(baseDAOHibernate, myQuery);
        if(page.isMap()){
        	query.setResultTransformer(Criteria.ALIAS_TO_ENTITY_MAP);
        }
        if (!page.isExported()) {
            HqlPage hqlPage = HqlPage.getHibernatePageInstance(query, page.getPageNo(), page.getPageSize(), true);
            Object result = hqlPage.getResult();
            if (result != null && result instanceof List) {
            	page.setResult((List)result);
            } else {
                page.setResult(new ArrayList());
            }
            page.setTotalRows(hqlPage.getTotalSize());
        } else {
            page.setResult(query.list());
            page.setPageNo(1);
            page.setTotalRows(page.getResult().size());
            page.setPageSize(page.getTotalRows());
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
