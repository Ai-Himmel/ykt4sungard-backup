package org.king.template.dao;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.template.domain.MonitorContactTemplate;

import java.io.Serializable;
import java.util.List;

public interface MonitorContactTemplateDAO extends DAO {

    public List find(MyQuery myQuery);

    public List find(String query);

    public MonitorContactTemplate get(Serializable id);

    public List getAll();

    public void save(MonitorContactTemplate transientInstance);

    public void update(MonitorContactTemplate transientInstance);

    public void delete(MonitorContactTemplate persistentInstance);

    public void findMonitorContactTemplateByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorContactTemplate(String templateName);
}