<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
<html> 
<body>
  <h2>Studenti</h2>
  <table border="1">
    <tr bgcolor="#9acd32">
      <th style="text-align:left">Name</th>
      <th style="text-align:left">Time</th>
      <th style="text-align:left">Data</th>
      <th style="text-align:left">Pol</th>
    </tr>
      <xsl:for-each select="FACULTY/SPECIALIZATION">
      <xsl:sort order="ascending" select="NAME"/>
      <tr bgcolor="#F5F5F5">
      <td><xsl:value-of select="NAME"/></td>
      <td><xsl:value-of select="TIME"/></td>
      <td><xsl:value-of select="DATA"/></td>
      <td><xsl:value-of select="POL"/></td>
    </tr>
    </xsl:for-each>
  </table>
</body>
</html>
</xsl:template>
</xsl:stylesheet>
