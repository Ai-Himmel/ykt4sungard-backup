package org.king.check.service;
import java.util.List;

import org.king.check.domain.Worktimepara;

public interface WorkConfTimeParaService {

  public void saveWorkTimePara(Worktimepara workTimePara, String workTimeConfId);

  public void updateWorkTimePara(Worktimepara workTimePara);

  public void deleteWorkTimePara(String workTimeParaId);

  public Worktimepara getWorkTimePara(String workTimeParaId);

  public List getAll();
}