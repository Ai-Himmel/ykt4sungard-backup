package org.king.check.service;
import java.util.List;
import java.util.Map;
import org.apache.struts.action.DynaActionForm;
import org.king.check.domain.TChecktype;

public interface CheckTypeService {

  public void saveCheckType(TChecktype checkType);

  public void updateCheckType(TChecktype checkType);

  public void deleteCheckType(String checkTypeId);

  public TChecktype getCheckType(String checkTypeId);

  public List getAll();
  
  public List search(Map filter)throws Exception;
    
}