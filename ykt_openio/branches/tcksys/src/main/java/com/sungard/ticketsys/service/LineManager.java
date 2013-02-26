package com.sungard.ticketsys.service;

import java.util.List;
import com.sungard.ticketsys.dao.LineDao;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.common.Page;



public class LineManager {
	
	private LineDao lineDAO = LineDao.getInstance();
	
	private static LineManager lineManager ;
    
    public static LineManager getInstance(){
        if(lineManager == null){
        	lineManager = new LineManager();
        }
        return lineManager;
    }
    
    @SuppressWarnings("unchecked")
	public List<Line> getLineByConditions(int pageNo, int pageSize, Line line, String orderBy) {
		Page page = lineDAO.getLineByCondition(pageNo, pageSize,line, orderBy);
		if (page != null) {
			return (List<Line>) page.getResult();
		}
		else {
			return null;
		}
	}
	
	public Page getLinePageByConditions(int pageNo, int pageSize,Line searchLine,String orderBy) {
		Page page=lineDAO.getLineByCondition(pageNo, pageSize, searchLine, orderBy);
			return page;
	}

	public Line getLine(String lineName) {
		return lineDAO.getLine(lineName);
	}

	public void removeLine(Line newLine) {
		lineDAO.remove(newLine);
	}

	public boolean checkLineIsUsed(String lineName) {
		return lineDAO.checkLine(lineName);
	}

	public void saveLine(Line line) {
		lineDAO.saveLine(line);
	}

	public void updateLine(Line infoLine) {
		lineDAO.updateLine(infoLine);
	}

	public List<Line> getAllLine() {
		return lineDAO.getAllLine();
	}

	/**
	 * 判断路线是否被使用
	 * @param linename
	 * @return
	 */
	public boolean lineIsUsed(String linename) {
		return lineDAO.lineIsUsed(linename);
	}
    
}
