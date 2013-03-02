package org.king.check.common.tst;

import junit.framework.TestCase;
import org.king.check.domain.Department;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * .
 * User: Yiming.You
 * Date: 2010-9-20
 */
public class PinyinSearchTest extends TestCase {

    public void testStringSearch() {
        List<String> sources = new ArrayList<String>();
        sources.add("2009ͨ�Ű�");
        sources.add("2009��Ϣ�����");
        sources.add("2009��ư�");
        sources.add("2010���ù����");
        sources.add("2009��ѧ��");
        sources.add("2009(�����01��");
        sources.add("2009���ù����");

        SearchEngine<String> searchEngine = new PinyinTSTSearchEngine<String>(sources);
        List<String> list = searchEngine.searchAll("2009j");
        for (String s : list) {
            System.out.println(s);
        }
    }

    public void testDepartmentSearch() {
        List<Department> departments = new ArrayList<Department>();

        Department dept1 = new Department();
        dept1.setId("093100000012003");
        dept1.setName("2009�������ű���(ר�����)09�����̹������£�012003");
        departments.add(dept1);

        Department dept2 = new Department();
        dept2.setId("083100000012013");
        dept2.setName("2008�＾���ű���(ר�����)08���е������켰���Զ�������˳��012013");
        departments.add(dept2);

        Department dept3 = new Department();
        dept3.setId("093100000012001");
        dept3.setName("2009�������ű���(ר�����)09�����ѧ�����£�012001");
        departments.add(dept3);

        Department dept4 = new Department();
        dept4.setId("093100000012002");
        dept4.setName("2009�������ű���(ר�����)09�������������£�012002");
        departments.add(dept4);

        Department dept5 = new Department();
        dept5.setId("093100000012004");
        dept5.setName("2009�������ű���(ר�����)09�������������£�012004");
        departments.add(dept5);

        Department dept6 = new Department();
        dept6.setId("093100000012005");
        dept6.setName("2009�������ű���(ר�����)09��Ӣ��(���񣩣����£�012005");
        departments.add(dept6);

        DepartmentSearchEngine departmentSearchEngine = new DepartmentSearchEngine(departments);
        List<Department> list = departmentSearchEngine.searchAll("lf");
        for (Department department : list) {
            System.out.println("ID:" + department.getId() + "    NAME:" + department.getName());
        }
    }

    public void testPerformance() {
        String[] array = new String[]{"��", "��", "��", "��", "��", "��", "��", "��", "Ӣ", "��"};
        Random random = new Random();
        List<Department> departments = new ArrayList<Department>();
        for (int i = 0; i < 20000; i++) {
            Department department = new Department();
            int max = random.nextInt(9) + 1;
            String name = "";
            String id = "";
            for (int j = 0; j < max; j++) {
                name += array[random.nextInt(10)];
                id += j;
            }
            department.setName(name);
            department.setId(id);
            departments.add(department);
        }
        long time1 = System.currentTimeMillis();
        DepartmentSearchEngine departmentSearchEngine = new DepartmentSearchEngine(departments);
        long time2 = System.currentTimeMillis();
        System.out.println("it takes me " + (time2 - time1) + " millisecond to construct the department tree");

        List<Department> list = departmentSearchEngine.searchAll("kf");
        long time3 = System.currentTimeMillis();
        System.out.println("it takes me " + (time3 - time2) + " millisecond to search the department,and we find " + list.size());

        for (Department department : list) {
            System.out.println("ID:" + department.getId() + "    NAME:" + department.getName());
        }
    }

    public void testPinyin() {
        String str = "2006���Ϻ���󿪷�ר�Ƴ�����������������������";
        List<String> list = PinyinUtil.toHanyuPinyin(str);
        for (String s : list) {
            System.out.println("s = " + s);
        }
    }
}