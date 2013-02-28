package org.king.framework.web.struts;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.tiles.TilesRequestProcessor;
import org.king.framework.service.ServiceLocator;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class ServiceAutowireRequestProcessor extends TilesRequestProcessor {
    protected Action processActionCreate(HttpServletRequest request, HttpServletResponse response, ActionMapping mapping)
            throws IOException {
        Action action = super.processActionCreate(request, response, mapping);
        autowireService(action);
        return action;
    }

    private void autowireService(Action action) {
        ServiceLocator.getInstance().autowireService(action);
    }
}