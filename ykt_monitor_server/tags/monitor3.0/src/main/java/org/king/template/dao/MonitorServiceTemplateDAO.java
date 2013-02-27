package org.king.template.dao;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.template.domain.MonitorServiceTemplate;

public interface MonitorServiceTemplateDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorServiceTemplate get(Serializable id);

	public List getAll();

	public void save(MonitorServiceTemplate transientInstance);

	public void update(MonitorServiceTemplate transientInstance);

	public void delete(MonitorServiceTemplate persistentInstance);

    public void findMonitorServiceTemplateByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorServiceTemplate(String templateName);

}