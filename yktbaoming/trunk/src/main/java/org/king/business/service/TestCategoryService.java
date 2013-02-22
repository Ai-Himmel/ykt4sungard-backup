package org.king.business.service;

import java.util.List;
import java.util.Map;

import org.king.business.domain.BmTestCat;

public interface TestCategoryService {

	public List getList(Map m);
	public List getnewaddList(Map m);
	public BmTestCat getDetail(String id);
	public List get4Update(String id);
	public List get4View(String id);
	public boolean save(BmTestCat bmTestCat);
	public boolean update(BmTestCat bmTestCat);
	public boolean delete(BmTestCat bmTestCat);
	
	public boolean check4Save(String testcatName,String id);
	public String check4Delete(String id);
}
