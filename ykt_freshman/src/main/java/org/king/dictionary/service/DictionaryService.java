package org.king.dictionary.service;

import java.util.List;

import org.king.classmanage.domain.Dictionary;
import org.king.classmanage.domain.DictionaryId;

public interface DictionaryService {
	public List getDictionaryList(String flag);
	
	public boolean check4Add(DictionaryId dictionaryId);
	
	public void save(Dictionary dictionary);
	public void update(Dictionary dictionary);
	public Dictionary findbyId(String dictvalue,String dictno);
	public List find(String sqlstring);
}
