package org.king.yangong.dormitorymanage.service;

import java.util.List;

import org.king.yangong.dormitorymanage.domain.GraduateType;

public interface DormTypeManageService {
	public List getDormTypeList(String type);

	public Object getDormTypeInfo(String itemList);

	public void updateDormTypeInfo(GraduateType graduateType);

	public void saveDormTypeInfo(GraduateType graduateType);

	public void deleteDormTypeInfo(String[] itemLists);
	
//	�������ͳ��
	public List getDormStatbyCollege(String stuemp_no);
	
	public List getDormListFromGraduateTableLimit(String stuemp_no);
	
	public List getDormStatbyDorm(String stuemp_no);
	
	public List findGraduateByGT(String gt);
	
}