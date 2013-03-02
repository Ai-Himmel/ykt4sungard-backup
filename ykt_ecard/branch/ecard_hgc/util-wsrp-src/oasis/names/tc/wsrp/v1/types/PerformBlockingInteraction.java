/**
 * PerformBlockingInteraction.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class PerformBlockingInteraction  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.RegistrationContext registrationContext;
    private oasis.names.tc.wsrp.v1.types.PortletContext portletContext;
    private oasis.names.tc.wsrp.v1.types.RuntimeContext runtimeContext;
    private oasis.names.tc.wsrp.v1.types.UserContext userContext;
    private oasis.names.tc.wsrp.v1.types.MarkupParams markupParams;
    private oasis.names.tc.wsrp.v1.types.InteractionParams interactionParams;

    public PerformBlockingInteraction() {
    }

    public PerformBlockingInteraction(
           oasis.names.tc.wsrp.v1.types.InteractionParams interactionParams,
           oasis.names.tc.wsrp.v1.types.MarkupParams markupParams,
           oasis.names.tc.wsrp.v1.types.PortletContext portletContext,
           oasis.names.tc.wsrp.v1.types.RegistrationContext registrationContext,
           oasis.names.tc.wsrp.v1.types.RuntimeContext runtimeContext,
           oasis.names.tc.wsrp.v1.types.UserContext userContext) {
           this.registrationContext = registrationContext;
           this.portletContext = portletContext;
           this.runtimeContext = runtimeContext;
           this.userContext = userContext;
           this.markupParams = markupParams;
           this.interactionParams = interactionParams;
    }


    /**
     * Gets the registrationContext value for this PerformBlockingInteraction.
     * 
     * @return registrationContext
     */
    public oasis.names.tc.wsrp.v1.types.RegistrationContext getRegistrationContext() {
        return registrationContext;
    }


    /**
     * Sets the registrationContext value for this PerformBlockingInteraction.
     * 
     * @param registrationContext
     */
    public void setRegistrationContext(oasis.names.tc.wsrp.v1.types.RegistrationContext registrationContext) {
        this.registrationContext = registrationContext;
    }


    /**
     * Gets the portletContext value for this PerformBlockingInteraction.
     * 
     * @return portletContext
     */
    public oasis.names.tc.wsrp.v1.types.PortletContext getPortletContext() {
        return portletContext;
    }


    /**
     * Sets the portletContext value for this PerformBlockingInteraction.
     * 
     * @param portletContext
     */
    public void setPortletContext(oasis.names.tc.wsrp.v1.types.PortletContext portletContext) {
        this.portletContext = portletContext;
    }


    /**
     * Gets the runtimeContext value for this PerformBlockingInteraction.
     * 
     * @return runtimeContext
     */
    public oasis.names.tc.wsrp.v1.types.RuntimeContext getRuntimeContext() {
        return runtimeContext;
    }


    /**
     * Sets the runtimeContext value for this PerformBlockingInteraction.
     * 
     * @param runtimeContext
     */
    public void setRuntimeContext(oasis.names.tc.wsrp.v1.types.RuntimeContext runtimeContext) {
        this.runtimeContext = runtimeContext;
    }


    /**
     * Gets the userContext value for this PerformBlockingInteraction.
     * 
     * @return userContext
     */
    public oasis.names.tc.wsrp.v1.types.UserContext getUserContext() {
        return userContext;
    }


    /**
     * Sets the userContext value for this PerformBlockingInteraction.
     * 
     * @param userContext
     */
    public void setUserContext(oasis.names.tc.wsrp.v1.types.UserContext userContext) {
        this.userContext = userContext;
    }


    /**
     * Gets the markupParams value for this PerformBlockingInteraction.
     * 
     * @return markupParams
     */
    public oasis.names.tc.wsrp.v1.types.MarkupParams getMarkupParams() {
        return markupParams;
    }


    /**
     * Sets the markupParams value for this PerformBlockingInteraction.
     * 
     * @param markupParams
     */
    public void setMarkupParams(oasis.names.tc.wsrp.v1.types.MarkupParams markupParams) {
        this.markupParams = markupParams;
    }


    /**
     * Gets the interactionParams value for this PerformBlockingInteraction.
     * 
     * @return interactionParams
     */
    public oasis.names.tc.wsrp.v1.types.InteractionParams getInteractionParams() {
        return interactionParams;
    }


    /**
     * Sets the interactionParams value for this PerformBlockingInteraction.
     * 
     * @param interactionParams
     */
    public void setInteractionParams(oasis.names.tc.wsrp.v1.types.InteractionParams interactionParams) {
        this.interactionParams = interactionParams;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof PerformBlockingInteraction)) return false;
        PerformBlockingInteraction other = (PerformBlockingInteraction) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.registrationContext==null && other.getRegistrationContext()==null) || 
             (this.registrationContext!=null &&
              this.registrationContext.equals(other.getRegistrationContext()))) &&
            ((this.portletContext==null && other.getPortletContext()==null) || 
             (this.portletContext!=null &&
              this.portletContext.equals(other.getPortletContext()))) &&
            ((this.runtimeContext==null && other.getRuntimeContext()==null) || 
             (this.runtimeContext!=null &&
              this.runtimeContext.equals(other.getRuntimeContext()))) &&
            ((this.userContext==null && other.getUserContext()==null) || 
             (this.userContext!=null &&
              this.userContext.equals(other.getUserContext()))) &&
            ((this.markupParams==null && other.getMarkupParams()==null) || 
             (this.markupParams!=null &&
              this.markupParams.equals(other.getMarkupParams()))) &&
            ((this.interactionParams==null && other.getInteractionParams()==null) || 
             (this.interactionParams!=null &&
              this.interactionParams.equals(other.getInteractionParams())));
        __equalsCalc = null;
        return _equals;
    }

    private boolean __hashCodeCalc = false;
    public synchronized int hashCode() {
        if (__hashCodeCalc) {
            return 0;
        }
        __hashCodeCalc = true;
        int _hashCode = 1;
        if (getRegistrationContext() != null) {
            _hashCode += getRegistrationContext().hashCode();
        }
        if (getPortletContext() != null) {
            _hashCode += getPortletContext().hashCode();
        }
        if (getRuntimeContext() != null) {
            _hashCode += getRuntimeContext().hashCode();
        }
        if (getUserContext() != null) {
            _hashCode += getUserContext().hashCode();
        }
        if (getMarkupParams() != null) {
            _hashCode += getMarkupParams().hashCode();
        }
        if (getInteractionParams() != null) {
            _hashCode += getInteractionParams().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(PerformBlockingInteraction.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", ">performBlockingInteraction"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("registrationContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "registrationContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "RegistrationContext"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("portletContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "portletContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "PortletContext"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("runtimeContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "runtimeContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "RuntimeContext"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("userContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "userContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "UserContext"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("markupParams");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "markupParams"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "MarkupParams"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("interactionParams");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "interactionParams"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "InteractionParams"));
        typeDesc.addFieldDesc(elemField);
    }

    /**
     * Return type metadata object
     */
    public static org.apache.axis.description.TypeDesc getTypeDesc() {
        return typeDesc;
    }

    /**
     * Get Custom Serializer
     */
    public static org.apache.axis.encoding.Serializer getSerializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanSerializer(
            _javaType, _xmlType, typeDesc);
    }

    /**
     * Get Custom Deserializer
     */
    public static org.apache.axis.encoding.Deserializer getDeserializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanDeserializer(
            _javaType, _xmlType, typeDesc);
    }

}
