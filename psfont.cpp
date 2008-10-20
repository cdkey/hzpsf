

#include "psfont.h"
#include <sstream>


PSFont::PSFont(string fontName):fontbase(fontName)
{

}

PSFont::~PSFont()
{
    //dtor
}
bool PSFont::Initialize(string fontName)
{
    m_psfOk=false;
    m_fontName=fontName;
    m_fontFile.open(m_fontName.c_str(),ios::in | ios::out);
    if(m_fontFile.is_open()) {
        return m_psfOk;
    }
    m_fontFile.read((char*)&m_magic,4);

    if((m_magic&0xffff)==PSF1_MAGIC) m_version=1;
    else if(m_magic==PSF2_MAGIC) m_version=2;
    else {
        return false;
    }
    m_psfOk=true;
    if(m_version==1){
        m_headersize=4;
		m_flags = (m_magic & 0x020000L) ? 1 : 0;  // PSF1_MODEHASTAB
		m_length = (m_magic & 0x010000L) ? 512 : 256;  // PSF1_MODE512
		m_charsize = ((m_magic >> 24) & 0xFF);
        m_height = m_charsize;
		m_width = 8;
    }
    if(m_version==2){
        int version ;
        m_fontFile.read((char*)&version,4);
        m_fontFile.read((char*)&m_headersize,4);
        m_fontFile.read((char*)&m_flags,4);
        m_fontFile.read((char*)&m_length,4);
        m_fontFile.read((char*)&m_charsize,4);
        m_fontFile.read((char*)&m_height,4);
        m_fontFile.read((char*)&m_width,4);
    }


    return m_psfOk;
}














