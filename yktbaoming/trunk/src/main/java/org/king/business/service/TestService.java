package org.king.business.service;

import java.util.List;
import java.util.Map;

import org.king.business.domain.BmTest;

public interface TestService {

	public List getList(Map m);
	public List getnewaddList(Map m);
	public BmTest getDetail(String id);
	public List get4Update(String id);
	public List get4View(String id);
	public boolean save(BmTest bmTest);
	public boolean update(BmTest bmTest);
	public boolean delete(BmTest bmTest);
	
	public boolean check4Save(BmTest bmTest);
	public String check4Delete(String id);
	
	public List find(String sqlstring);
}
