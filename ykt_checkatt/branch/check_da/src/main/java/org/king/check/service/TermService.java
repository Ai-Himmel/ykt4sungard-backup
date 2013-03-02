package org.king.check.service;

import java.util.List;

import org.king.check.domain.TTerm;

public interface TermService {

	public void  saveTerm(TTerm term);
	
	public List  findTerm(String  termName);
	
	public TTerm  getTerm(String id);
	
	public  void  delteTerm(String id);
	
	public TTerm  findTermByName(String termName);
	
	public void updateTerm(TTerm term);
	
	public List findAllTerm();
	
}
