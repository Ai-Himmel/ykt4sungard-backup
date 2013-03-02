package org.king.classmanage.service.impl;

import java.util.List;

import org.king.classmanage.service.StudentService;

import junit.framework.TestCase;

public class StudentServiceImplTest extends TestCase {
	private StudentService studentService;
	

	/**
	 * @param studentService The studentService to set.
	 */
	public void setStudentService(StudentService studentService) {
		this.studentService = studentService;
	}



	/*
	 * Test method for 'org.king.classmanage.service.impl.StudentServiceImpl.getCHNStudentCount()'
	 */
	public void testGetCHNStudentCount() {
		List list = studentService.getCHNStudentCount();
		System.out.print(list.size());
	}

	/*
	 * Test method for 'org.king.classmanage.service.impl.StudentServiceImpl.getAbroadStudentCount()'
	 */
	public void testGetAbroadStudentCount() {
		studentService.getAbroadStudentCount();
	}

}
