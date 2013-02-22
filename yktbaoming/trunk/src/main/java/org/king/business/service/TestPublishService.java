package org.king.business.service;

import java.util.List;
import java.util.Map;

import org.king.business.domain.BmTestPublish;

public interface TestPublishService {

	public List getList(Map m);
	public BmTestPublish getDetail(String id);
	public List get4Update(String id);
	public List get4View(String id);
	public boolean save(BmTestPublish bmTestPublish);
	public boolean update(BmTestPublish bmTestPublish);
	public boolean delete(BmTestPublish bmTestPublish);
	public List find(String sqlstring);
}
