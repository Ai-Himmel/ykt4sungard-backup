package org.king.template.dao;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.template.domain.MonitorTermdevTemplate;
import org.king.template.domain.MonitorTermdevTemplateAll;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-7
 */
public interface MonitorTermdevTemplateDAO extends DAO {

    public List find(MyQuery myQuery);

    public List find(String query);

    public MonitorTermdevTemplate get(Serializable id);
    
    public MonitorTermdevTemplateAll getTermdevTemplateAll(Serializable id);
    
    public MonitorTermdevTemplate getEnableMonitorTermdevTemplate();

    public List getAll();

    public void save(MonitorTermdevTemplate transientInstance);

    public void update(MonitorTermdevTemplate transientInstance);
    
    public void updateTermdevTemplateAll(MonitorTermdevTemplateAll transientInstance);

    public void delete(MonitorTermdevTemplate persistentInstance);

    public void findMonitorTermdevTemplateByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorTermdevTemplate(String templateName);
}
