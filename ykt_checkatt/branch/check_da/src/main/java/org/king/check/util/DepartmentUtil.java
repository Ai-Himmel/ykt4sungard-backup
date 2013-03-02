package org.king.check.util;

import org.king.check.domain.Department;
import org.king.check.service.DepartmentTreeService;

import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-9-21
 */
public class DepartmentUtil {
    private static int PAGE_SIZE = 10;

    private static String FIRST_PAGE_ENABLE = "/check/pages/images/pinyin/firstPage.gif";
    private static String FIRST_PAGE_DISABLE = "/check/pages/images/pinyin/firstPageDisabled.gif";
    private static String PREV_PAGE_ENABLE = "/check/pages/images/pinyin/prevPage.gif";
    private static String PREV_PAGE_DISABLE = "/check/pages/images/pinyin/prevPageDisabled.gif";
    private static String NEXT_PAGE_ENABLE = "/check/pages/images/pinyin/nextPage.gif";
    private static String NEXT_PAGE_DISABLE = "/check/pages/images/pinyin/nextPageDisabled.gif";
    private static String LAST_PAGE_ENABLE = "/check/pages/images/pinyin/lastPage.gif";
    private static String LAST_PAGE_DISABLE = "/check/pages/images/pinyin/lastPageDisabled.gif";

    public static DepartmentTreeService departmentTreeService;

    public void setDepartmentTreeService(DepartmentTreeService departmentTreeService) {
        DepartmentUtil.departmentTreeService = departmentTreeService;
    }

    public static String getDepartments(List<Department> departments, int page) {
        return getDepartments(departments, page, PAGE_SIZE);
    }

    public static String getDepartments(List<Department> departments, int page, int pageSize) {
        StringBuffer result = new StringBuffer("");
        if (departments == null || departments.size() == 0) {
            result.append("<LI>没有找到对应的班级</LI>");
        } else {
            int start = pageSize * (page - 1);
            int end = pageSize * page - 1;
            if (end >= departments.size()) {
                end = departments.size() - 1;
            }

            result.append("<LI>").append("<UL class=\"droplist\" style=\"overflow-x:auto;width:100%;height:180px;white-space: nowrap;\">");
            for (int i = start; i <= end; i++) {
                Department department = departments.get(i);
                result.append("<LI>").append("<A onclick=\"setValue('").append(department.getId()).append("','").append(department.getName()).append("');\" style=\"cursor:pointer\">").append(department.getName()).append("</A></LI>");
            }
            result.append("</UL>").append("</LI>");
            result.append(getBanner(departments.size(), page, pageSize));
        }
        return result.toString();
    }

    public static String getBanner(int totalSize, int page, int pageSize) {
        int pageCount = (totalSize - 1) / pageSize + 1;
        StringBuffer banner = new StringBuffer("<LI>");
        banner.append("<UL class=\"droplist\" style=\"width:100%;height:20px;text-align:center\">");
        banner.append("<LI style=\"display:inline;\">");
        if (page == 1) {
            banner.append("<img src=\"").append(FIRST_PAGE_DISABLE).append("\"").append("style=\"border:0\" alt=\"第一页\" />&nbsp;&nbsp;&nbsp;&nbsp;");
            banner.append("<img src=\"").append(PREV_PAGE_DISABLE).append("\"").append("style=\"border:0\" alt=\"上一页\" />&nbsp;&nbsp;&nbsp;&nbsp;");
        } else {
            banner.append("<a href=\"javascript:goToPage('").append(1).append("')\">");
            banner.append("<img src=\"").append(FIRST_PAGE_ENABLE).append("\"").append("style=\"border:0\" alt=\"第一页\" />&nbsp;&nbsp;&nbsp;&nbsp;");
            banner.append("</a>");
            banner.append("<a href=\"javascript:goToPage('").append(page - 1).append("')\">");
            banner.append("<img src=\"").append(PREV_PAGE_ENABLE).append("\"").append("style=\"border:0\" alt=\"上一页\" />&nbsp;&nbsp;&nbsp;&nbsp;");
            banner.append("</a>");
        }

        if (page == pageCount) {
            banner.append("<img src=\"").append(NEXT_PAGE_DISABLE).append("\"").append("style=\"border:0\" alt=\"下一页\" />&nbsp;&nbsp;&nbsp;&nbsp;");
            banner.append("<img src=\"").append(LAST_PAGE_DISABLE).append("\"").append("style=\"border:0\" alt=\"最后页\" />&nbsp;&nbsp;&nbsp;&nbsp;");
        } else {
            banner.append("<a href=\"javascript:goToPage('").append(page + 1).append("')\">");
            banner.append("<img src=\"").append(NEXT_PAGE_ENABLE).append("\"").append("style=\"border:0\" alt=\"下一页\" />&nbsp;&nbsp;&nbsp;&nbsp;");
            banner.append("</a>");
            banner.append("<a href=\"javascript:goToPage('").append(pageCount).append("')\">");
            banner.append("<img src=\"").append(LAST_PAGE_ENABLE).append("\"").append("style=\"border:0\" alt=\"最后页\" />&nbsp;&nbsp;&nbsp;&nbsp;");
            banner.append("</a>");
        }
        banner.append("</LI></UL></LI>");
        return banner.toString();
    }

    public static String getErrorMessage() {
        return "查询班级失败";
    }
}
