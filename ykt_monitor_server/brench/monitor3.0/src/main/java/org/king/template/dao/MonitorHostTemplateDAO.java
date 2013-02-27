package org.king.template.dao;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.template.domain.MonitorHostTemplate;

import java.io.Serializable;
import java.util.List;

public interface MonitorHostTemplateDAO extends DAO {

    public List find(MyQuery myQuery);

    public List find(String query);

    public MonitorHostTemplate get(Serializable id);

    public List getAll();

    public void save(MonitorHostTemplate transientInstance);

    public void update(MonitorHostTemplate transientInstance);

    public void delete(MonitorHostTemplate persistentInstance);

    public void findMonitorHostTemplateByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorHostTemplate(String templateName);
}