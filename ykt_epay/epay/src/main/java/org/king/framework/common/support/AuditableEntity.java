package org.king.framework.common.support;

import java.util.Date;

public abstract interface AuditableEntity {
    public abstract Date getCreateTime();

    public abstract void setCreateTime(Date paramDate);

    public abstract Date getModifyTime();

    public abstract void setModifyTime(Date paramDate);

    public abstract IUser getCreateUser();

    public abstract void setCreateUser(IUser paramIUser);

    public abstract IUser getModifyUser();

    public abstract void setModifyUser(IUser paramIUser);
}