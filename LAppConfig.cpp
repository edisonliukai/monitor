#include "LAppConfig.h"
#include<QDebug>
LAppConfig LAppConfig::m_Instance;
LAppConfig::LAppConfig()
{

}

LAppConfig &LAppConfig::GetInstance()
{
    return m_Instance;
}

void LAppConfig::printData()
{
   // qDebug()<<"LAppconfig data....0.0";
}
