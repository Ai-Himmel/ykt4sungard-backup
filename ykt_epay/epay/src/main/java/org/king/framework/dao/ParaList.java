package org.king.framework.dao;

import java.util.ArrayList;

public class ParaList extends ArrayList {
    private static final long serialVersionUID = 3902920560642970858L;

    public final Para getParas(int index) {
        return (Para) super.get(index);
    }

    public final void addPara(int index, Para p) {
        super.add(index, p);
    }

    public final void addPara(Para p) {
        super.add(p);
    }

    public final int indexofPara(Para p) {
        return super.indexOf(p);
    }

    public final void removePara(int index) {
        super.remove(index);
    }
}