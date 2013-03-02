/**
 * PortletPropertyDescriptionResponse.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class PortletPropertyDescriptionResponse  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.ModelDescription modelDescription;
    private oasis.names.tc.wsrp.v1.types.ResourceList resourceList;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public PortletPropertyDescriptionResponse() {
    }

    public PortletPropertyDescriptionResponse(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           oasis.names.tc.wsrp.v1.types.ModelDescription modelDescription,
           oasis.names.tc.wsrp.v1.types.ResourceList resourceList) {
           this.modelDescription = modelDescription;
           this.resourceList = resourceList;
           this.extensions = extensions;
    }


    /**
     * Gets the modelDescription value for this PortletPropertyDescriptionResponse.
     * 
     * @return modelDescription
     */
    public oasis.names.tc.wsrp.v1.types.ModelDescription getModelDescription() {
        return modelDescription;
    }


    /**
     * Sets the modelDescription value for this PortletPropertyDescriptionResponse.
     * 
     * @param modelDescription
     */
    public void setModelDescription(oasis.names.tc.wsrp.v1.types.ModelDescription modelDescription) {
        this.modelDescription = modelDescription;
    }


    /**
     * Gets the resourceList value for this PortletPropertyDescriptionResponse.
     * 
     * @return resourceList
     */
    public oasis.names.tc.wsrp.v1.types.ResourceList getResourceList() {
        return resourceList;
    }


    /**
     * Sets the resourceList value for this PortletPropertyDescriptionResponse.
     * 
     * @param resourceList
     */
    public void setResourceList(oasis.names.tc.wsrp.v1.types.ResourceList resourceList) {
        this.resourceList = resourceList;
    }


    /**
     * Gets the extensions value for this PortletPropertyDescriptionResponse.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this PortletPropertyDescriptionResponse.
     * 
     * @param extensions
     */
    public void setExtensions(oasis.names.tc.wsrp.v1.types.Extension[] extensions) {
        this.extensions = extensions;
    }

    public oasis.names.tc.wsrp.v1.types.Extension getExtensions(int i) {
        return this.extensions[i];
    }

    public void setExtensions(int i, oasis.names.tc.wsrp.v1.types.Extension _value) {
        this.extensions[i] = _value;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof PortletPropertyDescriptionResponse)) return false;
        PortletPropertyDescriptionResponse other = (PortletPropertyDescriptionResponse) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.modelDescription==null && other.getModelDescription()==null) || 
             (this.modelDescription!=null &&
              this.modelDescription.equals(other.getModelDescription()))) &&
            ((this.resourceList==null && other.getResourceList()==null) || 
             (this.resourceList!=null &&
              this.resourceList.equals(other.getResourceList()))) &&
            ((this.extensions==null && other.getExtensions()==null) || 
             (this.extensions!=null &&
              java.util.Arrays.equals(this.extensions, other.getExtensions())));
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
        if (getModelDescription() != null) {
            _hashCode += getModelDescription().hashCode();
        }
        if (getResourceList() != null) {
            _hashCode += getResourceList().hashCode();
        }
        if (getExtensions() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getExtensions());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getExtensions(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(PortletPropertyDescriptionResponse.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "PortletPropertyDescriptionResponse"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("modelDescription");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "modelDescription"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ModelDescription"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("resourceList");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "resourceList"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ResourceList"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("extensions");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "extensions"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Extension"));
        elemField.setMinOccurs(0);
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
